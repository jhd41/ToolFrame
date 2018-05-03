#pragma once

#include "MacroTopology.h"

#include "ToolFrame.h"
#include "IMsgStream.h"

//拓扑层协议
SERIALIZE_CLASS(XTopologyID,		t.uGtID & t.uID & t.uUserID);

SERIALIZE_CLASS(XPhysicalUpdate,	t.eState & t.uCpuUsage & t.uMemoryUsed & t.uMemoryFree & t.uMemoryUsage & t.uSendBytes & t.uRecvBytes & t.uSystemCleanUp);
SERIALIZE_CLASS(XLogicUpdate,		t.eState & t.uTimeReport & t.uTimeRunOnce & t.uTimeRunOnceMax & t.uRunTimes & t.uRunTimeOutRate & t.uRunElapsed & t.uTimeSave & t.uTimeCleanUp & t.uSystemCleanUp & t.uCacheVaild & t.uCacheTotal & t.uProcesserCount & t.uQueueSize & t.uQueueProcess & t.uCpuUseTime & t.uCpuUsage & t.uMemoryUsed & t.uThreads & t.nSessionNum & t.nPacketProcess & t.nLogicProcess & t.nNetProcess & t.nLogicCmd & t.nNetCmd & t.uSendBytes & t.uRecvBytes & t.uFreeTime & t.uTimeSendMax & t.uTimeSendAvg & t.uTimeSendingMax & t.uTimeSendingAvg & t.uProcessMax & t.uProcessAvg);

SERIALIZE_CLASS(XServerLogic,		t.uServerID & t.eSrvType & t.uProcessID & t.uTimeStartUp & t.uReconnect & t.xUpdate);
SERIALIZE_CLASS(XServerPhysical,	t.uPhysicalID & t.sMac & t.sIP & t.vAddress & t.uReconnect & t.xUpdate);

SERIALIZE_CLASS(XConfigLogic,		t.eSrvType & t.eRunType & t.uThread & t.uRunOnce & t.uTimeInterval & t.uHashCount & t.sExePath & t.sWorkingDir & t.uRecvSize & t.uSendSize & t.uBlockSize & t.uSaveTime & t.uPublicRecv & t.uPublicSend & t.uPublicBlock & t.sRemark);
SERIALIZE_CLASS(XConfigLink,		t.eSrcSrv & t.eDesSrv & t.uCount);
SERIALIZE_CLASS(XConfigServer,		t.uPhysicalID & t.uServerID & t.eSrvType & t.uPort & t.vPublicPort & t.uPublicConnect & t.uHash & t.sCommand);


NS_TOOL_FRAME_BEGIN

enum EServerOpCode
{
	MSG_INVAILD=0,

	MSG_CENTER_AUTHORIZATION,		//请求授权
	MSG_CENTER_AUTHORIZATION_REP,	//请求授权返回
	MSG_CENTER_NTF,					//广播
	MSG_CENTER_REP,

	MSG_PHYSICAL_REGIST,
	MSG_PHYSICAL_REGIST_REP,
	MSG_PHYSICAL_UPDATE_REQ,
	MSG_PHYSICAL_UPDATE_NTF,
	MSG_CONTROL_REGIST,
	MSG_CONTROL_SET_SERVER,		//设置服务器配置

	MSG_CONTROL_LOGIC_SAVE,
	MSG_CONTROL_LOGIC_CLEAN_UP,
	MSG_CONTROL_LOGIC_STOP_SERVICE,
	MSG_CONTROL_LOGIC_SHUTDOWN,
	MSG_CONTROL_LOGIC_DEBUG,
	
	MSG_CONTROL_PHYSICAL_START_SERVER,	//启动服务器
	MSG_CONTROL_PHYSICAL_MEMORY_CLEAR,	//物理服务器:内存清理
	MSG_CONTROL_PHYSICAL_REBOOT,		//物理服务器:重启
	MSG_CONTROL_PHYSICAL_SET_TIME,		//物理服务器:设置时间

	MSG_LOGIC_REGIST,
	MSG_LOGIC_REGIST_REP,
	MSG_LOGIC_UPDATE_REQ,	//更新状态
	MSG_LOGIC_UPDATE_NTF,
	MSG_LOGIC_DEBUG,		
	MSG_LINK_CONNECT_REQ,	//逻辑服务器之间连接协议
	MSG_LINK_CONNECT_REP,
	MSG_LINK_TRAN,		//逻辑服务器之间传输协议

	MSG_MANAGER_AUTHORIZATION,		//请求授权
	MSG_MANAGER_AUTHORIZATION_REP,	//请求授权返回
	MSG_MANAGER_NTF,				//广播
	MSG_MANAGER_REP,

	MSG_MAX,
};

//请求授权
struct MsgCenterAuthorization
	:public IMsgStream
{
	uint8		eClientType;//客户端类型
	String64	sPassword;	//连接密码

	MSG_CONSTRUCT_SERIALIZE(MsgCenterAuthorization,MSG_CENTER_AUTHORIZATION,eClientType & sPassword);
};

//请求授权
struct MsgCenterAuthorizationRep
	:public IMsgStream
{
	uint8	bAuthorized;//是否认证通过
	uint32	uTimeStart;	//服务器启动时间
	MSG_CONSTRUCT_SERIALIZE(MsgCenterAuthorizationRep,MSG_CENTER_AUTHORIZATION_REP,bAuthorized & uTimeStart);
};

//物理服务器 - 注册
struct MsgPhysicalRegist
	:public IMsgStream
{
	//物理服务器信息
	uint32			uPhysicalID;//ID
	String128		sMac;		//网卡地址
	String128		sIP;		//IP地址
	VectorString128	vAddress;
	XPhysicalUpdate xUpdate;
	MSG_CONSTRUCT_SERIALIZE(MsgPhysicalRegist,MSG_PHYSICAL_REGIST,uPhysicalID & sMac & sIP & vAddress & xUpdate);
};

//物理服务器 - 注册
struct MsgPhysicalRegistRep
	:public IMsgStream
{
	uint32			uPhysicalID;		//ID
	uint8			bSucceed;			//成功
	MSG_CONSTRUCT_SERIALIZE(MsgPhysicalRegistRep,MSG_PHYSICAL_REGIST_REP,uPhysicalID & bSucceed);
};

//物理服务器 - 更新
struct MsgPhysicalUpdateReq
	:public IMsgStream
{
	uint32			uPhysicalID;		//ID
	XPhysicalUpdate xUpdate;
	MSG_CONSTRUCT_SERIALIZE(MsgPhysicalUpdateReq,MSG_PHYSICAL_UPDATE_REQ,uPhysicalID & xUpdate);
};

struct MsgPhysicalUpdateNtf
	:public IMsgStream
{
	MapPhysicalUpdate vUpdate;
	MSG_CONSTRUCT_SERIALIZE(MsgPhysicalUpdateNtf,MSG_PHYSICAL_UPDATE_NTF,vUpdate);
};

//中心服务器-广播所有服务器
struct MsgCenterNtf
	:public IMsgStream
{
	enum {
		TYPE_INVAILD,
		TYPE_ALL_SERVER,
		TYPE_ADD_PHYSICAL,
		TYPE_ADD_LOGIC,
		TYPE_REMOVE_PHYSICAL,
		TYPE_REMOVE_LOGIC,
		TYPE_LOGIC_SAVE,			//逻辑服务器:保存服务器
		TYPE_LOGIC_CLEAN_UP,		//逻辑服务器:清理服务器
		TYPE_LOGIC_STOP_SERVICE,	//逻辑服务器:停止服务
		TYPE_LOGIC_SHUT_DOWN,		//逻辑服务器:关闭服务器
		TYPE_LOGIC_DEBUG,			//逻辑服务器:调试服务器
		TYPE_PHYSICAL_START_SERVER,	//物理服务器:启动服务
		TYPE_PHYSICAL_MEMORY_CLEAR,	//物理服务器:内存清理
		TYPE_PHYSICAL_REBOOT,		//物理服务器:重启
		TYPE_PHYSICAL_SET_TIME,		//物理服务器:统一时间
		TYPE_MAX,
	};
	uint8					uType;

	VectorLogic				vLogic;		//逻辑服务器
	VectorPhysical			vPhysical;	//物理服务器

	uint32					uID;

	MapConfigLink			vConfigLink;	//逻辑服务器连接方式
	MapConfigLogic			vConfigLogic;
	MapConfigServer			vConfigServer;	

	String128				sServerGroupID;	//服务器组ID
	String128				sServerZoneID;	//服务器大区ID
	String128				sServerName;	//服务器名称
	CDate					xServerOpen;	//开服时间
	String64				sServerTag;		//服务器标记

	uint32					uServerID;		//服务器ID
	uint8					eSrvType;		//服务器类型
	uint8					uThread;		//线程数
	uint16					uRunOnce;		//单次时间
	uint16					uPort;			//端口
	String1024				sExePath;		//Exe路径
	String1024				sWorkingDir;	//工作目录
	uint32					uRecvSize;		//接收缓冲池大小
	uint32					uSendSize;		//发送缓冲池大小
	uint32					uBlockSize;		//缓冲池单次分配大小
	uint64					uSaveTime;		//保存时间
	uint32					uPhysicalID;	//物理ID
	VectorUint16			vPublicPort;	//开放端口
	uint32					uPublicRecv;	//开放接收缓冲池
	uint32					uPublicSend;	//开放发送缓冲池
	uint32					uPublicBlock;	//缓冲池 单词分配大小
	uint16					uPublicConnect;	//开放连接最大
	uint8					uHash;			//哈希值
	uint8					uHashCount;		//哈希数
	String8192				sCommand;		//命令行

	VectorString			vDebug;			//调试模块

	uint64					uMillTime;
	
	MSG_SERIALIZE_BEGIN
		
	MSG_SERIALIZE_ARG(uType)
	MSG_SERIALIZE_IF(uType,TYPE_ALL_SERVER,				vLogic & vPhysical & vConfigLink & vConfigLogic & vConfigServer & sServerGroupID & sServerZoneID & sServerName & xServerOpen)
	MSG_SERIALIZE_IF(uType,TYPE_ADD_PHYSICAL,			vPhysical)
	MSG_SERIALIZE_IF(uType,TYPE_ADD_LOGIC,				vLogic)
	MSG_SERIALIZE_IF(uType,TYPE_REMOVE_PHYSICAL,		uID)
	MSG_SERIALIZE_IF(uType,TYPE_REMOVE_LOGIC,			uID)
	
	MSG_SERIALIZE_IF(uType,TYPE_LOGIC_DEBUG,			vDebug)

	MSG_SERIALIZE_IF(uType,TYPE_PHYSICAL_START_SERVER,	uServerID & eSrvType & uThread & uRunOnce & uPort & sExePath & sWorkingDir & uRecvSize & uSendSize & uBlockSize & uSaveTime & uPhysicalID & vPublicPort & uPublicRecv & uPublicSend & uPublicBlock & uPublicConnect & uHash & uHashCount & sServerTag & sCommand);
	MSG_SERIALIZE_IF(uType, TYPE_PHYSICAL_SET_TIME,		uMillTime)

	MSG_SERIALIZE_END
	MSG_CONSTRUCT(MsgCenterNtf,MSG_CENTER_NTF);
};

//中心服务器应答
struct MsgCenterRep
	:public IMsgStream
{
	enum{
		OPT_INVAILD=0,
		OPT_MAX
	};
	uint8 uOpt;
	MSG_CONSTRUCT_SERIALIZE(MsgCenterRep,MSG_CENTER_REP, uOpt);
};

//控制端 注册
//控制-添加
struct MsgControlRegist
	:public IMsgStream
{
	MSG_CONSTRUCT(MsgControlRegist,MSG_CONTROL_REGIST);
};

//控制-关闭服务器
struct MsgControlShutDown
	:public IMsgStream
{
	uint32 uServerID;
	MSG_CONSTRUCT_SERIALIZE(MsgControlShutDown,MSG_CONTROL_LOGIC_SHUTDOWN,uServerID);
};

//控制-停止服务
struct MsgControlStopService
	:public IMsgStream
{
	uint32 uServerID;
	MSG_CONSTRUCT_SERIALIZE(MsgControlStopService,MSG_CONTROL_LOGIC_STOP_SERVICE,uServerID);
};

//控制-保存服务器
struct MsgControlSaveServer
	:public IMsgStream
{
	uint32 uServerID;
	MSG_CONSTRUCT_SERIALIZE(MsgControlSaveServer,MSG_CONTROL_LOGIC_SAVE,uServerID);
};

//控制-清理服务器
struct MsgControlCleanUpServer
	:public IMsgStream
{
	uint32 uServerID;
	MSG_CONSTRUCT_SERIALIZE(MsgControlCleanUpServer,MSG_CONTROL_LOGIC_CLEAN_UP,uServerID);
};

//控制-调试服务器
struct MsgControlDebugServer
	:public IMsgStream
{
	uint32			uServerID;
	VectorString	vDebug;
	MSG_CONSTRUCT_SERIALIZE(MsgControlDebugServer, MSG_CONTROL_LOGIC_DEBUG, uServerID & vDebug);
};

//设置服务器配置
struct MsgControlSetServer
	:public IMsgStream
{
	String128			sServerGroupID;
	String128			sServerZoneID;
	String128			sServerName;
	CDate				xServerOpen;
	String64			sServerTag;
	MapConfigLogic		vConfigLogic;
	MapConfigLink		vConfigLink;
	MapConfigServer		vConfigServer;
	MSG_CONSTRUCT_SERIALIZE(MsgControlSetServer,MSG_CONTROL_SET_SERVER,sServerGroupID & sServerZoneID & sServerName & xServerOpen & sServerTag & vConfigLogic & vConfigLink & vConfigServer);
};

//控制启动服务器
struct MsgControlPhysicalStartServer
	:public IMsgStream
{
	uint32 uServerID;
	MSG_CONSTRUCT_SERIALIZE(MsgControlPhysicalStartServer,MSG_CONTROL_PHYSICAL_START_SERVER, uServerID);
};

//内存清理
struct MsgControlPhysicalMemoryClear
	:public IMsgStream
{
	uint32 uPhysicalID;
	MSG_CONSTRUCT_SERIALIZE(MsgControlPhysicalMemoryClear,MSG_CONTROL_PHYSICAL_MEMORY_CLEAR,uPhysicalID);
};

//重启
struct MsgControlPhysicalReboot
	:public IMsgStream
{
	uint32 uPhysicalID;
	MSG_CONSTRUCT_SERIALIZE(MsgControlPhysicalReboot,MSG_CONTROL_PHYSICAL_REBOOT,uPhysicalID);
};

//设置时间
struct MsgControlPhysicalSetTime
	:public IMsgStream
{
	uint32 uPhysicalID;
	uint64 uMillTime;
	MSG_CONSTRUCT_SERIALIZE(MsgControlPhysicalSetTime, MSG_CONTROL_PHYSICAL_SET_TIME, uPhysicalID & uMillTime);
};

//逻辑-注册
struct MsgLogicRegist
	:public IMsgStream
{
	uint32			uServerID;	//服务器ID
	uint8			eSrvType;	//服务器类型
	uint32			uProcessID;	//进程ID
	XLogicUpdate	xUpdate;
	MSG_CONSTRUCT_SERIALIZE(MsgLogicRegist,MSG_LOGIC_REGIST,uServerID & eSrvType & uProcessID & xUpdate);
};

//逻辑-注册
struct MsgLogicRegistRep
	:public IMsgStream
{
	uint32			uServerID;		//ID
	uint8			bSucceed;		//成功
	MSG_CONSTRUCT_SERIALIZE(MsgLogicRegistRep,MSG_LOGIC_REGIST_REP,uServerID & bSucceed);
};

//逻辑-状态
struct MsgLogicUpdateReq
	:public IMsgStream
{
	uint32			uServerID;		//ID
	XLogicUpdate	xUpdate;

	MSG_CONSTRUCT_SERIALIZE(MsgLogicUpdateReq,MSG_LOGIC_UPDATE_REQ,uServerID & xUpdate);
};

//逻辑-状态
struct MsgLogicUpdateNtf
	:public IMsgStream
{
	MapLogicUpdate vUpdate;
	MSG_CONSTRUCT_SERIALIZE(MsgLogicUpdateNtf,MSG_LOGIC_UPDATE_NTF,vUpdate);
};

//逻辑-调试
struct MsgLogicDebug
	:public IMsgStream
{
	uint32			uServerID;		//ID
	StringLong		sString;

	MSG_CONSTRUCT_SERIALIZE(MsgLogicDebug, MSG_LOGIC_DEBUG, uServerID & sString);
};

//链接-连接
struct MsgLinkConnectReq
	:public IMsgStream
{
	uint32	uServerID;
	uint8	eSrvType;
	MSG_CONSTRUCT_SERIALIZE(MsgLinkConnectReq,MSG_LINK_CONNECT_REQ,uServerID & eSrvType);
};

//链接-连接
struct MsgLinkConnectRep
	:public IMsgStream
{
	uint32 uServerID;
	MSG_CONSTRUCT_SERIALIZE(MsgLinkConnectRep,MSG_LINK_CONNECT_REP,uServerID );
};

//链接-传输
struct MsgLinkTran
	:public IMsgStream
{
	XTopologyID		xSrcID;		//发送源ID
	StreamBinaryPtr	ptr;		//协议内容
	uint32			uUserID;	//目标ID
	MSG_CONSTRUCT_SERIALIZE(MsgLinkTran,MSG_LINK_TRAN,xSrcID & ptr & uUserID);
};

//请求授权
struct MsgManagerAuthorization
	:public IMsgStream
{
	uint8		eClientType;//客户端类型
	String128	sPassword;	//连接密码

	MSG_CONSTRUCT_SERIALIZE(MsgManagerAuthorization,MSG_MANAGER_AUTHORIZATION,eClientType & sPassword);
};

//请求授权
struct MsgManagerAuthorizationRep
	:public IMsgStream
{
	uint8	bAuthorized;//是否认证通过
	uint32	uTimeStart;	//服务器启动时间
	MSG_CONSTRUCT_SERIALIZE(MsgManagerAuthorizationRep,MSG_MANAGER_AUTHORIZATION_REP,bAuthorized & uTimeStart);
};

//管理服务器-广播所有服务器
struct MsgManagerNtf
	:public IMsgStream
{
	enum {
		TYPE_INVAILD,
		TYPE_ALL_SERVER,
		TYPE_ADD_PHYSICAL,
		TYPE_REMOVE_PHYSICAL,

		TYPE_ADD_LOGIC,
		TYPE_REMOVE_LOGIC,
		TYPE_LOGIC_SAVE,			//逻辑服务器:保存服务器
		TYPE_LOGIC_CLEAN_UP,		//逻辑服务器:清理服务器
		TYPE_LOGIC_STOP_SERVICE,	//逻辑服务器:停止服务
		TYPE_LOGIC_SHUT_DOWN,		//逻辑服务器:关闭服务器
		TYPE_PHYSICAL_START_SERVER,	//物理服务器:启动服务
		TYPE_PHYSICAL_MEMORY_CLEAR,	//物理服务器:内存清理
		TYPE_PHYSICAL_REBOOT,		//物理服务器:重启
		TYPE_MAX,
	};
	uint8			uType;

	MapLogic		vLogic;		//逻辑服务器
	MapPhysical		vPhysical;	//物理服务器

	uint32			uID;

	MapConfigLink	vConfigLink;	//逻辑服务器连接方式
	MapConfigLogic	vConfigLogic;

	String128		sServerGroupID;	//服务器组ID
	String128		sServerZoneID;	//服务器大区ID

	uint32			uServerID;		//服务器ID
	uint8			eSrvType;		//服务器类型
	uint16			uPort;			//端口
	String1024		sExePath;		//Exe路径
	String1024		sWorkingDir;	//工作目录
	uint32			uRecvSize;		//接收缓冲池大小
	uint32			uSendSize;		//发送缓冲池大小
	uint64			uSaveTime;		//保存时间
	uint32			uPhysicalID;	//物理ID
	VectorUint16	vPublicPort;	//开放端口
	uint32			uPublicRecv;	//开放接收缓冲池
	uint32			uPublicSend;	//开放发送缓冲池
	uint8			uHash;			//哈希值
	uint8			uHashCount;		//哈希数
	String8192		sCommand;		//命令行
	String512		sCenterIP;		//中心服务器地址
	String128		sPassword;		//中心服务器密码

	MSG_SERIALIZE_BEGIN
	MSG_SERIALIZE_ARG(uType)
	MSG_SERIALIZE_IF(uType,TYPE_ALL_SERVER,				vLogic & vPhysical & vConfigLink & vConfigLogic & sServerGroupID & sServerZoneID)
	MSG_SERIALIZE_IF(uType,TYPE_ADD_PHYSICAL,			vPhysical)
	MSG_SERIALIZE_IF(uType,TYPE_ADD_LOGIC,				vLogic)
	MSG_SERIALIZE_IF(uType,TYPE_REMOVE_PHYSICAL,		uID)
	MSG_SERIALIZE_IF(uType,TYPE_REMOVE_LOGIC,			uID)
	MSG_SERIALIZE_IF(uType,TYPE_PHYSICAL_START_SERVER,	uServerID & eSrvType & uPort & sExePath & sWorkingDir & uRecvSize & uSendSize & uSaveTime & uPhysicalID & vPublicPort & uPublicRecv & uPublicSend & uHash & uHashCount & sCommand & sCenterIP & sPassword);
	MSG_SERIALIZE_IF(uType,TYPE_PHYSICAL_MEMORY_CLEAR,	uPhysicalID)
	MSG_SERIALIZE_IF(uType,TYPE_PHYSICAL_REBOOT,		uPhysicalID)
	MSG_SERIALIZE_END
		
	MSG_CONSTRUCT(MsgManagerNtf,MSG_CENTER_NTF);
};

NS_TOOL_FRAME_END
