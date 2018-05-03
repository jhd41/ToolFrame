#include "MemoryPool.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

CMemoryPool::CMemoryPool(void)
{
	_uMallocSize = 0;
	_nTotalCount = 0;
}

CMemoryPool::CMemoryPool(uint uSizeMalloc)
{
	_uMallocSize = uSizeMalloc;
	_nTotalCount = 0;
}

CMemoryPool::~CMemoryPool(void)
{
	Release();
}

bool CMemoryPool::SetMallocSize(size_t uSize)
{
	if (_uMallocSize == uSize)return true;

	if (_uMallocSize > 0)return false;
	_uMallocSize = uSize;
	return true;
}

void* CMemoryPool::Malloc()
{
	CLockWrite lock(_mutex);
	return UnlockMalloc();
}

bool CMemoryPool::Free( const void* mem )
{
	if (!mem)return true;
	CLockWrite lock(_mutex);
	return UnlockFree(mem);
}

bool CMemoryPool::IsEmpty() const
{
	CLockRead lock(_mutex);
	return _nTotalCount == (int)_vInvaild.size();
}

size_t CMemoryPool::GetMallocSize() const
{
	return _uMallocSize;
}

int CMemoryPool::GetVaildCount() const
{
	CLockRead lock(_mutex);
	return _nTotalCount - (int)_vInvaild.size();
}

int CMemoryPool::GetInvaildCount() const
{
	CLockRead lock(_mutex);
	return (int)_vInvaild.size();
}

int CMemoryPool::GetTotalCount() const
{
	CLockRead lock(_mutex);
	return _nTotalCount;
}


uint CMemoryPool::Release()
{
	CLockWrite lock(_mutex);

	if (_vInvaild.empty())return 0;

	uint uCount = (uint)_vInvaild.size();

	//分配的总内存
	_nTotalCount -= uCount;

	//释放无效内存
	QueueMemoryPool::iterator itr;
	foreach(itr, _vInvaild) {
		XMemoryBlock* pNode = *itr;
		ASSERT_LOG_ERROR(pNode);
		
		delete[] pNode->pReal;
	}

	ToolFrame::Clear(_vInvaild);
	return uCount;
}

CMutexReadWrite& CMemoryPool::GetMutex() const
{
	return _mutex;
}

const CMemoryPool::QueueMemoryPool& CMemoryPool::GetInvaild() const
{
	return _vInvaild;
}

void* CMemoryPool::UnlockMalloc()
{
	if (_uMallocSize <= 0)return nullptr;

	//先从无效地块获取
	if (!_vInvaild.empty())
	{
		QueueMemoryPool::iterator itr = _vInvaild.end();
		--itr;
		XMemoryBlock* pBlock = *itr;
		ASSERT_LOG_ERROR(pBlock);

		_vInvaild.erase(itr);
		return pBlock->pUserPtr;
	}

	//分配新内存
	//Fix:返回的内存地址必须是2的倍数
	char* pReal = new char[sizeof(XMemoryBlock) + _uMallocSize + 1];//多申请1字节 跳过奇数地址
	if (!pReal)return nullptr;

	//返回的内存地址必须是2的倍数 为了 O2优化
	char* pMem = pReal;
	if ((PtrAddress)pMem % 2 != 0)
		++pMem;

	//设置信息头
	XMemoryBlock* pNode = (XMemoryBlock*)pMem;
	ASSERT_LOG_ERROR(pNode);

	pNode->pPool	= this;
	pNode->pReal	= pReal;
	pNode->pUserPtr = pMem + sizeof(XMemoryBlock);

	//总分配大小
	++_nTotalCount;

	return pNode->pUserPtr;
}

bool CMemoryPool::UnlockFree( const void* mem )
{
	if (!mem)return true;
	char* pMem = (char*)mem;
	pMem -= sizeof(XMemoryBlock);
	XMemoryBlock* pBlock = (XMemoryBlock*)pMem;
	_vInvaild.push_back(pBlock);
	return true;
}

bool CMemoryPool::Free(XMemoryBlock* pBlock)
{
	if (!pBlock)return false;
	CLockWrite lock(_mutex);
	_vInvaild.push_back(pBlock);
	return true;
}

bool CMemoryPool::AutoFree(const void* mem)
{
	if (!mem)return true;
	char* pMem = (char*)mem;
	pMem -= sizeof(XMemoryBlock);
	XMemoryBlock* pBlock = (XMemoryBlock*)pMem;
	return pBlock->pPool->Free(pBlock);
}

NS_TOOL_FRAME_END
