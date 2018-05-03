#pragma once
#include "Macro.h"
#include "LockMutex.h"

#include "FunctionQueue.h"

NS_TOOL_FRAME_BEGIN
//˳���������
//���Ŀ��:Ϊ�����ϲ��߼�ִ�ж��̲߳�����ʱ���ܹ����߳�һ������ִ�У���������
//�ⲿʹ��ʱ����Ըö��е�GetMutex��õĻ�����Ϊ�������ٽ�����Ψһ�����塣
class CSyncOperateQueue
{
public:
	virtual bool SetOperateDelay(bool bOperateDelay);//�������ʧ�����Ӻ���õ��ӳٶ���
	virtual bool IsOperateDelay()const;
	virtual bool SetProcessContinue(bool bContinue);//�����굱ǰ������ �Ƿ��������(Ĭ�Ͽ���)
	virtual bool IsProcessContinue()const;

	virtual bool PauseProcess();			//��ͣ����
	virtual bool ResumeProcess();			//�ָ�����
	virtual bool IsPauseProcess()const;		//�Ƿ���ͣ

	virtual bool Clear();
	
	//�̰߳�ȫ
public:
	//����ִ�е�ǰ���� �������ʧ�����Ŷ� �п��ܳ��� �տ�ʼ����Ϊ�գ���������ͬʱѹ��ʱ���������������
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

	//�����������
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
	virtual bool ProcessOperate(uint64 uMillTime = 0);		//Mgr������� 
	virtual bool ProcessOperate(CTimeOut& timeout);
	virtual bool IsOperateEmpty()const;
	virtual size_t GetOperateSize()const;
	virtual size_t GetOperateDelaySize()const;
	virtual CMutexRecursive&	GetMutex()const;
	//�ӳٲ�������
public:
	virtual bool PushOperateDelay(IFunctionArgPtr pAnyArg);
	virtual bool SpliceOperateDelay();
	virtual bool IsOperateDelayEmpty()const;
public:
	CSyncOperateQueue();
	virtual ~CSyncOperateQueue();
protected:
	mutable CMutexRecursive	_mutex;			//�ٽ���������(����Ҫ����ٽ��������ĺ�����Ҫ���ϸ���)

	bool					_bPause;
	bool					_bProcessContinue;

	CFunctionQueue			_vOperate;		//��ǰ����
	CFunctionQueue			_vOperatePause;	//��ͣ����

	bool					_bOperateDelay;
	CFunctionQueue			_vOperateDelay; //�ӳٶ���
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
	//ִ��
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

	//ִ��֮���
	if (IsProcessContinue())
		ProcessOperate();
	return true;
}

template<typename TFn, typename TArg>
bool CSyncOperateQueue::OperateFunction(bool bBack, const TFn& fn, TArg& tArg)
{
	//ִ��
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

	//ִ��֮���
	if (IsProcessContinue())
		ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2>
bool CSyncOperateQueue::OperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2)
{
	//ִ��
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

	//ִ��֮���
	if (IsProcessContinue())
		ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool CSyncOperateQueue::OperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	//ִ��
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

	//ִ��֮���
	if (IsProcessContinue())
		ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
bool CSyncOperateQueue::OperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4)
{
	//ִ��
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

	//ִ��֮���
	if (IsProcessContinue())
		ProcessOperate();
	return true;
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
bool CSyncOperateQueue::OperateFunction(bool bBack, const TFn& fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3, TArg4& tArg4, TArg5& tArg5)
{
	//ִ��
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

	//ִ��֮���
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
