#pragma once
#include "MacroDataBase.h"

#ifdef MACRO_LIB_MY_SQL

#include "MacroMySql.h"
#include "MacroDefineEx.h"
#include "IPool.h"
#include "MySqlResults.h"
#include "TimeElapse.h"
#include "MDebug.h"

NS_TOOL_FRAME_BEGIN
class IMySqlProcess;
class IMySqlQueryOver;

//SQL��ѯ����
DEFINE_SHARE_PTR(IMySqlQuery,IMySqlQueryPtr);
class IMySqlQuery
	:public IPoolZero
{
	DEBUG_CLASS;
public:
	virtual bool				AddSql(const std::string& sSql);
	virtual bool				SetSql(const std::string& sSql,int nRecord = -1);//Ԥ�Ƽ�¼������(-1Ϊ��Ԥ��)
	virtual const std::string&	GetSql()const;
	virtual bool				IsSqlEmpty()const;//SQL����Ƿ�Ϊ��
	virtual bool				SetDBName(const std::string& sDataBase);
	virtual const std::string&	GetDBName()const;
	virtual bool				IsDBNameEmpty()const;//���ݿ������Ƿ�Ϊ��
	virtual const CTimeElapse&	GetElapse()const;	//Ч�ʼ�ʱ��(����ִ��Ч��)
	virtual CTimeElapse&		GetElapse();		//Ч�ʼ�ʱ��(����ִ��Ч��)
	virtual bool				MakeSqlStream();	//����SQL ���� ����SQL�Ƿ���ֵ
	virtual bool				Init();				//���ó�ʼ��
public:
	virtual bool				IsTimeOut()const;	//�ж��Ƿ��Ѿ���ʱ
public:
	virtual bool				OnSqlExecuted(CMySqlResults& record);
	virtual bool				OnSqlExecuted(CMySqlResults& record, ESqlErrCode eErrCode);
	//�ⲿ��Ҫ����
public:
	virtual bool				OnHandleOver(IMySqlQueryPtr ptr);
private:
	virtual	ESqlErrCode			CheckBaseRecord(const CMySqlResults& record )const;///����������� �Ƿ���Ԥ��
public:
	IMySqlQuery(void);
	virtual ~IMySqlQuery(void);
private:
	CFIELD_INT(ID);
	CFIELD_INT(ClientID);
	CFIELD_PTR(IMySqlProcess*,Process,p);
	CFIELD_PTR(IMySqlQueryOver*,HandlerOver,p);//ϵͳ�ڲ����� �ⲿ��Ҫ����
	CFIELD_INT(QueryType);
	CFIELD_UINT(TimeOut);					//���ó�ʱʱ�� ���� 0Ϊ����(����ѯʱ�Ѿ���ʱ�򲻲�ѯ)
	CFIELD_ENUM(ESqlErrCode, ErrCode);	//���ô������
private:
	std::string			_sDataBase;		//���ݿ�����
	std::stringstream	_sSqlStream;	//��������SQL�����
	std::string			_sSql;			//����ִ�е�SQL���
	int					_nRecord;		//�Խ������Ԥ��
	CTimeElapse			_tElapse;		//��ʱ
};

NS_TOOL_FRAME_END

#endif
