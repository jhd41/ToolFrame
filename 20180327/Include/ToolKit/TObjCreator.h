#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"

//类对象创建器 自动管理申请和释放

template<typename T>
class TObjCreator
{
	typedef typename std::list<T*> VectorObj;
public:
	//创建
	T*		CreateObj();
	template<typename TNew>
	TNew*	CreateObj();
	
	template<typename Arg1>
	T*		CreateObj(const Arg1& tArg1);

	template<typename TNew,typename Arg1>
	TNew*	CreateObj(const Arg1& tArg1);
	template<typename TNew,typename Arg1,typename Arg2>
	TNew*	CreateObj(const Arg1& tArg1,const Arg2& tArg2);
	template<typename TNew,typename Arg1,typename Arg2,typename Arg3>
	TNew*	CreateObj(const Arg1& tArg1,const Arg2& tArg2,const Arg3& tArg3);
	template<typename TNew,typename Arg1,typename Arg2,typename Arg3,typename Arg4>
	TNew*	CreateObj(const Arg1& tArg1,const Arg2& tArg2,const Arg3& tArg3,const Arg4& tArg4);
	template<typename TNew,typename Arg1,typename Arg2,typename Arg3,typename Arg4,typename Arg5>
	TNew*	CreateObj(const Arg1& tArg1,const Arg2& tArg2,const Arg3& tArg3,const Arg4& tArg4,const Arg5& tArg5);

	//释放
	bool	DeleteObj(const T* pObj);
	bool	DeleteAll();

	//移除(不释放 可能会内存泄露 外部需要管理好)
	bool	EraseObj(const T* pObj);
	bool	EraseAll();

	bool	IsEmpty()const;
	size_t	GetSize()const;

	//对 itr 的支持
	SUPPORT_FOREACH(VectorObj,_vObj)
public:
	TObjCreator(void);
	virtual ~TObjCreator(void);
private:
	VectorObj _vObj;
	mutable CMutexReadWrite _mutex;
};

template<typename T>
size_t TObjCreator<T>::GetSize() const
{
	CLockRead lock(_mutex);
	return _vObj.size();
}

template<typename T>
bool TObjCreator<T>::DeleteAll()
{
	CLockWrite lock(_mutex);
	
	if (!_vObj.empty())
	{
		typename VectorObj::iterator itr;
		foreach(itr,_vObj){
			delete *itr;
		}
		_vObj.clear();
	}
	return true;
}

template<typename T>
bool TObjCreator<T>::IsEmpty() const
{
	CLockRead lock(_mutex);
	return _vObj.empty();
}

template<typename T>
TObjCreator<T>::TObjCreator(void)
{

}

template<typename T>
TObjCreator<T>::~TObjCreator(void)
{
	DeleteAll();
}

template<typename T>
bool TObjCreator<T>::DeleteObj(const T* pObj )
{
	CLockWrite lock(_mutex);
	
	typename VectorObj::iterator itr;
	foreach(itr,_vObj){
		if (pObj == *itr)
		{
			delete *itr;
			_vObj.erase(itr);
			return true;
		}
	}
	return false;
}

template<typename T>
T* TObjCreator<T>::CreateObj()
{
	return CreateObj<T>();
}

template<typename T>
template<typename TNew>
TNew* TObjCreator<T>::CreateObj()
{
	CLockWrite lock(_mutex);

	TNew* pObj = new TNew();
	if (!pObj)return nullptr;

	_vObj.push_back(pObj);

	return pObj;
}

template<typename T>
template<typename Arg1>
T*	TObjCreator<T>::CreateObj(const Arg1& tArg1){
	return CreateObj<T,Arg1>(tArg1);
}

template<typename T>
template<typename TNew,typename Arg1,typename Arg2,typename Arg3,typename Arg4,typename Arg5>
TNew* TObjCreator<T>::CreateObj( const Arg1& tArg1,const Arg2& tArg2,const Arg3& tArg3,const Arg4& tArg4,const Arg5& tArg5 )
{
	CLockWrite lock(_mutex);

	TNew* pObj = new TNew(tArg1,tArg2,tArg3,tArg4,tArg5);
	if (!pObj)return nullptr;

	_vObj.push_back(pObj);

	return pObj;
}

template<typename T>
template<typename TNew,typename Arg1,typename Arg2,typename Arg3,typename Arg4>
TNew* TObjCreator<T>::CreateObj( const Arg1& tArg1,const Arg2& tArg2,const Arg3& tArg3,const Arg4& tArg4 )
{
	CLockWrite lock(_mutex);

	TNew* pObj = new TNew(tArg1,tArg2,tArg3,tArg4);
	if (!pObj)return nullptr;

	_vObj.push_back(pObj);

	return pObj;
}

template<typename T>
template<typename TNew,typename Arg1,typename Arg2,typename Arg3>
TNew* TObjCreator<T>::CreateObj( const Arg1& tArg1,const Arg2& tArg2,const Arg3& tArg3 )
{
	CLockWrite lock(_mutex);

	TNew* pObj = new TNew(tArg1,tArg2,tArg3);
	if (!pObj)return nullptr;

	_vObj.push_back(pObj);

	return pObj;
}

template<typename T>
template<typename TNew,typename Arg1,typename Arg2>
TNew* TObjCreator<T>::CreateObj( const Arg1& tArg1,const Arg2& tArg2 )
{
	CLockWrite lock(_mutex);

	TNew* pObj = new TNew(tArg1,tArg2);
	if (!pObj)return nullptr;

	_vObj.push_back(pObj);

	return pObj;
}

template<typename T>
template<typename TNew,typename Arg1>
TNew* TObjCreator<T>::CreateObj( const Arg1& tArg1 )
{
	CLockWrite lock(_mutex);

	TNew* pObj = new TNew(tArg1);
	if (!pObj)return nullptr;

	_vObj.push_back(pObj);

	return pObj;
}

template<typename T>
bool TObjCreator<T>::EraseAll()
{
	CLockWrite lock(_mutex);
	_vObj.clear();
	return true;
}

template<typename T>
bool TObjCreator<T>::EraseObj(const T* pObj)
{
	CLockWrite lock(_mutex);

	typename VectorObj::iterator itr;
	foreach(itr, _vObj) {
		if (pObj == *itr)
		{
			_vObj.erase(itr);
			return true;
		}
	}
	return false;
}
