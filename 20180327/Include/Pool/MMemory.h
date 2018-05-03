#pragma once

//内存管理器:
//目前作用主要是为了内存池 而 以后的发展方向可能会引入 内存回收概念。

#include "Macro.h"
#include "MemoryPoolMgr.h"
NS_TOOL_FRAME_BEGIN
class MMemory
{
	ST_INTANCE(MMemory)

public:
	void*	Malloc(size_t uSize,bool bGroup,bool bSmartLength = true,bool bMemClear = false );
	bool	Free(void* pMem,bool bGroup);
	uint	ReleaseMemory();//释放没有使用的内存(返回是否释放了内存)
public:
	const CMemoryPoolMgr& GetMgr()const;
public:
	MMemory();
	virtual ~MMemory();
private:
	CMemoryPoolMgr _vPool;
};

NS_TOOL_FRAME_END

namespace ToolFrame{
	void*	Malloc( size_t uSize,bool bGroup,bool bSmartLength = true,bool bMemClear = false );
	bool	Free( void* pMem,bool bGroup );
};
