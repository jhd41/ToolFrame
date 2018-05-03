#include "BoostPool.h"
#include "ToolStd.h"
#include "MLoger.h"
#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN
CBoostPool::CBoostPool( UINT uSize )
:_nCount(0)
{
	_pool = new boost::pool<>(uSize);
}

CBoostPool::~CBoostPool(void)
{
	ToolFrame::Delete(_pool);
}

void* CBoostPool::Malloc()
{
	CLockWrite lock(_mutex);
	++_nCount;
	return _pool->malloc();
}

void CBoostPool::Free( void*& mem )
{
	CLockWrite lock(_mutex);
	--_nCount;
	_pool->free(mem);
}

bool CBoostPool::ReleaseMemory()
{
	CLockWrite lock(_mutex);
	return _pool->release_memory();
}

bool CBoostPool::IsEmpty()const
{
	CLockRead lock(_mutex);
	return !_nCount;
}

int CBoostPool::GetUsedCount()const
{
	CLockRead lock(_mutex);
	return _nCount;
}

NS_TOOL_FRAME_END
