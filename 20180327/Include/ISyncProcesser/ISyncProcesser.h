#pragma once
#include "Macro.h"
#include "LockMutex.h"

#include "FunctionQueue.h"

NS_TOOL_FRAME_BEGIN

class ISyncProcesser;
typedef CSharePtr<ISyncProcesser>					ISyncProcesserPtr;
class ISyncProcesserManager;

//�첽������
//��Ҫ���ڶ��̴߳��� ������������PushOperate �� ProcessOperate
//����ǰ�߳����ɹ�ʱ PushOperate �ɹ�������ͽ�����У��ⲿ��Ҫ���� ProcessOperate �Ѷ����еĲ��������
class ISyncProcesser
	:public CShareFromThis<ISyncProcesser>
{
public:
	virtual bool SetOperateDelay(bool bOperateDelay);//�������ʧ�����Ӻ���õ��ӳٶ���
	virtual bool IsOperateDelay()const;

	//�̰߳�ȫ
public:
	//�п��ܳ��� �տ�ʼ����Ϊ�գ���������ͬʱѹ��ʱ���������������
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

	virtual bool ProcessOperate(uint64 uMillTime);		//Mgr������� 
	virtual bool ProcessOperate(CTimeOut& timeout);
	virtual bool IsOperateEmpty()const;
	virtual size_t GetOperateSize()const;
	virtual size_t GetOperateDelaySize()const;

	virtual bool PauseProcess();			//��ͣ����
	virtual bool ResumeProcess();			//�ָ�����
	virtual bool IsPauseProcess()const;		//�Ƿ���ͣ

	virtual bool MarkDeleted();			//���Ϊɾ��
	virtual bool IsMarkDeleted()const;
	virtual bool ClearDeleted();

	virtual bool MarkNormal();			//���Ϊ����
	virtual bool IsNormal()const;
	virtual bool ClearNormal();

	virtual bool MarkVaild();			//���Ϊ��Ч
	virtual bool IsVaild()const;
	virtual bool ClearVaild();

	DEFINE_TO_PTR(ToProcesser);

	virtual ISyncProcesserPtr		GetSharePtr();

	template<typename T>
	T*								GetUserData()const;

	template<typename T>
	T*								GetMgr()const;

	CMutexRecursive&				GetMutex()const;

	//�ӳٲ�������
public:
	virtual bool PushOperateDelay(IFunctionArgPtr pAnyArg);
	virtual bool SpliceOperateDelay();
	virtual bool IsOperateDelayEmpty()const;

	//���������������(�Ժ�Żᱻ����ִ��)
	virtual bool ReqMgrInsertSecond(uint uSecondID);
	virtual bool ReqMgrRemoveSecond(uint uSecondID);
protected:
	virtual bool ReqMgrOperate();
	virtual bool ReqMgrDelete();
public:
	CFIELD_UINT(ProcesserID);	//����
	CFIELD_UINT(SecondID);		//�μ�
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

	CFunctionQueue			_vOperate;		//��ǰ����
	CFunctionQueue			_vOperatePause;	//��ͣ����

	bool					_bOperateDelay;
	CFunctionQueue			_vOperateDelay; //�ӳٶ���
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

