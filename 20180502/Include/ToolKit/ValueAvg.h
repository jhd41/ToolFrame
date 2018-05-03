#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

//����ƽ��ֵ(�̰߳�ȫ)
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
	double					_fAvg;	//ƽ��ֵ
	uint					_uCount;//����
	mutable CMutexReadWrite	_mutex;
};

NS_TOOL_FRAME_END
