#pragma once
#include "Macro.h"
#include "ElasticThreadManager.h"
#include "MSystem.h"

//����������,�����߳�(Ĭ�ϲ�����)

NS_TOOL_FRAME_BEGIN
class IServer
	:public ISystemInit
	,public HElasticThread
{
public:
	virtual bool	SetRunOnceSleep(uint uRunOnceSleep);//����ѭ��˯��ʱ��
public:
	virtual bool	Init();						//��ʼ��
	virtual	bool	RunOnce();					//���е���
public:
	virtual	bool	Run();						//ѭ������
	virtual bool	ShutDown();					//�ر�
	//����ʵ��
public:
	virtual bool	OnInitSucceed();			//��ʼ���ɹ�
	virtual bool	OnInitFaild();				//��ʼ��ʧ��
protected:
	virtual bool	OnRunElasticThread();		//ִ�е����̣߳������Ƿ�ʱ
public:
	IServer(void);
	virtual ~IServer(void);
protected:
	CTimeElapse				_xTimeServerStart;	//����������ʱ��
	CElasticThreadManager	_mgrElasticThread;
	uint					_uRunOnceSleep;		//����ѭ��˯��ʱ��
};
NS_TOOL_FRAME_END
