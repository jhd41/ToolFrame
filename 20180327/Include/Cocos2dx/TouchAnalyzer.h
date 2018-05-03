#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "HTouchHandler.h"
#include "HTimeOut.h"

//////////////////////////////////////////////////////////////////////////
class CTouchListener;
class ITouchAnalyzer
	:public ToolFrame::HTimeOut
{
public:
	bool			IsEnabled()const;	//是否开启
	bool			IsActive()const;	//是否激活中
	bool			SetActive(bool bActive);
	bool			SetTouchLister(CTouchListener* pParent);
	CTouchListener*	GetTouchLister();
protected:
	virtual bool	StartTimer(uint uMillSecond);
	virtual bool	StopTimer();
protected:
	virtual bool	TryIntoState();
	virtual bool	TryLeaveState();
	virtual bool	IsEnterState()const;
public:
	virtual bool OnTouchBegan	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchMoved	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchEnded	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchCancelled(Touch* touch, Event *unusedEvent);
public:
	virtual bool OnTimeOut(const ToolFrame::CTimeNodePtr& pTimeNode);
public:
	ITouchAnalyzer(void);
	virtual ~ITouchAnalyzer(void);
private:
	bool					_bEnabled;
	CTouchListener*			_pTouchLister;
	bool					_bActive;
	ToolFrame::CTimeNodePtr _pTimer;
	bool					_bEnterState;
};
//////////////////////////////////////////////////////////////////////////
class CTouchAnalyzerIdel
	:public ITouchAnalyzer
	
{
public:
	virtual bool OnTouchBegan	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchMoved	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchEnded	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchCancelled(Touch* touch, Event *unusedEvent);
private:
	virtual bool CheckIdle();
	virtual bool OnTimeOut(const ToolFrame::CTimeNodePtr& pTimeNode);
public:
	CTouchAnalyzerIdel(void);
	virtual ~CTouchAnalyzerIdel(void);
};

//////////////////////////////////////////////////////////////////////////
class CTouchAnalyzerManual
	:public ITouchAnalyzer
{
public:
	virtual bool OnTouchBegan	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchMoved	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchEnded	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchCancelled(Touch* touch, Event *unusedEvent);
protected:
	virtual bool TryIntoState();
	virtual bool TryLeaveState();
public:
	CTouchAnalyzerManual(void);
	virtual ~CTouchAnalyzerManual(void);
};

//////////////////////////////////////////////////////////////////////////
class CTouchAnalyzerDrag
	:public ITouchAnalyzer
{
public:
	virtual bool OnTouchBegan	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchMoved	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchEnded	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchCancelled(Touch* touch, Event *unusedEvent);
protected:
	virtual bool TryIntoState(Touch* touch, Event *unusedEvent);
	virtual bool TryLeaveState(Touch* touch, Event *unusedEvent);
public:
	CTouchAnalyzerDrag(void);
	virtual ~CTouchAnalyzerDrag(void);
private:
	Vec2	_ptBegin;
};

//////////////////////////////////////////////////////////////////////////
class CTouchAnalyzerScaleView
	:public ITouchAnalyzer
{
public:
	virtual bool OnTouchBegan	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchMoved	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchEnded	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchCancelled(Touch* touch, Event *unusedEvent);
protected:
	virtual bool TryIntoState(Touch* touch, Event *unusedEvent);
	virtual bool TryLeaveState(Touch* touch, Event *unusedEvent);
public:
	CTouchAnalyzerScaleView(void);
	virtual ~CTouchAnalyzerScaleView(void);
protected:
	float _fRate;
};
//////////////////////////////////////////////////////////////////////////
class CTouchAnalyzerSingleTouch
	:public ITouchAnalyzer
{
public:
	virtual bool OnTouchBegan	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchMoved	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchEnded	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchCancelled(Touch* touch, Event *unusedEvent);
public:
	CTouchAnalyzerSingleTouch(void);
	virtual ~CTouchAnalyzerSingleTouch(void);
};
//////////////////////////////////////////////////////////////////////////
class CTouchAnalyzerDelay
	:public ITouchAnalyzer
{
public:
	CFIELD_INT(WaitMillSec);//延迟的毫秒数
private:
	virtual bool OnTouchBegan	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchMoved	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchEnded	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchCancelled(Touch* touch, Event *unusedEvent);
private:
	virtual bool OnTimeOut(const ToolFrame::CTimeNodePtr& pTimeNode);
private:
	virtual bool TryIntoState();
	virtual bool TryLeaveState();
	bool DeleteTimer();
public:
	CTouchAnalyzerDelay(void);
	virtual ~CTouchAnalyzerDelay(void);
};
//////////////////////////////////////////////////////////////////////////
class CTouchAnalyzerSlip
	:public ITouchAnalyzer
{
public:
	virtual bool OnTouchBegan(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchMoved(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchEnded(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchCancelled(Touch* touch, Event *unusedEvent);
private:
	virtual bool OnActiveEnd(Touch* touch);
public:
	CTouchAnalyzerSlip(void);
	virtual ~CTouchAnalyzerSlip(void);
protected:
	uint uTimeBegin;
};
#endif //MACRO_LIB_COCOS2D
