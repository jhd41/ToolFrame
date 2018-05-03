#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"

//类对象创建器 自动管理申请和释放

template<typename TKey,typename TValue>
class TObjCreatorMap
{
	typedef typename std::map<TKey,TValue*> MapObj;
public:
	//创建
	template<typename TNew>
	TNew*	CreateObj(const TKey& tKey);
	template<typename TNew,typename Arg1>
	TNew*	CreateObj(const TKey& tKey,const Arg1& tArg1);
	template<typename TNew,typename Arg1,typename Arg2>
	TNew*	CreateObj(const TKey& tKey,const Arg1& tArg1,const Arg2& tArg2);
	template<typename TNew,typename Arg1,typename Arg2,typename Arg3>
	TNew*	CreateObj(const TKey& tKey,const Arg1& tArg1,const Arg2& tArg2,const Arg3& tArg3);
	template<typename TNew,typename Arg1,typename Arg2,typename Arg3,typename Arg4>
	TNew*	CreateObj(const TKey& tKey,const Arg1& tArg1,const Arg2& tArg2,const Arg3& tArg3,const Arg4& tArg4);
	template<typename TNew,typename Arg1,typename Arg2,typename Arg3,typename Arg4,typename Arg5>
	TNew*	CreateObj(const TKey& tKey,const Arg1& tArg1,const Arg2& tArg2,const Arg3& tArg3,const Arg4& tArg4,const Arg5& tArg5);

	//释放Obj
	bool	DeleteObj(const TValue* pObj);
	bool	DeleteKey(const TKey& tKey);
	bool	DeleteAll();

	//移除Obj(不释放)
	bool	EraseObj(const TValue* pObj);
	bool	EraseKey(const TKey& tKey);
	bool	EraseAll();

	bool	IsEmpty()const;
	uint	GetSize()const;

	TValue* FindObj(const TKey& tKey)const;
	
	//对 itr 的支持
	SUPPORT_FOREACH(MapObj,_vObj)
public:
	TObjCreatorMap(void);
	virtual ~TObjCreatorMap(void);
private:
	MapObj _vObj;
	mutable CMutexReadWrite _mutex;
};

template<typename TKey,typename TValue>
TValue* TObjCreatorMap<TKey, TValue>::FindObj( const TKey& tKey ) const
{
	CLockRead lock(_mutex);
	typename MapObj::const_iterator itr = _vObj.find(tKey);
	if (itr == _vObj.end())return nullptr;

	return itr->second;
}

template<typename TKey,typename TValue>
template<typename TNew,typename Arg1,typename Arg2,typename Arg3,typename Arg4,typename Arg5>
TNew* TObjCreatorMap<TKey,TValue>::CreateObj( const TKey& tKey,const Arg1& tArg1,const Arg2& tArg2,const Arg3& tArg3,const Arg4& tArg4,const Arg5& tArg5 )
{
	CLockWrite lock(_mutex);

	if (_vObj.find(tKey) != _vObj.end())return nullptr;

	TNew* pObj = new TNew(tArg1,tArg2,tArg3,tArg4,tArg5);
	if (!pObj)return nullptr;

	_vObj.insert(std::make_pair(tKey,pObj));

	return pObj;
}

template<typename TKey,typename TValue>
template<typename TNew,typename Arg1,typename Arg2,typename Arg3,typename Arg4>
TNew* TObjCreatorMap<TKey,TValue>::CreateObj( const TKey& tKey,const Arg1& tArg1,const Arg2& tArg2,const Arg3& tArg3,const Arg4& tArg4 )
{
	CLockWrite lock(_mutex);

	if (_vObj.find(tKey) != _vObj.end())return nullptr;

	TNew* pObj = new TNew(tArg1,tArg2,tArg3,tArg4);
	if (!pObj)return nullptr;

	_vObj.insert(std::make_pair(tKey,pObj));

	return pObj;
}

template<typename TKey,typename TValue>
template<typename TNew,typename Arg1,typename Arg2,typename Arg3>
TNew* TObjCreatorMap<TKey,TValue>::CreateObj( const TKey& tKey,const Arg1& tArg1,const Arg2& tArg2,const Arg3& tArg3 )
{
	CLockWrite lock(_mutex);

	if (_vObj.find(tKey) != _vObj.end())return nullptr;

	TNew* pObj = new TNew(tArg1,tArg2,tArg3);
	if (!pObj)return nullptr;

	_vObj.insert(std::make_pair(tKey,pObj));

	return pObj;
}

template<typename TKey,typename TValue>
template<typename TNew,typename Arg1,typename Arg2>
TNew* TObjCreatorMap<TKey,TValue>::CreateObj( const TKey& tKey,const Arg1& tArg1,const Arg2& tArg2 )
{
	CLockWrite lock(_mutex);

	if (_vObj.find(tKey) != _vObj.end())return nullptr;

	TNew* pObj = new TNew(tArg1,tArg2);
	if (!pObj)return nullptr;

	_vObj.insert(std::make_pair(tKey,pObj));

	return pObj;
}

template<typename TKey,typename TValue>
template<typename TNew,typename Arg1>
TNew* TObjCreatorMap<TKey,TValue>::CreateObj( const TKey& tKey,const Arg1& tArg1 )
{
	CLockWrite lock(_mutex);

	if (_vObj.find(tKey) != _vObj.end())return nullptr;

	TNew* pObj = new TNew(tArg1);
	if (!pObj)return nullptr;

	_vObj.insert(std::make_pair(tKey,pObj));

	return pObj;
}

template<typename TKey,typename TValue>
template<typename TNew>
TNew* TObjCreatorMap<TKey,TValue>::CreateObj( const TKey& tKey )
{
	CLockWrite lock(_mutex);

	if (_vObj.find(tKey) != _vObj.end())return nullptr;

	TNew* pObj = new TNew();
	if (!pObj)return nullptr;

	_vObj.insert(std::make_pair(tKey,pObj));

	return pObj;
}

template<typename TKey,typename TValue>
uint TObjCreatorMap<TKey, TValue>::GetSize() const
{
	CLockRead lock(_mutex);
	return _vObj.size();
}

template<typename TKey,typename TValue>
bool TObjCreatorMap<TKey, TValue>::IsEmpty() const
{
	CLockRead lock(_mutex);
	return _vObj.empty();
}

template<typename TKey,typename TValue>
bool TObjCreatorMap<TKey, TValue>::DeleteAll()
{
	CLockWrite lock(_mutex);

	if (!_vObj.empty())
	{
		typename MapObj::iterator itr;
		foreach(itr,_vObj){
			delete itr->second;
		}
		_vObj.clear();
	}
	return true;
}

template<typename TKey,typename TValue>
bool TObjCreatorMap<TKey, TValue>::DeleteKey( const TKey& tKey )
{
	CLockWrite lock(_mutex);

	typename MapObj::iterator itr = _vObj.find(tKey);
	if (itr == _vObj.end())return false;

	delete itr->second;
	_vObj.erase(itr);
	return true;
}

template<typename TKey,typename TValue>
bool TObjCreatorMap<TKey, TValue>::DeleteObj( const TValue* pObj )
{
	CLockWrite lock(_mutex);

	typename MapObj::iterator itr;
	foreach(itr,_vObj){
		if (pObj == itr->second)
		{
			delete *itr;
			_vObj.erase(itr);
			return true;
		}
	}
	return false;
}
template<typename TKey, typename TValue>
bool TObjCreatorMap<TKey, TValue>::EraseAll()
{
	CLockWrite lock(_mutex);

	_vObj.clear();
	return true;
}

template<typename TKey, typename TValue>
bool TObjCreatorMap<TKey, TValue>::EraseKey(const TKey& tKey)
{
	CLockWrite lock(_mutex);

	typename MapObj::iterator itr = _vObj.find(tKey);
	if (itr == _vObj.end())return false;
	_vObj.erase(itr);
	return true;
}

template<typename TKey, typename TValue>
bool TObjCreatorMap<TKey, TValue>::EraseObj(const TValue* pObj)
{
	CLockWrite lock(_mutex);

	typename MapObj::iterator itr;
	foreach(itr, _vObj) {
		if (pObj == itr->second)
		{
			_vObj.erase(itr);
			return true;
		}
	}
	return false;
}

template<typename TKey,typename TValue>
TObjCreatorMap<TKey,TValue>::TObjCreator(void)
{

}

template<typename TKey,typename TValue>
TObjCreatorMap<TKey,TValue>::~TObjCreator(void)
{
	DeleteAll();
}