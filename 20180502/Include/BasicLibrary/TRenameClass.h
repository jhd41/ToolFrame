#pragma once
#include "Macro.h"

//重命名类
//用于将一个类型 重新命名为 另一种类型。使得能够进行重载
template<typename TClass,int Tag>
class TRenameClass
	:public TClass
{
public:
	using TClass::TClass;
	using TClass::operator =;

	TRenameClass() {}
	TRenameClass(const TClass& t)
		:TClass(t)
	{

	}
	TRenameClass(const TRenameClass& t)
		:TClass(t)
	{

	}

	TRenameClass& operator = (const TRenameClass& t){
		TClass::operator = (t);
		return *this;
	}

public:
	operator TClass&() {
		return *this;
	}
	operator const TClass&() const {
		return *this;
	}
};
