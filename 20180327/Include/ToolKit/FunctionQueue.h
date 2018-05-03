#pragma once

#include "Macro.h"
#include "IFunctionArg.h"
#include "TimeOut.h"

NS_TOOL_FRAME_BEGIN
//��������
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
	virtual bool		ProcessOne();							//����һ������ ���Ϊ�� ����false
	virtual bool		Process(CTimeOut& timeout);				//����涨ʱ���ڵĲ�������������� ����false
	virtual bool		ProcessRetry(CTimeOut& timeout);		//�涨ʱ���ڴ��������������ʧ�ܵ�ƴ�ӵ���β ���³���
	virtual bool		Empty()const;							//��
	virtual size_t		Size()const;
	virtual bool		PushFront(IFunctionArgPtr pAnyArg);
	virtual bool		PushBack(IFunctionArgPtr pAnyArg);
	virtual IFunctionArgPtr	PopFrontPtr();
	virtual IFunctionArgPtr	PopBackPtr();
	virtual bool		Splice(CFunctionQueue& vQueue, bool bBack = true);
	virtual bool		Clear();

	//���ض�д������(ͬһ�߳�Ҳ��������,����)
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

