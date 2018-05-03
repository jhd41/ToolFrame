#include "MemoryPoolMgr.h"

#include "MLoger.h"
#include "ToolStd.h"
#include "ToolPlat.h"

NS_TOOL_FRAME_BEGIN

CMemoryPoolMgr::CMemoryPoolMgr()
{
}

CMemoryPoolMgr::~CMemoryPoolMgr()
{
	ReleaseMemory();
}

void* CMemoryPoolMgr::Malloc(size_t uSize, bool bSmartLength /*= true*/, bool bMemClear /*= false*/)
{
	//实际申请的内存空间
	size_t uMalloc = uSize;

	//智能调整所需空间
	if (bSmartLength)
		uMalloc = ToolFrame::SmartMemoryLength(uSize);

	//找到对应的内存
	void* pMem = RealMalloc(uMalloc);
	if (!pMem)return nullptr;

	if (bMemClear)
		ToolFrame::MemClear(pMem, uSize);//只需要清理申请的空间大小就好了

	return pMem;
}

bool CMemoryPoolMgr::Free(void* pMem)
{
	if (!pMem)return false;//删除空指针是安全的

	return CMemoryPool::AutoFree(pMem);
}

uint CMemoryPoolMgr::ReleaseMemory()
{
	uint uReleased = 0;
	bool bEmpty = false;
	
	//遍历释放内存池
	{
		CLockRead lockRead(_mutex);

		MapMemoryPool::iterator itr;
		foreach(itr, _vPool) {
			CMemoryPool* pPool = itr->second;
			ASSERT_LOG_ERROR(pPool);

			uReleased += pPool->Release();
			bEmpty |= pPool->IsEmpty();
		}
	}

	//遍历释放空的内存池
	{
		CLockWrite lockWrite(_mutex);

		MapMemoryPool::iterator itr = _vPool.begin();
		while (itr != _vPool.end())
		{
			CMemoryPool* pPool = itr->second;
			ASSERT_LOG_ERROR(pPool);
			
			if (pPool->IsEmpty())
			{
				ToolFrame::Delete(pPool);
				itr = ToolFrame::EraseByItr(_vPool, itr);
				continue;
			}

			++itr;
		}
	}

	return uReleased;
}

bool CMemoryPoolMgr::IsEmpty() const
{
	CLockRead lockRead(_mutex);

	if (_vPool.empty())return true;

	MapMemoryPool::const_iterator itr;
	foreach(itr, _vPool) {
		CMemoryPool* pPool = itr->second;
		ASSERT_LOG_ERROR(pPool);

		if (!pPool->IsEmpty())
			return false;
	}

	return true;
}

std::string CMemoryPoolMgr::DebugString() const
{
	std::stringstream sStream;
	sStream <<"CMemoryPoolMgr:"<<std::endl;

	size_t uMemoryTotal = 0;

	CLockRead lockRead(_mutex);
	MapMemoryPool::const_iterator itr;
	foreach(itr,_vPool) {
		CMemoryPool* pPool = itr->second;
		ASSERT_LOG_ERROR(pPool);
		size_t uMemory = pPool->GetMallocSize() *  pPool->GetTotalCount();
		sStream << "Size:" <<std::left <<std::setw(10)<< itr->first<<" InvaildCount:" << std::left << std::setw(10) << pPool->GetInvaildCount() <<" VaildCount:" << std::left << std::setw(10) << pPool->GetVaildCount() <<" TotalCount:" << std::left << std::setw(10) << pPool->GetTotalCount()<<" Memory:" << std::left << std::setw(20) << ToolFrame::ValueToRead(uMemory) << std::endl;
		uMemoryTotal += uMemory;
	}

	sStream << "MemoryTotal:" << ToolFrame::ValueToRead(uMemoryTotal) << std::endl;

	return sStream.str();
}

void* CMemoryPoolMgr::RealMalloc(size_t uMalloc)
{
	//第一次搜索
	{
		CLockRead lockRead(_mutex);
		CMemoryPool* pPool = ToolFrame::GetPtrValueByKey(_vPool, uMalloc);
		if (pPool)
			return pPool->Malloc();//uMalloc
	}

	//第二次搜索
	CLockWrite lockWrite(_mutex);
	CMemoryPool* pPool = ToolFrame::GetPtrValueByKey(_vPool, uMalloc,true);
	if (!pPool)return nullptr;
	pPool->SetMallocSize(uMalloc);
	return pPool->Malloc();//uMalloc
}

NS_TOOL_FRAME_END
