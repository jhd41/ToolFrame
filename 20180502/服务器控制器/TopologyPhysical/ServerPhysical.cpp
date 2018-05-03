#include "ServerPhysical.h"

#include "ToolFrame.h"
#include "MProtocol.h"
#include "MSystem.h"

CServerPhysical::CServerPhysical(void)
{
	_xTopologyPhysical.SetHandler(this);
	SetRunOnceSleep(500);//睡久点

	ToolFrame::MLoger::Singleton().SetHandler(this);
}

CServerPhysical::~CServerPhysical(void)
{
}

bool CServerPhysical::Init()
{
	if (!IServer::Init())return false;

	TiXmlDocument xDoc;
	if (!ToolFrame::Parse(xDoc,ToolFrame::LoadFile("Config.xml")))return false;

	//读取中心服务器
	std::string sIP;
	ToolFrame::GetAttribute(&xDoc, "Config/Topology[CenterIP]", sIP);

	VectorString vCenterAddress = ToolFrame::SplitAddress(sIP);
	if (vCenterAddress.empty())return false;

	std::string sPassword;int nPhysicalID = 0;uint64 uMomory=0;
	if (!ToolFrame::GetAttribute(&xDoc,"Config/Topology[Password PhysicalID]",sPassword,nPhysicalID))return false;
	_xTopologyPhysical.SetCenterAddress(vCenterAddress);
	_xTopologyPhysical.SetCenterPassword(sPassword);
	_xTopologyPhysical.SetPhysicalID(nPhysicalID);

	//读取地址
	VectorString vAddress;
	ToolFrame::GetAttribute(&xDoc,"Config/Topology[Address]",vAddress);
	ToolFrame::RemoveString(vAddress,"");
	if (vAddress.empty()){
		std::string sLocalIP = ToolFrame::GetIPAddress();
		if (sLocalIP.empty())
			sLocalIP = "127.0.0.1";
		
		vAddress.push_back(sLocalIP);
	}
	_xTopologyPhysical.SetAddress(vAddress);

	std::stringstream sStream;
	sStream<<"PhysicalServerID:"<<_xTopologyPhysical.GetPhysicalID();
	ToolFrame::SetConsoleTitle(sStream.str());

	//读取内存清理上限(单位 MB)
	ToolFrame::SafeGetAttribute(&xDoc,"Config/Topology[ClearMemory]",uMomory,0);
	if (uMomory >0)
	{
		uMomory *= 1000000;
		ToolFrame::MSystem::Singleton().SetMemoryWarningLess(uMomory);
	}
	ToolFrame::MSystem::Singleton().SetCleanUpAllProcess();

	uint uSendSize = 0; uint uRecvSize = 0; uint uBlockSize = 0;
	ToolFrame::SafeGetAttribute(&xDoc, "Config/Center[SendSize]", uSendSize, 0);
	ToolFrame::SafeGetAttribute(&xDoc, "Config/Center[RecvSize]", uRecvSize, 0);
	ToolFrame::SafeGetAttribute(&xDoc, "Config/Center[BlockSize]", uBlockSize, ToolFrame::MProtocol::Singleton().GetBlockSize());
	
	_xTopologyPhysical.SetSendSize(uSendSize);
	_xTopologyPhysical.SetRecvSize(uRecvSize);
	_xTopologyPhysical.SetBlockSize(uBlockSize);

	if (!_xTopologyPhysical.Init())return false;

	_xTopologyPhysical.SetStateNormal();
	return true;
}

bool CServerPhysical::RunOnce()
{
	ToolFrame::IServer::RunOnce();
	ToolFrame::MProtocol::Singleton().ProcessBalance(100);
	return true;
}

bool CServerPhysical::OnCreateProcess( uint uServerID,uint eSrvType,const std::string& sExePath,const std::string& sWorkingDir )
{
	LOG_SYSTEM("OnCreateProcess ServerID:"<<uServerID<<" SrvType:"<<eSrvType);
	LOG_SYSTEM("OnCreateProcess ExePath:"<<sExePath<<" WorkingDir:"<<sWorkingDir);
	return true;
}

bool CServerPhysical::OnPurgeMemory()
{
	LOG_SYSTEM("OnPurgeMemory");
	return true;
}

bool CServerPhysical::OnSystemReboot()
{
	LOG_SYSTEM("OnSystemReboot");
	return true;
}

bool CServerPhysical::OnCenterConnected( uint uClientID )
{
	LOG_SYSTEM("OnCenterConnected "<<_xTopologyPhysical.GetConnectedCenterAddress());
	return true;
}

bool CServerPhysical::OnCenterDisconnected( uint uClientID )
{
	LOG_SYSTEM("OnCenterDisconnected "<<_xTopologyPhysical.GetConnectedCenterAddress());
	return true;
}

bool CServerPhysical::OnCenterAuthorized( uint uClientID,bool bAuthorized )
{
	LOG_SYSTEM("OnConnectedCenter Authorized="<<bAuthorized);
	return true;
}

bool CServerPhysical::OnLogMsg(const std::string& sLogLevel, const std::stringstream& sStreamLog)
{
	if (sLogLevel == "Error")
	{
		int a = 0;
		++a;
	}

	return true;
}
