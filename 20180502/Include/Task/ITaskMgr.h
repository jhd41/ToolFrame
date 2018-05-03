#pragma once

#include "Macro.h"
#include "TimeOutQueue.h"

NS_TOOL_FRAME_BEGIN

class ITaskMgr
{
public:
	virtual bool	ProcessTask(uint64 uProcessTime);	//处理任务(返回是否还有需要处理的)
	virtual bool	RunOnce(uint64 uProcessTime);		//运行时钟(返回是否还有需要处理的)
public:
	CTimeOutQueue&	GetTimeOutQueue();
public:
	ITaskMgr(void);
	virtual ~ITaskMgr(void);
private:
	CTimeOutQueue	_vTimeQueue;
};

NS_TOOL_FRAME_END
