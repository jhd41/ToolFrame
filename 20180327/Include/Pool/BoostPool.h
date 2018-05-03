#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN
class CBoostPool
{
	typedef boost::pool<>* PoolPtr;
public:
	void*	Malloc();
	void	Free(void*& mem);
	bool	ReleaseMemory();
	bool	IsEmpty()const;
	int		GetUsedCount()const;
public:
	CBoostPool(UINT uSize);
	virtual ~CBoostPool(void);
private:
	mutable CMutexReadWrite	_mutex;
	PoolPtr					_pool;
	int						_nCount;
};
NS_TOOL_FRAME_END
