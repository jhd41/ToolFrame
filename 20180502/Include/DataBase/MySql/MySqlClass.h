#pragma once

#include "Macro.h"

#ifdef MACRO_LIB_MY_SQL

#include "mysql.h"
#include "errmsg.h"

NS_TOOL_FRAME_BEGIN

class CMySql
{
public:
	operator const MYSQL*(void)const;
	operator MYSQL*(void);
public:
	CMySql(void);
	virtual ~CMySql(void);
private:
	MYSQL _xMySql;
};

NS_TOOL_FRAME_END

#endif