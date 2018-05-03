#include "SceneFrameMgr.h"

#ifdef MACRO_LIB_COCOS2D

#include "ApiCocos2dx.h"
#include "MLoger.h"

CSceneFrameMgr::CSceneFrameMgr(void)
{
	_pRunningScene = nullptr;
	_hHandler = nullptr;
	_bSceneChanging = false;

	//页面相关
	_bTouchEnabled			= true;
	_uGlobalTimeLoad		= 0;
	_bGlobalLoadDelayEnabled= true;
	_uGlobalLoadDelay		= 300;
	_vGlobalIgnoreTouch;
}

CSceneFrameMgr::~CSceneFrameMgr(void)
{
}

ISceneFrame* CSceneFrameMgr::ReplaceSceneForce( ISceneFrame* pScene )
{
	if (!pScene)return nullptr;
	
	_pRunningScene = pScene;
	MarkSceneChanging();
	ApiCocos2dx::ReplaceScene(pScene);
	
	if (_hHandler)
		_hHandler->OnSceneChanged();

	return pScene;
}

ISceneFrame* CSceneFrameMgr::ReplaceSceneForce( ISceneFrame* pScene,TransitionScene* pTransition )
{
	if (!pScene)return nullptr;
	if (!pTransition)return nullptr;

	_pRunningScene = pScene;
	MarkSceneChanging();
	ApiCocos2dx::ReplaceScene(pTransition);
	
	if (_hHandler)
		_hHandler->OnSceneChanged();

	return pScene;
}

ISceneFrame* CSceneFrameMgr::GetScene() const
{
	return _pRunningScene;
}

IPage* CSceneFrameMgr::GetRootPage()const
{
	if (!_pRunningScene)return nullptr;
	return _pRunningScene->GetRootPage();
}

bool CSceneFrameMgr::SetHandler( HSceneFrameMgr* hHandler )
{
	_hHandler = hHandler;
	return true;
}

bool CSceneFrameMgr::IsGlobalTimeLoadEnabled() const//是否忽略加载时间限制
{
	return _bGlobalLoadDelayEnabled;
}

bool CSceneFrameMgr::IsTimeLoadDelay( uint uLoadDelay ) const//是否是加载时间内(默认300毫秒)
{
	return IsGlobalTimeLoadEnabled() && ToolFrame::GetNowTimeMill() < _uGlobalTimeLoad + uLoadDelay;
}

bool CSceneFrameMgr::IsIgnoreTouchNode(const IPage* pPage, Ref *pSender, TouchEventType type )//是否是忽略触摸的节点
{
	if (!pPage)return false;

	//返回是否忽略
	switch(type)
	{
	case TOUCH_EVENT_BEGAN:
		if (pPage->IsTimeLoadDelay()){
			ToolFrame::Insert(_vGlobalIgnoreTouch,pSender);
			return true;
		}
		return false;
		break;
	case TOUCH_EVENT_MOVED:
		return ToolFrame::IsHasValue(_vGlobalIgnoreTouch,pSender);
		break;
	case TOUCH_EVENT_ENDED:
	case TOUCH_EVENT_CANCELED:
		return ToolFrame::EraseByValue(_vGlobalIgnoreTouch,pSender);
		break;
	}

	LOG_ERROR();
	return false;
}

bool CSceneFrameMgr::SetTouchEnabled( bool bEnabled )
{
	return _bTouchEnabled = bEnabled;
}

bool CSceneFrameMgr::IsTouchEnabled() const
{
	return _bTouchEnabled;
}

uint64 CSceneFrameMgr::GetGlobalTimeLoad() const
{
	return _uGlobalTimeLoad;
}

bool CSceneFrameMgr::SetGlobalLoadDelayEnabled( bool bEnabled/*=true*/ )
{
	_bGlobalLoadDelayEnabled = bEnabled;
	return true;
}

bool CSceneFrameMgr::SetGlobalLoadDelay( uint uDelay )
{
	_uGlobalLoadDelay = uDelay;
	return true;
}

uint CSceneFrameMgr::GetGlobalLoadDelay() const
{
	return _uGlobalLoadDelay;
}

bool CSceneFrameMgr::AddNewPage( IPage* pPage )
{
	if (!pPage)return false;

	//重置加载时间
	_uGlobalTimeLoad = ToolFrame::GetNowTimeMill();

	pPage->SetLoadDelay(_uGlobalLoadDelay);//默认为全局值
	_vInitPage.push_back(pPage);

	//回调
	_hHandler->OnNewPageAdd(pPage);
	return true;
}

bool CSceneFrameMgr::RemoveNewPage(IPage* pPage)
{
	if (!pPage)return true;
	return ToolFrame::EraseByValue(_vInitPage, pPage);
}

bool CSceneFrameMgr::TryInitPage()
{
	//场景切换中不初始化
	if (IsSceneChanging())return false;

	if (_vInitPage.empty())return true;

	IPage* pPage = ToolFrame::PopPtr(_vInitPage);
	while(pPage){
		pPage->Init();

		//回调
		_hHandler->OnNewPageInited(pPage);

		pPage = ToolFrame::PopPtr(_vInitPage);
	}

	//回调
	_hHandler->OnNewPageAllInited();
	return true;
}

bool CSceneFrameMgr::IsHasNewPage() const
{
	return !_vInitPage.empty();
}

bool CSceneFrameMgr::MarkSceneChanging()
{
	_bSceneChanging = true;
	return true;
}

bool CSceneFrameMgr::OnSceneChanged()
{
	_bSceneChanging = false;
	return true;
}

bool CSceneFrameMgr::IsSceneChanging() const
{
	return _bSceneChanging;
}

#endif //MACRO_LIB_COCOS2D
