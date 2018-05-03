#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "TouchAnalyzer.h"

class CTouchListener
{
	typedef std::vector<ITouchAnalyzer*> VectorAnalyzer;
public:
	bool				SetNode(Node* pNode);
	bool				SetHandler(HTouchListener* hHandler);
	bool				SetEnabled(bool bEnabled);
	bool				IsEnabled()const;
	const VectorTouch&	GetTouches()const;
	Node*				GetNode()const;
	HTouchListener*		GetHandler()const;
public:
	template<typename T>
	T*					FindAnalyzer()const;
private:
	bool Construction();//构造 不要轻易调用
	bool Destructor();	//析构 不要轻易调用
public:
	virtual bool OnTouchBegan	(Touch* touch, Event *unusedEvent);
	virtual void OnTouchMoved	(Touch* touch, Event *unusedEvent);
	virtual void OnTouchEnded	(Touch* touch, Event *unusedEvent);
	virtual void OnTouchCancelled(Touch* touch, Event *unusedEvent);
public:
	CTouchListener(const CTouchListener& lister);//拷贝构造
	CTouchListener& operator = (const CTouchListener& lister );
public:
	CTouchListener(void);
	virtual ~CTouchListener(void);
private:
	bool						_bEnabled;
	
	Node*						_pNode;

	VectorTouch					_vTouch;
	VectorAnalyzer				_vAnalyzer;
	HTouchListener*				_hHandler;
};

template<typename T>
T* CTouchListener::FindAnalyzer() const
{
	VectorAnalyzer::const_iterator itr;
	foreach(itr,_vAnalyzer){
		T* p = dynamic_cast<T*>(*itr);
		if (p)
			return p;
	}

	return nullptr;
}

#endif //MACRO_LIB_COCOS2D
