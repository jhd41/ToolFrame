#pragma once
#include "Macro.h"
#include "TThreadSaftyList.h"

NS_TOOL_FRAME_BEGIN

struct IFunctionArg
{
public:
	CFIELD_INT(UserInt);
	CFIELD_STRING(UserString);
public:
	virtual bool Call() { return true; }
public:
	IFunctionArg() {
		SetUserInt(0);
	}
	virtual ~IFunctionArg() {
	}
};

template<typename TFn>
struct CFunctionArg
	:public IFunctionArg
{
	TFn		_fn;
	CFunctionArg(const TFn& fn)
		:_fn(fn)
	{
	}

	virtual ~CFunctionArg() {
	}

	CFunctionArg& operator = (const CFunctionArg& xOther) {
		_fn = xOther._fn;
	}

public:
	virtual bool Call() override{
		return _fn();
	}
};

template<typename TFn, typename TArg>
struct CFunctionArg1
	:public IFunctionArg
{
	TFn		_fn;
	TArg	_tArg;
	CFunctionArg1(const TFn& fn, const TArg& tArg)
		:_fn(fn), _tArg(tArg)
	{
	}

	virtual ~CFunctionArg1() {
	}

	CFunctionArg1& operator = (const CFunctionArg1& xOther) {
		_fn = xOther._fn;
		_tArg = xOther._tArg;
	}

public:
	virtual bool Call() override {
		return _fn(_tArg);
	}
};

template<typename TFn, typename TArg1, typename TArg2>
struct CFunctionArg2
	:public IFunctionArg
{
	TFn	_fn;
	TArg1	_tArg1;
	TArg2	_tArg2;
	CFunctionArg2(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2) 
		:_fn(fn), _tArg1(tArg1), _tArg2(tArg2)
	{
	}

	virtual ~CFunctionArg2() {
	}

	CFunctionArg2& operator = (const CFunctionArg2& xOther) {
		_fn = xOther._fn;
		_tArg1 = xOther._tArg1;
		_tArg2 = xOther._tArg2;
	}

public:
	virtual bool Call() override {
		return _fn(_tArg1, _tArg2);
	}
};

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
struct CFunctionArg3
	:public IFunctionArg
{
	TFn		_fn;
	TArg1	_tArg1;
	TArg2	_tArg2;
	TArg3	_tArg3;
	CFunctionArg3(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3)
		:_fn(fn), _tArg1(tArg1), _tArg2(tArg2), _tArg3(tArg3)
	{
	}

	virtual ~CFunctionArg3() {
	}

	CFunctionArg3& operator = (const CFunctionArg3& xOther) {
		_fn = xOther._fn;
		_tArg1 = xOther._tArg1;
		_tArg2 = xOther._tArg2;
		_tArg3 = xOther._tArg3;
	}

public:
	virtual bool Call() override {
		return _fn(_tArg1, _tArg2, _tArg3);
	}
};

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
struct CFunctionArg4
	:public IFunctionArg
{
	TFn		_fn;
	TArg1	_tArg1;
	TArg2	_tArg2;
	TArg3	_tArg3;
	TArg4	_tArg4;
	CFunctionArg4(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3, const TArg4& tArg4)
		:_fn(fn), _tArg1(tArg1), _tArg2(tArg2), _tArg3(tArg3), _tArg4(tArg4)
	{
	}

	virtual ~CFunctionArg4() {
	}

	CFunctionArg4& operator = (const CFunctionArg4& xOther) {
		_fn = xOther._fn;
		_tArg1 = xOther._tArg1;
		_tArg2 = xOther._tArg2;
		_tArg3 = xOther._tArg3;
		_tArg4 = xOther._tArg4;
	}

public:
	virtual bool Call() override {
		return _fn(_tArg1, _tArg2, _tArg3, _tArg4);
	}
};

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
struct CFunctionArg5
	:public IFunctionArg
{
	TFn		_fn;
	TArg1	_tArg1;
	TArg2	_tArg2;
	TArg3	_tArg3;
	TArg4	_tArg4;
	TArg5	_tArg5;
	CFunctionArg5(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3, const TArg4& tArg4, const TArg5& tArg5)
		:_fn(fn), _tArg1(tArg1), _tArg2(tArg2), _tArg3(tArg3), _tArg4(tArg4), _tArg5(tArg5)
	{
	}

	virtual ~CFunctionArg5() {
	}

	CFunctionArg5& operator = (const CFunctionArg5& xOther) {
		_fn = xOther._fn;
		_tArg1 = xOther._tArg1;
		_tArg2 = xOther._tArg2;
		_tArg3 = xOther._tArg3;
		_tArg4 = xOther._tArg4;
		_tArg5 = xOther._tArg5;
	}

public:
	virtual bool Call() override {
		return _fn(_tArg1, _tArg2, _tArg3, _tArg4, _tArg5);
	}
};

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>
struct CFunctionArg6
	:public IFunctionArg
{
	TFn		_fn;
	TArg1	_tArg1;
	TArg2	_tArg2;
	TArg3	_tArg3;
	TArg4	_tArg4;
	TArg5	_tArg5;
	TArg6	_tArg6;
	CFunctionArg6(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3, const TArg4& tArg4, const TArg5& tArg5, const TArg6& tArg6)
		:_fn(fn), _tArg1(tArg1), _tArg2(tArg2), _tArg3(tArg3), _tArg4(tArg4), _tArg5(tArg5), _tArg6(tArg6)
	{
	}

	virtual ~CFunctionArg6() {
	}

	CFunctionArg6& operator = (const CFunctionArg6& xOther) {
		_fn = xOther._fn;
		_tArg1 = xOther._tArg1;
		_tArg2 = xOther._tArg2;
		_tArg3 = xOther._tArg3;
		_tArg4 = xOther._tArg4;
		_tArg5 = xOther._tArg5;
		_tArg6 = xOther._tArg6;
	}

public:
	virtual bool Call() override {
		return _fn(_tArg1, _tArg2, _tArg3, _tArg4, _tArg5, _tArg6);
	}
};

template<typename TFn>
IFunctionArg* CreateFunctionArg(const TFn& fn) {
	return new CFunctionArg<TFn>(fn);
}

template<typename TFn, typename TArg>
IFunctionArg* CreateFunctionArg(const TFn& fn, const TArg& tArg) {
	return new CFunctionArg1<TFn, TArg>(fn, tArg);
}

template<typename TFn, typename TArg1, typename TArg2>
IFunctionArg* CreateFunctionArg(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2) {
	return new CFunctionArg2<TFn, TArg1, TArg2>(fn, tArg1, tArg2);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
IFunctionArg* CreateFunctionArg(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3) {
	return new CFunctionArg3<TFn, TArg1, TArg2, TArg3>(fn, tArg1, tArg2, tArg3);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
IFunctionArg* CreateFunctionArg(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3, const TArg4& tArg4) {
	return new CFunctionArg4<TFn, TArg1, TArg2, TArg3, TArg4>(fn, tArg1, tArg2, tArg3, tArg4);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
IFunctionArg* CreateFunctionArg(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3, const TArg4& tArg4, const TArg5& tArg5) {
	return new CFunctionArg5<TFn, TArg1, TArg2, TArg3, TArg4, TArg5>(fn, tArg1, tArg2, tArg3, tArg4, tArg5);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>
IFunctionArg* CreateFunctionArg(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3, const TArg4& tArg4, const TArg5& tArg5, const TArg6& tArg6) {
	return new CFunctionArg6<TFn, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6>(fn, tArg1, tArg2, tArg3, tArg4, tArg5, tArg6);
}

bool DestoryFunctionArg(IFunctionArg* pFunctionArg);

typedef CSharePtr<IFunctionArg>					IFunctionArgPtr;
typedef TThreadSaftyListValue<IFunctionArgPtr>	QueueFunctionArgPtr;

NS_TOOL_FRAME_END
