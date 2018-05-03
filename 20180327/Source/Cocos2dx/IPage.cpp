#include "IPage.h"

#ifdef MACRO_LIB_COCOS2D

#include "ApiCocos2dx.h"
#include "RefRetain.h"
#include "WidgetPage.h"
#include "IPageCallBack.h"
#include "SceneFrameMgr.h"
#include "MLoger.h"

using namespace ui;

IPage::IPage(void)
{
	_bInited = false;
	_bEntered= false;
	_bEnterTransitionDidFinished = false;
	_bUpdated = false;

	_pRootPage = nullptr;
	_pRootRes = nullptr;

	_bDestoryed = false;

	_bRemoveThis = false;

	_uLoadDelay = 0;//默认为全局值
	_bEnabledTouchEvent = true;

	_ePageType = INVALID_ID;

	CleanReturnArg();

	SetParentNull();
	
	SetState(INVALID_ID);
	SetUpdated(false);

	SetUserDataInt(0);
	SetUserDataInt2(0);
	SetUserDataInt3(0);
	SetUserDataPtrNull();

	//加入指针管理
	//autorelease();

	//创建页面节点以及资源节点并建立关系
	CWidgetPage* pWidget = CWidgetPage::Create();
	ASSERT_LOG_ERROR(pWidget);
	pWidget->SetPage(this);
	pWidget->setLocalZOrder(ZORDER_PAGE_ROOT);//设置为页面层次
	_pRootPage = pWidget;
	ASSERT_LOG_ERROR(_pRootPage);
	_pRootRes = Node::create();
	_pRootRes->setLocalZOrder(ZORDER_RES_ROOT);//设置为资源层次
	_pRootPage->addChild(_pRootRes);

	_xTouchGroup.SetHandler(this);
	_xTouchGroup.Init();

	_xEventListener.SetHandler(this);
	_xEventListener.SetGraphPriorityNode(pWidget);
}

IPage::~IPage(void)
{
	Destory();
}

Node* IPage::LoadUIFile( const std::string& sFileName,int nZOder)
{
	Node* pWidget = ApiCocos2dx::LoadUIFile(sFileName);
	if (!pWidget)return nullptr;

	ASSERT_LOG_ERROR(_pRootRes);
	_pRootRes->addChild(pWidget,nZOder);
	return pWidget;
}

Node* IPage::GetRootNode()const
{
	return _pRootRes;
}

Node* IPage::GetRootPage() const
{
	return _pRootPage;
}

bool IPage::Show()
{
	if (!OnFireEvent())return false;
	if (!IsUpdated())return false;
	SetUpdated(false);

	IPageCallBack retain(this);
	return OnShow();
}

bool IPage::OnShow()
{
	return true;
}

bool IPage::OnCallBackPage( IPage* pPage )
{
	return false;
}

bool IPage::OnInit()
{
	return true;
}

bool IPage::OnTouchEvent( Ref *pSender, TouchEventType type )
{
	return false;
}

bool IPage::AddTouchEvent( Node* pWidget )
{
	return ApiCocos2dx::AddTouchEvent(pWidget,this, toucheventselector(IPage::touchEvent));
}

bool IPage::AddTouchEvent( Node* pRootWidget,const std::string& sName )
{
	return ApiCocos2dx::AddTouchEvent(pRootWidget,sName,this, toucheventselector(IPage::touchEvent));
}

bool IPage::AddTouchEvent( VectorNode& vButton )
{
	return ApiCocos2dx::AddTouchEvent(vButton,this, toucheventselector(IPage::touchEvent));
}

bool IPage::AddTouchEvent( const std::string& sName )
{
	return AddTouchEvent(GetRootNode(),sName);
}

bool IPage::OnCheckBoxChanged( Ref* pSender, CheckBoxEventType type )
{
	return false;
}

CheckBox* IPage::AddCheckBoxEvent(const Node* pRootWidget,const std::string& sName )
{
	return ApiCocos2dx::AddEventListenerCheckBox(pRootWidget,sName,this, checkboxselectedeventselector(IPage::checkboxEvent));
}

CheckBox* IPage::AddCheckBoxEvent( const std::string& sName )
{
	return AddCheckBoxEvent(GetRootNode(),sName);
}

CheckBox* IPage::AddCheckBoxEvent( VectorCheckBox& vCheckBox,const std::string& sName )
{
	CheckBox* pCheckBox = AddCheckBoxEvent(sName);
	if (!pCheckBox)return nullptr;

	vCheckBox.push_back(pCheckBox);
	return pCheckBox;
}

CheckBox* IPage::AddCheckBoxEvent( VectorCheckBox& vCheckBox,const Widget* pRootWidget,const std::string& sName )
{
	CheckBox* pCheckBox = AddCheckBoxEvent(pRootWidget,sName);
	if (!pCheckBox)return nullptr;

	vCheckBox.push_back(pCheckBox);
	return pCheckBox;
}

bool IPage::Init()
{	
	if (_bInited)return false;

	ASSERT_LOG_ERROR(_pRootPage);
	ASSERT_LOG_ERROR(_pRootRes);
	ASSERT_LOG_ERROR(_vAnimationQueue.Init(_pRootRes,this));
	ASSERT_LOG_ERROR(AddUpdateEveryFrame());

	SetUpdated(true);

	{
		IPageCallBack retain(this);
		if (!OnInit())return false;
		_bInited = true;
	}

	if (_bDestoryed)return false;

	if (_bEntered){
		IPageCallBack retain(this);
		if (!OnEnter())return false;
	}
		
	if (_bDestoryed)return false;

	if (_bEnterTransitionDidFinished){
		IPageCallBack retain(this);
		OnEnterTransitionDidFinish();
	}

	return true;
}

bool IPage::CallBackPage()
{
	//if (!OnFireEvent())return false;
	if (!GetParent())return false;

	IPageCallBack retain(this);
	return GetParent()->OnCallBackPage(this);
}
void IPage::touchEvent( Ref *pSender, TouchEventType type )
{
	//如果当前页不允许触摸
	if (!_bEnabledTouchEvent)return ;

	if (!OnFireEvent())return ;

	//当有界面加载延迟时间内 忽略新的触摸
	if (GetSceneMgr()->IsIgnoreTouchNode(this,pSender,type))
		return;

	//若还未展示出页面 忽略按钮效果
	if (!IsEntered() || !IsGlobalTouchEnabled())
		return;

	IPageCallBack retain(this);
	OnTouchEvent(pSender,type);
}

void IPage::checkboxEvent( Ref* pSender, CheckBoxEventType type )
{
	if (!OnFireEvent())return ;

	IPageCallBack retain(this);
	OnCheckBoxChanged(pSender,type);
}

bool IPage::OnDestory()
{
	return true;
}

bool IPage::Destory()
{
	if (_bDestoryed)return false;
	_bDestoryed = true;

	//移除子页面
	if(!_vPage.empty()){
		VectorPage vPage = _vPage;
		VectorPage::iterator itr;
		foreach(itr,vPage){
			IPage* pPage = *itr;
			ASSERT_LOG_ERROR(pPage);

			pPage->RemoveFromeParent();
		}
	}

	//移除自己
	OnDestory();

	_xEventListener.SetEnabledAll(false);
	_xTouchGroup.Destory();
	
	RemoveTimeUpdate();
	RemoveUpdateEveryFrame();
	_vAnimationQueue.Destory();

	_pRootPage->cleanup();

	GetSceneMgr()->RemoveNewPage(this);
	return true;
}

bool IPage::AddTimeUpdate( float fInterval, uint uRepeat, float fDelay, bool bPaused )
{
	GetSceneNode()->getScheduler()->schedule((SEL_SCHEDULE)&IPage::timeupdate,this,fInterval,uRepeat,fDelay,bPaused);
	return true;
}

bool IPage::OnUpdate( float dt )
{
	return true;
}

void IPage::update( float dt )
{
	if (_bDestoryed)return;

	if (_bRemoveThis) {
		RemoveFromeParent();
		return ;
	}

	if (_bDestoryed)return;
	
	_vAnimationQueue.RunActions();

	if (_bDestoryed)return;

	if (!OnFireEvent())return ;

	{
		IPageCallBack retain(this);
		OnUpdate(dt);
	}

	if (_bDestoryed)return;

	Show();
}

bool IPage::AddUpdateEveryFrame( bool bPaused /*= false*/ )
{
	ASSERT_LOG_ERROR(_pRootPage);
	_pRootPage->getScheduler()->scheduleUpdate(this,0,bPaused);
	return true;
}

bool IPage::OnEnter()
{
	return true;
}

bool IPage::OnEnterTransitionDidFinish()
{
	return true;
}

bool IPage::FireEventEnter()
{
	if (_bEntered)return false;
	_bEntered = true;

	if (!OnFireEvent())return false;
	
	IPageCallBack retain(this);
	return OnEnter();
}

bool IPage::FireEventEnterTransitionDidFinish()
{
	if (_bEnterTransitionDidFinished)return false;
	_bEnterTransitionDidFinished = true;
	if (!OnFireEvent())return false;

	IPageCallBack retain(this);
	return OnEnterTransitionDidFinish();
}

bool IPage::MarkUpdated( bool bChildren /*= true*/ )
{
	//设置子页面
	if (bChildren)
	{
		VectorPage vPage = _vPage;
		VectorPage::iterator itr;
		foreach(itr,vPage){
			IPage* pPage = *itr;
			ASSERT_LOG_ERROR(pPage);

			pPage->MarkUpdated(bChildren);
		}
	}

	return SetUpdated(true);
}

bool IPage::RemoveUpdateEveryFrame()
{
	ASSERT_LOG_ERROR(_pRootPage);
	_pRootPage->getScheduler()->unscheduleUpdate(this);
	return true;
}

bool IPage::RemoveTimeUpdate()
{
	ASSERT_LOG_ERROR(_pRootPage);
	_pRootPage->getScheduler()->unschedule((SEL_SCHEDULE)&IPage::timeupdate,this);
	return true;
}

bool IPage::SetUpdated( bool bUpdated )
{
	_bUpdated = bUpdated;
	return true;
}

bool IPage::IsUpdated() const
{
	return _bUpdated;
}

bool IPage::FireEventRecv( UINT uClientID,ToolFrame::IMsgStream& msgStream )
{
	if (!OnFireEvent())return false;

	bool bProcessed = false;

	IPageCallBack retain(this);
	bProcessed |= OnRecv(uClientID,msgStream);

	//设置子页面
	if(!_vPage.empty()){
		VectorPage vPage = _vPage;
		VectorPage::iterator itr;
		foreach(itr,vPage){
			IPage* pPage = *itr;
			ASSERT_LOG_ERROR(pPage);

			bProcessed |= pPage->FireEventRecv(uClientID,msgStream);
		}
	}
	return bProcessed;
}

bool IPage::OnRecv( UINT uClientID,ToolFrame::IMsgStream& msgStream )
{
	return false;
}

CAnimationQueue& IPage::GetAnimationQueue()
{
	return _vAnimationQueue;
}

const CAnimationQueue& IPage::GetAnimationQueue() const
{
	return _vAnimationQueue;
}

bool IPage::AddChild( IPage* pPage )
{
	if(!pPage)return false;
	if (!pPage->GetRootPage())return false;

	pPage->SetParent(this);
	pPage->retain();
	
	ToolFrame::Insert(_vPage,pPage);

	_pRootPage->addChild(pPage->GetRootPage());
	return true;
}

bool IPage::RemoveChild(IPage* pPage, bool bCleanUp)
{
	if(!pPage)return false;
	if (!ToolFrame::IsHasValue(_vPage,pPage))return false;

	ApiCocos2dx::RemoveFromParentAndCleanup(pPage->GetRootPage(), bCleanUp);

	pPage->release();
	ToolFrame::EraseByValue(_vPage,pPage);
	return true;
}

bool IPage::SetPageZOrder(int nZOrder)
{
	ASSERT_LOG_ERROR(_pRootPage);
	_pRootPage->setLocalZOrder(nZOrder);
	return true;
}

int IPage::GetPageZOrder() const
{
	ASSERT_LOG_ERROR(_pRootPage);
	return _pRootPage->getLocalZOrder();
}

const IPage::VectorPage& IPage::GetChildPage() const
{
	return _vPage;
}

bool IPage::IsInited() const
{
	return _bInited;
}

bool IPage::IsTopPage() const
{
	return !IsHasChildren();
}

bool IPage::IsHasChildren() const
{
	return !_vPage.empty();
}

bool IPage::RemoveFromeParent(bool bDestory)
{
	if (!GetParent())return false;
	return GetParent()->RemoveChild(this,bDestory);
}

bool IPage::MarkRemoveFromeParent()
{
	_bRemoveThis = true;
	return true;
}

bool IPage::OnTimeUpdate( float dt )
{
	return true;
}

void IPage::timeupdate( float dt )
{
	if (!OnFireEvent())return ;

	IPageCallBack retain(this);
	OnTimeUpdate(dt);
}

Node* IPage::FindNode( const std::string& sName )const
{
	return ApiCocos2dx::FindNode(_pRootRes,sName);
}

bool IPage::ChangeParentNode( const std::string& sChild,const std::string& sParent,bool bCleanUp /*= true*/ )
{
	return ApiCocos2dx::ChangeParentNode(GetRootNode(),sChild,sParent,bCleanUp);
}

bool IPage::SetSizeWidthWithResidue( const std::string& sName,const std::string& sArg1,const std::string& sArg2/*=""*/,const std::string& sArg3/*=""*/,const std::string& sArg4/*=""*/,const std::string& sArg5/*=""*/ )
{
	return SetSizeWithResidue(true,sName,sArg1,sArg2,sArg3,sArg4,sArg5);
}

bool IPage::SetSizeHeightWithResidue( const std::string& sName,const std::string& sArg1/*=""*/,const std::string& sArg2/*=""*/,const std::string& sArg3/*=""*/,const std::string& sArg4/*=""*/,const std::string& sArg5/*=""*/ )
{
	return SetSizeWithResidue(false,sName,sArg1,sArg2,sArg3,sArg4,sArg5);
}

bool IPage::SetSizeWithResidue( bool bWidth,const std::string& sName,const std::string& sArg1,const std::string& sArg2/*=""*/,const std::string& sArg3/*=""*/,const std::string& sArg4/*=""*/,const std::string& sArg5/*=""*/ )
{
	Node* pWidget = FindNode(sName);
	if (!pWidget)return false;

	Size xResidue = ApiCocos2dx::CalDesignResolutionSizeResidue(GetRootNode(),sArg1,sArg2,sArg3,sArg4,sArg5);

	if (bWidth)
		xResidue.height = pWidget->getContentSize().height;
	else
		xResidue.width = pWidget->getContentSize().width;

	return ApiCocos2dx::SetContentSize(pWidget,xResidue);
}

bool IPage::SetContentSize( const std::string& sName,const Size& size )
{
	Node* pWidget = FindNode(sName);
	if (!pWidget)return false;

	return ApiCocos2dx::SetContentSize(pWidget,size);
}

bool IPage::FireEventExit()
{
	if (!OnFireEvent())return false;

	IPageCallBack retain(this);
	return OnExit();
}

bool IPage::OnExit()
{
	return true;
}

bool IPage::OnAcceleration( Acceleration* pAcceleration, Event* pEvent )
{
	return false;
}

bool IPage::OnKeyPressed( EventKeyboard::KeyCode eKeyCode, Event* pEvent )
{
	return false;
}

bool IPage::OnKeyReleased( EventKeyboard::KeyCode eKeyCode, Event* pEvent )
{
	return false;
}

bool IPage::OnTouchBegan( Touch* touch, Event *unusedEvent )
{
	return _xTouchGroup.OnTouchBegan(touch,unusedEvent);
}

bool IPage::OnTouchMoved( Touch* touch, Event *unusedEvent )
{
	return _xTouchGroup.OnTouchMoved(touch,unusedEvent);
}

bool IPage::OnTouchEnded( Touch* touch, Event *unusedEvent )
{
	return _xTouchGroup.OnTouchEnded(touch,unusedEvent);
}

bool IPage::OnTouchCancelled( Touch* touch, Event *unusedEvent )
{
	return _xTouchGroup.OnTouchCancelled(touch,unusedEvent);
}

bool IPage::ListenKeyboard( bool bEnabled )
{
	return _xEventListener.SetKeyboardEnabled(bEnabled);
}

bool IPage::ListenAccelerometer( bool bEnabled )
{
	return _xEventListener.SetAccelerometerEnabled(bEnabled);
}

bool IPage::ListenTouch( bool bEnabled,bool bShare /*= false*/ )
{
	return _xEventListener.SetTouchEnabled(bEnabled,bShare);
}

bool IPage::IsListenKeyboard() const
{
	return _xEventListener.IsKeyboardEnabled();
}

bool IPage::IsListenAccelerometer() const
{
	return _xEventListener.IsAccelerometerEnabled();
}

bool IPage::IsListenTouch() const
{
	return _xEventListener.IsTouchEnabled();
}

bool IPage::FireEventConnected(uint uClientID)
{
	if (!OnFireEvent())return false;

	//设置子页面
	IPageCallBack retain(this);
	if (OnConnected(uClientID))return true;
	
	if(!_vPage.empty()){
		VectorPage vPage = _vPage;
		VectorPage::iterator itr;
		foreach(itr,vPage){
			IPage* pPage = *itr;
			ASSERT_LOG_ERROR(pPage);

			pPage->FireEventConnected(uClientID);
		}
	}

	return false;
}

bool IPage::FireEventDisconnected(uint uClientID)
{
	if (!OnFireEvent())return false;

	//设置子页面
	IPageCallBack retain(this);
	if (OnDisconnected(uClientID))return true;

	if(!_vPage.empty()){
		VectorPage vPage = _vPage;
		VectorPage::iterator itr;
		foreach(itr,vPage){
			IPage* pPage = *itr;
			ASSERT_LOG_ERROR(pPage);

			pPage->FireEventDisconnected(uClientID);
		}
	}

	return false;
}

bool IPage::FireEventConnectFailed( uint uClientID )
{
	if (!OnFireEvent())return false;

	//设置子页面
	IPageCallBack retain(this);
	if (OnConnectFailed(uClientID))return true;

	if(!_vPage.empty()){
		VectorPage vPage = _vPage;
		VectorPage::iterator itr;
		foreach(itr,vPage){
			IPage* pPage = *itr;
			ASSERT_LOG_ERROR(pPage);

			pPage->FireEventConnectFailed(uClientID);
		}
	}

	return false;
}

bool IPage::OnConnected( uint uClientID )
{
	return false;
}

bool IPage::OnDisconnected( uint uClientID )
{
	return false;
}

bool IPage::OnConnectFailed( uint uClientID )
{
	return false;
}

bool IPage::RemovePageChildren(bool bCleanUp)
{
	ASSERT_LOG_ERROR(_pRootPage);
	ASSERT_LOG_ERROR(_pRootRes);
	if (!_pRootPage)return false;
	if (!_pRootRes)return false;

	//先移除资源
	_pRootRes->removeAllChildrenWithCleanup(bCleanUp);

	//再移除资源根节点以外的其他节点
	CRefRetain ref(_pRootRes);
	_pRootPage->removeAllChildrenWithCleanup(bCleanUp);
	return true;
}

bool IPage::RemoveResChildren(bool bCleanUp /*= true*/)
{
	if (!_pRootRes)return false;

	_pRootRes->removeAllChildrenWithCleanup(bCleanUp);
	return true;
}

bool IPage::FireEventOnPause()
{
	if (!OnFireEvent())return false;

	//设置子页面
	IPageCallBack retain(this);
	if (OnPause())return true;

	if(!_vPage.empty()){
		VectorPage vPage = _vPage;
		VectorPage::iterator itr;
		foreach(itr,vPage){
			IPage* pPage = *itr;
			ASSERT_LOG_ERROR(pPage);

			pPage->FireEventOnPause();
		}
	}

	return false;
}

bool IPage::FireEventOnResume()
{
	if (!OnFireEvent())return false;

	//设置子页面
	IPageCallBack retain(this);
	if (OnResume())return true;

	if(!_vPage.empty()){
		VectorPage vPage = _vPage;
		VectorPage::iterator itr;
		foreach(itr,vPage){
			IPage* pPage = *itr;
			ASSERT_LOG_ERROR(pPage);

			pPage->FireEventOnResume();
		}
	}

	return false;
}

bool IPage::FireEventOnScreenSizeChanged( int nWidth, int nHeight )
{
	if (!OnFireEvent())return false;

	//设置子页面
	IPageCallBack retain(this);
	if (OnScreenSizeChanged(nWidth,nHeight))return true;

	if(!_vPage.empty()){
		VectorPage vPage = _vPage;
		VectorPage::iterator itr;
		foreach(itr,vPage){
			IPage* pPage = *itr;
			ASSERT_LOG_ERROR(pPage);

			pPage->FireEventOnScreenSizeChanged(nWidth,nHeight);
		}
	}

	return false;
}

bool IPage::OnPause()
{
	return false;
}

bool IPage::OnResume()
{
	return false;
}

bool IPage::OnScreenSizeChanged( int newWidth, int newHeight )
{
	return false;
}

bool IPage::SetVisible( const std::string& sName,bool bVisible )
{
	ASSERT_LOG_ERROR(_pRootRes);
	return ApiCocos2dx::SetVisible(_pRootRes,sName,bVisible);
}

bool IPage::SetEnabled( const std::string& sName,bool bEnabled )
{
	ASSERT_LOG_ERROR(_pRootRes);
	return ApiCocos2dx::SetEnabled(_pRootRes,sName,bEnabled);
}

bool IPage::QueueClose()
{
	return GetAnimationQueue().ActionCallBack(&IPage::OnQueueClose,this);
}

bool IPage::QueueCallBack()
{
	return GetAnimationQueue().ActionCallBack(&IPage::OnQueueCallBack,this);
}

bool IPage::OnQueueClose()
{
	return RemoveFromeParent();
}

bool IPage::OnQueueCallBack()
{
	return CallBackPage();
}

const Size& IPage::GetContentSize( const std::string& sName )const
{
	const Node* pWidget = FindNode(sName);
	if (!pWidget)return Size::ZERO;

	return ApiCocos2dx::GetContentSize(pWidget);
}

bool IPage::IsOutOfScreen( const VectorString& vWidget,bool bWidth ) const
{
	return ApiCocos2dx::IsOutOfScreen(_pRootRes,vWidget,bWidth);
}

bool IPage::IsOutOfScreen(bool bWidth,const std::string& sName1/*=""*/,const std::string& sName2/*=""*/,const std::string& sName3/*=""*/,const std::string& sName4/*=""*/,const std::string& sName5/*=""*/ )
{
	return ApiCocos2dx::IsOutOfScreen(_pRootRes,bWidth,sName1,sName2,sName3,sName4,sName5);
}

Node* IPage::GetSceneNode() const
{
	return ApiCocos2dx::FindRootNode(_pRootPage);
}

bool IPage::IsEntered() const
{
	return _bEntered;
}

bool IPage::SetLoadDelay( uint uDelay )
{
	_uLoadDelay = uDelay;
	return true;
}

uint IPage::GetLoadDelay() const
{
	return _uLoadDelay;
}

bool IPage::OnFireEvent()
{
	if (!IsInited())return false;
	return true;
}

bool IPage::SetGlobalTouchEnabled( bool bEnabled )
{
	return GetSceneMgr()->SetTouchEnabled(bEnabled);
}

bool IPage::IsGlobalTouchEnabled() const
{
	return GetSceneMgr()->IsTouchEnabled();
}

bool IPage::IsTimeLoadDelay() const
{
	return GetSceneMgr()->IsTimeLoadDelay(_uLoadDelay);
}

bool IPage::AddSceneManager( IPage* pPage )
{
	return GetSceneMgr()->AddNewPage(pPage);
}

bool IPage::SetTouchEventEnabled( bool bEnabled )
{
	_bEnabledTouchEvent = bEnabled;
	return true;
}

bool IPage::IsTouchEventEnabled() const
{
	return _bEnabledTouchEvent;
}

bool IPage::SetReturnType( int eReturnType )
{
	_eReturnType = eReturnType;
	return true;
}

bool IPage::SetReturnArgInt1( int nArg )
{
	_nReturnArg1 = nArg;
	return true;
}

bool IPage::SetReturnArgInt2( int nArg )
{
	_nReturnArg2 = nArg;
	return true;
}

bool IPage::SetReturnArgString1( const std::string& sArg )
{
	_sReturnArg1 = sArg;
	return true;
}

bool IPage::SetReturnArgString2( const std::string& sArg )
{
	_sReturnArg2 = sArg;
	return true;
}

int IPage::GetReturnType() const
{
	return _eReturnType;
}

int IPage::GetReturnArgInt1() const
{
	return _nReturnArg1;
}

int IPage::GetReturnArgInt2() const
{
	return _nReturnArg2;
}

const std::string& IPage::GetReturnArgString1() const
{
	return _sReturnArg1;
}

const std::string& IPage::GetReturnArgString2() const
{
	return _sReturnArg2;
}

bool IPage::CleanReturnArg()
{
	_eReturnType = INVALID_ID;

	_nReturnArg1 = 0;
	_nReturnArg2 = 0;

	_sReturnArg1 = "";
	_sReturnArg2 = "";
	return true;
}

bool IPage::SetPageType( int ePageType )
{
	_ePageType = ePageType;
	return true;
}

int IPage::GetPageType() const
{
	return _ePageType;
}

CTouchGroup& IPage::GetTouchGroup()
{
	return _xTouchGroup;
}

const CTouchGroup& IPage::GetTouchGroup() const
{
	return _xTouchGroup;
}

CInputEventListener& IPage::GetInputListener()
{
	return _xEventListener;
}

const CInputEventListener& IPage::GetInputListener() const
{
	return _xEventListener;
}

#endif //MACRO_LIB_COCOS2D
