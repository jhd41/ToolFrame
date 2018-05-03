#pragma once
#include "Macro.h"

#include "IThreadNew.h"
#include "ThreadGroup.h"
#include "TimeOut.h"
#include "AvgCounter.h"

//�����߳�
//��ע:���һ���Զ����ڵ�ǰ�߳��� ����Ӧ��ǰϵͳ���ࡣ
//��ҪĿ��Ϊ �������߳������ܹ����ɵķ����̶߳�� ���ﵽ�Ż�ϵͳ��Ŀ�ġ�
//���˼·���������߳�����ִ�г�ʱʱ���·����µ��̡߳������ڴ���δ��ʱ״̬ʱ��������߳�

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL HElasticThread
{
public:
	virtual bool OnElasticThreadStarted(){return false;}			//�����߳�����ʱ
	virtual bool OnElasticThreadStoped(){return false;}				//�����߳�ֹͣʱ
	
	virtual bool OnElasticRuned(uint64 uTimeUsed,bool bTimeOut){return false;}	//��������ʱ��
	virtual bool OnElasticTimeOut(uint64 uTimeElapsed){return false;}	//���г�ʱ(���ڵ���OnElasticRuned����ñ�����)
	virtual bool OnRunElasticThread(){return false;}					//ִ�е����̣߳������Ƿ�ʱ
public:
	HElasticThread(){}
	virtual ~HElasticThread(){}
};

class TOOLFRAME_DLL CElasticThreadProcesser;
class TOOLFRAME_DLL CElasticThreadManager
{
public:
	virtual bool SetHandler(HElasticThread* hHandler);
	virtual bool SetTimeRecycle(uint uTimeOut);			//���ÿ���ʱ�����߳�ʱ��(��) Ĭ��300
	virtual bool SetTimeCheck(uint uTimeSpace);			//���ü��ʱ������(����ͻȻ ��ܶ࣬ͻȻ�ͷźܶ�) Ĭ��3000����
	virtual bool SetThreadTimeInterval(uint uTimeInterval);//�̵߳�������ʱ����
public:
	virtual bool AddElasticThread(uint uTimeInterval=50);//����һ�������߳�
	virtual bool RecycleElasticThread();
	virtual bool RunElasticThread();
	virtual bool Stop();
	virtual size_t Count()const;
	virtual uint64 GetRunTimeAvg()const;
	virtual uint64 GetRunTimeMax()const;
	virtual bool CheckElastic();
	
	//�ڲ�����
public:
	virtual bool OnThreadStarted(CElasticThreadProcesser* pThread);
	virtual bool OnThreadStoped(CElasticThreadProcesser* pThread);
public:
	CFIELD_UINT(ThreadMax);			//�߳�����
public:
	CElasticThreadManager(void);
	virtual ~CElasticThreadManager(void);
public:
	HElasticThread* _hHandler;
	CThreadGroup	_vThread;
	bool			_bStarting;			//�����������߳�
	CTimeOut		_xTimeRecycle;		//��ʱ����
	CTimeOut		_xTimeCheck;		//���ʱ����
	uint			_uThreadTimeInterval;//�̵߳�������ʱ����
	uint64			_uRunTimeAvg;		//ƽ����������ʱ��
	uint64			_uRunTimeMax;		//���������ʱ��
	CMutexReadWrite	_mutex;

	CAvgCounter		_xRunTime;			//����ͳ��
};

//////////////////////////////////////////////////////////////////////////
class CElasticThreadProcesser
	:public IThreadNew
{
public:
	virtual bool SetManager(CElasticThreadManager* pMgr);
public:
	virtual	bool InitThread();
	virtual bool RunOnceThread();
	virtual bool OnThreadStoped();
public:
	CElasticThreadProcesser();
	virtual ~CElasticThreadProcesser();
private:
	CElasticThreadManager* _pMgr;
};

NS_TOOL_FRAME_END