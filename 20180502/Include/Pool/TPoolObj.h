#pragma once

//TPoolObj只可以提供自己本类的内存池 子类也不行

#include "MMemory.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

template<typename T>
class TPoolObj{
	//typename T仅仅是一个标记使得每个继承的类里的静态缓冲池都不冲突
	//可以不使用虚析构函数 因为我们析构时不需要保证size的正确性
private:
	static CBoostPool* _pPool;
public:
	static void* operator new(size_t uSize);
	static void operator delete(void* mem);
	static void* operator new[](size_t size);
	static void operator delete[](void* mem);
};

template<typename T>
CBoostPool* TPoolObj<T>::_pPool=nullptr;

template<typename T>
void* TPoolObj<T>::operator new(size_t uSize){
	if (nullptr == _pPool)
	{
		_pPool = CBoostPool(uSize);
	}
	return _pPool->Malloc();
}

template<typename T>
void TPoolObj<T>::operator delete(void* pMem)
{
	return _pPool->Free(pMem);
}

template<typename T>
void* TPoolObj<T>::operator new[](size_t uSize){
	return MMemory::Singleton().Malloc(uSize,true);
}
template<typename T>
void TPoolObj<T>::operator delete[](void* pMem)
{
	return MMemory::Singleton().Free(pMem,true);
}

NS_TOOL_FRAME_END
