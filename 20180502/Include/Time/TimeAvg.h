#pragma once
#include "Macro.h"
#include "ValueAvg.h"

//计算平均时间(线程安全)

NS_TOOL_FRAME_BEGIN

class CTimeAvg
{
public:
	uint64 GetAvgTime()const;
	uint64 AddTimeElapsed(uint64 uTimeElapsed);
	operator uint64()const;
public:
	CTimeAvg(void);
	virtual ~CTimeAvg(void);
private:
	CValueAvg	_avgValue;
};

NS_TOOL_FRAME_END
