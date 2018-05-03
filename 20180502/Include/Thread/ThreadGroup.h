#pragma once
#include "Macro.h"
#include "TThreadSaftyList.h"
#include "IThread.h"
#include "TObjCreator.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL CThreadGroup
{
	//�����߳��б�
	typedef TThreadSaftyListValue<IThread*>	ListThread;
	typedef TObjCreator<IThread>			CThreadCreator;

	//��������
public:
	bool	AddThread(IThread* pThread);
	bool	RemoveThread(IThread* pThread);

	template<typename T>
	T*		CreateThread();						//����һ���߳�
	bool	ReleaseThread(IThread* pThread);	//�ͷ��߳�

	//��������
public:
	bool	StartThread();
	bool	StopThread();			//ֻ�е������̶߳��˳���Ż᷵��
	bool	RemoveThread();
	bool	IsAllThreadStoped()const;
	bool	IsEmpty()const;			//�Ƿ�û���߳�
	size_t	GetCount()const;		//��ȡ�߳���
	IThread* GetFrontThread();		//��ȡ��һ���߳�(�ⲿע���߳�ͬ������)
	IThread* GetBackThread();		//��ȡ���һ���߳�(�ⲿע���߳�ͬ������)

	bool	ReqStopFrontThread();	//����رյ�һ���߳�
	bool	ReqStopBackThread();	//����ر����һ���߳�

	bool	IsFrontThreadStarted()const;//��һ���߳��Ƿ���������
	bool	IsBackThreadStarted()const;	//���һ���߳��Ƿ���������

	bool	ReleaseFrontThread();	//ֹͣ���ͷŵ�һ���߳�
	bool	ReleaseBackThread();	//ֹͣ���ͷ����һ���߳�
protected:
	bool	ReqStopThread()const;
public:
	CThreadGroup(void);
	virtual ~CThreadGroup(void);
private:
	//�߳��б�
	ListThread			_vThread;	//�߳��б�
	CThreadCreator		_vCreator;	//������
};

template<typename T>
T* ToolFrame::CThreadGroup::CreateThread()
{
	T* pThread = _vCreator.CreateObj<T>();
	if (!pThread)return nullptr;
	AddThread(pThread);
	return pThread;
}

NS_TOOL_FRAME_END
