#pragma once
#include "SqlUserInterface.h"

#ifdef MACRO_LIB_MY_SQL

#include "IMsgStream.h"

NS_TOOL_FRAME_BEGIN

class CUserActionSql
	:public ISqlUserAction
{
	enum {
		RESOLVE_INVAILD=0,
		RESOLVE_INIT,
		RESOLVE_QUERY,
		RESOLVE_MAX,
	};
public:
	static CUserActionSql* Create(IUserClient* pUser);
private:
	virtual bool OnResolve()override;
	virtual bool OnClientRecv(const IMsgStream& msgStream)override;
	virtual bool OnClientDisconnected()override;
public:
	CUserActionSql(void);
	virtual ~CUserActionSql(void);
};

NS_TOOL_FRAME_END

#endif
