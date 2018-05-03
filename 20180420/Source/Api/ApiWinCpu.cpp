#include "ApiWinCpu.h"

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS

#include "ApiWin.h"

CApiWinCpu::CApiWinCpu(void)
{
	Init();
}

CApiWinCpu::~CApiWinCpu(void)
{
}

bool CApiWinCpu::Init()
{
	if (!GetSystemTime(_xTimeNow))return false;
	
	_xTimeOld = _xTimeNow;
	return true;
}

bool CApiWinCpu::Reflash()
{
	_xTimeOld = _xTimeNow;
	return GetSystemTime(_xTimeNow);
}

bool CApiWinCpu::GetSystemTime( XTimeSystem& xTime ) const
{
	return ApiWin::GetSystemTimes(&xTime.uTimeIdle,&xTime.uTimeKernel,&xTime.uTimeUser);
}

int CApiWinCpu::CalCpuUsage() const
{
	uint64 uTimeIdle = GetIdleTime();
	uint64 uTimeKernel = GetKernelTime();
	uint64 uTimeUser = GetUserTime();

	if (uTimeKernel + uTimeUser <= 0)return 0;
	float fCpuUsage = 100.0f * (uTimeKernel + uTimeUser - uTimeIdle) / (uTimeKernel + uTimeUser);
	return (int)fCpuUsage;
}

int CApiWinCpu::CalCpuIdle() const
{
	if (GetKernelTime() + GetUserTime() <= 0)return 0;
	float fCpuIdle = 100.0f * GetIdleTime() / (GetKernelTime() + GetUserTime());
	return (int)fCpuIdle; 
}

uint64 CApiWinCpu::GetIdleTime() const
{
	return _xTimeNow.uTimeIdle - _xTimeOld.uTimeIdle;
}

uint64 CApiWinCpu::GetKernelTime() const
{
	return _xTimeNow.uTimeKernel - _xTimeOld.uTimeKernel;
}

uint64 CApiWinCpu::GetUserTime() const
{
	return _xTimeNow.uTimeUser - _xTimeOld.uTimeUser;
}

#endif
