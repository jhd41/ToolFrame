#pragma once
#include "MacroCocos2dx.h"
#include "IMsgStream.h"
#include "AnimationQueue.h"
#include "TouchGroup.h"
#include "InputEventListener.h"

//页面
//为了保证页面的层次关系一致，所有的页面的节点形成的树都只为页面层次关系服务，每个页面有个儿子叫做该页面的根节点用于所有资源的挂载和显示
//加载时间限制 防止多次重复点击

#ifdef MACRO_LIB_COCOS2D

class CSceneFrameMgr;
class TOOLFRAME_DLL IPage
	:public Ref
	,public HAnimationQueue
	,public HTouchListener
	,public HInputEventListener
{
public:
	enum ERootZorder
	{
		ZORDER_RES_ROOT		= 0,//资源层次
		ZORDER_PAGE_ROOT	= 1,//页面层次
	};
	typedef std::vector<IPage*>	VectorPage;
public:
	virtual bool	Init();									//初始化
	virtual bool	CallBackPage();							//回调
	virtual bool	MarkUpdated(bool bChildren = true);		//标记需要更新
	virtual CAnimationQueue&		GetAnimationQueue();
	virtual const CAnimationQueue&	GetAnimationQueue()const;
	virtual bool	IsInited()const;						//是否初始化
	virtual bool	IsEntered()const;						//是否已经展示
	virtual bool	IsTopPage()const;
	virtual bool	IsHasChildren()const;
	virtual bool	MarkRemoveFromeParent();
	virtual Node*	GetRootNode()const;								//获取资源根节点(供外部资源挂载)
	
	virtual bool	SetLoadDelay(uint uDelay);						//设置当前页 加载延迟时间
	virtual uint	GetLoadDelay()const;							//获取当前页 加载延迟时间

	virtual bool	SetTouchEventEnabled(bool bEnabled);			//设置当前页 触摸事件可用状态
	virtual bool	IsTouchEventEnabled()const;						//获取当前页 触摸事件可用状态

	virtual CTouchGroup&		GetTouchGroup();
	virtual const CTouchGroup&	GetTouchGroup()const;

	virtual	CInputEventListener&		GetInputListener();
	virtual const CInputEventListener&	GetInputListener()const;

	//全局函数
	virtual bool	ListenKeyboard(bool bEnabled);					//打开键盘
	virtual bool	ListenAccelerometer(bool bEnabled);				//打开重力感应
	virtual bool	ListenTouch(bool bEnabled,bool bShare = false);	//打开触摸

	virtual bool	IsListenKeyboard()const;
	virtual bool	IsListenAccelerometer()const;
	virtual bool	IsListenTouch()const;

	virtual bool	IsTimeLoadDelay() const;						//是否是加载时间内(默认300毫秒)
	virtual bool	SetGlobalTouchEnabled(bool bEnabled);			//打开全局是否可以触摸
	virtual bool	IsGlobalTouchEnabled()const;					//全局可否触摸

	template<typename T>
	T*	CreateChildPage(int nUserDataInt=0,int nUserDataInt2=0,const std::string& sUserDataString="");
	template<typename T>
	T*	ReplaceThisPage(int nUserDataInt=0,int nUserDataInt2=0,const std::string& sUserDataString="");

	virtual bool		QueueClose();	//加入动画队列 关闭自己
	virtual bool		QueueCallBack();//加入动画队列 CallBack

	//自定义参数
	virtual bool		SetPageType(int ePageType);//设置页面类型 用于上层逻辑判断该页面的类型
	virtual int			GetPageType()const;

	//返回值
	virtual bool				CleanReturnArg();
	virtual bool				SetReturnType(int eReturnType);
	virtual bool				SetReturnArgInt1(int nArg);
	virtual bool				SetReturnArgInt2(int nArg);
	virtual bool				SetReturnArgString1(const std::string& sArg);
	virtual bool				SetReturnArgString2(const std::string& sArg);
	virtual int					GetReturnType()const;
	virtual int					GetReturnArgInt1()const;
	virtual int					GetReturnArgInt2()const;
	virtual const std::string&	GetReturnArgString1()const;
	virtual const std::string&	GetReturnArgString2()const;
public:
	virtual bool		Destory();						//销毁(外部不要调用)
	virtual bool		AddChild(IPage* pPage);
	virtual bool		RemoveChild(IPage* pPage,bool bCleanUp = true);
	virtual Node*		GetRootPage()const;				//获取页面根节点(内部使用 外部尽可能不要调用)
	virtual bool		SetPageZOrder(int nZOrder);		//设置页面的根节点ZOrder，务必大于ZORDER_PAGE_ROOT 查看 ERootZorder 
	virtual int			GetPageZOrder()const;
	virtual const VectorPage& GetChildPage()const;

	template<typename T>
	T*		FindPage()const;
protected:
	virtual Node*		GetSceneNode()const;
	
	virtual Node*		LoadUIFile(const std::string& sFileName,int nZOder=0);
	virtual Node*		FindNode(const std::string& sName)const;
	template<typename T>
	bool				FindNode(T*& t, const std::string& sName)const;
	virtual bool		SetVisible(const std::string& sName,bool bVisible);
	virtual bool		SetEnabled(const std::string& sName,bool bEnabled);
	virtual bool		AddTouchEvent(Node* pWidget);
	virtual bool		AddTouchEvent(Node* pRootWidget,const std::string& sName);
	virtual bool		AddTouchEvent(VectorNode& vButton);
	virtual bool		AddTouchEvent(const std::string& sName);
	virtual CheckBox*	AddCheckBoxEvent(const std::string& sName);
	virtual CheckBox*	AddCheckBoxEvent(const Node* pRootWidget,const std::string& sName);
	virtual CheckBox*	AddCheckBoxEvent(VectorCheckBox& vCheckBox,const std::string& sName);
	virtual CheckBox*	AddCheckBoxEvent(VectorCheckBox& vCheckBox,const Widget* pRootWidget,const std::string& sName);
	
	virtual bool		SetContentSize(const std::string& sName,const Size& size);
	virtual bool		SetSizeWidthWithResidue(const std::string& sName,const std::string& sArg1="",const std::string& sArg2="",const std::string& sArg3="",const std::string& sArg4="",const std::string& sArg5="");
	virtual bool		SetSizeHeightWithResidue(const std::string& sName,const std::string& sArg1="",const std::string& sArg2="",const std::string& sArg3="",const std::string& sArg4="",const std::string& sArg5="");
	virtual bool		SetSizeWithResidue(bool bWidth,const std::string& sName,const std::string& sArg1,const std::string& sArg2="",const std::string& sArg3="",const std::string& sArg4="",const std::string& sArg5="");

	virtual const Size& GetContentSize(const std::string& sName)const;
	virtual bool		IsOutOfScreen(const VectorString& vWidget,bool bWidth)const;//是否超过屏幕
	virtual bool		IsOutOfScreen(bool bWidth,const std::string& sName1="",const std::string& sName2="",const std::string& sName3="",const std::string& sName4="",const std::string& sName5="");

	virtual bool		ChangeParentNode(const std::string& sChild,const std::string& sParent,bool bCleanUp = true);
	
	virtual bool		AddUpdateEveryFrame(bool bPaused = false);
	virtual bool		RemoveUpdateEveryFrame();
	virtual bool		AddTimeUpdate(float fInterval, uint uRepeat, float fDelay, bool bPaused = false);
	virtual bool		RemoveTimeUpdate();
	
	virtual bool		RemovePageChildren(bool bCleanUp = true);	//移除页面所有子节点(包括所有子页面以及资源)
	virtual bool		RemoveResChildren(bool bCleanUp = true);	//移除当前页面所有资源(不包括子页面)
	virtual bool		RemoveFromeParent(bool bDestory = true);

	//触发事件
public:
	virtual bool		FireEventEnter();
	virtual bool		FireEventExit();
	virtual bool		FireEventEnterTransitionDidFinish();

	//广播
	virtual bool		FireEventRecv(UINT uClientID,ToolFrame::IMsgStream& msgStream);
	virtual bool		FireEventConnected(uint uClientID);
	virtual bool		FireEventDisconnected(uint uClientID);
	virtual bool		FireEventConnectFailed(uint uClientID);
	virtual bool		FireEventOnPause();
	virtual bool		FireEventOnResume();
	virtual bool		FireEventOnScreenSizeChanged(int nWidth, int nHeight);

	//子类实现
protected:
	virtual bool OnFireEvent();

	virtual bool OnInit();		//初始化
	virtual bool OnDestory();	//被销毁
	virtual bool OnShow();		//显示
	virtual bool OnCallBackPage(IPage* pPage);
	virtual bool OnTouchEvent		(Ref *pSender, TouchEventType type);
	virtual bool OnCheckBoxChanged	(Ref* pSender, CheckBoxEventType type);
	virtual bool OnUpdate(float dt);
	virtual bool OnTimeUpdate(float dt);
	virtual bool OnEnter();						//即将显示
	virtual bool OnExit();						//即将离开
	virtual bool OnEnterTransitionDidFinish();	//旋转变换完成
	virtual bool OnConnected(uint uClientID);
	virtual bool OnDisconnected(uint uClientID);
	virtual bool OnConnectFailed(uint uClientID);
	virtual bool OnRecv(uint uClientID,ToolFrame::IMsgStream& msgStream);		//协议接收(被处理返回true)
	virtual bool OnAcceleration(Acceleration* pAcceleration, Event* pEvent);	//重力事件回调(被处理返回true)
	virtual bool OnKeyPressed(EventKeyboard::KeyCode eKeyCode, Event* pEvent);	//按下事件回调(被处理返回true)
	virtual bool OnKeyReleased(EventKeyboard::KeyCode eKeyCode, Event* pEvent);	//释放事件回调(被处理返回true)
	virtual bool OnTouchBegan(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchMoved(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchEnded(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchCancelled(Touch* touch, Event *unusedEvent);

	virtual bool OnPause();											//暂停
	virtual bool OnResume();										//回到游戏
	virtual bool OnScreenSizeChanged(int newWidth, int newHeight);	//屏幕尺寸改变
private:
	virtual bool Show();		//显示
	virtual bool SetUpdated(bool bUpdated);
	virtual bool IsUpdated()const;
private:
	void touchEvent(Ref *pSender, TouchEventType type);
	void checkboxEvent(Ref* pSender, CheckBoxEventType type);
	bool OnQueueClose();
	bool OnQueueCallBack();
	bool AddSceneManager(IPage* pPage);
public:
	virtual void update(float dt);
	virtual void timeupdate(float dt);
private:
	CFIELD_PTR(IPage*,Parent,p);
	CFIELD_INT(UserDataInt);
	CFIELD_INT(UserDataInt2);
	CFIELD_INT(UserDataInt3);
	CFIELD_STRING(UserDataString);
	CFIELD_STRING(UserDataString2);
	CFIELD_PTR(void*,UserDataPtr,p);
	CFIELD_INT(State);
	CFIELD_PTR(CSceneFrameMgr*,SceneMgr,p);
public:
	IPage(void);
	virtual ~IPage(void);
private:
	bool					_bInited;
	bool					_bEntered;
	bool					_bEnterTransitionDidFinished;
	bool					_bUpdated;
	bool					_bDestoryed;
	Node*					_pRootPage;		//页面的根	真正的根
	Node*					_pRootRes;		//资源的根	挂载资源用
	CAnimationQueue			_vAnimationQueue;
	VectorPage				_vPage;
	bool					_bRemoveThis;
	uint					_uLoadDelay;				//当前页加载延迟时间
	bool					_bEnabledTouchEvent;		//当前页触摸事件可用

	int						_ePageType;

	int						_eReturnType;
	int						_nReturnArg1;
	int						_nReturnArg2;
	std::string				_sReturnArg1;
	std::string				_sReturnArg2;

	CInputEventListener		_xEventListener;
	CTouchGroup				_xTouchGroup;
};

template<typename T>
T* IPage::ReplaceThisPage( int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/ )
{
	IPage* pPage = GetParent();
	if (!pPage)return nullptr;

	RemoveFromeParent();
	return pPage->CreateChildPage<T>(nUserDataInt,nUserDataInt2,sUserDataString);
}

template<typename T>
T* IPage::FindPage() const
{
	VectorPage::const_iterator itr;
	foreach(itr, _vPage) {
		T* pPage = dynamic_cast<T*>(*itr);
		if (pPage)
			return pPage;
	}

	return nullptr;
}

template<typename T>
bool IPage::FindNode( T*& t, const std::string& sName )const
{
	t = dynamic_cast<T*>(FindNode(sName));
	return !!t;
}

template<typename T>
T* IPage::CreateChildPage( int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/ )
{
	T* pPage = new T();
	if (!pPage)return nullptr;

	pPage->SetSceneMgr(GetSceneMgr());
	pPage->SetUserDataInt(nUserDataInt);
	pPage->SetUserDataInt2(nUserDataInt2);
	pPage->SetUserDataString(sUserDataString);
	
	this->AddChild(pPage);
	pPage->release();

	AddSceneManager(pPage);
	return pPage;
}

#endif //MACRO_LIB_COCOS2D
