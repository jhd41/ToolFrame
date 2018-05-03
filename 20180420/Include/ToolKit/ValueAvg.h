#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

//计算平均值(线程安全)
NS_TOOL_FRAME_BEGIN

class CValueAvg
{
public:
	double GetAvg()const;
	double AddValue(double fValue);
public:
	CValueAvg& operator = (const CValueAvg& xValueAvg);
	operator double()const;
public:
	CValueAvg(void);
	CValueAvg(const CValueAvg& xValueAvg);
	virtual ~CValueAvg(void);
private:
	double					_fAvg;	//平均值
	uint					_uCount;//次数
	mutable CMutexReadWrite	_mutex;
};

NS_TOOL_FRAME_END
