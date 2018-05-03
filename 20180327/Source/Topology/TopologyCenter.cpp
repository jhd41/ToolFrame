#include "TopologyCenter.h"

#include "TopologyProtocol.h"

#include "ToolFrame.h"
#include "MProtocol.h"
#include "MSystem.h"

NS_TOOL_FRAME_BEGIN

CTopologyCenter::CTopologyCenter(void)
{
	_uTimeStart = 0;
	_uTimeTryCreateServer=5;
	_uTimeNotifyState=5;
	_hHandler = nullptr;
}

CTopologyCenter::~CTopologyCenter(void)
{
	RemoveTimerCreateServer();

	MSystem::Singleton().GetTimeOutQueque().RemoveTimer(_pTimerNotifyState);
	ToolFrame::SetPtrNull(_pTimerNotifyState);
}

bool CTopologyCenter::Init()
{
	if (!_vLogic.Init())return false;

	CreateTimerCreateServer();

	_uTimeStart = ToolFrame::GetNowTime();
	_pTimerNotifyState = MSystem::Singleton().GetTimeOutQueque().CreateTimerByAfterSec(this,0,true,_uTimeNotifyState);
	return true;
}

bool CTopologyCenter::OnRecv( UINT uClientID,IMsgStream& msgStream )
{
	//处理
	XClientData* pClientData = ToolFrame::GetPtrValueByKey(_vClientData,uClientID);
	ASSERT_LOG_ERROR(pClientData);
	if (!pClientData)return true;

	switch(pClientData->eClientType)
	{
	case CLIENT_TYPE_INVAILD:
		{
			//单独处理授权信息
			if (MSG_CENTER_AUTHORIZATION == msgStream.GetOpCode())
			{
				MsgCenterAuthorization msg(msgStream);
				if (!msg.Load())return false;

				if (msg.sPassword != _sPassword)
				{
					SendAuthorizationRep(uClientID,false);
					return true;
				}

				AddClient(uClientID,msg.eClientType);

				_hHandler->OnCenterAuthorization(msg.eClientType);

				SendAuthorizationRep(uClientID,true);
				return true;
			}
		}
		break;
	case CLIENT_TYPE_PHYSICAL:
		{
			switch(msgStream.GetOpCode())
			{
			case MSG_PHYSICAL_REGIST:
				{
					MsgPhysicalRegist msg(msgStream);
					if (!msg.Load())return false;

					if (INVALID_ID == msg.uPhysicalID)return false;
					if (_vPhysical.FindPhysicalByClientID(uClientID))return false;

					const XServerPhysical* pServer = _vPhysical.FindPhysicalByPhysicalID(msg.uPhysicalID);
					if (pServer && INVALID_ID != pServer->uClientID)return false;

					//注册物理服务器
					XServerPhysical xPhysical;
					xPhysical.uPhysicalID	= msg.uPhysicalID;
					xPhysical.sMac			= msg.sMac;
					xPhysical.sIP			= msg.sIP;
					xPhysical.vAddress		= msg.vAddress;
					xPhysical.xUpdate		= msg.xUpdate;
					xPhysical.uReconnect	= pServer ? pServer->uReconnect+1:0;
					xPhysical.uClientID		= uClientID;

					ASSERT_LOG_ERROR(_vPhysical.AddServer(xPhysical));

					//广播给控制端
					MsgCenterNtf msgNtf;
					msgNtf.uType = MsgCenterNtf::TYPE_ADD_PHYSICAL;
					msgNtf.vPhysical.push_back(xPhysical);

					Broadcast(CLIENT_TYPE_CONTROL,msgNtf);

					_hHandler->OnPhysicalRegist(msg.uPhysicalID);

					//回馈注册成功
					SendPhysicalRegistRep(uClientID,xPhysical.uPhysicalID,true);
					return true;
				}
				break;
			case MSG_PHYSICAL_UPDATE_REQ:
				{
					MsgPhysicalUpdateReq msg(msgStream);
					if (!msg.Load())return false;

					//验证
					if (INVALID_ID == msg.uPhysicalID)return false;

					const XServerPhysical* pServer = _vPhysical.FindPhysicalByClientID(uClientID);
					if (!pServer)return false;

					if (pServer->uPhysicalID != msg.uPhysicalID)return false;

					_vPhysical.UpdatePhysicalState(msg.uPhysicalID,msg.xUpdate);

					SendPhysicalUpdate(pServer->uPhysicalID);
					return true;
				}
				break;
			}
		}
		break;
	case CLIENT_TYPE_CONTROL:
		{
			switch(msgStream.GetOpCode())
			{
			case MSG_CONTROL_REGIST:
				{
					XServerControl xControl;
					xControl.uClientID = uClientID;
					_vController.AddControl(xControl);

					_hHandler->OnControlRegist();

					//返回所有的服务器列表
					SendAllServer(uClientID);
					return true;
				}
				break;
			case MSG_CONTROL_LOGIC_SAVE:
				{
					MsgControlSaveServer msg(msgStream);
					if (!msg.Load())return false;

					const XServerLogic*	pLogic = _vLogic.FindLogicByServerID(msg.uServerID);
					if (!pLogic)return false;
					if (INVALID_ID == pLogic->uClientID)return false;

					_hHandler->OnControlLogicSave(msg.uServerID);

					MsgCenterNtf msgNtf; 
					msgNtf.uType = MsgCenterNtf::TYPE_LOGIC_SAVE;
					Send(pLogic->uClientID,msgNtf);
					return true;
				}
				break;
			case MSG_CONTROL_LOGIC_CLEAN_UP:
				{
					MsgControlCleanUpServer msg(msgStream);
					if (!msg.Load())return false;

					const XServerLogic*	pLogic = _vLogic.FindLogicByServerID(msg.uServerID);
					if (!pLogic)return false;
					if (INVALID_ID == pLogic->uClientID)return false;

					_hHandler->OnControlLogicCleanUp(msg.uServerID);
					
					MsgCenterNtf msgNtf; 
					msgNtf.uType = MsgCenterNtf::TYPE_LOGIC_CLEAN_UP;
					Send(pLogic->uClientID,msgNtf);
					return true;
				}
				break;
			case MSG_CONTROL_LOGIC_STOP_SERVICE:
				{
					MsgControlStopService msg(msgStream);
					if (!msg.Load())return false;

					const XServerLogic*	pLogic = _vLogic.FindLogicByServerID(msg.uServerID);
					if (!pLogic)return false;
					if (INVALID_ID == pLogic->uClientID)return false;

					_hHandler->OnControlLogicStopService(msg.uServerID);

					MsgCenterNtf msgNtf; 
					msgNtf.uType = MsgCenterNtf::TYPE_LOGIC_STOP_SERVICE;
					Send(pLogic->uClientID,msgNtf);
					return true;
				}
				break;
			case MSG_CONTROL_LOGIC_SHUTDOWN:
				{
					MsgControlShutDown msg(msgStream);
					if (!msg.Load())return false;

					const XServerLogic*	pLogic = _vLogic.FindLogicByServerID(msg.uServerID);
					if (!pLogic)return false;
					if (INVALID_ID == pLogic->uClientID)return false;

					_hHandler->OnControlShutDown(msg.uServerID);

					MsgCenterNtf msgNtf; 
					msgNtf.uType = MsgCenterNtf::TYPE_LOGIC_SHUT_DOWN;
					Send(pLogic->uClientID,msgNtf);
					return true;
				}
				break;
			case MSG_CONTROL_LOGIC_DEBUG:
			{
				MsgControlDebugServer msg(msgStream);
				if (!msg.Load())return false;

				const XServerLogic*	pLogic = _vLogic.FindLogicByServerID(msg.uServerID);
				if (!pLogic)return false;
				if (INVALID_ID == pLogic->uClientID)return false;

				_hHandler->OnControlDebug(msg.uServerID,msg.vDebug);

				MsgCenterNtf msgNtf;
				msgNtf.uType = MsgCenterNtf::TYPE_LOGIC_DEBUG;
				msgNtf.vDebug = msg.vDebug;
				Send(pLogic->uClientID, msgNtf);
				return true;
			}
			break;
			case MSG_CONTROL_SET_SERVER:
				{
					MsgControlSetServer msg(msgStream);
					if (!msg.Load())return false;

					//设置服务器类型 以及 连接方式
					_vLogic.SetServerGroupID(msg.sServerGroupID);
					_vLogic.SetServerZoneID(msg.sServerZoneID);
					_vLogic.SetServerName(msg.sServerName);
					_vLogic.SetServerOpen(msg.xServerOpen);
					_vLogic.SetServerTag(msg.sServerTag);

					_vLogic.SetConfigLink(msg.vConfigLink);
					_vLogic.SetConfigLogic(msg.vConfigLogic);
					_vLogic.SetConfigServer(msg.vConfigServer);

					_hHandler->OnServerConfigChanged(uClientID);
					return true;
				}
				break;
			case MSG_CONTROL_PHYSICAL_START_SERVER:
				{
					MsgControlPhysicalStartServer msg(msgStream);
					if (!msg.Load())return false;

					const XConfigServer* pServer = _vLogic.FindConfigServer(msg.uServerID);
					if (!pServer)return false;

					const XConfigLogic* pLogic = _vLogic.FindConfigLogic(pServer->eSrvType);
					if (!pLogic)return false;

					const XServerPhysical* pPhysical = _vPhysical.FindPhysicalByPhysicalID(pServer->uPhysicalID);
					if (!pPhysical)return false;

					MsgCenterNtf msgReq; 
					msgReq.uType			= MsgCenterNtf::TYPE_PHYSICAL_START_SERVER;
					msgReq.uServerID		= pServer->uServerID;
					msgReq.eSrvType			= pLogic->eSrvType;
					msgReq.uThread			= pLogic->uThread;
					msgReq.uRunOnce			= pLogic->uRunOnce;
					msgReq.uPort			= pServer->uPort;
					msgReq.sExePath			= pLogic->sExePath;
					msgReq.sWorkingDir		= pLogic->sWorkingDir;
					msgReq.uRecvSize		= pLogic->uRecvSize;
					msgReq.uSendSize		= pLogic->uSendSize;
					msgReq.uBlockSize		= pLogic->uBlockSize;
					msgReq.uSaveTime		= pLogic->uSaveTime;
					msgReq.uPhysicalID		= pPhysical->uPhysicalID;
					msgReq.vPublicPort		= pServer->vPublicPort;
					msgReq.uPublicRecv		= pLogic->uPublicRecv;
					msgReq.uPublicSend		= pLogic->uPublicSend;
					msgReq.uPublicBlock		= pLogic->uPublicBlock;
					msgReq.uPublicConnect	= pServer->uPublicConnect;
					msgReq.uHash			= pServer->uHash;
					msgReq.uHashCount		= pLogic->uHashCount;
					msgReq.sServerTag		= _vLogic.GetServerTag();
					msgReq.sCommand			= pServer->sCommand;

					Send(pPhysical->uClientID,msgReq);

					_hHandler->OnControlStartServer(pServer->uServerID, pServer->eSrvType);
					return true;
				}
				break;
			case MSG_CONTROL_PHYSICAL_MEMORY_CLEAR:
				{
					MsgControlPhysicalMemoryClear msg(msgStream);
					if (!msg.Load())return false;

					const XServerPhysical* pPhysical = _vPhysical.FindPhysicalByPhysicalID(msg.uPhysicalID);
					if (!pPhysical)return false;

					if (INVALID_ID == pPhysical->uClientID)return false;

					_hHandler->OnControlPurgeMemory(pPhysical->uPhysicalID);

					MsgCenterNtf msgReq; 
					msgReq.uType		= MsgCenterNtf::TYPE_PHYSICAL_MEMORY_CLEAR;

					Send(pPhysical->uClientID,msgReq);
					return true;
				}
				break;
			case MSG_CONTROL_PHYSICAL_REBOOT:
				{
					MsgControlPhysicalReboot msg(msgStream);
					if (!msg.Load())return false;

					const XServerPhysical* pPhysical = _vPhysical.FindPhysicalByPhysicalID(msg.uPhysicalID);
					if (!pPhysical)return false;

					if (INVALID_ID == pPhysical->uClientID)return false;

					_hHandler->OnControlReboot(pPhysical->uPhysicalID);

					MsgCenterNtf msgReq; 
					msgReq.uType		= MsgCenterNtf::TYPE_PHYSICAL_REBOOT;

					Send(pPhysical->uClientID,msgReq);
					return true;
				}
				break;
			}
		}
		break;
	case CLIENT_TYPE_LOGIC:
		{
			switch(msgStream.GetOpCode())
			{
			case MSG_LOGIC_REGIST:
				{
					MsgLogicRegist msg(msgStream);
					if (!msg.Load())return false;

					//验证
					if (INVALID_ID == msg.uServerID)return false;
					const XConfigServer* pConfigServer = _vLogic.FindConfigServer(msg.uServerID);
					if(!pConfigServer)return false;
					if(pConfigServer->eSrvType != msg.eSrvType )return false;
					if (_vLogic.FindLogicByClientID(uClientID))return false;
					const XServerLogic* pServer = _vLogic.FindLogicByServerID(msg.uServerID);
					if (pServer && INVALID_ID != pServer->uClientID)return false;

					//构造结构
					XServerLogic xServer;

					xServer.uServerID		= msg.uServerID;
					xServer.eSrvType		= msg.eSrvType;
					xServer.uProcessID		= msg.uProcessID;
					xServer.xUpdate			= msg.xUpdate;

					xServer.uTimeStartUp	= (uint32)ToolFrame::GetNowTime();
					xServer.uReconnect		= pServer ? pServer->uReconnect+1:0;
					xServer.uClientID		= uClientID;

					//广播
					MsgCenterNtf msgNtf; 
					msgNtf.uType = MsgCenterNtf::TYPE_ADD_LOGIC;
					msgNtf.vLogic.push_back(xServer);

					StreamBinaryPtr pBuffer = msgNtf.GetSendStream();
					ASSERT_LOG_ERROR(pBuffer);
					Broadcast(CLIENT_TYPE_LOGIC, pBuffer);
					Broadcast(CLIENT_TYPE_CONTROL, pBuffer);

					//添加至逻辑服务器列表
					ASSERT_LOG_ERROR(_vLogic.AddServer(xServer));

					//广播所有服务器列表
					SendAllServer(uClientID);

					//回馈注册成功
					SendLogicRegistRep(uClientID,xServer.uServerID,true);

					XServerArg xArg;
					xArg.uServerID	= xServer.uServerID;
					xArg.eSrvType	= xServer.eSrvType;
					xArg.uClientID	= uClientID;

					_hHandler->OnServerConnected(xArg);
					return true;
				}
				break;
			case MSG_LOGIC_UPDATE_REQ:
				{
					MsgLogicUpdateReq msg(msgStream);
					if (!msg.Load())return false;

					//验证
					if (INVALID_ID == msg.uServerID)return false;

					XServerArg xArg;
					xArg.uServerID = msg.uServerID;
					xArg.uClientID = uClientID;

					if(!_vLogic.UpdateLogicState(msg.uServerID,msg.xUpdate))
						return false;

					_hHandler->OnServerStateChanged(xArg);
					return true;
				}
				break;
			case MSG_LOGIC_DEBUG:
				{
					MsgLogicDebug msg(msgStream);
					if (!msg.Load())return false;

					//验证
					if (INVALID_ID == msg.uServerID)return false;
					
					Broadcast(CLIENT_TYPE_CONTROL, msg);
					return true;
				}
				break;
			}
		}
		break;
	}

	return false;
}

bool CTopologyCenter::OnConnected( UINT uClientID )
{
	AddClient(uClientID,CLIENT_TYPE_INVAILD);
	return true;
}

bool CTopologyCenter::OnDisconnected( UINT uClientID )
{
	XClientData* pClientData = ToolFrame::GetPtrValueByKey(_vClientData,uClientID);
	ASSERT_LOG_ERROR(pClientData);
	if (!pClientData)return true;

	switch(pClientData->eClientType)
	{
	case CLIENT_TYPE_PHYSICAL:
		{
			const XServerPhysical* pPhysical = _vPhysical.FindPhysicalByClientID(uClientID);
			if (pPhysical)
			{
				_vPhysical.RemovePhysicalByPhysicalID(pPhysical->uPhysicalID);

				//同步逻辑状态
				SendPhysicalUpdate(pPhysical->uPhysicalID);

				//广播数据包
				{
					MsgCenterNtf msg;
					msg.uType = MsgCenterNtf::TYPE_REMOVE_PHYSICAL;
					msg.uID = pPhysical->uPhysicalID;

					StreamBinaryPtr pBuffer = msg.GetSendStream();
					ASSERT_LOG_ERROR(pBuffer);

					Broadcast(CLIENT_TYPE_LOGIC,	pBuffer);
					Broadcast(CLIENT_TYPE_CONTROL,	pBuffer);
				}
			}
		}
		break; 
	case CLIENT_TYPE_LOGIC:
		{
			const XServerLogic* pLogic = _vLogic.FindLogicByClientID(uClientID);
			if (!pLogic)return false;

			XServerArg xArg;
			xArg.uServerID = pLogic->uServerID;
			xArg.eSrvType = pLogic->eSrvType;
			xArg.uClientID = uClientID;

			_hHandler->OnServerDisconnected(xArg);

			//保存最近一次状态
			int eStateLast = pLogic->xUpdate.eState;

			//移除
			_vLogic.RemoveLogicByServerID(pLogic->uServerID);

			//同步逻辑状态
			SendLogicUpdate(pLogic->uServerID);

			//广播数据包
			{
				MsgCenterNtf msg;
				msg.uType	= MsgCenterNtf::TYPE_REMOVE_LOGIC;
				msg.uID		= pLogic->uServerID;

				StreamBinaryPtr pBuffer = msg.GetSendStream();
				ASSERT_LOG_ERROR(pBuffer);

				Broadcast(CLIENT_TYPE_LOGIC,	pBuffer);
				Broadcast(CLIENT_TYPE_CONTROL,	pBuffer);
			}

			//重启
			if (CONNECT_STATE_STOP_SERVICE != eStateLast)
			{
				const XConfigServer* pConfigServer	= _vLogic.FindConfigServer(pLogic->uServerID);
				const XConfigLogic* pConfigLogic	= _vLogic.FindConfigLogic(pLogic->eSrvType);
				const XServerPhysical* pPhysical	= _vPhysical.FindPhysicalByPhysicalID(pConfigServer->uPhysicalID);
				
				if (pConfigServer && pConfigLogic && pPhysical)
				{
					MsgCenterNtf			msgReq;
					msgReq.uType			= MsgCenterNtf::TYPE_PHYSICAL_START_SERVER;
					msgReq.uServerID		= pLogic->uServerID;
					msgReq.eSrvType			= pLogic->eSrvType;
					msgReq.uThread			= pConfigLogic->uThread;
					msgReq.uRunOnce			= pConfigLogic->uRunOnce;
					msgReq.uPort			= pConfigServer->uPort;
					msgReq.sExePath			= pConfigLogic->sExePath;
					msgReq.sWorkingDir		= pConfigLogic->sWorkingDir;
					msgReq.uRecvSize		= pConfigLogic->uRecvSize;
					msgReq.uSendSize		= pConfigLogic->uSendSize;
					msgReq.uBlockSize		= pConfigLogic->uBlockSize;
					msgReq.uSaveTime		= pConfigLogic->uSaveTime;
					msgReq.uPhysicalID		= pConfigServer->uPhysicalID;
					msgReq.vPublicPort		= pConfigServer->vPublicPort;
					msgReq.uPublicRecv		= pConfigLogic->uPublicRecv;
					msgReq.uPublicSend		= pConfigLogic->uPublicSend;
					msgReq.uPublicBlock		= pConfigLogic->uPublicBlock;
					msgReq.uPublicConnect	= pConfigServer->uPublicConnect;

					msgReq.uHash			= pConfigServer->uHash;
					msgReq.uHashCount		= pConfigLogic->uHashCount;

					msgReq.sServerTag		= _vLogic.GetServerTag();

					msgReq.sCommand			= pConfigServer->sCommand;

					Send(pPhysical->uClientID,msgReq);

					_hHandler->OnCenterStartServer(pLogic->uServerID, pLogic->eSrvType);
				}
			}
		}
		break;
	case CLIENT_TYPE_CONTROL:
		_vController.RemoveControlByClientID(uClientID);
		break;
	}

	RemoveClient(uClientID);
	return true;
}

bool CTopologyCenter::OnConnectFailed( UINT uClientID )
{
	return true;
}

bool CTopologyCenter::SetPassword( const std::string& sPassword )
{
	_sPassword = sPassword;
	return true;
}

bool CTopologyCenter::SetPort( uint uPort )
{
	_uPort = uPort;
	return true;
}

bool CTopologyCenter::SendAuthorizationRep( uint uClientID,bool bAuthorized ) const
{
	MsgCenterAuthorizationRep msg;
	msg.bAuthorized = bAuthorized;
	msg.uTimeStart	= (uint32)_uTimeStart;
	return Send(uClientID,msg);
}

bool CTopologyCenter::SendAllServer( uint uClientID )
{
	MsgCenterNtf msgNtf;
	msgNtf.uType		= MsgCenterNtf::TYPE_ALL_SERVER;

	{
		MapLogic::const_iterator itr;
		foreach(itr,_vLogic.GetLogic()){
			const XServerLogic& xLogic = itr->second;

			ToolFrame::Insert(msgNtf.vLogic,xLogic);
		}
	}
	{
		MapPhysical::const_iterator itr;
		foreach(itr,_vPhysical.GetPhysical()){
			const XServerPhysical& xPhysical = itr->second;

			ToolFrame::Insert(msgNtf.vPhysical,xPhysical);
		}
	}

	msgNtf.vConfigLink		= _vLogic.GetConfigLinks();
	msgNtf.vConfigLogic		= _vLogic.GetConfigLogic();
	msgNtf.vConfigServer	= _vLogic.GetConfigServer();

	msgNtf.sServerGroupID	= _vLogic.GetServerGroupID();
	msgNtf.sServerZoneID	= _vLogic.GetServerZoneID();
	msgNtf.sServerName		= _vLogic.GetServerName();
	msgNtf.xServerOpen		= _vLogic.GetServerOpen();

	return Send(uClientID,msgNtf);
}

bool CTopologyCenter::SetSendSize( uint uSize )
{
	return _vLogic.SetSendSize(uSize);
}

bool CTopologyCenter::SetRecvSize( uint uSize )
{
	return _vLogic.SetRecvSize(uSize);
}

bool CTopologyCenter::SetBlockSize(uint uSize)
{
	return _vLogic.SetBlockSize(uSize);
}

bool CTopologyCenter::Send( uint uClientID,IMsgStream& msgBase ) const
{
	return Send(uClientID,msgBase.GetSendStream());
}

bool CTopologyCenter::Send( uint uClientID, StreamBinaryPtr ptrBuffer ) const
{
	return MProtocol::Singleton().Send(uClientID,ptrBuffer);
}

bool CTopologyCenter::AddClient( uint uClientID,uint eClientType )
{
	XClientData* pClientData = ToolFrame::GetPtrValueByKey(_vClientData,uClientID,true);
	ASSERT_LOG_ERROR(pClientData);
	pClientData->uClientID	= uClientID;
	pClientData->eClientType= eClientType;
	return true;
}

bool CTopologyCenter::Broadcast(EClientType eClientType, IMsgStream& msgStream)
{
	StreamBinaryPtr ptrBuffer = msgStream.GetSendStream();
	ASSERT_LOG_ERROR(ptrBuffer);
	return Broadcast(eClientType, ptrBuffer);
}

bool CTopologyCenter::Broadcast(EClientType eClientType, StreamBinaryPtr pBuffer)
{
	if (!pBuffer)return false;
	if (pBuffer->IsEmpty())return false;

	switch (eClientType)
	{
		case CLIENT_TYPE_LOGIC:
			{
				MapLogic::const_iterator itr;
				foreach(itr, _vLogic.GetLogic()) {
					const XServerLogic& xLogic = itr->second;
					if (INVALID_ID != xLogic.uClientID)
						Send(xLogic.uClientID, pBuffer);
				}
			}
			break;
		case CLIENT_TYPE_CONTROL:
			{
				MapControl::const_iterator itr;
				foreach(itr, _vController.GetControls()) {
					const XServerControl& xControl = itr->second;
					if (INVALID_ID != xControl.uClientID)
						Send(xControl.uClientID, pBuffer);
				}
			}
			break;
	}

	return true;
}

bool CTopologyCenter::RemoveClient( uint uClientID )
{
	return ToolFrame::DeleteByKey(_vClientData,uClientID);
}

bool CTopologyCenter::SetHandler( HTopologyCenter* hHandler )
{
	_hHandler = hHandler;
	return true;
}

bool CTopologyCenter::SendLogicUpdate( uint uServerID )
{
	const XServerLogic* pServer = _vLogic.FindLogicByServerID(uServerID);
	if (!pServer)return false;

	MsgLogicUpdateNtf msg;
	ASSERT_LOG_ERROR(ToolFrame::Insert(msg.vUpdate,pServer->uServerID,pServer->xUpdate));

	StreamBinaryPtr pBuffer = msg.GetSendStream();
	ASSERT_LOG_ERROR(pBuffer);

	Broadcast(CLIENT_TYPE_LOGIC,	pBuffer);
	Broadcast(CLIENT_TYPE_CONTROL,	pBuffer);

	return true;
}

bool CTopologyCenter::SendLogicUpdateAll()
{
	MsgLogicUpdateNtf msg;

	MapLogic::iterator itr;
	foreach(itr,_vLogic.GetLogic()){
		XServerLogic& xLogic = itr->second;
		if(xLogic.bUpdated){

			ASSERT_LOG_ERROR(ToolFrame::Insert(msg.vUpdate,xLogic.uServerID,xLogic.xUpdate));

			xLogic.bUpdated  = false;
		}
	}
	if(msg.vUpdate.empty())return false;

	StreamBinaryPtr pBuffer =  msg.GetSendStream();
	ASSERT_LOG_ERROR(pBuffer);

	Broadcast(CLIENT_TYPE_LOGIC,	pBuffer);
	Broadcast(CLIENT_TYPE_CONTROL,	pBuffer);

	return true;
}

bool CTopologyCenter::SendLogicRegistRep( uint uClientID,uint uServerID,bool bSucceed )
{
	MsgLogicRegistRep msg;
	msg.uServerID	= uServerID;
	msg.bSucceed	= bSucceed;

	return Send(uClientID,msg);
}

bool CTopologyCenter::SendPhysicalRegistRep( uint uClientID,uint uPhysicalID,bool bSucceed )
{
	MsgPhysicalRegistRep msg;
	msg.uPhysicalID	= uPhysicalID;
	msg.bSucceed	= bSucceed;

	return Send(uClientID,msg);
}

bool CTopologyCenter::SendPhysicalUpdate( uint uPhysicalID )
{
	const XServerPhysical* pServer = _vPhysical.FindPhysicalByPhysicalID(uPhysicalID);
	if (!pServer)return false;

	MsgPhysicalUpdateNtf msg;
	ASSERT_LOG_ERROR(ToolFrame::Insert(msg.vUpdate,pServer->uPhysicalID,pServer->xUpdate));

	Broadcast(CLIENT_TYPE_CONTROL, msg);
	return true;
}

const std::string& CTopologyCenter::GetServerGroupID() const
{
	return _vLogic.GetServerGroupID();
}

const std::string& CTopologyCenter::GetServerZoneID() const
{
	return _vLogic.GetServerZoneID();
}

bool CTopologyCenter::CreateTimerCreateServer()
{
	ASSERT_LOG_ERROR(!_pTimerCreateServer);
	_pTimerCreateServer = MSystem::Singleton().GetTimeOutQueque().CreateTimerByAfterSec(this,0,true,_uTimeTryCreateServer);
	return true;
}

bool CTopologyCenter::RemoveTimerCreateServer()
{
	MSystem::Singleton().GetTimeOutQueque().RemoveTimer(_pTimerCreateServer);
	ToolFrame::SetPtrNull(_pTimerCreateServer);
	return true;
}

bool CTopologyCenter::OnTimeOut( const CTimeNodePtr& pTimeNode )
{
	if (_pTimerCreateServer == pTimeNode)
	{
		if (!MProtocol::Singleton().CreateServer(this,_uPort, LINK_TYPE_NET_TCP,_vLogic.GetRecvSize(),_vLogic.GetSendSize(),_vLogic.GetBlockSize())){
			_hHandler->OnServerCreateFaild(_uPort);
			return true;
		}

		RemoveTimerCreateServer();
		_hHandler->OnServerCreateSucceed(_uPort);
		return true;
	}
	if (_pTimerNotifyState == pTimeNode)
	{
		SendLogicUpdateAll();
		_hHandler->OnServerNotifyState();
		return true;
	}
	return false;
}

bool CTopologyCenter::SetTimeTryCreateServer( uint uTime )
{
	_uTimeTryCreateServer = uTime;
	return true;
}

bool CTopologyCenter::SetTimeNotifyState( uint uTime )
{
	_uTimeNotifyState = uTime;
	return true;
}

NS_TOOL_FRAME_END
