#include "MySqlQuerySet.h"

#ifdef MACRO_LIB_MY_SQL

NS_TOOL_FRAME_BEGIN

CMySqlQuerySet::CMySqlQuerySet(void)
{
	_hHandler = nullptr;
}

CMySqlQuerySet::~CMySqlQuerySet(void)
{
}

IMySqlQueryPtr CMySqlQuerySet::AddQuery( IMySqlQueryPtr pSqlQuery )
{
	if (pSqlQuery->GetHandlerOver())return IMySqlQueryPtr();

	pSqlQuery->SetHandlerOver(this);

	if (!_vQuery.Insert(pSqlQuery))return IMySqlQueryPtr();
	return pSqlQuery;
}

IMySqlQueryPtr CMySqlQuerySet::RemoveQuery( IMySqlQueryPtr pSqlQuery )
{
	if (!_vQuery.EraseByKey(pSqlQuery))return IMySqlQueryPtr();

	return pSqlQuery;
}

bool CMySqlQuerySet::OnQueryOver( IMySqlQueryPtr pSqlQuery )
{
	if (!_vQuery.EraseByKey(pSqlQuery))return false;

	if (_vQuery.Empty())
	{
		if (_hHandler)
			_hHandler->OnQuerySetOver(this);
	}

	return true;
}

bool CMySqlQuerySet::SetHandler( HMySqlQuerySet* hHandler )
{
	_hHandler = hHandler;
	return true;
}

NS_TOOL_FRAME_END

#endif

