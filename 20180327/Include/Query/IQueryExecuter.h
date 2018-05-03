#pragma once
#include "Macro.h"

#include "IQuery.h"

NS_TOOL_FRAME_BEGIN
class IQueryClient;
class IQueryExecuter
{
public:
	virtual bool SetQueryClient(IQueryClient* pQueryClient);//设置查询客户端
	virtual bool Init();
	virtual bool Query(IQueryPtr ptr);
public:
	virtual IQueryPtr	OnQueryExecuted(uint uQueryID);//执行完成调用这个
	virtual bool		OnQueryOver(uint uQueryID);
public:
	IQueryExecuter();
	virtual ~IQueryExecuter();
protected:
	IQueryClient* _pQueryClient;
};

NS_TOOL_FRAME_END
