#pragma once
#include "Macro.h"
#include "ToolStd.h"

NS_TOOL_FRAME_BEGIN

template<typename TKey,typename TValue,typename Tag>
class MMultiMap
{
	ST_INTANCE(MMultiMap);
public:
	typedef typename	std::multimap<TKey,TValue>					Multimap;
	typedef typename	Multimap::const_iterator					const_iterator;
	typedef typename	Multimap::iterator							iterator;
public:
	typedef typename	std::pair<iterator,iterator>				PairItrItr;
	typedef typename	std::pair<const_iterator,const_iterator>	PairConstItrConstItr;
public:
	iterator begin(){return _vKeyValue.begin();}
	iterator end()	{return _vKeyValue.end();}

	const_iterator begin()const	{return _vKeyValue.begin();}
	const_iterator end()const	{return _vKeyValue.end();}
public:
	Multimap&			GetMap(){return _vKeyValue;}
	const Multimap&		GetMap()const {return _vKeyValue;}
public:
	MMultiMap(void){}
	virtual ~MMultiMap(void){_vKeyValue.clear();}
private:
	Multimap	_vKeyValue;
};

//×¢²á¼üÖµ
#define	MMULTIMAP_REGIST_KEY_VALUE(key,value,mgrName,valueTag)	bool __b##valueTag = ToolFrame::Insert(mgrName::Singleton().GetMap(),key,value)

NS_TOOL_FRAME_END
