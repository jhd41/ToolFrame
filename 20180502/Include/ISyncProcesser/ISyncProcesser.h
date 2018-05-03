#pragma once
#include "Macro.h"
#include "SyncOperateQueue.h"

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

	virtual CSyncOperateQueue& GetOperateQueue();
	virtual const CSyncOperateQueue& GetOperateQueue()const;

	DEFINE_TO_PTR_FUNC(ToProcesser);

	virtual ISyncProcesserPtr		GetSharePtr();

	template<typename T>
	T*								GetUserData()const;

	template<typename T>
	T*								GetMgr()const;

	virtual CMutexRecursive&		GetMutex()const;

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
	bool					_bNormal;
	bool					_bVaild;
	bool					_bDelete;

	CSyncOperateQueue		_vQueue;
};

template<typename T>
T*	ISyncProcesser::GetMgr()const {
	return static_cast<T*>(GetMgr());
}

template<typename T>
T*	ISyncProcesser::GetUserData()const {
	return static_cast<T*>(GetUserData());
}



NS_TOOL_FRAME_END

