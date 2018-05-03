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
	virtual bool				SetSql(const std::string& sSql, int nRecord = -1);//预计记录的条数(-1为不预计)
	virtual const std::string&	GetSql()const;
	virtual bool				IsSqlEmpty()const;		//SQL语句是否为空
	virtual bool				IsDBNameEmpty()const;	//数据库名称是否为空
	virtual bool				MakeSqlStream();		//创建SQL 从流 返回SQL是否有值
public:
	virtual bool OnSqlExecuted(CSqlResults& xResults);
public:
	ISqlQuery();
	virtual ~ISqlQuery();
private:
	CFIELD_STRING(DBName);		//设置DB的名字
	
private:
	std::stringstream	_sSqlStream;	//辅助生成SQL语句流
	std::string			_sSql;			//真正执行的SQL语句	
	int					_nRecord;		//对结果集的预估
};

NS_TOOL_FRAME_END

#endif
