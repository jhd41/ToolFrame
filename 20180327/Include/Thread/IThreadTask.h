#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"
#include "IThread.h"

//线程:
//继承本类之后 需要在子类里实现这两个函数.
//使用StartThread之后可以添加N个线程任务。MThread中启动的线程会来执行当前的任务
//该方法启动的线程会加入MTheard中去会由MThread统一管理

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CTaskThreadManager;
class TOOLFRAME_DLL IThreadTask
		:public IThread
{
public:
	virtual bool StartThread(int nLoop = -1,uint uCount = 1,uint uTimeInterval=50);
	virtual bool ReqStopThread();
public:
	IThreadTask(void);
	virtual ~IThreadTask(void);
private:
	CMutexRecursive		_mutex;
	CTaskThreadManager*	_pMgrTaskThread;
};

NS_TOOL_FRAME_END
