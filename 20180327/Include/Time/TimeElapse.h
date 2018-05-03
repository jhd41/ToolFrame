#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

//����ʱ��(�̰߳�ȫ)

NS_TOOL_FRAME_BEGIN

class CTimeElapse
{
public:
	virtual uint64	ReStart();			//���¿�ʼ��ʱ(����֮ǰ������ʱ��)
	virtual uint64	TimeElapsed()const;	//ʱ���Ѿ�����
	virtual uint64	TimeElapsed(uint64 uTimeNow)const;
	virtual uint64	GetTimeBegin()const;//��ȡ����ʱ��
	virtual bool	IsVaild()const;		//�Ƿ���Ч
	virtual bool	SetVaild(bool bVaild);

	virtual bool	SetTimeBegin(uint64 uTimeBegin);//������ʼʱ��

	//����
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
