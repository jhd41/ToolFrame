#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "HAnimationQueue.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class CAnimationQueue;
class CAnimationQueueMulit
	:public Ref
	,public HAnimationQueue
{
public:
	typedef std::vector<CAnimationQueue*> VectorAnimationQueue;
public:
	COCOS2DX_CREATE(CAnimationQueueMulit);
public:
	bool				Init(HAnimationQueue* hAnimation,CAnimationQueue* pParent);
	CAnimationQueue*	CreateQueue();
	bool				StartUp();
	bool				SetSpeed(float fSpeed);
	bool				Destory();
private:
	bool				RunActions();
	virtual bool		OnAnimationComplete();//动画队列里的动画播放完成
	bool				IsAllAnimationComplete()const;
	virtual bool		OnExecuteActionFaild(int eActionType);
public:
	void update( float dt );
public:
	CAnimationQueueMulit(void);
	virtual ~CAnimationQueueMulit(void);
private:
	VectorAnimationQueue	_vQueue;
	HAnimationQueue*		_hAnimation;
	CAnimationQueue*		_pParent;
	
	bool					_bDestoryed;
};

#endif //MACRO_LIB_COCOS2D
