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
	bool		Ping();	//�ж��Ƿ����ӳɹ�
	bool		Execute(const std::string& sSql, CMySqlResults& record);			//ִ��SQL���
	const std::string& GetDataBaseName()const;

	const char* GetLastError()const;	//��ȡ������Ϣ
	UINT		GetLastErrCode()const;	//��ȡ�����
	bool		IsConnected()const;

	bool		Close();//�ر�SQL
public:
	CMySqlClient(void);
	virtual ~CMySqlClient(void);
private:
	//���ݿ���Ϣ
	std::string _sHostName;
	int			_nPort;
	std::string _sDBName;
	std::string _sUserName;
	std::string _sPwd;
	bool		_bConnected;

	mutable MYSQL _xMySQL;//���ݿ�
};

NS_TOOL_FRAME_END

#endif
