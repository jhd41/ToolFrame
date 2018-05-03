#include "TopologyLogic.h"

#include "TopologyProtocol.h"
#include "MProtocol.h"
#include "MSystem.h"

NS_TOOL_FRAME_BEGIN

CTopologyLogic::CTopologyLogic(void)
{
	_uTimeReport			= 5000;
	_uTimeSave				= 30*60;
	_uTimeTryCreateServer	= 1000;

	_bAuthorized	= false;
	_bServerCreated = false;
	_bRegisted		= false;

	_eState			= CONNECT_STATE_INIT;
	_uCacheVaild	= 0;
	_uCacheTotal	= 0;
	_uProcesserCount = 0;
	_uQueueSize = 0;
	_uQueueProcess	= 0;
	_uTimeRunOnce	= 0;
	_uTimeRunOnceMax= 0;

	_uLastSave	= 0;
	_uLastCleanUp=0;
	_uPhysicalID= 0;
	_uPublicRecv= MProtocol::Singleton().GetRecvSize();
	_uPublicSend= MProtocol::Singleton().GetSendSize();
	_uPublicBlock = MProtocol::Singleton().GetBlockSize();
	_uPublicConnect = 0;
	_uRunOnceMax= 300;

	_bShutDown = false;

	_monitor.SetHandler(this);
	_vLinker.SetManager(&_vLogic);
	_vLinker.SetManager(&_vPhysical);
}

CTopologyLogic::~CTopologyLogic(void)
{
	RemoveTimerReport();
	RemoveTimerSave();
	RemoveTimerCreateServer();
	RemoveTimerCreatePublicServer();

	//关闭
	VectorUint::const_iterator itr;
	foreach(itr, _vPublicPort) {
		MProtocol::Singleton().RemoveConnectMax(*itr, LINK_TYPE_NET_TCP);
	}
}

bool CTopologyLogic::Init()
{
	if (!_hHandler)return false;
	if (INVALID_ID == _vLogic.GetServerType())return false;
	
	if (!_monitor.Start())return false;
	if (!_vLogic.Init())return false;

	_vLinker.SetHandler(_hHandler);

	if (!_vLinker.Init())return false;

	if (_pTimerReport)return false;

	CreateTimerReport();
	CreateTimerSave();
	return true;
}

bool CTopologyLogic::SetPassword( const std::string& sPassword )
{
	_sPassword = sPassword;
	return true;
}

bool CTopologyLogic::SetCenterIP( const std::string& sCenterIP )
{
	return _monitor.SetServerAddress(sCenterIP);
}

bool CTopologyLogic::OnConnected( CConnectMonitor* pConnectMonitor )
{
	_hHandler->OnCenterConnected(pConnectMonitor->GetClientID());
	SendAuthorization();
	return true;
}

bool CTopologyLogic::OnDisconnected( CConnectMonitor* pConnectMonitor )
{
	_bAuthorized = false;
	_bRegisted = false;
	RemoveTimerCreateServer();
	_hHandler->OnCenterDisconnected(pConnectMonitor->GetClientID());
	return true;
}

bool CTopologyLogic::OnRecved( CConnectMonitor* pConnectMonitor,IMsgStream& msgStream)
{
	switch(msgStream.GetOpCode())
	{
	case MSG_CENTER_AUTHORIZATION_REP:
		{
			MsgCenterAuthorizationRep msg(msgStream);
			if (!msg.Load())return false;

			//如果授权通过
			_bAuthorized = !!msg.bAuthorized;

			_hHandler->OnCenterAuthorized(pConnectMonitor->GetClientID(),_bAuthorized);

			if (!_bAuthorized)
				return true;

			if (!IsServerCreared())
				CreateTimerCreateServer();
			return true;
		}
		break;
	case MSG_LOGIC_REGIST_REP:
		{
			MsgLogicRegistRep msg(msgStream);
			if (!msg.Load())return false;

			_bRegisted = !!msg.bSucceed;
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

						ASSERT_LOG_ERROR(_vLogic.AddServer(msg.vLogic));
						ASSERT_LOG_ERROR(_vPhysical.AddServer(msg.vPhysical));

						ASSERT_LOG_ERROR(_vLogic.OptimizeSrvTypeInit());
						ASSERT_LOG_ERROR(_vLogic.OptimizeSrvType());
					}
					_vLinker.CheckIsAllServerConnectd();
				}
				break;
			case MsgCenterNtf::TYPE_ADD_LOGIC:
				{
					CLockRead lockLinkType(_vLogic.GetMutexConfig());
					CLockWrite lockLogic(_vLogic.GetMutexLogic());
					
					ASSERT_LOG_ERROR(_vLogic.AddServer(msg.vLogic));
					ASSERT_LOG_ERROR(_vLogic.OptimizeSrvType());
				}
				break; 
			case MsgCenterNtf::TYPE_REMOVE_LOGIC:
				{
					CLockRead lockLinkType(_vLogic.GetMutexConfig());
					CLockWrite lockLogic(_vLogic.GetMutexLogic());

					_vLinker.RemoveServer(msg.uID);
					_vLogic.RemoveLogicByServerID(msg.uID);
					ASSERT_LOG_ERROR(_vLogic.OptimizeSrvType());
				}
				break;
			case MsgCenterNtf::TYPE_LOGIC_SAVE:
				{
					//更新服务器保存时间
					RemoveTimerSave();

					_hHandler->OnServerSave();
					
					_uLastSave = ToolFrame::GetNowTime();

					CreateTimerSave();
				}
				break;
			case MsgCenterNtf::TYPE_LOGIC_CLEAN_UP:
				{
					_hHandler->OnServerCleanUp();

					_uLastCleanUp = ToolFrame::GetNowTime();
				}
				break;
			case MsgCenterNtf::TYPE_LOGIC_STOP_SERVICE:
				{
					_hHandler->OnServerStopService();
				}
				break;
			case MsgCenterNtf::TYPE_LOGIC_SHUT_DOWN:
				{
					_hHandler->OnServerShutDown();
					_bShutDown = true;
				}
				break;
			case MsgCenterNtf::TYPE_LOGIC_DEBUG:
				{
					std::string sDebugString = _hHandler->OnServerDebug(msg.vDebug);

					MsgLogicDebug msg;
					msg.uServerID = _vLogic.GetServerID();
					msg.sString = sDebugString;

					SendToCenter(msg);
				}
				break;
			}

			_vLinker.Update();
			return true;
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

				_vLogic.OptimizeSrvType();
			}

			_vLinker.Update();

			_hHandler->OnServerStateChanged(msg.vUpdate,pConnectMonitor->GetClientID());
			return true;
		}
		break;
	}
	return true;
}

bool CTopologyLogic::SendAuthorization() const
{
	MsgCenterAuthorization msg;
	msg.eClientType = CLIENT_TYPE_LOGIC;
	msg.sPassword = _sPassword;

	return SendToCenter(msg);
}

bool CTopologyLogic::SendLogicRegist() const
{
	MsgLogicRegist msg;
	msg.uServerID	= _vLogic.GetServerID();
	msg.eSrvType	= _vLogic.GetServerType();
	msg.uProcessID	= ToolFrame::GetProcessId();
	GetUpdateData(msg.xUpdate);
	return SendToCenter(msg);
}

bool CTopologyLogic::SendUpdateState() const
{
	MsgLogicUpdateReq msg;
	msg.uServerID	= _vLogic.GetServerID();
	GetUpdateData(msg.xUpdate);

	return SendToCenter(msg);
}

bool CTopologyLogic::SetType( int eType )
{
	return _vLogic.SetSrvType(eType);
}

bool CTopologyLogic::SetPort( uint uPort )
{
	return _vLogic.SetPort(uPort);
}

uint CTopologyLogic::SendClientID( uint uClientID, StreamBinaryPtr ptr,const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/,uint uUserID /*= INVALID_ID*/ ) const
{
	return _vLinker.SendClientID(uClientID,ptr,xSrcID,uUserID);
}

uint CTopologyLogic::SendClientID(uint uClientID, const IMsgStream& msg, const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, uint uUserID /*= INVALID_ID*/) const
{
	return SendClientID(uClientID, msg.GetSendStream(), xSrcID, uUserID);
}

uint CTopologyLogic::SendServerID( uint uServerID, StreamBinaryPtr ptr,const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/,uint uUserID /*= INVALID_ID*/ ) const
{
	if (INVALID_ID == uServerID)return INVALID_ID;

	uint uClientID = FindClientID(uServerID);
	if (INVALID_ID == uClientID)return INVALID_ID;
	return SendClientID(uClientID,ptr,xSrcID,uUserID);
}

uint CTopologyLogic::SendServerID(uint uServerID, const IMsgStream& msg, const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, uint uUserID /*= INVALID_ID*/) const
{
	return SendServerID(uServerID, msg.GetSendStream(), xSrcID, uUserID);
}

bool CTopologyLogic::SetListener( HTopologyLogic* hHandler )
{
	_hHandler = hHandler;
	return true;
}

bool CTopologyLogic::SetServerID( uint uServerID )
{
	return _vLogic.SetServerID(uServerID);
}

int CTopologyLogic::GetServerID() const
{
	return _vLogic.GetServerID();
}

int CTopologyLogic::GetServerType() const
{
	return _vLogic.GetServerType();
}

bool CTopologyLogic::SetStateNormal()
{
	if (CONNECT_STATE_NORMAL == _eState)return false;

	_eState = CONNECT_STATE_NORMAL;
	return UpdateState();
}

bool CTopologyLogic::SetStateStop()
{
	if (CONNECT_STATE_STOP_SERVICE == _eState)return false;

	_eState = CONNECT_STATE_STOP_SERVICE;
	return UpdateState();
}

bool CTopologyLogic::OnTimeOut( const CTimeNodePtr& pTimeNode )
{
	if (_pTimerReport == pTimeNode)
	{
		if (IsRegisted())
		{
			//触发
			_hHandler->OnServerReport();

			//更新
			UpdateState();
		}
		return true;
	}
	if (_pTimerSave == pTimeNode){
		if (IsRegisted())
		{
			//触发
			_hHandler->OnServerSave();
			_uLastSave = ToolFrame::GetNowTime();
		}
		return true;
	}
	if (_pTimerCreateServer == pTimeNode)
	{
		if (TryCreateServer())
		{
			RemoveTimerCreateServer();
			SendLogicRegist();
		}
		return true;
	}
	if (_pTimerCreatePublicServer == pTimeNode)
	{
		if (TryCreatePublicServer())
			RemoveTimerCreatePublicServer();
		return true;
	}
	return false;
}

bool CTopologyLogic::SetTimeReport(uint uTimeMil)
{
	_uTimeReport = uTimeMil;
	return true;
}

bool CTopologyLogic::SetCacheVaild(size_t uCacheVaild )
{
	_uCacheVaild = uCacheVaild;
	return true;
}

bool CTopologyLogic::SetCacheTotal(size_t uCacheTotal )
{
	_uCacheTotal = uCacheTotal;
	return true;
}

bool CTopologyLogic::SetProcesserCount(size_t uProcesserCount)
{
	_uProcesserCount = uProcesserCount;
	return true;
}

bool CTopologyLogic::SetQueueSize(size_t uQueueSize)
{
	_uQueueSize = uQueueSize;
	return true;
}

bool CTopologyLogic::SetQueueProcess(size_t uQueueProcess )
{
	_uQueueProcess = uQueueProcess;
	return true;
}

bool CTopologyLogic::SetRecvSize( uint uSize )
{
	_vLogic.SetRecvSize(uSize);
	return _monitor.SetRecvSize(uSize);
}

bool CTopologyLogic::SetSendSize( uint uSize )
{
	_vLogic.SetSendSize(uSize);
	return _monitor.SetSendSize(uSize);
}

bool CTopologyLogic::SetBlockSize(uint uSize)
{
	_vLogic.SetBlockSize(uSize);
	return _monitor.SetBlockSize(uSize);
}

bool CTopologyLogic::SetCommandLine( const std::string& sCommandLine )
{
	//std::string sCommandLine = MAKE_STRING("ServerID:"<<msg.uServerID<<" SrvType:"<<msg.eSrvType<<" Port:"<<msg.uPort<<" RecvBufferSize:"<<msg.uRecvBufferSize<<" SendBufferSize:"<<msg.uSendBufferSize<<" CenterIP:"<<msg.sCenterIP<<" Password:"<<msg.sPassword);

	MapStringString vKeyValue;
	if (!ToolFrame::ToValue(sCommandLine,vKeyValue))return false;
	
	uint uServerID = INVALID_ID;uint uSrvType = 0;uint uThread =0; uint uRunOnceMax = 0;
	uint uPort=0;uint uRecvSize=0;uint uSendSize=0; uint uBlockSize = 0;
	uint uHash=0;uint uHashCount=0;

	std::string sSrvTag;
	
	std::string sCenterIP;std::string sPassword;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"ServerID",		uServerID))return false;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"SrvType",		uSrvType))return false;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"Thread",			uThread))return false;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"RunOnce",		uRunOnceMax))return false;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"Port",			uPort))return false;
	
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"RecvSize",		uRecvSize))return false;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"SendSize",		uSendSize))return false;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"BlockSize",		uBlockSize))return false;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"SaveTime",		_uTimeSave))return false;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"PhysicalID",		_uPhysicalID))return false;
	
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"PublicPort",		_vPublicPort))return false;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"PublicRecv",		_uPublicRecv))return false;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"PublicSend",		_uPublicSend))return false;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"PublicBlock",	_uPublicBlock))return false;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"PublicConnect",	_uPublicConnect))return false;
	

	if (!ToolFrame::GetValueByKeyString(vKeyValue,"Hash",			uHash))return false;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"HashCount",		uHashCount))return false;

	if (!ToolFrame::GetValueByKeyString(vKeyValue, "SrvTag",		sSrvTag))return false;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"Command",		_sCommand))return false;

	if (!ToolFrame::GetValueByKeyString(vKeyValue,"CenterIP",		sCenterIP))return false;
	if (!ToolFrame::GetValueByKeyString(vKeyValue,"Password",		sPassword))return false;

	SetServerID(uServerID);
	SetCenterIP(sCenterIP);
	SetPassword(sPassword);
	SetType(uSrvType);
	SetThread(uThread);
	SetRunOnceMax(uRunOnceMax);
	SetPort(uPort);
	SetRecvSize(uRecvSize);
	SetSendSize(uSendSize);
	SetBlockSize(uBlockSize);

	SetHash(uHash);
	SetHashCount(uHashCount);

	_vLogic.SetServerTag(sSrvTag);
	return true;
}

bool CTopologyLogic::SetPublicPort( const VectorUint& vPort )
{
	_vPublicPort = vPort;
	return true;
}

bool CTopologyLogic::SetPublicRecv( uint uSize )
{
	_uPublicRecv = uSize;
	return true;
}

bool CTopologyLogic::SetPublicSend( uint uSize )
{
	_uPublicSend = uSize;
	return true;
}

bool CTopologyLogic::SetPublicBlock(uint uSize)
{
	_uPublicBlock = uSize;
	return true;
}

bool CTopologyLogic::SetPublicConnect(uint uSize)
{
	_uPublicConnect = uSize;
	return true;
}

const VectorUint& CTopologyLogic::GetPublicPort() const
{
	return _vPublicPort;
}

uint CTopologyLogic::GetPublicRecv() const
{
	return _uPublicRecv;
}

uint CTopologyLogic::GetPublicSend() const
{
	return _uPublicSend;
}

uint CTopologyLogic::GetPublicBlock() const
{
	return _uPublicBlock;
}

uint CTopologyLogic::GetPublicConnect() const
{
	return _uPublicConnect;
}

bool CTopologyLogic::SetHash( uint uHash )
{
	return _vLogic.SetHash(uHash);
}

bool CTopologyLogic::SetHashCount( uint uHashCount )
{
	return _vLogic.SetHashCount(uHashCount);
}

const std::string& CTopologyLogic::GetCommand() const
{
	return _sCommand;
}

uint CTopologyLogic::GetHash() const
{
	return _vLogic.GetHash();
}

bool CTopologyLogic::SendToCenter( IMsgStream& msgBase )const
{
	return _monitor.Send(msgBase);
}

uint CTopologyLogic::SendBalance( int eSrvType, StreamBinaryPtr ptr,const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/,uint uUserID /*= INVALID_ID*/ ) const
{
	if (INVALID_ID == eSrvType)return INVALID_ID;
	if (!ptr)return INVALID_ID;
	if (ptr->IsEmpty())return INVALID_ID;

	uint uClientID = FindClientIDBalance(eSrvType);
	if (INVALID_ID == uClientID)return INVALID_ID;
	return _vLinker.SendClientID(uClientID,ptr,xSrcID,uUserID);
}

uint CTopologyLogic::SendBalance(int eSrvType, const IMsgStream& msg, const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, uint uUserID /*= INVALID_ID*/) const
{
	return SendBalance(eSrvType, msg.GetSendStream(), xSrcID, uUserID);
}

uint CTopologyLogic::SendSrvType(int eSrvType, StreamBinaryPtr ptr, const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, uint uUserID /*= INVALID_ID*/) const
{
	if (INVALID_ID == eSrvType)return INVALID_ID;
	if (!ptr)return INVALID_ID;
	if (ptr->IsEmpty())return INVALID_ID;

	switch (_vLogic.FindServerRunType(eSrvType))
	{
		case RUN_TYPE_RANDOM:
			return SendRandom(eSrvType, ptr, xSrcID, uUserID);
			break;
		case RUN_TYPE_HASH:
			{
				//如果用户ID为无效值，为了考虑负载均衡，我们会随机发到所有的机器
				if (INVALID_ID == uUserID)
					return SendRandom(eSrvType, ptr, xSrcID, uUserID);
				return SendHash(eSrvType, uUserID, ptr, xSrcID, uUserID);
			}
			break;
		case RUN_TYPE_UNIQUE:
			return SendRandom(eSrvType, ptr, xSrcID, uUserID);
			break;
		case RUN_TYPE_BALANCE:
			return SendBalance(eSrvType, ptr, xSrcID, uUserID);
			break;
		case RUN_TYPE_SEQUENCE:
			return SendSeq(eSrvType, ptr, xSrcID, uUserID);
			break;
	}

	return INVALID_ID;
}

uint CTopologyLogic::SendSrvType(int eSrvType, const IMsgStream& msg, const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, uint uUserID /*= INVALID_ID*/) const
{
	return SendSrvType(eSrvType, msg.GetSendStream(), xSrcID, uUserID);
}

uint CTopologyLogic::SendRandom(int eSrvType, StreamBinaryPtr ptr, const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, uint uUserID /*= INVALID_ID*/) const
{
	if (INVALID_ID == eSrvType)return INVALID_ID;
	if (!ptr)return INVALID_ID;
	if (ptr->IsEmpty())return INVALID_ID;

	uint uClientID = FindClientIDRandom(eSrvType);
	if (INVALID_ID == uClientID)return INVALID_ID;
	return _vLinker.SendClientID(uClientID,ptr,xSrcID,uUserID);
}

uint CTopologyLogic::SendRandom(int eSrvType, const IMsgStream& msg, const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, uint uUserID /*= INVALID_ID*/) const
{
	return SendRandom(eSrvType, msg.GetSendStream(), xSrcID, uUserID);
}

uint CTopologyLogic::SendSeq( int eSrvType, StreamBinaryPtr ptr,const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/,uint uUserID /*= INVALID_ID*/ ) const
{
	if (INVALID_ID == eSrvType)return INVALID_ID;
	if (!ptr)return INVALID_ID;
	if (ptr->IsEmpty())return INVALID_ID;

	uint uClientID = FindClientIDSequence(eSrvType);
	if (INVALID_ID == uClientID)return INVALID_ID;
	return _vLinker.SendClientID(uClientID,ptr,xSrcID,uUserID);
}

uint CTopologyLogic::SendSeq(int eSrvType, const IMsgStream& msg, const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, uint uUserID /*= INVALID_ID*/) const
{
	return SendSeq(eSrvType, msg.GetSendStream(), xSrcID, uUserID);
}

uint CTopologyLogic::SendHashKey( int eSrvType,uint uHash, StreamBinaryPtr ptr,const XTopologyID& xSrcID,uint uUserID ) const
{
	if (INVALID_ID == eSrvType)return INVALID_ID;
	if (!ptr)return INVALID_ID;
	if (ptr->IsEmpty())return INVALID_ID;

	uint uClientID = FindClientIDHashKey(eSrvType,uHash);
	if (INVALID_ID == uClientID)return INVALID_ID;
	return _vLinker.SendClientID(uClientID,ptr,xSrcID,uUserID);
}

uint CTopologyLogic::SendHash( int eSrvType,uint uHashKey, StreamBinaryPtr ptr,const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/,uint uUserID /*= INVALID_ID*/ ) const
{
	if (INVALID_ID == eSrvType)return INVALID_ID;
	if (!ptr)return INVALID_ID;
	if (ptr->IsEmpty())return INVALID_ID;

	uint uClientID = FindClientIDHash(eSrvType,uHashKey);
	if (INVALID_ID == uClientID)return INVALID_ID;
	return _vLinker.SendClientID(uClientID,ptr,xSrcID,uUserID);
}

uint CTopologyLogic::SendHash( int eSrvType,const std::string& sHashString, StreamBinaryPtr ptr,const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/,uint uUserID /*= INVALID_ID*/ ) const
{
	if (INVALID_ID == eSrvType)return INVALID_ID;
	if (!ptr)return INVALID_ID;
	if (ptr->IsEmpty())return INVALID_ID;

	uint uClientID = FindClientIDHash(eSrvType,sHashString);
	if (INVALID_ID == uClientID)return INVALID_ID;
	return _vLinker.SendClientID(uClientID,ptr,xSrcID,uUserID);
}

uint CTopologyLogic::SendHash(int eSrvType, const std::string& sHashString, const IMsgStream& msg, const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, uint uUserID /*= INVALID_ID*/) const
{
	return SendHash(eSrvType, sHashString,msg.GetSendStream(), xSrcID, uUserID);
}

uint CTopologyLogic::SendHash(int eSrvType, uint uHashKey, const IMsgStream& msg, const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, uint uUserID /*= INVALID_ID*/) const
{
	return SendHash(eSrvType, uHashKey, msg.GetSendStream(), xSrcID, uUserID);
}

uint CTopologyLogic::FindClientIDHash( int eSrvType,uint uHashKey ) const
{
	if (INVALID_ID == eSrvType)return INVALID_ID;

	uint uHashCount = 0;
	if (!_vLogic.FindHashCount(&uHashCount,eSrvType))
		return INVALID_ID;

	if (uHashCount<= 0)return INVALID_ID;

	uint uHash = ToolFrame::Hash(uHashKey,uHashCount);
	return FindClientIDHashKey(eSrvType,uHash);
}

uint CTopologyLogic::FindClientIDHash( int eSrvType,const std::string& sHashString ) const
{
	if (INVALID_ID == eSrvType)return INVALID_ID;

	uint uHashCount = 0;
	if (!_vLogic.FindHashCount(&uHashCount,eSrvType))
		return INVALID_ID;

	if (uHashCount<= 0)return INVALID_ID;

	uint uHash = ToolFrame::Hash(sHashString,uHashCount);
	return FindClientIDHashKey(eSrvType,uHash);
}

uint CTopologyLogic::FindClientIDHashKey( int eSrvType,uint uHash ) const
{
	uint nSrvID = _vLogic.FindServerIDHash(eSrvType,uHash);
	if (INVALID_ID == nSrvID)return INVALID_ID;
	return FindClientID(nSrvID);
}

bool CTopologyLogic::IsAuthorized() const
{
	return _bAuthorized;
}

bool CTopologyLogic::CreatePublicServer()
{
	return CreateTimerCreatePublicServer();
}

bool CTopologyLogic::TryCreatePublicServer()
{
	bool bSucceed = true;
	VectorUint::const_iterator itr;
	foreach(itr,GetPublicPort()){
		uint uPort = *itr;
		if (!MProtocol::Singleton().IsCreatedServer(uPort,LINK_TYPE_NET_TCP)){
			MProtocol::Singleton().SetConnectMax(uPort, LINK_TYPE_NET_TCP,_uPublicConnect);
			if (!MProtocol::Singleton().CreateServer(this,uPort,LINK_TYPE_NET_TCP,GetPublicRecv(),GetPublicSend(), GetPublicBlock())){
				_hHandler->OnServerCreatePublicFaild(uPort);
				bSucceed = false;	
			}else{
				_hHandler->OnServerCreatePublicSucceed(uPort);		
			}
		}
	}
	return bSucceed;
}

bool CTopologyLogic::ClosePublicServer()
{
	VectorUint::const_iterator itr;
	foreach(itr,GetPublicPort()){
		MProtocol::Singleton().CloseServer(*itr,LINK_TYPE_NET_TCP);
	}
	return true;
}


bool CTopologyLogic::OnConnected( UINT uClientID )
{
	_hHandler->OnPublicConnected(uClientID);
	return true;
}

bool CTopologyLogic::OnConnectFailed( UINT uClientID )
{
	LOG_ERROR();
	return true;
}

bool CTopologyLogic::OnDisconnected( UINT uClientID )
{
	_hHandler->OnPublicDisconnected(uClientID);
	return true;
}

bool CTopologyLogic::OnRecv(IDataSession* pSession,IMsgStream& msgStream )
{
	_hHandler->OnPublicRecv(pSession->GetClientID(), pSession,msgStream);
	return true;
}

uint CTopologyLogic::OnRecv(IDataSession* pSession)
{
	ASSERT_LOG_ERROR(pSession);
	
	uint uProcessed = _hHandler->OnPublicRecv(pSession->GetClientID(),pSession);
	if (uProcessed > 0)
		return uProcessed;

	if (_hHandler->OnPublicRecv(pSession->GetClientID(), pSession,pSession->GetRecvedBuffer()))
		return 1;

	return IDataReceiverStream::OnRecv(pSession);
}

uint CTopologyLogic::GetRecvSize() const
{
	return _vLogic.GetRecvSize();
}

uint CTopologyLogic::GetSendSize() const
{
	return _vLogic.GetSendSize();
}

bool CTopologyLogic::IsShutDown() const
{
	return _bShutDown;
}

bool CTopologyLogic::SendPublic(uint uClientID, const char* pBuffer, uint uSize)
{
	return MProtocol::Singleton().Send(uClientID, pBuffer, uSize);
}

bool CTopologyLogic::SendPublic(uint uClientID, StreamBinaryPtr ptr)
{
	return MProtocol::Singleton().Send(uClientID, ptr);
}

bool CTopologyLogic::CreateTimerSave()
{
	if (_uTimeSave <= 0)return true;
	_pTimerSave = MSystem::Singleton().GetTimeOutQueque().CreateTimerByAfterSec(this,_uTimeSave,true,_uTimeSave);
	return true;
}

bool CTopologyLogic::RemoveTimerSave()
{
	MSystem::Singleton().GetTimeOutQueque().RemoveTimer(_pTimerSave);
	ToolFrame::SetPtrNull(_pTimerSave);
	return true;
}

bool CTopologyLogic::SetPhysicalID( uint uPhysicalID )
{
	_uPhysicalID = uPhysicalID;
	return true;
}

uint CTopologyLogic::GetPhysicalID() const
{
	return _uPhysicalID;
}

bool CTopologyLogic::BroadCast( int eSrvType, StreamBinaryPtr ptr,const XTopologyID& uID /*= TOPOLOGY_ID_INVAILD*/,uint uUserID /*= INVALID_ID*/ ) const
{
	SetUint vSrvID;
	if (!_vLinker.ConnectDataGetServerID(vSrvID,eSrvType))return false;
	if (vSrvID.empty())return false;

	SetUint::const_iterator itr;
	foreach(itr,vSrvID){
		SendServerID(*itr,ptr,uID,uUserID);
	}

	return true;
}

bool CTopologyLogic::BroadCast(int eSrvType, const IMsgStream& msg, const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, uint uUserID /*= INVALID_ID*/) const
{
	return BroadCast(eSrvType, msg.GetSendStream(), xSrcID, uUserID);
}

uint CTopologyLogic::FindServerID( uint uClientID ) const
{
	return _vLinker.ConnectDataFindServerID(uClientID);
}

bool CTopologyLogic::IsRegisted() const
{
	return _bRegisted;
}

bool CTopologyLogic::UpdateState()
{
	if (!_monitor.IsConnected())return false;
	if (!IsRegisted())return false;//只有当注册完成才可以更新自己的数据
	return SendUpdateState();
}

bool CTopologyLogic::TryCreateServer()
{
	ASSERT_LOG_ERROR(!_bServerCreated);
	if (!_vLinker.CreateServer()){
		_hHandler->OnServerCreateFaild(_vLogic.GetPort());
		return false;
	}
	_hHandler->OnServerCreateSucceed(_vLogic.GetPort());
	_bServerCreated = true;
	return true;
}

bool CTopologyLogic::CreateTimerReport()
{
	ASSERT_LOG_ERROR(!_pTimerReport);
	_pTimerReport = MSystem::Singleton().GetTimeOutQueque().CreateTimerByAfterMil(this,_uTimeReport,true,_uTimeReport);
	return true;
}

bool CTopologyLogic::RemoveTimerReport()
{
	MSystem::Singleton().GetTimeOutQueque().RemoveTimer(_pTimerReport);
	ToolFrame::SetPtrNull(_pTimerReport);
	return true;
}

bool CTopologyLogic::CreateTimerCreateServer()
{
	ASSERT_LOG_ERROR(!_pTimerCreateServer);
	_pTimerCreateServer = MSystem::Singleton().GetTimeOutQueque().CreateTimerByAfterMil(this,0,true,_uTimeTryCreateServer);
	return true;
}

bool CTopologyLogic::RemoveTimerCreateServer()
{
	MSystem::Singleton().GetTimeOutQueque().RemoveTimer(_pTimerCreateServer);
	ToolFrame::SetPtrNull(_pTimerCreateServer);
	return true;
}
bool CTopologyLogic::CreateTimerCreatePublicServer()
{
	if (_pTimerCreatePublicServer)return false;
	_pTimerCreatePublicServer = MSystem::Singleton().GetTimeOutQueque().CreateTimerByAfterMil(this,0,true,_uTimeTryCreateServer);
	return true;
}

bool CTopologyLogic::RemoveTimerCreatePublicServer()
{
	MSystem::Singleton().GetTimeOutQueque().RemoveTimer(_pTimerCreatePublicServer);
	ToolFrame::SetPtrNull(_pTimerCreatePublicServer);
	return true;
}
bool CTopologyLogic::IsServerCreared() const
{
	return _bServerCreated;
}

const std::string& CTopologyLogic::GetServerGroupID() const
{
	return _vLogic.GetServerGroupID();
}

const std::string& CTopologyLogic::GetServerZoneID() const
{
	return _vLogic.GetServerZoneID();
}

uint CTopologyLogic::FindClientIDRandom( int eSrvType ) const
{
	if (INVALID_ID == eSrvType)return INVALID_ID;

	//随机要发送的服务器ID
	SetUint vSrvID;
	if (!_vLinker.ConnectDataGetServerID(vSrvID,eSrvType))return INVALID_ID;
	if (vSrvID.empty())return INVALID_ID;

	uint nSrvID = ToolFrame::RandValue(vSrvID);
	if (INVALID_ID == nSrvID)return INVALID_ID;

	return _vLinker.ConnectDataFindRandClientID(nSrvID);
}

uint CTopologyLogic::FindClientIDSequence( int eSrvType ) const
{
	if (INVALID_ID == eSrvType)return INVALID_ID;

	uint nSrvID = _vLogic.FindServerIDSequence(eSrvType);
	if (INVALID_ID == nSrvID)return INVALID_ID;

	return _vLinker.ConnectDataFindRandClientID(nSrvID);
}

uint CTopologyLogic::FindClientIDBalance( int eSrvType ) const
{
	if (INVALID_ID == eSrvType)return INVALID_ID;

	uint nSrvID = _vLogic.FindServerIDBalance(eSrvType);
	if (INVALID_ID == nSrvID)return INVALID_ID;

	return _vLinker.ConnectDataFindRandClientID(nSrvID);
}

uint CTopologyLogic::FindClientID( uint uServerID ) const
{
	if (INVALID_ID == uServerID)return INVALID_ID;

	return _vLinker.ConnectDataFindRandClientID(uServerID);
}

uint CTopologyLogic::GetHashCount() const
{
	return _vLogic.GetHashCount();
}

const std::string& CTopologyLogic::GetServerName() const
{
	return _vLogic.GetServerName();
}

const CDate& CTopologyLogic::GetServerOpen() const
{
	return _vLogic.GetServerOpen();
}

const std::string& CTopologyLogic::GetServerTag() const
{
	return _vLogic.GetServerTag();
}

bool CTopologyLogic::SetThread( uint uCount )
{
	return _vLogic.SetThread(uCount);
}

uint CTopologyLogic::GetThread() const
{
	return _vLogic.GetThread();
}

bool CTopologyLogic::SetRunOnceTime( uint64 uTimeRunOnce )
{
	_uTimeRunOnce = uTimeRunOnce;
	return true;
}

bool CTopologyLogic::SetRunOnceTimeMax( uint64 uTime )
{
	_uTimeRunOnceMax = uTime;
	return true;
}

bool CTopologyLogic::SetRunOnceMax( uint uRunOnceMax )
{
	_uRunOnceMax = uRunOnceMax;
	return true;
}

uint CTopologyLogic::GetRunOnceMax() const
{
	return _uRunOnceMax;
}

bool CTopologyLogic::GetUpdateData( XLogicUpdate& xUpdate ) const
{
	return ToolFrame::ConstCast(this)->GetUpdateData(xUpdate);
}

bool CTopologyLogic::GetUpdateData( XLogicUpdate& xUpdate )
{
	int nProcessID			= ToolFrame::GetProcessId();

	uint64 uProcessTotal,uProcessMax=0,uProcessAvg = 0;uint uProcessTimes = 0;
	_vLinker.GetProcessAvg().Clear(&uProcessTotal,&uProcessTimes,&uProcessMax,&uProcessAvg);

	uint64 uTimeSendMax=0,uTimeSendAvg=0;
	MProtocol::Singleton().GetTimeSendAvg(&uTimeSendMax,&uTimeSendAvg);

	uint64 uTimeSendingMax=0,uTimeSendingAvg=0;
	MProtocol::Singleton().GetTimeSendingAvg(&uTimeSendingMax,&uTimeSendingAvg);

	xUpdate.eState			= _eState;
	xUpdate.uTimeReport		= (uint32)ToolFrame::GetNowTime();
	xUpdate.uTimeRunOnce	= (uint16)_uTimeRunOnce;
	xUpdate.uTimeRunOnceMax	= (uint16)_uTimeRunOnceMax;
	xUpdate.uCacheVaild		= (uint32)_uCacheVaild;
	xUpdate.uCacheTotal		= (uint32)_uCacheTotal;
	xUpdate.uProcesserCount = (uint32)_uProcesserCount;
	xUpdate.uQueueSize	= (uint32)_uQueueSize;
	xUpdate.uQueueProcess	= (uint32)_uQueueProcess;
	xUpdate.uCpuUseTime		= ToolFrame::GetCpuUseTime(nProcessID);
	xUpdate.uCpuUsage		= ToolFrame::GetCpuUsage(nProcessID);
	xUpdate.uMemoryUsed		= ToolFrame::GetProcessMemoryUsed(nProcessID);
	xUpdate.uThreads		= ToolFrame::GetThreadAmount();

	xUpdate.nSessionNum		= (uint32)MProtocol::Singleton().GetSessionNum();
	xUpdate.nPacketProcess	= (uint32)MProtocol::Singleton().ClearPackCounter();
	xUpdate.nLogicProcess	= (uint32)MProtocol::Singleton().ClearLogicCounter();
	xUpdate.nNetProcess		= (uint32)MProtocol::Singleton().ClearNetCounter();
	xUpdate.nLogicCmd		= (uint32)MProtocol::Singleton().GetLogicQueueSize();
	xUpdate.nNetCmd			= (uint32)MProtocol::Singleton().GetNetQueueSize();
	xUpdate.uSendBytes		= (uint32)MProtocol::Singleton().ClearSendCounter();
	xUpdate.uRecvBytes		= (uint32)MProtocol::Singleton().ClearRecvCounter();

	xUpdate.uFreeTime		= (uint32)_vLinker.ConnectDataGetMinFreeTime();

	xUpdate.uTimeSave		= (uint32)_uLastSave;
	xUpdate.uTimeCleanUp	= (uint32)_uLastCleanUp;
	xUpdate.uSystemCleanUp	= (uint32)MSystem::Singleton().GetLastCleanTime();
	
	xUpdate.uProcessMax		= (uint32)uProcessMax;
	xUpdate.uProcessAvg		= (uint32)uProcessAvg;

	xUpdate.uTimeSendMax	= (uint32)uTimeSendMax;
	xUpdate.uTimeSendAvg	= (uint32)uTimeSendAvg;

	xUpdate.uTimeSendingMax	= (uint32)uTimeSendingMax;
	xUpdate.uTimeSendingAvg	= (uint32)uTimeSendingAvg;
	return true;
}

NS_TOOL_FRAME_END
