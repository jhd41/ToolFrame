#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN

class IFunction
{
public:
	virtual bool CallFunction(){return false;}
public:
	IFunction(void){}
	virtual ~IFunction(void){}
};

template<typename T>
class TFunction
	:public IFunction
{
public:
	virtual bool CallFunction(){
		_fn();
		return true;
	}
public:
	TFunction(){}
	TFunction(boost::function<T> fn){_fn = fn;}
	virtual ~TFunction(void){}
public:
	boost::function<T> _fn;
};

NS_TOOL_FRAME_END
