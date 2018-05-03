#pragma once

//IPool�����ṩ���м̳���IPool�������ڴ�أ�
//ע��"ֻ��֧��ĳ��Χ�ڴ�С���ڴ�ռ䣬��Ϊ����size������Ŀ���ڴ�� ֻ�� �� Vector�ķ�ʽ�����ٶ���� ��������˼���ֵ
//ע��ֻ�н�IPool�ຬ�� ������ ���� delete��ʱ�� �����size�Ż���ȷ

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
