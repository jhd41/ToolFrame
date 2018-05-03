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
	//初始化(非线程安全)
public:
	bool SetCenterIP(const std::string& sCenterIP);
	bool SetPassword(const std::string& sPassword);
	bool SetServerID(uint uServerID);
	bool SetType(int eType);
	bool SetPort(uint uPort);
	bool SetListener(HTopologyLogic* hHandler);
	bool SetTimeReport(uint uTimeMil);
	bool SetRecvSize(uint uSize);//设置接收缓冲区大小
	bool SetSendSize(uint uSize);
	bool SetBlockSize(uint uSize);
	bool SetThread(uint uCount);//设置线程数量
	bool SetPhysicalID(uint uPhysicalID);
	bool SetPublicPort(const VectorUint& vPort);
	bool SetPublicRecv(uint uSize);
	bool SetPublicSend(uint uSize);
	bool SetPublicBlock(uint uSize);
	bool SetPublicConnect(uint uSize);
	bool SetHash(uint uHash);
	bool SetHashCount(uint uHashCount);
	bool SetCommandLine(const std::string& sCommandLine);//使用命令行设置
	bool SetRunOnceMax(uint uRunOnceMax);
	bool Init();
	bool CreatePublicServer();
	bool ClosePublicServer();
public:
	int					GetServerID()const;
	int					GetServerType()const;
	const VectorUint&	GetPublicPort()const;		//获取开放端口
	uint				GetPublicRecv()const;
	uint				GetPublicConnect()const;	//获取开放最大连接数
	uint				GetPublicSend()const;
	uint				GetPublicBlock()const;
	uint				GetHash()const;
	uint				GetHashCount()const;
	uint				GetRecvSize()const;
	uint				GetSendSize()const;
	uint				GetThread()const;
	uint				GetRunOnceMax()const;
	const std::string&	GetServerGroupID()const;	//服务器组ID
	const std::string&	GetServerZoneID()const;		//大区ID
	const std::string&	GetServerName()const;		//开服名称
	const CDate&		GetServerOpen()const;		//获取开服时间
	const std::string&	GetServerTag()const;		//获取服务器标记
	uint				GetPhysicalID()const;
	const std::string&	GetCommand()const;
	bool				IsAuthorized()const;
	bool				IsRegisted()const;
	bool				IsServerCreared()const;//是否监听了内部端口号

	//基本函数(线程安全)
public:
	uint SendClientID(uint uClientID, StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;//返回ClientID
	uint SendServerID(uint uServerID, StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;//发送的目标服务器,协议内容，发送源,发送目标 返回发送的ClientID
	uint SendClientID(uint uClientID, const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;//返回ClientID
	uint SendServerID(uint uServerID, const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;//发送的目标服务器,协议内容，发送源,发送目标 返回发送的ClientID

	uint SendRandom	(int eSrvType,									StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;//返回ClientID
	uint SendSeq	(int eSrvType,									StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;
	uint SendHash	(int eSrvType,uint uHashKey,					StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;
	uint SendHash	(int eSrvType,const std::string& sHashString,	StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;
	uint SendBalance(int eSrvType,									StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;

	uint SendRandom	(int eSrvType,									const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;//返回ClientID
	uint SendSeq	(int eSrvType,									const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;
	uint SendHash	(int eSrvType, uint uHashKey,					const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;
	uint SendHash	(int eSrvType, const std::string& sHashString,	const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;
	uint SendBalance(int eSrvType,									const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;
	
	uint SendSrvType(int eSrvType, StreamBinaryPtr ptr, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;//以合适的方式进行发送
	uint SendSrvType(int eSrvType, const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;//以合适的方式进行发送

	bool BroadCast	(int eSrvType, StreamBinaryPtr ptr,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID = INVALID_ID)const;
	bool BroadCast(int eSrvType, const IMsgStream& msg, const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, uint uUserID = INVALID_ID)const;

	uint SendHashKey(int eSrvType,uint uHash, StreamBinaryPtr ptr,const XTopologyID& xSrcID,uint uUserID)const;//返回ClientID

	uint FindServerID(uint uClientID)const;									//找到ServerID
	uint FindClientID(uint uServerID)const;									//找个ClientID
	uint FindClientIDRandom(int eSrvType)const;								//找个有效的ClientID
	uint FindClientIDSequence(int eSrvType)const;							//找个有效的ClientID
	uint FindClientIDHash(int eSrvType,uint uHashKey)const;					//找个有效的ClientID
	uint FindClientIDHash(int eSrvType,const std::string& sHashString)const;//找个有效的ClientID
	uint FindClientIDHashKey(int eSrvType,uint uHash)const;					//找个有效的ClientID
	uint FindClientIDBalance(int eSrvType)const;							//找个有效的ClientID

	bool SetStateNormal();
	bool SetStateStop();
	bool SetCacheVaild(size_t uCacheVaild);
	bool SetCacheTotal(size_t uCacheTotal);
	bool SetProcesserCount(size_t uProcesserCount);
	bool SetQueueSize(size_t uQueueSize);								//队列长度
	bool SetQueueProcess(size_t uQueueProcess);								//队列处理量
	bool SetRunOnceTime(uint64 uTimeRunOnce);
	bool SetRunOnceTimeMax(uint64 uTime);

	bool UpdateState();

	bool IsShutDown()const;

	bool SendPublic(uint uClientID, const char* pBuffer,uint uSize);		//发送至公网
	bool SendPublic(uint uClientID, StreamBinaryPtr ptr);					//发送至公网
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
	virtual uint OnRecv(IDataSession* pSession)override;//返回处理了包的个数
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
	uint					_uTimeReport;			//汇报时间 间隔(毫秒)
	uint					_uTimeSave;				//保存服务器 间隔(秒)
	uint					_uTimeTryCreateServer;	//创建监听端口 间隔(毫秒)

	int						_eState;

	size_t					_uCacheVaild;//有效缓存
	size_t					_uCacheTotal;//总缓存
	size_t					_uProcesserCount;//异步处理数
	size_t					_uQueueSize;	//队列长度
	size_t					_uQueueProcess;	//队列处理量

	time_t					_uLastSave;		//最近保存时间
	time_t					_uLastCleanUp;	//最近清理时间
	uint64					_uTimeRunOnce;		//单次执行时间(毫秒 最大值65秒)
	uint64					_uTimeRunOnceMax;

	uint					_uPhysicalID;
	VectorUint				_vPublicPort;
	uint					_uPublicRecv;	//接收缓冲池
	uint					_uPublicSend;	//发送缓冲池
	uint					_uPublicBlock;	//缓冲池每次分配大小
	uint					_uPublicConnect;//最大连接数
	uint					_uRunOnceMax;

	std::string				_sCommand;

	HTopologyLogic*			_hHandler;

	bool					_bShutDown;

	CTimeNodePtr			_pTimerReport;			//计时器 汇报状态
	CTimeNodePtr			_pTimerSave;			//计时器 服务器存储
	CTimeNodePtr			_pTimerCreateServer;	//计时器 监听端口
	CTimeNodePtr			_pTimerCreatePublicServer;	//计时器 监听端口
};

NS_TOOL_FRAME_END
