#pragma once
#include "MacroDataBase.h"

#ifdef MACRO_LIB_MY_SQL

#include "IQuery.h"

#include "SqlResults.h"

NS_TOOL_FRAME_BEGIN

DEFINE_SHARE_PTR(ISqlQuery, ISqlQueryPtr);
class ISqlQuery
	:public IQuery
{
public:
	virtual bool				AddSql(const std::string& sSql);
	virtual bool				SetSql(const std::string& sSql, int nRecord = -1);//Ԥ�Ƽ�¼������(-1Ϊ��Ԥ��)
	virtual const std::string&	GetSql()const;
	virtual bool				IsSqlEmpty()const;		//SQL����Ƿ�Ϊ��
	virtual bool				IsDBNameEmpty()const;	//���ݿ������Ƿ�Ϊ��
	virtual bool				MakeSqlStream();		//����SQL ���� ����SQL�Ƿ���ֵ
public:
	virtual bool OnSqlExecuted(CSqlResults& xResults);
public:
	ISqlQuery();
	virtual ~ISqlQuery();
private:
	CFIELD_STRING(DBName);		//����DB������
	
private:
	std::stringstream	_sSqlStream;	//��������SQL�����
	std::string			_sSql;			//����ִ�е�SQL���	
	int					_nRecord;		//�Խ������Ԥ��
};

NS_TOOL_FRAME_END

#endif
