#include "HMySql.h"

#ifdef MACRO_LIB_MY_SQL

#include "ToolFrame.h"
#include "MLoger.h"

#include "MySqlWorkThread.h"
#include "IMySqlQuery.h"

NS_TOOL_FRAME_BEGIN

bool HMySqlLog::OnInitFaild(CMySqlWorkThread* pThread)
{
	LOG_FATAL("[没有设置默认数据库回调接口...] ThreadID:" << ToolFrame::GetThreadId());
	return true;
}

bool HMySqlLog::OnInitConnectFaild(CMySqlWorkThread* pThread)
{
	LOG_FATAL("[连接数据库失败] ThreadID:" << ToolFrame::GetThreadId() << " Name：" << pThread->GetDbClient().GetDataBaseName());
	return true;
}

bool HMySqlLog::OnInited(CMySqlWorkThread* pThread)
{
	LOG_SYSTEM("[数据库线程启动成功] ThreadID:" << ToolFrame::GetThreadId() << " Name：" << pThread->GetDbClient().GetDataBaseName());
	return true;
}

bool HMySqlLog::OnReconnectFaild(CMySqlWorkThread* pThread)
{
	LOG_SYSTEM("[数据库重连失败] ThreadID:" << ToolFrame::GetThreadId() << " Name：" << pThread->GetDbClient().GetDataBaseName());
	return true;
}

bool HMySqlLog::OnReconnected(CMySqlWorkThread* pThread)
{
	LOG_SYSTEM("[数据库重连成功] ThreadID:" << ToolFrame::GetThreadId() << " Name：" << pThread->GetDbClient().GetDataBaseName());
	return true;
}

bool HMySqlLog::OnDisconnected(CMySqlWorkThread* pThread)
{
	LOG_SYSTEM("[数据库连接丢失,即将开始重连...] ThreadID:" << ToolFrame::GetThreadId() << " Name：" << pThread->GetDbClient().GetDataBaseName());
	return true;
}

bool HMySqlLog::OnExcuteError(CMySqlWorkThread* pThread, IMySqlQueryPtr ptr)
{
	std::stringstream sStream;
	sStream << "[数据库执行失败] ThreadID:" << ToolFrame::GetThreadId();
	sStream << " 错误代号: " << ptr->GetErrCode();
	sStream << " DataBaseName: " << ptr->GetDBName();
	sStream << " SQL: " << ptr->GetSql();
	sStream << " 错误信息:";

	switch (ptr->GetErrCode())
	{
		case ERR_SQL_TIMEOUT:
		{
			sStream <<" 执行超时";
		}
		break;
		case ERR_SQL_EXECUTE_FAILD:
		{
			sStream << " MYSQL错误代号:" << pThread->GetDbClient().GetLastErrCode();
			if (pThread->GetDbClient().GetLastError())
				sStream << " MYSQL错误信息:" << pThread->GetDbClient().GetLastError();
		}
		break;
	}

	std::string sMsg = sStream.str();
	LOG_ERROR_MSG(sMsg);
	return true;
}

bool HMySqlLog::OnExecuteSql(CMySqlWorkThread* pThread, IMySqlQueryPtr ptr)
{
	LOG_DEBUG("Execute:" << ptr->GetDBName() << " SQL: " << ptr->GetSql());
	return true;
}

bool HMySqlLog::OnPushSqlFaild(IMySqlQueryPtr ptr)
{
	std::stringstream sStream;
	sStream << "[数据库压入失败]";

	if (!ptr)
	{
		sStream << "查询为空";
	}
	else {
		sStream << " DataBaseName: " << ptr->GetDBName();
		sStream << " SQL: " << ptr->GetSql();
	}

	std::string sMsg = sStream.str();
	LOG_ERROR_MSG(sMsg);
	return true;
}

bool HMySqlLog::OnRePushSql(CMySqlWorkThread* pThread, IMySqlQueryPtr ptr)
{
	std::stringstream sStream;
	sStream << "[重新压入数据库]";

	if (!ptr)
	{
		sStream << "查询为空";
	}
	else {
		sStream << " DataBaseName: " << ptr->GetDBName();
		sStream << " SQL: " << ptr->GetSql();
	}

	std::string sMsg = sStream.str();
	LOG_SYSTEM(sMsg);
	return true;
}

bool HMySqlLog::OnSqlExecutedErr(CMySqlWorkThread* pThread, IMySqlQueryPtr ptr)
{
	std::stringstream sStream;
	sStream << "[SQL语句执行失败]";

	if (!ptr)
	{
		sStream << "查询为空";
	}
	else {
		sStream << " DataBaseName: " << ptr->GetDBName();
		sStream << " SQL: " << ptr->GetSql();
	}

	std::string sMsg = sStream.str();
	LOG_ERROR_MSG(sMsg);
	return true;
}

bool HMySqlLog::OnSqlPrepareErr(IMySqlQueryPtr pQuery)
{
	std::stringstream sStream;
	sStream << "[数据库查询错误:]";
	sStream << " 错误代号: "		<< pQuery->GetErrCode();
	sStream << " DataBaseName: "	<< pQuery->GetDBName();
	sStream << " SQL: "				<< pQuery->GetSql();
	sStream << " 错误信息:";
	switch (pQuery->GetErrCode())
	{
		case ERR_SQL_DBNAME_EMPTY:
			sStream << " SQL语句为空";
			break;
		case ERR_SQL_DBNAME_NOT_EXIST:
			sStream << " 指定数据库不存在";
			break;
		case ERR_SQL_DBNAME_SQL_EMPTY:
			sStream << " SQL语句为空";
			break;
		default:
			sStream << " 无法识别的错误代号";
	}
	
	std::string sMsg = sStream.str();
	LOG_ERROR_MSG(sMsg);
	return true;
}

NS_TOOL_FRAME_END


#endif
