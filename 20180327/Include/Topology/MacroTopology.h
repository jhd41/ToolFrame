#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"
#include "MacroDefineEx.h"
#include "Date.h"
#include "RandomPack.h"

NS_TOOL_FRAME_BEGIN

//拓扑ID
struct XTopologyID
{
	uint16	uGtID;		//网关服务器ID
	uint32	uID;		//网关分配的ID
	uint32	uUserID;	//用户自己的ID

	XTopologyID(){
		uGtID	= INVALID_ID;
		uID		= INVALID_ID;
		uUserID	= INVALID_ID;
	}
	XTopologyID(uint16 uServerID,uint uAssID){
		uGtID	= uServerID;
		uID		= uAssID;
		uUserID	= INVALID_ID;
	}
	//仅仅判断是否临时ID是否一致
	bool operator<(const XTopologyID& other)const{
		if (uGtID != other.uGtID)
			return uGtID < other.uGtID;

		return uID < other.uID;
	}

	bool operator == (const XTopologyID& other)const
	{
		return uGtID == other.uGtID && uID == other.uID;
	}

	bool operator != (const XTopologyID& other)const
	{
		return !(*this == other);
	}

	//完全相等
	bool IsEqual(const XTopologyID& other )const
	{
		if (uGtID != other.uGtID || uID != other.uID)return false;
		if (INVALID_ID != uUserID && uUserID != other.uUserID)return false;
		return true;
	}
};

const static XTopologyID TOPOLOGY_ID_INVAILD;//无效拓扑ID

typedef std::vector<XTopologyID> VectorTopologyID;

SERIALIZE_DECLARE(XTopologyID);


//运作方式
enum ERunType{
	RUN_TYPE_INVAILD=0,
	RUN_TYPE_RANDOM,		//随机
	RUN_TYPE_HASH,			//哈希
	RUN_TYPE_UNIQUE,		//唯一
	RUN_TYPE_BALANCE,		//平衡
	RUN_TYPE_SEQUENCE,		//顺序
	RUN_TYPE_MAX,
};

//客户端类型
enum EClientType{
	CLIENT_TYPE_INVAILD,
	CLIENT_TYPE_PHYSICAL,	//物理服务器
	CLIENT_TYPE_LOGIC,		//逻辑服务器
	CLIENT_TYPE_CONTROL,	//控制端
	CLIENT_TYPE_MAX,
};

//服务器状态
enum EServerConnectState
{
	CONNECT_STATE_INVAILD=0,

	CONNECT_STATE_INIT,			//初始化中
	CONNECT_STATE_NORMAL,		//正常状态
	CONNECT_STATE_STOP_SERVICE,	//停止服务
	CONNECT_STATE_OFFLINE,		//离线

	CONNECT_STATE_MAX,
};

//拓扑逻辑服务器 
struct XConfigLogic{
	uint8		eSrvType;		//服务器类型
	uint8		eRunType;		//运行方式
	uint8		uThread;		//线程数(最大)
	uint16		uRunOnce;		//单次执行时间 毫秒(最大)
	uint32		uTimeInterval;	//汇报时间间隔(毫秒)
	uint8		uHashCount;		//哈希数
	std::string sExePath;		//Exe路径
	std::string sWorkingDir;	//工作目录
	uint32		uRecvSize;		//接收缓冲池大小
	uint32		uSendSize;		//发送缓冲池大小
	uint32		uBlockSize;		//缓冲池单次分配大小
	uint16		uSaveTime;		//保存时间

	uint32		uPublicRecv;	//开放 接收缓冲池大小
	uint32		uPublicSend;	//开放 发送缓冲池大小
	uint32		uPublicBlock;	//开放 缓冲池单次分配大小
	
	std::string sRemark;		//备注

	XConfigLogic(){
		eSrvType		= INVALID_ID;
		eRunType		= INVALID_ID;
		uThread			= 0;
		uRunOnce		= 0;
		uTimeInterval	= 0;
		uHashCount		= 0;
		uRecvSize		= 0;
		uSendSize		= 0;
		uSaveTime		= 0;
		uPublicRecv		= 0;
		uPublicSend		= 0;
		uPublicBlock	= 0;
	}
};

//拓扑逻辑连接
struct XConfigLink{
	uint8 eSrcSrv;//ESrvType	起始连接服务器类型
	uint8 eDesSrv;//ESrvType	目标连接服务器类型
	uint8 uCount;//连接数

	bool operator < (const XConfigLink& t)const{
		if (eSrcSrv == t.eSrcSrv)
			return eDesSrv<t.eDesSrv;

		return eSrcSrv < t.eSrcSrv;
	}
};

//拓扑服务器
struct XConfigServer{
	uint32			uPhysicalID;	//物理服务器ID
	uint32			uServerID;		//服务器ID
	uint8			eSrvType;		//服务器类型
	uint16			uPort;			//端口
	VectorUint16	vPublicPort;	//开放端口
	int16			uPublicConnect;	//开放 连接数
	uint8			uHash;			//哈希值
	std::string		sCommand;		//自定义命令

	XConfigServer(){
		uPhysicalID		= INVALID_ID;
		uServerID		= INVALID_ID;
		eSrvType		= INVALID_ID;
		uPort			= 0;
		uPublicConnect	= 0;
		uHash			= 0;
	}
};

//物理服务器信息
struct XPhysicalUpdate
{
	uint8		eState;				//状态
	uint8		uCpuUsage;			//CPU占用率
	uint64		uMemoryUsed;		//内存使用量
	uint64		uMemoryFree;		//内存剩余量
	uint8		uMemoryUsage;		//内存使用率
	uint32		uSendBytes;			//发送字节数
	uint32		uRecvBytes;			//接收字节数
	uint32		uSystemCleanUp;		//最近清理时间

	XPhysicalUpdate(){
		eState			= 0;
		uCpuUsage		= 0;
		uMemoryUsed		= 0;
		uMemoryFree		= 0;
		uMemoryUsage	= 0;
		uSendBytes		= 0;
		uRecvBytes		= 0;
		uSystemCleanUp	= 0;
	}
};

struct XLogicUpdate
{
	uint8	eState;			//状态
	uint32	uTimeReport;	//汇报时间
	uint16	uTimeRunOnce;	//单次执行时间
	uint16	uTimeRunOnceMax;//单次执行时间 峰值
	uint32	uCacheVaild;	//有效缓存
	uint32	uCacheTotal;	//总缓存
	uint32	uProcesserCount;//处理器数
	uint32	uQueueProcess;	//逻辑队列
	uint64	uCpuUseTime;	//CPU使用时间
	uint8	uCpuUsage;		//CPU使用率
	uint64	uMemoryUsed;	//内存占用
	uint8	uThreads;		//线程数
	uint32	nSessionNum;	//会话数
	uint32	nPacketProcess;	//处理包数
	uint32	nLogicProcess;	//逻辑处理包数
	uint32	nNetProcess;	//网络处理包数
	uint32	nLogicCmd;		//逻辑包数
	uint32	nNetCmd;		//网络包数
	uint32	uSendBytes;		//发送字节数
	uint32	uRecvBytes;		//接收字节数
	uint32	uFreeTime;		//空闲时间(毫秒)
	uint32	uTimeSave;		//最近保存时间
	uint32	uTimeCleanUp;	//最近清理时间
	uint32	uSystemCleanUp;	//系统清理

	uint32	uProcessMax;	//单包处理时间 峰值
	uint32	uProcessAvg;	//单包处理时间 均值

	uint32	uTimeSendMax;	//发送时间 峰值
	uint32	uTimeSendAvg;	//发送时间 均值

	uint32	uTimeSendingMax;//发送中时间 峰值
	uint32	uTimeSendingAvg;//发送中时间 均值

	XLogicUpdate(){
		eState			= 0;	//状态
		uTimeReport		= 0;	//汇报时间
		uTimeRunOnce	= 0;	//单次执行时间
		uTimeRunOnceMax = 0;	//单次执行时间 峰值
		uCacheVaild		= 0;	//有效缓存
		uCacheTotal		= 0;	//总缓存
		uProcesserCount = 0;	//处理器数
		uQueueProcess	= 0;	//逻辑队列
		uCpuUseTime		= 0;	//CPU使用时间
		uCpuUsage		= 0;	//CPU使用率
		uMemoryUsed		= 0;	//内存占用
		uThreads		= 0;	//线程数
		nSessionNum		= 0;	//会话数
		nPacketProcess	= 0;	//处理包数
		nLogicProcess	= 0;	//逻辑处理包数
		nNetProcess		= 0;	//网络处理包数
		nLogicCmd		= 0;	//逻辑包数
		nNetCmd			= 0;	//网络包数
		uSendBytes		= 0;	//发送字节数
		uRecvBytes		= 0;	//接收字节数
		uFreeTime		= 0;	//空闲时间
		uTimeSave		= 0;	//最近保存时间
		uTimeCleanUp	= 0;	//最近清理时间
		uSystemCleanUp	= 0;	//系统清理

		uProcessMax		= 0;	//单包处理时间 峰值
		uProcessAvg		= 0;	//单包处理时间 均值

		uTimeSendMax	= 0;	//发送时间 峰值
		uTimeSendAvg	= 0;	//发送时间 均值

		uTimeSendingMax	= 0;	//发送中时间 峰值
		uTimeSendingAvg	= 0;	//发送中时间 均值
	}
};

//逻辑服务器信息
struct XServerLogic{
	uint32			uServerID;
	uint8			eSrvType;
	uint32			uTimeStartUp;
	uint16			uReconnect;		//重连次数
	XLogicUpdate	xUpdate;

	bool			bUpdated;
	std::string		sDebugString;
	uint			uClientID;		//ClientID

	mutable CMutexReadWrite mutex;

	XServerLogic(){
		uServerID		= INVALID_ID;
		eSrvType		= 0;
		uTimeStartUp	= 0;
		uReconnect		= 0;

		bUpdated		= false;
		uClientID		= INVALID_ID;
	}

	XServerLogic(const XServerLogic& xLogic){
		*this = xLogic;
	}

	bool operator = (const XServerLogic& xLogic){
		uServerID		= xLogic.uServerID;
		eSrvType		= xLogic.eSrvType;
		uTimeStartUp	= xLogic.uTimeStartUp;
		uReconnect		= xLogic.uReconnect;
		xUpdate			= xLogic.xUpdate;
		bUpdated		= xLogic.bUpdated;
		uClientID		= xLogic.uClientID;
		return true;
	}
};

//物理服务器信息
struct XServerPhysical{
	uint32			uPhysicalID;	//物理ID
	std::string		sMac;			//网卡地址
	std::string		sIP;			//IP地址
	VectorString128	vAddress;		//IP
	uint16			uReconnect;		//重连次数
	XPhysicalUpdate xUpdate;

	bool			bUpdated;
	uint			uClientID;		//ClientID

	XServerPhysical(){
		uPhysicalID		= INVALID_ID;
		uReconnect		= 0;

		bUpdated		= false;
		uClientID		= INVALID_ID;
	}
};        

//控制端信息
struct XServerControl 
{
	uint uClientID;			//ClientID
};

struct XServerArg
{
	uint			uServerID;		//ID
	uint			eSrvType;		//类型:网关 注册 等
	uint			uClientID;
	XTopologyID		xSrcID;
	uint			uUserID;
	XServerArg(){
		uServerID = INVALID_ID;
		eSrvType  = INVALID_ID;
		uClientID = INVALID_ID;
		uUserID = INVALID_ID;
	}
};

const static XServerArg SERVER_ARG_INVAILD;

struct XServerHashKey
{
	uint			eSrvType;		//类型:网关 注册 等
	uint			uHash;
	bool operator <(const XServerHashKey& xHash)const{
		if (eSrvType == xHash.eSrvType)return uHash < xHash.uHash;
		return eSrvType < xHash.eSrvType;
	}
};

typedef std::vector<XServerLogic*>				VectorLogicPtr;
typedef std::map<uint32,XServerLogic>			MapLogic;	//<ServerID,>
typedef std::map<uint,VectorLogicPtr>			MapTypeLogic;
typedef std::map<XServerHashKey,uint>			MapLogicHash;
typedef std::map<uint,CRandomPack>				MapTypeRandom;
typedef std::map<uint32,XServerPhysical>		MapPhysical;//<ServerID,>
typedef std::map<uint32,XServerControl>			MapControl;	//<ClientID,>

typedef std::vector<XServerLogic>				VectorLogic;
typedef std::vector<XServerPhysical>			VectorPhysical;
typedef std::vector<XServerControl>				VectorControl;	

typedef std::map<uint32,XConfigLogic>			MapConfigLogic;		//<eSrvType,XConfigLogic>
typedef std::set<XConfigLink>					MapConfigLink;
typedef std::map<uint32,XConfigServer>			MapConfigServer;	//<uServerID,XConfigServer>

typedef std::map<uint32,XPhysicalUpdate>		MapPhysicalUpdate;
typedef std::map<uint32,XLogicUpdate>			MapLogicUpdate;

NS_TOOL_FRAME_END
	