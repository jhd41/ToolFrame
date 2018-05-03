#pragma once
#include "MacroMySql.h"

#ifdef MACRO_LIB_MY_SQL

#include "MySqlResults.h"

NS_TOOL_FRAME_BEGIN
class IMySqlProcess
{
public:
	virtual bool OnSqlExecuted(IMySqlQuery* pSqlQuery,CMySqlResults& record);
public:
	IMySqlProcess(void);
	virtual ~IMySqlProcess(void);
};

//////////////////////////////////////////////////////////////////////////
class IMySqlQueryOver{
public:
	virtual bool OnQueryOver(IMySqlQueryPtr pSqlQuery);
public:
	IMySqlQueryOver(void);
	virtual ~IMySqlQueryOver(void);
};
NS_TOOL_FRAME_END


#endif
