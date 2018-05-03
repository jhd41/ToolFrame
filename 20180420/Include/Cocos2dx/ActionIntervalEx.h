#pragma once

#include "MacroCocos2dx.h"

#include "ApiCocos2dx.h"

#include "ToolFrame.h"

#ifdef MACRO_LIB_COCOS2D

NS_CC_BEGIN

/** @brief Fades an object that implements the RGBAProtocol protocol. It modifies the opacity from the current value to a custom one.
 @warning This action doesn't support "reverse"
 */
class TOOLFRAME_DLL FadeToEx : public ActionInterval
{
public:
    /** creates an action with duration and opacity */
    static FadeToEx* create(float duration, GLubyte opacity);

    //
    // Overrides
    //
    virtual FadeToEx* clone() const override;
	virtual FadeToEx* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    FadeToEx() {}
    virtual ~FadeToEx() {}

    /** initializes the action with duration and opacity */
    bool initWithDuration(float duration, GLubyte opacity);

protected:
    GLubyte _toOpacity;
    GLubyte _fromOpacity;
    friend class FadeOutEx;
    friend class FadeInEx;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeToEx);
};


/** @brief Fades In an object that implements the RGBAProtocol protocol. It modifies the opacity from 0 to 255.
 The "reverse" of this action is FadeOutEx
 */
class TOOLFRAME_DLL FadeInEx : public FadeToEx
{
public:
    /** creates the action */
    static FadeInEx* create(float d);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual FadeInEx* clone() const override;
	virtual FadeToEx* reverse(void) const override;
    
    void setReverseAction(FadeToEx* ac);

protected:
    FadeInEx():_reverseAction(nullptr) {}
    virtual ~FadeInEx() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeInEx);
    FadeToEx* _reverseAction;
};

/** @brief Fades Out an object that implements the RGBAProtocol protocol. It modifies the opacity from 255 to 0.
 The "reverse" of this action is FadeInEx
*/
class TOOLFRAME_DLL FadeOutEx : public FadeToEx
{
public:
    /** creates the action */
    static FadeOutEx* create(float d);

    //
    // Overrides
    //
    virtual void startWithTarget(Node *target) override;
    virtual FadeOutEx* clone() const  override;
	virtual FadeToEx* reverse(void) const override;
    
    void setReverseAction(FadeToEx* ac);

protected:
    FadeOutEx():_reverseAction(nullptr) {}
    virtual ~FadeOutEx() {}
private:
    CC_DISALLOW_COPY_AND_ASSIGN(FadeOutEx);
    FadeToEx* _reverseAction;
};

/** Moves a Node object to the position x,y. x and y are absolute coordinates by modifying it's position attribute.
 Several MoveTo actions can be concurrently called, and the resulting
 movement will be the sum of individual movements.
 @since v2.1beta2-custom
 */
class TOOLFRAME_DLL MoveToEx : public ActionInterval
{
public:
    /** creates the action */
    static MoveToEx* create(float duration, const Vec2& ptEnd);
	static MoveToEx* create(float duration, const Vec2& ptEnd,const Vec2& ptBegin);

	static MoveToEx* create(float duration, const Node* pNodeEnd);
	static MoveToEx* create(float duration, const Node* pNodeEnd,const Node* pNodeBegin);
	
    //
    // Overrides
    //
    virtual MoveToEx* clone() const override;
	virtual MoveToEx* reverse(void) const  override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
CC_CONSTRUCTOR_ACCESS:
    MoveToEx();
    virtual ~MoveToEx();

    /** initializes the action */
    bool initWithDuration(float duration, const Vec2& ptEnd);
	bool initWithDuration(float duration, const Vec2& ptEnd,const Vec2& ptBegin);
protected:
	Vec2 _ptBegin;
    Vec2 _ptEnd;
	bool _bSetBegin;
	Point _ptDelta;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(MoveToEx);
};

//////////////////////////////////////////////////////////////////////////
//可见
class TOOLFRAME_DLL CActionVisible : public FiniteTimeAction
{
public:
    /** creates the action */
    static CActionVisible* create(bool bVisible);

    //
    // Overrides
    //
 
    virtual CActionVisible* clone() const  override;
	virtual CActionVisible* reverse(void) const override;
	virtual void update(float time);
	virtual bool isDone() const;
	virtual void step(float dt);
protected:
    CActionVisible();
    virtual ~CActionVisible();
private:
    CC_DISALLOW_COPY_AND_ASSIGN(CActionVisible);
private:
	bool	_bVisible;
	bool	_bDone;
};

//监视Armature
class TOOLFRAME_DLL CActionArmatureMonitor 
	: public Action
{
public:
	virtual bool SetCallBackMovement(FnActionArmatureMovement fnMovement);
	virtual bool SetCallBackOver(FnActionArmatureOver fnOver);
	virtual bool SetRemove(bool bRemove);//设置需要移除
public:
	/** creates an action with duration and opacity */
	static CActionArmatureMonitor* create(int nLoop,const VectorString& vName,bool bRemove = true);

	//
	// Overrides
	//
	virtual CActionArmatureMonitor* clone() const override;
	virtual CActionArmatureMonitor* reverse(void) const override;
	virtual void startWithTarget(Node *target);
	virtual bool isDone() const;
	virtual void step(float dt);
	virtual void stop();
CC_CONSTRUCTOR_ACCESS:
	CActionArmatureMonitor();
	virtual ~CActionArmatureMonitor();

	void	CallBack(Armature* pArmature, MovementEventType eEventType,const std::string& sName);
	virtual bool OnOver();
protected:
	int						_nLoop;
	VectorString			_vName;
	bool					_bDone;
	bool					_bRemove;
	FnActionArmatureMovement _fnMovement;
	FnActionArmatureOver	_fnOver;

	std::string				_sLastAnmiation;
private:
	CC_DISALLOW_COPY_AND_ASSIGN(CActionArmatureMonitor);
};

//监视Spine
class TOOLFRAME_DLL CActionSpineMonitor 
	: public Action
{
public:
	virtual bool SetLoop(int nLoop);		//设置循环
	virtual bool SetRemove(bool bRemove);	//设置需要移除
	virtual bool SetEntryEnd(spTrackEntry* pEntryEnd);
	virtual bool SetCallBackEvent(FnActionSpineEvent fnEvent);
	virtual bool SetCallBackOver(FnActionSpineOver fnOver);
	virtual bool SetCallBackEventErr(FnActionSpineEvent fnEvent);
public:
	/** creates an action with duration and opacity */
	static CActionSpineMonitor* create(int nLoop,bool bRemove = false);

	// Overrides
	//
	virtual CActionSpineMonitor* clone() const override;
	virtual CActionSpineMonitor* reverse(void) const override;
	virtual void startWithTarget(Node *target);
	virtual bool isDone() const;
	virtual void step(float dt);
	virtual void stop();
CC_CONSTRUCTOR_ACCESS:
	CActionSpineMonitor();
	virtual ~CActionSpineMonitor();

	void CallBackRemoveComplete(spTrackEntry* entry);
	void CallBackEvent(spTrackEntry* entry, spEvent* event);
protected:
	int					_nLoop;
	bool				_bRemove;
	spTrackEntry*		_pEntryEnd;//最后一个动画实体

	FnActionSpineEvent	_fnEvent;
	FnActionSpineOver	_fnOver;
	FnActionSpineEvent	_fnEventErr;
private:
	CC_DISALLOW_COPY_AND_ASSIGN(CActionSpineMonitor);
};

//绑定骨骼
class TOOLFRAME_DLL CActionSpineBindBones
	: public Action
{
public:
	/** creates an action with duration and opacity */
	static CActionSpineBindBones* create(SkeletonAnimation* pAnimation,const std::string& sBones,Node* pNode);
	virtual void update(float time);
	virtual bool isDone() const;
	virtual void step(float dt);
	//
	// Overrides
	//
	virtual CActionSpineBindBones* clone() const override;
	virtual CActionSpineBindBones* reverse(void) const override;
CC_CONSTRUCTOR_ACCESS:
	CActionSpineBindBones(){}
	virtual ~CActionSpineBindBones(){}
protected:
	spBone*				_pBone;
	Node*				_pNode;
private:
	CC_DISALLOW_COPY_AND_ASSIGN(CActionSpineBindBones);
};

NS_CC_END

//设置数值
template<typename T,typename TValue>
class TOOLFRAME_DLL TActionSetValue : public ActionInterval
{
public:
	/** creates the action */
	static TActionSetValue* create(TValue fTargetValue ,float fDuration){
		TActionSetValue* action = new TActionSetValue();

		action->_fValueTarget=fTargetValue;
		action->initWithDuration(fDuration);
		action->autorelease();
		
		return action;
	}
	
	virtual void startWithTarget(Node *target) override
	{
		ActionInterval::startWithTarget(target);

		ApiCocos2dx::GetValue<T>(target,_fValueStart);
	}
	virtual void update( float time ) override
	{
		if (!ToolFrame::IsEqual(time,1.f))
		{
			TValue fValue = ( _fValueTarget - _fValueStart ) * time + _fValueStart;
			ApiCocos2dx::SetValue<T>(_target,fValue);
			return ;
		}
		
		ApiCocos2dx::SetValue<T>(_target,_fValueTarget);
	}

	virtual TActionSetValue* clone() const override
	{
		return create(_fValueTarget,_duration);
	}

	virtual TActionSetValue* reverse() const override
	{
		return create(_fValueStart,_duration);
	}

protected:
	TActionSetValue(){
		_fValueTarget = _fValueStart= 0.f;
		setTag(COCOS_ACTION_SET_VALUE);
	}

	virtual ~TActionSetValue() {
	}
private:
	CC_DISALLOW_COPY_AND_ASSIGN(TActionSetValue);
	TValue _fValueTarget;
	TValue _fValueStart;
};


#endif //MACRO_LIB_COCOS2D