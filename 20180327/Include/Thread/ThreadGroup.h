#pragma once
#include "Macro.h"
#include "TThreadSaftyList.h"
#include "IThread.h"
#include "TObjCreator.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL CThreadGroup
{
	//定义线程列表
	typedef TThreadSaftyListValue<IThread*>	ListThread;
	typedef TObjCreator<IThread>			CThreadCreator;

	//单个操作
public:
	bool	AddThread(IThread* pThread);
	bool	RemoveThread(IThread* pThread);

	template<typename T>
	T*		CreateThread();						//创建一个线程
	bool	ReleaseThread(IThread* pThread);	//释放线程

	//批量操作
public:
	bool	StartThread();
	bool	StopThread();			//只有当所有线程都退出后才会返回
	bool	RemoveThread();
	bool	IsAllThreadStoped()const;
	bool	IsEmpty()const;			//是否没有线程
	size_t	GetCount()const;		//获取线程数
	IThread* GetFrontThread();		//获取第一个线程(外部注意线程同步问题)
	IThread* GetBackThread();		//获取最后一个线程(外部注意线程同步问题)

	bool	ReqStopFrontThread();	//请求关闭第一个线程
	bool	ReqStopBackThread();	//请求关闭最后一个线程

	bool	IsFrontThreadStarted()const;//第一个线程是否在启动中
	bool	IsBackThreadStarted()const;	//最后一个线程是否在启动中

	bool	ReleaseFrontThread();	//停止并释放第一个线程
	bool	ReleaseBackThread();	//停止并释放最后一个线程
protected:
	bool	ReqStopThread()const;
public:
	CThreadGroup(void);
	virtual ~CThreadGroup(void);
private:
	//线程列表
	ListThread			_vThread;	//线程列表
	CThreadCreator		_vCreator;	//创建器
};

template<typename T>
T* ToolFrame::CThreadGroup::CreateThread()
{
	T* pThread = _vCreator.CreateObj<T>();
	if (!pThread)return nullptr;
	AddThread(pThread);
	return pThread;
}

NS_TOOL_FRAME_END
