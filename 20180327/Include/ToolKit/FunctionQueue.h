#pragma once

#include "Macro.h"
#include "IFunctionArg.h"
#include "TimeOut.h"

NS_TOOL_FRAME_BEGIN
//函数队列
class CFunctionQueue
{
public:
	template<typename TFn>
	bool				PushFunction(const TFn& fn);
	template<typename TFn, typename TArg>
	bool				PushFunction(const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool				PushFunction(const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool				PushFunction(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool				PushFunction(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool				PushFunction(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);
public:
	virtual bool		ProcessOne();							//处理一个操作 如果为空 返回false
	virtual bool		Process(CTimeOut& timeout);				//处理规定时间内的操作，如果处理不完 返回false
	virtual bool		ProcessRetry(CTimeOut& timeout);		//规定时间内处理操作，将处理失败的拼接到队尾 重新尝试
	virtual bool		Empty()const;							//空
	virtual size_t		Size()const;
	virtual bool		PushFront(IFunctionArgPtr pAnyArg);
	virtual bool		PushBack(IFunctionArgPtr pAnyArg);
	virtual IFunctionArgPtr	PopFrontPtr();
	virtual IFunctionArgPtr	PopBackPtr();
	virtual bool		Splice(CFunctionQueue& vQueue, bool bBack = true);
	virtual bool		Clear();

	//返回读写互斥锁(同一线程也可能死锁,慎用)
	virtual  CMutexReadWrite& GetMutex()const;
public:
	CFunctionQueue();
	virtual ~CFunctionQueue();
private:
	QueueAnyArgPtr			_vFunction;
};

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CFunctionQueue::PushFunction(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3, tArg4, tArg5));
	return _vFunction.PushBack(ptr);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CFunctionQueue::PushFunction(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2, tArg3, tArg4));
	return _vFunction.PushBack(ptr);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CFunctionQueue::PushFunction(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2 , tArg3));
	return _vFunction.PushBack(ptr);
}

template<typename TFn, typename TArg1, typename TArg2>
bool CFunctionQueue::PushFunction(const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg1, tArg2));
	return _vFunction.PushBack(ptr);
}

template<typename TFn, typename TArg>
bool CFunctionQueue::PushFunction(const TFn& fn, TArg& tArg)
{
	IFunctionArgPtr ptr(CreateFunctionArg(fn, tArg));
	return _vFunction.PushBack(ptr);
}

template<typename TFn>
bool CFunctionQueue::PushFunction(const TFn& fn)
{
	IFunctionArgPtr ptr(CreateFunctionArg(fn));
	return _vFunction.PushBack(ptr);
}

NS_TOOL_FRAME_END

