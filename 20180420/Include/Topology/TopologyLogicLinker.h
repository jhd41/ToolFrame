#pragma once

#include "MacroTopology.h"
#include "HTopologyLogic.h"
#include "ConnectMonitor.h"
#include "IDataReceiverStream.h"
#include "Mark.h"
#include "TimeElapseEx.h"
#include "TopologyServerLogic.h"
#include "TopologyServerPhysical.h"
#include "AvgCounter.h"

NS_TOOL_FRAME_BEGIN
class CTopologyLogicLinker
	:public HConnectMonitor
	,public IDataReceiverStream
{
	//��������
	struct XTopologySession
	{
		mutable	CMutexReadWrite	mutex;
		uint	uServerID;
		uint	uClientID;

		uint	eSrvType;	//����������
		XTopologySession(){
			uServerID = INVALID_ID;
			uClientID = INVALID_ID;
		}
	};
	typedef std::map<uint,XTopologySession*>	MapConnectData;

	typedef std::list<CConnectMonitor>		VectorConnector;
	typedef std::map<int,VectorConnector>	MapConnector;
	//��ʼ��
public:
	bool SetManager(CTopologyServerLogic* pManager);
	bool SetManager(CTopologyServerPhysical* pManager);
	bool SetHandler(HTopologyLogic* hHandler);
	bool Init();

	//�̰߳�ȫ
public:
	bool Update();
	bool RemoveServer(uint uServerID);
	uint SendClientID(uint uClientID, StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;//���͵�Ŀ�������,Э�����ݣ�����Դ,����Ŀ�� ���ط��͵�ClientID
public:
	bool CreateServer();
	bool CloseServer();
	
	//������
private:  
	virtual bool OnStateChanged(CConnectMonitor* pConnectMonitor,int eState)override {return true;}
	virtual bool OnConnected(CConnectMonitor* pConnectMonitor)override;
	virtual bool OnDisconnected(CConnectMonitor* pConnectMonitor)override;
	virtual bool OnRecved(CConnectMonitor* pConnectMonitor,IMsgStream& msgStream)override;

	//������
private:
	virtual bool OnConnected(UINT uClientID)override;
	virtual bool OnConnectFailed(UINT uClientID)override;
	virtual bool OnDisconnected(UINT uClientID)override;
	virtual bool OnRecv( uint uClientID,IMsgStream& msgStream)override;

	//�������ݸ���
private:
	virtual bool ConnectDataAdd(uint uClientID,uint uServerID,uint eSrvType);
	virtual bool ConnectDataRemove( uint* uServerID,uint* eSrvType,uint uClientID );
	virtual bool ConnectDataRecv(uint* uServerID,uint* eSrvType,uint uClientID);//����ServerID
public:
	virtual bool	ConnectDataGetServerID(SetUint& vSrvID,int eServerType ) const;
	virtual uint	ConnectDataFindServerID(uint uClientID)const;	
	virtual uint	ConnectDataFindRandClientID(uint uServerID)const;//�������һ��������ServerID������
	virtual uint64	ConnectDataGetMinFreeTime();
	virtual bool	ConnectDataIsConnectedAllSrvType()const;
	virtual bool	CheckIsAllServerConnectd();
	virtual CAvgCounter& GetProcessAvg();
public:
	CTopologyLogicLinker(void);
	virtual ~CTopologyLogicLinker(void);
private:
	HTopologyLogic*			 _hHandler;
	CTopologyServerLogic*	 _pLogic;
	CTopologyServerPhysical* _pPhysical;

	mutable	CMutexReadWrite	_xMutexConnector;
	MapConnector			_vConnector;

	mutable	CMutexReadWrite	_xMutexConnectData;
	MapConnectData			_vConnectData;	//<ClientID,Data*>
	MapUintVectorUint		_vServerData;	//<ServerID,ClientID>
	CTimeElapseEx			_xTimeElapse;	//ʱ������

	CMark					_vMark;

	CAvgCounter				_xProcessAvg;	//ͳ���߼���ִ��Ч��
};

NS_TOOL_FRAME_END
