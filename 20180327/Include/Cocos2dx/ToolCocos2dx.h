#pragma once
#include "Macro.h"

#ifdef MACRO_LIB_COCOS2D
#include "MacroCocos2dx.h"

namespace ToolFrame{

	//ToValue	
	template<typename T>
	bool ToValue(const std::vector<T>& tSrc,CCArray* pArray);
	template<typename T>
	bool ToValue(const std::list<T>& tSrc,CCArray* pArray);
	template<typename T>
	bool ToValue(const std::set<T>& tSrc,CCArray* pArray);
	template<typename T>
	bool ToValue(const std::multiset<T>& tSrc,CCArray* pArray);
	template<typename Key,typename Value>
	bool ToValue(const std::map<Key,Value>& tSrc,CCArray* pArray,bool bKey = false);
	template<typename Key,typename Value>
	bool ToValue(const std::multimap<Key,Value>& tSrc,CCArray* pArray,bool bKey = false);

	template<typename T>
	bool ToValue(CCArray* pArray, std::vector<T>& tDes);
	template<typename T>
	bool ToValue(CCArray* pArray, std::list<T>& tDes);
	template<typename T>
	bool ToValue(CCArray* pArray, std::set<T>& tDes);
	template<typename T>
	bool ToValue(CCArray* pArray, std::multiset<T>& tDes);
};

template<typename T>
bool ToolFrame::ToValue( CCArray* pArray, std::multiset<T>& tDes )
{
	if (!pArray)return false;
	if ( 0 == pArray->count() )return true;
	for (uint uIndex=0; uIndex<pArray->count(); ++uIndex)
	{
		tDes.insert((T)pArray->objectAtIndex(uIndex));
	}
	return true;
}

template<typename T>
bool ToolFrame::ToValue( const std::multiset<T>& tSrc,CCArray* pArray )
{
	if (!pArray)return false;
	if (tSrc.empty())return true;
	typename std::multiset<T>::const_iterator itr;
	foreach(itr,tSrc){
		pArray->addObject(*itr);
	}
	return true;
}

template<typename Key,typename Value>
bool ToolFrame::ToValue( const std::multimap<Key,Value>& tSrc,CCArray* pArray,bool bKey /*= false*/ )
{
	if (!pArray)return false;
	if (tSrc.empty())return true;
	typename std::multimap<Key,Value>::const_iterator itr;
	foreach(itr,tSrc){
		pArray->addObject(bKey ? itr->first:itr->second);
	}
	return true;
}

template<typename Key,typename Value>
bool ToolFrame::ToValue( const std::map<Key,Value>& tSrc,CCArray* pArray,bool bKey /*= false*/ )
{
	if (!pArray)return false;
	if (tSrc.empty())return true;
	typename std::map<Key,Value>::const_iterator itr;
	foreach(itr,tSrc){
		pArray->addObject(bKey ? itr->first:itr->second);
	}
	return true;
}

template<typename T>
bool ToolFrame::ToValue( CCArray* pArray, std::set<T>& tDes )
{
	if (!pArray)return false;
	if ( 0 == pArray->count() )return true;
	if (tDes.empty()) return false;
	for (uint uIndex=0; uIndex<pArray->count(); ++uIndex)
	{
		tDes.insert((T)pArray->objectAtIndex(uIndex));
	}
	return tDes.size() == pArray->count();
}

template<typename T>
bool ToolFrame::ToValue( CCArray* pArray, std::list<T>& tDes )
{
	if (!pArray)return false;
	if ( 0 == pArray->count() )return true;
	for (uint uIndex=0; uIndex<pArray->count(); ++uIndex)
	{
		tDes.push_back((T)pArray->objectAtIndex(uIndex));
	}
	return true;
}

template<typename T>
bool ToolFrame::ToValue( CCArray* pArray, std::vector<T>& tDes )
{
	if (!pArray)return false;
	if ( 0 == pArray->count() )return true;
	for (uint uIndex=0; uIndex<pArray->count(); ++uIndex)
	{
		tDes.push_back((T)pArray->objectAtIndex(uIndex));
	}
	return true;
}

template<typename T>
bool ToolFrame::ToValue( const std::set<T>& tSrc,CCArray* pArray )
{
	if (!pArray)return false;
	if (tSrc.empty())return true;
	typename std::set<T>::const_iterator itr;
	foreach(itr,tSrc){
		pArray->addObject(*itr);
	}
	return true;
}

template<typename T>
bool ToolFrame::ToValue( const std::list<T>& tSrc,CCArray* pArray )
{
	if (!pArray)return false;
	if (tSrc.empty())return true;
	typename std::list<T>::const_iterator itr;
	foreach(itr,tSrc){
		pArray->addObject(*itr);
	}
	return true;
}

template<typename T>
bool ToolFrame::ToValue( const std::vector<T>& tSrc,CCArray* pArray )
{
	if (!pArray)return false;
	if (tSrc.empty())return true;
	typename std::vector<T>::const_iterator itr;
	foreach(itr,tSrc){
		pArray->addObject(*itr);
	}
	return true;
}

#endif //MACRO_LIB_COCOS2D