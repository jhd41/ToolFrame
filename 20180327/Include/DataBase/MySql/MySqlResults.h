#pragma once
#include "Macro.h"

#ifdef MACRO_LIB_MY_SQL
#include "mysql.h"

//备注:
//记录	Record
//结果集 Result	一个结果由多条记录组成的

//MySql查询过后会生成结果集(Result)，一条SQL语句生成一个结果集，多条语句则生成多个。
//切换结果集使用 NextResult 函数
//在单个结果集中 有多条记录 切换 记录 使用 NextRecord();

NS_TOOL_FRAME_BEGIN

class CMySqlResults
{
public:
	bool		IsRecordEmpty()const;	//是否为空记录
	uint		GetRecordCount()const;	//获取记录个数
	uint		GetFieldCount()const;	//获取字段个数

	uint		GetAffectedRows()const;	//返回影响行数

	bool		FirstRecord();				//获取第一个记录行
	bool		NextRecord();				//获取下一个记录行
	const char* GetFieldValue(uint nIndex)const;//获取当前记录行中某一个字段的值(Index从0开始)
	std::string	GetFieldString(uint nIndex)const;//同GetFieldValue 只是若值无效 返回空string,性能较GetFieldValue略低
	int			GetFieldLength(uint nIndex)const;//获取单行记录长度

	//遍历结果集用
// 	bool		ResetRecord();//重置记录
// 	bool		FetchRecord();//拿下一条记录

// 	bool		ResetResult();//重置结果集
// 	bool		FetchResult();//拿下一结果集
public:
	bool		SetMySql(MYSQL* pMySql);//设置指针
	void		SetError();				//设置错误标记
	bool		Clear();				//清除所有
	bool		IsHasResult()const;		//是否有结果集
	bool		IsMoreResult();			//是否有多个结果集
	bool		NextResult();			//下一个结果集
	bool		ClearResult();			//清除结果集

	bool		IsError()const;			//是否有错误
	const char* GetLastError()const;	//获取错误信息
	uint		GetLastErrCode()const;	//获取错误号
public:
	CMySqlResults(void);
	virtual ~CMySqlResults(void);
private:
	MYSQL*		_pMySql;	//SQL连接字
	MYSQL_RES*  _pSqlRes;	//SQL结果集
	MYSQL_ROW   _sqlRow;	//SQL结果单行
	bool		_bError;	//是否有错
};

NS_TOOL_FRAME_END


#endif

