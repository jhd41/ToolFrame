#pragma once

#include "Macro.h"
#include "TimeOutQueue.h"

NS_TOOL_FRAME_BEGIN

class ITaskMgr
{
public:
	virtual bool	ProcessTask(uint64 uProcessTime);	//��������(�����Ƿ�����Ҫ�����)
	virtual bool	RunOnce(uint64 uProcessTime);		//����ʱ��(�����Ƿ�����Ҫ�����)
public:
	CTimeOutQueue&	GetTimeOutQueue();
public:
	ITaskMgr(void);
	virtual ~ITaskMgr(void);
private:
	CTimeOutQueue	_vTimeQueue;
};

NS_TOOL_FRAME_END
