#pragma once

//IPool可以提供所有继承自IPool的子类内存池，
//注意"只能支持某范围内大小的内存空间，因为根据size来查找目标内存池 只有 以 Vector的方式索引速度最快 因此引入了极限值
//注记只有将IPool类含有 虚析构 函数 delete的时候 传入的size才会正确

#include "Macro.h"
#include <new>

NS_TOOL_FRAME_BEGIN

class IPool{
 public:
 	static void* operator new(size_t uSize);
 	static void operator delete(void* pMem);
 
 	static void* operator new[](size_t uSize);
 	static void operator delete[](void* pMem);
public:
	IPool();
	virtual ~IPool();
};

class IPoolZero
{
 public:
 	static void* operator new(size_t uSize);
 	static void operator delete(void* pMem);
 
 	static void* operator new[](size_t uSize);
 	static void operator delete[](void* pMem);
public:
	IPoolZero();
	virtual ~IPoolZero();
};

NS_TOOL_FRAME_END

//void* FN_CDECL operator new(UINT size)
//{
//	return MMemory::Singleton().Malloc(size);
//}
//
//void FN_CDECL operator delete(void* mem)
//{
//	return MMemory::Singleton().Delete(mem);
//}

//////////////////////////////////////////////////////////////////////////

//void* FN_CDECL operator new(dsize_t size, const char* fileName, const U32 line)
//{
//	return nullptr;
//}
//
//void* FN_CDECL operator new[](dsize_t size, const char* fileName, const U32 line)
//{
//	return nullptr;
//}
//
//void* FN_CDECL operator new(dsize_t size)
//{
//	if (g_pGoble)return g_pGoble;
//	
//	g_pGoble = malloc(size);
//	return g_pGoble;
//}
//
//void* FN_CDECL operator new[](dsize_t size)
//{
//	return nullptr;
//}
//
//void FN_CDECL operator delete(void* mem)
//{
//	return free(mem);
//}
//
//void FN_CDECL operator delete[](void* mem)
//{
//	return ;
//}
