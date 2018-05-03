#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"
#include "TimeElapse.h"

//流逝时间(线程安全)

NS_TOOL_FRAME_BEGIN

class CTimeElapseEx
{
public:
	virtual uint64	ReStart();			//重新开始计时(返回之前的流逝时间)
	virtual uint64	TimeElapsed()const;	//时间已经流逝
	virtual uint64	TimeElapsed(uint64 uTimeNow)const;
	
	virtual bool	Pause();			//暂停
	virtual bool	Resume();			//恢复
	virtual bool	IsPausing()const;	//是否在暂停中

	virtual bool	SetTimeBegin(uint64 uTimeBegin);//设置起始时间
public:
	CTimeElapseEx(void);
	virtual ~CTimeElapseEx(void);
private:
	uint64		_uTimeElapse;	//流逝时间
	uint64		_uPauseElapse;	//暂停时间
	bool		_bPause;		//暂停中

	CTimeElapse _xTimeElapse;	//时间流逝

	mutable CMutexReadWrite _mutex;
};

NS_TOOL_FRAME_END
