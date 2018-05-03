#include "IServerLogic.h"

#include "ToolFrame.h"
#include "MProtocol.h"
#include "MThread.h"
#include "MSystem.h"

#include "IServerCache.h"
#include "TimeOut.h"

#include "MDebug.h"
#include "MMemory.h"

#include "UrlRequestTopology.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

IServerLogic::IServerLogic(void)
{
	_bDebugReport = ToolFrame::IsDebugVer();
	_bInited = false;
	_xTopologyLogic.SetListener(this);
	_mgrCache.SetCacheHandler(this);
}

IServerLogic::~IServerLogic(void)
{
	MSystem::Singleton().SetHandler(nullptr);
	MLoger::Singleton().SetHandler(nullptr);
}

bool IServerLogic::Init()
{
	MSystem::Singleton().SetHandler(this);
	MLoger::Singleton().SetHandler(this);

	//启动拓扑逻辑端
	{
		std::string sCommandLine = GetCommandLine();
		_xTopologyLogic.SetCommandLine(sCommandLine);
		if (!_xTopologyLogic.Init())return false;
	}

	//初始化日志
	{
		MLoger::Singleton().SetTag(MAKE_STRING(_xTopologyLogic.GetServerID()));
	}

	//修改控制台Title
	{
		std::stringstream sStream;
		sStream<<"["<<ToolFrame::GetProcessId()<<"]ServerID:"<<_xTopologyLogic.GetServerID() <<" "<<GetProcessNameWithOutExt();
		SetConsoleTitle(sStream.str());
	}

	//启动系统
	{
		uint uThreadCount=_xTopologyLogic.GetThread();

		//启动线程
		_mgrElasticThread.SetThreadMax(uThreadCount);
	}

	//启动缓存
	if (!_mgrCache.Init())return false;

	LOG_SYSTEM("ServerID:"<<_xTopologyLogic.GetServerID());
	return IServer::Init();
}

int IServerLogic::GetServerID() const
{
	return _xTopologyLogic.GetServerID();
}

int IServerLogic::GetServerType() const
{
	return _xTopologyLogic.GetServerType();
}

CServerCacheManager& IServerLogic::GetCacheManager()
{
	return _mgrCache;
}

const CServerCacheManager& IServerLogic::GetCacheManager() const
{
	return _mgrCache;
}

uint IServerLogic::FindServerID( uint uClientID )const
{
	return _xTopologyLogic.FindServerID(uClientID);
}

uint IServerLogic::FindClientID(uint uServerID) const
{
	return _xTopologyLogic.FindClientID(uServerID);
}

uint IServerLogic::SendSrvType(int eSrvType, const IMsgStream& msg) const
{
	return SendSrvType(eSrvType, TOPOLOGY_ID_INVAILD, msg);
}

uint IServerLogic::SendSrvType(int eSrvType, const XTopologyID& xSrcID, const IMsgStream& msg) const
{
	return SendSrvType(eSrvType, xSrcID, msg, xSrcID.uUserID);
}

uint IServerLogic::SendSrvType(int eSrvType, const XTopologyID& xSrcID, const IMsgStream& msg, uint uUserID) const
{
	return _xTopologyLogic.SendSrvType(eSrvType, msg.GetSendStream(), xSrcID, uUserID);
}

uint IServerLogic::SendRandom(int eSrvType, const IMsgStream& msg)const
{
	return SendRandom(eSrvType,TOPOLOGY_ID_INVAILD,msg);
}

uint IServerLogic::SendRandom( int eSrvType,const XTopologyID& xSrcID,const IMsgStream& msg )const
{
	return SendRandom(eSrvType,xSrcID,msg,xSrcID.uUserID);
}

uint IServerLogic::SendRandom( int eSrvType,const XTopologyID& xSrcID,const IMsgStream& msg,uint uUserID ) const
{
	return _xTopologyLogic.SendRandom(eSrvType, msg.GetSendStream(),xSrcID,uUserID);
}

uint IServerLogic::SendBalance(int eSrvType, const IMsgStream& msg) const
{
	return SendBalance(eSrvType, TOPOLOGY_ID_INVAILD, msg);
}

uint IServerLogic::SendBalance(int eSrvType, const XTopologyID& xSrcID, const IMsgStream& msg) const
{
	return SendBalance(eSrvType, xSrcID, msg, xSrcID.uUserID);
}

uint IServerLogic::SendBalance(int eSrvType, const XTopologyID& xSrcID, const IMsgStream& msg, uint uUserID) const
{
	return _xTopologyLogic.SendBalance(eSrvType, msg.GetSendStream(), xSrcID, uUserID);
}

bool IServerLogic::BoardCast(int eSrvType, const IMsgStream& msg, const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, uint uUserID/*=INVALID_ID*/) const
{
	return _xTopologyLogic.BroadCast(eSrvType, msg.GetSendStream(),xSrcID,uUserID);
}

uint IServerLogic::SendGateWaySrv(const XTopologyID& uID, StreamBinaryPtr ptr)const
{
	return SendSrvID(uID.uGtID, ptr, uID);
}

uint IServerLogic::SendGateWaySrv(const XTopologyID& uID, const IMsgStream& msg)const
{
	return SendSrvID(uID.uGtID, msg, uID);
}

bool IServerLogic::SendGateWaySrv(const VectorTopologyID& vTopologyID, StreamBinaryPtr ptr)const
{
	if (vTopologyID.empty())return false;
	
	VectorTopologyID::const_iterator itr;
	foreach(itr, vTopologyID) {
		SendGateWaySrv(*itr, ptr);
	}
	return true;
}

bool IServerLogic::SendGateWaySrv(const VectorTopologyID& vTopologyID, const IMsgStream& msg)const
{
	if (vTopologyID.empty())return false;

	VectorTopologyID::const_iterator itr;
	foreach(itr, vTopologyID) {
		SendGateWaySrv(*itr, msg);
	}
	return true;
}

uint IServerLogic::SendSrvID(int nServerID, const IMsgStream& msg, const XTopologyID& uID /*= TOPOLOGY_ID_INVAILD*/) const
{
	return SendSrvID(nServerID, msg.GetSendStream(),uID,uID.uUserID);
}

uint IServerLogic::SendSrvID( int nServerID, StreamBinaryPtr ptr,const XTopologyID& uID /*= TOPOLOGY_ID_INVAILD*/ ) const
{
	return SendSrvID(nServerID,ptr,uID,uID.uUserID);
}

uint IServerLogic::SendSrvID( int nServerID,const IMsgStream& msg,const XTopologyID& uID,uint32 uUserID ) const
{
	return SendSrvID(nServerID, msg.GetSendStream(),uID,uUserID);
}

uint IServerLogic::SendSrvID( int nServerID, StreamBinaryPtr ptr,const XTopologyID& uID,uint32 uUserID ) const
{
	uint uClientID = _xTopologyLogic.SendServerID(nServerID,ptr,uID,uUserID);
	if (INVALID_ID == uClientID)
	{
		OnSendFaild(nServerID,uID,ptr);
		return INVALID_ID;
	}

	return uClientID;
}

uint IServerLogic::SendSrvID( const XTopologyID& xSrcID, StreamBinaryPtr ptr,uint32 uUserID ) const
{
	return SendSrvID(xSrcID.uGtID,ptr,xSrcID,uUserID);
}

uint IServerLogic::SendSrvID( const XTopologyID& xSrcID, StreamBinaryPtr ptr ) const
{
	return SendSrvID(xSrcID.uGtID,ptr,xSrcID,xSrcID.uUserID);
}

uint IServerLogic::SendSrvID( const XTopologyID& xSrcID,const IMsgStream& msg,uint32 uUserID ) const
{
	return SendSrvID(xSrcID.uGtID, msg.GetSendStream(),xSrcID,uUserID);
}

uint IServerLogic::SendSrvID( const XTopologyID& xSrcID,const IMsgStream& msg ) const
{
	return SendSrvID(xSrcID.uGtID, msg.GetSendStream(),xSrcID,xSrcID.uUserID);
}

bool IServerLogic::SetStateNormal()
{
	return _xTopologyLogic.SetStateNormal();
}

bool IServerLogic::SetStateStop()
{
	return _xTopologyLogic.SetStateStop();
}

bool IServerLogic::IsDebugReport() const
{
	return _bDebugReport;
}

bool IServerLogic::IsInited() const
{
	return _bInited;
}

bool IServerLogic::SetInited( bool bInited )
{
	_bInited = bInited;
	return true;
}

bool IServerLogic::SetCacheVaild(size_t uCacheVaild )
{
	return _xTopologyLogic.SetCacheVaild(uCacheVaild);
}

bool IServerLogic::SetCacheTotal(size_t uCacheTotal )
{
	return _xTopologyLogic.SetCacheTotal(uCacheTotal);
}

bool IServerLogic::SetProcesserCount(size_t uCacheTotal)
{
	return _xTopologyLogic.SetProcesserCount(uCacheTotal);
}

bool IServerLogic::SetQueueSize(size_t uQueueSize)
{
	return _xTopologyLogic.SetQueueSize(uQueueSize);
}

bool IServerLogic::SetQueueProcess(size_t uQueueProcess )
{
	return _xTopologyLogic.SetQueueProcess(uQueueProcess);
}

bool IServerLogic::SetDebugReport(bool bReport)
{
	_bDebugReport = bReport;
	return true;
}

bool IServerLogic::OnServerAllConnected()
{
	SetStateNormal();
	return true;
}

bool IServerLogic::OnServerReport()
{
	_xTopologyLogic.SetRunOnceTimeAvg(_mgrElasticThread.GetRunOnceTimeAvg());
	_xTopologyLogic.SetRunOnceTimeMax(_mgrElasticThread.GetRunOnceTimeMax());
	_xTopologyLogic.SetRunTimes(_mgrElasticThread.GetRunTimes());
	_xTopologyLogic.SetRunTimeOutRate(_mgrElasticThread.GetRunTimeOutRate());
	_xTopologyLogic.SetRunElapsed(_mgrElasticThread.GetRunElapsed() / (_mgrElasticThread.Count() + 1 ));// +1原因是当前还有一个主线程在跑，这里求的是平均每根线程的运行时间 

	SetCacheVaild(_mgrCache.GetVaildCount());
	SetCacheTotal(_mgrCache.GetTotalCount());
	SetProcesserCount(_mgrCache.GetTotalCount());
	SetQueueSize(_mgrCache.GetOperateCount());
	SetQueueProcess(_mgrCache.ClearOperateProcess());

	if (IsDebugReport())
		DebugReport();

	return true;
}

uint IServerLogic::SendClientID( uint uClientID,const IMsgStream& msg,const XTopologyID& uID,uint32 uUserID )const
{
	return _xTopologyLogic.SendClientID(uClientID, msg.GetSendStream(),uID,uUserID);
}

uint IServerLogic::SendClientID( uint uClientID,const IMsgStream& msg,const XTopologyID& uID )const
{
	return _xTopologyLogic.SendClientID(uClientID, msg.GetSendStream(),uID,uID.uUserID);
}

uint IServerLogic::SendClientID( uint uClientID,const IMsgStream& msg )const
{
	return _xTopologyLogic.SendClientID(uClientID, msg.GetSendStream(),TOPOLOGY_ID_INVAILD,INVALID_ID);
}

uint IServerLogic::SendClientID( uint uClientID, StreamBinaryPtr ptr,const XTopologyID& uID,uint32 uUserID )const
{
	return _xTopologyLogic.SendClientID(uClientID,ptr,uID,uUserID);
}

bool IServerLogic::OnRunElasticThread()
{
	CTimeOut xTimeOut(_xTopologyLogic.GetRunOnceMax());

	bool bTimeOut1 = IServer::OnRunElasticThread();
	bool bTimeOut3 = _mgrCache.Run(200);
	bool bTimeOut4 = OnRunElasticThreadExtra();
	bool bTimeOut5 = xTimeOut.IsTimeOut();

// 	if (bTimeOut1)
// 	{
// 		LOG_WARNING("[TimeOut]IServer::RunElasticThread");
// 	}
// 	if (bTimeOut3)
// 	{
// 		LOG_WARNING("[TimeOut]ExecuteOperate");
// 	}
// 	if (bTimeOut4)
// 	{
// 		LOG_WARNING("[TimeOut]OnRunElasticThreadExtra");
// 	}
// 	if (bTimeOut5)
// 	{
// 		LOG_WARNING("[TimeOut]OnRunElasticThread");
// 	}

	return bTimeOut1 || bTimeOut3 || bTimeOut4 || bTimeOut5;
}

bool IServerLogic::OnRunElasticThreadExtra()
{
	return false;
}

bool IServerLogic::OnServerSave()
{
	_mgrCache.SyncAllSave();
	return true;
}

bool IServerLogic::OnServerCleanUp()
{
	_mgrCache.SyncAllDestory();
	return true;
}

bool IServerLogic::OnServerStopService()
{
	SetStateStop();
	return true;
}

bool IServerLogic::OnServerShutDown()
{
	ShutDown();
	return true;
}

bool IServerLogic::OnServerRecved(const XServerArg& xServerArg, IMsgStream& msgBase)
{
	DEBUG_POINT_TAG("OnServerRecved SrvID:" << xServerArg.uServerID);
	return false;
}

std::string IServerLogic::OnServerDebug(const VectorString& vDebug)
{
	std::stringstream sStream;
	if (ToolFrame::IsHasValue(vDebug,"Memory")){
		sStream << MMemory::Singleton().GetMgr().DebugString() << std::endl;
	}

	if (ToolFrame::IsHasValue(vDebug, "CallStack")) {
		sStream << ToolFrame::GetCallStackAll() << std::endl;
	}

	sStream << MDebug::Singleton().DebugString(vDebug) << std::endl;
	return sStream.str();
}

bool IServerLogic::OnSendFaild( int nServerID,const XTopologyID& uID, StreamBinaryPtr ptr ) const
{
	return true;
}

CUrlRequestTopologyPtr IServerLogic::UrlRequest(const XTopologyID& xSrcID, uint uID, int eType, const std::string& sUrl, uint uSrvID /*= INVALID_ID*/)
{
	CUrlProcessor& xUrlProcessor = ToolFrame::MSystem::Singleton().GetUrlProcessor();

	//发送请求
	CUrlRequestTopologyPtr pRequest(new CUrlRequestTopology());
	ASSERT_LOG_ERROR(pRequest);

	pRequest->SetHandler(this);
	pRequest->SetUrl(sUrl);
	pRequest->SetType(eType);

	pRequest->SetID(uID);
	pRequest->SetServerID(uSrvID);
	pRequest->SetTopologyID(xSrcID);

	xUrlProcessor.AddRequest(pRequest);
	return pRequest;
}

CUrlRequestTopologyPtr IServerLogic::UrlRequest(const XTopologyID& xSrcID, uint uID, CUrlRequestTopologyPtr pRequest)
{
	if (INVALID_ID == uID)return CUrlRequestTopologyPtr();
	if (!pRequest)return CUrlRequestTopologyPtr();
	if (pRequest->GetUrl().empty())return CUrlRequestTopologyPtr();

	CUrlProcessor& xUrlProcessor = ToolFrame::MSystem::Singleton().GetUrlProcessor();

	pRequest->SetHandler(this);
	pRequest->SetID(uID);
	pRequest->SetTopologyID(xSrcID);

	xUrlProcessor.AddRequest(pRequest);
	return pRequest;
}

CUrlRequestTopologyPtr IServerLogic::UrlRequest(const XTopologyID& xSrcID, const std::string& sUrl)
{
	if (sUrl.empty())return CUrlRequestTopologyPtr();

	CUrlProcessor& xUrlProcessor = ToolFrame::MSystem::Singleton().GetUrlProcessor();

	//发送请求
	CUrlRequestTopologyPtr pRequest(new CUrlRequestTopology());
	ASSERT_LOG_ERROR(pRequest);

	pRequest->SetHandler(this);
	pRequest->SetUrl(sUrl);
	pRequest->SetTopologyID(xSrcID);

	xUrlProcessor.AddRequest(pRequest);
	return pRequest;
}

CUrlRequestTopologyPtr IServerLogic::UrlRequest(const std::string& sUrl)
{
	if (sUrl.empty())return CUrlRequestTopologyPtr();

	CUrlProcessor& xUrlProcessor = ToolFrame::MSystem::Singleton().GetUrlProcessor();

	//发送请求
	CUrlRequestTopologyPtr pRequest(new CUrlRequestTopology());
	ASSERT_LOG_ERROR(pRequest);

	pRequest->SetHandler(this);
	pRequest->SetUrl(sUrl);

	xUrlProcessor.AddRequest(pRequest);
	return pRequest;
}

bool IServerLogic::OnFinished(IUrlRequestPtr pRequest)
{
	ASSERT_LOG_ERROR(pRequest);

	if (INVALID_ID == pRequest->GetID())
		return true;

	CUrlRequestTopologyPtr pRequestTopology;
	ToolFrame::DynamicCast(pRequestTopology, pRequest);

	ASSERT_LOG_ERROR(pRequestTopology);

	return _mgrCache.SyncUrlResponce(pRequest->GetID(), pRequestTopology);
}

bool IServerLogic::DebugReport()
{
	uint uTotal = 0; uint uVaild = 0; uint uNormal = 0; uint uQueue = 0; uint uDelete = 0; uint uPerpairing = 0; uint uCache = 0; uint uOperateQueue = 0; uint uDelayOperateQueue = 0;
	if (!_mgrCache.SyncCalState(uTotal, uVaild, uNormal, uQueue, uDelete, uPerpairing, uCache, uOperateQueue, uDelayOperateQueue))return false;

	LOG_SYSTEM("CacheState: Total:" << uTotal << " Vaild:" << uVaild << " Normal:" << uNormal << " Cache:" << uCache << " Perairing:" << uPerpairing << " Queue:" << uQueue << " Delete:" << uDelete << " OperateQueue:" << uOperateQueue << " DelayOperateQueue:" << uDelayOperateQueue);
	return true;
}

NS_TOOL_FRAME_END
