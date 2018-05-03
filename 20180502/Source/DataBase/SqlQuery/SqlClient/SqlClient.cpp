#include "SqlClient.h"

#ifdef MACRO_LIB_MY_SQL

#include "ToolFrame.h"

#include "MLoger.h"
#include "MProtocol.h"

NS_TOOL_FRAME_BEGIN

//Sql客户端
CSqlClient::CSqlClient()
{
	_hHandler = nullptr;

	SetHandler(this);

	SetRecvSize(0);
	SetSendSize(0);
	SetBlockSize(MProtocol::Singleton().GetBlockSize());
}

CSqlClient::~CSqlClient()
{
	
}

bool CSqlClient::SetHandler(HSqlClient* hHandler)
{
	_hHandler = hHandler;
	return true;
}

bool CSqlClient::Init()
{
	if (!IQueryClient::Init())return false;
	
	return true;
}

bool CSqlClient::AddServer(const std::string& sAddress, uint uConcurrent /*= 1*/)
{
	if (sAddress.empty())return false;
	if (uConcurrent <= 0)return false;

	for (uint uIndex = 0; uIndex < uConcurrent;++uIndex) {
		CSqlQueryExecuter* pConnector = CreateExecuter<CSqlQueryExecuter>();
		ASSERT_LOG_ERROR(pConnector);

		pConnector->SetHandler(_hHandler);
		pConnector->SetClient(this);
		pConnector->SetServerAddress(sAddress);
		pConnector->SetNetBuffer(GetRecvSize(),GetSendSize(),GetBlockSize());
	}

	return true;
}

bool CSqlClient::OpenDataBase(const std::string& sIP, uint uPort, const std::string& sDBName, const std::string& sUserName, const std::string& sPwd, uint uConcurrent)
{
	VectorExecuter* pVectorExecuter = FindExecuter();
	if (!pVectorExecuter)return false;

	VectorExecuter::iterator itr;
	foreach(itr, *pVectorExecuter) {
		CSqlQueryExecuter* pConnector = dynamic_cast<CSqlQueryExecuter*>(*itr);
		ASSERT_LOG_ERROR(pConnector);
		pConnector->OpenDataBase(sIP, uPort, sDBName, sUserName, sPwd, uConcurrent);
	}

	return true;
}

bool CSqlClient::CloseDataBase(const std::string& sDBName)
{
	VectorExecuter* pVectorExecuter = FindExecuter();
	if (!pVectorExecuter)return false;

	VectorExecuter::iterator itr;
	foreach(itr, *pVectorExecuter) {
		CSqlQueryExecuter* pConnector = dynamic_cast<CSqlQueryExecuter*>(*itr);
		ASSERT_LOG_ERROR(pConnector);
		pConnector->CloseDataBase(sDBName);
	}

	return true;
}

ISqlQueryPtr CSqlClient::Query(const std::string& sDBName, const std::string& sSql)
{
	ISqlQueryPtr ptr(new ISqlQuery());
	if (!ptr)return ISqlQueryPtr();

	ptr->SetDBName(sDBName);
	ptr->SetSql(sSql);

	return Query(ptr);
}

ISqlQueryPtr CSqlClient::Query(ISqlQueryPtr ptr, size_t uKey)
{
	if (!ptr)return ISqlQueryPtr();

	//如果SQL语句没有生成则 从流生成
	if (ptr->IsSqlEmpty())
		ptr->MakeSqlStream();
	if (ptr->IsSqlEmpty()) {
		_hHandler->OnSqlClientErrSqlEmpty(ptr);
		return ISqlQueryPtr();
	}

	//先生成SQL语句 方便调试
	if (ptr->IsDBNameEmpty()) {
		_hHandler->OnSqlClientErrDBNameEmpty(ptr);
		return ISqlQueryPtr();
	}

	if (_vExecuter.empty()) {
		_hHandler->OnSqlClientErrNoConnector(ptr);
		return ISqlQueryPtr();
	}
		
	//压入查询
	if (!IQueryClient::Query(ptr, uKey))
	{
		DEBUG_POINT();
		_hHandler->OnSqlClientErrQueryClientFailed(ptr);
		return ISqlQueryPtr();
	}

	_hHandler->OnSqlClientQuery(ptr);
	return  ptr;
}

bool CSqlClient::OnSqlExecuted(CSqlQueryExecuter* pConnector, uint uSqlID, CSqlResults& sqlResults)
{
	ASSERT_LOG_ERROR(pConnector);

	ISqlQueryPtr pQuery;
	ASSERT_LOG_ERROR(ToolFrame::DynamicCast(pQuery, OnQueryExecuted(pConnector, uSqlID)));
	if (pQuery)
	{
		pQuery->OnSqlExecuted(sqlResults);
	}

	//执行回调
	_hHandler->OnSqlClientExecuted(pQuery, sqlResults);

	return OnQueryOver(pConnector, uSqlID);
}

NS_TOOL_FRAME_END

#endif
