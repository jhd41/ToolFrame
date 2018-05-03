#pragma once
#include "MacroCocos2dx.h"

//��ע:��ѡ�� ���ø�ѡ�� ʵ�� ��ѡ���ܡ��ṩ ����������������˸������������еĵ�ѡ��ĸ��ڵ�ᱻ�ı�
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
	bool		SetContainer(Node* pWidget);				//������������(�ɲ���)
	bool		SetContainer(const std::string& sContainer);//������������(�ɲ���)
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
	CheckBox*		_pCur;		//��ǰѡ��
	CheckBox*		_pLast;		//���ѡ��
	HRadioGroup*	_pListener;
	Node*			_pWidgetRoot;
	Node*			_pContainer;
};

#endif //MACRO_LIB_COCOS2D
