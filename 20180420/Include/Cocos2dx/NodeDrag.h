#pragma once
#include "MacroCocos2dx.h"

//Node拖拽
#ifdef MACRO_LIB_COCOS2D

class CNodeDrag;
class HNodeDrag
{
public:
	virtual bool OnDragBegin(CNodeDrag* pDrag){return false;}
	virtual bool OnDragMove(CNodeDrag* pDrag){return false;}
	virtual bool OnDragEnd(CNodeDrag* pDrag){return false;}
public:
	HNodeDrag(){}
	virtual ~HNodeDrag(){}
};

class CNodeDrag
{
public:
	enum EDirection
	{
		DIRECTION_NONE,
		DIRECTION_VERTICAL,
		DIRECTION_HORIZONTAL,
		DIRECTION_BOTH
	};
public:
	bool	SetNode(Node* pNode);
	bool	SetDragRect(const Rect& rDragRect);		//设置拖动区域
	bool	SetHandler(HNodeDrag* hHandler);
	bool	SetCenterTouch(bool bCenter);			//设置节点 跟随触摸点

	Node*	GetNode()const;

	bool	RemoveNode(bool bRemoveFromParent = false);
	bool	IsNodeNull()const;

	template<typename T>
	T*		GetNode();

	bool	IsDraging()const;
	bool	IsCenterTouch()const;
	bool	ResetBegin();//节点重置到拖拽之前的位置
public:
	bool	DragBegin(const Touch* touch);
	bool	DragMove(const Touch* touch);
	bool	DragEnd(const Touch* touch);
private:
	bool	DragBegin(const Point& ptTouch);
	bool	DragMove(const Point& ptTouch);
	bool	DragEnd(const Point& ptTouch);
public:
	CNodeDrag(void);
	virtual ~CNodeDrag(void);
private:
	Node*		_pNode;			//Widget
	Rect		_rDragRect;		//拖动区域
	EDirection	_eDirection;	//拖动方向
	HNodeDrag*	_hHandler;

	Point		_ptNodeBegin;	//节点起始坐标
	Point		_ptTouchBegin;	//触摸起始坐标

	bool		_bDraging;		//拖动中
	bool		_bTouchCenter;	//触摸点在中心
};

template<typename T>
T* CNodeDrag::GetNode()
{
	return dynamic_cast<T*>(_pNode);
}

#endif //MACRO_LIB_COCOS2D