#pragma once
#include "IServer.h"
#include "TopologyCenter.h"
class CServerCenter
	:public ToolFrame::IServer
	,public ToolFrame::HTopologyCenter
{
public:
	virtual bool	Init()override;	//初始化
	virtual	bool	RunOnce()override;//运行单次
private:
	virtual bool OnCenterStartServer(uint uSrvID, int eSrvType)override;
	virtual bool OnCenterAuthorization(uint eClientType)override;
	
	virtual bool OnPhysicalRegist(uint uPhysicalID) override;
	
	virtual bool OnServerConnected(const ToolFrame::XServerArg& xServerArg)override;
	virtual bool OnServerStateChanged(const ToolFrame::XServerArg& xServerArg)override;
	virtual bool OnServerDisconnected(const ToolFrame::XServerArg& xServerArg)override;
	virtual bool OnServerConfigChanged(uint uClientID)override;
	virtual bool OnServerCreateFaild(uint uPort)override;
	virtual bool OnServerCreateSucceed(uint uPort)override;

	virtual bool OnControlRegist()override;
	virtual bool OnControlLogicSave(uint uSrvID)override;
	virtual bool OnControlLogicCleanUp(uint uSrvID)override;
	virtual bool OnControlLogicStopService(uint uSrvID)override;
	virtual bool OnControlStartServer(uint uSrvID, int eSrvType)override;
	virtual bool OnControlShutDown(uint uSrvID)override;
	virtual bool OnControlDebug(uint uSrvID, const VectorString& vDebug)override;
	virtual bool OnControlPurgeMemory(uint uPhysicalID)override;
	virtual bool OnControlReboot(uint uPhysicalID)override;
public:
	CServerCenter(void);
	virtual ~CServerCenter(void);
private:
	ToolFrame::CTopologyCenter	_xTopologyCenter;
};

