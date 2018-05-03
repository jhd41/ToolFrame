#include "IActionAnimation.h"

#ifdef MACRO_LIB_COCOS2D

#include "AnimationQueue.h"
#include "ActionIntervalEx.h"
#include "AnimationQueueMulit.h"
#include "MLoger.h"

IActionAnimation::IActionAnimation(void)
{
	SetActionType(ACTION_INVAILD);
	SetQueueNull();

	autorelease();
}

IActionAnimation::~IActionAnimation(void)
{
}
//////////////////////////////////////////////////////////////////////////
IActionAnimationAddTarget::IActionAnimationAddTarget( void )
{
	SetActionType(ACTION_ADD_TARGET);
}

IActionAnimationAddTarget::~IActionAnimationAddTarget( void )
{
	
}

bool IActionAnimationAddTarget::Init( Node* pNode,int nIndex )
{
	_pNode = pNode;
	_nIndex= nIndex;
	return true;
}

bool IActionAnimationAddTarget::OnExecute()
{
	GetQueue()->AddTarget(_pNode,_nIndex);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationAddTargetFind::IActionAnimationAddTargetFind( void )
{
	SetActionType(ACTION_ADD_TARGET_FIND);
}

IActionAnimationAddTargetFind::~IActionAnimationAddTargetFind( void )
{

}

bool IActionAnimationAddTargetFind::Init( Widget* pWidget,const std::string& sName,int nIndex)
{
	_pWidget = pWidget;
	_sName = sName;
	_nIndex = nIndex;
	return true;
}

bool IActionAnimationAddTargetFind::OnExecute()
{
	GetQueue()->AddTarget(ApiCocos2dx::FindNode(_pWidget,_sName),_nIndex);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationClearTarget::IActionAnimationClearTarget( void )
{
	SetActionType(ACTION_CLEAR_TARGET);
}

IActionAnimationClearTarget::~IActionAnimationClearTarget( void )
{

}

bool IActionAnimationClearTarget::Init(int nIndex )
{
	_nIndex = nIndex;
	return true;
}

bool IActionAnimationClearTarget::OnExecute()
{
	GetQueue()->RemoveTarget(_nIndex);
	if (_nIndex == GetQueue()->GetIndexCur())
		GetQueue()->ClearCurTarget();
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationClearTargetAll::IActionAnimationClearTargetAll( void )
{
	SetActionType(ACTION_CLEAR_TARGET_ALL);
}

IActionAnimationClearTargetAll::~IActionAnimationClearTargetAll( void )
{

}

bool IActionAnimationClearTargetAll::Init()
{
	return true;
}

bool IActionAnimationClearTargetAll::OnExecute()
{
	GetQueue()->ClearTargets();
	GetQueue()->ClearCurTarget();
	return true;
}


//////////////////////////////////////////////////////////////////////////
IActionAnimationSetCurTarget::IActionAnimationSetCurTarget( void )
{
	SetActionType(ACTION_SET_CUR_TARGET);
}

IActionAnimationSetCurTarget::~IActionAnimationSetCurTarget( void )
{

}

bool IActionAnimationSetCurTarget::Init( int nIndex )
{
	_nIndex = nIndex;
	return true;
}

bool IActionAnimationSetCurTarget::OnExecute()
{
	GetQueue()->SetCurTarget(_nIndex);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationRemoveCurTarget::IActionAnimationRemoveCurTarget( void )
{
	SetActionType(ACTION_REMOVE_CUR_TARGET);
}

IActionAnimationRemoveCurTarget::~IActionAnimationRemoveCurTarget( void )
{

}

bool IActionAnimationRemoveCurTarget::Init()
{
	return true;
}

bool IActionAnimationRemoveCurTarget::OnExecute()
{
	if (-1 != GetQueue()->GetIndexCur())
	{
		GetQueue()->RemoveTarget(GetQueue()->GetIndexCur());
		GetQueue()->ClearCurTarget();
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationStoreCurTarget::IActionAnimationStoreCurTarget( void )
{
	SetActionType(ACTION_STORE_CUR_TARGET);
}

IActionAnimationStoreCurTarget::~IActionAnimationStoreCurTarget( void )
{

}

bool IActionAnimationStoreCurTarget::Init()
{
	return true;
}

bool IActionAnimationStoreCurTarget::OnExecute()
{
	int nStoreTarget = GetQueue()->GetIndexCur();
	GetQueue()->SetStoreTarget(nStoreTarget);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationReStoreCurTarget::IActionAnimationReStoreCurTarget( void )
{
	SetActionType(ACTION_RESTORE_CUR_TARGET);
}

IActionAnimationReStoreCurTarget::~IActionAnimationReStoreCurTarget( void )
{

}

bool IActionAnimationReStoreCurTarget::Init()
{
	return true;
}

bool IActionAnimationReStoreCurTarget::OnExecute()
{
	GetQueue()->SetCurTarget(GetQueue()->GetStoreTarget());
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationSetPostion::IActionAnimationSetPostion( void )
{
	SetActionType(ACTION_SET_POSTION);
}

IActionAnimationSetPostion::~IActionAnimationSetPostion( void )
{

}

bool IActionAnimationSetPostion::Init( const Point& ptPostion)
{
	_ptPostion = ptPostion;
	return true;
}

bool IActionAnimationSetPostion::OnExecute()
{
	ApiCocos2dx::SetPostion(GetQueue()->GetTargetCur(),_ptPostion);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationSetZOrder::IActionAnimationSetZOrder( void )
{
	SetActionType(ACTION_SET_Z_ORDER);
}

IActionAnimationSetZOrder::~IActionAnimationSetZOrder( void )
{

}

bool IActionAnimationSetZOrder::Init( int nZOrder)
{
	_nZOrder = nZOrder;
	return true;
}

bool IActionAnimationSetZOrder::OnExecute()
{
	ApiCocos2dx::SetZOrder(GetQueue()->GetTargetCur(),_nZOrder);
	return true;
}
//////////////////////////////////////////////////////////////////////////
IActionAnimationSetVisible::IActionAnimationSetVisible( void )
{
	SetActionType(ACTION_SET_VISIBLE);
}

IActionAnimationSetVisible::~IActionAnimationSetVisible( void )
{

}

bool IActionAnimationSetVisible::Init(bool bVisible)
{
	_bVisible = bVisible;
	return true;
}

bool IActionAnimationSetVisible::OnExecute()
{
	ApiCocos2dx::SetVisible(GetQueue()->GetTargetCur(),_bVisible);
	return true;
}

//////////////////////////////////////////////////////////////////////////

IActionAnimationSetEnable::IActionAnimationSetEnable( void )
{
	SetActionType(ACTION_SET_ENABLE);
}

IActionAnimationSetEnable::~IActionAnimationSetEnable( void )
{

}

bool IActionAnimationSetEnable::Init( bool bEnabled )
{
	_bEnabled = bEnabled;
	return true;
}

bool IActionAnimationSetEnable::OnExecute()
{
	return ApiCocos2dx::SetEnabled(dynamic_cast<Widget*>(GetQueue()->GetTargetCur()),_bEnabled);
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationSetRotation::IActionAnimationSetRotation( void )
{
	SetActionType(ACTION_SET_ROTATION);
}

IActionAnimationSetRotation::~IActionAnimationSetRotation( void )
{

}

bool IActionAnimationSetRotation::Init( float fRotation )
{
	_fRotation = fRotation;
	return true;
}

bool IActionAnimationSetRotation::OnExecute()
{
	ApiCocos2dx::SetRotation(GetQueue()->GetTargetCur(),_fRotation);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationSetOpacity::IActionAnimationSetOpacity( void )
{
	SetActionType(ACTION_SET_OPACITY);
}

IActionAnimationSetOpacity::~IActionAnimationSetOpacity( void )
{

}

bool IActionAnimationSetOpacity::Init( GLubyte uOpacity,bool bChildren )
{
	_uOpacity = uOpacity;
	_bChildren = bChildren;
	return true;
}

bool IActionAnimationSetOpacity::OnExecute()
{
	ApiCocos2dx::SetOpacity(GetQueue()->GetTargetCur(),_uOpacity,_bChildren);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationSetScale::IActionAnimationSetScale( void )
{
	SetActionType(ACTION_SET_SCALE);
}

IActionAnimationSetScale::~IActionAnimationSetScale( void )
{

}

bool IActionAnimationSetScale::Init( float fScaleX,float fScaleY)
{
	_fScaleX = fScaleX;
	_fScaleY = fScaleY;
	return true;
}

bool IActionAnimationSetScale::OnExecute()
{
	ApiCocos2dx::SetScale(GetQueue()->GetTargetCur(),_fScaleX,_fScaleY);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationRemoveFromParent::IActionAnimationRemoveFromParent( void )
{
	SetActionType(ACTION_REMOVE_FROM_PARENT);
}

IActionAnimationRemoveFromParent::~IActionAnimationRemoveFromParent( void )
{

}

bool IActionAnimationRemoveFromParent::Init( bool bCleanUp )
{
	_bCleanUp = bCleanUp;
	return true;
}

bool IActionAnimationRemoveFromParent::OnExecute()
{
	Node* pNode = GetQueue()->GetTargetCur();
	if (!pNode)return false;

	ApiCocos2dx::RemoveFromParentAndCleanup(pNode,_bCleanUp);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationChangeParent::IActionAnimationChangeParent( void )
{
	SetActionType(ACTION_CHANGE_PARENT);
}

IActionAnimationChangeParent::~IActionAnimationChangeParent( void )
{

}

bool IActionAnimationChangeParent::Init( Node* pNodeParent, bool bCleanUp)
{
	_pNodeParent = pNodeParent;
	_bCleanUp = bCleanUp;
	return true;
}

bool IActionAnimationChangeParent::OnExecute()
{
	ApiCocos2dx::ChangeParentNode(GetQueue()->GetTargetCur(),_pNodeParent,_bCleanUp);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationClone::IActionAnimationClone( void )
{
	SetActionType(ACTION_CLONE);
}

IActionAnimationClone::~IActionAnimationClone( void )
{

}

bool IActionAnimationClone::Init( Widget* pWidget )
{
	_pWidget = pWidget;
	return true;
}

bool IActionAnimationClone::OnExecute()
{
	Node* pNode = ApiCocos2dx::Clone(_pWidget);
	if (!pNode)return false;

	GetQueue()->AddTarget(pNode);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationSetWorldPostionNode::IActionAnimationSetWorldPostionNode( void )
{
	SetActionType(ACTION_SET_WORLD_POSTION_NODE);
}

IActionAnimationSetWorldPostionNode::~IActionAnimationSetWorldPostionNode( void )
{

}

bool IActionAnimationSetWorldPostionNode::Init(const Node* pNodePostion )
{
	_pNodePostion = pNodePostion;
	return true;
}

bool IActionAnimationSetWorldPostionNode::OnExecute()
{
	if (!_pNodePostion->getParent())return false;

	Point ptWorldPostion = ApiCocos2dx::GetWorldPostion((CCNode*)_pNodePostion);
	ApiCocos2dx::SetWorldPostion(GetQueue()->GetTargetCur(),ptWorldPostion);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationSetWorldPostionPoint::IActionAnimationSetWorldPostionPoint( void )
{
	SetActionType(ACTION_SET_WORLD_POSTION_POINT);
}

IActionAnimationSetWorldPostionPoint::~IActionAnimationSetWorldPostionPoint( void )
{

}

bool IActionAnimationSetWorldPostionPoint::Init( Point ptPostion )
{
	_ptPostion = ptPostion;
	return true;
}

bool IActionAnimationSetWorldPostionPoint::OnExecute()
{
	ApiCocos2dx::SetWorldPostion(GetQueue()->GetTargetCur(),_ptPostion);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationMoveTo::IActionAnimationMoveTo( void )
{
	SetActionType(ACTION_MOVE_TO);
}

IActionAnimationMoveTo::~IActionAnimationMoveTo( void )
{

}

bool IActionAnimationMoveTo::Init( const Point& ptPostion,float fDuration)
{
	_fDuration = fDuration;
	_ptPostion = ptPostion;
	return true;
}

bool IActionAnimationMoveTo::OnExecute()
{
	ActionInterval*  pAc		= CCMoveTo::create(_fDuration / GetQueue()->GetSpeed(),_ptPostion);
	CCCallFunc*  pAcCallBack	= CCCallFuncN::create(this, callfuncN_selector(IActionAnimationMoveTo::CallBackFuncN));
	ASSERT_LOG_ERROR(pAc && pAcCallBack);
	GetQueue()->GetTargetCur()->runAction( CCSequence::create(pAc,pAcCallBack, nullptr));

	GetQueue()->MarkWaitCallBack();
	return true;
}

void IActionAnimationMoveTo::CallBackFuncN( Node* pNode )
{
	GetQueue()->OnActionOver();
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationMoveBy::IActionAnimationMoveBy( void )
{
	SetActionType(ACTION_MOVE_BY);
}

IActionAnimationMoveBy::~IActionAnimationMoveBy( void )
{

}

bool IActionAnimationMoveBy::Init(const Point& ptPostion,float fDuration)
{
	_fDuration = fDuration;
	_ptPostion = ptPostion;
	return true;
}

bool IActionAnimationMoveBy::OnExecute()
{
	ActionInterval*  pAc		= CCMoveBy::create(_fDuration / GetQueue()->GetSpeed(),_ptPostion);
	CCCallFunc*  pAcCallBack	= CCCallFuncN::create(this, callfuncN_selector(IActionAnimationMoveBy::CallBackFuncN));
	ASSERT_LOG_ERROR(pAc && pAcCallBack);
	GetQueue()->GetTargetCur()->runAction( CCSequence::create(pAc,pAcCallBack, nullptr));

	GetQueue()->MarkWaitCallBack();
	return true;
}

void IActionAnimationMoveBy::CallBackFuncN( Node* pNode )
{
	GetQueue()->OnActionOver();
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationDelay::IActionAnimationDelay( void )
{
	SetActionType(ACTION_DELAY);

	_pNode = nullptr;
}

IActionAnimationDelay::~IActionAnimationDelay( void )
{

}

bool IActionAnimationDelay::Init( float fDuration )
{
	_fDuration = fDuration;
	return true;
}

bool IActionAnimationDelay::OnExecute()
{
	ASSERT_LOG_ERROR(!_pNode);
	_pNode = Node::create();
	GetQueue()->GetParentNode()->addChild(_pNode);

	ActionInterval*  pAc		= CCDelayTime::create(_fDuration / GetQueue()->GetSpeed());
	CCCallFunc*  pAcCallBack	= CCCallFuncN::create(this, callfuncN_selector(IActionAnimationDelay::CallBackFuncN));
	ASSERT_LOG_ERROR(pAc && pAcCallBack);
	_pNode->runAction( CCSequence::create(pAc,pAcCallBack, nullptr));

	GetQueue()->MarkWaitCallBack();
	return true;
}

void IActionAnimationDelay::CallBackFuncN( Node* pNode )
{
	_pNode->removeFromParentAndCleanup(true);
	GetQueue()->OnActionOver();
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationFadeIn::IActionAnimationFadeIn( void )
{
	SetActionType(ACTION_FADE_IN);
}

IActionAnimationFadeIn::~IActionAnimationFadeIn( void )
{

}

bool IActionAnimationFadeIn::Init(float fDuration )
{
	_fDuration = fDuration;
	return true;
}

bool IActionAnimationFadeIn::OnExecute()
{
	ActionInterval*  pAc		= CCFadeIn::create(_fDuration / GetQueue()->GetSpeed());
	CCCallFunc*  pAcCallBack	= CCCallFuncN::create(this, callfuncN_selector(IActionAnimationFadeIn::CallBackFuncN));
	ASSERT_LOG_ERROR(pAc && pAcCallBack);
	GetQueue()->GetTargetCur()->runAction( CCSequence::create(pAc,pAcCallBack, nullptr));

	GetQueue()->MarkWaitCallBack();
	return true;
}

void IActionAnimationFadeIn::CallBackFuncN( Node* pNode )
{
	GetQueue()->OnActionOver();
}
//////////////////////////////////////////////////////////////////////////
IActionAnimationFadeOut::IActionAnimationFadeOut( void )
{
	SetActionType(ACTION_FADE_OUT);
}

IActionAnimationFadeOut::~IActionAnimationFadeOut( void )
{

}

bool IActionAnimationFadeOut::Init( float fDuration )
{
	_fDuration = fDuration;
	return true;
}

bool IActionAnimationFadeOut::OnExecute()
{
	ActionInterval*  pAc		= CCFadeOut::create(_fDuration / GetQueue()->GetSpeed());
	CCCallFunc*  pAcCallBack	= CCCallFuncN::create(this, callfuncN_selector(IActionAnimationFadeOut::CallBackFuncN));
	ASSERT_LOG_ERROR(pAc && pAcCallBack);
	GetQueue()->GetTargetCur()->runAction( CCSequence::create(pAc,pAcCallBack, nullptr));

	GetQueue()->MarkWaitCallBack();
	return true;
}

void IActionAnimationFadeOut::CallBackFuncN( Node* pNode )
{
	GetQueue()->OnActionOver();
}
//////////////////////////////////////////////////////////////////////////
IActionAnimationFadeInEx::IActionAnimationFadeInEx( void )
{
	SetActionType(ACTION_FADE_IN_EX);
}

IActionAnimationFadeInEx::~IActionAnimationFadeInEx( void )
{

}

bool IActionAnimationFadeInEx::Init( float fDuration )
{
	_fDuration = fDuration;
	return true;
}

bool IActionAnimationFadeInEx::OnExecute()
{
	ActionInterval*  pAc		= FadeInEx::create(_fDuration / GetQueue()->GetSpeed());
	CCCallFunc*  pAcCallBack	= CCCallFuncN::create(this, callfuncN_selector(IActionAnimationFadeInEx::CallBackFuncN));
	ASSERT_LOG_ERROR(pAc && pAcCallBack);
	GetQueue()->GetTargetCur()->runAction( CCSequence::create(pAc,pAcCallBack, nullptr));

	GetQueue()->MarkWaitCallBack();
	return true;
}

void IActionAnimationFadeInEx::CallBackFuncN( Node* pNode )
{
	GetQueue()->OnActionOver();
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationFadeOutEx::IActionAnimationFadeOutEx( void )
{
	SetActionType(ACTION_FADE_OUT_EX);
}

IActionAnimationFadeOutEx::~IActionAnimationFadeOutEx( void )
{

}

bool IActionAnimationFadeOutEx::Init( float fDuration )
{
	_fDuration = fDuration;
	return true;
}

bool IActionAnimationFadeOutEx::OnExecute()
{
	ActionInterval*  pAc		= FadeOutEx::create(_fDuration / GetQueue()->GetSpeed());
	CCCallFunc*  pAcCallBack	= CCCallFuncN::create(this, callfuncN_selector(IActionAnimationFadeOutEx::CallBackFuncN));
	ASSERT_LOG_ERROR(pAc && pAcCallBack);
	GetQueue()->GetTargetCur()->runAction( CCSequence::create(pAc,pAcCallBack, nullptr));

	GetQueue()->MarkWaitCallBack();
	return true;
}

void IActionAnimationFadeOutEx::CallBackFuncN( Node* pNode )
{
	GetQueue()->OnActionOver();
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationCreate::IActionAnimationCreate( void )
{
	SetActionType(ACTION_ANIMATION_CREATE);
}

IActionAnimationCreate::~IActionAnimationCreate( void )
{

}

bool IActionAnimationCreate::Init( const std::string& sFileName,const Point& ptPostion )
{
	_sFileName = sFileName;
	_ptPostion = ptPostion;
	return true;
}

bool IActionAnimationCreate::OnExecute()
{
	//加载资源
	ApiCocos2dx::CacheArmatureFile(_sFileName);

	//创建动画
	std::string sArmature = ToolFrame::PickFileNameWithOutExt(_sFileName);
	Armature* pArmature = ApiCocos2dx::CreateArmature(sArmature);
	ASSERT_LOG_ERROR(pArmature);

	ApiCocos2dx::SetPostion(pArmature,_ptPostion);
	GetQueue()->GetParent()->addChild(pArmature,GetQueue()->GetZOrder());

	GetQueue()->AddTarget(pArmature);
	GetQueue()->SetCurTarget();
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationPlayByName::IActionAnimationPlayByName( void )
{
	SetActionType(ACTION_ANIMATION_PLAY_BY_NAME);
}

IActionAnimationPlayByName::~IActionAnimationPlayByName( void )
{

}

bool IActionAnimationPlayByName::Init( const VectorString& vName,int nLoop )
{
	_vName = vName;
	_nLoop = nLoop;
	return true;
}

bool IActionAnimationPlayByName::OnExecute()
{
	Armature* pArmature = dynamic_cast<Armature*>(GetQueue()->GetTargetCur());
	if (!pArmature)return false;

	if (_vName.empty()){
		if (!ApiCocos2dx::PlayArmature(pArmature,_nLoop))return false;
	}else{
		if (!ApiCocos2dx::PlayArmature(pArmature,_vName,_nLoop))return false;
	}
	
	ASSERT_LOG_ERROR(ApiCocos2dx::SetSpeed(pArmature,GetQueue()->GetSpeed()));

	if (_nLoop>=0)
	{
		CActionArmatureMonitor* pAction = dynamic_cast<CActionArmatureMonitor*>(pArmature->getActionByTag(COCOS_ACTION_ARMATURE_MONITOR));
		if (pAction)
		{
			pAction->SetCallBackOver(ToolFrame::Bind(&IActionAnimationPlayByName::OnActionArmatureOver,this));
			pAction->SetRemove(false);
			GetQueue()->MarkWaitCallBack();
		}
	}
	return true;
}

bool IActionAnimationPlayByName::OnDestory()
{
	Armature* pArmature = dynamic_cast<Armature*>(GetQueue()->GetTargetCur());
	if (!pArmature)return false;
	ApiCocos2dx::SetAnimationCallBackOver(pArmature,nullptr);
	return false;
}

bool IActionAnimationPlayByName::OnActionArmatureOver(Armature* pArmature)
{
	GetQueue()->OnActionOver();
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationPlayFileByName::IActionAnimationPlayFileByName( void )
{
	_pArmature = nullptr;
	SetActionType(ACTION_ANIMATION_PLAY_FILE_BY_NAME);
}

IActionAnimationPlayFileByName::~IActionAnimationPlayFileByName( void )
{

}

bool IActionAnimationPlayFileByName::Init( const Point& ptPostion,const std::string& sFileName,const VectorString& vName,int nLoop )
{
	_ptPostion	= ptPostion;
	_sFileName	= sFileName;
	_vName		= vName;
	_nLoop		= nLoop;
	return true;
}

bool IActionAnimationPlayFileByName::OnExecute()
{
	//传递进去都是循环播放 而是否能够实际循环播放 还取决于 动画编辑时的值
	if (_vName.empty())
		_pArmature = ApiCocos2dx::PlayArmature(_ptPostion,_sFileName,_nLoop);
	else
		_pArmature = ApiCocos2dx::PlayArmature(_ptPostion,_sFileName,_vName,_nLoop);

	if (!_pArmature)return false;

	GetQueue()->GetParentNode()->addChild(_pArmature);
	ASSERT_LOG_ERROR(ApiCocos2dx::SetSpeed(_pArmature,GetQueue()->GetSpeed()));

	if (_nLoop>=0)
	{
		CActionArmatureMonitor* pAction = dynamic_cast<CActionArmatureMonitor*>(_pArmature->getActionByTag(COCOS_ACTION_ARMATURE_MONITOR));
		if (pAction)
		{
			pAction->SetCallBackOver(ToolFrame::Bind(&IActionAnimationPlayFileByName::OnActionArmatureOver,this));
			GetQueue()->MarkWaitCallBack();
		}
	}
	return true;
}

bool IActionAnimationPlayFileByName::OnDestory()
{
	Armature* pArmature = dynamic_cast<Armature*>(GetQueue()->GetTargetCur());
	if (!pArmature)return false;
	ApiCocos2dx::SetAnimationCallBackOver(pArmature, nullptr);
	return false;
}

bool IActionAnimationPlayFileByName::OnActionArmatureOver( Armature* pArmature )
{
	GetQueue()->OnActionOver();
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationPlayToFrame::IActionAnimationPlayToFrame( void )
{
	_nFrameBegin = 0;
	_nFrameTarget = 0;
	_fTimePass = 0.0f;
	SetActionType(ACTION_ANIMATION_PLAY_TO_FRAME);
}

IActionAnimationPlayToFrame::~IActionAnimationPlayToFrame( void )
{

}

bool IActionAnimationPlayToFrame::Init( int nTarget )
{
	_nFrameTarget = nTarget;
	return true;
}

bool IActionAnimationPlayToFrame::OnExecute()
{
	Armature* pArmature = dynamic_cast<Armature*>(GetQueue()->GetTargetCur());
	if (!pArmature)return false;

	_nFrameBegin = pArmature->getAnimation()->getCurrentFrameIndex();

	if (_nFrameBegin == _nFrameTarget)return true;

	GetQueue()->GetParentNode()->getScheduler()->scheduleUpdate(this,0,false);
	GetQueue()->MarkWaitCallBack();
	return true;
}

bool IActionAnimationPlayToFrame::OnDestory()
{
	GetQueue()->GetParentNode()->getScheduler()->unscheduleUpdate(this);
	return true;
}

void IActionAnimationPlayToFrame::update( float dt )
{
	_fTimePass += dt;

	Armature* pArmature = dynamic_cast<Armature*>(GetQueue()->GetTargetCur());
	if (!pArmature)return ;
	
	float fInternal = ApiCocos2dx::GetAnimationInterval();
	int nFrame = pArmature->getAnimation()->getProcessScale() * (_fTimePass / fInternal);
	
	int nFrameCur = _nFrameBegin < _nFrameTarget ? _nFrameBegin + nFrame : _nFrameBegin - nFrame;
	pArmature->getAnimation()->gotoAndPause(nFrameCur);

	if (_nFrameBegin == _nFrameTarget){
		GetQueue()->OnActionOver();
	}
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationBoneAdd::IActionAnimationBoneAdd( void )
{
	SetActionType(ACTION_ANIMATION_BONE_ADD);
}

IActionAnimationBoneAdd::~IActionAnimationBoneAdd( void )
{

}

bool IActionAnimationBoneAdd::Init( const std::string& sParentBone,const std::string& sNewBone,Node* pNode )
{
	if (!pNode)return false;

	_sParentBone = sParentBone;
	_sNewBone = sNewBone;
	_pNode = pNode;

	_pNode->retain();

	return true;
}

bool IActionAnimationBoneAdd::OnExecute()
{
	Armature* pArmature = dynamic_cast<Armature*>(GetQueue()->GetTargetCur());
	if (!pArmature)return false;

	ApiCocos2dx::AddBone(pArmature,_sParentBone,_sNewBone,_pNode);
	return true;
}

bool IActionAnimationBoneAdd::OnDestory()
{
	_pNode->release();
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationDisplayAdd::IActionAnimationDisplayAdd( void )
{
	SetActionType(ACTION_ANIMATION_DISPLAY_ADD);
}

IActionAnimationDisplayAdd::~IActionAnimationDisplayAdd( void )
{

}

bool IActionAnimationDisplayAdd::Init(const std::string& sName,int nDisplayIndex /*= -1*/,int nTargetIndex /*= -1*/ )
{
	_sName = sName;
	_nDisplayIndex = nDisplayIndex;
	_nTargetIndex = nTargetIndex;
	return true;
}

bool IActionAnimationDisplayAdd::OnExecute()
{
	Armature* pArmature = dynamic_cast<Armature*>(GetQueue()->GetTargetCur());
	if (!pArmature)return false;

	return ApiCocos2dx::AddDisplay(pArmature,_sName,GetQueue()->FindTarget(_nTargetIndex),_nDisplayIndex,true,true);
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationDisplayRemove::IActionAnimationDisplayRemove( void )
{
	SetActionType(ACTION_ANIMATION_DISPLAY_REMOVE);
}

IActionAnimationDisplayRemove::~IActionAnimationDisplayRemove( void )
{

}

bool IActionAnimationDisplayRemove::Init(const std::string& sName,int nIndex)
{
	_sName = sName;
	_nIndex = nIndex;
	return true;
}

bool IActionAnimationDisplayRemove::OnExecute()
{
	Armature* pArmature = dynamic_cast<Armature*>(GetQueue()->GetTargetCur());
	if (!pArmature)return false;

	ApiCocos2dx::RemoveDisplay(pArmature,_sName,_nIndex);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationDisplayChange::IActionAnimationDisplayChange( void )
{
	SetActionType(ACTION_ANIMATION_DISPLAY_CHANGE);
}

IActionAnimationDisplayChange::~IActionAnimationDisplayChange( void )
{

}

bool IActionAnimationDisplayChange::Init(const std::string& sName,int nIndex /*= 0*/,bool bForce /*= true*/ )
{
	_sName = sName;
	_nIndex = nIndex;
	_bForce = bForce;
	return true;
}

bool IActionAnimationDisplayChange::OnExecute()
{
	Armature* pArmature = dynamic_cast<Armature*>(GetQueue()->GetTargetCur());
	if (!pArmature)return false;

	ApiCocos2dx::ChangeDisplay(pArmature,_sName,_nIndex,_bForce);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationPlayMusic::IActionAnimationPlayMusic( void )
{
	SetActionType(ACTION_SOUND_PLAY_MUSIC);
}

IActionAnimationPlayMusic::~IActionAnimationPlayMusic( void )
{

}

bool IActionAnimationPlayMusic::Init(const std::string& sFilePath,bool bLoop)
{
	_sFilePath = sFilePath;
	_bLoop = bLoop;
	return true;

}

bool IActionAnimationPlayMusic::OnExecute()
{
	ApiCocos2dx::PlayMusic(_sFilePath,_bLoop);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationPlaySound::IActionAnimationPlaySound( void )
{
	SetActionType(ACTION_SOUND_PLAY_EFFECT);
}

IActionAnimationPlaySound::~IActionAnimationPlaySound( void )
{

}

bool IActionAnimationPlaySound::Init(const std::string& sFilePath,bool bLoop)
{
	_sFilePath = sFilePath;
	_bLoop = bLoop;
	return true;
}

bool IActionAnimationPlaySound::OnExecute()
{
	ApiCocos2dx::PlaySound(_sFilePath,_bLoop);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationCallBack::IActionAnimationCallBack( void )
{
	SetActionType(ACTION_CALL_BACK);
}

IActionAnimationCallBack::~IActionAnimationCallBack( void )
{

}

bool IActionAnimationCallBack::Init(int nUserInt)
{
	_nUserInt = nUserInt;
	return true;
}

bool IActionAnimationCallBack::OnExecute()
{
	if (!GetQueue()->GetHandler())return false;
	GetQueue()->GetHandler()->OnQueueCallBack(_nUserInt);
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationMulitQueue::IActionAnimationMulitQueue( void )
{
	_pQueue = nullptr;
	SetActionType(ACTION_MULIT_QUEUE);
}

IActionAnimationMulitQueue::~IActionAnimationMulitQueue( void )
{
	if(_pQueue)
		_pQueue->release();
}

bool IActionAnimationMulitQueue::Init(CAnimationQueue* pParent)
{
	if (!pParent)return false;
	if (_pQueue)return false;

	_pQueue = CAnimationQueueMulit::Create();
	if (!_pQueue)return false;

	_pQueue->Init(this,pParent);
	_pQueue->retain();

	return true;
}

bool IActionAnimationMulitQueue::OnExecute()
{
	_pQueue->SetSpeed(GetQueue()->GetSpeed());
	_pQueue->StartUp();

	GetQueue()->MarkWaitCallBack();
	return true;
}

bool IActionAnimationMulitQueue::OnAnimationComplete()
{
	GetQueue()->OnActionOver();
	return true;
}

CAnimationQueueMulit* IActionAnimationMulitQueue::GetMulitQueue()
{
	return _pQueue;
}

bool IActionAnimationMulitQueue::OnAnimationSpeed( int nSpeed )
{
	_pQueue->SetSpeed(nSpeed);
	return true;
}

bool IActionAnimationMulitQueue::OnDestory()
{
	_pQueue->Destory();
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationNextFrame::IActionAnimationNextFrame( void )
{
	SetActionType(ACTION_NEXT_FRAME);
}

IActionAnimationNextFrame::~IActionAnimationNextFrame( void )
{

}

bool IActionAnimationNextFrame::Init(float fDuration,const Point& ptPostion,float fRotation,GLubyte uOpacity,float fScale,const std::string& sAnimationName)
{
	_fDuration	= fDuration;
	_ptPostion	= ptPostion;
	_fRotation	= fRotation;
	_uOpacity	= uOpacity;
	_fScale		= fScale;
	_sAnimationName	= sAnimationName;
	return true;
}

bool IActionAnimationNextFrame::OnExecute()
{
	float fRealTime = _fDuration / GetQueue()->GetSpeed();
	GetQueue()->GetTargetCur()->runAction(CCMoveTo::create	(fRealTime,_ptPostion));
	GetQueue()->GetTargetCur()->runAction(CCRotateTo::create(fRealTime,_fRotation));
	GetQueue()->GetTargetCur()->runAction(CCFadeTo::create	(fRealTime,_uOpacity));
	GetQueue()->GetTargetCur()->runAction(CCScaleTo::create	(fRealTime,_fScale));

	if (!_sAnimationName.empty())
	{
		Armature* pArmature = dynamic_cast<Armature*>(GetQueue()->GetTargetCur());
		ASSERT_LOG_ERROR(pArmature);
		ASSERT_LOG_ERROR(ApiCocos2dx::SetSpeed(pArmature,GetQueue()->GetSpeed()));
		ASSERT_LOG_ERROR(ApiCocos2dx::PlayArmature(pArmature,_sAnimationName,-1));
	}

	//设置回调
	{
		ActionInterval*  pAc	= CCDelayTime::create(fRealTime);
		CCCallFunc*  pAcCallBack = CCCallFuncN::create(this, callfuncN_selector(IActionAnimationNextFrame::CallBackFuncN));
		GetQueue()->GetTargetCur()->runAction( CCSequence::create(pAc,pAcCallBack, nullptr));
	}

	GetQueue()->MarkWaitCallBack();
	return true;
}

void IActionAnimationNextFrame::CallBackFuncN( Node* pNode )
{
	GetQueue()->OnActionOver();
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationExit::IActionAnimationExit( void )
{

}

IActionAnimationExit::~IActionAnimationExit( void )
{

}

bool IActionAnimationExit::Init()
{
	return true;
}

bool IActionAnimationExit::OnExecute()
{
	ApiCocos2dx::Exit();
	return true;
}

//////////////////////////////////////////////////////////////////////////

IActionAnimationOpenUrl::IActionAnimationOpenUrl( void )
{

}

IActionAnimationOpenUrl::~IActionAnimationOpenUrl( void )
{

}

bool IActionAnimationOpenUrl::Init( const std::string& sUrl )
{
	_sUrl = sUrl;
	return true;
}

bool IActionAnimationOpenUrl::OnExecute()
{
	return ToolFrame::OpenUrl(_sUrl);
}
//////////////////////////////////////////////////////////////////////////
IActionSpinePlayByName::IActionSpinePlayByName( void )
{
	SetActionType(ACTION_SPINE_PLAY_BY_NAME);
}

IActionSpinePlayByName::~IActionSpinePlayByName( void )
{

}

bool IActionSpinePlayByName::Init( const VectorString& vName ,int nLoop,float fDelay )
{
	_vName = vName;
	_nLoop = nLoop;
	_fDelay= fDelay;
	return true;
}

bool IActionSpinePlayByName::OnExecute()
{
	SkeletonAnimation* pArmature = dynamic_cast<SkeletonAnimation*>(GetQueue()->GetTargetCur());
	if (!pArmature)return false;

	ApiCocos2dx::SetSpeed(pArmature, GetQueue()->GetSpeed());
	if (!ApiCocos2dx::PlaySpineAnimation(pArmature, _vName, _nLoop, _fDelay))return false;

	if (_nLoop>=0)
	{
		ApiCocos2dx::SetSpineRemove(pArmature, false);
		ApiCocos2dx::SetSpineCallBackOver(pArmature, ToolFrame::Bind(&IActionSpinePlayByName::CallBackOver, this));
		GetQueue()->MarkWaitCallBack();
	}
	return true;
}

bool IActionSpinePlayByName::OnDestory(){
	SkeletonAnimation* pArmature = dynamic_cast<SkeletonAnimation*>(GetQueue()->GetTargetCur());
	if (!pArmature)return false;

	ApiCocos2dx::SetSpineCallBackOver(pArmature,nullptr);
	return true;
}

bool IActionSpinePlayByName::CallBackOver(SkeletonAnimation* pAnimation)
{
	GetQueue()->OnActionOver();
	return true;
}

//////////////////////////////////////////////////////////////////////////
IActionAnimationSpeed::IActionAnimationSpeed(void)
{
	SetActionType(ACTION_SET_SPEED);
}

IActionAnimationSpeed::~IActionAnimationSpeed(void)
{

}

bool IActionAnimationSpeed::Init(float fSpeed)
{
	_fSpeed = fSpeed;
	return true;
}

bool IActionAnimationSpeed::OnExecute()
{
	return GetQueue()->SetSpeed(_fSpeed);
}

#endif //MACRO_LIB_COCOS2D

