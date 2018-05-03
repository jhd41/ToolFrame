#pragma once

#include "Macro.h"

NS_TOOL_FRAME_BEGIN

template<typename T>
class TNew
{
public:
	operator T*(void)const{return _pT;}
	T* operator ->(void)const{return _pT;}
public:
	TNew(void);
	virtual ~TNew(void);
private:
	T*	_pT;
};

template<typename T>
TNew<T>::TNew(void){
	_pT = new T();
}

template<typename T>
TNew<T>::~TNew(void){
	if (_pT){
		delete _pT;
		_pT = nullptr;
	}
}

NS_TOOL_FRAME_END
	