#pragma once
#include "Macro.h"

#ifdef MACRO_LIB_MY_SQL

#include "ISqlQuery.h"

NS_TOOL_FRAME_BEGIN

//////////////////////////////////////////////////////////////////////////
//Sql客户端处理器
class HSqlClient {
public:
	virtual bool OnSqlClientQuery(ISqlQueryPtr ptr);							//开始查询
	virtual bool OnSqlClientExecuted(ISqlQueryPtr ptr, CSqlResults& sqlResults);//查询回调
public:
	virtual bool OnSqlClientConnected(const std::string& sAddress);
	virtual bool OnSqlClientFaild(const std::string& sAddress);
	virtual bool OnSqlClientDisconnected(const std::string& sAddress);
public:
	virtual bool OnSqlClientErrDBNameEmpty(ISqlQueryPtr ptr);
	virtual bool OnSqlClientErrSqlEmpty(ISqlQueryPtr ptr);
	virtual bool OnSqlClientErrNoConnector(ISqlQueryPtr ptr);//没有有效的连接器

	virtual bool OnSqlClientErrQueryClientFailed(ISqlQueryPtr ptr);//压入查询队列失败
public:
	HSqlClient() {}
	virtual ~HSqlClient() {}
};
//////////////////////////////////////////////////////////////////////////
//Sql客户端处理器(写日志)
class HSqlClientLog
	:public HSqlClient
{
public:
	virtual bool OnSqlClientConnected(const std::string& sAddress)override;
	virtual bool OnSqlClientFaild(const std::string& sAddress)override;
	virtual bool OnSqlClientDisconnected(const std::string& sAddress)override;
public:
	virtual bool OnSqlClientErrDBNameEmpty(ISqlQueryPtr ptr)override;
	virtual bool OnSqlClientErrSqlEmpty(ISqlQueryPtr ptr)override;
	virtual bool OnSqlClientErrNoConnector(ISqlQueryPtr ptr)override;//没有有效的连接器

	virtual bool OnSqlClientErrQueryClientFailed(ISqlQueryPtr ptr)override;//压入查询队列失败
};

NS_TOOL_FRAME_END

#endif
