#pragma once
#include "Macro.h"

#include <functional>

//��������Ҫ֧��C++11�¼���ĺ���
namespace ToolFrame
{
	//���� ���� ���ݺ����ķ���ֵ �����Ǹ����з���
	template<typename TFun, typename T>
	T* FindPtrMaxByFn(const std::vector<T*>& v, TFun fn);
	template<typename TFun, typename T>
	T* FindMaxByFn(const std::vector<T>& v, TFun fn);

	//���� ���� ���ݺ����ķ���ֵ ��С���Ǹ����з���
	template<typename TFun, typename T>
	T* FindPtrMinByFn(const std::vector<T*>& v, TFun fn);
	template<typename TFun, typename T>
	T* FindMinByFn(const std::vector<T>& v, TFun fn);

	//ȫ�ֺ���
	template<typename T>
	typename std::function<T> Bind(T& t);

	//��Ա����
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

	//������
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

//ȫ�ֺ���
template<typename T>
typename std::function<T> ToolFrame::Bind( T& t )
{
	return std::function<T>(t);
}

//��Ա����
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

//������
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