#pragma once

#include "Macro.h"
#include "HTimeOut.h"
#include "TThreadSaftyList.h"

NS_TOOL_FRAME_BEGIN
class CTimeOutQueue;
class CTimeBar
{
	typedef TThreadSaftyListValue<CTimeNodePtr> QueueTime;
public:
	bool		IsEmpty()const;
	bool		PushTime(CTimeNodePtr& pTime);
	bool		AddOutTime(uint64 uTimePaused);//增加超时时间

	//系统调用
public:
	bool		Process(uint64 uTimeNow,uint64 uTimeProcess);//处理 限时处理，返回是否 还需要继续处理
public:
	CTimeBar(void);
	virtual ~CTimeBar(void);
private:
	QueueTime	_vQueue;
private:
	CFIELD_PTR(CTimeOutQueue*,Parent,p);
};

NS_TOOL_FRAME_END
