#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

template<typename T>
class TOOLFRAME_DLL TRefNew
{
public:
	TRefNew(void)
	{
		_p = new T();
	}

	~TRefNew(void)
	{
		_p->release();
	}
public:
	operator T* (void)const//ÒþÊ½Á´½Ó
	{
		return _p;
	}
private:
	T* _p;
};

#endif //MACRO_LIB_COCOS2D
