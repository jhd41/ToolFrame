#pragma once
#include "MacroCocos2dx.h"

//Node��ק
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
	bool	SetDragRect(const Rect& rDragRect);		//�����϶�����
	bool	SetHandler(HNodeDrag* hHandler);
	bool	SetCenterTouch(bool bCenter);			//���ýڵ� ���津����

	Node*	GetNode()const;

	bool	RemoveNode(bool bRemoveFromParent = false);
	bool	IsNodeNull()const;

	template<typename T>
	T*		GetNode();

	bool	IsDraging()const;
	bool	IsCenterTouch()const;
	bool	ResetBegin();//�ڵ����õ���ק֮ǰ��λ��
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
	Rect		_rDragRect;		//�϶�����
	EDirection	_eDirection;	//�϶�����
	HNodeDrag*	_hHandler;

	Point		_ptNodeBegin;	//�ڵ���ʼ����
	Point		_ptTouchBegin;	//������ʼ����

	bool		_bDraging;		//�϶���
	bool		_bTouchCenter;	//������������
};

template<typename T>
T* CNodeDrag::GetNode()
{
	return dynamic_cast<T*>(_pNode);
}

#endif //MACRO_LIB_COCOS2D