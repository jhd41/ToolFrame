#include "AnimationQueue.h"

#ifdef MACRO_LIB_COCOS2D

#include "ApiCocos2dx.h"
#include "ActionIntervalEx.h"
#include "AnimationQueueMulit.h"
#include "MLoger.h"

CAnimationQueue::CAnimationQueue(void)
{
	_pParent = nullptr;
	_hHandler = nullptr;

	_pTargetCur = nullptr;

	_nZOrder = 0;
	_fSpeed	 = 1.0f;

	_nIndexCur = -1;
	_nStoreTarget = -1;

	_pAction = nullptr;

	_bStoped = false;
	_bWaitCallBack = false;
}

CAnimationQueue::~CAnimationQueue(void)
{
	Destory();
}

bool CAnimationQueue::Init( Node* pParent,HAnimationQueue* pHandler )
{
	if (!pParent)return false;

	_pParent = pParent;
	_hHandler = pHandler;

	return true;
}

bool CAnimationQueue::RunAction()
{
	if (IsWaitCallBack())return false;

	if (_pAction)
		ClearCurAction();

	ASSERT_LOG_ERROR(!_pAction);
	_pAction = PopAction();
	if (!_pAction)
	{
		if (_hHandler)
			_hHandler->OnAnimationComplete();
		return false;
	}

	if (!_pAction->OnExecute())
	{
		if (_hHandler)
			_hHandler->OnExecuteActionFaild(_pAction->GetActionType());
	}

	if (!IsWaitCallBack()){
		OnActionOver();
		ClearCurAction();
	}

	return true;
}

bool CAnimationQueue::ActionAnimationCreate( const std::string& sFileName )
{
	Point pt;
	return ActionAnimationCreate(sFileName,pt);
}

bool CAnimationQueue::ActionAnimationCreate( const std::string& sFileName,const Point& ptPostion )
{
	if(sFileName.empty())return false;

	IActionAnimationCreate* pAction = new IActionAnimationCreate();
	if(!pAction)return false;

	pAction->Init(sFileName,ptPostion);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionAnimationPlay( const std::string& sName,int nLoop /*= 0*/ )
{
	if (sName.empty())return false;

	VectorString vName;
	vName.push_back(sName);
	return ActionAnimationPlay(vName,nLoop);
}

bool CAnimationQueue::ActionAnimationPlay( const std::string& sName1,const std::string& sName2,int nLoop /*= 0*/ )
{
	if (sName1.empty())return false;
	if (sName2.empty())return false;

	VectorString vName;
	vName.push_back(sName1);
	vName.push_back(sName2);
	return ActionAnimationPlay(vName,nLoop);
}

bool CAnimationQueue::ActionAnimationPlay( const VectorString& vName,int nLoop /*= 0*/ )
{
	if (vName.empty())return false;

	IActionAnimationPlayByName* pAction = new IActionAnimationPlayByName();
	if(!pAction)return false;

	pAction->Init(vName,nLoop);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionAnimationPlay( int nLoop /*= 0*/ )
{
	IActionAnimationPlayByName* pAction = new IActionAnimationPlayByName();
	if(!pAction)return false;

	VectorString vName;
	pAction->Init(vName,nLoop);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionAnimationToFrame( int nFrameIndex )
{
	if (nFrameIndex < 0 )return false;

	IActionAnimationPlayToFrame* pAction = new IActionAnimationPlayToFrame();
	if(!pAction)return false;

	pAction->Init(nFrameIndex);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionSetPostion( const Point& ptPostion )
{
	IActionAnimationSetPostion* pAction = new IActionAnimationSetPostion();
	if(!pAction)return false;

	pAction->Init(ptPostion);

	return PushAction(pAction);
}

bool CAnimationQueue::IsEmpty() const
{
	return !IsWaitCallBack() && _vActions.empty();
}

bool CAnimationQueue::ActionSetZOrder( int nZOrder )
{
	IActionAnimationSetZOrder* pAction = new IActionAnimationSetZOrder();
	if(!pAction)return false;

	pAction->Init(nZOrder);

	return PushAction(pAction);
}

int CAnimationQueue::GetZOrder() const
{
	return _nZOrder;
}

bool CAnimationQueue::SetZOrder( int nZOrder )
{
	_nZOrder = nZOrder;
	return true;
}

bool CAnimationQueue::ActionRemoveFromParent( bool bCleanUp /*= true*/ )
{
	IActionAnimationRemoveFromParent* pAction = new IActionAnimationRemoveFromParent();
	if(!pAction)return false;

	pAction->Init(bCleanUp);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionSetVisible( bool bVisible )
{
	IActionAnimationSetVisible* pAction = new IActionAnimationSetVisible();
	if(!pAction)return false;

	pAction->Init(bVisible);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionSetEnabled( bool bEnabled )
{
	IActionAnimationSetEnable* pAction = new IActionAnimationSetEnable();
	if(!pAction)return false;

	pAction->Init(bEnabled);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionMoveTo( const Point& ptPostion,float fDuration )
{
	IActionAnimationMoveTo* pAction = new IActionAnimationMoveTo();
	if(!pAction)return false;

	pAction->Init(ptPostion,fDuration);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionMoveBy(const Point& ptPostion,float fDuration)
{
	IActionAnimationMoveBy* pAction = new IActionAnimationMoveBy();
	if(!pAction)return false;

	pAction->Init(ptPostion,fDuration);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionDelay( float fDuration )
{
	IActionAnimationDelay* pAction = new IActionAnimationDelay();
	if(!pAction)return false;

	pAction->Init(fDuration);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionClearTarget(int nIndex)
{
	IActionAnimationClearTarget* pAction = new IActionAnimationClearTarget();
	if(!pAction)return false;

	pAction->Init(nIndex);

	return PushAction(pAction);
}

bool CAnimationQueue::Destory()
{
	if (_bStoped)return false;
	
	_bStoped = true;
	
	ClearCurAction();
	ReleaseActions();
	ClearTargets();

	StopModeSelfRun();
	return true;
}

bool CAnimationQueue::ActionCallBack( int nUserInt /*=0*/ )
{
	IActionAnimationCallBack* pAction = new IActionAnimationCallBack();
	if(!pAction)return false;

	pAction->Init(nUserInt);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionFadeIn(float fDuration)
{
	IActionAnimationFadeIn* pAction = new IActionAnimationFadeIn();
	if(!pAction)return false;

	pAction->Init(fDuration);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionFadeOut(float fDuration)
{
	IActionAnimationFadeOut* pAction = new IActionAnimationFadeOut();
	if(!pAction)return false;

	pAction->Init(fDuration);

	return PushAction(pAction);
}

bool CAnimationQueue::SetSpeed( float fSpeed /*= 1.0f*/ )
{
	_fSpeed = fSpeed;

	if (_pAction)
		_pAction->OnAnimationSpeed(fSpeed);

	return true;
}

bool CAnimationQueue::ActionChangeParent( Node* pNodeParent, bool bCleanUp /*= true*/ )
{
	if (!pNodeParent)return false;

	IActionAnimationChangeParent* pAction = new IActionAnimationChangeParent();
	if(!pAction)return false;

	pAction->Init(pNodeParent,bCleanUp);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionAnimationDisplayAdd( const std::string& sName,Node* pNode,int nIndex /*= -1*/ )
{
	if (sName.empty())return false;
	if (!pNode)return false;

	ActionAddTarget(pNode);
	ActionAnimationDisplayAddArg(sName,nIndex,-1);
	ActionClearTarget();

	return true;
}

bool CAnimationQueue::ActionAnimationDisplayRemove( const std::string& sName,int nIndex /*= -1*/ )
{
	if (sName.empty())return false;

	IActionAnimationDisplayRemove* pAction = new IActionAnimationDisplayRemove();
	if(!pAction)return false;

	pAction->Init(sName,nIndex);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionAnimationDisplayChange( const std::string& sName,int nIndex /*= 0*/,bool bForce /*= true*/ )
{
	if (sName.empty())return false;

	IActionAnimationDisplayChange* pAction = new IActionAnimationDisplayChange();
	if(!pAction)return false;

	pAction->Init(sName,nIndex,bForce);

	return PushAction(pAction);
}

bool CAnimationQueue::AddTarget( Node* pNodeTarget,int nIndex /*= -1*/ )
{
	//修正nIndex
	if (-1 == nIndex)
	{
		nIndex = ToolFrame::GetKeyByKeyMax(_vTarget,-1);
		nIndex = -1 == nIndex ? 1: (nIndex + 1);
	}

	//释放前一个节点
	RemoveTarget(nIndex);

	if (!pNodeTarget)return false;

	//添加新的节点
	pNodeTarget->retain();
	_vTarget[nIndex]=pNodeTarget;
	return true;
}

bool CAnimationQueue::RemoveTarget( int nIndex /*= -1*/ )
{
	if (-1 == nIndex)
	{
		nIndex = ToolFrame::GetKeyByKeyMax(_vTarget,-1);
		if (-1 == nIndex)return false;
	}

	Node* pNode = ToolFrame::GetPtrValueByKey(_vTarget,nIndex);
	if (pNode)
		pNode->release();

	ToolFrame::EraseByKey(_vTarget,nIndex);

	return true;
}

bool CAnimationQueue::ClearTargets()
{
	std::map<int,Node*>::iterator itr;
	foreach(itr,_vTarget){
		Node* pNode = itr->second;
		ASSERT_LOG_ERROR(pNode);

		pNode->release();
	}

	_vTarget.clear();

	return true;
}

Node* CAnimationQueue::FindTarget( int nIndex/*=-1*/ ) const
{
	if (-1 == nIndex)
	{
		nIndex = ToolFrame::GetKeyByKeyMax(_vTarget,-1);
		if (-1 == nIndex)return nullptr;
	}

	return  ToolFrame::GetPtrValueByKey(_vTarget,nIndex);
}

bool CAnimationQueue::ActionClearAllTarget()
{
	IActionAnimationClearTargetAll* pAction = new IActionAnimationClearTargetAll();
	if(!pAction)return false;

	pAction->Init();

	return PushAction(pAction);
}

bool CAnimationQueue::ActionSetCurTarget( int nIndex )
{
	IActionAnimationSetCurTarget* pAction = new IActionAnimationSetCurTarget();
	if(!pAction)return false;

	pAction->Init(nIndex);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionSetPostion( Node* pNode,const Point& ptPostion )
{
	if (!pNode)return true;

	ActionStoreCurTarget();

	ActionAddTarget(pNode);
	ActionSetCurTarget();
	ActionSetPostion(ptPostion);
	ActionClearTarget();

	ActionRestoreCurTarget();

	return true;
}

bool CAnimationQueue::ActionChangeParent( Node* pNodeTarget,Node* pNodeParent,bool bCleanUp /*= true*/ )
{
	if (!pNodeParent)return false;

	ActionStoreCurTarget();
	ActionAddTarget(pNodeTarget);
	ActionSetCurTarget();
	ActionChangeParent(pNodeParent,bCleanUp);
	ActionClearTarget();
	ActionRestoreCurTarget();
	return true;
}

bool CAnimationQueue::ActionStoreCurTarget()
{
	IActionAnimationStoreCurTarget* pAction = new IActionAnimationStoreCurTarget();
	if(!pAction)return false;

	pAction->Init();

	return PushAction(pAction);
}

bool CAnimationQueue::ActionRestoreCurTarget()
{
	IActionAnimationReStoreCurTarget* pAction = new IActionAnimationReStoreCurTarget();
	if(!pAction)return false;

	pAction->Init();

	return PushAction(pAction);
}

bool CAnimationQueue::SetCurTarget( int nIndex )
{
	if (-1 == nIndex)
	{
		nIndex = ToolFrame::GetKeyByKeyMax(_vTarget,-1);
		if (-1 == nIndex)return nullptr;
	}
	
	_pTargetCur = FindTarget(nIndex);
	_nIndexCur = _pTargetCur ? nIndex : -1;
	return true;
}

bool CAnimationQueue::ClearCurTarget()
{
	_nIndexCur = -1;
	_pTargetCur = nullptr;
	return true;
}

bool CAnimationQueue::ActionClone(Widget* pNode)
{
	if (!pNode)return false;

	IActionAnimationClone* pAction = new IActionAnimationClone();
	if(!pAction)return false;

	pAction->Init(pNode);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionSetWorldPostion( const Node* pNodePostion )
{
	if (!pNodePostion)return false;

	IActionAnimationSetWorldPostionNode* pAction = new IActionAnimationSetWorldPostionNode();
	if(!pAction)return false;

	pAction->Init(pNodePostion);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionSetWorldPostion( const Point& ptPostion )
{
	IActionAnimationSetWorldPostionPoint* pAction = new IActionAnimationSetWorldPostionPoint();
	if(!pAction)return false;

	pAction->Init(ptPostion);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionAnimationDisplayAddArg( const std::string& sName,int nDisplayIndex /*= -1*/,int nTargetIndex /*= -1*/ )
{
	IActionAnimationDisplayAdd* pAction = new IActionAnimationDisplayAdd();
	if(!pAction)return false;

	pAction->Init(sName,nDisplayIndex,nTargetIndex);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionAddTarget( Node* pNode,int nIndex /*= -1*/ )
{
	if (!pNode)return false;

	IActionAnimationAddTarget* pAction = new IActionAnimationAddTarget();
	if(!pAction)return false;

	pAction->Init(pNode,nIndex);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionAddTarget( Widget* pRootWidget,const std::string& sName,int nIndex /*= -1*/ )
{
	if (!pRootWidget)return false;
	if (sName.empty())return false;

	IActionAnimationAddTargetFind* pAction = new IActionAnimationAddTargetFind();
	if(!pAction)return false;

	pAction->Init(pRootWidget,sName,nIndex);

	return PushAction(pAction);
}


bool CAnimationQueue::ActionSetTarget( Node* pNode,int nIndex)
{
	if (!pNode)return false;
	
	ActionRemoveCurTarget();
	ActionAddTarget(pNode,nIndex);
	ActionSetCurTarget(nIndex);

	return true;
}

bool CAnimationQueue::ActionSetTarget( Widget* pRootWidget,const std::string& sName,int nIndex)
{
	if (!pRootWidget)return false;
	if (sName.empty())return false;

	ActionRemoveCurTarget();
	ActionAddTarget(pRootWidget,sName,nIndex);
	ActionSetCurTarget(nIndex);

	return true;
}

bool CAnimationQueue::ActionRemoveCurTarget()
{
	IActionAnimationRemoveCurTarget* pAction = new IActionAnimationRemoveCurTarget();
	if(!pAction)return false;

	pAction->Init();

	return PushAction(pAction);
}

bool CAnimationQueue::ActionFadeInEx(float fDuration)
{
	IActionAnimationFadeInEx* pAction = new IActionAnimationFadeInEx();
	if(!pAction)return false;

	pAction->Init(fDuration);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionFadeOutEx(float fDuration)
{
	IActionAnimationFadeOutEx* pAction = new IActionAnimationFadeOutEx();
	if(!pAction)return false;

	pAction->Init(fDuration);

	return PushAction(pAction);
}

CAnimationQueueMulit* CAnimationQueue::ActionMulitQueue()
{
	IActionAnimationMulitQueue* pAction = new IActionAnimationMulitQueue();
	if(!pAction)return nullptr;

	pAction->Init(this);

	PushAction(pAction);
	return pAction->GetMulitQueue();
}

bool CAnimationQueue::ActionSetRotation( float fRotation )
{
	IActionAnimationSetRotation* pAction = new IActionAnimationSetRotation();
	if(!pAction)return false;

	pAction->Init(fRotation);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionSetOpacity( GLubyte uOpacity,bool bChildren /*= true*/ )
{
	IActionAnimationSetOpacity* pAction = new IActionAnimationSetOpacity();
	if(!pAction)return false;

	pAction->Init(uOpacity,bChildren);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionSetScale( float fScale /*= 1.0f*/ )
{
	return ActionSetScale(fScale,fScale);
}

bool CAnimationQueue::ActionSetScale( float fScaleX,float fScaleY )
{
	IActionAnimationSetScale* pAction = new IActionAnimationSetScale();
	if(!pAction)return false;

	pAction->Init(fScaleX,fScaleY);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionNextFrame( float fDuration,const Point& ptPostion,float fRotation,GLubyte uOpacity,float fScale,const std::string& sAnimationName )
{
	IActionAnimationNextFrame* pAction = new IActionAnimationNextFrame();
	if(!pAction)return false;

	pAction->Init(fDuration,ptPostion,fRotation,uOpacity,fScale,sAnimationName);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionPlayMusic( const std::string& sFilePath,bool bLoop /*= true*/ )
{
	IActionAnimationPlayMusic* pAction = new IActionAnimationPlayMusic();
	if(!pAction)return false;

	pAction->Init(sFilePath,bLoop);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionPlaySound( const std::string& sFilePath,bool bLoop /*= false*/ )
{
	IActionAnimationPlaySound* pAction = new IActionAnimationPlaySound();
	if(!pAction)return false;

	pAction->Init(sFilePath,bLoop);

	return PushAction(pAction);
}

bool CAnimationQueue::OnActionOver()
{
	_bWaitCallBack = false;
	return true;
}

Node* CAnimationQueue::GetParentNode()
{
	return _pParent;
}

bool CAnimationQueue::IsStoped() const
{
	return _bStoped;
}

Node* CAnimationQueue::GetTargetCur()
{
	return _pTargetCur;
}

int CAnimationQueue::GetIndexCur()
{
	return _nIndexCur;
}

int CAnimationQueue::GetStoreTarget()
{
	return _nStoreTarget;
}

bool CAnimationQueue::SetStoreTarget( int nStoreTarget )
{
	_nStoreTarget = nStoreTarget;
	return true;
}

float CAnimationQueue::GetSpeed()
{
	return _fSpeed;
}

Node* CAnimationQueue::GetParent()
{
	return _pParent;
}

HAnimationQueue* CAnimationQueue::GetHandler()
{
	return _hHandler;
}

bool CAnimationQueue::PushAction( IActionAnimation* pAction )
{
	if (!pAction)return false;

	pAction->SetQueue(this);

	pAction->retain();

	return ToolFrame::Insert(_vActions,pAction);
}

IActionAnimation* CAnimationQueue::PopAction()
{
	return ToolFrame::PopPtr(_vActions);
}

bool CAnimationQueue::RunActions()
{
	while (!IsStoped() && RunAction());
	return true;
}

bool CAnimationQueue::ClearCurAction()
{
	if (_pAction)
	{
		_pAction->OnDestory();
		_pAction->release();
		_pAction = nullptr;
	}
	
	return true;
}

bool CAnimationQueue::ReleaseActions()
{
	VectorAnimation::iterator itr;
	foreach(itr,_vActions){
		IActionAnimation* pAction = *itr;
		ASSERT_LOG_ERROR(pAction);

		pAction->OnDestory();
		pAction->release();
	}
	ToolFrame::Clear(_vActions);
	return true;
}

bool CAnimationQueue::IsWaitCallBack() const
{
	return _bWaitCallBack;
}

bool CAnimationQueue::MarkWaitCallBack()
{
	ASSERT_LOG_ERROR(!_bWaitCallBack);
	if (_bWaitCallBack)return false;
	
	_bWaitCallBack = true;
	return true;
}

bool CAnimationQueue::ActionAnimationBoneAdd( const std::string& sParentBone,const std::string& sNewBone,Node* pNode )
{
	if (!pNode)return false;
	if (sParentBone.empty())return false;
	
	IActionAnimationBoneAdd* pAction = new IActionAnimationBoneAdd();
	if(!pAction)return false;

	pAction->Init(sParentBone,sNewBone,pNode);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionExit()
{
	IActionAnimationExit* pAction = new IActionAnimationExit();
	if(!pAction)return false;

	pAction->Init();

	return PushAction(pAction);
}

bool CAnimationQueue::ActionOpenUrl( const std::string& sUrl )
{
	if (sUrl.empty()) return false;

	IActionAnimationOpenUrl* pAction = new IActionAnimationOpenUrl();
	if(!pAction)return false;

	pAction->Init(sUrl);

	return PushAction(pAction);
}

bool CAnimationQueue::SetModeSelfRun()
{
	if (!_pParent)return false;
	_pParent->getScheduler()->schedule((SEL_SCHEDULE)&CAnimationQueue::update,this,0,false);
	return true;
}

bool CAnimationQueue::StopModeSelfRun()
{
	if (!_pParent)return false;
	_pParent->getScheduler()->unschedule((SEL_SCHEDULE)&CAnimationQueue::update,this);
	return true;
}

void CAnimationQueue::update( float dt )
{
	RunActions();
}

bool CAnimationQueue::ActionSpinePlay( const std::string& sName,int nLoop /*= 0*/,float fDelay/*=0.f*/ )
{
	if (sName.empty())return false;

	VectorString vName;
	vName.push_back(sName);

	return ActionSpinePlay(vName,nLoop,fDelay);
}

bool CAnimationQueue::ActionSpinePlay( const std::string& sName1,const std::string& sName2,int nLoop /*= 0*/,float fDelay/*=0.3f*/ )
{
	if (sName1.empty())return false;
	if (sName2.empty())return false;

	VectorString vName;
	vName.push_back(sName1);
	vName.push_back(sName2);
	return ActionSpinePlay(vName,nLoop,fDelay);
}

bool CAnimationQueue::ActionSpinePlay( const VectorString& vName,int nLoop /*= 0*/,float fDelay/*=0.3f*/ )
{
	IActionSpinePlayByName* pAction = new IActionSpinePlayByName();
	if(!pAction)return false;

	pAction->Init(vName,nLoop,fDelay);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionSetSpeed(float fSpeed)
{
	IActionAnimationSpeed* pAction = new IActionAnimationSpeed();
	if (!pAction)return false;

	pAction->Init(fSpeed);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionAnimationPlayFile(const Point& ptPostion, const std::string& sFileName, int nLoop/*=0*/)
{
	if (sFileName.empty())return false;

	IActionAnimationPlayFileByName* pAction = new IActionAnimationPlayFileByName();
	if(!pAction)return false;

	VectorString vName;
	pAction->Init(ptPostion,sFileName,vName,nLoop);

	return PushAction(pAction);
}

bool CAnimationQueue::ActionAnimationPlayFile( const Point& ptPostion,const std::string& sFileName,const std::string& sName,int nLoop/*=0*/ )
{
	if (sFileName.empty())return false;
	if (sName.empty())return false;

	VectorString vName;
	vName.push_back(sName);
	return ActionAnimationPlayFile(ptPostion,sFileName,vName,nLoop);
}

bool CAnimationQueue::ActionAnimationPlayFile( const Point& ptPostion,const std::string& sFileName,const std::string& sName1,const std::string& sName2,int nLoop/*=0*/ )
{
	if (sFileName.empty())return false;
	if (sName1.empty())return false;
	if (sName2.empty())return false;

	VectorString vName;
	vName.push_back(sName1);
	vName.push_back(sName2);
	return ActionAnimationPlayFile(ptPostion,sFileName,vName,nLoop);
}

bool CAnimationQueue::ActionAnimationPlayFile( const Point& ptPostion,const std::string& sFileName,const VectorString& vName,int nLoop/*=0*/ )
{
	if (sFileName.empty())return false;
	if (vName.empty())return false;

	IActionAnimationPlayFileByName* pAction = new IActionAnimationPlayFileByName();
	if(!pAction)return false;

	pAction->Init(ptPostion,sFileName,vName,nLoop);

	return PushAction(pAction);
}

#endif //MACRO_LIB_COCOS2D
