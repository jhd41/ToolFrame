#pragma once

#include "Macro.h"

//�����ȳ�ʼ����
//֮����Ҫ���ʱ��ȥ����Reflash����������֮������CPU�ĸ�������

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

	//��ȡ�����һ��ˢ�µ�������Ϣ
	uint64	GetIdleTime()const;		//��ȡ����״̬ʱ��
	uint64	GetKernelTime()const;	//��ȡ�ں�״̬ʱ��
	uint64	GetUserTime()const;		//��ȡ�û�״̬ʱ��
	int		CalCpuUsage()const;		//����CPU������
	int		CalCpuIdle()const;		//����CPU������
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
