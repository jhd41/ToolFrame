#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

//流逝时间(线程安全)

NS_TOOL_FRAME_BEGIN

class CTimeElapse
{
public:
	virtual uint64	ReStart();			//重新开始计时(返回之前的流逝时间)
	virtual uint64	TimeElapsed()const;	//时间已经流逝
	virtual uint64	TimeElapsed(uint64 uTimeNow)const;
	virtual uint64	GetTimeBegin()const;//获取启动时间
	virtual bool	IsVaild()const;		//是否有效
	virtual bool	SetVaild(bool bVaild);

	virtual bool	SetTimeBegin(uint64 uTimeBegin);//设置起始时间

	//无锁
public:
	virtual uint64	NoLockRestart(uint64 uTimeNow);
	virtual uint64	NoLockTimeElapsed(uint64 uTimeNow)const;
	CMutexReadWrite& GetMutex()const;
public:
	CTimeElapse& operator = (const CTimeElapse& xElapse);
public:
	CTimeElapse(void);
	CTimeElapse(const CTimeElapse& xElapse);
	virtual ~CTimeElapse(void);
private:
	uint64	_uTimeBegin;
	bool	_bVaild;
	mutable CMutexReadWrite	_mutex;
};

NS_TOOL_FRAME_END
