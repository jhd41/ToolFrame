#pragma once
#include "Macro.h"
#include "MLoger.h"
#include "ToolStd.h"

using namespace ToolFrame;

class CTestToValue
{
public:
	bool	Test();
public:
	class A{
	public:
		A(){}
		A(const A& a){

		}
		A& operator = (const A& a){
			ASSERT_LOG_ERROR(ToolFrame::IsSelf(*this,a));
			return *this;
		}
	};
public:
	template<typename T>
	bool TestStringToValue(const std::string& sSrc,const T& tValue,const T& tDefault);//×Ö·û´®µ½Öµ
public:
	CTestToValue(void);
	virtual ~CTestToValue(void);
};

template<typename T>
bool CTestToValue::TestStringToValue( const std::string& sSrc,const T& tValue,const T& tDefault )
{
	T t = tDefault;
	ASSERT_LOG_ERROR(ToolFrame::ToValue(sSrc,t));
	ASSERT_LOG_ERROR(ToolFrame::IsEqual(t,tValue));
	return true;
}
