#pragma once
#include "Macro.h"

#ifdef MACRO_LIB_MY_SQL

#include "IQueryClient.h"

#include "ISqlQuery.h"
#include "SqlQueryExecuter.h"

#include "HSqlClient.h"

NS_TOOL_FRAME_BEGIN

//Sql�ͻ���
class CSqlClient
	:public IQueryClient
	,public HSqlClientLog
{
public:
	virtual bool SetHandler(HSqlClient* hHandler);			//���ô���ص�
	virtual bool AddServer(const std::string& sAddress, uint uConcurrent = 1);
	virtual bool Init();
public:
	virtual bool OpenDataBase(const std::string& sIP, uint uPort, const std::string& sDBName, const std::string& sUserName, const std::string& sPwd, uint uConcurrent);//���һ�����ݿ�
	virtual bool CloseDataBase(const std::string& sDBName);
public:
	virtual ISqlQueryPtr	Query(const std::string& sDBName,const std::string& sSql);
	virtual ISqlQueryPtr	Query(ISqlQueryPtr ptr, size_t uKey = INVALID_ID);

	//�ڲ����� �ⲿ��Ҫ����
public:
	virtual bool			OnSqlExecuted(CSqlQueryExecuter* pConnector, uint uSqlID, CSqlResults& sqlResults);
	
private:
	CFIELD_SIZE(RecvSize);	//���ջ�������С(Ĭ�� ����0)
	CFIELD_SIZE(SendSize);	//���ͻ�������С(Ĭ�� ����0)
	CFIELD_SIZE(BlockSize);	//������ÿ�η����С(Ĭ�� 65535)
public:
	CSqlClient();
	virtual ~CSqlClient();
private:
	HSqlClient*			_hHandler;	//������
};

NS_TOOL_FRAME_END

#endif


