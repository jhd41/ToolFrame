#include "MSystem.h"

#include "ToolFrame.h"

#include "ToolFramePatch.h"

#include "IDataSession.h"

#include "ApiBoost.h"
#include "boost/asio/io_service.hpp"

#include "MDevice.h"

NS_TOOL_FRAME_BEGIN

//导入DataSession
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
	//全局性质的静态变量的初始化
	ToolFrame::ZeroVectorInt();
	ToolFrame::EmptyString();
	ToolFrame::GetVarCodeSignMap();
	ToolFrame::GetSearchDir();
	ToolFrame::GetFileIndex();
	ToolFrame::GetNowTimeString();

	//初始化
	ToolFrame::InitDirType();
	ToolFrame::InitSearchDir();		//搜索路径

	//系统级的初始化,初始化顺序非常重要
	ToolFrame::Srand();
	MLogExecutorCreater::Singleton();
	MLoger::Singleton();
	MMemory::Singleton();
	MThread::Singleton();

	//协议管理器
	ApiBoost::GetGlobeIoService();
	MProtocol::Singleton();

	if (!InitDataSessionNetTcp())return false;
	if (!InitDataSessionNetUdp())return false;
	if (!InitDataSessionMemory())return false;

	//为ToolFrame打补丁
	if (false)InitToolFramePatch();//将那些弱链接的obj链接进来

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

	//自身初始化
	SetCleanUpSystemTime(300000);

	MDevice::Singleton().Init();

	MProtocol::Singleton().StartUp();

	//回调上层
	if (_hHandler && !_hHandler->OnSystemInit())return false;

	GetEventTrigger().FireEvent(EVENT_TF_SYSTEM_INITED);
	return true;
}

bool MSystem::RunOnce( uint64 uTime )
{
	ASSERT_LOG_DEBUG_ERR(_bInit);
	
	bool bTimeOut = false;

	CTimeOut timeout(uTime);

	//处理事件
	bTimeOut |= _mEventTrigger.ProcessEvent(timeout.TimeRemaining());

	//处理URL
	_xUrlProcessor.ProcessOnce();

	//处理时间
	bTimeOut |= _vQueueTime.TestTimeOut(ToolFrame::GetNowTimeMill(), timeout.TimeRemaining());
	bTimeOut |= _vQueueTime.ProcessTimeOut(timeout.TimeRemaining());
	
	//处理协议
	bTimeOut |= MProtocol::Singleton().ProcessBalance(uTime);

	//循环回调
	ASSERT_LOG_ERROR(_mLoop.Loop());

	//回调上层
	if (_hHandler)
		_hHandler->OnSystemProcess(timeout.TimeRemaining());

	//异步清理 防止递归引起崩溃
	if (IsTimeBarCleanUp())
	{
		_vQueueTime.ClearEmptyTimebar();		//清除空的无效时间条

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
	//清理时间条
	SetTimeBarCleanUp(true);

	//内存不足时
	if (GetMemoryWarningLess() >= ToolFrame::GetProcessMemoryFree())
	{
		if (_hHandler)
			_hHandler->OnSystemMemoryLow();

		GetEventTrigger().FireEvent(EVENT_TF_SYSTEM_MEMORY_LOW);

		//清理系统
		SetSystemCleanUp(true);
	}

	return true;
}

bool MSystem::OnSystemCleanUp()
{
	if (_hHandler && !_hHandler->OnSystemCleanUp())return false;

	MMemory::Singleton().ReleaseMemory();	//释放内存池里的无效内存
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