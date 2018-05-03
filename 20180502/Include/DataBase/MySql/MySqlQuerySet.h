#pragma once
#include "IMySqlQuery.h"
#include "IMySqlProcess.h"
#include "TThreadSaftySet.h"

#ifdef MACRO_LIB_MY_SQL

NS_TOOL_FRAME_BEGIN

class CMySqlQuerySet;
class HMySqlQuerySet
{
public:
	virtual bool OnQuerySetOver(CMySqlQuerySet*){return false;}
public:
	HMySqlQuerySet(){}
	virtual ~HMySqlQuerySet(){}
};

class CMySqlQuerySet
	:public IMySqlQueryOver
{
	typedef TThreadSaftySet<IMySqlQueryPtr> SetSqlQueryPtr;
public:
	virtual bool			SetHandler(HMySqlQuerySet* hHandler);
	virtual IMySqlQueryPtr	AddQuery(IMySqlQueryPtr pSqlQuery);
	virtual IMySqlQueryPtr	RemoveQuery(IMySqlQueryPtr pSqlQuery);
private:
	virtual bool OnQueryOver(IMySqlQueryPtr pSqlQuery);
public:
	CMySqlQuerySet(void);
	virtual ~CMySqlQuerySet(void);
private:
	SetSqlQueryPtr	_vQuery;
	HMySqlQuerySet*		_hHandler;
};

NS_TOOL_FRAME_END

#endif
