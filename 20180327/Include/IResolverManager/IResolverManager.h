#pragma once

#include "MacroResolver.h"

#include "IResolver.h"
#include "HTimeOut.h"
#include "TimeOutQueue.h"

//结算器管理器
//维持结算器的堆栈结构 默认使用 全局超时队列

NS_TOOL_FRAME_BEGIN

class HResolverManager{
public:
	virtual bool OnResolveTimeOut		(IResolverManager* pMgrResolver, const CTimeNodePtr& pTimeNode);						//结算超时(可能是多线程回调)
	virtual bool OnResolveOver			(IResolverManager* pMgrResolver);						//结算完成
public:
	virtual bool OnResolveErrTimeOut	(IResolverManager* pMgrResolver, IResolver* pAc);	//结算器超时没有被正确处理
	virtual bool OnResolveErrLoop		(IResolverManager* pMgrResolver, IResolver* pAc);	//结算器循环结算
	virtual bool OnResolveErrOutOfSize	(IResolverManager* pMgrResolver, IResolver* pAc);	//结算器数量超过规定大小(防递归)
	virtual bool OnResolveErrEmpty		(IResolverManager* pMgrResolver, IResolver* pAc);	//结算器已空
	virtual bool OnResolveErrProcessTimeOut(IResolverManager* pMgrResolver, IResolver* pAc);//结算器处理超时 可能死循环了
public:
	HResolverManager(){}
	virtual ~HResolverManager(){}
};

class HResolverManagerLog 
	:public HResolverManager
{
public:
	virtual bool OnResolveErrTimeOut(IResolverManager* pMgrResolver, IResolver* pAc)override;		//结算器超时没有被正确处理
	virtual bool OnResolveErrLoop(IResolverManager* pMgrResolver, IResolver* pAc)override;			//结算器循环结算
	virtual bool OnResolveErrOutOfSize(IResolverManager* pMgrResolver, IResolver* pAc)override;		//结算器数量超过规定大小(防递归)
	virtual bool OnResolveErrEmpty(IResolverManager* pMgrResolver, IResolver* pAc)override;			//结算器已空
	virtual bool OnResolveErrProcessTimeOut(IResolverManager* pMgrResolver, IResolver* pAc)override;//结算器处理超时 可能死循环了
public:
	HResolverManagerLog() {}
	virtual ~HResolverManagerLog() {}
};

class IResolverManager
	:public HTimeOut
	,public HResolver
	,public HResolverManagerLog
{
	friend class IResolver;
public:
	bool				SetHandler(HResolverManager* hHandler);
	bool				SetResolverSizeMax(uint uResolverSizeMax);			//设置结算器个数最多个数 默认50
	bool				SetProcessNeverTimeout(bool bNeverTimeOut = true);	//设置结算永不超时(默认:Debug开启 Release关闭)

	template<typename T>
	T*					CreateTopResolver(IResolver* pAcParent);

	virtual bool		Process(uint64 uMillSeconds = 3000);	//处理直到时间不足(0为无限时间)
	virtual bool		ProcessOne(uint64 uMillSeconds = 3000);	//处理一个阶段 返回是否处理(返回Flase代表 不需要处理)
	virtual bool		IsProcessed()const;						//是否已经处理完成

	virtual bool		Close();								//只能调用一次,返回是否真的删除(通常外部不用关心)
	virtual bool		IsEmpty()const;							//结算期已空
	virtual size_t		GetResolverSize()const;					//获取结算器个数
	virtual size_t		GetResolverSizeMax()const;				//获取结算器极限个数

	virtual bool		ResolveTimeOut(const CTimeNodePtr& pTimeNode);	//结算超时(务必清楚你在做什么)
	virtual bool		TimeOut();										//执行超时操作(务必清楚你在做什么)

	virtual CTimeOutQueue*			GetGlobalTimeOutQueue();		//获取全局时间条
	virtual const CTimeOutQueue*	GetGlobalTimeOutQueue()const;	//获取全局时间条
	virtual CTimeOutQueue*			GetLocalTimeOutQueue();			//获取本地时间条
	virtual const CTimeOutQueue*	GetLocalTimeOutQueue()const;	//获取本地时间条

	virtual bool		SetUserPtr(void* pUserPtr);
	template<typename T>
	T*					GetUserPtr()const;
	
	//本地时间
public:
	virtual bool		LocalTimeProcess(uint64 uMillSeconds = 0);//处理时间 返回是否 还需处理(true 需要，false 不需要) (若使用系统时间，则无需处理)
	virtual bool		LocalPause();				//时间暂停
	virtual bool		LocalResume();				//时间继续
	virtual uint64		LocalSetTimeNow(uint64 uTimeNow);//设置当前时间	
	virtual uint64		LocalGetTimeNow()const;

	//全局时间
public:
	//无锁(外部调用时 请上锁)
	virtual IResolver*	FindTopResolver()const;		//获取栈顶的结算器
	virtual IResolver*	FindRootResolver()const;	//获取栈底的结算期
	virtual bool		WaitSeconds(int nSeconds);	//等待N秒 填0也会立刻超时
	virtual bool		WaitSeconds(float fSeconds);//等待N秒 例如 4.5秒
	virtual bool		WaitMillSec(uint64 uMillSec);//等待百万秒
	virtual bool		WaitForever();				//永远等待
	virtual bool		ClearWait();
	virtual bool		IgnoreCheckResolve();		//本次忽略检查(用于自身阶段循环)
	virtual bool		MarkResolveOver();			//标记结算已经完成
	virtual bool		IsResolveOver()const;		//判断结算是否完成
private:
	CFIELD_BOOL(Waiting);
	CFIELD_BOOL(CheckResolve);//检查阶段是否改变
protected:
	virtual bool		RemoveResolver(IResolver* pAction);
	virtual	bool		RemoveTimer();
	template<typename T>
	T*					CreateResolver(IResolver* pAcParent);
	virtual	bool		DestoryResolver(IResolver* pResolver);
	virtual bool		CallBackResolveOver();							//结算结束

	//IResolve调用
protected:
	virtual bool PushResolver(IResolver* pAction,IResolver* pParent,bool bReset = true);
public:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode);	//另一线程入口

	//子类可以覆盖父类的函数
protected:
	virtual bool OnResolverCreate(IResolver* pResolver);
	virtual bool OnResolverDestory(IResolver* pResolver);
	virtual bool OnResolverResetResolve(IResolver* pResolver);

public:
	IResolverManager(void);
	virtual ~IResolverManager(void);
protected:
	VectorResolverEx		_vResolver;
	size_t					_uResolverSizeMax;
	CTimeNodePtr			_pGlobalTimer;
	
	bool					_bResolveOver;
	bool					_bCallBackOver;

	void*					_pUserPtr;

	CTimeOutQueue			_xLocalTimeOutQueue;//独立的超时队列
	HResolverManager*		_hHandler;
	bool					_bProcessNeverTimeout;
};

template<typename T>
T* IResolverManager::GetUserPtr()const
{
	return static_cast<T*>(_pUserPtr);
}

template<typename T>
T* IResolverManager::CreateTopResolver(IResolver* pAcParent)
{
	T* pResolver = CreateResolver<T>(pAcParent);
	if (!pResolver)return nullptr;
	
	PushResolver(pResolver,pAcParent);
	return pResolver;
}

template<typename T>
T* IResolverManager::CreateResolver(IResolver* pAcParent)
{
	T* pResolver = new T();
	if (!pResolver)return nullptr;
	pResolver->SetManagerCreate(true);
	pResolver->SetResolverMgr(this);
	pResolver->SetParent(pAcParent);
	return pResolver;
}

NS_TOOL_FRAME_END
