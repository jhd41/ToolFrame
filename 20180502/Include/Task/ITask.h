#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"
#include "HTimeOut.h"

NS_TOOL_FRAME_BEGIN
class ITaskMgr;
class ITask
		:public HTimeOut
{
public:
	virtual bool Init();//���ó�ʼ״̬
	//������Ԫ ����Ҫ�����̻߳�����
public:
	virtual bool OnInit(int eState){return true;}
	virtual bool OnStateReclaim(int eState){return true;}//��״̬����
	virtual bool OnStateChanged(int eState){return true;}//״̬�ı����
	virtual bool OnTimeOut(int eState){return false;}//��ʱ
protected:
	virtual bool SetOverState(int eState);//���ý���״̬(����״̬ʱ ������ᱻ����)
	virtual bool SetState(int eState);//ֻ�����ڲ�����
	virtual	bool StartWaitByMill(uint64 uMillSecond,bool bLoop = false,time_t uTimeDelay=0);//��ʼ�ȴ�(����)
	virtual bool StartWaitBySecond(uint uSecond,bool bLoop = false,time_t uTimeDelay=0);//��ʼ�ȴ�(��)
	virtual bool CancelWait();
	virtual bool RemoveTimer();

	//�ⲿ��Ҫ����
public:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode);
public:
	CMutexRecursive& GetMutex()const;
public:
	ITask(void);
	virtual ~ITask(void);
private:
	CFIELD_PTR(ITaskMgr*,TaskMgr,p);
	CFIELD_BOOL(TaskOver);			//�������(��������)
protected:
	mutable	CMutexRecursive	_mutex;
	int						_eState;	//��ǰ״̬
	int						_eStateOver;//����״̬
	CTimeNodePtr			_pTimer;
};

NS_TOOL_FRAME_END
