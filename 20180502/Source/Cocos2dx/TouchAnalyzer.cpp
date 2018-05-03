#include "TouchAnalyzer.h"

#ifdef MACRO_LIB_COCOS2D

#include "ApiCocos2dx.h"
#include "TouchListener.h"
#include "MSystem.h"

#include "ToolFrame.h"

//////////////////////////////////////////////////////////////////////////
ITouchAnalyzer::ITouchAnalyzer(void)
{
	_bEnabled = false;
	_bActive = false;
	_pTouchLister = nullptr;
	_bEnterState = false;
}

ITouchAnalyzer::~ITouchAnalyzer(void)
{
	StopTimer();
}

bool ITouchAnalyzer::OnTouchBegan( Touch* touch, Event *unusedEvent )
{
	return false;
}

bool ITouchAnalyzer::OnTouchMoved( Touch* touch, Event *unusedEvent )
{
	return false;
}

bool ITouchAnalyzer::OnTouchEnded( Touch* touch, Event *unusedEvent )
{
	return false;
}

bool ITouchAnalyzer::OnTouchCancelled( Touch* touch, Event *unusedEvent )
{
	return false;
}

bool ITouchAnalyzer::IsEnabled() const
{
	return _bEnabled;
}

CTouchListener* ITouchAnalyzer::GetTouchLister()
{
	return _pTouchLister;
}

bool ITouchAnalyzer::SetTouchLister( CTouchListener* pParent )
{
	_pTouchLister = pParent;
	return true;
}

bool ITouchAnalyzer::IsActive() const
{
	return _bActive;
}

bool ITouchAnalyzer::SetActive( bool bActive )
{
	if (_bActive == bActive)return false;

	_bActive = bActive;
	return true;
}

bool ITouchAnalyzer::StartTimer( uint uMillSecond )
{
	StopTimer();

	_pTimer = ToolFrame::MSystem::Singleton().GetTimeOutQueque().CreateTimerByAfterMil(this,uMillSecond);
	return true;
}

bool ITouchAnalyzer::StopTimer()
{
	if (!_pTimer)return true;

	ToolFrame::MSystem::Singleton().GetTimeOutQueque().RemoveTimer(_pTimer);
	ToolFrame::SetPtrNull(_pTimer);

	return true;
}

bool ITouchAnalyzer::OnTimeOut( const ToolFrame::CTimeNodePtr& pTimeNode )
{
	return true;
}

bool ITouchAnalyzer::TryIntoState()
{
	if (_bEnterState)return false;

	_bEnterState = true;
	return true;
}

bool ITouchAnalyzer::TryLeaveState()
{
	if (!_bEnterState)return false;

	_bEnterState = false;
	return true;
}

bool ITouchAnalyzer::IsEnterState() const
{
	return _bEnterState;
}

//////////////////////////////////////////////////////////////////////////
CTouchAnalyzerIdel::CTouchAnalyzerIdel( void )
{

}

CTouchAnalyzerIdel::~CTouchAnalyzerIdel( void )
{
}

bool CTouchAnalyzerIdel::OnTouchBegan( Touch* touch, Event *unusedEvent )
{
	SetActive(false);
	StopTimer();
	return true;
}

bool CTouchAnalyzerIdel::OnTouchMoved( Touch* touch, Event *unusedEvent )
{
	SetActive(false);
	StopTimer();
	return true;
}

bool CTouchAnalyzerIdel::OnTouchEnded( Touch* touch, Event *unusedEvent )
{
	const VectorTouch& vTouch = GetTouchLister()->GetTouches();
	SetActive(vTouch.empty());

	StopTimer();
	CheckIdle();
	return true;
}

bool CTouchAnalyzerIdel::OnTouchCancelled( Touch* touch, Event *unusedEvent )
{
	const VectorTouch& vTouch = GetTouchLister()->GetTouches();
	SetActive(vTouch.empty());

	StopTimer();
	CheckIdle();
	return true;
}

bool CTouchAnalyzerIdel::OnTimeOut( const ToolFrame::CTimeNodePtr& pTimeNode )
{
	StopTimer();
	GetTouchLister()->GetHandler()->OnTouchIdle(GetTouchLister()->GetNode());
	return true;
}

bool CTouchAnalyzerIdel::CheckIdle()
{
	if (!IsActive())return false;
	return StartTimer(3000);
}

//////////////////////////////////////////////////////////////////////////
CTouchAnalyzerDrag::CTouchAnalyzerDrag( void )
{

}

CTouchAnalyzerDrag::~CTouchAnalyzerDrag( void )
{

}

bool CTouchAnalyzerDrag::OnTouchBegan( Touch* touch, Event *unusedEvent )
{
	const VectorTouch& vTouch = GetTouchLister()->GetTouches();
	SetActive(vTouch.size() == 1);

	if (IsActive())
	{
		_ptBegin = ApiCocos2dx::GetWorldPostion(GetTouchLister()->GetNode());
	}
	return false;
}

bool CTouchAnalyzerDrag::OnTouchMoved( Touch* touch, Event *unusedEvent )
{
	if (IsActive() && !IsEnterState() && ApiCocos2dx::IsTouchBlur(touch))
		TryIntoState(touch,unusedEvent);
	if (IsActive() && IsEnterState())
		TryIntoState(touch,unusedEvent);

	return false;
}

bool CTouchAnalyzerDrag::OnTouchEnded( Touch* touch, Event *unusedEvent )
{
	SetActive(false);
	TryLeaveState(touch,unusedEvent);
	return false;
}

bool CTouchAnalyzerDrag::OnTouchCancelled( Touch* touch, Event *unusedEvent )
{
	SetActive(false);
	TryLeaveState(touch,unusedEvent);
	return false;
}

bool CTouchAnalyzerDrag::TryIntoState(Touch* touch, Event *unusedEvent)
{
	ITouchAnalyzer::TryIntoState();

	Vec2 ptOffset = touch->getLocation() - touch->getStartLocation();
	GetTouchLister()->GetHandler()->OnTouchDrag(GetTouchLister()->GetNode(),IsEnterState(),ptOffset,_ptBegin,touch,unusedEvent);
	return true;
}

bool CTouchAnalyzerDrag::TryLeaveState( Touch* touch, Event *unusedEvent )
{
	if (!ITouchAnalyzer::TryLeaveState())return false;

	Vec2 ptOffset = touch->getLocation() - touch->getStartLocation();
	GetTouchLister()->GetHandler()->OnTouchDrag(GetTouchLister()->GetNode(),IsEnterState(),ptOffset,_ptBegin,touch,unusedEvent);
	return true;
}

//////////////////////////////////////////////////////////////////////////

CTouchAnalyzerScaleView::CTouchAnalyzerScaleView( void )
{
	_fRate = 0.f;
}

CTouchAnalyzerScaleView::~CTouchAnalyzerScaleView( void )
{

}

bool CTouchAnalyzerScaleView::OnTouchBegan( Touch* touch, Event *unusedEvent )
{
	const VectorTouch& vTouch = GetTouchLister()->GetTouches();
	SetActive(vTouch.size() == 2);
	return false;
}

bool CTouchAnalyzerScaleView::OnTouchMoved( Touch* touch, Event *unusedEvent )
{
	if (IsActive())
	{
		TryIntoState(touch,unusedEvent);
	}

	return false;
}

bool CTouchAnalyzerScaleView::OnTouchEnded( Touch* touch, Event *unusedEvent )
{
	const VectorTouch& vTouch = GetTouchLister()->GetTouches();
	if (vTouch.size() < 2)
	{
		SetActive(false);
		TryLeaveState(touch,unusedEvent);
	}
	return false;
}

bool CTouchAnalyzerScaleView::OnTouchCancelled( Touch* touch, Event *unusedEvent )
{
	const VectorTouch& vTouch = GetTouchLister()->GetTouches();
	if (vTouch.size() < 2)
	{
		SetActive(false);
		TryLeaveState(touch,unusedEvent);
	}
	return false;
}

bool CTouchAnalyzerScaleView::TryIntoState( Touch* touch, Event *unusedEvent )
{
	ITouchAnalyzer::TryIntoState();

	const VectorTouch& vTouch = GetTouchLister()->GetTouches();
	float fDistanceOrg = ApiCocos2dx::CalDistanceSquared(vTouch[0]->getStartLocationInView(),	vTouch[1]->getStartLocationInView());
	if (fDistanceOrg > 0)
	{
		float fDistanceCur = ApiCocos2dx::CalDistanceSquared(vTouch[0]->getLocationInView(),	vTouch[1]->getLocationInView());
		float fRate = fDistanceCur / fDistanceOrg;

		GetTouchLister()->GetHandler()->OnTouchScaleView(GetTouchLister()->GetNode(),IsEnterState(),fRate,touch,unusedEvent);

		_fRate = fRate;
	}

	return true;
}

bool CTouchAnalyzerScaleView::TryLeaveState( Touch* touch, Event *unusedEvent )
{
	if (!ITouchAnalyzer::TryLeaveState())return false;

	GetTouchLister()->GetHandler()->OnTouchScaleView(GetTouchLister()->GetNode(),IsEnterState(),_fRate,touch,unusedEvent);
	return true;
}

//////////////////////////////////////////////////////////////////////////
CTouchAnalyzerSingleTouch::CTouchAnalyzerSingleTouch( void )
{

}

CTouchAnalyzerSingleTouch::~CTouchAnalyzerSingleTouch( void )
{

}

bool CTouchAnalyzerSingleTouch::OnTouchBegan( Touch* touch, Event *unusedEvent )
{
	const VectorTouch& vTouch = GetTouchLister()->GetTouches();
	SetActive(vTouch.size() == 1);
	
	return false;
}

bool CTouchAnalyzerSingleTouch::OnTouchMoved( Touch* touch, Event *unusedEvent )
{
	if (IsActive() && ApiCocos2dx::IsTouchBlur(touch))
	{
		SetActive(false);
	}
	return false;
}

bool CTouchAnalyzerSingleTouch::OnTouchEnded( Touch* touch, Event *unusedEvent )
{
	if (IsActive())
	{
		GetTouchLister()->GetHandler()->OnTouchSingle(GetTouchLister()->GetNode(),touch->getLocation());
	}
	SetActive(false);
	return false;
}

bool CTouchAnalyzerSingleTouch::OnTouchCancelled( Touch* touch, Event *unusedEvent )
{
	SetActive(false);
	return false;
}

//////////////////////////////////////////////////////////////////////////
CTouchAnalyzerDelay::CTouchAnalyzerDelay( void )
{
	SetWaitMillSec(300);
}

CTouchAnalyzerDelay::~CTouchAnalyzerDelay( void )
{
	StopTimer();
}

bool CTouchAnalyzerDelay::OnTouchBegan( Touch* touch, Event *unusedEvent )
{
	SetActive(GetTouchLister()->GetTouches().size() == 1);

	if (IsActive())
	{
		DeleteTimer();
		StartTimer(GetWaitMillSec());
	}
	return true;
}

bool CTouchAnalyzerDelay::OnTouchMoved( Touch* touch, Event *unusedEvent )
{
	//Ä£ºý·¶Î§
	if (IsActive() && ApiCocos2dx::IsTouchBlur(touch))
	{
		SetActive(false);
		DeleteTimer();
	}

	return true;
}

bool CTouchAnalyzerDelay::OnTouchEnded( Touch* touch, Event *unusedEvent )
{
	SetActive(false);
	DeleteTimer();
	return true;
}

bool CTouchAnalyzerDelay::OnTouchCancelled( Touch* touch, Event *unusedEvent )
{
	SetActive(false);
	DeleteTimer();
	return true;
}

bool CTouchAnalyzerDelay::OnTimeOut( const ToolFrame::CTimeNodePtr& pTimeNode )
{
	DeleteTimer();
	if (IsActive())
	{
		TryIntoState();
	}
	
	return true;
}

bool CTouchAnalyzerDelay::DeleteTimer()
{
	TryLeaveState();
	return StopTimer();
}

bool CTouchAnalyzerDelay::TryIntoState()
{
	if (!ITouchAnalyzer::TryIntoState())return false;

	GetTouchLister()->GetHandler()->OnTouchDelay(GetTouchLister()->GetNode(),IsEnterState());
	return true;
}

bool CTouchAnalyzerDelay::TryLeaveState()
{
	if (!ITouchAnalyzer::TryLeaveState())return false;

	GetTouchLister()->GetHandler()->OnTouchDelay(GetTouchLister()->GetNode(),IsEnterState());
	return true;
}

//////////////////////////////////////////////////////////////////////////
CTouchAnalyzerManual::CTouchAnalyzerManual( void )
{

}

CTouchAnalyzerManual::~CTouchAnalyzerManual( void )
{

}

bool CTouchAnalyzerManual::OnTouchBegan( Touch* touch, Event *unusedEvent )
{
	SetActive(true);
	TryIntoState();
	return true;
}

bool CTouchAnalyzerManual::OnTouchMoved( Touch* touch, Event *unusedEvent )
{
	SetActive(true);
	TryIntoState();
	return true;
}

bool CTouchAnalyzerManual::OnTouchEnded( Touch* touch, Event *unusedEvent )
{
	if (GetTouchLister()->GetTouches().empty())
	{
		SetActive(false);
		TryLeaveState();
	}
	return true;
}

bool CTouchAnalyzerManual::OnTouchCancelled( Touch* touch, Event *unusedEvent )
{
	if (GetTouchLister()->GetTouches().empty())
	{
		SetActive(false);
		TryLeaveState();
	}
	return true;
}

bool CTouchAnalyzerManual::TryIntoState()
{
	if (!ITouchAnalyzer::TryIntoState())return false;

	GetTouchLister()->GetHandler()->OnTouchManual(GetTouchLister()->GetNode(),IsEnterState());
	return true;
}

bool CTouchAnalyzerManual::TryLeaveState()
{
	if (!ITouchAnalyzer::TryLeaveState())return false;

	GetTouchLister()->GetHandler()->OnTouchManual(GetTouchLister()->GetNode(),IsEnterState());
	return true;
}
//////////////////////////////////////////////////////////////////////////
CTouchAnalyzerSlip::CTouchAnalyzerSlip(void)
{

}

CTouchAnalyzerSlip::~CTouchAnalyzerSlip(void)
{

}

bool CTouchAnalyzerSlip::OnTouchBegan(Touch* touch, Event *unusedEvent)
{
	const VectorTouch& vTouch = GetTouchLister()->GetTouches();
	SetActive(vTouch.size() == 1);

	
	uTimeBegin = ToolFrame::GetNowTimeMill();
	return true;
}

bool CTouchAnalyzerSlip::OnTouchMoved(Touch* touch, Event *unusedEvent)
{
	return true;
}

bool CTouchAnalyzerSlip::OnTouchEnded(Touch* touch, Event *unusedEvent)
{
	OnActiveEnd(touch);
	return true;
}

bool CTouchAnalyzerSlip::OnTouchCancelled(Touch* touch, Event *unusedEvent)
{
	OnActiveEnd(touch);
	return true;
}

bool CTouchAnalyzerSlip::OnActiveEnd(Touch* touch)
{
	if (IsActive() && ApiCocos2dx::IsTouchBlur(touch))
	{
		SetActive(false);
		if (ToolFrame::GetNowTimeMill() - uTimeBegin < 500)
			GetTouchLister()->GetHandler()->OnTouchSlip(GetTouchLister()->GetNode(), touch->getLocation() - touch->getStartLocation());
	}

	return true;
}

#endif //MACRO_LIB_COCOS2D
