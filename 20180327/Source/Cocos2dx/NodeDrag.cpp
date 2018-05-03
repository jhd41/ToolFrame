#include "NodeDrag.h"

#ifdef MACRO_LIB_COCOS2D

#include "ApiCocos2dx.h"
#include "ToolFrame.h"

CNodeDrag::CNodeDrag(void)
{
	_pNode = nullptr;
	_rDragRect = ApiCocos2dx::GetVisibleRect();
	_eDirection = DIRECTION_BOTH;
	_hHandler = nullptr;
	_bDraging = false;
	_bTouchCenter = false;
}

CNodeDrag::~CNodeDrag(void)
{
	RemoveNode();
}

bool CNodeDrag::SetNode( Node* pNode )
{
	_pNode = pNode;
	_pNode->retain();
	return true;
}

bool CNodeDrag::RemoveNode( bool bRemoveFromParent /*= false*/ )
{
	if (!_pNode)return false;

	if (bRemoveFromParent)
		_pNode->removeFromParent();

	_pNode->release();
	_pNode = nullptr;

	return true;
}

bool CNodeDrag::SetDragRect( const Rect& rDragRect )
{
	_rDragRect = rDragRect;
	return true;
}

bool CNodeDrag::IsNodeNull() const
{
	return !_pNode;
}

Node* CNodeDrag::GetNode() const
{
	return _pNode;
}

bool CNodeDrag::DragBegin(const Touch* touch)
{
	if (!touch)return false;
	return DragBegin(touch->getStartLocation());
}

bool CNodeDrag::DragBegin( const Point& ptTouch )
{
	if (!_pNode)return false;

	_ptNodeBegin = ApiCocos2dx::GetWorldPostion(_pNode);
	_ptTouchBegin = ptTouch;
	_bDraging = true;

	if (_bTouchCenter)
		ApiCocos2dx::SetWorldPostion(_pNode,ptTouch);

	if (_hHandler)
		_hHandler->OnDragBegin(this);

	return true;
}

bool CNodeDrag::DragMove(const Touch* touch)
{
	if (!touch)return false;

	//如果是第一次
	if (!_bDraging)
		DragBegin(touch->getPreviousLocation());

	return DragMove(touch->getLocation());
}

bool CNodeDrag::DragMove( const Point& ptTouch )
{
	if (!_pNode)return false;

	Point ptOffset = ptTouch - _ptTouchBegin;

	switch (_eDirection)
	{
	case DIRECTION_HORIZONTAL:
		ptOffset.y = 0;
		break;
	case DIRECTION_VERTICAL:
		ptOffset.x = 0;
		break;
	case DIRECTION_BOTH:
		break;
	}

	if (_bTouchCenter)
	{
		ApiCocos2dx::SetWorldPostion(_pNode,ptTouch);
	}else{
		Point ptPostion = _ptNodeBegin + ptOffset;
		ApiCocos2dx::SetWorldPostion(_pNode,ptPostion);
	}

	ApiCocos2dx::MakeInRect(_pNode,ptOffset,_rDragRect);

	if (_hHandler)
		_hHandler->OnDragMove(this);
	return true;
}

bool CNodeDrag::DragEnd(const Touch* touch)
{
	if (!touch)return false;
	return DragEnd(touch->getLocation());
}

bool CNodeDrag::DragEnd( const Point& ptTouch )
{
	if (!_pNode)return false;
	_bDraging = false;

	if (_hHandler)
		_hHandler->OnDragEnd(this);
	return true;
}

bool CNodeDrag::SetHandler( HNodeDrag* hHandler )
{
	_hHandler = hHandler;
	return true;
}

bool CNodeDrag::IsDraging() const
{
	return _bDraging;
}

bool CNodeDrag::SetCenterTouch( bool bCenter )
{
	_bTouchCenter = bCenter;
	return true;
}

bool CNodeDrag::IsCenterTouch() const
{
	return _bTouchCenter;
}

bool CNodeDrag::ResetBegin()
{
	if (!_pNode)return false;
	
	return ApiCocos2dx::SetWorldPostion(_pNode,_ptNodeBegin);
}

#endif //MACRO_LIB_COCOS2D
