#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

class TOOLFRAME_DLL HAnimationQueue
{
public:
	virtual bool OnAnimationComplete();		//所有的都完成
	virtual bool OnQueueCallBack(int nUserDataInt);
	virtual bool OnExecuteActionFaild(int eActionType);
public:
	HAnimationQueue();
	virtual ~HAnimationQueue();
};

#endif //MACRO_LIB_COCOS2D
