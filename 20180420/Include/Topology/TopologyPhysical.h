#pragma once

#include "MacroTopology.h"
#include "ConnectMonitor.h"
#include "IMsgStream.h"
#include "HTimeOut.h"

NS_TOOL_FRAME_BEGIN

class HTopologyPhysical
{
public:
	virtual bool OnCenterConnected(uint uClientID){return false;}
	virtual bool OnCenterDisconnected(uint uClientID){return false;}
	virtual bool OnCenterAuthorized(uint uClientID,bool bAuthorized){return false;}
	virtual bool OnCreateProcess(uint uServerID,uint eSrvType,const std::string& sExePath,const std::string& sWorkingDir){return false;}//创建进程
	virtual bool OnPurgeMemory() { return false; }
	virtual bool OnSystemReboot() { return false; }
	virtual bool OnSystemSetTime(uint64 uMillTime) { return false; }
public:
	HTopologyPhysical(){}
	virtual ~HTopologyPhysical(){}
};

class CTopologyPhysical
		:public HConnectMonitor
		,public HTimeOut
{
public:
	bool SetCenterAddress(const VectorString& vCenterIP);
	bool SetCenterPassword(const std::string& sPassword);
	bool SetPhysicalID(uint uPhysicalID);
	bool SetAddress(const VectorString& vAddress);
	bool SetRecvSize(uint uSize);
	bool SetSendSize(uint uSize);
	bool SetBlockSize(uint uSize);
	bool SetHandler(HTopologyPhysical* hHandler);
	bool Init();
	bool SetStateNormal();
	uint GetPhysicalID()const;
	const std::string& GetConnectedCenterAddress()const;
	const std::string& GetCenterPassword()const;
	const VectorString& GetCenterAddress()const;
private:
	bool SendToCenter( IMsgStream& msgBase )const;
	bool SendAuthorization()const;
	bool SendPhysicalRegist()const;
	bool SendUpdateState()const;
private:
	bool GetUpdateData(XPhysicalUpdate& xUpdate)const;
private:
	virtual bool OnConnected(CConnectMonitor* pConnectMonitor);
	virtual bool OnDisconnected(CConnectMonitor* pConnectMonitor);
	virtual bool OnRecved(CConnectMonitor* pConnectMonitor,IMsgStream& msgStream);
protected:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode);
public:
	CTopologyPhysical(void);
	virtual ~CTopologyPhysical(void);
	
private:
	uint32				_uPhysicalID;
	CConnectMonitor		_xCenterMonitor;
	std::string			_sCenterPassword;
	uint				_eState;
	VectorString		_vAddress;
	HTopologyPhysical*	_hHandler;

	bool				_bAuthorized;
	bool				_bRegisted;
	time_t				_uTimeReport;	//汇报时间 间隔
	CTimeNodePtr		_pTimerReport;	//计时器 汇报状态
};

NS_TOOL_FRAME_END

