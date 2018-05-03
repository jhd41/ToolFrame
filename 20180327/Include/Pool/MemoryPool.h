#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN

//内存池
//快速分配每次固定大小的内存(返回的内存地址符合O2地址优化规则)
class CMemoryPool
{
public:
	//内存块
	struct XMemoryBlock
	{
		CMemoryPool*	pPool;		//分配的池
		void*			pUserPtr;	//返回用户分配地址
		void*			pReal;		//实际内存分配地址
	};

	typedef std::list<XMemoryBlock*> QueueMemoryPool;
public:
	bool	SetMallocSize(size_t uSize);//设置每次分配的大小 先调用后使用，调用后不得修改
	void*	Malloc();
	bool	Free(const void* mem);
public:
	static bool	AutoFree(const void* mem);//自动释放(无需找到分配池)
public:
	bool	IsEmpty()const;			//是否都无效
	
	size_t	GetMallocSize()const;	//获取单元分配大小
	int		GetInvaildCount()const;	//获取无效数
	int		GetVaildCount()const;	//获取有效数
	int		GetTotalCount()const;	//获取总共含有的数量(包括无效块)

	uint	Release();				//回收无效的内存

	//无上锁
public:
	const QueueMemoryPool&	GetInvaild()const;
	CMutexReadWrite&		GetMutex()const;
	void*					UnlockMalloc();
	bool					UnlockFree(const void* mem);
private:
	bool	Free(XMemoryBlock* pBlock);//内部函数 加速释放
public:
	CMemoryPool(void);
	CMemoryPool(uint uSizeMalloc);
	virtual ~CMemoryPool(void);
private:
	size_t			_uMallocSize;
	QueueMemoryPool	_vInvaild;		//回收的
	int				_nTotalCount;	//总共分配的内存大小

	mutable CMutexReadWrite	_mutex;
};

NS_TOOL_FRAME_END
