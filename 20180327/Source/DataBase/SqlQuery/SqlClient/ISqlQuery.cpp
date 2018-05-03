#include "ISqlQuery.h"

#include "ToolFrame.h"

#ifdef MACRO_LIB_MY_SQL

NS_TOOL_FRAME_BEGIN

ISqlQuery::ISqlQuery()
{
	_nRecord = 0;
}

ISqlQuery::~ISqlQuery()
{

}

bool ISqlQuery::AddSql(const std::string& sSql)
{
	if (sSql.empty())return false;

	_sSqlStream << sSql;

	if (!ToolFrame::IsEndWith(sSql, ";"))//末尾;号 对结果的影响很大
		_sSqlStream << ";";
	return true;
}

bool ISqlQuery::SetSql(const std::string& sSql, int nRecord /*= -1*/)
{
	if (sSql.empty())return false;

	_nRecord = nRecord;
	_sSql = sSql;
	return true;
}

const std::string& ISqlQuery::GetSql() const
{
	return _sSql;
}

bool ISqlQuery::IsSqlEmpty() const
{
	return _sSql.empty();
}

bool ISqlQuery::IsDBNameEmpty() const
{
	return GetDBName().empty();
}

bool ISqlQuery::MakeSqlStream()
{
	if (!_sSql.empty())return false;
	_sSql = _sSqlStream.str();
	return !_sSql.empty();
}

bool ISqlQuery::OnSqlExecuted(CSqlResults& xResults)
{
	return false;
}

NS_TOOL_FRAME_END

#endif
