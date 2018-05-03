#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"
#include "TimeElapse.h"

//����ʱ��(�̰߳�ȫ)

NS_TOOL_FRAME_BEGIN

class CTimeElapseEx
{
public:
	virtual uint64	ReStart();			//���¿�ʼ��ʱ(����֮ǰ������ʱ��)
	virtual uint64	TimeElapsed()const;	//ʱ���Ѿ�����
	virtual uint64	TimeElapsed(uint64 uTimeNow)const;
	
	virtual bool	Pause();			//��ͣ
	virtual bool	Resume();			//�ָ�
	virtual bool	IsPausing()const;	//�Ƿ�����ͣ��

	virtual bool	SetTimeBegin(uint64 uTimeBegin);//������ʼʱ��
public:
	CTimeElapseEx(void);
	virtual ~CTimeElapseEx(void);
private:
	uint64		_uTimeElapse;	//����ʱ��
	uint64		_uPauseElapse;	//��ͣʱ��
	bool		_bPause;		//��ͣ��

	CTimeElapse _xTimeElapse;	//ʱ������

	mutable CMutexReadWrite _mutex;
};

NS_TOOL_FRAME_END
