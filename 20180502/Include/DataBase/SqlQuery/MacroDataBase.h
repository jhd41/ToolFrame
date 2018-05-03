#pragma once

#include "Macro.h"

//遍历结果集关键字
#define foreachResult(record) for (bool bResult = true;bResult;bResult = record.NextResult())
#define foreachRecord(record) for (bool bRecord = !record.IsRecordEmpty();bRecord;bRecord = record.NextRecord())

//SQL语句执行错误代号
enum ESqlErrCode {
	ERR_SQL_INVALID = 0,

	ERR_SQL_SUCCEED = 1,

	//准备期错误
	ERR_SQL_DBNAME_EMPTY,		//数据库名称为空
	ERR_SQL_DBNAME_NOT_EXIST,	//数据库不存在
	ERR_SQL_DBNAME_SQL_EMPTY,	//SQL为空
	ERR_SQL_PUSH_FAILD,			//压入失败

	//执行期错误
	ERR_SQL_TIMEOUT,			//超时
	ERR_SQL_EXECUTE_FAILD,		//执行失败	

	//回调后错误
	ERR_SQL_RECODE_EMPTY,		//记录为空
	ERR_SQL_RECODE_MORE,		//记录过多
	ERR_SQL_DATA_SIZE_MAX,		//数据量过大(无法回传)

	ERR_SQL_MAX,
};