#pragma once
#include "Macro.h"

#ifdef MACRO_LIB_MY_SQL

#include "mysql.h"
#include "errmsg.h"

#include "MySqlResults.h"

NS_TOOL_FRAME_BEGIN

class CMySqlClient
{
public:
	bool		SetDataBase(const std::string& sHostName,int nPort,const std::string& sDBName,const std::string& sUserName,const std::string& sPwd);
	bool		ConnectDB(const std::string& sHostName,int nPort,const std::string& sDBName,const std::string& sUserName,const std::string& sPwd);
	bool		ConnectDB(void);
	bool		Ping();	//判断是否连接成功
	bool		Execute(const std::string& sSql, CMySqlResults& record);			//执行SQL语句
	const std::string& GetDataBaseName()const;

	const char* GetLastError()const;	//获取错误信息
	UINT		GetLastErrCode()const;	//获取错误号
	bool		IsConnected()const;

	bool		Close();//关闭SQL
public:
	CMySqlClient(void);
	virtual ~CMySqlClient(void);
private:
	//数据库信息
	std::string _sHostName;
	int			_nPort;
	std::string _sDBName;
	std::string _sUserName;
	std::string _sPwd;
	bool		_bConnected;

	mutable MYSQL _xMySQL;//数据库
};

NS_TOOL_FRAME_END

#endif
