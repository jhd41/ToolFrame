#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "HAnimationQueue.h"
#include "IActionAnimation.h"
#include "MLoger.h"

//��������
class TOOLFRAME_DLL CAnimationQueueMulit;
class TOOLFRAME_DLL CAnimationQueue
	:public Ref
{
	COCOS2DX_CREATE(CAnimationQueue);
	typedef std::list<IActionAnimation*> VectorAnimation;
public:
	//ȫ������
	bool	Init(Node* pParent,HAnimationQueue* pHandler);
	bool	Destory();
	bool	IsEmpty()const;
	bool	RunAction();
	bool	IsStoped()const;
	bool	RunActions();
	bool	IsWaitCallBack()const;
	bool	SetModeSelfRun();//������ģʽ
	bool	StopModeSelfRun();//������ģʽ

	bool	SetZOrder(int nZOrder);
	int		GetZOrder()const;
	bool	SetSpeed(float fSpeed = 1.0f);
	float	GetSpeed();
	Node*	GetParentNode();

	//��������
public:
	bool ActionAddTarget(Node* pNode,int nIndex = -1);//-1�������
	bool ActionAddTarget(Widget* pRootWidget,const std::string& sName,int nIndex = -1);//-1�������

	bool ActionClearTarget(int nIndex = -1);			//-1���������ӵ�
	bool ActionClearAllTarget();

	bool ActionSetCurTarget(int nIndex = -1);	//���õ�ǰĿ��
	bool ActionRemoveCurTarget();				//�Ƴ���ǰĿ��

	bool ActionStoreCurTarget();			//���浱ǰĿ��
	bool ActionRestoreCurTarget();			//��ԭ��ǰĿ��Ϊ�洢��Ŀ��

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

	bool ActionClone(Widget* pNode);//��¡(�����Ŀ��)
	
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

	bool ActionAnimationPlay(int nLoop = 0);														//����ָ��ѭ���ζ�����ص�(��������������һ������ѭ������)
	bool ActionAnimationPlay(const std::string& sName,int nLoop = 0);
	bool ActionAnimationPlay(const std::string& sName1,const std::string& sName2,int nLoop = 0);
	bool ActionAnimationPlay(const VectorString& vName,int nLoop = 0);

	bool ActionAnimationPlayFile(const Point& ptPostion,const std::string& sFileName,int nLoop=-1);														//����ָ��ѭ���ζ�����ص�(������ص����Ƴ�)
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

	bool ActionPlayMusic(const std::string& sFilePath,bool bLoop = true);	//��������
	bool ActionPlaySound(const std::string& sFilePath,bool bLoop = false);	//������Ч

	bool ActionExit();//�뿪��Ϸ
	bool ActionOpenUrl(const std::string& sUrl);//��Url
	//������
public:
	bool ActionSetTarget(Node* pNode,int nIndex = -1);//��Ӳ�����Ϊ��ǰ����Ŀ��
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
	Node*					_pParent;	//���ڵ�
	HAnimationQueue*		_hHandler;	//������

	VectorAnimation			_vActions;	//��������

	int						_nZOrder;	//z-order
	float					_fSpeed;	//���Ŷ����ٶ�

	int						_nStoreTarget;//�������һ��Ŀ�����

	std::map<int,Node*>	_vTarget;	//����Ŀ��<���,Node*>
	Node*					_pTargetCur;//����������
	int						_nIndexCur;	//��ǰ��ѡ�еĲ�������
	IActionAnimation*		_pAction;		//���һ�β�������

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
