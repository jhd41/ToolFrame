#pragma once
#include "Macro.h"

#ifdef MACRO_LIB_MY_SQL

#include "ISqlQuery.h"

NS_TOOL_FRAME_BEGIN

//////////////////////////////////////////////////////////////////////////
//Sql�ͻ��˴�����
class HSqlClient {
public:
	virtual bool OnSqlClientQuery(ISqlQueryPtr ptr);							//��ʼ��ѯ
	virtual bool OnSqlClientExecuted(ISqlQueryPtr ptr, CSqlResults& sqlResults);//��ѯ�ص�
public:
	virtual bool OnSqlClientConnected(const std::string& sAddress);
	virtual bool OnSqlClientFaild(const std::string& sAddress);
	virtual bool OnSqlClientDisconnected(const std::string& sAddress);
public:
	virtual bool OnSqlClientErrDBNameEmpty(ISqlQueryPtr ptr);
	virtual bool OnSqlClientErrSqlEmpty(ISqlQueryPtr ptr);
	virtual bool OnSqlClientErrNoConnector(ISqlQueryPtr ptr);//û����Ч��������

	virtual bool OnSqlClientErrQueryClientFailed(ISqlQueryPtr ptr);//ѹ���ѯ����ʧ��
public:
	HSqlClient() {}
	virtual ~HSqlClient() {}
};
//////////////////////////////////////////////////////////////////////////
//Sql�ͻ��˴�����(д��־)
class HSqlClientLog
	:public HSqlClient
{
public:
	virtual bool OnSqlClientConnected(const std::string& sAddress)override;
	virtual bool OnSqlClientFaild(const std::string& sAddress)override;
	virtual bool OnSqlClientDisconnected(const std::string& sAddress)override;
public:
	virtual bool OnSqlClientErrDBNameEmpty(ISqlQueryPtr ptr)override;
	virtual bool OnSqlClientErrSqlEmpty(ISqlQueryPtr ptr)override;
	virtual bool OnSqlClientErrNoConnector(ISqlQueryPtr ptr)override;//û����Ч��������

	virtual bool OnSqlClientErrQueryClientFailed(ISqlQueryPtr ptr)override;//ѹ���ѯ����ʧ��
};

NS_TOOL_FRAME_END

#endif
