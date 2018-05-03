#pragma once
#include "Macro.h"

#ifdef MACRO_LIB_BOOST
#include "MacroDefineBoost.h"

#include <boost/regex.hpp>
#include <boost/function.hpp>

namespace boost{
	namespace asio{
		class io_service;
	};
};

class ApiBoost
{
public:
	//时间
	static std::string					GetWorkingDir();
	static void							Sleep(uint64 uTimeMill );
	static UINT							GetThreadTotals();//获取线程数量

	//正则表达式
	static bool							IsRegexMatch(const std::string& sString, const std::string& sRegex);//是否符合正则表达式
	static bool							IsRegexMatch(const std::string& sString, const boost::regex& regex);//是否符合正则表达式
	
	static std::string					RegexReplace(const std::string& sString, const std::string& sRegex,const std::string& sReplaceTo);//将字符串根据正则表达式的规则替换为指定符号
	static std::string					RegexReplace(const std::string& sString, const boost::regex& regex, const std::string& sReplaceTo);//将字符串根据正则表达式的规则替换为指定符号

	static bool							IsEmail(const std::string& sAddress);			//是否为邮箱地址
	static bool							IsTelNumber(const std::string& sTelNumber);		//是否为电话号码
	static bool							IsIdentityNumber(const std::string& sAddress);	//是否为身份证号码

	static std::string					GetLocalIp();
	static std::string					GetHostName();

	static boost::asio::io_service&		GetGlobeIoService();
	static void							SetGlobeServiceWork();

	template<typename TSrc,typename TDes>
	static bool		DynamicCast(boost::shared_ptr<TDes>& ptrDes,const boost::shared_ptr<TSrc>& ptrSrc);

	//全局函数
	template<typename T>
	static typename boost::function<T> Bind(T& t);

	//成员函数
	template<typename R,typename T>
	static typename boost::function<R()> Bind(R(T::*f)(),T* pClass);

	template<typename R,typename T,typename A1>
	static typename boost::function<R(A1)> Bind(R(T::*f)(A1),T* pClass);

	template<typename R,typename T,typename A1,typename A2>
	static typename boost::function<R(A1,A2)> Bind(R(T::*f)(A1,A2),T* pClass);

	template<typename R,typename T,typename A1,typename A2,typename A3>
	static typename boost::function<R(A1,A2,A3)> Bind(R(T::*f)(A1,A2,A3),T* pClass);

	template<typename R,typename T,typename A1,typename A2,typename A3,typename A4>
	static typename boost::function<R(A1,A2,A3,A4)> Bind(R(T::*f)(A1,A2,A3,A4),T* pClass);

	template<typename R,typename T,typename A1,typename A2,typename A3,typename A4,typename A5>
	static typename boost::function<R(A1,A2,A3,A4,A5)> Bind(R(T::*f)(A1,A2,A3,A4,A5),T* pClass);

	//常函数
	template<typename R, typename T>
	static typename boost::function<R()> Bind(R(T::*f)()const, const T* pClass);

	template<typename R, typename T, typename A1>
	static typename boost::function<R(A1)> Bind(R(T::*f)(A1)const, const T* pClass);

	template<typename R, typename T, typename A1, typename A2>
	static typename boost::function<R(A1, A2)> Bind(R(T::*f)(A1, A2)const, const T* pClass);

	template<typename R, typename T, typename A1, typename A2, typename A3>
	static typename boost::function<R(A1, A2, A3)> Bind(R(T::*f)(A1, A2, A3)const, const T* pClass);

	template<typename R, typename T, typename A1, typename A2, typename A3, typename A4>
	static typename boost::function<R(A1, A2, A3, A4)> Bind(R(T::*f)(A1, A2, A3, A4)const, const T* pClass);

	template<typename R, typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
	static typename boost::function<R(A1, A2, A3, A4, A5)> Bind(R(T::*f)(A1, A2, A3, A4, A5)const, const T* pClass);


	//函数调用
	template<typename R,typename T>
	static R CallFunction(boost::function<R()> fn);

	template<typename R,typename T,typename A1>
	static R CallFunction(boost::function<R(A1)> fn);

	template<typename R,typename T,typename A1,typename A2>
	static R CallFunction(boost::function<R(A1,A2)> fn);

	template<typename R,typename T,typename A1,typename A2,typename A3>
	static R CallFunction(boost::function<R(A1,A2,A3)> fn);

	template<typename R,typename T,typename A1,typename A2,typename A3,typename A4>
	static R CallFunction(boost::function<R(A1,A2,A3,A4)> fn);

	template<typename R,typename T,typename A1,typename A2,typename A3,typename A4,typename A5>
	static R CallFunction(boost::function<R(A1,A2,A3,A4,A5)> fn);
};

template<typename TSrc,typename TDes>
bool ApiBoost::DynamicCast( boost::shared_ptr<TDes>& ptrDes,const boost::shared_ptr<TSrc>& ptrSrc)
{
	if (!ptrSrc){
		ptrDes = boost::shared_ptr<TDes>();
		return true;
	}

	ptrDes = boost::dynamic_pointer_cast<TDes>(ptrSrc);
	return true;
}

template<typename R,typename T,typename A1,typename A2,typename A3,typename A4,typename A5>
R ApiBoost::CallFunction( boost::function<R(A1,A2,A3,A4,A5)> fn )
{
	return fn(_1,_2,_3,_4,_5);
}

template<typename R,typename T,typename A1,typename A2,typename A3,typename A4>
R ApiBoost::CallFunction( boost::function<R(A1,A2,A3,A4)> fn )
{
	return fn(_1,_2,_3,_4);
}

template<typename R,typename T,typename A1,typename A2,typename A3>
R ApiBoost::CallFunction( boost::function<R(A1,A2,A3)> fn )
{
	return fn(_1,_2,_3);
}

template<typename R,typename T,typename A1,typename A2>
R ApiBoost::CallFunction( boost::function<R(A1,A2)> fn )
{
	return fn(_1,_2);
}

template<typename R,typename T,typename A1>
R ApiBoost::CallFunction( boost::function<R(A1)> fn )
{
	return fn(_1);
}

template<typename R,typename T>
R ApiBoost::CallFunction( boost::function<R()> fn )
{
	return fn();
}

//全局函数
template<typename T>
typename boost::function<T> ApiBoost::Bind( T& t )
{
	return boost::function<T>(t);
}

//成员函数
template<typename R,typename T>
typename boost::function<R()> ApiBoost::Bind(R(T::*f)(),T* pClass)
{
	return boost::bind(f,pClass);
}

template<typename R,typename T,typename A1>
typename boost::function<R(A1)> ApiBoost::Bind(R(T::*f)(A1),T* pClass)
{
	return boost::bind(f,pClass,_1);
}

template<typename R,typename T,typename A1,typename A2>
typename boost::function<R(A1,A2)> ApiBoost::Bind(R(T::*f)(A1,A2),T* pClass)
{
	return boost::bind(f,pClass,_1,_2);
}

template<typename R,typename T,typename A1,typename A2,typename A3>
typename boost::function<R(A1,A2,A3)> ApiBoost::Bind(R(T::*f)(A1,A2,A3),T* pClass)
{
	return boost::bind(f,pClass,_1,_2,_3);
}

template<typename R,typename T,typename A1,typename A2,typename A3,typename A4>
typename boost::function<R(A1,A2,A3,A4)> ApiBoost::Bind(R(T::*f)(A1,A2,A3,A4),T* pClass)
{
	return boost::bind(f,pClass,_1,_2,_3,_4);
}

template<typename R,typename T,typename A1,typename A2,typename A3,typename A4,typename A5>
typename boost::function<R(A1,A2,A3,A4,A5)> ApiBoost::Bind(R(T::*f)(A1,A2,A3,A4,A5),T* pClass)
{
	return boost::bind(f,pClass,_1,_2,_3,_4,_5);
}

//常函数
template<typename R, typename T>
typename boost::function<R()> ApiBoost::Bind(R(T::*f)()const, const T* pClass)
{
	return boost::bind(f, pClass);
}

template<typename R, typename T, typename A1>
typename boost::function<R(A1)> ApiBoost::Bind(R(T::*f)(A1)const, const T* pClass)
{
	return boost::bind(f, pClass, _1);
}

template<typename R, typename T, typename A1, typename A2>
typename boost::function<R(A1, A2)> ApiBoost::Bind(R(T::*f)(A1, A2)const, const T* pClass)
{
	return boost::bind(f, pClass, _1, _2);
}

template<typename R, typename T, typename A1, typename A2, typename A3>
typename boost::function<R(A1, A2, A3)> ApiBoost::Bind(R(T::*f)(A1, A2, A3)const, const T* pClass)
{
	return boost::bind(f, pClass, _1, _2, _3);
}

template<typename R, typename T, typename A1, typename A2, typename A3, typename A4>
typename boost::function<R(A1, A2, A3, A4)> ApiBoost::Bind(R(T::*f)(A1, A2, A3, A4)const, const T* pClass)
{
	return boost::bind(f, pClass, _1, _2, _3, _4);
}

template<typename R, typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
typename boost::function<R(A1, A2, A3, A4, A5)> ApiBoost::Bind(R(T::*f)(A1, A2, A3, A4, A5)const, const T* pClass)
{
	return boost::bind(f, pClass, _1, _2, _3, _4, _5);
}
#endif
