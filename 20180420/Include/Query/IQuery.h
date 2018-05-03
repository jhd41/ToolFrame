#pragma once
#include "Macro.h"
#include "MacroDefineEx.h"

#include "TimeElapse.h"
#include "IPool.h"
#include "HTimeOut.h"
#include "MDebug.h"

NS_TOOL_FRAME_BEGIN

DEFINE_SHARE_PTR(IQuery, IQueryPtr);

typedef std::vector<IQueryPtr> VectorQueryPtr;

class IQuery
	:public boost::enable_shared_from_this<IQuery>
	,public IPoolZero
	,public HTimeOut
{
	DEBUG_CLASS;
public:
	virtual bool OnQueryTimeOut();//超时回调
public:
	CFIELD_UINT(ID);			//系统分配的ID号
	CFIELD_UINT(Type);			//查询类型(用于筛选查询执行器)
	CFIELD_UINT(TypeSub);		//查询类型(用于筛选查询执行器)
	CFIELD_UINT64(QueryElapse);	//查询流逝的时间
	CFIELD_UINT(TimeOut);		//设置查询超时时间(毫秒 0为无限) (若查询时已经超时则不查询)
	CFIELD_STRING(Tag);			//查询标记(内部用,外部不要访问 调试模式下 会在Init()时自动填值)

	CFIELD_INT(ArgInt);			//附带参数
	CFIELD_UINT(ArgUint);		//附带参数
	CFIELD_STRING(ArgString);	//附带参数

	//系统调用 外部不要访问
public:
	virtual bool Init();
	virtual bool QueryBegin();
	virtual bool QueryEnd();
protected:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode);
public:
	IQuery();
	virtual ~IQuery();
private:
	CTimeElapse			_xElapse;		//时间流逝
	CTimeNodePtr		_pTimer;
};

NS_TOOL_FRAME_END
