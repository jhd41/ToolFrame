#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"

//�̻߳���

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL IThread
{
	//���̰߳�ȫ(����ǰ����)
public:
	virtual bool AutoRelease();		//�Զ��ͷ�(�̵߳��ý�������Զ��ͷ�)�� �߳�δ���� ���ᱻ�ͷ�
	virtual bool Release();			//�ͷ�(��� �߳��Ѿ����� �� ����ͷ� ��� �߳���ֹͣ ��ֱ���ͷ�)
public:
	virtual bool StartThread();		//�����߳�
	virtual bool StopThread();		//ֹͣ�߳�(�߳��˳���ŷ���)
	virtual bool ReqStopThread()=0;	//����ֹͣ�߳�(���������˱��)
public:
	virtual	bool InitThread()=0;
	virtual bool RunOnceThread()=0;
public:
	virtual bool IsThreadStarting()const;
	virtual bool IsThreadStarted()const;
	virtual	bool IsThreadStoped()const;
	virtual bool IsAutoRelease()const;
protected:
	virtual	bool SetThreadStarted();
	virtual	bool SetThreadStoped();
	virtual bool ClearThreadStoped();
protected:
	virtual bool OnThreadStoped();			//�߳̽���ʱ����
public:
	IThread(void);
	virtual ~IThread(void);
private:
	volatile bool	_bThreadStarting;	//�߳�������
	volatile bool	_bThreadStarted;	//�߳�������
	volatile bool	_bThreadStoped;		//�߳��ѹر�
	volatile bool	_bAutoRelease;		//����Զ��ͷ�
	mutable CMutexReadWrite _mThreadMutex;
};
NS_TOOL_FRAME_END
