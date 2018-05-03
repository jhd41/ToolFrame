#include "RadioGroup.h"

#ifdef MACRO_LIB_COCOS2D

#include "ApiCocos2dx.h"
#include "ToolFrame.h"
#include "MLoger.h"

CRadioGroup::CRadioGroup(void)
{
	_pCur = nullptr;
	_pLast = nullptr;

	_pListener = nullptr;
	_pWidgetRoot = nullptr;
	_pContainer =nullptr;
}

CRadioGroup::~CRadioGroup(void)
{
}

CheckBox* CRadioGroup::AddCheckBox( const std::string& sName )
{
	return AddCheckBox(_pWidgetRoot,sName);
}

CheckBox* CRadioGroup::AddCheckBox( const Node* pRootWidget,const std::string& sName )
{
	if (!pRootWidget)return nullptr;
	
	CheckBox* pCheckBox = nullptr;
	if (!ApiCocos2dx::FindNode(pCheckBox,pRootWidget,sName))return nullptr;
	return AddCheckBox(pCheckBox);
}

CheckBox* CRadioGroup::AddCheckBox( CheckBox* pCheckBox,bool bChecked /*= false*/ )
{
	if (!pCheckBox)return nullptr;

	if (_pContainer)
		ApiCocos2dx::ChangeParentNode(pCheckBox,_pContainer);

	//取消最近一次选中
	if (bChecked)
	{
		ApiCocos2dx::SetChecked(_pLast,false);
		_pLast = pCheckBox;
	}
	ApiCocos2dx::SetChecked(pCheckBox,bChecked);

	ApiCocos2dx::AddEventListenerCheckBox(pCheckBox,this, checkboxselectedeventselector(CRadioGroup::checkboxEvent));
	ToolFrame::Insert(_vCheckBox,pCheckBox);
	return pCheckBox;
}

void CRadioGroup::checkboxEvent( Ref* pSender, CheckBoxEventType type )
{
	if (_pCur)return ;

	CheckBox* pCheckBox = nullptr;
	ASSERT_LOG_ERROR(ToolFrame::DynamicCast(pCheckBox,pSender));

	_pCur = pCheckBox;

	if (CHECKBOX_STATE_EVENT_SELECTED == type)
	{	
		if (_pLast != pCheckBox)
		{
			ApiCocos2dx::SetChecked(_pLast,false);
			_pLast = pCheckBox;	
			if (_pListener)
				_pListener->OnRadioChecked(this,pCheckBox);
		}
	}else
	{
		if (_pLast == pCheckBox )
		{
			ApiCocos2dx::SetChecked(_pLast,true);
		}
	}
	_pCur = nullptr;
}

CheckBox* CRadioGroup::GetLastSelected() const
{
	return _pLast;
}

bool CRadioGroup::SetListener( HRadioGroup* pListener )
{
	if (!pListener)return false;
	_pListener = pListener;
	return true;
}

bool CRadioGroup::SetRootWidget( Node* pWidget )
{
	if (!pWidget)return false;
	_pWidgetRoot = pWidget;
	return true;
}

bool CRadioGroup::SetContainer( Node* pWidget )
{
	if (!pWidget)return false;
	_pContainer = pWidget;
	return true;
}

bool CRadioGroup::SetContainer( const std::string& sContainer )
{
	return SetContainer(ApiCocos2dx::FindNode(_pWidgetRoot,sContainer));
}

bool CRadioGroup::SetChecked( const std::string& sName )
{
	CheckBox* pCheckBox = nullptr;
	if (!ApiCocos2dx::FindNode(pCheckBox,_pWidgetRoot,sName))return false;
	return SetChecked(pCheckBox);
}

bool CRadioGroup::SetChecked( CheckBox* pCheckBox )
{
	if (!pCheckBox)return false;
	
	ApiCocos2dx::SetChecked(pCheckBox,true);
	checkboxEvent(pCheckBox,CHECKBOX_STATE_EVENT_SELECTED);
	return true;
}

CheckBox* CRadioGroup::GetCheckBox( const std::string& sName ) const
{
	VectorCheckBox::const_iterator itr;
	foreach(itr,_vCheckBox){
		CheckBox* pCheckBox = *itr;
		ASSERT_LOG_ERROR(pCheckBox);

		if (pCheckBox->getName() == sName)
			return pCheckBox;
	}

	return nullptr;
}

CheckBox* CRadioGroup::GetCheckBox( int nIndex ) const
{
	return ToolFrame::GetPtrValueByIndex(_vCheckBox,nIndex);
}

bool CRadioGroup::SelectFirst()
{
	if (_vCheckBox.empty())return false;
	
	return SetChecked(*_vCheckBox.begin());
}

bool CRadioGroup::Clear()
{
	_pLast = nullptr;
	ToolFrame::Clear(_vCheckBox);
	return true;
}

#endif //MACRO_LIB_COCOS2D
