#pragma once
#include "ElasticThreadManager.h"
#include "TaskThreadManager.h"

//�̹߳�����:
//���������߳�
//1.IThread:	�߳�		����ʵ����һ��ȫ�µ��߳�
//2.IThreadTask:�߳�����	����ӵ�������� ʹ�ñ������õ��̻߳���ִ�� �Դﵽ���������߳�������Ŀ��

//��ע:���˼· ����Ϊ�˼�������ϵͳ�̸߳��������ڣ�ϣ����ÿ����Ҫ�߳�ִ�е����� �ܹ� �����ٵ������̣߳������װ������ķ�ʽ �������߳������С�
//���� ԭ�Ȼ���4�������̣߳�4���߼��̣߳���������8�̡߳������ֻ��Ҫ��4�̣߳�ͬʱִ������������߼����񼴿ɡ�
//������߳���������Ӧ�þ��������������д��������ҵ���ȣ�4�߳�����2������ҵ�̣߳�2������ҵ�̡߳�
//���ǵ�ĿǰΪֹ����ʱû������������δ�������Ż��ɡ�


NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL MThread
{
	ST_INTANCE(MThread);
public:
	bool AddThread(IThread* pThread);			//���һ���߳�
	bool RemoveThread(IThread* pThread);		//�Ƴ�һ���߳�
	bool Stop();
public:
	CElasticThreadManager&	GetElasticMgr();	//�����߳�
	CTaskThreadManager&		GetTaskMgr();		//�����߳�
public:
	MThread(void);
	virtual ~MThread(void);
private:
	CElasticThreadManager	_mgrElastic;	//�����߳�
	CTaskThreadManager		_mgrTask;		//�����߳�
	CThreadGroup			_vThread;		//���е��߳�
};

NS_TOOL_FRAME_END
