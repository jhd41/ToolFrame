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

//SQL查询基类
DEFINE_SHARE_PTR(IMySqlQuery,IMySqlQueryPtr);
class IMySqlQuery
	:public IPoolZero
{
	DEBUG_CLASS;
public:
	virtual bool				AddSql(const std::string& sSql);
	virtual bool				SetSql(const std::string& sSql,int nRecord = -1);//预计记录的条数(-1为不预计)
	virtual const std::string&	GetSql()const;
	virtual bool				IsSqlEmpty()const;//SQL语句是否为空
	virtual bool				SetDBName(const std::string& sDataBase);
	virtual const std::string&	GetDBName()const;
	virtual bool				IsDBNameEmpty()const;//数据库名称是否为空
	virtual const CTimeElapse&	GetElapse()const;	//效率计时器(计算执行效率)
	virtual CTimeElapse&		GetElapse();		//效率计时器(计算执行效率)
	virtual bool				MakeSqlStream();	//创建SQL 从流 返回SQL是否有值
	virtual bool				Init();				//调用初始化
public:
	virtual bool				IsTimeOut()const;	//判断是否已经超时
public:
	virtual bool				OnSqlExecuted(CMySqlResults& record);
	virtual bool				OnSqlExecuted(CMySqlResults& record, ESqlErrCode eErrCode);
	//外部不要调用
public:
	virtual bool				OnHandleOver(IMySqlQueryPtr ptr);
private:
	virtual	ESqlErrCode			CheckBaseRecord(const CMySqlResults& record )const;///基本检查结果集 是否是预期
public:
	IMySqlQuery(void);
	virtual ~IMySqlQuery(void);
private:
	CFIELD_INT(ID);
	CFIELD_INT(ClientID);
	CFIELD_PTR(IMySqlProcess*,Process,p);
	CFIELD_PTR(IMySqlQueryOver*,HandlerOver,p);//系统内部调用 外部不要调用
	CFIELD_INT(QueryType);
	CFIELD_UINT(TimeOut);					//设置超时时间 毫秒 0为无限(若查询时已经超时则不查询)
	CFIELD_ENUM(ESqlErrCode, ErrCode);	//设置错误代号
private:
	std::string			_sDataBase;		//数据库名称
	std::stringstream	_sSqlStream;	//辅助生成SQL语句流
	std::string			_sSql;			//真正执行的SQL语句
	int					_nRecord;		//对结果集的预估
	CTimeElapse			_tElapse;		//耗时
};

NS_TOOL_FRAME_END

#endif
