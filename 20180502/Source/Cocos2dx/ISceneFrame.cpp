#include "ISceneFrame.h"

#ifdef MACRO_LIB_COCOS2D

#include "ToolFrame.h"
#include "SceneFrameMgr.h"

ISceneFrame::ISceneFrame(void)
{
	_pRootPage = nullptr;
}

ISceneFrame::~ISceneFrame(void)
{
	if (_pRootPage){
		_pRootPage->release();
		_pRootPage = nullptr;
	}
}

void ISceneFrame::onEnter()
{
	//清理内存
	if (ApiCocos2dx::IsAutoPurgeCache())
	{
		ApiCocos2dx::PurgeCachedData();
		ToolFrame::PurgeMemory(ToolFrame::GetProcessId());	//清理当前进程内存
	}

	GetSceneMgr()->OnSceneChanged();
	GetSceneMgr()->TryInitPage();

	Scene::onEnter();
}

void ISceneFrame::onExit()
{
	Scene::onExit();

	if (_pRootPage){
		_pRootPage->release();
		_pRootPage = nullptr;
	}


	//少量回收内存
	if (ApiCocos2dx::IsAutoPurgeCache()){
		ApiCocos2dx::PurgeTextureCache(false);
		ToolFrame::PurgeMemory(ToolFrame::GetProcessId());	//清理当前进程内存
	}
}

void ISceneFrame::onExitTransitionDidStart()
{
	Scene::onExitTransitionDidStart();
}

void ISceneFrame::onEnterTransitionDidFinish()
{
	CCScene::onEnterTransitionDidFinish();
}

bool ISceneFrame::MarkUpdated()
{
	if (!_pRootPage)return false;

	return _pRootPage->MarkUpdated();
}

bool ISceneFrame::OnConnected( UINT uClientID )
{
	if (!_pRootPage)return false;

	return _pRootPage->FireEventConnected(uClientID);
}

bool ISceneFrame::OnDisconnected( UINT uClientID )
{
	if (!_pRootPage)return false;

	return _pRootPage->FireEventDisconnected(uClientID);
}

bool ISceneFrame::OnConnectFailed( UINT uClientID )
{
	if (!_pRootPage)return false;

	return _pRootPage->FireEventConnectFailed(uClientID);
}

bool ISceneFrame::OnRecv( UINT uClientID,ToolFrame::IMsgStream& msgStream )
{
	if (!_pRootPage)return false;

	return _pRootPage->FireEventRecv(uClientID,msgStream);
}

bool ISceneFrame::SetRootPage( IPage* pPage )
{
	if (_pRootPage){
		ApiCocos2dx::RemoveFromParentAndCleanup(_pRootPage->GetRootPage(),true);
		_pRootPage->release();
		_pRootPage=nullptr;
	}
		
	_pRootPage = pPage;
	if (_pRootPage)
	{
		_pRootPage->retain();
		_pRootPage->SetGlobalTouchEnabled(true);
		this->addChild(_pRootPage->GetRootPage());
	}
	return true;
}

IPage* ISceneFrame::GetRootPage()const
{
	return _pRootPage;
}

bool ISceneFrame::OnPause()
{
	if (!_pRootPage)return false;

	return _pRootPage->FireEventOnPause();
}

bool ISceneFrame::OnResume()
{
	if (!_pRootPage)return false;

	return _pRootPage->FireEventOnResume();
}

bool ISceneFrame::OnScreenSizeChanged( int newWidth, int newHeight )
{
	if (!_pRootPage)return false;

	return _pRootPage->FireEventOnScreenSizeChanged(newWidth,newHeight);
}

bool ISceneFrame::AddSceneManager( IPage* pPage )
{
	if (!pPage)return false;
	return GetSceneMgr()->AddNewPage(pPage);
}

#endif //MACRO_LIB_COCOS2D
