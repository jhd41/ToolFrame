#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN

//平均计数器(线程安全)
class TOOLFRAME_DLL CAvgCounter
{
public:
	virtual bool AddCount(uint64 uValue,bool bMark = false);
	virtual bool GetAvg	( uint64* uTotal, uint64* uTimes = nullptr,uint64* uValueMax = nullptr ,uint64* uAvg = nullptr, uint64* uMarkTotal = nullptr,uint* uMarkTimes = nullptr,uint64* uMarkMax = nullptr ,uint64* uMarkAvg = nullptr);
	virtual bool Clear	( uint64* uTotal, uint64* uTimes = nullptr,uint64* uValueMax = nullptr ,uint64* uAvg = nullptr, uint64* uMarkTotal = nullptr,uint* uMarkTimes = nullptr,uint64* uMarkMax = nullptr ,uint64* uMarkAvg = nullptr);
public:
	CAvgCounter& operator = (const CAvgCounter& xCounter);
public:
	CAvgCounter(void);
	CAvgCounter(const CAvgCounter& xCounter);
	virtual ~CAvgCounter(void);
private:
	mutable CMutexReadWrite	_mutex;				//统计的锁

	uint64			_uValueTotal;		//总值
	uint64			_uValueMax;			//峰值
	uint64			_uValueTimes;		//次数

	uint64			_uMarkTotal;		//总值
	uint64			_uMarkMax;			//峰值
	uint			_uMarkTimes;		//次数
};

NS_TOOL_FRAME_END
