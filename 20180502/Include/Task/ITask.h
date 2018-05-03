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
	virtual bool Init();//设置初始状态
	//操作单元 不需要考虑线程互斥锁
public:
	virtual bool OnInit(int eState){return true;}
	virtual bool OnStateReclaim(int eState){return true;}//当状态回收
	virtual bool OnStateChanged(int eState){return true;}//状态改变完成
	virtual bool OnTimeOut(int eState){return false;}//超时
protected:
	virtual bool SetOverState(int eState);//设置结束状态(结束状态时 该任务会被清理)
	virtual bool SetState(int eState);//只允许内部调用
	virtual	bool StartWaitByMill(uint64 uMillSecond,bool bLoop = false,time_t uTimeDelay=0);//开始等待(毫秒)
	virtual bool StartWaitBySecond(uint uSecond,bool bLoop = false,time_t uTimeDelay=0);//开始等待(秒)
	virtual bool CancelWait();
	virtual bool RemoveTimer();

	//外部不要调用
public:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode);
public:
	CMutexRecursive& GetMutex()const;
public:
	ITask(void);
	virtual ~ITask(void);
private:
	CFIELD_PTR(ITaskMgr*,TaskMgr,p);
	CFIELD_BOOL(TaskOver);			//任务结束(可以清理)
protected:
	mutable	CMutexRecursive	_mutex;
	int						_eState;	//当前状态
	int						_eStateOver;//结束状态
	CTimeNodePtr			_pTimer;
};

NS_TOOL_FRAME_END
