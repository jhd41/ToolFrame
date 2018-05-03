#include "HMySql.h"

#ifdef MACRO_LIB_MY_SQL

#include "ToolFrame.h"
#include "MLoger.h"

#include "MySqlWorkThread.h"
#include "IMySqlQuery.h"

NS_TOOL_FRAME_BEGIN

bool HMySqlLog::OnInitFaild(CMySqlWorkThread* pThread)
{
	LOG_FATAL("[û������Ĭ�����ݿ�ص��ӿ�...] ThreadID:" << ToolFrame::GetThreadId());
	return true;
}

bool HMySqlLog::OnInitConnectFaild(CMySqlWorkThread* pThread)
{
	LOG_FATAL("[�������ݿ�ʧ��] ThreadID:" << ToolFrame::GetThreadId() << " Name��" << pThread->GetDbClient().GetDataBaseName());
	return true;
}

bool HMySqlLog::OnInited(CMySqlWorkThread* pThread)
{
	LOG_SYSTEM("[���ݿ��߳������ɹ�] ThreadID:" << ToolFrame::GetThreadId() << " Name��" << pThread->GetDbClient().GetDataBaseName());
	return true;
}

bool HMySqlLog::OnReconnectFaild(CMySqlWorkThread* pThread)
{
	LOG_SYSTEM("[���ݿ�����ʧ��] ThreadID:" << ToolFrame::GetThreadId() << " Name��" << pThread->GetDbClient().GetDataBaseName());
	return true;
}

bool HMySqlLog::OnReconnected(CMySqlWorkThread* pThread)
{
	LOG_SYSTEM("[���ݿ������ɹ�] ThreadID:" << ToolFrame::GetThreadId() << " Name��" << pThread->GetDbClient().GetDataBaseName());
	return true;
}

bool HMySqlLog::OnDisconnected(CMySqlWorkThread* pThread)
{
	LOG_SYSTEM("[���ݿ����Ӷ�ʧ,������ʼ����...] ThreadID:" << ToolFrame::GetThreadId() << " Name��" << pThread->GetDbClient().GetDataBaseName());
	return true;
}

bool HMySqlLog::OnExcuteError(CMySqlWorkThread* pThread, IMySqlQueryPtr ptr)
{
	std::stringstream sStream;
	sStream << "[���ݿ�ִ��ʧ��] ThreadID:" << ToolFrame::GetThreadId();
	sStream << " �������: " << ptr->GetErrCode();
	sStream << " DataBaseName: " << ptr->GetDBName();
	sStream << " SQL: " << ptr->GetSql();
	sStream << " ������Ϣ:";

	switch (ptr->GetErrCode())
	{
		case ERR_SQL_TIMEOUT:
		{
			sStream <<" ִ�г�ʱ";
		}
		break;
		case ERR_SQL_EXECUTE_FAILD:
		{
			sStream << " MYSQL�������:" << pThread->GetDbClient().GetLastErrCode();
			if (pThread->GetDbClient().GetLastError())
				sStream << " MYSQL������Ϣ:" << pThread->GetDbClient().GetLastError();
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
	sStream << "[���ݿ�ѹ��ʧ��]";

	if (!ptr)
	{
		sStream << "��ѯΪ��";
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
	sStream << "[����ѹ�����ݿ�]";

	if (!ptr)
	{
		sStream << "��ѯΪ��";
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
	sStream << "[SQL���ִ��ʧ��]";

	if (!ptr)
	{
		sStream << "��ѯΪ��";
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
	sStream << "[���ݿ��ѯ����:]";
	sStream << " �������: "		<< pQuery->GetErrCode();
	sStream << " DataBaseName: "	<< pQuery->GetDBName();
	sStream << " SQL: "				<< pQuery->GetSql();
	sStream << " ������Ϣ:";
	switch (pQuery->GetErrCode())
	{
		case ERR_SQL_DBNAME_EMPTY:
			sStream << " SQL���Ϊ��";
			break;
		case ERR_SQL_DBNAME_NOT_EXIST:
			sStream << " ָ�����ݿⲻ����";
			break;
		case ERR_SQL_DBNAME_SQL_EMPTY:
			sStream << " SQL���Ϊ��";
			break;
		default:
			sStream << " �޷�ʶ��Ĵ������";
	}
	
	std::string sMsg = sStream.str();
	LOG_ERROR_MSG(sMsg);
	return true;
}

NS_TOOL_FRAME_END


#endif
