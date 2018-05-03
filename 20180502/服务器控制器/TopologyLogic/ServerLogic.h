#pragma once
#include "IServer.h"
#include "TopologyLogic.h"
class CServerLogic
	:public ToolFrame::IServer
	,public ToolFrame::HTopologyLogic
{
public:
	virtual bool	Init();	//初始化
	virtual	bool	RunOnce();//运行单次
private:
	virtual bool OnCenterConnected(uint uClientID);
	virtual bool OnCenterDisconnected(uint uClientID);

	virtual bool OnServerConnected(const ToolFrame::XServerLogic* pServer,uint uClientID);
	virtual bool OnServerDisconnected(const ToolFrame::XServerLogic* pServer,uint uClientID);
	virtual bool OnServerRecved(const ToolFrame::XServerLogic* pServer,uint uClientID,const ToolFrame::XTopologyID& uUserID,ToolFrame::IMsgStream& msgBase);
	virtual bool OnServerStateChanged(const ToolFrame::XServerLogic* pServer,uint uClientID);
	virtual bool OnServerCreateFaild();
	virtual bool OnServerAllConnected();
	virtual bool OnServerShutDown(uint uClientID);
	virtual bool OnServerReport();
public:
	CServerLogic(void);
	virtual ~CServerLogic(void);
private:
	ToolFrame::CTopologyLogic	_xTopologyLogic;
};

