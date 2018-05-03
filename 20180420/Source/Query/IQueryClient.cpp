#include "IQueryClient.h"

#include "ToolFrame.h"

#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

IQueryClient::IQueryClient()
{
	_vVectorMap.SetIDRange(1, ToolFrame::GetLimitMax<uint32>());
	SetQueryMax(6000);
}

IQueryClient::~IQueryClient()
{
	DestoryExecuter();
}

bool IQueryClient::SetQueryMax(size_t uMax)
{
	//初始化映射表
	return _vVectorMap.Resize(uMax);
}

bool IQueryClient::Init()
{
	if (_vExecuter.empty())return false;

	//初始化连接
	MapVectorExecuter::iterator itrMap;
	foreach(itrMap, _vExecuter) {

		VectorExecuter& vVectorExecuter = itrMap->second;

		VectorExecuter::iterator itr;
		foreach(itr, vVectorExecuter) {
			IQueryExecuter* pExecuter = *itr;
			ASSERT_LOG_ERROR(pExecuter);
			if (!pExecuter->Init())return false;
		}

	}
	return true;
}

IQueryPtr IQueryClient::Query(IQueryPtr ptr, size_t uKey)
{
	if (!ptr)return IQueryPtr();

	if (INVALID_ID != ptr->GetID())return IQueryPtr();

	//随机找个连接器
	VectorExecuter* pVectorExecuter = ToolFrame::GetValuePtrByKey(_vExecuter, ptr->GetType());
	if (!pVectorExecuter)return IQueryPtr();

	IQueryExecuter* pExecuter = ToolFrame::RandPtr(*pVectorExecuter);
	if (!pExecuter)return IQueryPtr();

	size_t uID = _vVectorMap.SmartInsert(uKey, ptr);
	//如果查询已满进入等待队列
	if (INVALID_ID == uID)
	{
		_vWait.Push(ptr);
		return ptr;
	}

	ptr->SetID(uID);
	ptr->Init();

	DEBUG_POINT();

	ASSERT_LOG_ERROR(pExecuter);
	ASSERT_LOG_ERROR(pExecuter->Query(ptr));
	return ptr;
}

size_t IQueryClient::GetQueryCount() const
{
	return  _vVectorMap.GetSize() + _vWait.Size();
}

size_t IQueryClient::ClearProcessCount()
{
	return _uProcessCount.ClearCounter();
}

bool IQueryClient::IsQueryEmpty() const
{
	return _vVectorMap.Empty() && _vWait.Empty();
}

const IQueryClient::MapVectorExecuter& IQueryClient::GetExecuter() const
{
	return _vExecuter;
}

IQueryClient::VectorExecuter* IQueryClient::FindExecuter(int eType /*= 0*/) const
{
	return ToolFrame::GetValuePtrByKey(_vExecuter, eType);
}

bool IQueryClient::DestoryExecuter()
{
	ToolFrame::Delete(_vExecuter);
	return true;
}

IQueryPtr IQueryClient::OnQueryExecuted(IQueryExecuter* pExecuter, uint uQueryID)
{
	DEBUG_POINT();
	
	//查询结束
	IQueryPtr pQuery = _vVectorMap.Erase(uQueryID);
	if (!pQuery)return IQueryPtr();

	pQuery->QueryEnd();

	return pQuery;
}

bool IQueryClient::OnQueryOver(IQueryExecuter* pExecuter, uint uQueryID)
{
	//查询
	_uProcessCount.AddCount();
	
	//进行下一次查询
	IQueryPtr ptr = _vWait.PopPtr();
	if (ptr) {
		Query(ptr, uQueryID);
	}

	return true;
}

bool IQueryClient::InsertExecuter(IQueryExecuter* pExecuter, int eType /*= 0*/)
{
	if (!pExecuter)return false;

	pExecuter->SetQueryClient(this);

	return ToolFrame::InsertVector(_vExecuter, eType, pExecuter);
}

NS_TOOL_FRAME_END


