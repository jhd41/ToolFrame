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
	//外部调用
public:
	bool AddTaskThread(uint uThreads,uint uTimeInterval=50);	//添加执行任务的线程,
	bool Stop();												//等待所有的线程都安全退出后 返回

	bool RunOneTask();											//执行一个任务(若没有执行 返回false)
	bool RunTask(uint64 uTime);									//在执行任务直到超出为止 返回是否执行过任务
public:
	//定义线程任务节点队列
	struct XTaskNode{
		CMutexRecursive mutex;
		IThreadTask*	pTask;			//任务指针
		uint			uTimeInterval;	//时间间隔
		bool			bDeleted;		//删除标记
		uint64			uTimeLast;		//最近开始执行的时间
		bool			bInited;		//初始化
		uint64			uTimeLastWork;	//任务执行时间(最近一次)
		int				nLoopCount;		//剩余循环次数
	};
	typedef CSharePtr<XTaskNode>					TaskNodePtr;
	typedef TThreadSaftyListValue<TaskNodePtr>		QueueTask;

	//定义线程列表
	typedef std::list<IThread*>						ListThread;

	//线程内部调用(外部最好不要调用)
public:
	bool AddTask(IThreadTask* pTask,int nLoop = -1,uint uCount=1,uint uTimeInterval=0);//添加任务(任务指针,任务个数,任务执行间隔)
	bool RemoveTask(const IThreadTask* pTask);	//移除任务
	QueueTask&	GetRunningTaskQueue();
	TaskNodePtr PopRunOneTask();//弹出一个任务 并 执行(返回 被弹出的 任务)
public:
	CTaskThreadManager(void);
	virtual ~CTaskThreadManager(void);
private:
	//线程任务队列
	QueueTask			_vTask;			//仅仅是一个注册
	QueueTask			_vRuning;		//实际运行的队列
	CThreadGroup		_vThread;		//所有的线程
};

//线程任务处理器
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
