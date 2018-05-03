#include "MMemory.h"
#include "MLoger.h"
#include "ToolStd.h"
#include "ToolPlat.h"

NS_TOOL_FRAME_BEGIN

MMemory::MMemory(void)
{
}

MMemory::~MMemory(void)
{

}

void* MMemory::Malloc(size_t uSize, bool bGroup, bool bSmartLength /*= true*/, bool bMemClear /*= false */)
{
	return _vPool.Malloc(uSize, bSmartLength, bMemClear);
}

bool MMemory::Free(void* pMem, bool bGroup)
{
	return _vPool.Free(pMem);
}

uint MMemory::ReleaseMemory()
{
	return _vPool.ReleaseMemory();
}

const CMemoryPoolMgr& MMemory::GetMgr() const
{
	return _vPool;
}

NS_TOOL_FRAME_END

using namespace ToolFrame;
void* ToolFrame::Malloc( size_t uSize,bool bGroup,bool bSmartLength /*= true*/,bool bMemClear /*= false*/ )
{
	return MMemory::Singleton().Malloc(uSize,bGroup,bSmartLength,bMemClear);
}

bool ToolFrame::Free( void* pMem,bool bGroup )
{
	return MMemory::Singleton().Free(pMem,bGroup);
}


