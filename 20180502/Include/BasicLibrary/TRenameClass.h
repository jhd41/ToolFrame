#pragma once
#include "Macro.h"

//��������
//���ڽ�һ������ ��������Ϊ ��һ�����͡�ʹ���ܹ���������
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
