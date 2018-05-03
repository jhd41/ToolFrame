#pragma once

#include "Macro.h"

//必须先初始化，
//之后需要间隔时间去调用Reflash函数，调用之后会计算CPU的各个属性

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS

class CApiWinCpu
{
	struct XTimeSystem{
		uint64	uTimeIdle;
		uint64	uTimeKernel;
		uint64	uTimeUser;
	};
public:
	bool	Reflash();

	//获取至最近一次刷新的数据信息
	uint64	GetIdleTime()const;		//获取空闲状态时间
	uint64	GetKernelTime()const;	//获取内核状态时间
	uint64	GetUserTime()const;		//获取用户状态时间
	int		CalCpuUsage()const;		//计算CPU利用率
	int		CalCpuIdle()const;		//计算CPU空闲率
private:
	bool	Init();
	bool GetSystemTime(XTimeSystem& xTime)const;
public:
	CApiWinCpu(void);
	virtual ~CApiWinCpu(void);
private:
	XTimeSystem	_xTimeOld;
	XTimeSystem	_xTimeNow;
};

#endif
