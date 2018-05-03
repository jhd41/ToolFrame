#pragma once
#include "Macro.h"

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS

#include <unordered_map>

namespace ToolFrame{
	//普通插入函数
	template<typename T,typename K>
	bool			Insert(std::unordered_map<T,K>& vMap,T& tKey,K& kValue);

	//万能获取值
	template<typename TKey,typename TValue>
	TValue&			GetValueByKey(std::unordered_map<TKey,TValue>& vMap,const TKey& tKey,TValue& tDefault );
	template<typename TKey,typename TValue>
	const TValue&	GetValueByKey(std::unordered_map<TKey,TValue>& vMap,const TKey& tKey,const TValue& tDefault );

};

NS_TOOL_FRAME_BEGIN

template<typename T,typename K>
bool ToolFrame::Insert(std::unordered_map<T,K>& vMap,T& tKey,K& kValue )
{
	size_t uSize = vMap.size();
	vMap.insert(std::make_pair(tKey,kValue));

	return vMap.size() == uSize + 1;
}

template<typename TKey,typename TValue>
const TValue& ToolFrame::GetValueByKey(std::unordered_map<TKey,TValue>& vMap,const TKey& tKey,const TValue& tDefault )
{
	typename std::hash_map<TKey,TValue>::iterator itr = vMap.find(tKey);
	if (itr == vMap.end())
		return tDefault;

	return itr->second;
}

template<typename TKey,typename TValue>
TValue& ToolFrame::GetValueByKey(std::unordered_map<TKey,TValue>& vMap,const TKey& tKey,TValue& tDefault )
{
	typename std::hash_map<TKey,TValue>::iterator itr = vMap.find(tKey);
	if (itr == vMap.end())
		return tDefault;

	return itr->second;
}

NS_TOOL_FRAME_END

#endif