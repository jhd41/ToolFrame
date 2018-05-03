#pragma once
//��������������
//ά�������������
//ά���߼���������
//˼·:
//��������������������ʼ����
//��һ̨��������������� ���������ӷ�������������
//�������������ľ�֪���ж���̨��������ˡ�
//֮��ͨ��UI�������ÿ�������ÿ̨���������Ӷ����߼����ͷ�����
//�������Ļᷢ����Ϣ����������� ���������涨�������߼�������
//�߼����������������ӷ������������ġ�
//���Ƹ��½����еķ������б�,�����͸����з�����
//�����������Լ���ҵ����������໥���ӡ�

#include "MacroTopology.h"
#include "IDataReceiverStream.h"
#include "HTopologyLogic.h"
#include "TopologyServerLogic.h"
#include "TopologyServerPhysical.h"
#include "TopologyServerController.h"
#include "HTimeOut.h"

NS_TOOL_FRAME_BEGIN

class HTopologyCenter{
public:
	virtual bool OnCenterStartServer(uint uSrvID, int eSrvType) { return false; }
	virtual bool OnCenterAuthorization(uint eClientType) { return false; }

	virtual bool OnPhysicalRegist(uint uPhysicalID) { return false; }

	virtual bool OnServerConnected(const XServerArg& xServerArg){return false;}
	virtual bool OnServerStateChanged(const XServerArg& xServerArg){return false;}
	virtual bool OnServerDisconnected(const XServerArg& xServerArg){return false;}
	virtual bool OnServerConfigChanged(uint uClientID){return false;}
	virtual bool OnServerCreateFaild(uint uPort){return false;}
	virtual bool OnServerCreateSucceed(uint uPort){return false;}
	virtual bool OnServerNotifyState(){return false;}

	virtual bool OnControlRegist() { return false; }
	virtual bool OnControlLogicSave(uint uSrvID) { return false; }
	virtual bool OnControlLogicCleanUp(uint uSrvID) { return false; }
	virtual bool OnControlLogicStopService(uint uSrvID) { return false; }
	virtual bool OnControlStartServer(uint uSrvID, int eSrvType) { return false; }
	virtual bool OnControlShutDown(uint uSrvID) { return false; }
	virtual bool OnControlDebug(uint uSrvID,const VectorString&	vDebug) { return false; }
	virtual bool OnControlPurgeMemory(uint uPhysicalID) { return false; }
	virtual bool OnControlReboot(uint uPhysicalID) { return false; }
	
	
public:
	HTopologyCenter(){}
	virtual ~HTopologyCenter(){}
};

class CTopologyCenter
	:public IDataReceiverStream
	,public HTimeOut
{
	struct XClientData 
	{
		uint uClientID;
		uint eClientType;	//EClientType
	};

	typedef std::map<uint,XClientData*> MapClientData;

public:
	bool SetPort(uint uPort);									//���ÿ��Ŷ˿�
	bool SetPassword(const std::string& sPassword);				//������Ȩ����
	bool SetSendSize(uint uSize);
	bool SetRecvSize(uint uSize);
	bool SetBlockSize(uint uSize);
	bool SetTimeTryCreateServer(uint uTime);					//���ó��Դ�����������ʱ����
	bool SetTimeNotifyState(uint uTime);						//���÷������㲥���з�����״̬ʱ����
	bool SetHandler(HTopologyCenter* hHandler);
	bool Init();
public:
	const std::string&			GetServerGroupID()const;
	const std::string&			GetServerZoneID()const;
private:
	bool Send(uint uClientID,IMsgStream& msgBase)const;
	bool Send(uint uClientID, StreamBinaryPtr ptrBuffer)const;

	bool SendAuthorizationRep(uint uClientID,bool bAuthorized)const;
	bool SendAllServer(uint uClientID);
	bool SendLogicUpdate(uint uServerID);
	bool SendLogicUpdateAll();
	bool SendLogicRegistRep(uint uClientID,uint uServerID,bool bSucceed);
	bool SendPhysicalUpdate(uint uPhysicalID);
	bool SendPhysicalRegistRep(uint uClientID,uint uPhysicalID,bool bSucceed);
private:
	bool AddClient(uint uClientID,uint eClientType);
	bool RemoveClient(uint uClientID);
	bool Broadcast(EClientType eClientType, IMsgStream& msgStream);
	bool Broadcast(EClientType eClientType, StreamBinaryPtr pBuffer);
private:
	bool CreateTimerCreateServer();
	bool RemoveTimerCreateServer();
private:
	virtual bool OnConnected(UINT uClientID);
	virtual bool OnConnectFailed(UINT uClientID);
	virtual bool OnDisconnected(UINT uClientID);
	virtual bool OnRecv( UINT uClientID,IMsgStream& msgStream);
private:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode);
public:
	CTopologyCenter(void);
	virtual ~CTopologyCenter(void);
private:
	uint			_uPort;

	std::string		_sPassword;					//��Ȩ����

	MapClientData	_vClientData;				//<ClientID,Data*>

	CTopologyServerLogic		_vLogic;		//���еķ�����
	CTopologyServerPhysical		_vPhysical;
	CTopologyServerController	_vController;

	HTopologyCenter* _hHandler;

	time_t			_uTimeStart;				//����ʱ��

	uint			_uTimeTryCreateServer;		//�����˿�ʱ����
	CTimeNodePtr	_pTimerCreateServer;		//��ʱ�� �����˿�

	uint			_uTimeNotifyState;			//�㲥���з�������״̬
	CTimeNodePtr	_pTimerNotifyState;			//��ʱ�� �����˿�
};

NS_TOOL_FRAME_END
