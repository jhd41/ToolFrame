#include "IMySqlProcess.h"

#ifdef MACRO_LIB_MY_SQL

NS_TOOL_FRAME_BEGIN

IMySqlProcess::IMySqlProcess(void)
{
}

IMySqlProcess::~IMySqlProcess(void)
{
}

bool IMySqlProcess::OnSqlExecuted( IMySqlQuery* pSqlQuery,CMySqlResults& record )
{
	return false;
}

//////////////////////////////////////////////////////////////////////////
IMySqlQueryOver::IMySqlQueryOver( void )
{

}

IMySqlQueryOver::~IMySqlQueryOver( void )
{

}

bool IMySqlQueryOver::OnQueryOver( IMySqlQueryPtr pSqlQuery )
{
	return false;
}

NS_TOOL_FRAME_END


#endif
