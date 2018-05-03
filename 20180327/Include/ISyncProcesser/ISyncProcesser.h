#pragma once
#include "Macro.h"
#include "LockMutex.h"

#include "FunctionQueue.h"

NS_TOOL_FRAME_BEGIN

class ISyncProcesser;
typedef CSharePtr<ISyncProcesser>					ISyncProcesserPtr;
class ISyncProcesserManager;

//异步操作器
//主要用于多线程处理 有两个驱动。PushOperate 和 ProcessOperate
//当当前线程锁成功时 PushOperate 成功，否则就进入队列，外部需要调用 ProcessOperate 把队列中的操作处理掉
class ISyncProcesser
	:public CShareFromThis<ISyncProcesser>
{
public:
	virtual bool SetOperateDelay(bool bOperateDelay);//如果处理失败则延后放置到延迟队列
	virtual bool IsOperateDelay()const;

	//线程安全
public:
	//有可能出现 刚开始队列为空，两个操作同时压入时，两个都进入队列
	template<typename TFn>
	bool		 Operate(const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 Operate(const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 Operate(const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 Operate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 Operate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 Operate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);

	virtual bool ProcessOperate(uint64 uMillTime);		//Mgr调用这个 
	virtual bool ProcessOperate(CTimeOut& timeout);
	virtual bool IsOperateEmpty()const;
	virtual size_t GetOperateSize()const;
	virtual size_t GetOperateDelaySize()const;

	virtual bool PauseProcess();			//暂停处理
	virtual bool ResumeProcess();			//恢复处理
	virtual bool IsPauseProcess()const;		//是否暂停

	virtual bool MarkDeleted();			//标记为删除
	virtual bool IsMarkDeleted()const;
	virtual bool ClearDeleted();

	virtual bool MarkNormal();			//标记为正常
	virtual bool IsNormal()const;
	virtual bool ClearNormal();

	virtual bool MarkVaild();			//标记为有效
	virtual bool IsVaild()const;
	virtual bool ClearVaild();

	DEFINE_TO_PTR(ToProcesser);

	virtual ISyncProcesserPtr		GetSharePtr();

	template<typename T>
	T*								GetUserData()const;

	template<typename T>
	T*								GetMgr()const;

	CMutexRecursive&				GetMutex()const;

	//延迟操作队列
public:
	virtual bool PushOperateDelay(IFunctionArgPtr pAnyArg);
	virtual bool SpliceOperateDelay();
	virtual bool IsOperateDelayEmpty()const;

	//向管理器发起请求(稍后才会被真正执行)
	virtual bool ReqMgrInsertSecond(uint uSecondID);
	virtual bool ReqMgrRemoveSecond(uint uSecondID);
protected:
	virtual bool ReqMgrOperate();
	virtual bool ReqMgrDelete();
public:
	CFIELD_UINT(ProcesserID);	//主键
	CFIELD_UINT(SecondID);		//次键
	CFIELD_PTR(ISyncProcesserManager*,Mgr,p);

public:
	CFIELD_INT(UserInt);
	CFIELD_PTR(void*, UserData, p);
public:
	ISyncProcesser();
	virtual ~ISyncProcesser();
protected:
	mutable CMutexRecursive	_mutex;
	bool					_bNormal;
	bool					_bVaild;
	bool					_bDelete;
	bool					_bPause;

	CFunctionQueue			_vOperate;		//当前队列
	CFunctionQueue			_vOperatePause;	//暂停队列

	bool					_bOperateDelay;
	CFunctionQueue			_vOperateDelay; //延迟队列
};

template<typename T>
T*	ISyncProcesser::GetMgr()const {
	return static_cast<T*>(GetMgr());
}

template<typename T>
T*	ISyncProcesser::GetUserData()const {
	return static_cast<T*>(GetUserData());
}

template<typename TFn>
bool ISyncProcesser::Operate(const TFn& fn)
{
	CLockScoped lock(_mutex, true);
	if (lock.IsLocked() && _vOperate.Empty() && !IsPauseProcess()) {
		if (!fn() && IsOperateDelay())
			_vOperateDelay.PushFunction(fn);
		return true;
	}

	_vOperate.PushFunction(fn);

	ReqMgrOperate();
	return false;
}

template<typename TFn, typename TArg>
bool ISyncProcesser::Operate(const TFn& fn, TArg& tArg)
{
	CLockScoped lock(_mutex, true);
	if (lock.IsLocked() && _vOperate.Empty() && !IsPauseProcess()) {
		if (!fn(tArg) && IsOperateDelay())
			_vOperateDelay.PushFunction(fn, tArg);
		return true;
	}

	_vOperate.PushFunction(fn, tArg);

	ReqMgrOperate();
	return false;
}

template<typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesser::Operate(const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	CLockScoped lock(_mutex, true);
	if (lock.IsLocked() && _vOperate.Empty() && !IsPauseProcess()) {
		if (!fn(tArg1, tArg2) && IsOperateDelay())
			_vOperateDelay.PushFunction(fn,tArg1, tArg2);
		return true;
	}

	_vOperate.PushFunction(fn, tArg1, tArg2);

	ReqMgrOperate();
	return false;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesser::Operate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	CLockScoped lock(_mutex, true);
	if (lock.IsLocked() && _vOperate.Empty() && !IsPauseProcess()) {
		if (!fn(tArg1, tArg2, tArg3) && IsOperateDelay())
			_vOperateDelay.PushFunction(fn, tArg1, tArg2, tArg3);
		return true;
	}

	_vOperate.PushFunction(fn, tArg1, tArg2, tArg3);

	ReqMgrOperate();
	return false;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool ISyncProcesser::Operate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	CLockScoped lock(_mutex, true);
	if (lock.IsLocked() && _vOperate.Empty() && !IsPauseProcess()) {
		if (!fn(tArg1, tArg2, tArg3, tArg4) && IsOperateDelay())
			_vOperateDelay.PushFunction(fn, tArg1, tArg2, tArg3, tArg4);
		return true;
	}

	_vOperate.PushFunction(fn, tArg1, tArg2, tArg3, tArg4);

	ReqMgrOperate();
	return false;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool ISyncProcesser::Operate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	CLockScoped lock(_mutex, true);
	if (lock.IsLocked() && _vOperate.Empty() && !IsPauseProcess()) {
		if (!fn(tArg1, tArg2, tArg3, tArg4, tArg5) && IsOperateDelay())
			_vOperateDelay.PushFunction(fn, tArg1, tArg2, tArg3, tArg4, tArg5);
		return true;
	}

	_vOperate.PushFunction(fn, tArg1, tArg2, tArg3, tArg4, tArg5);

	ReqMgrOperate();
	return false;
}

NS_TOOL_FRAME_END

