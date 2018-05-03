#include "WidgetDrag.h"

#ifdef MACRO_LIB_COCOS2D

#include "ApiCocos2dx.h"
#include "ToolFrame.h"

CWidgetDrag::CWidgetDrag(void)
{
	_nZOrder = 0;
	_nBeginZOrder = 0;
	_pWidget = nullptr;
	_pWidgetDrag = nullptr;
	_rDragRect = ApiCocos2dx::GetVisibleRect();
}

CWidgetDrag::~CWidgetDrag(void)
{
	StopDrag();

	if (_pWidget)
		_pWidget->release();
}

bool CWidgetDrag::Drag( Ref *pSender, TouchEventType type )
{
	if (_pWidget != pSender)return false;

	//ÍÏ¶¯
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		if (IsDrag())return false;

		SetDraging();
		return false;
		break;
	case TOUCH_EVENT_MOVED:
		{
			if (!IsDrag())return false;

			Point ptOffset = _pWidget->getTouchMovePosition() - _pWidget->getTouchBeganPosition();
			Point ptPostion = _ptBegin + ptOffset;
			ApiCocos2dx::SetWorldPostion(_pWidget,ptPostion);
			ApiCocos2dx::MakeInRect(_pWidget,ptOffset,_rDragRect);
			return false;
		}
		break;
	case TOUCH_EVENT_ENDED:
		if (!IsDrag())return false;
		StopDrag();
		return true;
		break;
	case TOUCH_EVENT_CANCELED:
		if (!IsDrag())return false;
		StopDrag();
		return true;
		break;
	default:
		break;
	}
	return false;
}

bool CWidgetDrag::IsMove( Ref *pSender, TouchEventType type )
{
	if (_pWidget != pSender)return false;

	return IsDrag() && TOUCH_EVENT_MOVED == type;
}

bool CWidgetDrag::StopDrag()
{
	if (!_pWidgetDrag)return false;

	_pWidgetDrag = nullptr;

	_pWidget->setZOrder(_nBeginZOrder);
	return true;
}

Widget* CWidgetDrag::GetWidget()const
{
	return _pWidget;
}

bool CWidgetDrag::IsDrag() const
{
	return !!_pWidgetDrag;
}

bool CWidgetDrag::SetWidget( Widget* pWidget )
{
	if (!pWidget)return false;
	if (pWidget == _pWidget)return true;

	if (_pWidget)
	{
		_pWidget->release();
		_pWidget=nullptr;
	}
	_pWidget = pWidget;
	_pWidget->retain();
	return true;
}

bool CWidgetDrag::SetDraging()
{
	if (_pWidgetDrag)return false;

	_pWidgetDrag = _pWidget;

	_nBeginZOrder = _pWidget->getZOrder();
	_ptBegin = ApiCocos2dx::GetWorldPostion(_pWidget);
	_pWidget->setZOrder(GetZOrder());
	return true;
}

bool CWidgetDrag::SetDragRect( const Rect& rDragRect )
{
	_rDragRect = rDragRect;
	return true;
}


bool CWidgetDrag::Drag( const std::string& sName,Ref *pSender, TouchEventType type )
{
	if (TOUCH_EVENT_BEGAN == type)
	{
		if (IsDrag())return false;

		Widget* pWidget = dynamic_cast<Widget*>(pSender);
		if (!pWidget || pWidget->getName() != sName)return false;
		
		SetWidget(pWidget);
		return Drag(pSender,type);
	}

	return Drag(pSender,type);
}

bool CWidgetDrag::IsMove( const std::string& sName,Ref *pSender, TouchEventType type )
{
	return IsMove(pSender,type);
}

bool CWidgetDrag::IsWidgetNull() const
{
	return !_pWidget;
}

#endif //MACRO_LIB_COCOS2D
