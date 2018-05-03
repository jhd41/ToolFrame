#include "TouchGroup.h"

#ifdef MACRO_LIB_COCOS2D

#include "ToolFrame.h"
#include "ApiCocos2dx.h"

CTouchGroup::CTouchGroup(void)
{
	_hHandler = nullptr;
	_bEnabled = false;
}

CTouchGroup::~CTouchGroup(void)
{
	Destory();
}

bool CTouchGroup::Init()
{
	SetEnabled(true);
	return true;
}

CTouchListener* CTouchGroup::AddListener( Node* pNode,HTouchListener* hHander,bool bEnabled /*= true*/ )
{
	if (!pNode)return nullptr;
	if (!hHander)return nullptr;

 	CTouchListener& lister = ToolFrame::GetValueByKeyForce(_vTouch,pNode);
 	lister.SetNode(pNode);
 	lister.SetHandler(hHander);
 	lister.SetEnabled(bEnabled);
	return &lister;
}

bool CTouchGroup::RemoveListener( Node* pNode )
{
	return ToolFrame::EraseByKey(_vTouch,pNode) > 0;
}

bool CTouchGroup::RemoveListener()
{
	ToolFrame::Clear(_vTouch);
	return true;
}

bool CTouchGroup::SetEnabled( bool bEnabled )
{
	return _bEnabled = bEnabled;
}

bool CTouchGroup::IsEnabled() const
{
	return _bEnabled;
}

bool CTouchGroup::OnTouchBegan( Touch* touch, Event *unusedEvent )
{
	if (!_bEnabled)return true;

	if (_hHandler)
		_hHandler->OnTouchGroupBegan(touch,unusedEvent);

	if (!_vTouch.empty())
	{
		MapTouchLister::iterator itr;
		foreach(itr,_vTouch){
			CTouchListener& lister = itr->second;
			if (lister.IsEnabled())
				lister.OnTouchBegan(touch,unusedEvent);
		}
	}

	return true;
}

bool CTouchGroup::OnTouchMoved( Touch* touch, Event *unusedEvent )
{
	if (!_bEnabled)return true;

	if (_hHandler)
		_hHandler->OnTouchGroupMoved(touch,unusedEvent);

	if (!_vTouch.empty()){
		MapTouchLister::iterator itr;
		foreach(itr,_vTouch){
			CTouchListener& lister = itr->second;
			if (lister.IsEnabled())
				lister.OnTouchMoved(touch,unusedEvent);
		}
	}

	return true;
}

bool CTouchGroup::OnTouchEnded( Touch* touch, Event *unusedEvent )
{
	if (!_bEnabled)return true;

	if (_hHandler)
		_hHandler->OnTouchGroupEnded(touch,unusedEvent);

	if (!_vTouch.empty()){
		MapTouchLister::iterator itr;
		foreach(itr,_vTouch){
			CTouchListener& lister = itr->second;
			if (lister.IsEnabled())
				lister.OnTouchEnded(touch,unusedEvent);
		}
	}

	return true;
}

bool CTouchGroup::OnTouchCancelled( Touch* touch, Event *unusedEvent )
{
	if (!_bEnabled)return true;

	if (_hHandler)
		_hHandler->OnTouchGroupCancelled(touch,unusedEvent);

	if (!_vTouch.empty()){
		MapTouchLister::iterator itr;
		foreach(itr,_vTouch){
			CTouchListener& lister = itr->second;
			if (lister.IsEnabled())
				lister.OnTouchCancelled(touch,unusedEvent);
		}
	}

	return true;
}

bool CTouchGroup::SetHandler( HTouchListener* hHandler )
{
	_hHandler = hHandler;
	return true;
}

bool CTouchGroup::Destory()
{
	RemoveListener();
	return true;
}

#endif //MACRO_LIB_COCOS2D
