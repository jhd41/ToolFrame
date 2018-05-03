#include "MySqlClass.h"

#ifdef MACRO_LIB_MY_SQL

#include "ApiMySql.h"

NS_TOOL_FRAME_BEGIN

CMySql::CMySql(void)
{
	CLockScoped lock(ApiMySql::GetMutex());
	mysql_init(&_xMySql);
}

CMySql::~CMySql(void)
{
	mysql_close(&_xMySql);
}

CMySql::operator const MYSQL*( void ) const
{
	return &_xMySql;
}

CMySql::operator MYSQL*( void )
{
	return &_xMySql;
}

NS_TOOL_FRAME_END

#endif