#include "InputEventListener.h"

#ifdef MACRO_LIB_COCOS2D

#include "ToolFrame.h"

CInputEventListener::CInputEventListener(void)
{
	_pKeyBoard = nullptr;
	_pAcceleration = nullptr;
	_pTouchListener = nullptr;

	_hHandler = nullptr;
	_pNodeGraphPriority = nullptr;
}

CInputEventListener::~CInputEventListener(void)
{
	SetEnabledAll (false);
}

bool CInputEventListener::SetKeyboardEnabled( bool bEnabled )
{
	if (bEnabled && !_pKeyBoard){
		//对手机返回键的监听 
		_pKeyBoard = EventListenerKeyboard::create(); 
		//和回调函数绑定 
		_pKeyBoard->onKeyPressed	= ToolFrame::Bind(&CInputEventListener::OnKeyPressed, this);
		_pKeyBoard->onKeyReleased	= ToolFrame::Bind(&CInputEventListener::OnKeyReleased, this); 

		//添加到事件分发器中 
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_pKeyBoard,_pNodeGraphPriority);
	}

	if (!bEnabled && _pKeyBoard)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pKeyBoard);
		_pKeyBoard = nullptr;
	}

	return true;
}

bool CInputEventListener::SetAccelerometerEnabled( bool bEnabled )
{
	if (bEnabled && !_pAcceleration){
		_pAcceleration = EventListenerAcceleration::create(ToolFrame::Bind(&CInputEventListener::OnAcceleration, this));//创建一个重力监听事件
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_pAcceleration,_pNodeGraphPriority);
	}

	if (!bEnabled && _pAcceleration){
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pAcceleration);
		_pAcceleration = nullptr;
	}
	return true;
}

bool CInputEventListener::SetTouchEnabled( bool bEnabled,bool bShare /*= false*/ )
{
	if (bEnabled && !_pTouchListener){
		_pTouchListener = EventListenerTouchOneByOne::create();

		_pTouchListener->onTouchBegan =		ToolFrame::Bind(&CInputEventListener::OnTouchBegan,this);
		_pTouchListener->onTouchMoved =		ToolFrame::Bind(&CInputEventListener::OnTouchMoved,this);
		_pTouchListener->onTouchEnded =		ToolFrame::Bind(&CInputEventListener::OnTouchEnded,this);
		_pTouchListener->onTouchCancelled =	ToolFrame::Bind(&CInputEventListener::OnTouchCancelled,this);

		if (!bShare)
		{
			_pTouchListener->setSwallowTouches(true);
			Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_pTouchListener,_pNodeGraphPriority);
		}else{
			Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_pTouchListener,-1);
		}
		return true;
	}

	if (!bEnabled && _pTouchListener){
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pTouchListener);
		_pTouchListener = nullptr;
		return true;
	}
	return false;
}

void CInputEventListener::OnAcceleration( Acceleration* pAcceleration, Event* pEvent )
{
	if (_hHandler)
		_hHandler->OnAcceleration(pAcceleration,pEvent);
}

void CInputEventListener::OnKeyPressed( EventKeyboard::KeyCode eKeyCode, Event* pEvent )
{
	if (_hHandler)
		_hHandler->OnKeyPressed(eKeyCode,pEvent);
}

void CInputEventListener::OnKeyReleased( EventKeyboard::KeyCode eKeyCode, Event* pEvent )
{
	if (_hHandler)
		_hHandler->OnKeyReleased(eKeyCode,pEvent);
}

bool CInputEventListener::OnTouchBegan( Touch* touch, Event *unusedEvent )
{
	if (_hHandler)
		_hHandler->OnTouchBegan(touch,unusedEvent);
	return true;
}

void CInputEventListener::OnTouchMoved( Touch* touch, Event *unusedEvent )
{
	if (_hHandler)
		_hHandler->OnTouchMoved(touch,unusedEvent);
}

void CInputEventListener::OnTouchEnded( Touch* touch, Event *unusedEvent )
{
	if (_hHandler)
		_hHandler->OnTouchEnded(touch,unusedEvent);
}

void CInputEventListener::OnTouchCancelled( Touch* touch, Event *unusedEvent )
{
	if (_hHandler)
		_hHandler->OnTouchCancelled(touch,unusedEvent);
}

bool CInputEventListener::SetHandler( HInputEventListener* hHandler )
{
	_hHandler = hHandler;
	return true;
}

bool CInputEventListener::IsKeyboardEnabled() const
{
	return !!_pKeyBoard;
}

bool CInputEventListener::IsAccelerometerEnabled() const
{
	return !!_pAcceleration;
}

bool CInputEventListener::IsTouchEnabled() const
{
	return !!_pTouchListener;
}

bool CInputEventListener::SetEnabledAll( bool bEnabled )
{
	SetKeyboardEnabled(bEnabled);
	SetAccelerometerEnabled(bEnabled);
	SetTouchEnabled(bEnabled);
	return true;
}

bool CInputEventListener::SetGraphPriorityNode( Node* pNode )
{
	_pNodeGraphPriority = pNode;
	return true;
}

#endif //MACRO_LIB_COCOS2D
