#pragma once

#include "Macro.h"
#include "TimeElapse.h"

//帮助是否超时

NS_TOOL_FRAME_BEGIN

class CTimeOut
{
public:
	virtual uint64	ReStart();							//重新计时(返回最近一次计时间隔)
	virtual bool	IsTimeOut()const;					//是否超时
	virtual bool	IsTimeOutMill(uint64 uTimeNow)const;//是否超时
	virtual bool	IsTimeOutMill(uint64 uTimeNow,uint64 uInterval)const;	//是否超时
	virtual bool	IsTimeOutSec(time_t uTimeNow)const;	//是否超时
	virtual bool	IsTimeOutSec(time_t uTimeNow,time_t uInterval)const;	//是否超时
	

	virtual uint64	TimeRemaining()const;				//时间剩余

	virtual bool	IsNeverTimeout()const;				//是否永不超时
	virtual bool	IsNeverTimeout(uint64 uInterval)const;//是否永不超时

	virtual bool	SetIntervalMill(uint64 uInterval);	//设置时间间隔(毫秒)
	virtual uint64	GetIntervalMill()const;				//获取间隔时间

	virtual bool	SetIntervalSec(time_t uInterval);	//设置时间间隔(秒)
	virtual time_t	GetIntervalSec()const;				//获取间隔时间(秒)

	virtual bool	IsVaild()const;						//是否有效
	virtual bool	SetVaild(bool bVaild);				//设置有效标记

	virtual bool	TryTimeOutRestart();					//超时时 尝试重置，若未超时 返回false
public:
	CTimeOut();
	CTimeOut(uint64 uTime);	//传入时间间隔(0为无限时间 永不超时 务必注意)
	virtual ~CTimeOut(void);
private:
	CTimeElapse	_tElapse;	//时间流逝
	uint64		_uInterval;	//超时时间
	bool		_bVaild;	//有效标记
};

NS_TOOL_FRAME_END
