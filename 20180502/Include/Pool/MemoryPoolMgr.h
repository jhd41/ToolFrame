#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"
#include "MemoryPool.h"

NS_TOOL_FRAME_BEGIN

class CMemoryPoolMgr
{
	//内存块
	struct XMemoryBlock
	{
		CMemoryPool* pPool;
	};

	typedef std::map<size_t, CMemoryPool*> MapMemoryPool;
public:
	void*	Malloc(size_t uSize, bool bSmartLength = true, bool bMemClear = false);
	bool	Free(void* pMem);
	uint	ReleaseMemory();//释放没有使用的内存(返回是否释放了内存)
	bool	IsEmpty()const;
public:
public:
	virtual std::string DebugString()const;//获取调试信息
private:
	void*	RealMalloc(size_t uMalloc);//真正分配
public:
	CMemoryPoolMgr();
	virtual ~CMemoryPoolMgr();
private:
	MapMemoryPool _vPool;

	mutable CMutexReadWrite	_mutex;
};

NS_TOOL_FRAME_END
