#include "MSystem.h"

#include "ToolFrame.h"

#include "ToolFramePatch.h"

#include "IDataSession.h"

#include "ApiBoost.h"
#include "boost/asio/io_service.hpp"

#include "MDevice.h"

NS_TOOL_FRAME_BEGIN

//����DataSession
bool InitDataSessionNetTcp();
bool InitDataSessionNetUdp();
bool InitDataSessionMemory();

ISystemCall::ISystemCall()
{
	Init();
}

ISystemCall::~ISystemCall()
{
	Destory();
}

bool ISystemCall::Init()
{
	//ȫ�����ʵľ�̬�����ĳ�ʼ��
	ToolFrame::ZeroVectorInt();
	ToolFrame::EmptyString();
	ToolFrame::GetVarCodeSignMap();
	ToolFrame::GetSearchDir();
	ToolFrame::GetFileIndex();
	ToolFrame::GetNowTimeString();

	//��ʼ��
	ToolFrame::InitDirType();
	ToolFrame::InitSearchDir();		//����·��

	//ϵͳ���ĳ�ʼ��,��ʼ��˳��ǳ���Ҫ
	ToolFrame::Srand();
	MLogExecutorCreater::Singleton();
	MLoger::Singleton();
	MMemory::Singleton();
	MThread::Singleton();

	//Э�������
	ApiBoost::GetGlobeIoService();
	MProtocol::Singleton();

	if (!InitDataSessionNetTcp())return false;
	if (!InitDataSessionNetUdp())return false;
	if (!InitDataSessionMemory())return false;

	//ΪToolFrame�򲹶�
	if (false)InitToolFramePatch();//����Щ�����ӵ�obj���ӽ���

	return true;
}

bool ISystemCall::Destory()
{
	MThread::Singleton().Stop();
	return true;
}

//////////////////////////////////////////////////////////////////////////

MSystem::MSystem(void)
{
	_bInit		= false;
	_bReqStop	= false;

	_bAllProcess= false;
	_hHandler	= nullptr;
	_tLastCleanTime = 0;
	
	SetSystemCleanUp(false);
	SetTimeBarCleanUp(false);
	SetMemoryWarningLess(50000000);//50MB
}

MSystem::~MSystem(void)
{
	RemoveTimer();
}

bool MSystem::Init()
{
	if (_bInit)return true;
	_bInit = true;

	//�����ʼ��
	SetCleanUpSystemTime(300000);

	MDevice::Singleton().Init();

	MProtocol::Singleton().StartUp();

	//�ص��ϲ�
	if (_hHandler && !_hHandler->OnSystemInit())return false;

	GetEventTrigger().FireEvent(EVENT_TF_SYSTEM_INITED);
	return true;
}

bool MSystem::RunOnce( uint64 uTime )
{
	ASSERT_LOG_DEBUG_ERR(_bInit);
	
	bool bTimeOut = false;

	CTimeOut timeout(uTime);

	//�����¼�
	bTimeOut |= _mEventTrigger.ProcessEvent(timeout.TimeRemaining());

	//����URL
	_xUrlProcessor.ProcessOnce();

	//����ʱ��
	bTimeOut |= _vQueueTime.TestTimeOut(ToolFrame::GetNowTimeMill(), timeout.TimeRemaining());
	bTimeOut |= _vQueueTime.ProcessTimeOut(timeout.TimeRemaining());
	
	//����Э��
	bTimeOut |= MProtocol::Singleton().ProcessBalance(uTime);

	//ѭ���ص�
	ASSERT_LOG_ERROR(_mLoop.Loop());

	//�ص��ϲ�
	if (_hHandler)
		_hHandler->OnSystemProcess(timeout.TimeRemaining());

	//�첽���� ��ֹ�ݹ��������
	if (IsTimeBarCleanUp())
	{
		_vQueueTime.ClearEmptyTimebar();		//����յ���Чʱ����

		SetTimeBarCleanUp(false);
	}
	if (IsSystemCleanUp())
	{
		OnSystemCleanUp();
		SetSystemCleanUp(false);
	}

	bTimeOut |= timeout.IsTimeOut();
	return bTimeOut;
}

bool MSystem::Run()
{
	if (!Init())return false;
	while (!_bReqStop) {
		RunOnce();
		ToolFrame::Sleep(10);
	}

	return true;
}

bool MSystem::ReqStop()
{
	_bReqStop = true;
	return true;
}

CTimeOutQueue& MSystem::GetTimeOutQueque()
{
	return _vQueueTime;
}

CEventTrigger& MSystem::GetEventTrigger()
{
	return _mEventTrigger;
}

CUrlProcessor& MSystem::GetUrlProcessor()
{
	return _xUrlProcessor;
}

bool MSystem::SetCleanUpSystemTime( UINT64 uTime )
{
	RemoveTimer();
	_pTimer = _vQueueTime.CreateTimerByAfterMil(this,uTime,true,uTime);
	return true;
}

bool MSystem::OnTimeOut( const CTimeNodePtr& pTimeNode )
{
	//����ʱ����
	SetTimeBarCleanUp(true);

	//�ڴ治��ʱ
	if (GetMemoryWarningLess() >= ToolFrame::GetProcessMemoryFree())
	{
		if (_hHandler)
			_hHandler->OnSystemMemoryLow();

		GetEventTrigger().FireEvent(EVENT_TF_SYSTEM_MEMORY_LOW);

		//����ϵͳ
		SetSystemCleanUp(true);
	}

	return true;
}

bool MSystem::OnSystemCleanUp()
{
	if (_hHandler && !_hHandler->OnSystemCleanUp())return false;

	MMemory::Singleton().ReleaseMemory();	//�ͷ��ڴ�������Ч�ڴ�
	ToolFrame::PurgeMemory( _bAllProcess ? -1:ToolFrame::GetProcessId());
	_tLastCleanTime = ToolFrame::GetNowTime();

	GetEventTrigger().FireEvent(EVENT_TF_SYSTEM_CLEAN_UP);
	return true;
}

CLoopManager& MSystem::GetLoopMgr()
{
	return _mLoop;
}

MSystem::AnyObjCreator& MSystem::GetAnyObjCreator()
{
	return _vObjCreator;
}

MProtocol& MSystem::GetProtocol()
{
	return MProtocol::Singleton();
}

MMemory& MSystem::GetMemory()
{
	return MMemory::Singleton();
}

MLoger& MSystem::GetLoger()
{
	return MLoger::Singleton();
}

MThread& MSystem::GetThread()
{
	return MThread::Singleton();
}

bool MSystem::RemoveTimer()
{
	return _vQueueTime.RemoveTimer(_pTimer);
}

bool MSystem::SetHandler( HSystem* pHandler )
{
	_hHandler = pHandler;
	return true;
}

bool MSystem::SetCleanUpAllProcess( bool bAllProcess )
{
	_bAllProcess = bAllProcess;
	return true;
}

time_t MSystem::GetLastCleanTime() const
{
	return _tLastCleanTime;
}

bool MSystem::IsReqStop() const
{
	return _bReqStop;
}

NS_TOOL_FRAME_END

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#include <jni.h>
extern "C"
{
	void Java_com_CloudCity_Lib_CToolFrameActivity_OnNetChange(JNIEnv* env, jobject thiz, jstring jEventName)
	{
		ToolFrame::MSystem::Singleton().GetEventTrigger().FireEvent(EVENT_TF_SYSTEM_NET_CHANGE);
	}
}

#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS
	void OnNetChange()
	{
		ToolFrame::MSystem::Singleton().GetEventTrigger().FireEvent(EVENT_TF_SYSTEM_NET_CHANGE);
	}
#endif