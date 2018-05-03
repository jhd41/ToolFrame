#pragma once

#include "Macro.h"
#include "IThread.h"
#include "MacroDefineBoost.h"

//线程:
//继承本类之后 需要在子类里实现这两个函数.
//使用StartThread之后可以轻松的启动一个新的线程
//不允许在任何回调的时候 delete这个类的对象，如果真的需要删除，请使用AutoRelease标记即可

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IThreadNew
	:public IThread
{
public:
	virtual bool StartThread(uint uTimeInterval=50);
	virtual bool ReqStopThread();
	virtual bool IsReqStopThread()const ;
	virtual bool SetTimeInterval(uint uTimeInterval);	//设置循环间隔时间
	virtual uint GetTimeInterval()const;				//获取循环间隔时间
	virtual bool Interrupt();							//强制打断(无论何种情况下 都不应调用该函数)
	virtual bool ReqInterrupt();						//请求打断
	virtual bool InterruptPoint();						//设置打断点 若请求了打断 则会 打断当前线程
	virtual bool IsReqInterrupt()const;					//是否请求打断
	virtual bool IsInterrupted()const;					//是否已被打断
public:
	virtual bool OnInterrupted();						//线程打断时
private:
	void RunThread();
public:
	IThreadNew(void);
	virtual ~IThreadNew(void);
private:
	volatile bool	_bReqStop;
	volatile bool	_bReqInterrupt;
	volatile bool	_bInterrupted;
	uint			_uTimeInterval;
	boost::thread*	_pThread;
};

class CExceptionThreadInterrupt
{
public:
	CExceptionThreadInterrupt(){}
	~CExceptionThreadInterrupt(){}
};
NS_TOOL_FRAME_END
