#include "ServerCenter.h"

#include "ToolFrame.h"
#include "MProtocol.h"

CServerCenter::CServerCenter(void)
{
	_xTopologyCenter.SetHandler(this);
	SetRunOnceSleep(500);//睡久点
}

CServerCenter::~CServerCenter(void)
{
}

bool CServerCenter::Init()
{
	if (!IServer::Init())return false;

	TiXmlDocument xDoc;
	if (!ToolFrame::Parse(xDoc,ToolFrame::LoadFile("Config.xml")))
		return false;
	
	//读取中央配置
	{
		uint uPort =0;std::string sPassword;
		uint uSendSize=0;uint uRecvSize=0;uint uBlockSize = 0;
		std::string sTitle;

		if (!ToolFrame::GetAttribute(&xDoc,"Config/Center[Port Password]",uPort,sPassword))
			return false;

		ToolFrame::SafeGetAttribute(&xDoc,"Config/Center[Title]",	sTitle,"");

		ToolFrame::SafeGetAttribute(&xDoc,"Config/Center[SendSize]",	uSendSize,	0);
		ToolFrame::SafeGetAttribute(&xDoc,"Config/Center[RecvSize]",	uRecvSize,	0);
		ToolFrame::SafeGetAttribute(&xDoc,"Config/Center[BlockSize]",	uBlockSize, ToolFrame::MProtocol::Singleton().GetBlockSize());

		_xTopologyCenter.SetPort(uPort);
		_xTopologyCenter.SetPassword(sPassword);
		_xTopologyCenter.SetSendSize(uSendSize);
		_xTopologyCenter.SetRecvSize(uRecvSize);
		_xTopologyCenter.SetBlockSize(uBlockSize);

		ToolFrame::SetConsoleTitle(sTitle);
	}
	return _xTopologyCenter.Init();
}

bool CServerCenter::RunOnce()
{
	ToolFrame::IServer::RunOnce();
	ToolFrame::MProtocol::Singleton().ProcessBalance(100);
	return true;
}

bool CServerCenter::OnServerConnected( const ToolFrame::XServerArg& xServerArg )
{
	LOG_SYSTEM("OnServerConnected ServerID:"<<xServerArg.uServerID<<" ClientID:"<<xServerArg.uClientID);
	return true;
}

bool CServerCenter::OnServerDisconnected( const ToolFrame::XServerArg& xServerArg )
{
	LOG_SYSTEM("OnServerDisconnected ServerID:"<<xServerArg.uServerID<<" ClientID:"<<xServerArg.uClientID);
	return true;
}

bool CServerCenter::OnServerStateChanged( const ToolFrame::XServerArg& xServerArg )
{
	return true;
}

bool CServerCenter::OnServerConfigChanged(uint uClientID)
{
	std::stringstream sStream;
	sStream<<"OnServerConfigChanged ClientID:"<<uClientID;

	if (!_xTopologyCenter.GetServerZoneID().empty())
		sStream<<" ServerZoneID:"<<_xTopologyCenter.GetServerZoneID();

	if (!_xTopologyCenter.GetServerGroupID().empty())
		sStream<<" ServerGroupID:"<<_xTopologyCenter.GetServerGroupID();

	LOG_SYSTEM(sStream.str());
	return true;
}

bool CServerCenter::OnServerCreateFaild( uint uPort )
{
	LOG_FATAL("OnServerCreateFaild Port:"<<uPort);
	LOG_FATAL(ToolFrame::GetPortInfoString(uPort));
	return true;
}

bool CServerCenter::OnServerCreateSucceed( uint uPort )
{
	LOG_SYSTEM("OnServerCreateSucceed Port:"<<uPort);
	return true;
}

bool CServerCenter::OnControlRegist()
{
	LOG_SYSTEM("OnControlRegist");
	return true;
}

bool CServerCenter::OnControlLogicSave(uint uSrvID)
{
	LOG_SYSTEM("OnControlLogicSave SrvID:"<< uSrvID);
	return true;
}

bool CServerCenter::OnControlLogicCleanUp(uint uSrvID)
{
	LOG_SYSTEM("OnControlLogicCleanUp SrvID:" << uSrvID);
	return true;
}

bool CServerCenter::OnControlLogicStopService(uint uSrvID)
{
	LOG_SYSTEM("OnControlLogicStopService SrvID:" << uSrvID);
	return true;
}

bool CServerCenter::OnControlStartServer(uint uSrvID, int eSrvType)
{
	LOG_SYSTEM("ControlStartServer: SrvID:" << uSrvID << "eSrvType:" << eSrvType);
	return true;
}

bool CServerCenter::OnControlShutDown(uint uSrvID)
{
	LOG_SYSTEM("OnControlShutDown SrvID:" << uSrvID);
	return true;
}

bool CServerCenter::OnControlDebug(uint uSrvID, const VectorString& vDebug)
{
	LOG_SYSTEM("OnControlDebug SrvID:" << uSrvID<<" Debug:"<< ToolFrame::ToString(vDebug));
	return true;
}

bool CServerCenter::OnControlPurgeMemory(uint uPhysicalID)
{
	LOG_SYSTEM("OnControlPurgeMemory SrvID:" << uPhysicalID);
	return true;
}

bool CServerCenter::OnControlReboot(uint uPhysicalID)
{
	LOG_SYSTEM("OnControlReboot SrvID:" << uPhysicalID);
	return true;
}

bool CServerCenter::OnCenterStartServer(uint uSrvID, int eSrvType)
{
	LOG_SYSTEM("CenterStartServer: SrvID:" << uSrvID << "eSrvType:" << eSrvType);
	return true;
}

bool CServerCenter::OnCenterAuthorization(uint eClientType)
{
	LOG_SYSTEM("OnCenterAuthorization ClientType:" << eClientType);
	return true;
}

bool CServerCenter::OnPhysicalRegist(uint uPhysicalID)
{
	LOG_SYSTEM("OnPhysicalRegist SrvID:" << uPhysicalID);
	return true;
}
