#pragma once
#include "MacroCocos2dx.h"

//Widget拖拽

#ifdef MACRO_LIB_COCOS2D

class TOOLFRAME_DLL CWidgetDrag
{
public:
	bool	SetWidget(Widget* pWidget);
	bool	SetDragRect(const Rect& rDragRect);		//设置拖动区域
	bool	Drag(Ref *pSender, TouchEventType type);//拖动(返回 拖动完成)
	bool	IsMove(Ref *pSender, TouchEventType type);//是否是Move本Widget

	bool	IsDrag()const;
	bool	StopDrag();					//清除拖动
	Widget* GetWidget()const;
	template<typename T>
	T*		GetWidget()const;
	bool	IsWidgetNull()const;
public:
	bool	Drag(const std::string& sName,Ref *pSender, TouchEventType type);	//拖动(返回 拖动完成)
	bool	IsMove(const std::string& sName,Ref *pSender, TouchEventType type);	//是否是Move本Widget
private:
	bool	SetDraging();//设置在拖动中
private:
	CFIELD_INT(ZOrder);
public:
	CWidgetDrag(void);
	virtual ~CWidgetDrag(void);
private:
	int		_nBeginZOrder;	//原始ZOrder
	Point	_ptBegin;		//起始坐标
	Rect	_rDragRect;		//拖动区域

	Widget* _pWidget;		//Widget
	Widget*	_pWidgetDrag;	//拖动中
};

template<typename T>
T* CWidgetDrag::GetWidget()const
{
	return dynamic_cast<T*>(_pWidget);
}

#endif //MACRO_LIB_COCOS2D
