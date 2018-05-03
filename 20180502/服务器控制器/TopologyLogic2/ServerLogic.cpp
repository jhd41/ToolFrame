#include "ServerLogic.h"

#include "ToolFrame.h"
#include "MProtocol.h"

CServerLogic::CServerLogic(void)
{
}

CServerLogic::~CServerLogic(void)
{
}

bool CServerLogic::Init()
{
	if (!IServer::Init())return false;
	_xTopologyLogic.SetServerID(2);
	_xTopologyLogic.SetCenterIP("127.0.0.1:16000");
	_xTopologyLogic.SetPassword("");
	_xTopologyLogic.SetType(2);
	_xTopologyLogic.SetPort(2044);
	_xTopologyLogic.SetListener(this);
	if (!_xTopologyLogic.Init())return false;
	
	return true;
}

bool CServerLogic::RunOnce()
{
	ToolFrame::Sleep(500);//睡的时间长点没事
	ToolFrame::MProtocol::Singleton().ProcessNet(100);
	ToolFrame::MProtocol::Singleton().ProcessLogic(100);
	return true;
}

bool CServerLogic::OnCenterConnected( uint uClientID )
{
	LOG_SYSTEM("OnCenterConnected");
	return false;
}

bool CServerLogic::OnCenterDisconnected( uint uClientID )
{
	LOG_SYSTEM("OnCenterDisconnected");
	return false;
}

bool CServerLogic::OnServerConnected( const ToolFrame::XServerLogic* pServer,uint uClientID )
{
	LOG_SYSTEM("OnServerConnected");
	return false;
}

bool CServerLogic::OnServerDisconnected( const ToolFrame::XServerLogic* pServer,uint uClientID )
{
	LOG_SYSTEM("OnServerDisconnected");
	return false;
}

bool CServerLogic::OnServerRecved( const ToolFrame::XServerLogic* pServer,uint uClientID,const ToolFrame::XTopologyID& uUserID,ToolFrame::IMsgStream& msgBase )
{
	LOG_SYSTEM("OnServerRecved");
	return false;
}

bool CServerLogic::OnServerStateChanged( const ToolFrame::XServerLogic* pServer,uint uClientID )
{
	LOG_SYSTEM("OnServerStateChanged");
	return false;
}

bool CServerLogic::OnServerCreateFaild()
{
	LOG_SYSTEM("OnServerCreateFaild");
	return false;
}

bool CServerLogic::OnServerAllConnected()
{
	LOG_SYSTEM("OnServerAllConnected");
	_xTopologyLogic.SetStateNormal();
	return false;
}

bool CServerLogic::OnServerShutDown( uint uClientID )
{
	LOG_SYSTEM("OnServerShutDown");
	return false;
}

bool CServerLogic::OnServerReport()
{
	LOG_SYSTEM("OnServerReport");
	return false;
}

