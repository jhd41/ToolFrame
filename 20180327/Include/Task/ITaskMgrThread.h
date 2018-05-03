#pragma once
#include "Macro.h"
#include "ITaskMgr.h"
#include "IThreadTask.h"

NS_TOOL_FRAME_BEGIN

class ITaskMgrThread
	:public ITaskMgr
	,public IThreadTask
{
public:
	virtual	bool InitThread();
	virtual bool RunOnceThread();
public:
	ITaskMgrThread(void);
	virtual ~ITaskMgrThread(void);
};

NS_TOOL_FRAME_END
