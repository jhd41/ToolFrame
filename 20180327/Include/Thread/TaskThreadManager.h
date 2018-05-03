#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"
#include "TThreadSaftyList.h"
#include "TThreadSaftyList.h"

#include "IThreadTask.h"
#include "IThreadNew.h"
#include "ThreadGroup.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL CTaskThreadManager
{
	//�ⲿ����
public:
	bool AddTaskThread(uint uThreads,uint uTimeInterval=50);	//���ִ��������߳�,
	bool Stop();												//�ȴ����е��̶߳���ȫ�˳��� ����

	bool RunOneTask();											//ִ��һ������(��û��ִ�� ����false)
	bool RunTask(uint64 uTime);									//��ִ������ֱ������Ϊֹ �����Ƿ�ִ�й�����
public:
	//�����߳�����ڵ����
	struct XTaskNode{
		CMutexRecursive mutex;
		IThreadTask*	pTask;			//����ָ��
		uint			uTimeInterval;	//ʱ����
		bool			bDeleted;		//ɾ�����
		uint64			uTimeLast;		//�����ʼִ�е�ʱ��
		bool			bInited;		//��ʼ��
		uint64			uTimeLastWork;	//����ִ��ʱ��(���һ��)
		int				nLoopCount;		//ʣ��ѭ������
	};
	typedef CSharePtr<XTaskNode>					TaskNodePtr;
	typedef TThreadSaftyListValue<TaskNodePtr>		QueueTask;

	//�����߳��б�
	typedef std::list<IThread*>						ListThread;

	//�߳��ڲ�����(�ⲿ��ò�Ҫ����)
public:
	bool AddTask(IThreadTask* pTask,int nLoop = -1,uint uCount=1,uint uTimeInterval=0);//�������(����ָ��,�������,����ִ�м��)
	bool RemoveTask(const IThreadTask* pTask);	//�Ƴ�����
	QueueTask&	GetRunningTaskQueue();
	TaskNodePtr PopRunOneTask();//����һ������ �� ִ��(���� �������� ����)
public:
	CTaskThreadManager(void);
	virtual ~CTaskThreadManager(void);
private:
	//�߳��������
	QueueTask			_vTask;			//������һ��ע��
	QueueTask			_vRuning;		//ʵ�����еĶ���
	CThreadGroup		_vThread;		//���е��߳�
};

//�߳���������
//////////////////////////////////////////////////////////////////////////
class CThreadTaskProcesser
	:public IThreadNew
{
public:
	bool SetManager(CTaskThreadManager* pMgr);
public:
	virtual	bool InitThread();
	virtual bool RunOnceThread();
public:
	CThreadTaskProcesser();
	virtual ~CThreadTaskProcesser();
private:
	CTaskThreadManager*	_pMgr;
};

NS_TOOL_FRAME_END
