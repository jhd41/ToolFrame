#pragma once
#include "Macro.h"
#include "ToolStd.h"

NS_TOOL_FRAME_BEGIN

template<typename TValue,typename Tag>
class MVector
{
	ST_INTANCE(MVector);
public:
	typedef typename	std::vector<TValue>		Vector;
	typedef typename	Vector::const_iterator	const_iterator;
	typedef typename	Vector::iterator		iterator;
public:
	iterator begin(){return _vValue.begin();}
	iterator end()	{return _vValue.end();}

	const_iterator begin()const	{return _vValue.begin();}
	const_iterator end()const	{return _vValue.end();}
public:
	Vector&			GetVector(){return _vValue;}
	const Vector&	GetVector()const {return _vValue;}
public:
	MVector(void){}
	virtual ~MVector(void){_vValue.clear();}
private:
	Vector	_vValue;
};

//×¢²á¼üÖµ
#define	MVECTOR_REGIST_VALUE(value,mgrName,valueTag)	bool __b##valueTag = ToolFrame::Insert(mgrName::Singleton().GetVector(),value)

NS_TOOL_FRAME_END
