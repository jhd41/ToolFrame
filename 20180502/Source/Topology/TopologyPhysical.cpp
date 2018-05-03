#include "TopologyPhysical.h"

#include "TopologyProtocol.h"

#include "MProtocol.h"
#include "MSystem.h"

#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

CTopologyPhysical::CTopologyPhysical(void)
{
	_uTimeReport	= 5;
	_bAuthorized	= false;
	_bRegisted		= false;
	_uPhysicalID	= INVALID_ID;
	_eState			= CONNECT_STATE_INIT;
	_xCenterMonitor.SetHandler(this);

	_hHandler = nullptr;

	MSystem::Singleton().GetTimeOutQueque().RemoveTimer(_pTimerReport);
}

CTopologyPhysical::~CTopologyPhysical(void)
{
}

bool CTopologyPhysical::Init()
{
	if (INVALID_ID == _uPhysicalID)return false;
	
	if (_pTimerReport)return false;

	_pTimerReport = MSystem::Singleton().GetTimeOutQueque().CreateTimerByAfterSec(this,_uTimeReport,true,_uTimeReport);

	return _xCenterMonitor.Start();
}

bool CTopologyPhysical::SetCenterAddress( const VectorString& vCenterIP )
{
	return _xCenterMonitor.SetServerAddress(vCenterIP);
}

bool CTopologyPhysical::SetCenterPassword( const std::string& sPassword )
{
	_sCenterPassword = sPassword;
	return true;
}

bool CTopologyPhysical::SendAuthorization() const
{
	MsgCenterAuthorization msg;
	msg.eClientType = CLIENT_TYPE_PHYSICAL;
	msg.sPassword = _sCenterPassword;
	return SendToCenter(msg);
}

bool CTopologyPhysical::OnConnected( CConnectMonitor* pConnectMonitor )
{
	_hHandler->OnCenterConnected(pConnectMonitor->GetClientID());
	SendAuthorization();
	return true;
}

bool CTopologyPhysical::OnDisconnected( CConnectMonitor* pConnectMonitor )
{
	_bAuthorized = false;
	_bRegisted = false;
	_hHandler->OnCenterDisconnected(pConnectMonitor->GetClientID());
	return true;
}

bool CTopologyPhysical::OnRecved(CConnectMonitor* pConnectMonitor, IMsgStream& msgStream)
{
	switch (msgStream.GetOpCode())
	{
		case MSG_CENTER_AUTHORIZATION_REP:
			{
				MsgCenterAuthorizationRep msg(msgStream);
				if (!msg.Load())return false;

				//如果授权通过
				_bAuthorized = !!msg.bAuthorized;

				_hHandler->OnCenterAuthorized(pConnectMonitor->GetClientID(), _bAuthorized);

				if (!_bAuthorized)
					return true;

				SendPhysicalRegist();
				return true;
			}
			break;
		case MSG_PHYSICAL_REGIST_REP:
			{
				MsgPhysicalRegistRep msg(msgStream);
				if (!msg.Load())return false;

				_bRegisted = !!msg.bSucceed;
				return true;
			}
			break;
		case MSG_CENTER_NTF:
			{
				MsgCenterNtf msg(msgStream);
				if (!msg.Load())return false;

				switch (msg.uType)
				{
					case MsgCenterNtf::TYPE_PHYSICAL_START_SERVER:
						{
							MapStringString vCommandLine;
							ToolFrame::InsertString(vCommandLine, "ServerID", msg.uServerID);
							ToolFrame::InsertString(vCommandLine, "SrvType", (uint)msg.eSrvType);
							ToolFrame::InsertString(vCommandLine, "Thread", (uint)msg.uThread);
							ToolFrame::InsertString(vCommandLine, "RunOnce", (uint)msg.uRunOnce);
							ToolFrame::InsertString(vCommandLine, "Port", msg.uPort);
							ToolFrame::InsertString(vCommandLine, "RecvSize", msg.uRecvSize);
							ToolFrame::InsertString(vCommandLine, "SendSize", msg.uSendSize);
							ToolFrame::InsertString(vCommandLine, "BlockSize", msg.uBlockSize);
							ToolFrame::InsertString(vCommandLine, "SaveTime", msg.uSaveTime);
							ToolFrame::InsertString(vCommandLine, "PhysicalID", msg.uPhysicalID);

							ToolFrame::InsertString(vCommandLine, "PublicPort", msg.vPublicPort);
							ToolFrame::InsertString(vCommandLine, "PublicRecv", msg.uPublicRecv);
							ToolFrame::InsertString(vCommandLine, "PublicSend", msg.uPublicSend);
							ToolFrame::InsertString(vCommandLine, "PublicBlock", msg.uPublicBlock);
							ToolFrame::InsertString(vCommandLine, "PublicConnect", msg.uPublicConnect);

							ToolFrame::InsertString(vCommandLine, "Hash", (uint)msg.uHash);
							ToolFrame::InsertString(vCommandLine, "HashCount", (uint)msg.uHashCount);

							ToolFrame::InsertString(vCommandLine, "SrvTag", msg.sServerTag);

							ToolFrame::InsertString(vCommandLine, "Command", msg.sCommand);

							ToolFrame::InsertString(vCommandLine, "CenterIP", GetCenterAddress());
							ToolFrame::InsertString(vCommandLine, "Password", GetCenterPassword());

							std::string sCommandLine;
							ASSERT_LOG_ERROR(ToolFrame::ToValue(vCommandLine, sCommandLine));
							ToolFrame::CreateProcess(msg.sExePath, msg.sWorkingDir, sCommandLine);

							if (_hHandler)
								_hHandler->OnCreateProcess(msg.uServerID, msg.eSrvType, msg.sExePath, msg.sWorkingDir);
							return true;
						}
						break;
					case MsgCenterNtf::TYPE_PHYSICAL_MEMORY_CLEAR:
						{
							if (_hHandler)
								_hHandler->OnPurgeMemory();

							ToolFrame::PurgeMemory();
							return true;
						}
						break;
					case MsgCenterNtf::TYPE_PHYSICAL_REBOOT:
						{
							if (_hHandler)
								_hHandler->OnSystemReboot();

							ToolFrame::SystemReboot();
							return true;
						}
						break;
					case MsgCenterNtf::TYPE_PHYSICAL_SET_TIME:
						{
							if (_hHandler)
								_hHandler->OnSystemSetTime(msg.uMillTime);

							ToolFrame::SystemSetTime(msg.uMillTime);
							return true;
						}
						break;
				}
			}
			break;
	}
	return false;
}

bool CTopologyPhysical::SendPhysicalRegist() const
{
	MsgPhysicalRegist msg;
	msg.uPhysicalID = _uPhysicalID;
	msg.sMac		= ToolFrame::GetMacAddress();
	msg.sIP			= ToolFrame::GetIPAddress();
	
	ToolFrame::ToValue(_vAddress, msg.vAddress);
	GetUpdateData(msg.xUpdate);

	return SendToCenter(msg);
}

bool CTopologyPhysical::SetPhysicalID( uint uPhysicalID )
{
	_uPhysicalID = uPhysicalID;
	return true;
}

bool CTopologyPhysical::SetRecvSize( uint uSize )
{
	return _xCenterMonitor.SetRecvSize(uSize);
}

bool CTopologyPhysical::SetSendSize(uint uSize)
{
	return _xCenterMonitor.SetSendSize(uSize);
}

bool CTopologyPhysical::SetBlockSize(uint uSize)
{
	return _xCenterMonitor.SetBlockSize(uSize);
}

bool CTopologyPhysical::SetHandler( HTopologyPhysical* hHandler )
{
	_hHandler = hHandler;
	return true;
}

bool CTopologyPhysical::OnTimeOut( const CTimeNodePtr& pTimeNode )
{
	if (_pTimerReport == pTimeNode)
	{
		if (_bRegisted)
			SendUpdateState();//更新
		return true;
	}

	return false;
}

bool CTopologyPhysical::SendUpdateState() const
{
	MsgPhysicalUpdateReq msg;
	msg.uPhysicalID		= _uPhysicalID;
	GetUpdateData(msg.xUpdate);
	return SendToCenter(msg);
}

bool CTopologyPhysical::SendToCenter( IMsgStream& msgBase )const
{
	return _xCenterMonitor.Send(msgBase);
}

bool CTopologyPhysical::SetStateNormal()
{
	_eState = CONNECT_STATE_NORMAL;
	return SendUpdateState();
}

uint CTopologyPhysical::GetPhysicalID() const
{
	return _uPhysicalID;
}

bool CTopologyPhysical::GetUpdateData( XPhysicalUpdate& xUpdate ) const
{
	ToolFrame::ReflashCpuState();

	uint64 uUpLoad =0;uint64 uDownLoad = 0;
	ToolFrame::GetMacFlow(&uUpLoad,&uDownLoad);

	xUpdate.eState			= _eState;
	xUpdate.uCpuUsage		= ToolFrame::GetCpuUsage();
	xUpdate.uMemoryUsed		= ToolFrame::GetProcessMemoryTotal() - ToolFrame::GetProcessMemoryFree();
	xUpdate.uMemoryFree		= ToolFrame::GetProcessMemoryFree();
	xUpdate.uMemoryUsage	= ToolFrame::GetProcessMemoryUsage();
	xUpdate.uSendBytes		= (uint32)uUpLoad;
	xUpdate.uRecvBytes		= (uint32)uDownLoad;
	xUpdate.uSystemCleanUp  = (uint32)MSystem::Singleton().GetLastCleanTime();
	return true;
}

bool CTopologyPhysical::SetAddress( const VectorString& vAddress )
{
	_vAddress = vAddress;
	return true;
}

const std::string& CTopologyPhysical::GetConnectedCenterAddress() const
{
	return _xCenterMonitor.GetConnectedAddress();
}

const std::string& CTopologyPhysical::GetCenterPassword() const
{
	return _sCenterPassword;
}

const VectorString& CTopologyPhysical::GetCenterAddress() const
{
	return _xCenterMonitor.GetServerAddress();
}

NS_TOOL_FRAME_END
