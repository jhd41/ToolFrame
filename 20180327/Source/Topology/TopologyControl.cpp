#include "TopologyControl.h"

#include "TopologyProtocol.h"

#include "MProtocol.h"

NS_TOOL_FRAME_BEGIN

CTopologyControl::CTopologyControl(void)
{
	_monitor.SetHandler(this);

	_hHandler = nullptr;

	_bAuthorized = false;
}

CTopologyControl::~CTopologyControl(void)
{
}

bool CTopologyControl::SetCenterIP( const std::string& sCenterIP )
{
	return _monitor.SetServerAddress(sCenterIP);
}

bool CTopologyControl::SetPassword( const std::string& sPassword )
{
	_sPassword = sPassword;
	return true;
}

bool CTopologyControl::Init()
{
	if (!_vLogic.Init())return false;
	if (!_hHandler)return false;
	return _monitor.Start();
}

bool CTopologyControl::OnConnected( CConnectMonitor* pConnectMonitor )
{
	SendAuthorization(pConnectMonitor->GetClientID());
	return true;
}

bool CTopologyControl::OnDisconnected( CConnectMonitor* pConnectMonitor )
{
	_bAuthorized = false;
	return true;
}

bool CTopologyControl::OnRecved( CConnectMonitor* pConnectMonitor,IMsgStream& msgStream )
{
	switch(msgStream.GetOpCode())
	{
	case MSG_CENTER_AUTHORIZATION_REP:
		{
			MsgCenterAuthorizationRep msg(msgStream);
			if (!msg.Load())return false;

			_bAuthorized = !!msg.bAuthorized;

			//如果授权通过
			if (msg.bAuthorized)
				SendControlRegist(pConnectMonitor->GetClientID());

			//回调
			_hHandler->OnAuthorizationRep(!!msg.bAuthorized,msg.uTimeStart);
			return true;
		}
		break;
	case MSG_CENTER_NTF:
		{
			MsgCenterNtf msg(msgStream);
			if (!msg.Load())return false;

			switch(msg.uType)
			{
			case MsgCenterNtf::TYPE_ALL_SERVER:
				{
					//修改配置
					{
						CLockWrite lockLinkType(_vLogic.GetMutexConfig());
						CLockWrite lockLogic(_vLogic.GetMutexLogic());
						CLockWrite lockPhysical(_vPhysical.GetMutexPhysical());

						_vLogic.Clear();
						_vPhysical.Clear();

						_vLogic.SetConfigLink(msg.vConfigLink);
						_vLogic.SetConfigLogic(msg.vConfigLogic);
						_vLogic.SetConfigServer(msg.vConfigServer);
						_vLogic.SetServerGroupID(msg.sServerGroupID);
						_vLogic.SetServerZoneID(msg.sServerZoneID);
						_vLogic.SetServerName(msg.sServerName);
						_vLogic.SetServerOpen(msg.xServerOpen);

						ASSERT_LOG_ERROR(_vLogic.OptimizeSrvTypeInit());

						ASSERT_LOG_ERROR(_vLogic.AddServer(msg.vLogic));
						ASSERT_LOG_ERROR(_vPhysical.AddServer(msg.vPhysical));
					}
					
					//回调
					_hHandler->OnAllServer(msg.vPhysical,msg.vLogic);
					return true;
				}
				break;
			case MsgCenterNtf::TYPE_ADD_PHYSICAL:
				{
					{
						CLockWrite lockPhysical(_vPhysical.GetMutexPhysical());
						ASSERT_LOG_ERROR(_vPhysical.AddServer(msg.vPhysical));
					}

					//回调
					_hHandler->OnAddPhysical(msg.vPhysical);
					return true;
				}
				break;
			case MsgCenterNtf::TYPE_ADD_LOGIC:
				{
					{
						CLockRead lockLinkType(_vLogic.GetMutexConfig());
						CLockWrite lockLogic(_vLogic.GetMutexLogic());
						ASSERT_LOG_ERROR(_vLogic.AddServer(msg.vLogic));
						ASSERT_LOG_ERROR(_vLogic.OptimizeSrvType());
					}

					//回调
					_hHandler->OnAddLogic(msg.vLogic);
					return true;
				}
				break;
			case MsgCenterNtf::TYPE_REMOVE_PHYSICAL:
				{
					{
						CLockWrite lockPhysical(_vPhysical.GetMutexPhysical());
						_vPhysical.RemovePhysicalByPhysicalID(msg.uID);
					}

					//回调
					_hHandler->OnRemovePhysical(msg.uID);
					return true;
				}
				break;
			case MsgCenterNtf::TYPE_REMOVE_LOGIC:
				{
					{
						CLockRead lockLinkType(_vLogic.GetMutexConfig());
						CLockWrite lockLogic(_vLogic.GetMutexLogic());

						_vLogic.RemoveLogicByServerID(msg.uID);
						_vLogic.OptimizeSrvType();
					}

					//回调
					_hHandler->OnRemoveLogic(msg.uID);
					return true;
				}
				break;
			case MsgCenterNtf::TYPE_LOGIC_SHUT_DOWN:
				{
					//回调
					_hHandler->OnShutDown();
					return true;
				}
				break;
			}
		}
		break;
	case MSG_LOGIC_UPDATE_NTF:
		{
			MsgLogicUpdateNtf msg(msgStream);
			if (!msg.Load())return false;

			{
				CLockRead lockLinkType(_vLogic.GetMutexConfig());
				CLockWrite lockLogic(_vLogic.GetMutexLogic());
				MapLogicUpdate::const_iterator itr;
				foreach(itr,msg.vUpdate){
					ASSERT_LOG_ERROR(_vLogic.UpdateLogicState(itr->first,itr->second));
				}
			}

			_hHandler->OnLogicStateChanged(msg.vUpdate,pConnectMonitor->GetClientID());
			return true;
		}
		break;
	case MSG_PHYSICAL_UPDATE_NTF:
		{
			MsgPhysicalUpdateNtf msg(msgStream);
			if (!msg.Load())return false;

			{
				CLockWrite lockPhysical(_vPhysical.GetMutexPhysical());
				MapPhysicalUpdate::const_iterator itr;
				foreach(itr,msg.vUpdate){
					ASSERT_LOG_ERROR(_vPhysical.UpdatePhysicalState(itr->first,itr->second));
				}
			}

			_hHandler->OnPhysicalStateChanged(msg.vUpdate,pConnectMonitor->GetClientID());
			return true;
		}
		break;
	case MSG_LOGIC_DEBUG:
		{
			MsgLogicDebug msg(msgStream);
			if (!msg.Load())return false;

			{
				CLockRead lockLinkType(_vLogic.GetMutexConfig());
				CLockWrite lockLogic(_vLogic.GetMutexLogic());
				_vLogic.UpdateDebugString(msg.uServerID, msg.sString);
			}

			_hHandler->OnLogicDebug(msg.uServerID, msg.sString);
			return true;
		}
		break;
	}
	return true;
}

bool CTopologyControl::SendAuthorization( uint uClientID ) const
{
	MsgCenterAuthorization msg;
	msg.eClientType = CLIENT_TYPE_CONTROL;
	msg.sPassword = _sPassword;
	return Send(msg);
}

bool CTopologyControl::SendControlRegist( uint uClientID ) const
{
	MsgControlRegist msg;
	return Send(msg);
}

bool CTopologyControl::SetHandler( HTopologyControl* hHandler )
{
	_hHandler = hHandler;
	return true;
}

bool CTopologyControl::SetRecvSize( uint uSize )
{
	_vLogic.SetRecvSize(uSize);
	return _monitor.SetRecvSize(uSize);
}

bool CTopologyControl::SetSendSize( uint uSize )
{
	_vLogic.SetSendSize(uSize);
	return _monitor.SetSendSize(uSize);
}

bool CTopologyControl::SetBlockSize(uint uSize)
{
	_vLogic.SetBlockSize(uSize);
	return _monitor.SetBlockSize(uSize);
}

bool CTopologyControl::SetConfigLogic( const MapConfigLogic& vConfigLogic )
{
	_vConfigLogic = vConfigLogic;
	return true;
}

bool CTopologyControl::SetConfigLink( const MapConfigLink& vConfigLink )
{
	_vConfigLink = vConfigLink;
	return true;
}

bool CTopologyControl::SetConfigServer( const MapConfigServer& vConfigServer )
{
	_vConfigServer = vConfigServer;
	return true;
}

bool CTopologyControl::SendServerConfig()const
{
	MsgControlSetServer msg;
	msg.sServerGroupID	= _sServerGroupID;
	msg.sServerZoneID	= _sServerZoneID;
	msg.sServerName		= _sServerName;
	msg.xServerOpen		= _xServerOpen;
	msg.sServerTag		= _sServerTag;
	
	msg.vConfigLogic	= _vConfigLogic;
	msg.vConfigLink		= _vConfigLink;
	msg.vConfigServer	= _vConfigServer;

	return Send(msg);
}

bool CTopologyControl::SendPhysicalStartServer( uint32 uServerID )const
{
	MsgControlPhysicalStartServer msg;
	msg.uServerID = uServerID;

	return Send(msg);
}

bool CTopologyControl::SendPhysicalMemoryClear( uint32 uPhysicalID )const
{
	MsgControlPhysicalMemoryClear msg;
	msg.uPhysicalID = uPhysicalID;

	return Send(msg);
}

bool CTopologyControl::SendPhysicalReboot( uint32 uPhysicalID )const
{
	MsgControlPhysicalReboot msg;
	msg.uPhysicalID = uPhysicalID;

	return Send(msg);
}

const MapConfigLogic& CTopologyControl::GetConfigLogic() const
{
	return _vConfigLogic;
}

const MapConfigLink& CTopologyControl::GetConfigLink() const
{
	return _vConfigLink;
}

const MapConfigServer& CTopologyControl::GetConfigServer() const
{
	return _vConfigServer;
}

const std::string& CTopologyControl::TranSrvType( int eSrvType ) const
{
	const XConfigLogic* pConfig = FindConfigSrvType(eSrvType);
	if (!pConfig)return ToolFrame::EmptyString();

	return pConfig->sRemark;
}

const XConfigServer* CTopologyControl::FindConfigServer( uint uServerID ) const
{
	return ToolFrame::GetValuePtrByKey(_vConfigServer,uServerID);
}

const XConfigLogic* CTopologyControl::FindConfigSrvType( int eSrvType ) const
{
	return ToolFrame::GetValuePtrByKey(_vConfigLogic,eSrvType);
}

bool CTopologyControl::Send( IMsgStream& msgBase )const
{
	return _monitor.Send(msgBase);
}

bool CTopologyControl::SendLogicSaveServer( uint32 uServerID )const
{
	MsgControlSaveServer msg;
	msg.uServerID = uServerID;
	return Send(msg);
}

bool CTopologyControl::SendLogicCleanUpServer( uint32 uServerID )const
{
	MsgControlCleanUpServer msg;
	msg.uServerID = uServerID;
	return Send(msg);
}

bool CTopologyControl::SendLogicStopService( uint32 uServerID )const
{
	MsgControlStopService msg;
	msg.uServerID = uServerID;
	return Send(msg);
}	

bool CTopologyControl::SendLogicShutDown(uint32 uServerID)const
{
	MsgControlShutDown msg;
	msg.uServerID = uServerID;
	return Send(msg);
}

bool CTopologyControl::SendLogicDebug(uint32 uServerID, const VectorString& vDebug) const
{
	MsgControlDebugServer msg;
	msg.uServerID = uServerID;
	msg.vDebug = vDebug;
	return Send(msg);
}

const VectorString& CTopologyControl::GetCenterAddress() const
{
	return _monitor.GetServerAddress();
}

bool CTopologyControl::OnStateChanged( CConnectMonitor* pConnectMonitor,int eState )
{
	return _hHandler->OnConnectStateChanged(eState);
}

bool CTopologyControl::IsLogicOnline( uint32 uServerID ) const
{
	return _vLogic.IsLogicOnline(uServerID);
}

bool CTopologyControl::FindOnlineServerList(VectorUint& vServerID)const
{
	return _vLogic.FindOnlineServerList(vServerID);
}

bool CTopologyControl::IsAuthorized() const
{
	return _bAuthorized;
}

bool CTopologyControl::SetServerGroupID( const std::string& sServerGroupID )
{
	_sServerGroupID = sServerGroupID;
	return true;
}

bool CTopologyControl::SetServerZoneID( const std::string& sServerZoneID )
{
	_sServerZoneID = sServerZoneID;
	return true;
}
bool CTopologyControl::SetServerName( const std::string& sServerName )
{
	_sServerName = sServerName;
	return true;
}

bool CTopologyControl::SetServerOpen( const CDate& xServerOpen )
{
	_xServerOpen = xServerOpen;
	return true;
}

bool CTopologyControl::SetServerTag(const std::string& sTag)
{
	_sServerTag = sTag;
	return true;
}

const std::string& CTopologyControl::GetServerGroupID() const
{
	 return _sServerGroupID;
}

const std::string& CTopologyControl::GetServerZoneID() const
{
	 return _sServerZoneID;
}

const std::string& CTopologyControl::GetServerTag() const
{
	return _sServerTag;
}

std::string CTopologyControl::GetDebugString() const
{
	return _vLogic.GetDebugString();
}

const CTopologyServerLogic& CTopologyControl::GetServersLogic() const
{
	return _vLogic;
}

const CTopologyServerPhysical& CTopologyControl::GetServersPhysical() const
{
	return _vPhysical;
}

const std::string& CTopologyControl::GetConnectedCenterAddress() const
{
	return _monitor.GetConnectedAddress();
}

NS_TOOL_FRAME_END
