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
	//连接数据
	struct XTopologySession
	{
		mutable	CMutexReadWrite	mutex;
		uint	uServerID;
		uint	uClientID;

		uint	eSrvType;	//服务器类型
		XTopologySession(){
			uServerID = INVALID_ID;
			uClientID = INVALID_ID;
		}
	};
	typedef std::map<uint,XTopologySession*>	MapConnectData;

	typedef std::list<CConnectMonitor>		VectorConnector;
	typedef std::map<int,VectorConnector>	MapConnector;
	//初始化
public:
	bool SetManager(CTopologyServerLogic* pManager);
	bool SetManager(CTopologyServerPhysical* pManager);
	bool SetHandler(HTopologyLogic* hHandler);
	bool Init();

	//线程安全
public:
	bool Update();
	bool RemoveServer(uint uServerID);
	uint SendClientID(uint uClientID, StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;//发送的目标服务器,协议内容，发送源,发送目标 返回发送的ClientID
public:
	bool CreateServer();
	bool CloseServer();
	
	//连接器
private:  
	virtual bool OnStateChanged(CConnectMonitor* pConnectMonitor,int eState)override {return true;}
	virtual bool OnConnected(CConnectMonitor* pConnectMonitor)override;
	virtual bool OnDisconnected(CConnectMonitor* pConnectMonitor)override;
	virtual bool OnRecved(CConnectMonitor* pConnectMonitor,IMsgStream& msgStream)override;

	//服务器
private:
	virtual bool OnConnected(UINT uClientID)override;
	virtual bool OnConnectFailed(UINT uClientID)override;
	virtual bool OnDisconnected(UINT uClientID)override;
	virtual bool OnRecv( uint uClientID,IMsgStream& msgStream)override;

	//连接数据更新
private:
	virtual bool ConnectDataAdd(uint uClientID,uint uServerID,uint eSrvType);
	virtual bool ConnectDataRemove( uint* uServerID,uint* eSrvType,uint uClientID );
	virtual bool ConnectDataRecv(uint* uServerID,uint* eSrvType,uint uClientID);//返回ServerID
public:
	virtual bool	ConnectDataGetServerID(SetUint& vSrvID,int eServerType ) const;
	virtual uint	ConnectDataFindServerID(uint uClientID)const;	
	virtual uint	ConnectDataFindRandClientID(uint uServerID)const;//随机返回一个连接至ServerID的连接
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
	CTimeElapseEx			_xTimeElapse;	//时间流逝

	CMark					_vMark;

	CAvgCounter				_xProcessAvg;	//统计逻辑层执行效率
};

NS_TOOL_FRAME_END
