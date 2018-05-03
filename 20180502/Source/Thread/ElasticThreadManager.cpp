#include "ElasticThreadManager.h"
#include "MLoger.h"
#include "TimeElapse.h"

NS_TOOL_FRAME_BEGIN
CElasticThreadManager::CElasticThreadManager(void)
{
	_xTimeRecycle.SetIntervalSec(300);
	_xTimeCheck.SetIntervalMill(3000);
	SetThreadMax(0);

	_uThreadTimeInterval = 10;
	_uRunTimeAvg = 0;
	_uRunTimeMax = 0;
	_uRunTimes = 0;
	_fRunTimeOutRate = 0.f;
	_uRunElapsed = 0;
}

CElasticThreadManager::~CElasticThreadManager(void)
{
	Stop();
}

bool CElasticThreadManager::RecycleElasticThread()
{
	_vThread.ReleaseBackThread();
	return true;
}

bool CElasticThreadManager::OnThreadStarted(CElasticThreadProcesser* pThread)
{
	if (_hHandler)
		_hHandler->OnElasticThreadStarted();
	return true;
}

bool CElasticThreadManager::OnThreadStoped( CElasticThreadProcesser* pThread )
{
	if (_hHandler)
		_hHandler->OnElasticThreadStoped();
	return true;
}

bool CElasticThreadManager::Stop()
{
	return _vThread.StopThread();
}

size_t CElasticThreadManager::Count() const
{
	return _vThread.GetCount();
}

bool CElasticThreadManager::RunElasticThread()
{
	if (!_hHandler)return false;

	//执行函数
	CTimeElapse xTimeElapse;
	bool bTimeOut		= _hHandler->OnRunElasticThread();
	uint64 uTimeElapsed	=  xTimeElapse.TimeElapsed();
	
	//添加统计
	_xRunTime.AddCount(uTimeElapsed,bTimeOut);

	//进行回调
	_hHandler->OnElasticRuned(uTimeElapsed,bTimeOut);
	if (bTimeOut)
		_hHandler->OnElasticTimeOut(uTimeElapsed);

	CheckElastic();
	return bTimeOut;
}

bool CElasticThreadManager::SetTimeRecycle( uint uTimeOut )
{
	return _xTimeRecycle.SetIntervalSec(uTimeOut);
}

bool CElasticThreadManager::AddElasticThread( uint uTimeInterval/*=50*/ )
{
	{
		CLockRead lock(_mutex);

		if (!_vThread.IsEmpty() && !_vThread.IsBackThreadStarted())return false;
		if (_vThread.GetCount() >= GetThreadMax())return false;
	}

	//启动新线程
	CLockWrite lock(_mutex);
	if (!_vThread.IsEmpty() && !_vThread.IsBackThreadStarted())return false;
	if (_vThread.GetCount() >= GetThreadMax())return false;

	CElasticThreadProcesser* pThreadNew = _vThread.CreateThread<CElasticThreadProcesser>();
	ASSERT_LOG_ERROR(pThreadNew);
	pThreadNew->SetManager(this);
	pThreadNew->StartThread(uTimeInterval);
	return true;
}

bool CElasticThreadManager::SetHandler( HElasticThread* hHandler )
{
	_hHandler = hHandler;
	return true;
}

bool CElasticThreadManager::SetTimeCheck( uint uTimeSpace )
{
	return _xTimeCheck.SetIntervalMill(uTimeSpace);
}

bool CElasticThreadManager::CheckElastic()
{
	if (!_xTimeCheck.TryTimeOutRestart())return false;

	uint64 uOutTimeUsed=0;uint uRunOutTimes=0;
	_xRunTime.Clear(&_uRunElapsed,&_uRunTimes,&_uRunTimeMax,&_uRunTimeAvg,&uOutTimeUsed,&uRunOutTimes);
	_fRunTimeOutRate = 1.f* uOutTimeUsed / _uRunElapsed;//计算超时率

	//思路:首先对运行情况进行评估

	//超时总累计时间超过总使用时间的20%
	if (_uRunElapsed > 0 && (_fRunTimeOutRate >= 0.2f))
	{
		//重置回收时间
		_xTimeRecycle.ReStart();

		//添加线程
		AddElasticThread(_uThreadTimeInterval);
		return true;
	}

	//减少线程
	if (_xTimeRecycle.TryTimeOutRestart())
		RecycleElasticThread();

	return true;
}

uint64 CElasticThreadManager::GetRunOnceTimeAvg() const
{
	return _uRunTimeAvg;
}

bool CElasticThreadManager::SetThreadTimeInterval( uint uTimeInterval )
{
	_uThreadTimeInterval = uTimeInterval;
	return true;
}

uint64 CElasticThreadManager::GetRunOnceTimeMax() const
{
	return _uRunTimeMax;
}

uint64 CElasticThreadManager::GetRunTimes() const
{
	return _uRunTimes;
}

float CElasticThreadManager::GetRunTimeOutRate() const
{
	return _fRunTimeOutRate;
}

uint64 CElasticThreadManager::GetRunElapsed() const
{
	return _uRunElapsed;
}

//////////////////////////////////////////////////////////////////////////
CElasticThreadProcesser::CElasticThreadProcesser()
{
	_pMgr = nullptr;
}

CElasticThreadProcesser::~CElasticThreadProcesser()
{
}

bool CElasticThreadProcesser::SetManager( CElasticThreadManager* pMgr )
{
	_pMgr = pMgr;
	return true;
}

bool CElasticThreadProcesser::InitThread()
{
	_pMgr->OnThreadStarted(this);
	return true;
}

bool CElasticThreadProcesser::RunOnceThread()
{
	_pMgr->RunElasticThread();
	return true;
}

bool CElasticThreadProcesser::OnThreadStoped()
{
	_pMgr->OnThreadStoped(this);
	return true;
}

NS_TOOL_FRAME_END