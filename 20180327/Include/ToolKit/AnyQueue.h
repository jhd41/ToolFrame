#pragma once

#include "Macro.h"
#include "IAnyArg.h"
#include "TimeOut.h"

NS_TOOL_FRAME_BEGIN

class CAnyQueue
{
public:
	template<typename TFn>
	bool				PushArg(const TFn& fn);
	template<typename TFn, typename TArg>
	bool				PushArg(const TFn& fn, TArg& tArg);
	template<typename TFn, typename TArg1, typename TArg2>
	bool				PushArg(const TFn& fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool				PushArg(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
	bool				PushArg(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4);
	template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	bool				PushArg(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5);
public:
	virtual bool		ProcessOne();							//����һ������ ���Ϊ�� ����false
	virtual bool		Process(CTimeOut& timeout);				//����涨ʱ���ڵĲ�������������� ����false
	virtual bool		ProcessRetry(CTimeOut& timeout);		//�涨ʱ���ڴ��������������ʧ�ܵ�ƴ�ӵ���β ���³���
	virtual bool		Empty()const;							//��
	virtual size_t		Size()const;
	virtual bool		PushFront(IAnyArgPtr pAnyArg);
	virtual bool		PushBack(IAnyArgPtr pAnyArg);
	virtual IAnyArgPtr	PopFrontPtr();
	virtual IAnyArgPtr	PopBackPtr();
	virtual bool		Splice(CAnyQueue& vQueue, bool bBack = true);
	virtual bool		Clear();

	//���ض�д������(ͬһ�߳�Ҳ��������,����)
	virtual  CMutexReadWrite& GetMutex()const;
public:
	CAnyQueue();
	virtual ~CAnyQueue();
private:
	QueueAnyArgPtr			_vOperate;
};

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CAnyQueue::PushArg(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	IAnyArgPtr ptr(CreateAnyArg(fn, tArg1, tArg2, tArg3, tArg4, tArg5));
	return _vOperate.PushBack(ptr);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CAnyQueue::PushArg(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	IAnyArgPtr ptr(CreateAnyArg(fn, tArg1, tArg2, tArg3, tArg4));
	return _vOperate.PushBack(ptr);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CAnyQueue::PushArg(const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	IAnyArgPtr ptr(CreateAnyArg(fn, tArg1, tArg2 , tArg3));
	return _vOperate.PushBack(ptr);
}

template<typename TFn, typename TArg1, typename TArg2>
bool CAnyQueue::PushArg(const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	IAnyArgPtr ptr(CreateAnyArg(fn, tArg1, tArg2));
	return _vOperate.PushBack(ptr);
}

template<typename TFn, typename TArg>
bool CAnyQueue::PushArg(const TFn& fn, TArg& tArg)
{
	IAnyArgPtr ptr(CreateAnyArg(fn, tArg));
	return _vOperate.PushBack(ptr);
}

template<typename TFn>
bool CAnyQueue::PushArg(const TFn& fn)
{
	IAnyArgPtr ptr(CreateAnyArg(fn));
	return _vOperate.PushBack(ptr);
}

NS_TOOL_FRAME_END

