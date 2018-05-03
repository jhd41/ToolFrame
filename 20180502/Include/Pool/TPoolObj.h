#pragma once

//TPoolObjֻ�����ṩ�Լ�������ڴ�� ����Ҳ����

#include "MMemory.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

template<typename T>
class TPoolObj{
	//typename T������һ�����ʹ��ÿ���̳е�����ľ�̬����ض�����ͻ
	//���Բ�ʹ������������ ��Ϊ��������ʱ����Ҫ��֤size����ȷ��
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
