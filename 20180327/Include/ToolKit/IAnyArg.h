#pragma once
#include "Macro.h"
#include "TThreadSaftyList.h"

NS_TOOL_FRAME_BEGIN

struct IAnyArg
{
public:
	virtual bool Call() { return true; }
public:
	IAnyArg() {
	}
	virtual ~IAnyArg() {
	}
};

template<typename TFn>
struct CAnyArg
	:public IAnyArg
{
	TFn		_fn;
	CAnyArg(const TFn& fn)
		:_fn(fn)
	{
	}

	virtual ~CAnyArg() {
	}

	CAnyArg& operator = (const CAnyArg& xOther) {
		_fn = xOther._fn;
	}

public:
	virtual bool Call() override{
		return _fn();
	}
};

template<typename TFn, typename TArg>
struct CAnyArg1
	:public IAnyArg
{
	TFn		_fn;
	TArg	_tArg;
	CAnyArg1(const TFn& fn, const TArg& tArg)
		:_fn(fn), _tArg(tArg)
	{
	}

	virtual ~CAnyArg1() {
	}

	CAnyArg1& operator = (const CAnyArg1& xOther) {
		_fn = xOther._fn;
		_tArg = xOther._tArg;
	}

public:
	virtual bool Call() override {
		return _fn(_tArg);
	}
};

template<typename TFn, typename TArg1, typename TArg2>
struct CAnyArg2
	:public IAnyArg
{
	TFn	_fn;
	TArg1	_tArg1;
	TArg2	_tArg2;
	CAnyArg2(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2) 
		:_fn(fn), _tArg1(tArg1), _tArg2(tArg2)
	{
	}

	virtual ~CAnyArg2() {
	}

	CAnyArg2& operator = (const CAnyArg2& xOther) {
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
struct CAnyArg3
	:public IAnyArg
{
	TFn		_fn;
	TArg1	_tArg1;
	TArg2	_tArg2;
	TArg3	_tArg3;
	CAnyArg3(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3)
		:_fn(fn), _tArg1(tArg1), _tArg2(tArg2), _tArg3(tArg3)
	{
	}

	virtual ~CAnyArg3() {
	}

	CAnyArg3& operator = (const CAnyArg3& xOther) {
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
struct CAnyArg4
	:public IAnyArg
{
	TFn		_fn;
	TArg1	_tArg1;
	TArg2	_tArg2;
	TArg3	_tArg3;
	TArg4	_tArg4;
	CAnyArg4(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3, const TArg4& tArg4)
		:_fn(fn), _tArg1(tArg1), _tArg2(tArg2), _tArg3(tArg3), _tArg4(tArg4)
	{
	}

	virtual ~CAnyArg4() {
	}

	CAnyArg4& operator = (const CAnyArg4& xOther) {
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
struct CAnyArg5
	:public IAnyArg
{
	TFn		_fn;
	TArg1	_tArg1;
	TArg2	_tArg2;
	TArg3	_tArg3;
	TArg4	_tArg4;
	TArg5	_tArg5;
	CAnyArg5(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3, const TArg4& tArg4, const TArg5& tArg5)
		:_fn(fn), _tArg1(tArg1), _tArg2(tArg2), _tArg3(tArg3), _tArg4(tArg4), _tArg5(tArg5)
	{
	}

	virtual ~CAnyArg5() {
	}

	CAnyArg5& operator = (const CAnyArg5& xOther) {
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


template<typename TFn>
IAnyArg* CreateAnyArg(const TFn& fn) {
	return new CAnyArg<TFn>(fn);
}

template<typename TFn, typename TArg>
IAnyArg* CreateAnyArg(const TFn& fn, const TArg& tArg) {
	return new CAnyArg1<TFn, TArg>(fn, tArg);
}

template<typename TFn, typename TArg1, typename TArg2>
IAnyArg* CreateAnyArg(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2) {
	return new CAnyArg2<TFn, TArg1, TArg2>(fn, tArg1, tArg2);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3>
IAnyArg* CreateAnyArg(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3) {
	return new CAnyArg3<TFn, TArg1, TArg2, TArg3>(fn, tArg1, tArg2, tArg3);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
IAnyArg* CreateAnyArg(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3, const TArg4& tArg4) {
	return new CAnyArg4<TFn, TArg1, TArg2, TArg3, TArg4>(fn, tArg1, tArg2, tArg3, tArg4);
}

template<typename TFn, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
IAnyArg* CreateAnyArg(const TFn& fn, const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3, const TArg4& tArg4, const TArg5& tArg5) {
	return new CAnyArg5<TFn, TArg1, TArg2, TArg3, TArg4, TArg5>(fn, tArg1, tArg2, tArg3, tArg4, tArg5);
}

bool DestoryAnyArg(IAnyArg* pAnyArg);

typedef CSharePtr<IAnyArg>					IAnyArgPtr;
typedef TThreadSaftyListValue<IAnyArgPtr>	QueueAnyArgPtr;

NS_TOOL_FRAME_END
