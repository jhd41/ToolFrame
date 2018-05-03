#pragma once

#include "MacroTopology.h"
#include "ConnectMonitor.h"
#include "IMsgStream.h"
#include "TopologyServerLogic.h"
#include "TopologyServerPhysical.h"

NS_TOOL_FRAME_BEGIN

class HTopologyControl
{
public:
	virtual bool OnAuthorizationRep(bool bAuthorized,time_t uTimeStart){return false;}
	virtual bool OnAllServer(const VectorPhysical& vPhysical,const VectorLogic& vLogic){return false;}
	virtual bool OnAddPhysical(const VectorPhysical& vPhysical){return false;}
	virtual bool OnAddLogic(const VectorLogic& vLogic){return false;}
	virtual bool OnRemovePhysical(int nID){return false;}
	virtual bool OnRemoveLogic(int nID){return false;}
	virtual bool OnShutDown(){return false;}
	virtual bool OnLogicStateChanged(const MapLogicUpdate& vUpdate,uint uClientID){return false;}
	virtual bool OnPhysicalStateChanged(const MapPhysicalUpdate& vUpdate,uint uClientID){return false;}
	virtual bool OnConnectStateChanged(int eState){return false;}//CConnectMonitor::EState
	virtual bool OnLogicDebug(uint uServerID,const std::string& sDebugString) { return false; }
public:
	HTopologyControl(void){}
	virtual ~HTopologyControl(void){}
};

class CTopologyControl
	:public HConnectMonitor
{
public:
	bool SetHandler(HTopologyControl* pListener);
	bool SetCenterIP(const std::string& sCenterIP);
	bool SetPassword(const std::string& sPassword);
	bool SetServerGroupID(const std::string& sServerGroupID);
	bool SetServerZoneID(const std::string& sServerZoneID);
	bool SetServerName(const std::string& sServerName);
	bool SetServerOpen(const CDate& xServerOpen);
	bool SetServerTag(const std::string& sTag);
	bool SetRecvSize(uint uSize);//���ý��ջ�������С
	bool SetSendSize(uint uSize);
	bool SetBlockSize(uint uSize);

	bool SetConfigLogic(const MapConfigLogic& vConfigLogic);
	bool SetConfigLink(const MapConfigLink& vConfigLink);
	bool SetConfigServer(const MapConfigServer& vConfigServer);

	bool Init();			//����

	bool SendServerConfig()const;		//���÷���������

	bool SendLogicSaveServer(uint32 uServerID)const;
	bool SendLogicCleanUpServer( uint32 uServerID )const;
	bool SendLogicStopService(uint32 uServerID)const;
	bool SendLogicShutDown(uint32 uServerID)const;
	bool SendLogicDebug(uint32 uServerID,const VectorString& vDebug)const;

	bool SendPhysicalStartServer(uint32 uServerID)const;
	bool SendPhysicalMemoryClear(uint32 uPhysicalID)const;
	bool SendPhysicalReboot(uint32 uPhysicalID)const;
	bool SendPhysicalSetTime(uint32 uPhysicalID) const;

	bool IsAuthorized()const;					//�Ƿ���֤ͨ��
public:
	const MapConfigLogic&		GetConfigLogic()const;
	const MapConfigLink&		GetConfigLink()const;
	const MapConfigServer&		GetConfigServer()const;

	const CTopologyServerLogic&		GetServersLogic()const;
	const CTopologyServerPhysical&	GetServersPhysical()const;

	const std::string& 			TranSrvType( int eSrvType ) const;
	const XConfigServer*		FindConfigServer(uint uServerID)const;
	const XConfigLogic*			FindConfigSrvType(int eSrvType)const;
	bool						IsLogicOnline(uint32 uServerID)const;	//�Ƿ��߼�����������
	bool						FindOnlineServerList(VectorUint& vServerID)const;//��ȡ���߷������б�
	const VectorString&			GetCenterAddress()const;			//��ȡ���ķ�������ַ�б�
	const std::string&			GetConnectedCenterAddress()const;	//��ȡ�����ӵķ�������ַ
	const std::string&			GetServerGroupID()const;
	const std::string&			GetServerZoneID()const;
	const std::string&			GetServerTag()const;

	std::string					GetDebugString()const;	//��ȡ������Ϣ
private:
	bool Send(IMsgStream& msgBase)const;
	bool SendAuthorization( uint uClientID ) const;
	bool SendControlRegist( uint uClientID ) const;
private:
	virtual bool OnConnected(CConnectMonitor* pConnectMonitor)override;
	virtual bool OnDisconnected(CConnectMonitor* pConnectMonitor)override;
	virtual bool OnRecved(CConnectMonitor* pConnectMonitor,IMsgStream& msgStream)override;
	virtual bool OnStateChanged(CConnectMonitor* pConnectMonitor,int eState)override;
public:
	CTopologyControl(void);
	virtual ~CTopologyControl(void);
private:
	CConnectMonitor		_monitor;
	std::string			_sPassword;

	CTopologyServerLogic	_vLogic;
	CTopologyServerPhysical _vPhysical;

	HTopologyControl*	_hHandler;
	bool				_bAuthorized;

	MapConfigLogic		_vConfigLogic;
	MapConfigLink		_vConfigLink;
	MapConfigServer		_vConfigServer;

	std::string			_sServerGroupID;
	std::string			_sServerZoneID;
	std::string			_sServerName;
	CDate				_xServerOpen;
	std::string			_sServerTag;
};

NS_TOOL_FRAME_END
