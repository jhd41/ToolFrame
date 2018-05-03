#pragma once
#include "Macro.h"
#include "SyncOperateQueue.h"

NS_TOOL_FRAME_BEGIN

class ISyncProcesser;
typedef CSharePtr<ISyncProcesser>					ISyncProcesserPtr;
class ISyncProcesserManager;

//异步操作器
//主要用于多线程处理 有两个驱动。PushOperate 和 ProcessOperate
//当当前线程锁成功时 PushOperate 成功，否则就进入队列，外部需要调用 ProcessOperate 把队列中的操作处理掉
class ISyncProcesser
	:public CShareFromThis<ISyncProcesser>
{
public:
	virtual bool SetOperateDelay(bool bOperateDelay);//如果处理失败则延后放置到延迟队列
	virtual bool IsOperateDelay()const;
	virtual bool PauseProcess();			//暂停处理
	virtual bool ResumeProcess();			//恢复处理
	virtual bool IsPauseProcess()const;		//是否暂停

	virtual bool MarkDeleted();			//标记为删除
	virtual bool IsMarkDeleted()const;
	virtual bool ClearDeleted();

	virtual bool MarkNormal();			//标记为正常
	virtual bool IsNormal()const;
	virtual bool ClearNormal();

	virtual bool MarkVaild();			//标记为有效
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

	//向管理器发起请求(稍后才会被真正执行)
	virtual bool ReqMgrInsertSecond(uint uSecondID);
	virtual bool ReqMgrRemoveSecond(uint uSecondID);
protected:
	virtual bool ReqMgrOperate();
	virtual bool ReqMgrDelete();
public:
	CFIELD_UINT(ProcesserID);	//主键
	CFIELD_UINT(SecondID);		//次键
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

