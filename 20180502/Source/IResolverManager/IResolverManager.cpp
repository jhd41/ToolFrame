#include "IResolverManager.h"

#include "MLoger.h"
#include "MSystem.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN
bool HResolverManager::OnResolveTimeOut(IResolverManager* pMgrResolver, const CTimeNodePtr& pTimeNode)
{
	return pMgrResolver->ResolveTimeOut(pTimeNode);
}

bool HResolverManager::OnResolveOver(IResolverManager* pMgrResolver)
{
	return true;
}

bool HResolverManager::OnResolveErrTimeOut(IResolverManager* pMgrResolver, IResolver* pAc)
{
	return true;
}

bool HResolverManager::OnResolveErrLoop(IResolverManager* pMgrResolver, IResolver* pAc)
{
	return true;
}

bool HResolverManager::OnResolveErrOutOfSize(IResolverManager* pMgrResolver, IResolver* pAc)
{
	return true;
}

bool HResolverManager::OnResolveErrEmpty(IResolverManager* pMgrResolver, IResolver* pAc)
{
	return true;
}

bool HResolverManager::OnResolveErrProcessTimeOut(IResolverManager* pMgrResolver, IResolver* pAc)
{
	ASSERT_LOG_ERROR(pMgrResolver && pAc);

	pMgrResolver->MarkResolveOver();
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool HResolverManagerLog::OnResolveErrTimeOut(IResolverManager* pMgrResolver, IResolver* pAc)
{
	ASSERT_LOG_ERROR(pMgrResolver && pAc);

	LOG_ERROR_MSG("OnResolveErrTimeOut:" << ToolFrame::GetTypeName(pAc) << ":" << pAc->GetResolve());
	return true;
}

bool HResolverManagerLog::OnResolveErrLoop(IResolverManager* pMgrResolver, IResolver* pAc)
{
	ASSERT_LOG_ERROR(pMgrResolver && pAc);

	LOG_ERROR_MSG("OnResolveErrLoop:" << ToolFrame::GetTypeName(pAc) << pAc->GetResolve());
	return true;
}

bool HResolverManagerLog::OnResolveErrOutOfSize(IResolverManager* pMgrResolver, IResolver* pAc)
{
	ASSERT_LOG_ERROR(pMgrResolver && pAc);

	LOG_ERROR_MSG("OnResolveErrOutOfSize：" << ToolFrame::GetTypeName(pAc) << pMgrResolver->GetResolverSize() << " Limit:" << pMgrResolver->GetResolverSizeMax());
	return true;
}

bool HResolverManagerLog::OnResolveErrEmpty(IResolverManager* pMgrResolver, IResolver* pAc)
{
	ASSERT_LOG_ERROR(pMgrResolver);

	LOG_ERROR_MSG("OnResolveErrEmpty:" << ToolFrame::GetTypeName(pAc));
	return true;
}

bool HResolverManagerLog::OnResolveErrProcessTimeOut(IResolverManager* pMgrResolver, IResolver* pAc)
{
	HResolverManager::OnResolveErrProcessTimeOut(pMgrResolver, pAc);

	ASSERT_LOG_ERROR(pMgrResolver);

	LOG_ERROR_MSG("OnResolveErrProcessTimeOut:" << ToolFrame::GetTypeName(pAc)<<" Resolve:"<< pAc->GetResolve());
	return true;
}

//////////////////////////////////////////////////////////////////////////
IResolverManager::IResolverManager(void)
{
	_uResolverSizeMax = 50;
	_bProcessNeverTimeout = ToolFrame::IsDebugVer();

	_pUserPtr		= nullptr;
	_hHandler		= nullptr;
	_bResolveOver	= false;
	_bCallBackOver  = false;

	_xLocalTimeOutQueue.SetInterface(TIME_MODE_SEQ);

	SetHandler(this);
	SetWaiting(false);
	SetCheckResolve(true);
}

IResolverManager::~IResolverManager(void)
{
	RemoveTimer();

	//卸载所有本类创建的结算器(每次卸载第一个 因为卸载会引起容器内部变化)
	if (!_vResolver.empty())
	{
		bool bDeleted = false;
		
		do
		{
			bDeleted = false;
			VectorResolver::iterator itr;
			foreach(itr, _vResolver) {
				IResolver* pResolver = *itr;
				ASSERT_LOG_ERROR(pResolver);

				if (pResolver->IsManagerCreate()) {
					bDeleted = true;
					DestoryResolver(pResolver);
					break;
				}
			}
		} while (bDeleted);
	}
}

bool IResolverManager::PushResolver( IResolver* pAction,IResolver* pParent,bool bReset /*= true*/ )
{
	if (!pAction)return false;
	if (pAction->GetHandler())return false;//同一个结算器只能被添加一次

	pAction->SetHandler(this);
	pAction->SetRemoved(false);
	pAction->SetResolverMgr(this);
	pAction->SetParent(pParent);
	ToolFrame::PushBack(_vResolver,pAction);
	if (bReset)
		pAction->ResetResolve();

	//容量出错
	if (_hHandler && _vResolver.size() >= _uResolverSizeMax)
		_hHandler->OnResolveErrOutOfSize(this, pAction);
	return true;
}

bool IResolverManager::RemoveResolver(IResolver* pAction)
{
	if (!ToolFrame::EraseByValue(_vResolver,pAction,true))return false;
	pAction->SetHandler(nullptr);
	pAction->SetRemoved(true);
	return true;
}

IResolver* IResolverManager::FindTopResolver()const
{
	return ToolFrame::GetBackPtr(_vResolver);
}

IResolver* IResolverManager::FindRootResolver() const
{
	return ToolFrame::GetFrontPtr(_vResolver);
}

bool IResolverManager::OnTimeOut( const CTimeNodePtr& pTimeNode )
{
	_hHandler->OnResolveTimeOut(this,pTimeNode);
	return true;
}

bool IResolverManager::Process( uint64 uMillSeconds )
{
	if (_bProcessNeverTimeout)
		uMillSeconds = 0;

	//执行
	{
		CTimeOut timeOut(uMillSeconds);
		while (!timeOut.IsTimeOut()) {
			if (ProcessOne(uMillSeconds))return true;
		}
	}

	//若还没有被处理完
	if (_hHandler) {
		_hHandler->OnResolveErrProcessTimeOut(this, ToolFrame::GetBackPtr(_vResolver));
	}

	return false;
}

bool IResolverManager::RemoveTimer()
{
	if (!_pGlobalTimer)return true;

	GetGlobalTimeOutQueue()->RemoveTimer(_pGlobalTimer);
	ToolFrame::SetPtrNull(_pGlobalTimer);
	return true;
}

bool IResolverManager::DestoryResolver( IResolver* pResolver)
{
	ASSERT_LOG_ERROR(pResolver);
	delete pResolver;
	return true;
}

bool IResolverManager::Close()
{
	RemoveTimer();
	return true;
}

bool IResolverManager::IsEmpty() const
{
	return _vResolver.empty();
}

size_t ToolFrame::IResolverManager::GetResolverSize() const
{
	return _vResolver.size();
}

bool IResolverManager::SetUserPtr(void* pUserPtr)
{
	_pUserPtr = pUserPtr;
	return true;
}

bool IResolverManager::ProcessOne( uint64 uMillSeconds /*= 0*/ )
{
	if (IsProcessed())return true;

	//如果结算已经完成
	if (IsResolveOver())
	{
		//回调结束
		if (_bCallBackOver)
		{
			_bCallBackOver = false;
			CallBackResolveOver();
			//回调结束后不要执行任何代码
			return true;
		}
	}
	else
	{
		//结算器为空
		if (_vResolver.empty())
		{
			MarkResolveOver();
		}
		else
		{
			//结算
			IResolver* pAc = FindTopResolver();
			ASSERT_LOG_ERROR(pAc);

			if (pAc->IsResolveOver())
			{
				pAc->SetResolving(false);

				bool bManagerCreate = pAc->IsManagerCreate();
				pAc->OnResolveOver();

				//修复结束
				if (_vResolver.size() <= 1 && !IsResolveOver())
				{
					MarkResolveOver();
					if (_hHandler)
						_hHandler->OnResolveErrEmpty(this, pAc);
				}

				RemoveResolver(pAc);
				if (bManagerCreate)
					DestoryResolver(pAc);
			}
			else
			{
				//记录结算前的阶段
				int nResolveBefore = pAc->GetResolve();
				SetCheckResolve(true);

				if (!pAc->IsResolving())
				{
					pAc->SetResolving(true);
					pAc->OnResolveBegin();
				}

				//结算
				pAc->OnResolve();

				//如果阶段没有改变又没等待的话 则认为死循环出错了
				if (_hHandler && IsCheckResolve() && nResolveBefore == pAc->GetResolve() && !IsWaiting() && !IsResolveOver())
					_hHandler->OnResolveErrLoop(this, pAc);
			}
		}
	}

	return IsProcessed();
}

bool IResolverManager::IsProcessed() const
{
	//写上没有处理完的情况
	if (IsResolveOver())
	{
		if (_bCallBackOver)
			return false;
	}
	else {
		if (!IsWaiting())return false;
	}

	return true;
}

bool IResolverManager::ResolveTimeOut(const CTimeNodePtr& pTimeNode)
{
	if (_pGlobalTimer == pTimeNode)
		return TimeOut();
	return false;
}

bool IResolverManager::TimeOut()
{
	if (!IsWaiting())return false;
	if (IsResolveOver())return false;

	ClearWait();

	IResolver* pAc = FindTopResolver();
	ASSERT_LOG_ERROR(pAc);

	if (!pAc->OnTimeOut())
	{
		if (_hHandler)
			_hHandler->OnResolveErrTimeOut(this, pAc);
	}
	
	Process();
	
	return true;
}

bool IResolverManager::LocalPause()
{
	return GetLocalTimeOutQueue()->Pause();
}

bool IResolverManager::LocalResume()
{
	return GetLocalTimeOutQueue()->Resume();
}

uint64 IResolverManager::LocalSetTimeNow( uint64 uTimeNow )
{
	return GetLocalTimeOutQueue()->SetModeTimeNow(uTimeNow);
}

uint64 IResolverManager::LocalGetTimeNow() const
{
	return GetLocalTimeOutQueue()->GetModeTimeNow();
}

bool IResolverManager::LocalTimeProcess( uint64 uMillSeconds /*= 0*/ )
{
	CTimeOut timeOut(uMillSeconds);
	while (!timeOut.IsTimeOut())
	{
		//如果都没有超时，代表处理完了
		bool bProcessed = true;
		bProcessed &= GetLocalTimeOutQueue()->ProcessTestTimeOut(timeOut.TimeRemaining());
		bProcessed &= GetLocalTimeOutQueue()->ProcessTimeOut(timeOut.TimeRemaining());

		if (bProcessed)
			return true;
	} 

	return false;
}

CTimeOutQueue* IResolverManager::GetLocalTimeOutQueue() 
{
	return &_xLocalTimeOutQueue;
}

const CTimeOutQueue* IResolverManager::GetLocalTimeOutQueue() const
{
	return &_xLocalTimeOutQueue;
}

CTimeOutQueue* IResolverManager::GetGlobalTimeOutQueue()
{
	return &MSystem::Singleton().GetTimeOutQueque();
}

const CTimeOutQueue* IResolverManager::GetGlobalTimeOutQueue() const
{
	return &MSystem::Singleton().GetTimeOutQueque();
}

bool IResolverManager::WaitSeconds( int nSeconds )
{
	return WaitMillSec((uint64)nSeconds*1000);
}

bool IResolverManager::WaitSeconds( float fSeconds )
{
	fSeconds *= 1000;
	return WaitMillSec((uint64)fSeconds);
}

bool IResolverManager::WaitForever()
{
	if (IsWaiting())return false;
	SetWaiting(true);
	return true;
}

bool IResolverManager::WaitMillSec(uint64 uMillSec)
{
	if (IsWaiting())return false;
	SetWaiting(true);

	ASSERT_LOG_ERROR(!_pGlobalTimer);
	_pGlobalTimer = GetGlobalTimeOutQueue()->CreateTimerByAfterMil(this, uMillSec);
	return true;
}

bool IResolverManager::ClearWait()
{
	RemoveTimer();
	SetWaiting(false);
	return true;
}

bool IResolverManager::IgnoreCheckResolve()
{
	return SetCheckResolve(false);
}

bool IResolverManager::CallBackResolveOver()
{
	RemoveTimer();
	if (_hHandler)
		_hHandler->OnResolveOver(this);
	return true;
}

bool IResolverManager::OnResolverCreate( IResolver* pResolver )
{
	return true;
}

bool IResolverManager::OnResolverDestory( IResolver* pResolver )
{
	if (!pResolver->IsRemoved())
		ToolFrame::EraseByValueAll(_vResolver,pResolver);
	return true;
}

bool IResolverManager::OnResolverResetResolve( IResolver* pResolver )
{
	return true;
}

bool IResolverManager::SetHandler( HResolverManager* hHandler )
{
	_hHandler = hHandler;
	return true;
}

bool IResolverManager::SetResolverSizeMax(uint uResolverSizeMax)
{
	_uResolverSizeMax = uResolverSizeMax;
	return true;
}

bool IResolverManager::SetProcessNeverTimeout(bool bNeverTimeOut /*= true*/)
{
	_bProcessNeverTimeout = bNeverTimeOut;
	return true;
}

bool IResolverManager::MarkResolveOver()
{
	if (_bResolveOver)
		return false;
	_bResolveOver = true;
	_bCallBackOver = true;
	return true;
}

bool IResolverManager::IsResolveOver() const
{
	return _bResolveOver;
}

size_t ToolFrame::IResolverManager::GetResolverSizeMax() const
{
	return _uResolverSizeMax;
}

NS_TOOL_FRAME_END
