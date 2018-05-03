#pragma once
#include "Macro.h"

#include <functional>

//本工具主要支持C++11新加入的函数
namespace ToolFrame
{
	//容器 查找 根据函数的返回值 最大的那个进行返回
	template<typename TFun, typename T>
	T* FindPtrMaxByFn(const std::vector<T*>& v, TFun fn);
	template<typename TFun, typename T>
	T* FindMaxByFn(const std::vector<T>& v, TFun fn);

	//容器 查找 根据函数的返回值 最小的那个进行返回
	template<typename TFun, typename T>
	T* FindPtrMinByFn(const std::vector<T*>& v, TFun fn);
	template<typename TFun, typename T>
	T* FindMinByFn(const std::vector<T>& v, TFun fn);

	//全局函数
	template<typename T>
	typename std::function<T> Bind(T& t);

	//成员函数
	template<typename R,typename T>
	typename std::function<R()> Bind(R(T::*f)(),T* pClass);

	template<typename R,typename T,typename A1>
	typename std::function<R(A1)> Bind(R(T::*f)(A1),T* pClass);

	template<typename R,typename T,typename A1,typename A2>
	typename std::function<R(A1,A2)> Bind(R(T::*f)(A1,A2),T* pClass);

	template<typename R,typename T,typename A1,typename A2,typename A3>
	typename std::function<R(A1,A2,A3)> Bind(R(T::*f)(A1,A2,A3),T* pClass);

	template<typename R,typename T,typename A1,typename A2,typename A3,typename A4>
	typename std::function<R(A1,A2,A3,A4)> Bind(R(T::*f)(A1,A2,A3,A4),T* pClass);

	template<typename R,typename T,typename A1,typename A2,typename A3,typename A4,typename A5>
	typename std::function<R(A1,A2,A3,A4,A5)> Bind(R(T::*f)(A1,A2,A3,A4,A5),T* pClass);

	//常函数
	template<typename R, typename T>
	typename std::function<R()> Bind(R(T::*f)()const, const T* pClass);

	template<typename R, typename T, typename A1>
	typename std::function<R(A1)> Bind(R(T::*f)(A1)const, const T* pClass);

	template<typename R, typename T, typename A1, typename A2>
	typename std::function<R(A1, A2)> Bind(R(T::*f)(A1, A2)const, const T* pClass);

	template<typename R, typename T, typename A1, typename A2, typename A3>
	typename std::function<R(A1, A2, A3)> Bind(R(T::*f)(A1, A2, A3)const, const T* pClass);

	template<typename R, typename T, typename A1, typename A2, typename A3, typename A4>
	typename std::function<R(A1, A2, A3, A4)> Bind(R(T::*f)(A1, A2, A3, A4)const, const T* pClass);

	template<typename R, typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
	typename std::function<R(A1, A2, A3, A4, A5)> Bind(R(T::*f)(A1, A2, A3, A4, A5)const, const T* pClass);
};

//全局函数
template<typename T>
typename std::function<T> ToolFrame::Bind( T& t )
{
	return std::function<T>(t);
}

//成员函数
template<typename R,typename T>
typename std::function<R()> ToolFrame::Bind(R(T::*f)(),T* pClass)
{
	return std::bind(f,pClass);
}

template<typename R,typename T,typename A1>
typename std::function<R(A1)> ToolFrame::Bind(R(T::*f)(A1),T* pClass)
{
	return std::bind(f,pClass,std::placeholders::_1);
}

template<typename R,typename T,typename A1,typename A2>
typename std::function<R(A1,A2)> ToolFrame::Bind(R(T::*f)(A1,A2),T* pClass)
{
	return std::bind(f,pClass,std::placeholders::_1,std::placeholders::_2);
}

template<typename R,typename T,typename A1,typename A2,typename A3>
typename std::function<R(A1,A2,A3)> ToolFrame::Bind(R(T::*f)(A1,A2,A3),T* pClass)
{
	return std::bind(f,pClass,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
}

template<typename R,typename T,typename A1,typename A2,typename A3,typename A4>
typename std::function<R(A1,A2,A3,A4)> ToolFrame::Bind(R(T::*f)(A1,A2,A3,A4),T* pClass)
{
	return std::bind(f,pClass,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
}

template<typename R,typename T,typename A1,typename A2,typename A3,typename A4,typename A5>
typename std::function<R(A1,A2,A3,A4,A5)> ToolFrame::Bind(R(T::*f)(A1,A2,A3,A4,A5),T* pClass)
{
	return std::bind(f,pClass,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
}

//常函数
template<typename R, typename T>
typename std::function<R()> ToolFrame::Bind(R(T::*f)()const, const T* pClass)
{
	return std::bind(f, pClass);
}

template<typename R, typename T, typename A1>
typename std::function<R(A1)> ToolFrame::Bind(R(T::*f)(A1)const, const T* pClass)
{
	return std::bind(f, pClass, std::placeholders::_1);
}

template<typename R, typename T, typename A1, typename A2>
typename std::function<R(A1, A2)> ToolFrame::Bind(R(T::*f)(A1, A2)const, const T* pClass)
{
	return std::bind(f, pClass, std::placeholders::_1, std::placeholders::_2);
}

template<typename R, typename T, typename A1, typename A2, typename A3>
typename std::function<R(A1, A2, A3)> ToolFrame::Bind(R(T::*f)(A1, A2, A3)const, const T* pClass)
{
	return std::bind(f, pClass, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

template<typename R, typename T, typename A1, typename A2, typename A3, typename A4>
typename std::function<R(A1, A2, A3, A4)> ToolFrame::Bind(R(T::*f)(A1, A2, A3, A4)const, const T* pClass)
{
	return std::bind(f, pClass, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
}

template<typename R, typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
typename std::function<R(A1, A2, A3, A4, A5)> ToolFrame::Bind(R(T::*f)(A1, A2, A3, A4, A5)const, const T* pClass)
{
	return std::bind(f, pClass, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5);
}

template<typename TFun, typename T>
T* ToolFrame::FindPtrMaxByFn(const std::vector<T*>& v, TFun fn)
{
	if (v.empty())return nullptr;

	typename std::vector<T*>::const_iterator itr = v.begin();

	T* pMax = *itr;
	auto uScoreMax = fn(pMax);

	++itr;
	for (; itr != v.end(); ++itr)
	{
		T* pCur = *itr;

		auto uScore = fn(pCur);
		if (uScore > uScoreMax)
		{
			uScoreMax = uScore;
			pMax = pCur;
		}
	}

	return pMax;
}

template<typename TFun, typename T>
T* ToolFrame::FindMaxByFn(const std::vector<T>& v, TFun fn)
{
	if (v.empty())return nullptr;

	typename std::vector<T>::const_iterator itr = v.begin();

	const T* pMax = &*itr;
	auto uScoreMax = fn(pMax);

	++itr;
	for (; itr != v.end(); ++itr)
	{
		const T* pCur = &*itr;

		auto uScore = fn(pCur);
		if (uScore > uScoreMax)
		{
			uScoreMax = uScore;
			pMax = pCur;
		}
	}

	return (T*)pMax;
}

template<typename TFun, typename T>
T* ToolFrame::FindPtrMinByFn(const std::vector<T*>& v, TFun fn)
{
	if (v.empty())return nullptr;

	typename std::vector<T*>::const_iterator itr = v.begin();

	T* pMin = *itr;
	auto uScoreMin = fn(pMin);

	++itr;
	for (; itr != v.end(); ++itr)
	{
		T* pCur = *itr;

		auto uScore = fn(pCur);
		if (uScore < uScoreMin)
		{
			uScoreMin = uScore;
			pMin = pCur;
		}
	}

	return pMin;
}

template<typename TFun, typename T>
T* ToolFrame::FindMinByFn(const std::vector<T>& v, TFun fn)
{
	if (v.empty())return nullptr;

	typename std::vector<T>::const_iterator itr = v.begin();

	const T* pMin = &*itr;
	auto uScoreMin = fn(pMin);

	++itr;
	for (; itr != v.end(); ++itr)
	{
		const T* pCur = &*itr;

		auto uScore = fn(pCur);
		if (uScore > uScoreMin)
		{
			uScoreMin = uScore;
			pMin = pCur;
		}
	}

	return (T*)pMin;
}