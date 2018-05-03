#pragma once
#include "MacroCocos2dx.h"

//备注:单选组 利用复选框 实现 单选功能。提供 父容器概念，若设置了父容器，则所有的单选框的父节点会被改变
#ifdef MACRO_LIB_COCOS2D

class TOOLFRAME_DLL CRadioGroup;
class TOOLFRAME_DLL HRadioGroup{
public:
	virtual bool OnRadioChecked(CRadioGroup* pRadioGroup,CheckBox* pSender){return false;}
public:
	HRadioGroup(){}
	virtual ~HRadioGroup(){}
};

class TOOLFRAME_DLL CRadioGroup
	:public Ref
{
public:
	bool		SetListener(HRadioGroup* pListener);
	bool		SetRootWidget(Node* pWidget);
	bool		SetContainer(Node* pWidget);				//设置所属容器(可不填)
	bool		SetContainer(const std::string& sContainer);//设置所属容器(可不填)
	CheckBox*	AddCheckBox(CheckBox* pCheckBox,bool bChecked = false);
	CheckBox*	AddCheckBox(const std::string& sName);
	CheckBox*	AddCheckBox(const Node* pRootWidget,const std::string& sName);
	CheckBox*	GetLastSelected()const;
	bool		SetChecked(const std::string& sName);
	bool		SetChecked(CheckBox* pCheckBox);
	CheckBox*	GetCheckBox(const std::string& sName)const;
	CheckBox*	GetCheckBox(int nIndex)const;
	bool		SelectFirst();
	bool		Clear();
private:
	void checkboxEvent( Ref* pSender, CheckBoxEventType type );
public:
	CRadioGroup(void);
	virtual ~CRadioGroup(void);
private:
	VectorCheckBox	_vCheckBox;
	CheckBox*		_pCur;		//当前选中
	CheckBox*		_pLast;		//最近选中
	HRadioGroup*	_pListener;
	Node*			_pWidgetRoot;
	Node*			_pContainer;
};

#endif //MACRO_LIB_COCOS2D
