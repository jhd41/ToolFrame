#pragma once

//思路:此类为ToolFrame系统级单件.
//包含 超时队列,事件系统 内存管理 日志管理 等系统性内容。

#include "Macro.h"

#include "TimeOutQueue.h"
#include "EventTrigger.h"
#include "LoopManager.h"
#include "HSystem.h"

#include "IAnyObj.h"
#include "TObjCreator.h"

#include "MLoger.h"
#include "MMemory.h"
#include "MThread.h"
#include "MSystem.h"
#include "MProtocol.h"

//系统级别综合体
//调用任何ToolFrame函数前 必须先初始化 MSystem.内部已考虑析构顺序问题
//AnyObjCreator 用于 外部 系统级的需要释放的申请释放管理器

//想要通过继承的方式初始化MSystem，只需要 继承ISystemInit 就可以，不用考虑析构顺序

//系统事件:
static std::string EVENT_TF_SYSTEM_INITED		= "EVENT_TF_SYSTEM_INITED";		//[系统]初始化
static std::string EVENT_TF_SYSTEM_NET_CHANGE	= "EVENT_TF_SYSTEM_NET_CHANGE";	//[系统]网络切换
static std::string EVENT_TF_SYSTEM_MEMORY_LOW	= "EVENT_TF_SYSTEM_MEMORY_LOW";	//[系统]内存低
static std::string EVENT_TF_SYSTEM_CLEAN_UP		= "EVENT_TF_SYSTEM_CLEAN_UP";	//[系统]内存清理

NS_TOOL_FRAME_BEGIN

class ISystemCall
{
public:
	bool Init();
	bool Destory();
public:
	ISystemCall();
	~ISystemCall();
};

class ISystem
{
public:
	ISystem(){}
	virtual ~ISystem(){}
private:
	ISystemCall _xSystemCall;
};

//////////////////////////////////////////////////////////////////////////
class TOOLFRAME_DLL MSystem
	:public ISystem
	,public HTimeOut
{
	typedef TObjCreator<IAnyObj> AnyObjCreator;
public:
	ST_INTANCE(MSystem);
public:
	bool		SetHandler(HSystem* pHandler);
	bool		SetCleanUpSystemTime(UINT64 uTime);				//设置清理系统时间
	bool		SetCleanUpAllProcess(bool bAllProcess = true);	//设置清理所有进程
	bool		Init();
	bool		RunOnce(uint64 uTime = 300);					//处理一次 返回是否有项超时
	bool		Run();											//运行(堵塞 不返回)
	bool		ReqStop();										//请求停止
public:
	time_t		GetLastCleanTime()const;						//获得最近一次清理时间
	bool		IsReqStop() const;
public:
	CTimeOutQueue&	GetTimeOutQueque();
	CEventTrigger&	GetEventTrigger();
	CLoopManager&	GetLoopMgr();
	AnyObjCreator&	GetAnyObjCreator();

	MThread&		GetThread();
	MLoger&			GetLoger();
	MMemory&		GetMemory();
	MProtocol&		GetProtocol();
private:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode);
private:
	bool		OnSystemCleanUp();
	bool		RemoveTimer();
public:
	MSystem(void);
	virtual ~MSystem(void);
private:
	CFIELD_UINT64(MemoryWarningLess);	//内存不足警戒值
	CFIELD_BOOL(SystemCleanUp);			//需要清理的标记(为了防止递归)
	CFIELD_BOOL(TimeBarCleanUp);		//时间条清理标记(为了防止递归)
private:
	bool			_bInit;
	volatile bool	_bReqStop;

	CTimeOutQueue	_vQueueTime;	//超时队列
	CEventTrigger	_mEventTrigger;	//事件触发器
	CLoopManager	_mLoop;			//循环管理器
	
	CTimeNodePtr	_pTimer;

	HSystem*		_hHandler;
	bool			_bAllProcess;
	time_t			_tLastCleanTime;//最近一次清理时间

	AnyObjCreator	_vObjCreator;	//任意Obj创建器 要求放在最后一行
};

//////////////////////////////////////////////////////////////////////////
class ISystemInitCall
{
public:
	ISystemInitCall() {
		MSystem::Singleton();
	}
	~ISystemInitCall() {

	}
};

class ISystemInit
{
public:
	ISystemInit(){}
	virtual ~ISystemInit(){}
private:
	ISystemInitCall _xInitSystem;
};


NS_TOOL_FRAME_END
