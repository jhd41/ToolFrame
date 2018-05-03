#include "MySqlResults.h"

#ifdef MACRO_LIB_MY_SQL

#include "ToolFrame.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

CMySqlResults::CMySqlResults(void)
{
	_pMySql=NULL;
	_pSqlRes=NULL;
	_sqlRow =NULL;

	_bError = false;
}

CMySqlResults::~CMySqlResults(void)
{
	Clear();
}

bool CMySqlResults::Clear()
{
	ClearResult();
	_pMySql = NULL;
	_bError = false;
	return true;
}

bool CMySqlResults::ClearResult()
{
	if (!_pMySql)return false;

	if( _pSqlRes ){
		mysql_free_result(_pSqlRes);
		_pSqlRes = nullptr;
	}
		
	int status =0;
	do{
		status = mysql_next_result(_pMySql);
		if( 0!=status )
			break;
		_pSqlRes = mysql_store_result(_pMySql);
		if( _pSqlRes ) mysql_free_result(_pSqlRes);
	}while(0 == status);

	_pSqlRes= NULL;
	_sqlRow = NULL;
	return true;
}

bool CMySqlResults::SetMySql( MYSQL* pMySql )
{
	if (!pMySql)return false;
	_pMySql = pMySql;
	return true;
}

bool CMySqlResults::IsHasResult() const
{
	return !!_pSqlRes;
}

bool CMySqlResults::FirstRecord()
{
	if (!_pMySql)return false;

	ASSERT_LOG_ERROR(!_pSqlRes);
	ASSERT_LOG_ERROR(!_sqlRow);
	_pSqlRes = mysql_store_result(_pMySql);
	if (_pSqlRes)
		_sqlRow = mysql_fetch_row(_pSqlRes);
	return true;
}

bool CMySqlResults::NextRecord()
{
	if (!_pSqlRes)return false;

	_sqlRow = mysql_fetch_row(_pSqlRes);
	return NULL != _sqlRow;
}

const char* CMySqlResults::GetFieldValue( uint nIndex )const
{
	if (!_sqlRow)return NULL;
	if (nIndex >= GetFieldCount())return NULL;

	return _sqlRow[nIndex];
}

uint CMySqlResults::GetRecordCount()const
{
	return _pSqlRes ? (uint)mysql_num_rows(_pSqlRes) : 0;
}

bool CMySqlResults::IsRecordEmpty() const
{
	return !GetRecordCount();
}

uint CMySqlResults::GetFieldCount()const
{
	return _pSqlRes ? (uint)mysql_num_fields(_pSqlRes) : 0;
}

const char* CMySqlResults::GetLastError() const
{
	ASSERT_LOG_ERROR(_pMySql);
	return mysql_error(_pMySql);
}

uint CMySqlResults::GetLastErrCode() const
{
	ASSERT_LOG_ERROR(_pMySql);
	return  mysql_errno(_pMySql);
}

void CMySqlResults::SetError()
{
	_bError = true;
}

bool CMySqlResults::IsError() const
{
	return _bError;
}

std::string CMySqlResults::GetFieldString( uint nIndex ) const
{
	const char* sz = GetFieldValue(nIndex);
	if (!sz)return "";

	return sz;
}

int CMySqlResults::GetFieldLength( uint nIndex ) const
{
	//获取当前记录的长度
	if (!_sqlRow)return false;
	unsigned long * pArray  = mysql_fetch_lengths( _pSqlRes );
	return pArray[nIndex];
}

bool CMySqlResults::IsMoreResult() 
{
	if (!_pMySql)return false;
	return !!mysql_more_results(_pMySql);
}

bool CMySqlResults::NextResult()
{
	// 	返回值
	// 		描述
	// 		0
	// 		成功并有多个结果。
	// 		-1
	// 		成功但没有多个结果。
	// >0
	// 出错

	if (!_pMySql)return false;

	//清理上一个结果集
	if( _pSqlRes ){
		mysql_free_result(_pSqlRes);
		_pSqlRes = nullptr;
	}
	_sqlRow = nullptr;

	int nResult = mysql_next_result(_pMySql);
	if (nResult > 0)
	{
		SetError();
		return false;
	}
	if (-1 == nResult)
	{
		return false;
	}

	return FirstRecord();
}

uint CMySqlResults::GetAffectedRows() const
{
	if (!_pMySql)return 0;
	return mysql_affected_rows(_pMySql);
}

NS_TOOL_FRAME_END

#endif
