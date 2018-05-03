#pragma once

#include "MacroTopology.h"
#include "MacroDefineBoost.h"
#include "ConnectMonitor.h"

#include "HTimeOut.h"

#include "TopologyLogicLinker.h"
#include "TopologyServerLogic.h"
#include "TopologyServerPhysical.h"

NS_TOOL_FRAME_BEGIN

class CTopologyLogic
	:public HConnectMonitor
	,public IDataReceiverStream
	,public HTimeOut
{
	//��ʼ��(���̰߳�ȫ)
public:
	bool SetCenterIP(const std::string& sCenterIP);
	bool SetPassword(const std::string& sPassword);
	bool SetServerID(uint uServerID);
	bool SetType(int eType);
	bool SetPort(uint uPort);
	bool SetListener(HTopologyLogic* hHandler);
	bool SetTimeReport(uint uTimeMil);
	bool SetRecvSize(uint uSize);//���ý��ջ�������С
	bool SetSendSize(uint uSize);
	bool SetBlockSize(uint uSize);
	bool SetThread(uint uCount);//�����߳�����
	bool SetPhysicalID(uint uPhysicalID);
	bool SetPublicPort(const VectorUint& vPort);
	bool SetPublicRecv(uint uSize);
	bool SetPublicSend(uint uSize);
	bool SetPublicBlock(uint uSize);
	bool SetPublicConnect(uint uSize);
	bool SetHash(uint uHash);
	bool SetHashCount(uint uHashCount);
	bool SetCommandLine(const std::string& sCommandLine);//ʹ������������
	bool SetRunOnceMax(uint uRunOnceMax);
	bool Init();
	bool CreatePublicServer();
	bool ClosePublicServer();
public:
	int					GetServerID()const;
	int					GetServerType()const;
	const VectorUint&	GetPublicPort()const;		//��ȡ���Ŷ˿�
	uint				GetPublicRecv()const;
	uint				GetPublicConnect()const;	//��ȡ�������������
	uint				GetPublicSend()const;
	uint				GetPublicBlock()const;
	uint				GetHash()const;
	uint				GetHashCount()const;
	uint				GetRecvSize()const;
	uint				GetSendSize()const;
	uint				GetThread()const;
	uint				GetRunOnceMax()const;
	const std::string&	GetServerGroupID()const;	//��������ID
	const std::string&	GetServerZoneID()const;		//����ID
	const std::string&	GetServerName()const;		//��������
	const CDate&		GetServerOpen()const;		//��ȡ����ʱ��
	const std::string&	GetServerTag()const;		//��ȡ���������
	uint				GetPhysicalID()const;
	const std::string&	GetCommand()const;
	bool				IsAuthorized()const;
	bool				IsRegisted()const;
	bool				IsServerCreared()const;//�Ƿ�������ڲ��˿ں�

	//��������(�̰߳�ȫ)
public:
	uint SendClientID(uint uClientID, StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;//����ClientID
	uint SendServerID(uint uServerID, StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;//���͵�Ŀ�������,Э�����ݣ�����Դ,����Ŀ�� ���ط��͵�ClientID
	uint SendClientID(uint uClientID, const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;//����ClientID
	uint SendServerID(uint uServerID, const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;//���͵�Ŀ�������,Э�����ݣ�����Դ,����Ŀ�� ���ط��͵�ClientID

	uint SendRandom	(int eSrvType,									StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;//����ClientID
	uint SendSeq	(int eSrvType,									StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;
	uint SendHash	(int eSrvType,uint uHashKey,					StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;
	uint SendHash	(int eSrvType,const std::string& sHashString,	StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;
	uint SendBalance(int eSrvType,									StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;

	uint SendRandom	(int eSrvType,									const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;//����ClientID
	uint SendSeq	(int eSrvType,									const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;
	uint SendHash	(int eSrvType, uint uHashKey,					const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;
	uint SendHash	(int eSrvType, const std::string& sHashString,	const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;
	uint SendBalance(int eSrvType,									const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;
	
	uint SendSrvType(int eSrvType, StreamBinaryPtr ptr, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;//�Ժ��ʵķ�ʽ���з���
	uint SendSrvType(int eSrvType, const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;//�Ժ��ʵķ�ʽ���з���

	bool BroadCast	(int eSrvType, StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;
	bool BroadCast(int eSrvType, const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;

	uint SendHashKey(int eSrvType,uint uHash, StreamBinaryPtr ptr,const XTopologyID& xSrcID,uint uUserID)const;//����ClientID

	uint FindServerID(uint uClientID)const;									//�ҵ�ServerID
	uint FindClientID(uint uServerID)const;									//�Ҹ�ClientID
	uint FindClientIDRandom(int eSrvType)const;								//�Ҹ���Ч��ClientID
	uint FindClientIDSequence(int eSrvType)const;							//�Ҹ���Ч��ClientID
	uint FindClientIDHash(int eSrvType,uint uHashKey)const;					//�Ҹ���Ч��ClientID
	uint FindClientIDHash(int eSrvType,const std::string& sHashString)const;//�Ҹ���Ч��ClientID
	uint FindClientIDHashKey(int eSrvType,uint uHash)const;					//�Ҹ���Ч��ClientID
	uint FindClientIDBalance(int eSrvType)const;							//�Ҹ���Ч��ClientID

	bool SetStateNormal();
	bool SetStateStop();
	bool SetCacheVaild(size_t uCacheVaild);
	bool SetCacheTotal(size_t uCacheTotal);
	bool SetProcesserCount(size_t uProcesserCount);
	bool SetQueueSize(size_t uQueueSize);								//���г���
	bool SetQueueProcess(size_t uQueueProcess);								//���д�����
	bool SetRunOnceTime(uint64 uTimeRunOnce);
	bool SetRunOnceTimeMax(uint64 uTime);

	bool UpdateState();

	bool IsShutDown()const;

	bool SendPublic(uint uClientID, const char* pBuffer,uint uSize);		//����������
	bool SendPublic(uint uClientID, StreamBinaryPtr ptr);					//����������
private:
	bool SendAuthorization()const;
	bool SendLogicRegist()const;
	bool SendUpdateState()const;
private:
	bool TryCreateServer();
	bool TryCreatePublicServer();
	bool SendToCenter(IMsgStream& msgBase)const;
private:
	bool GetUpdateData(XLogicUpdate& xUpdate)const;
	bool GetUpdateData(XLogicUpdate& xUpdate);
private:
	bool CreateTimerSave();
	bool RemoveTimerSave();

	bool CreateTimerReport();
	bool RemoveTimerReport();

	bool CreateTimerCreateServer();
	bool RemoveTimerCreateServer();

	bool CreateTimerCreatePublicServer();
	bool RemoveTimerCreatePublicServer();
private:
	virtual bool OnConnected(CConnectMonitor* pConnectMonitor)override;
	virtual bool OnDisconnected(CConnectMonitor* pConnectMonitor)override;
	virtual bool OnRecved(CConnectMonitor* pConnectMonitor,IMsgStream& msgStream)override;
private:
	virtual bool OnConnected(UINT uClientID)override;
	virtual bool OnConnectFailed(UINT uClientID)override;
	virtual bool OnDisconnected(UINT uClientID)override;
	virtual uint OnRecv(IDataSession* pSession)override;//���ش����˰��ĸ���
	virtual bool OnRecv(IDataSession* pSession,IMsgStream& msgStream)override;
protected:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode);
public:
	CTopologyLogic(void);
	virtual ~CTopologyLogic(void);
private:
	CConnectMonitor			_monitor;
	std::string				_sPassword;

	bool					_bAuthorized;
	bool					_bServerCreated;
	bool					_bRegisted;

	CTopologyServerLogic	_vLogic;
	CTopologyServerPhysical _vPhysical;
	CTopologyLogicLinker	_vLinker;
	uint					_uTimeReport;			//�㱨ʱ�� ���(����)
	uint					_uTimeSave;				//��������� ���(��)
	uint					_uTimeTryCreateServer;	//���������˿� ���(����)

	int						_eState;

	size_t					_uCacheVaild;//��Ч����
	size_t					_uCacheTotal;//�ܻ���
	size_t					_uProcesserCount;//�첽������
	size_t					_uQueueSize;	//���г���
	size_t					_uQueueProcess;	//���д�����

	time_t					_uLastSave;		//�������ʱ��
	time_t					_uLastCleanUp;	//�������ʱ��
	uint64					_uTimeRunOnce;		//����ִ��ʱ��(���� ���ֵ65��)
	uint64					_uTimeRunOnceMax;

	uint					_uPhysicalID;
	VectorUint				_vPublicPort;
	uint					_uPublicRecv;	//���ջ����
	uint					_uPublicSend;	//���ͻ����
	uint					_uPublicBlock;	//�����ÿ�η����С
	uint					_uPublicConnect;//���������
	uint					_uRunOnceMax;

	std::string				_sCommand;

	HTopologyLogic*			_hHandler;

	bool					_bShutDown;

	CTimeNodePtr			_pTimerReport;			//��ʱ�� �㱨״̬
	CTimeNodePtr			_pTimerSave;			//��ʱ�� �������洢
	CTimeNodePtr			_pTimerCreateServer;	//��ʱ�� �����˿�
	CTimeNodePtr			_pTimerCreatePublicServer;	//��ʱ�� �����˿�
};

NS_TOOL_FRAME_END
