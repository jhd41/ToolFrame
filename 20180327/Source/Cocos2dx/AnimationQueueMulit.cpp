#include "AnimationQueueMulit.h"

#ifdef MACRO_LIB_COCOS2D

#include "ToolFrame.h"
#include "AnimationQueue.h"
#include "MLoger.h"

CAnimationQueueMulit::CAnimationQueueMulit(void)
{
	_pParent	= nullptr;
	_hAnimation = nullptr;
	_bDestoryed = false;
}

CAnimationQueueMulit::~CAnimationQueueMulit(void)
{
	ASSERT_LOG_ERROR(_bDestoryed);
}

bool CAnimationQueueMulit::Init( HAnimationQueue* hAnimation,CAnimationQueue* pParent )
{
	if (!hAnimation)return false;
	if (!pParent)return false;

	_hAnimation = hAnimation;
	_pParent= pParent;
	return true;
}

CAnimationQueue* CAnimationQueueMulit::CreateQueue()
{
	if (!_pParent)return nullptr;

	CAnimationQueue* pQueue = CAnimationQueue::Create();
	if (!pQueue)return nullptr;

	pQueue->Init(_pParent->GetParentNode(),this);

	ToolFrame::PushBack(_vQueue,pQueue);
	pQueue->retain();
	return pQueue;
}

bool CAnimationQueueMulit::RunActions()
{
	if (!_vQueue.empty())
	{
		VectorAnimationQueue::iterator itr;
		foreach(itr,_vQueue){
			CAnimationQueue* pQueue = *itr;
			ASSERT_LOG_ERROR(pQueue);

			pQueue->RunActions();
		}
	}

	return true;
}

bool CAnimationQueueMulit::OnAnimationComplete()
{
	if (IsAllAnimationComplete())
	{
		ASSERT_LOG_ERROR(_hAnimation);
		_hAnimation->OnAnimationComplete();
	}
	return true;
}

bool CAnimationQueueMulit::SetSpeed( float fSpeed )
{
	VectorAnimationQueue::iterator itr;
	foreach(itr,_vQueue){
		CAnimationQueue* pQueue = *itr;
		ASSERT_LOG_ERROR(pQueue);

		pQueue->SetSpeed(fSpeed);
	}
	return true;
}

bool CAnimationQueueMulit::Destory()
{
	ASSERT_LOG_ERROR(!_bDestoryed);
	if (_bDestoryed)return false;
	_bDestoryed = true;

	_pParent->GetParentNode()->getScheduler()->unscheduleUpdate(this);
	
	VectorAnimationQueue::iterator itr;
	foreach(itr,_vQueue){
		CAnimationQueue* pQueue = *itr;
		ASSERT_LOG_ERROR(pQueue);

		pQueue->Destory();
		pQueue->release();
	}
	ToolFrame::Clear(_vQueue);
	return true;
}

bool CAnimationQueueMulit::StartUp()
{
	_pParent->GetParentNode()->getScheduler()->scheduleUpdate(this,0,false);
	
	RunActions();
	return true;
}

void CAnimationQueueMulit::update( float dt ){
	RunActions();
}

bool CAnimationQueueMulit::IsAllAnimationComplete() const
{
	VectorAnimationQueue::const_iterator itr;
	foreach(itr,_vQueue){
		const CAnimationQueue* pQueue = *itr;
		ASSERT_LOG_ERROR(pQueue);

		if (!pQueue->IsEmpty())
			return false;
	}

	return true;
}

bool CAnimationQueueMulit::OnExecuteActionFaild( int eActionType )
{
	ASSERT_LOG_ERROR(_pParent);
	return _pParent->GetHandler()->OnExecuteActionFaild(eActionType);
}

#endif //MACRO_LIB_COCOS2D
