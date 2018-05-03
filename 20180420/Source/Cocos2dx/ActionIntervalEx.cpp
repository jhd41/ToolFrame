#include "ActionIntervalEx.h"

#ifdef MACRO_LIB_COCOS2D

#include "ApiCocos2dx.h"
#include "MLoger.h"

NS_CC_BEGIN

//
// FadeInEx
//

FadeInEx* FadeInEx::create(float d)
{
	FadeInEx* action = new FadeInEx();

	action->initWithDuration(d,255.0f);
	action->autorelease();

	return action;
}

FadeInEx* FadeInEx::clone() const
{
	// no copy constructor
	auto a = new FadeInEx();
	a->initWithDuration(_duration,255.0f);
	a->autorelease();
	return a;
}

void FadeInEx::setReverseAction(FadeToEx *ac)
{
	_reverseAction = ac;
}


FadeToEx* FadeInEx::reverse() const
{
	auto action = FadeOutEx::create(_duration);
	action->setReverseAction(const_cast<FadeInEx*>(this));
	return action;

}

void FadeInEx::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);

	if (nullptr != _reverseAction) {
		this->_toOpacity = this->_reverseAction->_fromOpacity;
	}else{
		_toOpacity = 255.0f;
	}

	if (target) {
		_fromOpacity = 0;//SongJ target->getOpacity();
	}
}



//
// FadeOutEx
//

FadeOutEx* FadeOutEx::create(float d)
{
	FadeOutEx* action = new FadeOutEx();

	action->initWithDuration(d,0.0f);
	action->autorelease();

	return action;
}

FadeOutEx* FadeOutEx::clone() const
{
	// no copy constructor
	auto a = new FadeOutEx();
	a->initWithDuration(_duration,0.0f);
	a->autorelease();
	return a;
}

void FadeOutEx::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);

	if (nullptr != _reverseAction) {
		_toOpacity = _reverseAction->_fromOpacity;
	}else{
		_toOpacity = 0.0f;
	}

	if (target) {
		_fromOpacity = target->getOpacity();
	}
}

void FadeOutEx::setReverseAction(FadeToEx *ac)
{
	_reverseAction = ac;
}


FadeToEx* FadeOutEx::reverse() const
{
	auto action = FadeInEx::create(_duration);
	action->setReverseAction(const_cast<FadeOutEx*>(this));
	return action;
}

//
// FadeToEx
//

FadeToEx* FadeToEx::create(float duration, GLubyte opacity)
{
	FadeToEx* pFadeToEx = new FadeToEx();
	pFadeToEx->initWithDuration(duration, opacity);
	pFadeToEx->autorelease();

	return pFadeToEx;
}

bool FadeToEx::initWithDuration(float duration, GLubyte opacity)
{
	if (ActionInterval::initWithDuration(duration))
	{
		_toOpacity = opacity;
		return true;
	}

	return false;
}

FadeToEx* FadeToEx::clone() const
{
	// no copy constructor
	auto a = new FadeToEx();
	a->initWithDuration(_duration, _toOpacity);
	a->autorelease();
	return a;
}

FadeToEx* FadeToEx::reverse() const
{
	CCASSERT(false, "reverse() not supported in FadeToEx");
	return nullptr;
}

void FadeToEx::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);

	if (target)
	{
		_fromOpacity = target->getOpacity();
	}
	/*_fromOpacity = target->getOpacity();*/
}

void FadeToEx::update(float time)
{
	if (_target)
	{
		ApiCocos2dx::SetOpacity(_target,(GLubyte)(_fromOpacity + (_toOpacity - _fromOpacity) * time),true);//SongJ

		//_target->setOpacity((GLubyte)(_fromOpacity + (_toOpacity - _fromOpacity) * time));
	}
	/*_target->setOpacity((GLubyte)(_fromOpacity + (_toOpacity - _fromOpacity) * time));*/
}

//
// MoveToEx
//

MoveToEx::MoveToEx()
{
	_bSetBegin = false;
}

MoveToEx::~MoveToEx()
{

}

MoveToEx* MoveToEx::create(float duration, const Vec2& ptEnd)
{
	MoveToEx *ret = new MoveToEx();
	ret->initWithDuration(duration, ptEnd);
	ret->autorelease();

	return ret;
}

MoveToEx* MoveToEx::create( float duration, const Vec2& ptEnd,const Vec2& ptBegin )
{
	MoveToEx *ret = new MoveToEx();
	ret->initWithDuration(duration, ptEnd,ptBegin);
	ret->autorelease();

	return ret;
}

MoveToEx* MoveToEx::create( float duration, const Node* pNodeEnd )
{
	if (!pNodeEnd)return nullptr;
	
	MoveToEx *ret = new MoveToEx();
	ret->initWithDuration(duration, ApiCocos2dx::GetWorldPostion(pNodeEnd));
	ret->autorelease();

	return ret;
}

MoveToEx* MoveToEx::create( float duration, const Node* pNodeEnd,const Node* pNodeBegin )
{
	if (!pNodeEnd)return nullptr;
	if (!pNodeBegin)return nullptr;

	MoveToEx *ret = new MoveToEx();
	ret->initWithDuration(duration, ApiCocos2dx::GetWorldPostion(pNodeEnd),ApiCocos2dx::GetWorldPostion(pNodeBegin));
	ret->autorelease();

	return ret;
}

bool MoveToEx::initWithDuration(float duration, const Vec2& ptEnd)
{
	if (ActionInterval::initWithDuration(duration))
	{
		_ptEnd = ptEnd;
		_bSetBegin = false;
		return true;
	}

	return false;
}

bool MoveToEx::initWithDuration( float duration, const Vec2& ptEnd,const Vec2& ptBegin )
{
	if (ActionInterval::initWithDuration(duration))
	{
		_ptEnd = ptEnd;
		_bSetBegin = true;
		_ptBegin = ptBegin;
		return true;
	}

	return false;
}

MoveToEx* MoveToEx::clone() const
{
	// no copy constructor
	auto a = new MoveToEx();
	if (_bSetBegin)
		a->initWithDuration(_duration, _ptEnd);
	else
		a->initWithDuration(_duration, _ptEnd,_ptBegin);
	a->autorelease();
	return a;
}

void MoveToEx::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);

	if (_bSetBegin)
		ApiCocos2dx::SetWorldPostion(target,_ptBegin);
	else
		_ptBegin = ApiCocos2dx::GetWorldPostion(target);

	_ptDelta = _ptEnd - _ptBegin;
}

void MoveToEx::update( float t )
{
	if (_target)
	{
		if (Point::ZERO != _ptDelta)
		{
			ApiCocos2dx::SetWorldPostion(_target,_ptBegin + _ptDelta * t);
		}
	}
}

MoveToEx* MoveToEx::reverse( void ) const 
{
	return MoveToEx::create(_duration, Vec2( -_ptDelta.x, -_ptDelta.y));
}

//////////////////////////////////////////////////////////////////////////
CActionArmatureMonitor::CActionArmatureMonitor()
{
	_nLoop = -1;
	_bDone = false;
	_bRemove = true;
	setTag(COCOS_ACTION_ARMATURE_MONITOR);
}

CActionArmatureMonitor::~CActionArmatureMonitor()
{

}

CActionArmatureMonitor* CActionArmatureMonitor::create( int nLoop,const VectorString& vName,bool bRemove /*= true*/)
{
	if (vName.empty())return nullptr;

	CActionArmatureMonitor* pAction = new CActionArmatureMonitor();
	pAction->_nLoop = nLoop;
	pAction->_vName = vName;
	pAction->_bRemove = bRemove;
	pAction->_sLastAnmiation = ToolFrame::GetBack(vName);
	pAction->autorelease();

	return pAction;
}

CActionArmatureMonitor* CActionArmatureMonitor::clone() const 
{
	// no copy constructor
	auto pAction = new CActionArmatureMonitor();
	pAction->_nLoop				= _nLoop;
	pAction->_vName				= _vName;
	pAction->_bDone				= _bDone;
	pAction->_bRemove			= _bRemove;
	pAction->_fnMovement		= _fnMovement;
	pAction->_fnOver			= _fnOver;
	pAction->_sLastAnmiation	= _sLastAnmiation;
	pAction->autorelease();
	return pAction;
}

CActionArmatureMonitor* CActionArmatureMonitor::reverse( void ) const 
{
	CCASSERT(false, "reverse() not supported in CActionArmatureRemove");
	return nullptr;
}

void CActionArmatureMonitor::startWithTarget( Node *target )
{
	Action::startWithTarget(target);

	Armature* pArmature = dynamic_cast<Armature*>(target);
	if (pArmature)
		pArmature->getAnimation()->setMovementEventCallFunc(ToolFrame::Bind(&CActionArmatureMonitor::CallBack,this));
}

bool CActionArmatureMonitor::isDone() const
{
	return false;
}

void CActionArmatureMonitor::CallBack( Armature* pArmature, MovementEventType eEventType,const std::string& sName )
{
	//回调上层事件
	if (_fnMovement)
		_fnMovement(pArmature,eEventType,sName);

	//移除
	if (COMPLETE == eEventType || LOOP_COMPLETE == eEventType)
		ToolFrame::EraseByValue(_vName,sName);

	//如果列表中都没播放完 不处理
	if (!_vName.empty())
		return;

	//如果已经完成 保持最后一个动画继续播放下去
	if (_bDone){
		if (COMPLETE == eEventType){
			//继续播放
			ASSERT_LOG_ERROR(pArmature);
			pArmature->getAnimation()->play(_sLastAnmiation,-1,0);
		}
		return ;
	}
	
	//一次性的(包含 程序要求循环，但美术制作时定义为一次性，最终还是归为1次性)
	if (COMPLETE == eEventType){
		//判断结束
		if (_nLoop >= 0)
			OnOver();//结束之后还需要继续播放下去

		//继续播放
		ASSERT_LOG_ERROR(pArmature);
		pArmature->getAnimation()->play(_sLastAnmiation,-1,0);
	}

	//循环播放的
	if (LOOP_COMPLETE == eEventType)
	{
		if (_nLoop >= 0)
		{
			if (_nLoop>0)
				--_nLoop;
			if (_nLoop<=0)
				OnOver();
		}
	}

	if (_bDone && _bRemove)
		ApiCocos2dx::RemoveFromParentAndCleanupNextFrame(pArmature);
}

void CActionArmatureMonitor::stop() {
	Armature* pArmature = dynamic_cast<Armature*>(getTarget());
	if (pArmature)
		pArmature->getAnimation()->setMovementEventCallFunc(nullptr);

	return Action::stop();
}

bool CActionArmatureMonitor::OnOver()
{
	_bDone = true;

	Armature* pArmature = dynamic_cast<Armature*>(getTarget());
	if (!pArmature)return false;

	if (_fnOver)
		_fnOver(pArmature);

	return true;
}

bool CActionArmatureMonitor::SetRemove( bool bRemove )
{
	_bRemove = bRemove;
	return true;
}

void CActionArmatureMonitor::step( float dt )
{

}

bool CActionArmatureMonitor::SetCallBackMovement( FnActionArmatureMovement fnMovement )
{
	_fnMovement = fnMovement;
	return true;
}

bool CActionArmatureMonitor::SetCallBackOver( FnActionArmatureOver fnOver )
{
	_fnOver = fnOver;
	return true;
}

//////////////////////////////////////////////////////////////////////////
CActionSpineMonitor::CActionSpineMonitor()
{
	_bRemove = false;
	_nLoop = -1;
	_pEntryEnd = nullptr;
	setTag(COCOS_ACTION_SPINE_MONITOR);
}

CActionSpineMonitor::~CActionSpineMonitor()
{
}

CActionSpineMonitor* CActionSpineMonitor::create( int nLoop,bool bRemove /*= true*/ )
{
	CActionSpineMonitor* pAction = new CActionSpineMonitor();
	pAction->_nLoop		= nLoop;
	pAction->_bRemove	= bRemove;
	pAction->autorelease();

	return pAction;
}


CActionSpineMonitor* CActionSpineMonitor::clone() const
{
	// no copy constructor
	auto a = new CActionSpineMonitor();
	a->_nLoop	= _nLoop;
	a->_fnEvent	= _fnEvent;
	a->_fnOver	= _fnOver;
	a->_bRemove	= _bRemove;
	a->autorelease();
	return a;
}

CActionSpineMonitor* CActionSpineMonitor::reverse() const
{
	CCASSERT(false, "reverse() not supported in CActionSpineMonitor");
	return nullptr;
}

void CActionSpineMonitor::startWithTarget( Node *target )
{
	Action::startWithTarget(target);

	SkeletonAnimation* pSpine = dynamic_cast<SkeletonAnimation*>(target);
	if (pSpine){
		pSpine->setCompleteListener(ToolFrame::Bind(&CActionSpineMonitor::CallBackRemoveComplete,this));
		pSpine->setEventListener(ToolFrame::Bind(&CActionSpineMonitor::CallBackEvent,this));
	}
}

void CActionSpineMonitor::CallBackRemoveComplete(spTrackEntry* entry)
{
	if (!_pEntryEnd || _pEntryEnd == entry)
	{
		_pEntryEnd = nullptr;

		SkeletonAnimation* pSpine = dynamic_cast<SkeletonAnimation*>(getTarget());
		if (pSpine) {

			if (_fnOver)
				_fnOver(pSpine);

			if (_bRemove)
				ApiCocos2dx::RemoveFromParentAndCleanupNextFrame(pSpine);
		}
	}


// 	if (_nLoop>=0 && loopCount >= _nLoop){
// 		SkeletonAnimation* pSpine = dynamic_cast<SkeletonAnimation*>(getTarget());
// 		if (pSpine){
// 
// 			if (_fnOver)
// 				_fnOver(pSpine);
// 
// 			if (_bRemove)
// 				ApiCocos2dx::RemoveFromParentAndCleanupNextFrame(pSpine);
// 		}
// 	}
}

void CActionSpineMonitor::CallBackEvent(spTrackEntry* entry, spEvent* event){
	SkeletonAnimation* pSpine = dynamic_cast<SkeletonAnimation*>(getTarget());
	if (pSpine){
		if (_fnEvent) {
			std::string sEvent; std::string sEventArg;
			if (event->data && event->data->name)
			{
				std::string sSpineEvent = event->data->name;
				sSpineEvent = ToolFrame::ToUpperCase(sSpineEvent);

				VectorString vReturn;
				
				if (ToolFrame::GetStringByFormat(vReturn, sSpineEvent,"{Value}","TF|{Value}:{Value}"))
				{
					sEvent = ToolFrame::ToUpperCase(vReturn[0]);
					sEventArg = vReturn[1];
				}
				else {
					if (ToolFrame::GetStringByFormat(vReturn, sSpineEvent, "{Value}", "TF|{Value}")) {
						sEvent = ToolFrame::ToUpperCase(vReturn[0]);
					}
				}

			}
			if (!_fnEvent(pSpine, entry, event, sEvent, sEventArg))
			{
				if (_fnEventErr)
					_fnEventErr(pSpine, entry, event, sEvent, sEventArg);
			}
		}
	}
}

bool CActionSpineMonitor::isDone() const
{
	return false;
}


bool CActionSpineMonitor::SetLoop(int nLoop)
{
	_nLoop = nLoop;
	return true;
}

bool CActionSpineMonitor::SetRemove(bool bRemove)
{
	_bRemove = bRemove;
	return true;
}

void CActionSpineMonitor::step( float dt )
{

}


void cocos2d::CActionSpineMonitor::stop()
{
	SkeletonAnimation* pSpine = dynamic_cast<SkeletonAnimation*>(_target);
	if (pSpine)
		ApiCocos2dx::SetCallFuncNull(pSpine);
}

bool CActionSpineMonitor::SetCallBackEvent(FnActionSpineEvent fnEvent)
{
	_fnEvent = fnEvent;
	return true;
}

bool CActionSpineMonitor::SetCallBackOver( FnActionSpineOver fnOver )
{
	_fnOver = fnOver;
	return true;
}

bool CActionSpineMonitor::SetCallBackEventErr(FnActionSpineEvent fnEvent)
{
	_fnEventErr = fnEvent;
	return true;
}

bool CActionSpineMonitor::SetEntryEnd(spTrackEntry* pEntryEnd)
{
	_pEntryEnd = pEntryEnd;
	return true;
}

//////////////////////////////////////////////////////////////////////////
CActionSpineBindBones* CActionSpineBindBones::create( SkeletonAnimation* pAnimation,const std::string& sBones,Node* pNode )
{
	if (!pAnimation)return nullptr;
	if (!pNode)return nullptr;
	spBone* pBone = pAnimation->findBone(sBones);
	if (!pBone)return nullptr;	

	CActionSpineBindBones* pFadeToEx = new CActionSpineBindBones();
	pFadeToEx->_pBone = pBone;
	pFadeToEx->_pNode = pNode;
	
	pFadeToEx->autorelease();

	return pFadeToEx;
}

CActionSpineBindBones* CActionSpineBindBones::clone() const 
{
	// no copy constructor
	auto a = new CActionSpineBindBones();
	a->_pBone = _pBone;
	a->_pNode = _pNode;
	a->autorelease();
	return a;
}

CActionSpineBindBones* CActionSpineBindBones::reverse( void ) const 
{
	CCASSERT(false, "reverse() not supported in CActionSpineBindBones");
	return nullptr;
}

void CActionSpineBindBones::update( float time )
{
	ApiCocos2dx::SetWorldPostion(_pNode,ccp(_pBone->worldX,_pBone->worldY));
}

bool CActionSpineBindBones::isDone() const
{
	return false;
}

void CActionSpineBindBones::step( float dt )
{

}

//////////////////////////////////////////////////////////////////////////
CActionVisible::CActionVisible()
{
	_bVisible = false;
	_bDone = false;
}

CActionVisible::~CActionVisible()
{

}

CActionVisible* CActionVisible::create( bool bVisible)
{
	CActionVisible* pAction = new CActionVisible();
	pAction->_bVisible		= bVisible;
	pAction->autorelease();

	return pAction;
}

CActionVisible* CActionVisible::clone() const 
{
	// no copy constructor
	auto a = new CActionVisible();
	a->_bVisible = _bVisible;
	a->_bDone = _bDone;
	a->autorelease();
	return a;
}

CActionVisible* CActionVisible::reverse( void ) const 
{
	// no copy constructor
	auto a = new CActionVisible();
	a->_bVisible = !_bVisible;
	a->_bDone = _bDone;
	a->autorelease();
	return a;
}

void CActionVisible::update( float time )
{
	getTarget()->setVisible(_bVisible);
	_bDone = true;
}

bool CActionVisible::isDone() const
{
	return _bDone;
}

void CActionVisible::step( float dt )
{

}


NS_CC_END
#endif //MACRO_LIB_COCOS2D

//////////////////////////////////////////////////////////////////////////

