#include "MMySql.h"

#ifdef MACRO_LIB_MY_SQL

#include "ToolFrame.h"
#include "MLoger.h"
#include "MySqlWorkThread.h"
#include "IMySqlQuery.h"

NS_TOOL_FRAME_BEGIN

MMySql::MMySql(void)
{
	SetProcessNull();
	SetHandlerNull();

	SetHandler(this);
}

MMySql::~MMySql(void)
{
	_vThread.StopThread();
}

bool MMySql::Init()
{
	if (!GetProcess())return false;
	return true;
}

bool MMySql::AddDataBase( const std::string& sIp,uint uPort,const std::string& sDBName,const std::string& sUserName,const std::string& sPwd,uint uConcurrent )
{
	if (uConcurrent<=0)return false;
	if (!_vRequest.InsertKey(sDBName))return false;

	for (uint uIndex = 0; uIndex < uConcurrent; ++uIndex)
	{
		CMySqlWorkThread* pWorThread =  _vThread.CreateThread<CMySqlWorkThread>();

		ASSERT_LOG_ERROR(pWorThread);
		ASSERT_LOG_ERROR(pWorThread->SetHandler(GetHandler()));
		ASSERT_LOG_ERROR(pWorThread->SetDataBase(sIp,uPort,sDBName,sUserName,sPwd));
		ASSERT_LOG_ERROR(pWorThread->StartThread());//1,0
	}

	return true;
}

IMySqlQueryPtr MMySql::Query( IMySqlQueryPtr pQuery )
{
	do 
	{
		//如果SQL语句没有生成则 从流生成
		if (pQuery->IsSqlEmpty())
			pQuery->MakeSqlStream();
		if (pQuery->IsSqlEmpty()) {
			pQuery->SetErrCode(ERR_SQL_DBNAME_SQL_EMPTY);
			GetHandler()->OnSqlPrepareErr(pQuery);
			break;
		}

		//放在SQL语句生成之后便于出错信息的调试
		if (pQuery->IsDBNameEmpty()) {
			pQuery->SetErrCode(ERR_SQL_DBNAME_EMPTY);
			GetHandler()->OnSqlPrepareErr(pQuery);
			break;
		}

		if (!pQuery->GetProcess())
		{
			ASSERT_LOG_ERROR(GetProcess());
			pQuery->SetProcess(GetProcess());
		}

		pQuery->Init();
		
		_uQuerying.AddCount();

		IMySqlQueryPtr ptr = Push(pQuery);
		if (!ptr) {
			pQuery->SetErrCode(ERR_SQL_DBNAME_NOT_EXIST);
			GetHandler()->OnSqlPrepareErr(pQuery);
			break;
		}
			
		return ptr;

	} while (false);

	pQuery->SetErrCode(ERR_SQL_PUSH_FAILD);
	GetHandler()->OnPushSqlFaild(pQuery);
	return IMySqlQueryPtr();
}

IMySqlQueryPtr MMySql::Query( const std::string& sDataBaseName,const std::string& sSql,IMySqlProcess* pDBProcess /*= nullptr*/ )
{
	if (sSql.empty())return IMySqlQueryPtr();
	if (sDataBaseName.empty())return IMySqlQueryPtr();

	IMySqlQueryPtr ptr(new IMySqlQuery());
	if (!ptr)return IMySqlQueryPtr();

	ptr->SetDBName(sDataBaseName);
	ptr->SetSql(sSql);
	ptr->SetProcess(pDBProcess);

	return Query(ptr);
}

IMySqlQueryPtr MMySql::Pop(const std::string& sDataBaseName)
{
	CLockRead lock(_vRequest.GetMutex());
	QueueRequest* pvRequest = ToolFrame::GetValuePtrByKey(_vRequest.GetMap(),sDataBaseName);
	if (!pvRequest)return IMySqlQueryPtr();

	return pvRequest->PopFrontPtr();
}

uint MMySql::GetQueryCount() const
{
	uint uCount = 0;
	CLockRead lock(_vRequest.GetMutex());
	MapRequest::StdMap::const_iterator itr;
	foreach(itr,_vRequest.GetMap()){
		const QueueRequest& vQueue = itr->second;
		uCount += vQueue.Size();
	}

	return uCount;
}

IMySqlQueryPtr MMySql::Push( IMySqlQueryPtr pQuery )
{
	if (!pQuery)return IMySqlQueryPtr();

	CLockRead lock(_vRequest.GetMutex());
	QueueRequest* pvRequest = ToolFrame::GetValuePtrByKey(_vRequest.GetMap(),pQuery->GetDBName());
	if (!pvRequest)return IMySqlQueryPtr();

	pvRequest->Push(pQuery);
	return pQuery;
}

ToolFrame::IMySqlQueryPtr MMySql::PushFront( IMySqlQueryPtr pQuery )
{
	if (!pQuery)return IMySqlQueryPtr();

	CLockRead lock(_vRequest.GetMutex());
	QueueRequest* pvRequest = ToolFrame::GetValuePtrByKey(_vRequest.GetMap(),pQuery->GetDBName());
	if (!pvRequest)return IMySqlQueryPtr();

	pvRequest->PushFront(pQuery);
	return pQuery;
}
bool MMySql::IsEmpty() const
{
	return _uQuerying.IsZero();
}

bool MMySql::OnQueryOver( IMySqlQueryPtr pSqlQuery )
{
	ASSERT_LOG_ERROR(pSqlQuery);
	_uQuerying.ReduceCount();
	_uTotal.AddCount();

	_uTimeAvg.AddTimeElapsed(pSqlQuery->GetElapse().TimeElapsed());
	return true;
}

uint MMySql::GetQueryTotal() const
{
	return _uTotal.GetCount();
}

uint MMySql::GetQueryAvgTime() const
{
	return _uTimeAvg.GetAvgTime();
}

NS_TOOL_FRAME_END


#endif
