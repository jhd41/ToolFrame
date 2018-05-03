#pragma once

#include "Macro.h"
#include "IThread.h"
#include "MacroDefineBoost.h"

//�߳�:
//�̳б���֮�� ��Ҫ��������ʵ������������.
//ʹ��StartThread֮��������ɵ�����һ���µ��߳�
//���������κλص���ʱ�� delete�����Ķ�����������Ҫɾ������ʹ��AutoRelease��Ǽ���

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IThreadNew
	:public IThread
{
public:
	virtual bool StartThread(uint uTimeInterval=50);
	virtual bool ReqStopThread();
	virtual bool IsReqStopThread()const ;
	virtual bool SetTimeInterval(uint uTimeInterval);	//����ѭ�����ʱ��
	virtual uint GetTimeInterval()const;				//��ȡѭ�����ʱ��
	virtual bool Interrupt();							//ǿ�ƴ��(���ۺ�������� ����Ӧ���øú���)
	virtual bool ReqInterrupt();						//������
	virtual bool InterruptPoint();						//���ô�ϵ� �������˴�� ��� ��ϵ�ǰ�߳�
	virtual bool IsReqInterrupt()const;					//�Ƿ�������
	virtual bool IsInterrupted()const;					//�Ƿ��ѱ����
public:
	virtual bool OnInterrupted();						//�̴߳��ʱ
private:
	void RunThread();
public:
	IThreadNew(void);
	virtual ~IThreadNew(void);
private:
	volatile bool	_bReqStop;
	volatile bool	_bReqInterrupt;
	volatile bool	_bInterrupted;
	uint			_uTimeInterval;
	boost::thread*	_pThread;
};

class CExceptionThreadInterrupt
{
public:
	CExceptionThreadInterrupt(){}
	~CExceptionThreadInterrupt(){}
};
NS_TOOL_FRAME_END
