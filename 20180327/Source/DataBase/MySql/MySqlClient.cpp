#include "MySqlClient.h"

#ifdef MACRO_LIB_MY_SQL

#include "MLoger.h"
#include "ApiMySql.h"

#pragma comment(lib, "libmysql.lib")

NS_TOOL_FRAME_BEGIN

CMySqlClient::CMySqlClient(void)
{
	_bConnected = false;
}

CMySqlClient::~CMySqlClient(void)
{
	Close();
}

bool CMySqlClient::SetDataBase( const std::string& sHostName,int nPort,const std::string& sDBName,const std::string& sUserName,const std::string& sPwd )
{
	//保存连接信息。
	_sHostName = sHostName;
	_nPort = nPort;
	_sDBName = sDBName;
	_sUserName = sUserName;
	_sPwd = sPwd;
	return true;
}

bool CMySqlClient::ConnectDB( const std::string& sHostName,int nPort,const std::string& sDBName,const std::string& sUserName,const std::string& sPwd )
{
	if (!SetDataBase(sHostName,nPort,sDBName,sUserName,sPwd))return false;
	return ConnectDB();
}

bool CMySqlClient::ConnectDB( void )
{
	if(_bConnected)Close();
	
	CLockScoped lock(ApiMySql::GetMutex());
	my_bool b= true;
	try
	{
		mysql_init(&_xMySQL);
		mysql_options(&_xMySQL,MYSQL_OPT_RECONNECT,&b);
		if (!mysql_real_connect(&_xMySQL,_sHostName.c_str(),_sUserName.c_str(),_sPwd.c_str(),_sDBName.c_str(),_nPort,NULL, CLIENT_MULTI_STATEMENTS))
		{
			return false;
		}
		mysql_options(&_xMySQL,MYSQL_OPT_RECONNECT,&b);
	}
	catch (...)
	{
		return false;
	}
	ASSERT_LOG_ERROR(0 == mysql_set_server_option(&_xMySQL,MYSQL_OPTION_MULTI_STATEMENTS_ON));
	_bConnected = true;
	return true;
}

const char* CMySqlClient::GetLastError()const
{
	return mysql_error(&_xMySQL);
}

UINT CMySqlClient::GetLastErrCode()const
{
	return  mysql_errno(&_xMySQL);
}

bool CMySqlClient::Close()
{
	mysql_close(&_xMySQL);
	_bConnected=false;
	return true;
}

bool CMySqlClient::Ping()
{
	_bConnected = (0 == mysql_ping(&_xMySQL));
	return _bConnected;
}

bool CMySqlClient::Execute(const std::string& sSql, CMySqlResults& record)
{
	if (!record.SetMySql(&_xMySQL))return false;

	if (0 != mysql_query(&_xMySQL,sSql.c_str()))
	{
		switch (GetLastErrCode())
		{
		case CR_SERVER_LOST:
		case CR_SERVER_GONE_ERROR:
			_bConnected = false;
			break;
		}

		return false;
	}

	ASSERT_LOG_ERROR(record.FirstRecord());
	if (record.IsHasResult())return true;
	return 0 == mysql_field_count(&_xMySQL);
}

const std::string& CMySqlClient::GetDataBaseName() const
{
	return _sDBName;
}

bool CMySqlClient::IsConnected() const
{
	return _bConnected;
}

NS_TOOL_FRAME_END


#endif
