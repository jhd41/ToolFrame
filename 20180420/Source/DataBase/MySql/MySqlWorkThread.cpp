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

	_uTimeWaitConnect	= 3000;//每3秒 尝试连接一次
	_uTimeExcute			= 100;	
}

CMySqlWorkThread::~CMySqlWorkThread(void)
{
}

bool CMySqlWorkThread::QuerySql()
{
	//获取一个查询请求
	IMySqlQueryPtr ptr = MMySql::Singleton().Pop(_dbClient.GetDataBaseName());
	if (!ptr)return false;

	//清理结果集
	ASSERT_LOG_ERROR(_dbRecord.Clear());

	//打印SQL语句
	if (_hHandler)
		_hHandler->OnExecuteSql(this,ptr);

	//开始执行
	do 
	{
		//判断超时
		if (ptr->IsTimeOut())
		{
			//打上错误标记
			_dbRecord.SetError();
			ptr->SetErrCode(ERR_SQL_TIMEOUT);

			//错误回调
			if (_hHandler)
				_hHandler->OnExcuteError(this, ptr);
			break;
		}

		//开始查询
		DEBUG_FUN_TAG("RealExecute "<<ptr->GetTag());

		//执行查询请求
		if (!_dbClient.Execute(ptr->GetSql(), _dbRecord)) {

			//打上错误标记
			DEBUG_FUN_INVAILD();
			_dbRecord.SetError();
			ptr->SetErrCode(ERR_SQL_EXECUTE_FAILD);

			//如果是断网错误
			if (!_dbClient.IsConnected())
			{
				if (_hHandler)
					_hHandler->OnDisconnected(this);

				if (_hHandler)
					_hHandler->OnRePushSql(this, ptr);

				MMySql::Singleton().PushFront(ptr);
				return false;
			}

			//错误回调
			if (_hHandler)
				_hHandler->OnExcuteError(this, ptr);

			break;
		}
		ptr->SetErrCode(ERR_SQL_SUCCEED);
	} while (false);

	//回调
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

	//至多执行队列长度 次 循环 或者 超时
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

