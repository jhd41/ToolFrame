#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"
#include "IFunction.h"

NS_TOOL_FRAME_BEGIN

//析构时会 按照添加的顺序 调用 注册的函数。

class MDestoryMonitor
{
	ST_INTANCE(MDestoryMonitor);
public:
	typedef CSharePtr<IFunction>		IFunctionPtr;
	typedef std::vector<IFunctionPtr>	VectorFunction;
public:
	bool AddFunction(void(*fn)());
	template<typename T>
	bool AddFunction(void(T::*fn)(),T* t);

	bool AddFunction(bool(*fn)());
	template<typename T>
	bool AddFunction(bool(T::*fn)(),T* t);

	bool CallFunction()const;
	bool Clear();
private:
	template<typename T>
	bool DoAddFunction(T fn);

	template<typename T,typename TFn,typename TClass>
	bool DoAddFunction(TFn fn,TClass* t);
public:
	MDestoryMonitor(void);
	virtual ~MDestoryMonitor(void);
private:
	VectorFunction	_vFunction;
};

template<typename T,typename TFn,typename TClass>
bool MDestoryMonitor::DoAddFunction(TFn fn,TClass* t )
{
	CSharePtr< TFunction<T> > ptr(new TFunction<T>());
	ptr->_fn = boost::bind(fn,t);
	_vFunction.push_back(ptr);
	return true;
}

template<typename T>
bool MDestoryMonitor::DoAddFunction( T fn )
{
	CSharePtr< TFunction<T> >  ptr(new TFunction<T>());
	ptr->_fn = boost::bind(fn);
	_vFunction.push_back(ptr);
	return true;
}

template<typename T>
bool MDestoryMonitor::AddFunction( void(T::*fn)(),T* t )
{
	return DoAddFunction<void()>(fn,t);
}

template<typename T>
bool ToolFrame::MDestoryMonitor::AddFunction( bool(T::*fn)(),T* t )
{
	return DoAddFunction<bool()>(fn,t);
}

NS_TOOL_FRAME_END
