#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN

//ƽ��������(�̰߳�ȫ)
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
	mutable CMutexReadWrite	_mutex;				//ͳ�Ƶ���

	uint64			_uValueTotal;		//��ֵ
	uint64			_uValueMax;			//��ֵ
	uint64			_uValueTimes;		//����

	uint64			_uMarkTotal;		//��ֵ
	uint64			_uMarkMax;			//��ֵ
	uint			_uMarkTimes;		//����
};

NS_TOOL_FRAME_END
