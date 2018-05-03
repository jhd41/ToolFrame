#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "HTouchHandler.h"
#include "TouchListener.h"

class CTouchGroup
{
	typedef std::map<Node*,CTouchListener> MapTouchLister;
public:
	bool			SetHandler(HTouchListener* hHandler);
	bool			Init();
	bool			Destory();
	CTouchListener*	AddListener(Node* pNode,HTouchListener* hHander,bool bEnabled = true);
	bool			RemoveListener(Node* pNode);

	bool			RemoveListener();

	bool			SetEnabled( bool bEnabled );
	bool			IsEnabled() const;
public:
	virtual bool OnTouchBegan	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchMoved	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchEnded	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchCancelled(Touch* touch, Event *unusedEvent);
public:
	CTouchGroup(void);
	virtual ~CTouchGroup(void);
private:
	MapTouchLister				_vTouch;
	HTouchListener*				_hHandler;
	bool						_bEnabled;
};

#endif //MACRO_LIB_COCOS2D
