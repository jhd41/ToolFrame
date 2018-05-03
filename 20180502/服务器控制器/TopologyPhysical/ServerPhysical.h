#pragma once
#include "IServer.h"
#include "TopologyPhysical.h"
#include "HLog.h"
class CServerPhysical
	:public ToolFrame::IServer
	,public ToolFrame::HTopologyPhysical
	,public ToolFrame::HLog
{
public:
	virtual bool	Init()override;	//��ʼ��
	virtual	bool	RunOnce()override;//���е���
private:
	virtual bool OnCenterConnected(uint uClientID)override;
	virtual bool OnCenterDisconnected(uint uClientID)override;
	virtual bool OnCenterAuthorized(uint uClientID,bool bAuthorized)override;
	virtual bool OnCreateProcess(uint uServerID,uint eSrvType,const std::string& sExePath,const std::string& sWorkingDir)override;//��������
	virtual bool OnPurgeMemory()override;
	virtual bool OnSystemReboot()override;
private:
	virtual bool OnLogMsg(const std::string& sLogLevel, const std::stringstream& sStreamLog)override;//������־ʱ(����false��ֹд��־)
public:
	CServerPhysical(void);
	virtual ~CServerPhysical(void);
private:
	ToolFrame::CTopologyPhysical	_xTopologyPhysical;
};

