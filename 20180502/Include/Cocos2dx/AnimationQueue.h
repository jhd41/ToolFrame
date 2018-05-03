#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "HAnimationQueue.h"
#include "IActionAnimation.h"
#include "MLoger.h"

//动画队列
class TOOLFRAME_DLL CAnimationQueueMulit;
class TOOLFRAME_DLL CAnimationQueue
	:public Ref
{
	COCOS2DX_CREATE(CAnimationQueue);
	typedef std::list<IActionAnimation*> VectorAnimation;
public:
	//全局设置
	bool	Init(Node* pParent,HAnimationQueue* pHandler);
	bool	Destory();
	bool	IsEmpty()const;
	bool	RunAction();
	bool	IsStoped()const;
	bool	RunActions();
	bool	IsWaitCallBack()const;
	bool	SetModeSelfRun();//自运行模式
	bool	StopModeSelfRun();//自运行模式

	bool	SetZOrder(int nZOrder);
	int		GetZOrder()const;
	bool	SetSpeed(float fSpeed = 1.0f);
	float	GetSpeed();
	Node*	GetParentNode();

	//动作命令
public:
	bool ActionAddTarget(Node* pNode,int nIndex = -1);//-1代表添加
	bool ActionAddTarget(Widget* pRootWidget,const std::string& sName,int nIndex = -1);//-1代表添加

	bool ActionClearTarget(int nIndex = -1);			//-1代表最近添加的
	bool ActionClearAllTarget();

	bool ActionSetCurTarget(int nIndex = -1);	//设置当前目标
	bool ActionRemoveCurTarget();				//移除当前目标

	bool ActionStoreCurTarget();			//储存当前目标
	bool ActionRestoreCurTarget();			//还原当前目标为存储的目标

	bool ActionSetPostion(const Point& ptPostion);
	bool ActionSetWorldPostion(const Point& ptPostion);
	bool ActionSetWorldPostion(const Node* pNodePostion);
	bool ActionSetZOrder(int nZOrder);
	template<typename T,typename TValue>
	bool ActionSetValue(const TValue& nValue );	
	bool ActionSetVisible(bool bVisible);
	bool ActionSetEnabled(bool bEnabled);
	bool ActionSetRotation(float fRotation);
	bool ActionSetOpacity(GLubyte uOpacity,bool bChildren = true);
	bool ActionSetScale(float fScale = 1.0f);
	bool ActionSetScale(float fScaleX,float fScaleY);
	bool ActionSetSpeed(float fSpeed);

	template<typename T,typename TValue> 
	bool ActionActionsSetValue( const TValue& nValue,float fDuration = 1.f);

	bool ActionRemoveFromParent(bool bCleanUp = true);
	bool ActionChangeParent(Node* pNodeParent,bool bCleanUp = true);

	bool ActionClone(Widget* pNode);//克隆(添加新目标)
	
	bool ActionMoveTo(const Point& ptPostion,float fDuration = 1.0f);
	bool ActionMoveBy(const Point& ptPostion,float fDuration = 1.0f);
	bool ActionDelay(float fDuration = 1.0f);

	bool ActionFadeIn(float fDuration = 1.0f);
	bool ActionFadeOut(float fDuration = 1.0f);
	bool ActionFadeInEx(float fDuration = 1.0f);
	bool ActionFadeOutEx(float fDuration = 1.0f);

	bool ActionNextFrame(float fDuration,const Point& ptPostion,float fRotation,GLubyte uOpacity,float fScale,const std::string& sAnimationName);

	bool ActionAnimationCreate(const std::string& sFileName);
	bool ActionAnimationCreate(const std::string& sFileName,const Point& ptPostion);

	bool ActionAnimationToFrame(int nFrameIndex);
	bool ActionAnimationBoneAdd(const std::string& sParentBone,const std::string& sNewBone,Node* pNode);

	bool ActionAnimationPlay(int nLoop = 0);														//播放指定循环次动画后回调(动画会继续在最后一个动画循环播放)
	bool ActionAnimationPlay(const std::string& sName,int nLoop = 0);
	bool ActionAnimationPlay(const std::string& sName1,const std::string& sName2,int nLoop = 0);
	bool ActionAnimationPlay(const VectorString& vName,int nLoop = 0);

	bool ActionAnimationPlayFile(const Point& ptPostion,const std::string& sFileName,int nLoop=-1);														//播放指定循环次动画后回调(动画会回调后移除)
	bool ActionAnimationPlayFile(const Point& ptPostion,const std::string& sFileName,const std::string& sName,int nLoop=-1);
	bool ActionAnimationPlayFile(const Point& ptPostion,const std::string& sFileName,const std::string& sName1,const std::string& sName2,int nLoop=-1);
	bool ActionAnimationPlayFile(const Point& ptPostion,const std::string& sFileName,const VectorString& vName,int nLoop=-1);

	bool ActionAnimationDisplayAdd(const std::string& sName,Node* pNode,int nIndex = -1);
	bool ActionAnimationDisplayRemove(const std::string& sName,int nIndex = 0);
	bool ActionAnimationDisplayChange(const std::string& sName,int nIndex = 0,bool bForce = true);

	bool ActionSpinePlay(const std::string& sName,int nLoop = 0,float fDelay=0.f);
	bool ActionSpinePlay(const std::string& sName1,const std::string& sName2,int nLoop = 0,float fDelay=0.f);
	bool ActionSpinePlay(const VectorString& vName,int nLoop = 0,float fDelay=0.f);

	bool ActionCallBack(int nUserInt =0);
	template<typename TFun>
	bool ActionCallBack(const TFun& t);
	template<typename TFun,typename TClass>
	bool ActionCallBack(TFun t,TClass pClass);

	template<typename T>
	bool ActionCallBackFunction(const T& tFun);

	CAnimationQueueMulit* ActionMulitQueue();

	bool ActionPlayMusic(const std::string& sFilePath,bool bLoop = true);	//播放音乐
	bool ActionPlaySound(const std::string& sFilePath,bool bLoop = false);	//播放音效

	bool ActionExit();//离开游戏
	bool ActionOpenUrl(const std::string& sUrl);//打开Url
	//组命令
public:
	bool ActionSetTarget(Node* pNode,int nIndex = -1);//添加并设置为当前操作目标
	bool ActionSetTarget(Widget* pRootWidget,const std::string& sName,int nIndex = -1);
	
	bool ActionSetPostion(Node* pNode,const Point& ptPostion);
	bool ActionChangeParent(Node* pNodeTarget,Node* pNodeParent,bool bCleanUp = true);

	template<typename T,typename TValue>
	bool ActionSetValue(Node* pNode,const TValue& nValue );
private:
	bool ActionAnimationDisplayAddArg(const std::string& sName,int nDisplayIndex = -1,int nTargetIndex = -1);
public:
	bool	OnActionOver();
public:
	void	CallBackFuncN(Node* pNode);
	void	CallBack(Armature* pArmature, MovementEventType eEventType,const std::string& sName);
	bool	AddTarget(Node* pNodeTarget,int nIndex = -1);	
	bool	RemoveTarget(int nIndex = -1);
	bool	ClearTargets();
	Node*	FindTarget(int nIndex = -1)const;
	bool	SetCurTarget(int nIndex = -1);
	bool	ClearCurTarget();
	Node*	GetTargetCur();
	int		GetIndexCur();
	int		GetStoreTarget();
	bool	SetStoreTarget(int nStoreTarget);
	bool	GetWaitCallBack();

	Node*	GetParent();
	bool	MarkWaitCallBack();
	HAnimationQueue* GetHandler();
	bool	PushAction(IActionAnimation* pAction);
	IActionAnimation*	PopAction();
	bool	ClearCurAction();
	bool	ReleaseActions();
private:
	void	update(float dt);
public:
	CAnimationQueue(void);
	virtual ~CAnimationQueue(void);
private:
	Node*					_pParent;	//父节点
	HAnimationQueue*		_hHandler;	//处理器

	VectorAnimation			_vActions;	//动作队列

	int						_nZOrder;	//z-order
	float					_fSpeed;	//播放动画速度

	int						_nStoreTarget;//储存最近一次目标序号

	std::map<int,Node*>	_vTarget;	//操作目标<序号,Node*>
	Node*					_pTargetCur;//被操作对象
	int						_nIndexCur;	//当前被选中的操作对象
	IActionAnimation*		_pAction;		//最近一次操作参数

	bool					_bStoped;
	bool					_bWaitCallBack;
};

template<typename T,typename TValue>
bool CAnimationQueue::ActionSetValue( Node* pNode,const TValue& nValue )
{
	if (!pNode)return false;

	ActionSetTarget(pNode);
	ActionSetValue<T>(nValue);
	ActionClearTarget();
	return true;
}

template<typename T,typename TValue>
bool CAnimationQueue::ActionSetValue( const TValue& nValue )
{
	IActionAnimationSetValue<T,TValue>* pAction = new IActionAnimationSetValue<T,TValue>();
	ASSERT_LOG_ERROR(pAction);

	pAction->Init(nValue);

	return PushAction(pAction);
}

template<typename T,typename TValue>
bool CAnimationQueue::ActionActionsSetValue( const TValue& nValue,float fDuration)
{
	IActionAnimationActionsSetValue<T,TValue>* pAction = new IActionAnimationActionsSetValue<T,TValue>();
	ASSERT_LOG_ERROR(pAction);

	pAction->Init(nValue,fDuration);

	return PushAction(pAction);
}

template<typename T>
bool CAnimationQueue::ActionCallBackFunction( const T& tFun )
{
	IActionAnimationCallBackFunction<T>* pAction = new IActionAnimationCallBackFunction<T>();
	ASSERT_LOG_ERROR(pAction);

	pAction->Init(tFun);

	return PushAction(pAction);
}

template<typename TFun>
bool CAnimationQueue::ActionCallBack( const TFun& t )
{
	return ActionCallBackFunction(ApiBoost::Bind(t));
}

template<typename TFun,typename TClass>
bool CAnimationQueue::ActionCallBack( TFun t,TClass pClass )
{
	return ActionCallBackFunction(ApiBoost::Bind(t,pClass));
}

#endif //MACRO_LIB_COCOS2D
