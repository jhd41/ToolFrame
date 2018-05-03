#pragma once
#include "MacroCocos2dx.h"

//Widget��ק

#ifdef MACRO_LIB_COCOS2D

class TOOLFRAME_DLL CWidgetDrag
{
public:
	bool	SetWidget(Widget* pWidget);
	bool	SetDragRect(const Rect& rDragRect);		//�����϶�����
	bool	Drag(Ref *pSender, TouchEventType type);//�϶�(���� �϶����)
	bool	IsMove(Ref *pSender, TouchEventType type);//�Ƿ���Move��Widget

	bool	IsDrag()const;
	bool	StopDrag();					//����϶�
	Widget* GetWidget()const;
	template<typename T>
	T*		GetWidget()const;
	bool	IsWidgetNull()const;
public:
	bool	Drag(const std::string& sName,Ref *pSender, TouchEventType type);	//�϶�(���� �϶����)
	bool	IsMove(const std::string& sName,Ref *pSender, TouchEventType type);	//�Ƿ���Move��Widget
private:
	bool	SetDraging();//�������϶���
private:
	CFIELD_INT(ZOrder);
public:
	CWidgetDrag(void);
	virtual ~CWidgetDrag(void);
private:
	int		_nBeginZOrder;	//ԭʼZOrder
	Point	_ptBegin;		//��ʼ����
	Rect	_rDragRect;		//�϶�����

	Widget* _pWidget;		//Widget
	Widget*	_pWidgetDrag;	//�϶���
};

template<typename T>
T* CWidgetDrag::GetWidget()const
{
	return dynamic_cast<T*>(_pWidget);
}

#endif //MACRO_LIB_COCOS2D
