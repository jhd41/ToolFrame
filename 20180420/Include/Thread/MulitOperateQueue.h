#pragma once
#include "Macro.h"
#include "LockMutex.h"

#include "FunctionQueue.h"
#include "CalCounter.h"

NS_TOOL_FRAME_BEGIN
//��д��������
//���Ŀ��:�ñ��������ٽ��� �ܹ� ���Եı� ��д���ʣ�����������
//�ⲿʹ��ʱ����Ըö��е�GetMutex��õĻ�����Ϊ�������ٽ�����Ψһ�����塣
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
	virtual bool SetOperateDelay(bool bOperateDelay);//�������ʧ�����Ӻ���õ��ӳٶ���
	virtual bool IsOperateDelay()const;

	virtual bool PauseProcess();			//��ͣ����
	virtual bool ResumeProcess();			//�ָ�����
	virtual bool IsPauseProcess()const;		//�Ƿ���ͣ

	virtual bool Clear();
	
	virtual size_t ClearProcessCount();	//��������� �����Ѿ��������

	//�̰߳�ȫ
public:
	//����ִ�е�ǰ���� �������ʧ�����Ŷ� �п��ܳ��� �տ�ʼ����Ϊ�գ���������ͬʱѹ��ʱ���������������
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

	//д����
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

	//�����������
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
	virtual bool ProcessOperate(uint64 uMillTime = 0);		//Mgr������� 
	virtual bool ProcessOperate(CTimeOut& timeout);
	virtual bool IsOperateEmpty()const;
	virtual size_t GetOperateSize()const;
	virtual size_t GetOperateDelaySize()const;
	virtual CMutexReadWrite&	GetMutex()const;
	//�ӳٲ�������
public:
	virtual bool PushOperateDelay(IFunctionArgPtr pAnyArg);
	virtual bool SpliceOperateDelay();
	virtual bool IsOperateDelayEmpty()const;
public:
	CMulitOperateQueue();
	virtual ~CMulitOperateQueue();
protected:
	mutable CMutexReadWrite	_mutex;			//�ٽ���������(����Ҫ����ٽ��������ĺ�����Ҫ���ϸ���)
	mutable CMutexReadWrite	_mutexQueue;	//��ǰ���еĻ�����

	CCalCounterSize			_uProcessCount;	//������

	bool					_bPause;

	CFunctionQueue			_vOperate;		//��ǰ����
	CFunctionQueue			_vOperatePause;	//��ͣ����

	bool					_bOperateDelay;
	CFunctionQueue			_vOperateDelay; //�ӳٶ���
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
	//ִ��
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

	//ִ��֮���
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg>
bool CMulitOperateQueue::ReadOperateFunction(bool bBack, const TFn& fn, TArg& tArg)
{
	//ִ��
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

	//ִ��֮���
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2>
bool CMulitOperateQueue::ReadOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	//ִ��
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

	//ִ��֮���
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CMulitOperateQueue::ReadOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	//ִ��
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

	//ִ��֮���
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CMulitOperateQueue::ReadOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	//ִ��
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

	//ִ��֮���
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CMulitOperateQueue::ReadOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	//ִ��
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

	//ִ��֮���
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>
bool CMulitOperateQueue::ReadOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5, TArg6& tArg6)
{
	//ִ��
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

	//ִ��֮���
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
	//ִ��
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

	//ִ��֮���
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg>
bool CMulitOperateQueue::WriteOperateFunction(bool bBack, const TFn& fn, TArg& tArg)
{
	//ִ��
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

	//ִ��֮���
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2>
bool CMulitOperateQueue::WriteOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	//ִ��
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

	//ִ��֮���
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CMulitOperateQueue::WriteOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	//ִ��
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

	//ִ��֮���
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CMulitOperateQueue::WriteOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	//ִ��
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

	//ִ��֮���
	ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CMulitOperateQueue::WriteOperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	//ִ��
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

	//ִ��֮���
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
