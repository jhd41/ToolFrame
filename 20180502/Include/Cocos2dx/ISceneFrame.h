#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "IDataReceiverStream.h"
#include "IPage.h"

class TOOLFRAME_DLL ISceneFrame
	:public Scene
	,public ToolFrame::IDataReceiverStream
{
	COCOS2DX_CREATE_INIT(ISceneFrame);
public:
	template<typename T>
	IPage* ReplaceRootPage(int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/);
public:
	virtual bool	MarkUpdated();
	virtual bool	SetRootPage(IPage* pPage);
	virtual IPage*	GetRootPage()const;
public:
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
public:
	virtual bool OnConnected(UINT uClientID);
	virtual bool OnDisconnected(UINT uClientID);
	virtual bool OnConnectFailed(UINT uClientID);
	virtual bool OnRecv( UINT uClientID,ToolFrame::IMsgStream& msgStream);
public:
	virtual bool OnPause();											//暂停
	virtual bool OnResume();										//回到游戏
	virtual bool OnScreenSizeChanged(int newWidth, int newHeight);	//屏幕尺寸改变
private:
	virtual bool AddSceneManager(IPage* pPage);
private:
	CFIELD_PTR(CSceneFrameMgr*,SceneMgr,p);
public:
	ISceneFrame(void);
	virtual ~ISceneFrame(void);
private:
	IPage*						_pRootPage;		//根页面
};

template<typename T>
IPage* ISceneFrame::ReplaceRootPage( int nUserDataInt/*=0*/,int nUserDataInt2/*=0*/,const std::string& sUserDataString/*=""*/ )
{
	T* pPage = new T();
	if (!pPage)return nullptr;

	pPage->SetSceneMgr(GetSceneMgr());
	pPage->SetUserDataInt(nUserDataInt);
	pPage->SetUserDataInt2(nUserDataInt2);
	pPage->SetUserDataString(sUserDataString);
	
	SetRootPage(pPage);
	pPage->release();

	AddSceneManager(pPage);
	return pPage;
}

#endif //MACRO_LIB_COCOS2D
