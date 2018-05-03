#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "ISceneFrame.h"

class TOOLFRAME_DLL HSceneFrameMgr
{
public:
	virtual bool OnSceneChanged(){return false;}				//场景切换
	virtual bool OnRootPageChanged(){return false;}				//根页面切换
	virtual bool OnNewPageAdd(IPage* pPage){return false;}		//当新页面增加
	virtual bool OnNewPageInited(IPage* pPage){return false;}	//当新页面初始化完成
	virtual bool OnNewPageAllInited() { return false; }			//当所有新页面初始化完成
public:
	HSceneFrameMgr(){}
	virtual ~HSceneFrameMgr(){}
};

class TOOLFRAME_DLL CSceneFrameMgr
{
	typedef std::vector<IPage*>	VectorPage;
public:
	virtual bool	SetHandler(HSceneFrameMgr* hHandler);
public:
	//本场景根页面切换 重置(不会释放资源) 
	template<typename T>
	IPage*			ReplaceRootPage(int nUserDataInt=0,int nUserDataInt2=0,const std::string& sUserDataString="");
	
	//场景切换(无特效)
	template<typename T>//若本场景已经被运行 则返回空(无特效)
	ISceneFrame*	ReplaceScene(int nUserDataInt=0,int nUserDataInt2=0,const std::string& sUserDataString="");
	template<typename T>//强制替换本场景 不判断是否与当前场景相同
	ISceneFrame*	ReplaceSceneForce(int nUserDataInt=0,int nUserDataInt2=0,const std::string& sUserDataString="");

	//创建场景(用于 使用特效)
	template<typename T>//若本场景已经被运行 则返回空(无特效)
	ISceneFrame*	CreateScene(int nUserDataInt=0,int nUserDataInt2=0,const std::string& sUserDataString="");
	template<typename T>//强制创建 不判断是否与当前场景相同
	ISceneFrame*	CreateSceneForce(int nUserDataInt=0,int nUserDataInt2=0,const std::string& sUserDataString="");	

	//场景切换 执行
	ISceneFrame*	ReplaceSceneForce(ISceneFrame* pScene);//切换场景(无特效)
	ISceneFrame*	ReplaceSceneForce(ISceneFrame* pScene,TransitionScene* pTransition);//切换场景(使用特效)

	//页面相关
	virtual bool	AddNewPage(IPage* pPage);						//添加新页面
	virtual bool	RemoveNewPage(IPage* pPage);					//移除新页面
	virtual	bool	TryInitPage();									//初始化页面
	virtual bool	IsHasNewPage()const;							//是否还存在未初始化的页面

	virtual bool	MarkSceneChanging();							//标记场景切换中
	virtual bool	OnSceneChanged();								//场景切换完成
	virtual bool	IsSceneChanging()const;							//是否场景切换中

	virtual bool	SetTouchEnabled(bool bEnabled);					//打开全局是否可以触摸
	virtual bool	IsTouchEnabled()const;							//可否触摸

	virtual uint64	GetGlobalTimeLoad()const;						//获取最近一次页面加载时间
	virtual bool	SetGlobalLoadDelayEnabled(bool bEnabled=true);	//是否开启加载时间限制 默认true
	virtual bool	SetGlobalLoadDelay(uint uDelay);				//设置加载的延时时间
	virtual uint	GetGlobalLoadDelay()const;						//获取加载延时时间

	virtual bool	IsGlobalTimeLoadEnabled()const;					//是否忽略加载时间限制
	virtual bool	IsTimeLoadDelay(uint uLoadDelay) const;			//是否是加载时间内(默认300毫秒)
	virtual bool	IsIgnoreTouchNode(const IPage* pPage, Ref *pSender, TouchEventType type );//是否是忽略触摸的节点;
public:
	ISceneFrame*	GetScene()const;
	IPage*			GetRootPage()const;
public:
	CSceneFrameMgr(void);
	virtual ~CSceneFrameMgr(void);
public:
	ISceneFrame*		_pRunningScene;
	HSceneFrameMgr*		_hHandler;

	bool				_bSceneChanging;

	VectorPage			_vInitPage;					//待初始化页面

	bool				_bTouchEnabled;				//是否可以触碰(全局变量)
	bool				_bGlobalLoadDelayEnabled;	//是否要有加载延时
	uint				_uGlobalLoadDelay;			//加载延时时长
	uint64				_uGlobalTimeLoad;			//最近一次加载页面的时间(用于屏蔽 快速连击 导致创建多个相同页面 )
	VectorRef			_vGlobalIgnoreTouch;		//忽略触摸的节点
};

template<typename T>
ISceneFrame* CSceneFrameMgr::ReplaceScene( int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/ )
{
	//否则创建新场景压入场景替换
	ISceneFrame* pSceneFrame = CreateScene<T>(nUserDataInt,nUserDataInt2,sUserDataString);
	if (!pSceneFrame)return nullptr;
	return ReplaceSceneForce(pSceneFrame);
}

template<typename T>
//创建场景 若本场景已经被运行 则返回空
ISceneFrame* CSceneFrameMgr::CreateScene( int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/ )
{
	//如果就是自己这个场景本身 则 直接返回
	if (_pRunningScene)
	{
		T* pPage = dynamic_cast<T*>(_pRunningScene->GetRootPage());
		if (pPage)return nullptr;
	}

	return CreateSceneForce<T>(nUserDataInt,nUserDataInt2,sUserDataString);
}

template<typename T>
ISceneFrame* CSceneFrameMgr::CreateSceneForce( int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/ )
{
	ISceneFrame* pSceneFrame = ISceneFrame::Create();
	if (!pSceneFrame)return nullptr;

	pSceneFrame->SetSceneMgr(this);
	pSceneFrame->ReplaceRootPage<T>(nUserDataInt,nUserDataInt2,sUserDataString);
	return pSceneFrame;
}

template<typename T>
IPage* CSceneFrameMgr::ReplaceRootPage( int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/ )
{
	if (!_pRunningScene)return nullptr;

	IPage* pPage = _pRunningScene->ReplaceRootPage<T>(nUserDataInt,nUserDataInt2,sUserDataString);
	if (!pPage)return pPage;

	if (_hHandler)
		_hHandler->OnRootPageChanged();

	return pPage;
}

template<typename T>
ISceneFrame* CSceneFrameMgr::ReplaceSceneForce( int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/ )
{
	//否则创建新场景压入场景替换
	ISceneFrame* pSceneFrame = CreateSceneForce<T>(nUserDataInt,nUserDataInt2,sUserDataString);
	if (!pSceneFrame)return nullptr;
	return ReplaceSceneForce(pSceneFrame);
}

#endif //MACRO_LIB_COCOS2D
