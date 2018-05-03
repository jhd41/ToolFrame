#include "IMySqlQuery.h"

#ifdef MACRO_LIB_MY_SQL

#include "MLoger.h"
#include "ToolFrame.h"

#include "IMySqlProcess.h"

NS_TOOL_FRAME_BEGIN

//SQL��ѯ����
IMySqlQuery::IMySqlQuery(void)
{
	_nRecord = 0;
	SetID(INVALID_ID);
	SetClientID(INVALID_ID);
	SetProcessNull();
	SetHandlerOverNull();
	SetQueryType(INVALID_ID);
	SetTimeOut(0);
	SetErrCode(ERR_SQL_INVALID);
}

IMySqlQuery::~IMySqlQuery(void)
{
}

bool IMySqlQuery::OnSqlExecuted( CMySqlResults& record )
{
	//�������
	return OnSqlExecuted(record,CheckBaseRecord(record));
}

bool IMySqlQuery::OnSqlExecuted( CMySqlResults& record, ESqlErrCode eErrCode )
{
	ASSERT_LOG_ERROR(GetProcess());	
	return GetProcess()->OnSqlExecuted(this,record);
}

bool IMySqlQuery::AddSql( const std::string& sSql)
{
	if (sSql.empty())return false;

	_sSqlStream<<sSql;
	
	if (!ToolFrame::IsEndWith(sSql,";"))//ĩβ;�� �Խ����Ӱ��ܴ�
		_sSqlStream<<";";
	return true;
}

bool IMySqlQuery::SetSql( const std::string& sSql,int nRecord/*=-1*/ )
{
	if (sSql.empty())return false;
	
	_nRecord = nRecord;
	_sSql = sSql;
	return true;
}

const std::string& IMySqlQuery::GetSql() const
{
	return _sSql;
}

bool IMySqlQuery::IsSqlEmpty() const
{
	return _sSql.empty();
}

ESqlErrCode IMySqlQuery::CheckBaseRecord( const CMySqlResults& record ) const
{
	if (record.IsError())return ERR_SQL_EXECUTE_FAILD;

	//���Խ����Ԥ�ڣ����� ��� ��Ԥ�ڲ�һ��
	if (-1 != _nRecord && _nRecord != record.GetRecordCount())
	{
		//��Ԥ��Ϊ�� ��ֱ�ӷ���
		if (_nRecord <= 0)
			return ERR_SQL_RECODE_MORE;

		//��Ԥ�ڲ�Ϊ��,���ж�һ�¿�ֵ
		return record.IsRecordEmpty() ? ERR_SQL_RECODE_EMPTY:ERR_SQL_RECODE_MORE;
	}

	return ERR_SQL_INVALID;
}

bool IMySqlQuery::SetDBName( const std::string& sDataBase )
{
	_sDataBase = sDataBase;
	return true;
}

const std::string& IMySqlQuery::GetDBName() const
{
	return _sDataBase;
}

const CTimeElapse& IMySqlQuery::GetElapse() const
{
	return _tElapse;
}

CTimeElapse& IMySqlQuery::GetElapse()
{
	return _tElapse;
}

bool IMySqlQuery::OnHandleOver( IMySqlQueryPtr ptr )
{
	if (!GetHandlerOver())return true;
	return GetHandlerOver()->OnQueryOver(ptr);
}

bool IMySqlQuery::MakeSqlStream()
{
	if (!_sSql.empty())return false;
	_sSql = _sSqlStream.str();
	return !_sSql.empty();
}

bool IMySqlQuery::Init()
{
	DEBUG_CLASS_INIT();

	_tElapse.ReStart();
	return true;
}

bool IMySqlQuery::IsTimeOut() const
{
	if (GetTimeOut() <= 0)return false;
	return _tElapse.TimeElapsed() > GetTimeOut();
}

bool IMySqlQuery::IsDBNameEmpty() const
{
	return _sDataBase.empty();
}

NS_TOOL_FRAME_END


#endif
