#include "HSqlClient.h"

#ifdef MACRO_LIB_MY_SQL

#include "MLoger.h"

NS_TOOL_FRAME_BEGIN
bool HSqlClient::OnSqlClientQuery(ISqlQueryPtr ptr)
{
	return false;
}

bool HSqlClient::OnSqlClientExecuted(ISqlQueryPtr ptr, CSqlResults& sqlResults)
{
	return false;
}

bool HSqlClient::OnSqlClientConnected(const std::string& sAddress)
{
	return false;
}

bool HSqlClient::OnSqlClientFaild(const std::string& sAddress)
{
	return false;
}

bool HSqlClient::OnSqlClientDisconnected(const std::string& sAddress)
{
	return false;
}

bool HSqlClient::OnSqlClientErrDBNameEmpty(ISqlQueryPtr ptr)
{
	return false;
}

bool HSqlClient::OnSqlClientErrSqlEmpty(ISqlQueryPtr ptr)
{
	return false;
}

bool HSqlClient::OnSqlClientErrNoConnector(ISqlQueryPtr ptr)
{
	return false;
}

bool HSqlClient::OnSqlClientErrQueryClientFailed(ISqlQueryPtr ptr)
{
	return false;
}

//////////////////////////////////////////////////////////////////////////
bool HSqlClientLog::OnSqlClientConnected(const std::string& sAddress)
{
	LOG_SYSTEM("OnSqlClientConnected:" << sAddress);
	return true;
}

bool HSqlClientLog::OnSqlClientFaild(const std::string& sAddress)
{
	LOG_SYSTEM("OnSqlClientFaild:" << sAddress);
	return true;
}

bool HSqlClientLog::OnSqlClientDisconnected(const std::string& sAddress)
{
	LOG_SYSTEM("OnSqlClientDisconnected:" << sAddress);
	return true;
}

bool HSqlClientLog::OnSqlClientErrDBNameEmpty(ISqlQueryPtr ptr)
{
	LOG_ERROR_MSG("OnSqlClientErrDBNameEmpty");
	return true;
}

bool HSqlClientLog::OnSqlClientErrSqlEmpty(ISqlQueryPtr ptr)
{
	LOG_ERROR_MSG("OnSqlClientErrSqlEmpty");
	return false;
}

bool HSqlClientLog::OnSqlClientErrNoConnector(ISqlQueryPtr ptr)
{
	LOG_ERROR_MSG("OnSqlClientErrNoConnector");
	return false;
}

bool HSqlClientLog::OnSqlClientErrQueryClientFailed(ISqlQueryPtr ptr)
{
	LOG_ERROR_MSG("OnSqlClientErrQueryClientFailed");
	return false;
}

NS_TOOL_FRAME_END

#endif
