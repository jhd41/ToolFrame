#include "TopologyLogicLinker.h"
#include "ToolFrame.h"
#include "MProtocol.h"
#include "TopologyProtocol.h"

NS_TOOL_FRAME_BEGIN

CTopologyLogicLinker::CTopologyLogicLinker(void)
{
	_pLogic  = nullptr;
	_pPhysical = nullptr;
	_hHandler	= nullptr;
}

CTopologyLogicLinker::~CTopologyLogicLinker(void)
{
	CloseServer();
	ToolFrame::Delete(_vConnectData);
}

bool CTopologyLogicLinker::Update()
{
	CLockWrite lock(_xMutexConnector);

	CLockRead lockLinkType(_pLogic->GetMutexConfig());
	CLockRead lockLogic(_pLogic->GetMutexLogic());
	CLockRead lockPhysical(_pPhysical->GetMutexPhysical());

	const MapTypeLogic& vLogic = _pLogic->GetTypeLogic();
	MapTypeLogic::const_iterator itr;
	foreach(itr,vLogic){
		uint uSrvTypeCur = itr->first;
		const XConfigLink* pLink = _pLogic->FindConfigLink(_pLogic->GetServerType(),uSrvTypeCur);
		if (pLink){
			const VectorLogicPtr& vServer = itr->second;
			if (!vServer.empty())
			{
				VectorLogicPtr::const_iterator itrServer;
				foreach(itrServer,vServer){
					const XServerLogic* pServer = *itrServer;
					ASSERT_LOG_ERROR(pServer);

					if (CONNECT_STATE_NORMAL == pServer->xUpdate.eState || pServer->eSrvType == _pLogic->GetServerType())//自己连接自己时
					{
						const XConfigServer* pConfigServer = _pLogic->FindConfigServer(pServer->uServerID);
						if(pConfigServer){
							const XServerPhysical* pPhysical = _pPhysical->FindPhysicalByPhysicalID(pConfigServer->uPhysicalID);
							if (pPhysical)
							{
								VectorConnector& vMonitor =	ToolFrame::GetValueByKeyForce(_vConnector,pServer->uServerID);
								if (vMonitor.empty())
								{
									VectorString vServerIPPort;

									VectorString128::const_iterator itrAddress;
									foreach(itrAddress,pPhysical->vAddress){
										vServerIPPort.push_back(MAKE_STRING(*itrAddress<<":"<<pConfigServer->uPort));
									}

									for (uint nIndex = 0; nIndex < pLink->uCount; ++nIndex)
									{
										CConnectMonitor& monitor = ToolFrame::CreateValue(vMonitor);
										monitor.SetID(pServer->uServerID);
										monitor.SetUserInt(pServer->eSrvType);
										monitor.SetServerAddress(vServerIPPort);
										monitor.SetHandler(this);
										monitor.SetSendSize(_pLogic->GetSendSize());
										monitor.SetRecvSize(_pLogic->GetRecvSize());
										ASSERT_LOG_ERROR(monitor.Start());
									}
								}
							}
						}
					}
				}
			}

		}
	}

	return true;
}

bool CTopologyLogicLinker::CloseServer()
{
	MProtocol::Singleton().CloseServer(_pLogic->GetPort(),LINK_TYPE_NET_TCP);
	return true;
}

bool CTopologyLogicLinker::CreateServer()
{
	if (INVALID_ID == _pLogic->GetPort())return true;
	return MProtocol::Singleton().CreateServer(this,_pLogic->GetPort(),LINK_TYPE_NET_TCP,_pLogic->GetRecvSize(),_pLogic->GetSendSize(), _pLogic->GetBlockSize());
}

bool CTopologyLogicLinker::OnConnected( CConnectMonitor* pConnectMonitor )
{
	//添加客户端数据
	if (!ConnectDataAdd(pConnectMonitor->GetClientID(),pConnectMonitor->GetID(),pConnectMonitor->GetUserInt()))
	{
		LOG_NET_ERR("添加已连接列表失败:"<<pConnectMonitor->GetID());
		MProtocol::Singleton().Disconnect(pConnectMonitor->GetClientID());
		return true;
	}

	//发送连接请求
	{
		MsgLinkConnectReq msg;
		msg.uServerID	= _pLogic->GetServerID();
		msg.eSrvType	= _pLogic->GetServerType();
		pConnectMonitor->Send(msg);
	}
	return true;
}

bool CTopologyLogicLinker::OnDisconnected( CConnectMonitor* pConnectMonitor )
{
	XServerArg xArg;

	xArg.uClientID = pConnectMonitor->GetClientID();

	//移除客户端数据
	if (ConnectDataRemove(&xArg.uServerID,&xArg.eSrvType,pConnectMonitor->GetClientID()))
		_hHandler->OnServerDisconnected(xArg);

	return true;
}

bool CTopologyLogicLinker::OnRecved( CConnectMonitor* pConnectMonitor,IMsgStream& msgStream)
{
	switch (msgStream.GetOpCode())
	{
	case MSG_LINK_CONNECT_REP:
		{
			MsgLinkConnectRep msg(msgStream);
			if (!msg.Load())return false;

			ASSERT_LOG_ERROR(pConnectMonitor->GetID() == msg.uServerID);

			XServerArg xArg;
			xArg.uServerID	= pConnectMonitor->GetID();
			xArg.eSrvType	= pConnectMonitor->GetUserInt();
			xArg.uClientID	= pConnectMonitor->GetClientID();
			_hHandler->OnServerConnected(xArg);

			CheckIsAllServerConnectd();
			return true;
		}
		break;
	case MSG_LINK_TRAN:
		{
			MsgLinkTran msg(msgStream);
			if (!msg.Load())return false;

			IMsgStream msgTran(msg.ptr);
			if (!msgTran.LoadBegin())
			{
				//传包有误
				LOG_NET_ERR("ClientID:" << pConnectMonitor->GetClientID()<<" UserID:"<< msg.uUserID);
				return true;
			}

			XServerArg xServerArg;
			if (!ConnectDataRecv(&xServerArg.uServerID,&xServerArg.eSrvType,pConnectMonitor->GetClientID()))
			{
				LOG_ERROR_MSG("ClientID:" << pConnectMonitor->GetClientID() << " UserID:" << msg.uUserID);
				return false;
			}
			xServerArg.uClientID= pConnectMonitor->GetClientID();
			xServerArg.xSrcID	= msg.xSrcID;
			xServerArg.uUserID	= msg.uUserID;

			CTimeElapse xTimeElapse;
			if (!_hHandler->OnServerRecved(xServerArg,msgTran))
				_hHandler->OnServerRecvErr(xServerArg,msgTran);

			_xProcessAvg.AddCount(xTimeElapse.TimeElapsed());
			return true;
		}
		break;
	}

	return false;
}

bool CTopologyLogicLinker::OnConnected( UINT uClientID )
{
	return true;
}

bool CTopologyLogicLinker::OnConnectFailed( UINT uClientID )
{
	return true;
}

bool CTopologyLogicLinker::OnDisconnected( UINT uClientID )
{
	XServerArg xArg;

	xArg.uClientID = uClientID;

	//移除客户端数据
	if (ConnectDataRemove(&xArg.uServerID,&xArg.eSrvType,uClientID))
		_hHandler->OnServerDisconnected(xArg);
	return true;
}

bool CTopologyLogicLinker::OnRecv( uint uClientID,IMsgStream& msgStream)
{
	switch (msgStream.GetOpCode())
	{
	case MSG_LINK_CONNECT_REQ:
		{
			MsgLinkConnectReq msg(msgStream);
			if (!msg.Load())return false;
			if (!ConnectDataAdd(uClientID,msg.uServerID,msg.eSrvType))
			{
				LOG_NET_ERR("添加已连接列表失败:"<<msg.uServerID);
				MProtocol::Singleton().Disconnect(uClientID);
				return true;
			}

			//应答连接请求
			{
				MsgLinkConnectRep msgRep;
				msgRep.uServerID = _pLogic->GetServerID();
				MProtocol::Singleton().Send(uClientID,msgRep);
			}

			XServerArg xArg;
			xArg.uServerID	= msg.uServerID;
			xArg.eSrvType	= msg.eSrvType;
			xArg.uClientID	= uClientID;
			_hHandler->OnServerConnected(xArg);

			CheckIsAllServerConnectd();
			return true;
		}
		break;
	case MSG_LINK_TRAN:
		{
			MsgLinkTran msg(msgStream);
			if (!msg.Load())return false;

			IMsgStream msgTran(msg.ptr);
			if (!msgTran.LoadBegin())
			{
				//传包有误
				LOG_ERROR();
				return true;
			}

			XServerArg xServerArg;
			if (!ConnectDataRecv(&xServerArg.uServerID,&xServerArg.eSrvType,uClientID))
			{
				LOG_ERROR();
				return false;
			}
			xServerArg.uClientID= uClientID;
			xServerArg.xSrcID	= msg.xSrcID;
			xServerArg.uUserID= msg.uUserID;

			CTimeElapse xTimeElapse;
			if (!_hHandler->OnServerRecved(xServerArg,msgTran))
				_hHandler->OnServerRecvErr(xServerArg,msgTran);

			_xProcessAvg.AddCount(xTimeElapse.TimeElapsed());
			return true;
		}
		break;
	}

	return false;
}

bool CTopologyLogicLinker::Init()
{
	if (!_pLogic)return false;
	return true;
}


bool CTopologyLogicLinker::SetManager( CTopologyServerLogic* pManager )
{
	_pLogic = pManager;
	return true;
}

bool CTopologyLogicLinker::SetManager( CTopologyServerPhysical* pManager )
{
	_pPhysical = pManager;
	return true;
}

bool CTopologyLogicLinker::RemoveServer( uint uServerID )
{
	CLockWrite lock(_xMutexConnector);
	
	ToolFrame::EraseByKey(_vConnector,uServerID);
	return true;
}

uint CTopologyLogicLinker::SendClientID( uint uClientID, StreamBinaryPtr ptr,const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/,uint uUserID /*= INVALID_ID*/ ) const
{
	MsgLinkTran msg;
	msg.xSrcID		= xSrcID;	//大小 10
	msg.ptr			= ptr;
	msg.uUserID		= uUserID;	//大小 4

	if (!MProtocol::Singleton().Send(uClientID,msg))return INVALID_ID;

	return uClientID;
}

bool CTopologyLogicLinker::ConnectDataAdd( uint uClientID,uint uServerID,uint eSrvType)
{
	CLockWrite lock(_xMutexConnectData);

	XTopologySession* pData = ToolFrame::GetPtrValueByKey(_vConnectData,uClientID,true);
	ASSERT_LOG_ERROR(pData);

	//如果之前的 连接还没断开 则 取消
	if (INVALID_ID != pData->uClientID)
		return false;

	pData->uServerID	= uServerID;
	pData->uClientID	= uClientID;

	pData->eSrvType		= eSrvType;

	return ToolFrame::InsertVector(_vServerData,uServerID,pData->uClientID);
}

bool CTopologyLogicLinker::ConnectDataRemove(  uint* uServerID,uint* eSrvType,uint uClientID )
{
	CLockWrite lock(_xMutexConnectData);

	XTopologySession* pData = ToolFrame::GetPtrValueByKey(_vConnectData,uClientID);
	if (!pData)return false;

	*uServerID	= pData->uServerID;
	*eSrvType	= pData->eSrvType;

	//移除_vServerData
	ToolFrame::EraseByValue(_vServerData,pData->uServerID,uClientID);
	ToolFrame::DeleteByKey(_vConnectData,uClientID);
	return true;
}

bool CTopologyLogicLinker::ConnectDataRecv(uint* uServerID, uint* eSrvType, uint uClientID)
{
	CLockRead lock(_xMutexConnectData);

	XTopologySession* pData = ToolFrame::GetPtrValueByKey(_vConnectData, uClientID);
	if (!pData)return false;

	*uServerID = pData->uServerID;
	*eSrvType = pData->eSrvType;

	return true;
}

uint CTopologyLogicLinker::ConnectDataFindServerID(uint uClientID) const
{
	CLockRead lock(_xMutexConnectData);

	const XTopologySession* pData = ToolFrame::GetPtrValueByKey(_vConnectData,uClientID);
	if (!pData)return INVALID_ID;
	
	CLockRead lockData(pData->mutex);
	return pData->uServerID;
}

uint CTopologyLogicLinker::ConnectDataFindRandClientID( uint uServerID ) const
{
	CLockRead lock(_xMutexConnectData);

	const VectorUint& vClientID = ToolFrame::GetPtrValueByKey(_vServerData,uServerID);
	if(vClientID.empty())return INVALID_ID;

	return ToolFrame::RandValue(vClientID);
}

bool CTopologyLogicLinker::ConnectDataGetServerID(SetUint& vSrvID,int eServerType ) const
{
	CLockRead lock(_xMutexConnectData);

	MapConnectData::const_iterator itr;
	foreach(itr,_vConnectData){
		XTopologySession* pData = itr->second;
		ASSERT_LOG_ERROR(pData);

		CLockRead lockData(pData->mutex);

		if (pData->eSrvType == eServerType){
			vSrvID.insert(pData->uServerID);
		}
	}
	return true;
}

uint64 CTopologyLogicLinker::ConnectDataGetMinFreeTime() 
{
	CLockRead lock(_xMutexConnectData);

	uint64 uFreeTimeMin = _xTimeElapse.ReStart();

	MapConnectData::const_iterator itr;
	foreach(itr,_vConnectData){
		const XTopologySession* pData = itr->second;
		ASSERT_LOG_ERROR(pData);

		CLockRead lockData(pData->mutex);

		int64 uFreeTime = MProtocol::Singleton().ClearFreeTime(pData->uClientID);
		if (uFreeTime >=0 && (uint64)uFreeTime < uFreeTimeMin){
			uFreeTimeMin = uFreeTime;
		}	
	}

	return uFreeTimeMin;
}

bool CTopologyLogicLinker::SetHandler( HTopologyLogic* hHandler )
{
	_hHandler = hHandler;
	return true;
}

bool CTopologyLogicLinker::ConnectDataIsConnectedAllSrvType() const
{
	SetInt vSrvType;

	//整理出连接到的服务器
	CLockRead lockConnect(_xMutexConnectData);
	MapConnectData::const_iterator itrConnect;
	foreach(itrConnect,_vConnectData){
		XTopologySession* pData = itrConnect->second;
		ASSERT_LOG_ERROR(pData);

		CLockRead lockData(pData->mutex);

		vSrvType.insert(pData->eSrvType);
	}

	CLockRead lockConfig(_pLogic->GetMutexConfig());

	MapConfigLink::const_iterator itr;
	foreach(itr,_pLogic->GetConfigLinks()){
		const XConfigLink& xLink = *itr;

		//只判断 正向 方向 链接 方式 只有这样 组网 才有可能从内到外 依次完成
		if (xLink.eSrcSrv == _pLogic->GetServerType())
		{
			if (!ToolFrame::IsHasKey(vSrvType,xLink.eDesSrv))
				return false;
		}
	}
	return true;
}

bool CTopologyLogicLinker::CheckIsAllServerConnectd() 
{
	if(_vMark.IsMarked())return true;

	if (ConnectDataIsConnectedAllSrvType() && _vMark.TryMark())
		_hHandler->OnServerAllConnected();
	return true;
}

CAvgCounter& CTopologyLogicLinker::GetProcessAvg()
{
	return _xProcessAvg;
}

NS_TOOL_FRAME_END
	