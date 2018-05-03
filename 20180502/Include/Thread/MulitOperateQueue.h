#pragma once
#include "Macro.h"
#include "LockMutex.h"

#include "FunctionQueue.h"
#include "CalCounter.h"

NS_TOOL_FRAME_BEGIN
//读写操作队列
//设计目的:让被保护的临界区 能够 软性的被 读写访问，避免死锁。
//外部使用时务必以该队列的GetMutex获得的互斥体为保护的临界区的唯一互斥体。
class CMulitOperateQueue
{
	enum EOperatorType
	{
		OPERATOR_INVAILD,

		OPERATOR_READ,
		OPERATOR_WRITE,

		OPERATOR_MAX,
	};
public:
	virtual bool SetOperateDelay(bool bOperateDelay);//如果处理失败则延后放置到延迟队列
	virtual bool IsOperateDelay()const;

	virtual bool PauseProcess();			//暂停处理
	virtual bool ResumeProcess();			//恢复处理
	virtual bool IsPauseProcess()const;		//是否暂停

	virtual bool Clear();
	
	virtual size_t ClearProcessCount();	//清除处理量 返回已经处理的量

	//线程安全
public:
	//立刻执行当前操作 如果上锁失败则排队 有可能出现 刚开始队列为空，两个操作同时压入时，两个都进入队列
	template<typename TFn>
	bool		 ReadOperate(const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 ReadOperate(const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 ReadOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 ReadOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 ReadOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 ReadOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>
	bool		 ReadOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5, TArg6& tArg6);

	template<typename TFn>
	bool		 ReadOperateFront(const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 ReadOperateFront(const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 ReadOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 ReadOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 ReadOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 ReadOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);

	template<typename TFn>
	bool		 ReadOperateFunction(bool bBack,const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 ReadOperateFunction(bool bBack, const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 ReadOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 ReadOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 ReadOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 ReadOperateFunction(bool bBack,const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>
	bool		 ReadOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5, TArg6& tArg6);

	//写操作
	template<typename TFn>
	bool		 WriteOperate(const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 WriteOperate(const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 WriteOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 WriteOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 WriteOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 WriteOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);

	template<typename TFn>
	bool		 WriteOperateFront(const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 WriteOperateFront(const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 WriteOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 WriteOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 WriteOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 WriteOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);

	template<typename TFn>
	bool		 WriteOperateFunction(bool bBack, const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 WriteOperateFunction(bool bBack, const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 WriteOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 WriteOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 WriteOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 WriteOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);

	//单纯插入操作
public:
	template<typename TFn>
	bool		 PushOperateRead(const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 PushOperateRead(const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 PushOperateRead(const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 PushOperateRead(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 PushOperateRead(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 PushOperateRead(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);

	template<typename TFn>
	bool		 PushOperateReadFront(const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 PushOperateReadFront(const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 PushOperateReadFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 PushOperateReadFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 PushOperateReadFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 PushOperateReadFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);

	template<typename TFn>
	bool		 PushOperateWrite(const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 PushOperateWrite(const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 PushOperateWrite(const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 PushOperateWrite(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 PushOperateWrite(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 PushOperateWrite(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);

	template<typename TFn>
	bool		 PushOperateWriteFront(const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 PushOperateWriteFront(const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 PushOperateWriteFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 PushOperateWriteFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 PushOperateWriteFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 PushOperateWriteFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);

	template<typename TFn>
	bool		 PushOperateFunction(EOperatorType eOperatorType, bool bBack,const TFn& fn);
	template<typename TFn, typename TArg>
	bool		 PushOperateFunction(EOperatorType eOperatorType, bool bBack, const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool		 PushOperateFunction(EOperatorType eOperatorType, bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool		 PushOperateFunction(EOperatorType eOperatorType, bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool		 PushOperateFunction(EOperatorType eOperatorType, bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool		 PushOperateFunction(EOperatorType eOperatorType, bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);
public:
	virtual bool ProcessOperate(uint64 uMillTime = 0);		//Mgr调用这个 
	virtual bool ProcessOperate(CTimeOut& timeout);
	virtual bool IsOperateEmpty()const;
	virtual size_t GetOperateSize()const;
	virtual size_t GetOperateDelaySize()const;
	virtual CMutexReadWrite&	GetMutex()const;
	//延迟操作队列
public:
	virtual bool PushOperateDelay(IFunctionArgPtr pAnyArg);
	virtual bool SpliceOperateDelay();
	virtual bool IsOperateDelayEmpty()const;
public:
	CMulitOperateQueue();
	virtual ~CMulitOperateQueue();
protected:
	mutable CMutexReadWrite	_mutex;			//临界区互斥体(所有要求对临界区操作的函数都要锁上该锁)
	mutable CMutexReadWrite	_mutexQueue;	//当前队列的互斥体

	CCalCounterSize			_uProcessCount;	//处理量

	bool					_bPause;

	CFunctionQueue			_vOperate;		//当前队列
	CFunctionQueue			_vOperatePause;	//暂停队列

	bool					_bOperateDelay;
	CFunctionQueue			_vOperateDelay; //延迟队列
};

template<typename TFn>
bool CMulitOperateQueue::ReadOperate(const TFn& fn)
{
	return ReadOperateFunction(true, fn);
}

template<typename TFn, typename TArg>
bool CMulitOperateQueue::ReadOperate(const TFn& fn, TArg& tArg)
{
	return ReadOperateFunction(true, fn, tArg);
}

template<typename TFn, typename TArg1, typename TArg2>
bool CMulitOperateQueue::ReadOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	return ReadOperateFunction(true, fn, tArg1, tArg2);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CMulitOperateQueue::ReadOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return ReadOperateFunction(true, fn, tArg1, tArg2, tArg3);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CMulitOperateQueue::ReadOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	return ReadOperateFunction(true, fn, tArg1, tArg2, tArg3, tArg4);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CMulitOperateQueue::ReadOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	return ReadOperateFunction(true, fn,tArg1, tArg2, tArg3, tArg4, tArg5);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>
bool CMulitOperateQueue::ReadOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5, TArg6& tArg6)
{
	return ReadOperateFunction(true, fn, tArg1, tArg2, tArg3, tArg4, tArg5, tArg6);
}

template<typename TFn>
bool CMulitOperateQueue::ReadOperateFront(const TFn& fn)
{
	return ReadOperateFunction(false, fn);
}

template<typename TFn, typename TArg>
bool CMulitOperateQueue::ReadOperateFront(const TFn& fn, TArg& tArg)
{
	return ReadOperateFunction(false, fn, tArg);
}

template<typename TFn, typename TArg1, typename TArg2>
bool CMulitOperateQueue::ReadOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	return ReadOperateFunction(false, fn, tArg1, tArg2);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CMulitOperateQueue::ReadOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return ReadOperateFunction(false, fn, tArg1, tArg2, tArg3);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CMulitOperateQueue::ReadOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	return ReadOperateFunction(false, fn, tArg1, tArg2, tArg3, tArg4);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CMulitOperateQueue::ReadOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	return ReadOperateFunction(false, fn, tArg1, tArg2, tArg3, tArg4, tArg5);
}

template<typename TFn>
bool CMulitOperateQueue::ReadOperateFunction(bool bBack,const TFn& fn)
{
	//执行
	{
		CLockRead lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn() && IsOperateDelay()) {
				IFunctionArgPtr ptr(CreateFunctionArg(fn));
				ptr->SetUserInt(OPERATOR_READ);
				_vOperateDelay.Push(bBack, ptr);
			}
		}
		else {
			IFunctionArgPtr ptr(CreateFunctionArg(fn));
			ptr->SetUserInt(OPERATOR_READ);
			_vOperate.Push(bBack, ptr);
		}
	}

	//执行之后的
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg>
bool CMulitOperateQueue::ReadOperateFunction(bool bBack, const TFn& fn, TArg& tArg)
{
	//执行
	{
		CLockRead lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg) && IsOperateDelay()) {
				IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg));
				ptr->SetUserInt(OPERATOR_READ);
				_vOperateDelay.Push(bBack, ptr);
			}
		}
		else {
			IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg));
			ptr->SetUserInt(OPERATOR_READ);
			_vOperate.Push(bBack,ptr);
		}
	}

	//执行之后的
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2>
bool CMulitOperateQueue::ReadOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	//执行
	{
		CLockRead lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg1, tArg2) && IsOperateDelay()) {
				IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2));
				ptr->SetUserInt(OPERATOR_READ);
				_vOperateDelay.Push(bBack, ptr);
			}
		}
		else {
			IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2));
			ptr->SetUserInt(OPERATOR_READ);
			_vOperate.Push(bBack, ptr);
		}
	}

	//执行之后的
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CMulitOperateQueue::ReadOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	//执行
	{
		CLockRead lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg1, tArg2, tArg3) && IsOperateDelay()) {
				IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3));
				ptr->SetUserInt(OPERATOR_READ);
				_vOperateDelay.Push(bBack, ptr);
			}
		}
		else {
			IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3));
			ptr->SetUserInt(OPERATOR_READ);
			_vOperate.Push(bBack, ptr);
		}
	}

	//执行之后的
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CMulitOperateQueue::ReadOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	//执行
	{
		CLockRead lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg1, tArg2, tArg3, tArg4) && IsOperateDelay()) {
				IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3, tArg4));
				ptr->SetUserInt(OPERATOR_READ);
				_vOperateDelay.Push(bBack, ptr);
			}
		}
		else {
			IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3, tArg4));
			ptr->SetUserInt(OPERATOR_READ);
			_vOperate.Push(bBack, ptr);
		}
	}

	//执行之后的
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CMulitOperateQueue::ReadOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	//执行
	{
		CLockRead lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg1, tArg2, tArg3, tArg4, tArg5) && IsOperateDelay()) {
				IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3, tArg4, tArg5));
				ptr->SetUserInt(OPERATOR_READ);
				_vOperateDelay.Push(bBack, ptr);
			}
		}
		else {
			IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3, tArg4, tArg5));
			ptr->SetUserInt(OPERATOR_READ);
			_vOperate.Push(bBack, ptr);
		}
	}

	//执行之后的
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>
bool CMulitOperateQueue::ReadOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5, TArg6& tArg6)
{
	//执行
	{
		CLockRead lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg1, tArg2, tArg3, tArg4, tArg5, tArg6) && IsOperateDelay()) {
				IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3, tArg4, tArg5, tArg6));
				ptr->SetUserInt(OPERATOR_READ);
				_vOperateDelay.Push(bBack, ptr);
			}
		}
		else {
			IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3, tArg4, tArg5, tArg6));
			ptr->SetUserInt(OPERATOR_READ);
			_vOperate.Push(bBack, ptr);
		}
	}

	//执行之后的
	ProcessOperate();
	return true;
}

//////////////////////////////////////////////////////////////////////////
template<typename TFn>
bool CMulitOperateQueue::WriteOperate(const TFn& fn)
{
	return WriteOperateFunction(true, fn);
}

template<typename TFn, typename TArg>
bool CMulitOperateQueue::WriteOperate(const TFn& fn, TArg& tArg)
{
	return WriteOperateFunction(true, fn, tArg);
}

template<typename TFn, typename TArg1, typename TArg2>
bool CMulitOperateQueue::WriteOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	return WriteOperateFunction(true, fn, tArg1, tArg2);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CMulitOperateQueue::WriteOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return WriteOperateFunction(true, fn, tArg1, tArg2, tArg3);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CMulitOperateQueue::WriteOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	return WriteOperateFunction(true, fn, tArg1, tArg2, tArg3, tArg4);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CMulitOperateQueue::WriteOperate(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	return WriteOperateFunction(true, fn, tArg1, tArg2, tArg3, tArg4, tArg5);
}

template<typename TFn>
bool CMulitOperateQueue::WriteOperateFront(const TFn& fn)
{
	return WriteOperateFunction(false, fn);
}

template<typename TFn, typename TArg>
bool CMulitOperateQueue::WriteOperateFront(const TFn& fn, TArg& tArg)
{
	return WriteOperateFunction(false, fn, tArg);
}

template<typename TFn, typename TArg1, typename TArg2>
bool CMulitOperateQueue::WriteOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	return WriteOperateFunction(false, fn, tArg1, tArg2);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CMulitOperateQueue::WriteOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return WriteOperateFunction(false, fn, tArg1, tArg2, tArg3);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CMulitOperateQueue::WriteOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	return WriteOperateFunction(false, fn, tArg1, tArg2, tArg3, tArg4);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CMulitOperateQueue::WriteOperateFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	return WriteOperateFunction(false, fn, tArg1, tArg2, tArg3, tArg4, tArg5);
}

template<typename TFn>
bool CMulitOperateQueue::WriteOperateFunction(bool bBack, const TFn& fn)
{
	//执行
	{
		CLockWrite lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn() && IsOperateDelay()) {
				IFunctionArgPtr ptr(CreateFunctionArg(fn));
				ptr->SetUserInt(OPERATOR_WRITE);
				_vOperateDelay.Push(bBack, ptr);
			}
		}
		else {
			IFunctionArgPtr ptr(CreateFunctionArg(fn));
			ptr->SetUserInt(OPERATOR_WRITE);
			_vOperate.Push(bBack, ptr);
		}
	}

	//执行之后的
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg>
bool CMulitOperateQueue::WriteOperateFunction(bool bBack, const TFn& fn, TArg& tArg)
{
	//执行
	{
		CLockWrite lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg) && IsOperateDelay()) {
				IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg));
				ptr->SetUserInt(OPERATOR_WRITE);
				_vOperateDelay.Push(bBack, ptr);
			}
		}
		else {
			IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg));
			ptr->SetUserInt(OPERATOR_WRITE);
			_vOperate.Push(bBack, ptr);
		}
	}

	//执行之后的
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2>
bool CMulitOperateQueue::WriteOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	//执行
	{
		CLockWrite lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg1, tArg2) && IsOperateDelay()) {
				IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2));
				ptr->SetUserInt(OPERATOR_WRITE);
				_vOperateDelay.Push(bBack, ptr);
			}
		}
		else {
			IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2));
			ptr->SetUserInt(OPERATOR_WRITE);
			_vOperate.Push(bBack, ptr);
		}
	}

	//执行之后的
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CMulitOperateQueue::WriteOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	//执行
	{
		CLockWrite lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg1, tArg2, tArg3) && IsOperateDelay()) {
				IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3));
				ptr->SetUserInt(OPERATOR_WRITE);
				_vOperateDelay.Push(bBack, ptr);
			}
		}
		else {
			IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3));
			ptr->SetUserInt(OPERATOR_WRITE);
			_vOperate.Push(bBack, ptr);
		}
	}

	//执行之后的
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CMulitOperateQueue::WriteOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	//执行
	{
		CLockWrite lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg1, tArg2, tArg3, tArg4) && IsOperateDelay()) {
				IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3, tArg4));
				ptr->SetUserInt(OPERATOR_WRITE);
				_vOperateDelay.Push(bBack, ptr);
			}
		}
		else {
			IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3, tArg4));
			ptr->SetUserInt(OPERATOR_WRITE);
			_vOperate.Push(bBack, ptr);
		}
	}

	//执行之后的
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CMulitOperateQueue::WriteOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	//执行
	{
		CLockWrite lock(_mutex, true);
		if (lock.IsLocked() && !IsPauseProcess() && _vOperate.Empty())
		{
			if (!fn(tArg1, tArg2, tArg3, tArg4, tArg5) && IsOperateDelay()) {
				IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3, tArg4, tArg5));
				ptr->SetUserInt(OPERATOR_WRITE);
				_vOperateDelay.Push(bBack, ptr);
			}
		}
		else {
			IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3, tArg4, tArg5));
			ptr->SetUserInt(OPERATOR_WRITE);
			_vOperate.Push(bBack, ptr);
		}
	}

	//执行之后的
	ProcessOperate();
	return true;
}


//////////////////////////////////////////////////////////////////////////

template<typename TFn>
bool CMulitOperateQueue::PushOperateRead(const TFn& fn)
{
	return PushOperateFunction(OPERATOR_READ, true, fn);
}

template<typename TFn, typename TArg>
bool CMulitOperateQueue::PushOperateRead(const TFn& fn, TArg& tArg)
{
	return PushOperateFunction(OPERATOR_READ, true, fn, tArg);
}

template<typename TFn, typename TArg1, typename TArg2>
bool CMulitOperateQueue::PushOperateRead(const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	return PushOperateFunction(OPERATOR_READ, true, fn, tArg1, tArg2);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CMulitOperateQueue::PushOperateRead(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return PushOperateFunction(OPERATOR_READ, true, fn, tArg1, tArg2, tArg3);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CMulitOperateQueue::PushOperateRead(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	return PushOperateFunction(OPERATOR_READ, true, fn, tArg1, tArg2, tArg3, tArg4);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CMulitOperateQueue::PushOperateRead(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	return PushOperateFunction(OPERATOR_READ, false, fn, tArg1, tArg2, tArg3, tArg4, tArg5);
}

template<typename TFn>
bool CMulitOperateQueue::PushOperateReadFront(const TFn& fn)
{
	return PushOperateFunction(OPERATOR_READ, false, fn);
}

template<typename TFn, typename TArg>
bool CMulitOperateQueue::PushOperateReadFront(const TFn& fn, TArg& tArg)
{
	return PushOperateFunction(OPERATOR_READ, false, fn, tArg);
}

template<typename TFn, typename TArg1, typename TArg2>
bool CMulitOperateQueue::PushOperateReadFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	return PushOperateFunction(OPERATOR_READ, false, fn, tArg1, tArg2);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CMulitOperateQueue::PushOperateReadFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return PushOperateFunction(OPERATOR_READ, false, fn, tArg1, tArg2, tArg3);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CMulitOperateQueue::PushOperateReadFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	return PushOperateFunction(OPERATOR_READ, false, fn, tArg1, tArg2, tArg3, tArg4);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CMulitOperateQueue::PushOperateReadFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	return PushOperateFunction(OPERATOR_READ,false,fn, tArg1, tArg2, tArg3, tArg4, tArg5);
}
//////////////////////////////////////////////////////////////////////////
template<typename TFn>
bool CMulitOperateQueue::PushOperateWrite(const TFn& fn)
{
	return PushOperateFunction(OPERATOR_WRITE, true, fn);
}

template<typename TFn, typename TArg>
bool CMulitOperateQueue::PushOperateWrite(const TFn& fn, TArg& tArg)
{
	return PushOperateFunction(OPERATOR_WRITE, true, fn, tArg);
}

template<typename TFn, typename TArg1, typename TArg2>
bool CMulitOperateQueue::PushOperateWrite(const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	return PushOperateFunction(OPERATOR_WRITE, true, fn, tArg1, tArg2);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CMulitOperateQueue::PushOperateWrite(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return PushOperateFunction(OPERATOR_WRITE, true, fn, tArg1, tArg2, tArg3);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CMulitOperateQueue::PushOperateWrite(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	return PushOperateFunction(OPERATOR_WRITE, true, fn, tArg1, tArg2, tArg3, tArg4);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CMulitOperateQueue::PushOperateWrite(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	return PushOperateFunction(OPERATOR_WRITE, false, fn, tArg1, tArg2, tArg3, tArg4, tArg5);
}

template<typename TFn>
bool CMulitOperateQueue::PushOperateWriteFront(const TFn& fn)
{
	return PushOperateFunction(OPERATOR_WRITE, false, fn);
}

template<typename TFn, typename TArg>
bool CMulitOperateQueue::PushOperateWriteFront(const TFn& fn, TArg& tArg)
{
	return PushOperateFunction(OPERATOR_WRITE, false, fn, tArg);
}

template<typename TFn, typename TArg1, typename TArg2>
bool CMulitOperateQueue::PushOperateWriteFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	return PushOperateFunction(OPERATOR_WRITE, false, fn, tArg1, tArg2);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CMulitOperateQueue::PushOperateWriteFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return PushOperateFunction(OPERATOR_WRITE, false, fn, tArg1, tArg2, tArg3);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CMulitOperateQueue::PushOperateWriteFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	return PushOperateFunction(OPERATOR_WRITE, false, fn, tArg1, tArg2, tArg3, tArg4);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CMulitOperateQueue::PushOperateWriteFront(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	return PushOperateFunction(OPERATOR_WRITE, false, fn, tArg1, tArg2, tArg3, tArg4, tArg5);
}

//////////////////////////////////////////////////////////////////////////
template<typename TFn>
bool CMulitOperateQueue::PushOperateFunction(EOperatorType eOperatorType, bool bBack, const TFn& fn) {
	IFunctionArgPtr ptr(CreateFunctionArg(fn));
	ptr->SetUserInt(eOperatorType);
	return _vOperate.Push(bBack, ptr);
}

template<typename TFn, typename TArg>
bool CMulitOperateQueue::PushOperateFunction(EOperatorType eOperatorType, bool bBack, const TFn& fn, TArg& tArg) {
	IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg));
	ptr->SetUserInt(eOperatorType);
	return _vOperate.Push(bBack, ptr);
}

template<typename TFn, typename TArg1, typename TArg2>
bool CMulitOperateQueue::PushOperateFunction(EOperatorType eOperatorType, bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2) {
	IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2));
	ptr->SetUserInt(eOperatorType);
	return _vOperate.Push(bBack, ptr);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CMulitOperateQueue::PushOperateFunction(EOperatorType eOperatorType, bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3) {
	IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3));
	ptr->SetUserInt(eOperatorType);
	return _vOperate.Push(bBack, ptr);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CMulitOperateQueue::PushOperateFunction(EOperatorType eOperatorType, bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4) {
	IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3, tArg4));
	ptr->SetUserInt(eOperatorType);
	return _vOperate.Push(bBack, ptr);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CMulitOperateQueue::PushOperateFunction(EOperatorType eOperatorType, bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5) {
	IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3, tArg4, tArg5));
	ptr->SetUserInt(eOperatorType);
	return _vOperate.Push(bBack, ptr);
}


NS_TOOL_FRAME_END
