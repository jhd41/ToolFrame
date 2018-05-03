#include "IQueryExecuter.h"

#include "IQueryClient.h"

NS_TOOL_FRAME_BEGIN

IQueryExecuter::IQueryExecuter()
{
	_pQueryClient = nullptr;
}

IQueryExecuter::~IQueryExecuter()
{
}

bool IQueryExecuter::SetQueryClient(IQueryClient* pQueryClient)
{
	_pQueryClient = pQueryClient;
	return true;
}

bool IQueryExecuter::Init()
{
	return true;
}

bool IQueryExecuter::Query(IQueryPtr ptr)
{
	return true;
}

IQueryPtr IQueryExecuter::OnQueryExecuted(uint uQueryID)
{
	return _pQueryClient->OnQueryExecuted(this, uQueryID);
}

bool IQueryExecuter::OnQueryOver(uint uQueryID)
{
	return _pQueryClient->OnQueryOver(this, uQueryID);
}

NS_TOOL_FRAME_END
