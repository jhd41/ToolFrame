#pragma once
#include "Macro.h"
#include "LockMutex.h"

#include "FunctionQueue.h"

NS_TOOL_FRAME_BEGIN
//顺序操作队列
//设计目的:为了让上层逻辑执行多线程操作的时候能够像单线程一样进行执行，避免死锁
//外部使用时务必以该队列的GetMutex获得的互斥体为保护的临界区的唯一互斥体。
class CSyncOperateQueue
{
public:
	virtual bool SetOperateDelay(bool bOperateDelay);//如果处理失败则延后放置到延迟队列
	virtual bool IsOperateDelay()const;
	virtual bool SetProcessContinue(bool bContinue);//处理完当前操作后 是否继续处理(默认开启)
	virtual bool IsProcessContinue()const;

	virtual bool PauseProcess();			//暂停处理
	virtual bool ResumeProcess();			//恢复处理
	virtual bool IsPauseProcess()const;		//是否暂停

	virtual bool Clear();
	
	//线程安全
public:
	//立刻执行当前操作 如果上锁失败则排队 有可能出现 刚开始队列为空，两个操作同时压入时，两个都进入队列
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

	template<typename TFn>
	bool		 OperateFront(const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 OperateFront(const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 OperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 OperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 OperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 OperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);

	template<typename TFn>
	bool		 OperateFunction(bool bBack,const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 OperateFunction(bool bBack, const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 OperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 OperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 OperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 OperateFunction(bool bBack,const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);

	//单纯插入操作
public:
	template<typename TFn>
	bool		 PushOperate(const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 PushOperate(const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 PushOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 PushOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 PushOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 PushOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);

	template<typename TFn>
	bool		 PushOperateFront(const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 PushOperateFront(const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 PushOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 PushOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 PushOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 PushOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);
public:
	virtual bool ProcessOperate(uint64 uMillTime = 0);		//Mgr调用这个 
	virtual bool ProcessOperate(CTimeOut& timeout);
	virtual bool IsOperateEmpty()const;
	virtual size_t GetOperateSize()const;
	virtual size_t GetOperateDelaySize()const;
	virtual CMutexRecursive&	GetMutex()const;
	//延迟操作队列
public:
	virtual bool PushOperateDelay(IFunctionArgPtr pAnyArg);
	virtual bool SpliceOperateDelay();
	virtual bool IsOperateDelayEmpty()const;
public:
	CSyncOperateQueue();
	virtual ~CSyncOperateQueue();
protected:
	mutable CMutexRecursive	_mutex;			//临界区互斥体(所有要求对临界区操作的函数都要锁上该锁)

	bool					_bPause;
	bool					_bProcessContinue;

	CFunctionQueue			_vOperate;		//当前队列
	CFunctionQueue			_vOperatePause;	//暂停队列

	bool					_bOperateDelay;
	CFunctionQueue			_vOperateDelay; //延迟队列
};

template<typename TFn>
bool CSyncOperateQueue::Operate(const TFn& fn)
{
	return OperateFunction(true, fn);
}

template<typename TFn, typename TArg>
bool CSyncOperateQueue::Operate(const TFn& fn, TArg& tArg)
{
	return OperateFunction(true, fn, tArg);
}

template<typename TFn, typename TArg1, typename TArg2>
bool CSyncOperateQueue::Operate(const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	return OperateFunction(true, fn, tArg1, tArg2);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CSyncOperateQueue::Operate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return OperateFunction(true, fn, tArg1, tArg2, tArg3);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CSyncOperateQueue::Operate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	return OperateFunction(true, fn, tArg1, tArg2, tArg3, tArg4);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CSyncOperateQueue::Operate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	return OperateFunction(true, fn,tArg1, tArg2, tArg3, tArg4, tArg5);
}

template<typename TFn>
bool CSyncOperateQueue::OperateFront(const TFn& fn)
{
	return OperateFunction(false, fn);
}

template<typename TFn, typename TArg>
bool CSyncOperateQueue::OperateFront(const TFn& fn, TArg& tArg)
{
	return OperateFunction(false, fn, tArg);
}

template<typename TFn, typename TArg1, typename TArg2>
bool CSyncOperateQueue::OperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	return OperateFunction(false, fn, tArg1, tArg2);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CSyncOperateQueue::OperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return OperateFunction(false, fn, tArg1, tArg2, tArg3);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CSyncOperateQueue::OperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	return OperateFunction(false, fn, tArg1, tArg2, tArg3, tArg4);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CSyncOperateQueue::OperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	return OperateFunction(false, fn, tArg1, tArg2, tArg3, tArg4, tArg5);
}

template<typename TFn>
bool CSyncOperateQueue::OperateFunction(bool bBack,const TFn& fn)
{
	//执行
	{
		CLockScoped lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn() && IsOperateDelay())
				_vOperateDelay.Push(bBack, fn);
		}
		else {
			_vOperate.Push(bBack, fn);
		}
	}

	//执行之后的
	if (IsProcessContinue())
		ProcessOperate();
	return true;
}

template<typename TFn, typename TArg>
bool CSyncOperateQueue::OperateFunction(bool bBack, const TFn& fn, TArg& tArg)
{
	//执行
	{
		CLockScoped lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg) && IsOperateDelay())
				_vOperateDelay.Push(bBack, fn,tArg);
		}
		else {
			_vOperate.Push(bBack, fn, tArg);
		}
	}

	//执行之后的
	if (IsProcessContinue())
		ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2>
bool CSyncOperateQueue::OperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	//执行
	{
		CLockScoped lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg1, tArg2) && IsOperateDelay())
				_vOperateDelay.Push(bBack, fn, tArg1, tArg2);
		}
		else {
			_vOperate.Push(bBack, fn, tArg1, tArg2);
		}
	}

	//执行之后的
	if (IsProcessContinue())
		ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CSyncOperateQueue::OperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	//执行
	{
		CLockScoped lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg1, tArg2, tArg3) && IsOperateDelay())
				_vOperateDelay.Push(bBack, fn, tArg1, tArg2, tArg3);
		}
		else {
			_vOperate.Push(bBack, fn, tArg1, tArg2, tArg3);
		}
	}

	//执行之后的
	if (IsProcessContinue())
		ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CSyncOperateQueue::OperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	//执行
	{
		CLockScoped lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg1, tArg2, tArg3,tArg4) && IsOperateDelay())
				_vOperateDelay.Push(bBack, fn, tArg1, tArg2, tArg3, tArg4);
		}
		else {
			_vOperate.Push(bBack, fn, tArg1, tArg2, tArg3, tArg4);
		}
	}

	//执行之后的
	if (IsProcessContinue())
		ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CSyncOperateQueue::OperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	//执行
	{
		CLockScoped lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg1, tArg2, tArg3, tArg4, tArg5) && IsOperateDelay())
				_vOperateDelay.Push(bBack, fn, tArg1, tArg2, tArg3, tArg4, tArg5);
		}
		else {
			_vOperate.Push(bBack, fn, tArg1, tArg2, tArg3, tArg4, tArg5);
		}
	}

	//执行之后的
	if (IsProcessContinue())
		ProcessOperate();
	return true;
}

template<typename TFn>
bool CSyncOperateQueue::PushOperate(const TFn& fn)
{
	return _vOperate.PushBack(fn);
}

template<typename TFn, typename TArg>
bool CSyncOperateQueue::PushOperate(const TFn& fn, TArg& tArg)
{
	return _vOperate.PushBack(fn, tArg);
}

template<typename TFn, typename TArg1, typename TArg2>
bool CSyncOperateQueue::PushOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	return _vOperate.PushBack(fn, tArg1, tArg2);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CSyncOperateQueue::PushOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return _vOperate.PushBack(fn, tArg1, tArg2, tArg3);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CSyncOperateQueue::PushOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	return _vOperate.PushBack(fn, tArg1, tArg2, tArg3, tArg4);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CSyncOperateQueue::PushOperate( const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	return _vOperate.PushBack(fn, tArg1, tArg2, tArg3, tArg4, tArg5);
}

template<typename TFn>
bool CSyncOperateQueue::PushOperateFront(const TFn& fn)
{
	return _vOperate.PushFront(fn);
}

template<typename TFn, typename TArg>
bool CSyncOperateQueue::PushOperateFront(const TFn& fn, TArg& tArg)
{
	return _vOperate.PushFront(fn, tArg);
}

template<typename TFn, typename TArg1, typename TArg2>
bool CSyncOperateQueue::PushOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	return _vOperate.PushFront(fn, tArg1, tArg2);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CSyncOperateQueue::PushOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return _vOperate.PushFront(fn, tArg1, tArg2, tArg3);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CSyncOperateQueue::PushOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	return _vOperate.PushFront(fn, tArg1, tArg2, tArg3, tArg4);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CSyncOperateQueue::PushOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	return _vOperate.PushFront(fn, tArg1, tArg2, tArg3, tArg4, tArg5);
}
NS_TOOL_FRAME_END
