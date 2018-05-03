#pragma once

#include "Macro.h"
#include "TimeElapse.h"

//�����Ƿ�ʱ

NS_TOOL_FRAME_BEGIN

class CTimeOut
{
public:
	virtual uint64	ReStart();							//���¼�ʱ(�������һ�μ�ʱ���)
	virtual bool	IsTimeOut()const;					//�Ƿ�ʱ
	virtual bool	IsTimeOutMill(uint64 uTimeNow)const;//�Ƿ�ʱ
	virtual bool	IsTimeOutMill(uint64 uTimeNow,uint64 uInterval)const;	//�Ƿ�ʱ
	virtual bool	IsTimeOutSec(time_t uTimeNow)const;	//�Ƿ�ʱ
	virtual bool	IsTimeOutSec(time_t uTimeNow,time_t uInterval)const;	//�Ƿ�ʱ
	

	virtual uint64	TimeRemaining()const;				//ʱ��ʣ��

	virtual bool	IsNeverTimeout()const;				//�Ƿ�������ʱ
	virtual bool	IsNeverTimeout(uint64 uInterval)const;//�Ƿ�������ʱ

	virtual bool	SetIntervalMill(uint64 uInterval);	//����ʱ����(����)
	virtual uint64	GetIntervalMill()const;				//��ȡ���ʱ��

	virtual bool	SetIntervalSec(time_t uInterval);	//����ʱ����(��)
	virtual time_t	GetIntervalSec()const;				//��ȡ���ʱ��(��)

	virtual bool	IsVaild()const;						//�Ƿ���Ч
	virtual bool	SetVaild(bool bVaild);				//������Ч���

	virtual bool	TryTimeOutRestart();					//��ʱʱ �������ã���δ��ʱ ����false
public:
	CTimeOut();
	CTimeOut(uint64 uTime);	//����ʱ����(0Ϊ����ʱ�� ������ʱ ���ע��)
	virtual ~CTimeOut(void);
private:
	CTimeElapse	_tElapse;	//ʱ������
	uint64		_uInterval;	//��ʱʱ��
	bool		_bVaild;	//��Ч���
};

NS_TOOL_FRAME_END
