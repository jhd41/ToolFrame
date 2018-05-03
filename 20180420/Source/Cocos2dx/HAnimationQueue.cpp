#include "HAnimationQueue.h"

#ifdef MACRO_LIB_COCOS2D

#include "AnimationQueue.h"

HAnimationQueue::HAnimationQueue()
{

}

HAnimationQueue::~HAnimationQueue()
{

}

bool HAnimationQueue::OnAnimationComplete()
{
	return false;
}

bool HAnimationQueue::OnQueueCallBack( int nUserDataInt )
{
	return false;
}

bool HAnimationQueue::OnExecuteActionFaild( int eActionType )
{
	return false;
}

#endif //MACRO_LIB_COCOS2D
