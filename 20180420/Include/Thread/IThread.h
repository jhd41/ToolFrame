#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"

//线程基类

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL IThread
{
	//非线程安全(启动前设置)
public:
	virtual bool AutoRelease();		//自动释放(线程调用结束后会自动释放)若 线程未启动 不会被释放
	virtual bool Release();			//释放(如果 线程已经启动 则 标记释放 如果 线程已停止 则直接释放)
public:
	virtual bool StartThread();		//启动线程
	virtual bool StopThread();		//停止线程(线程退出后才返回)
	virtual bool ReqStopThread()=0;	//请求停止线程(仅仅设置了标记)
public:
	virtual	bool InitThread()=0;
	virtual bool RunOnceThread()=0;
public:
	virtual bool IsThreadStarting()const;
	virtual bool IsThreadStarted()const;
	virtual	bool IsThreadStoped()const;
	virtual bool IsAutoRelease()const;
protected:
	virtual	bool SetThreadStarted();
	virtual	bool SetThreadStoped();
	virtual bool ClearThreadStoped();
protected:
	virtual bool OnThreadStoped();			//线程结束时调用
public:
	IThread(void);
	virtual ~IThread(void);
private:
	volatile bool	_bThreadStarting;	//线程启动中
	volatile bool	_bThreadStarted;	//线程已启动
	volatile bool	_bThreadStoped;		//线程已关闭
	volatile bool	_bAutoRelease;		//标记自动释放
	mutable CMutexReadWrite _mThreadMutex;
};
NS_TOOL_FRAME_END
