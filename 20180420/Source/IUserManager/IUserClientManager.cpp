#include "IUserClientManager.h"
#include "IUserClient.h"
#include "ToolFrame.h"
#include "MLoger.h"
#include "MSystem.h"
#include "MDebug.h"

NS_TOOL_FRAME_BEGIN

IUserClientManager::IUserClientManager()
{
	_uCheckTime = 30;
	_uTimeOut = 300;
	_uRecvMax = 0;
	_uRecvPer = 0;

	_bInit = false;

	SetSrvID(INVALID_ID);
}

IUserClientManager::~IUserClientManager()
{
	MSystem::Singleton().GetTimeOutQueque().RemoveTimer(_pTimerCheck);
}

bool IUserClientManager::SetCheckTime(uint uTimeOut)
{
	_uCheckTime = uTimeOut;
	return true;
}

bool IUserClientManager::SetTimeOut(uint uTimeOut)
{
	_uTimeOut = uTimeOut;
	return true;
}

bool IUserClientManager::SetRecvPack(uint uRecvMax, uint uRecvPer)
{
	_uRecvMax = uRecvMax;
	_uRecvPer = uRecvPer;
	return true;
}

bool IUserClientManager::Init()
{
	if (_bInit)return false;

	if (INVALID_ID == GetSrvID())return false;

	ASSERT_LOG_ERROR(!_pTimerCheck);
	_pTimerCheck = MSystem::Singleton().GetTimeOutQueque().CreateTimerByAfterSec(this, _uCheckTime, true, _uCheckTime);

	_bInit = true;
	return true;
}

bool IUserClientManager::SyncDisconnectAll(bool bActive /*= true*/)
{
	return SyncForEachCallProcesser<IUserClient>(&IUserClient::SyncDisconnected, bActive);
}

bool IUserClientManager::SyncDisconnect(uint uAssID, bool bActive /*= true*/)
{
	return SyncCallProcesserSecondID<IUserClient>(uAssID, &IUserClient::SyncDisconnected, bActive);
}

bool IUserClientManager::SyncTryServerRecved(const XServerArg& xServerArg, const IMsgStream& msgBase)
{
	DEBUG_POINT_FUN();
	return SyncTryCallProcesserSecondID<IUserClient>(xServerArg.xSrcID.uID, &IUserClient::SyncServerRecved, xServerArg, msgBase);
}

bool IUserClientManager::SyncClientConnected(uint uClientID)
{
	{
		CLockWrite lock(GetMutex());

		uint uAssID = MakeSecondID();
		if (INVALID_ID == uAssID)return false;

		ISyncProcesserPtr pProcesser = _hHandler->OnCreateProcesser();
		if (!pProcesser)return false;

		pProcesser->SetProcesserID(uClientID);
		pProcesser->SetSecondID(uAssID);
		pProcesser->SetMgr(this);

		IUserClient* pClient = pProcesser->ToProcesser<IUserClient>();
		if (!pClient)return false;
		
		pClient->Init(GetSrvID(),uClientID, uAssID);

		//添加到索引表
		ASSERT_LOG_ERROR(AutoInsertProcesser(pProcesser));

		pClient->SyncClientConnected(uClientID);
		pClient->Process();
	}
	return true;
}

bool IUserClientManager::SyncClientDisconnect(uint uClientID)
{
	return SyncCallProcesser<IUserClient>(uClientID, &IUserClient::SyncClientDisconnected);
}

bool IUserClientManager::SyncTryClientRecved(uint uClientID, const IMsgStream& msgStream)
{
	DEBUG_POINT_FUN();

	return SyncTryCallProcesser<IUserClient>(uClientID, &IUserClient::SyncClientRecvStream, msgStream);
}

bool IUserClientManager::SyncTryClientRecved(uint uClientID, StreamBinaryPtr pMsgStream)
{
	DEBUG_POINT_FUN();

	if (!pMsgStream)return false;
	if (pMsgStream->IsEmpty())return false;
	return SyncTryCallProcesser<IUserClient>(uClientID, &IUserClient::SyncClientRecvBuffer, pMsgStream);
}

bool IUserClientManager::SyncClientUrlResponce(uint uClientID, CUrlRequestTopologyPtr pRequest)
{
	DEBUG_POINT_FUN();

	if (!pRequest)return false;
	return SyncTryCallProcesser<IUserClient>(uClientID, &IUserClient::SyncClientUrlResponce, pRequest);
}

bool IUserClientManager::SyncSendClient(uint uClientID, const void* pBuffer, size_t uLen, bool bSecret /*= true*/)
{
	return SyncCallProcesser<IUserClient>(uClientID, (bool(IUserClient::*)(const void*, size_t, bool)) &IUserClient::SyncSendClient, pBuffer, uLen, bSecret);
}

bool IUserClientManager::SyncSendClient(uint uClientID, const std::string& sMsg, bool bSecret /*= true*/)
{
	return SyncCallProcesser<IUserClient>(uClientID, (bool(IUserClient::*)(const std::string&, bool))&IUserClient::SyncSendClient, sMsg, bSecret);
}

bool IUserClientManager::SyncSendClient(uint uClientID, StreamBinaryPtr ptr, bool bSecret /*= true*/)
{
	return SyncCallProcesser<IUserClient>(uClientID, (bool(IUserClient::*)(StreamBinaryPtr, bool))&IUserClient::SyncSendClient, ptr, bSecret);
}

bool IUserClientManager::SyncSendClient(uint uClientID,const IMsgStream& msgStream, bool bSecret /*= true*/)
{
	return SyncCallProcesser<IUserClient>(uClientID, (bool(IUserClient::*)(const IMsgStream&, bool))&IUserClient::SyncSendClient, msgStream, bSecret);
}

bool IUserClientManager::ProcessRetry(uint64 uMillTime)
{
	ASSERT_LOG_DEBUG_ERR(_bInit);
	return ISyncProcesserManager::ProcessRetry(uMillTime);
}

size_t IUserClientManager::GetAssCount() const
{
	return GetSecondSize();
}

size_t IUserClientManager::GetQueueSize() const
{
	return ISyncProcesserManager::GetQueueSize();
}

size_t IUserClientManager::ClearOperateProcess()
{
	return ISyncProcesserManager::ClearQueueProcess();
}

bool IUserClientManager::SyncCalState(uint& uTotal, uint& uVaild, uint& uNormal, uint& uQueue, uint& uDelete, uint& uPerpairing, uint& uCache, uint& uOperateQueue, uint& uDelayOperateQueue) const
{
	return ISyncProcesserManager::SyncCalState(uTotal, uVaild, uNormal, uQueue, uDelete, uPerpairing, uCache, uOperateQueue, uDelayOperateQueue);
}

size_t IUserClientManager::GetClientCount() const
{
	return ISyncProcesserManager::GetProcesserSize();
}

time_t IUserClientManager::GetCheckTime() const
{
	return _uCheckTime;
}

time_t IUserClientManager::GetTimeOut() const
{
	return _uTimeOut;
}

bool IUserClientManager::OnTimeOut(const CTimeNodePtr& pTimeNode)
{
	if (_pTimerCheck == pTimeNode)
	{
		//检查心跳超时客户端
		time_t uTimeNow = ToolFrame::GetNowTime();

		SyncForEachCallProcesser<IUserClient>(&IUserClient::SyncCheck, uTimeNow);
		return true;
	}
	return false;
}

ISyncProcesserPtr IUserClientManager::OnCreateProcesser(int nUserInt, void* pUserData)
{
	return ISyncProcesserPtr(new IUserClient());
}

bool IUserClientManager::OnDestoryProcesser(ISyncProcesserPtr pProcesser)
{
	IUserClient* pClient = pProcesser->ToProcesser<IUserClient>();
	if (!pClient)return false;

	pClient->Close();
	return true;
}


NS_TOOL_FRAME_END
