#include "MySqlWorkThread.h"

#ifdef MACRO_LIB_MY_SQL

#include "ToolFrame.h"
#include "IMySqlQuery.h"
#include "MLoger.h"
#include "MMySql.h"
#include "IMySqlProcess.h"
#include "TimeOut.h"

NS_TOOL_FRAME_BEGIN

CMySqlWorkThread::CMySqlWorkThread(void)
{
	_hHandler = nullptr;

	_uTimeWaitConnect	= 3000;//ÿ3�� ��������һ��
	_uTimeExcute			= 100;	
}

CMySqlWorkThread::~CMySqlWorkThread(void)
{
}

bool CMySqlWorkThread::QuerySql()
{
	//��ȡһ����ѯ����
	IMySqlQueryPtr ptr = MMySql::Singleton().Pop(_dbClient.GetDataBaseName());
	if (!ptr)return false;

	//��������
	ASSERT_LOG_ERROR(_dbRecord.Clear());

	//��ӡSQL���
	if (_hHandler)
		_hHandler->OnExecuteSql(this,ptr);

	//��ʼִ��
	do 
	{
		//�жϳ�ʱ
		if (ptr->IsTimeOut())
		{
			//���ϴ�����
			_dbRecord.SetError();
			ptr->SetErrCode(ERR_SQL_TIMEOUT);

			//����ص�
			if (_hHandler)
				_hHandler->OnExcuteError(this, ptr);
			break;
		}

		//��ʼ��ѯ
		DEBUG_FUN_TAG("RealExecute "<<ptr->GetTag());

		//ִ�в�ѯ����
		if (!_dbClient.Execute(ptr->GetSql(), _dbRecord)) {

			//���ϴ�����
			DEBUG_FUN_INVAILD();
			_dbRecord.SetError();
			ptr->SetErrCode(ERR_SQL_EXECUTE_FAILD);

			//����Ƕ�������
			if (!_dbClient.IsConnected())
			{
				if (_hHandler)
					_hHandler->OnDisconnected(this);

				if (_hHandler)
					_hHandler->OnRePushSql(this, ptr);

				MMySql::Singleton().PushFront(ptr);
				return false;
			}

			//����ص�
			if (_hHandler)
				_hHandler->OnExcuteError(this, ptr);

			break;
		}
		ptr->SetErrCode(ERR_SQL_SUCCEED);
	} while (false);

	//�ص�
	if (!ptr->OnSqlExecuted(_dbRecord))
		_hHandler->OnSqlExecutedErr(this,ptr);

	ASSERT_LOG_ERROR(ptr->OnHandleOver(ptr));
	MMySql::Singleton().OnQueryOver(ptr);
	return true;
}

bool CMySqlWorkThread::RunOnceThread()
{
	if (!_dbClient.IsConnected())
	{
		if (!_dbClient.Ping())
		{
			if (_hHandler)
				_hHandler->OnReconnectFaild(this);

			ToolFrame::Sleep(_uTimeWaitConnect);
			return true;
		}
		
		if (_hHandler)
			_hHandler->OnReconnected(this);
	}

	//����ִ�ж��г��� �� ѭ�� ���� ��ʱ
	size_t uCount = MMySql::Singleton().GetQueueSize(_dbClient.GetDataBaseName());
	CTimeOut timeExcute(_uTimeExcute);
	for (size_t uIndex=0;uIndex<uCount;++uIndex)
	{
		if (timeExcute.IsTimeOut())
			break;
		if (!QuerySql())
			break;
	}
	return true;
}

bool CMySqlWorkThread::InitThread()
{
	IMySqlProcess* pProcess = MMySql::Singleton().GetProcess();
	if (!pProcess)
	{
		if (_hHandler)
			_hHandler->OnInitFaild(this);
		return false;
	}
	if (!_dbClient.ConnectDB())
	{
		if (_hHandler)
			_hHandler->OnInitConnectFaild(this);
		return false;
	}
	if (_hHandler)
		_hHandler->OnInited(this);
	return true;
}

bool CMySqlWorkThread::SetDataBase( const std::string& sHostName,int nPort,const std::string& sDBName,const std::string& sUserName,const std::string& sPwd )
{
	return _dbClient.SetDataBase(sHostName,nPort,sDBName,sUserName,sPwd);
}

bool CMySqlWorkThread::SetHandler( HMySql* hHandler )
{
	_hHandler = hHandler;
	return true;
}

const CMySqlClient& CMySqlWorkThread::GetDbClient() const
{
	return _dbClient;
}

uint CMySqlWorkThread::GetTimeWaitConnect() const
{
	return _uTimeWaitConnect;
}

uint CMySqlWorkThread::GetTimeExcute() const
{
	return _uTimeExcute;
}

bool CMySqlWorkThread::SetTimeWaitConnect( uint uTime )
{
	_uTimeWaitConnect = uTime;
	return true;
}

bool CMySqlWorkThread::SetTimeExcute( uint uTime )
{
	_uTimeExcute = uTime;
	return true;
}

NS_TOOL_FRAME_END

#endif

