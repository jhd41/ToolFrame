#pragma once

//˼·:����ΪToolFrameϵͳ������.
//���� ��ʱ����,�¼�ϵͳ �ڴ���� ��־���� ��ϵͳ�����ݡ�

#include "Macro.h"

#include "TimeOutQueue.h"
#include "EventTrigger.h"
#include "LoopManager.h"
#include "HSystem.h"

#include "IAnyObj.h"
#include "TObjCreator.h"

#include "MLoger.h"
#include "MMemory.h"
#include "MThread.h"
#include "MSystem.h"
#include "MProtocol.h"

//ϵͳ�����ۺ���
//�����κ�ToolFrame����ǰ �����ȳ�ʼ�� MSystem.�ڲ��ѿ�������˳������
//AnyObjCreator ���� �ⲿ ϵͳ������Ҫ�ͷŵ������ͷŹ�����

//��Ҫͨ���̳еķ�ʽ��ʼ��MSystem��ֻ��Ҫ �̳�ISystemInit �Ϳ��ԣ����ÿ�������˳��

//ϵͳ�¼�:
static std::string EVENT_TF_SYSTEM_INITED		= "EVENT_TF_SYSTEM_INITED";		//[ϵͳ]��ʼ��
static std::string EVENT_TF_SYSTEM_NET_CHANGE	= "EVENT_TF_SYSTEM_NET_CHANGE";	//[ϵͳ]�����л�
static std::string EVENT_TF_SYSTEM_MEMORY_LOW	= "EVENT_TF_SYSTEM_MEMORY_LOW";	//[ϵͳ]�ڴ��
static std::string EVENT_TF_SYSTEM_CLEAN_UP		= "EVENT_TF_SYSTEM_CLEAN_UP";	//[ϵͳ]�ڴ�����

NS_TOOL_FRAME_BEGIN

class ISystemCall
{
public:
	bool Init();
	bool Destory();
public:
	ISystemCall();
	~ISystemCall();
};

class ISystem
{
public:
	ISystem(){}
	virtual ~ISystem(){}
private:
	ISystemCall _xSystemCall;
};

//////////////////////////////////////////////////////////////////////////
class TOOLFRAME_DLL MSystem
	:public ISystem
	,public HTimeOut
{
	typedef TObjCreator<IAnyObj> AnyObjCreator;
public:
	ST_INTANCE(MSystem);
public:
	bool		SetHandler(HSystem* pHandler);
	bool		SetCleanUpSystemTime(UINT64 uTime);				//��������ϵͳʱ��
	bool		SetCleanUpAllProcess(bool bAllProcess = true);	//�����������н���
	bool		Init();
	bool		RunOnce(uint64 uTime = 300);					//����һ�� �����Ƿ����ʱ
	bool		Run();											//����(���� ������)
	bool		ReqStop();										//����ֹͣ
public:
	time_t		GetLastCleanTime()const;						//������һ������ʱ��
	bool		IsReqStop() const;
public:
	CTimeOutQueue&	GetTimeOutQueque();
	CEventTrigger&	GetEventTrigger();
	CLoopManager&	GetLoopMgr();
	AnyObjCreator&	GetAnyObjCreator();

	MThread&		GetThread();
	MLoger&			GetLoger();
	MMemory&		GetMemory();
	MProtocol&		GetProtocol();
private:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode);
private:
	bool		OnSystemCleanUp();
	bool		RemoveTimer();
public:
	MSystem(void);
	virtual ~MSystem(void);
private:
	CFIELD_UINT64(MemoryWarningLess);	//�ڴ治�㾯��ֵ
	CFIELD_BOOL(SystemCleanUp);			//��Ҫ����ı��(Ϊ�˷�ֹ�ݹ�)
	CFIELD_BOOL(TimeBarCleanUp);		//ʱ����������(Ϊ�˷�ֹ�ݹ�)
private:
	bool			_bInit;
	volatile bool	_bReqStop;

	CTimeOutQueue	_vQueueTime;	//��ʱ����
	CEventTrigger	_mEventTrigger;	//�¼�������
	CLoopManager	_mLoop;			//ѭ��������
	
	CTimeNodePtr	_pTimer;

	HSystem*		_hHandler;
	bool			_bAllProcess;
	time_t			_tLastCleanTime;//���һ������ʱ��

	AnyObjCreator	_vObjCreator;	//����Obj������ Ҫ��������һ��
};

//////////////////////////////////////////////////////////////////////////
class ISystemInitCall
{
public:
	ISystemInitCall() {
		MSystem::Singleton();
	}
	~ISystemInitCall() {

	}
};

class ISystemInit
{
public:
	ISystemInit(){}
	virtual ~ISystemInit(){}
private:
	ISystemInitCall _xInitSystem;
};


NS_TOOL_FRAME_END
