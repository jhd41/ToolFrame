#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"
#include "ToolStd.h"
#include "MemoryPool.h"

NS_TOOL_FRAME_BEGIN

template<typename T>
class CMemoryPoolObj
{
public:
	T*		Malloc();
	bool	Free(const void* mem);
public:
	bool	IsEmpty()const;			//�Ƿ�Ϊ��
	int		GetInvaildCount()const;	//��ȡ��Ч��
	int		GetVaildCount()const;	//��ȡ��Ч��
	int		GetTotalCount()const;	//��ȡ�ܹ����е�����(������Ч��)
	uint	Release();				//������Ч���ڴ�
public:
	CMemoryPoolObj(void);
	virtual ~CMemoryPoolObj(void);
private:
	CMemoryPool	_vPool;
};

template<typename T>
CMemoryPoolObj<T>::CMemoryPoolObj(void)
{
	_vPool.SetMallocSize(sizeof(T));
}

template<typename T>
CMemoryPoolObj<T>::~CMemoryPoolObj(void)
{
	Release();
}

template<typename T>
T* CMemoryPoolObj<T>::Malloc()
{
	return ToolFrame::Construct<T>(_vPool.Malloc());
}

template<typename T>
bool CMemoryPoolObj<T>::Free( const void* mem )
{
	if (!mem)return true;
	ToolFrame::Destruct((T*)mem);
	return _vPool.Free(mem);
}

template<typename T>
bool CMemoryPoolObj<T>::IsEmpty() const
{
	return _vPool.IsEmpty();
}

template<typename T>
int CMemoryPoolObj<T>::GetInvaildCount() const
{
	return _vPool.GetInvaildCount();
}

template<typename T>
int CMemoryPoolObj<T>::GetVaildCount() const
{
	return _vPool.GetVaildCount();
}

template<typename T>
int CMemoryPoolObj<T>::GetTotalCount() const
{
	return _vPool.GetTotalCount();
}

template<typename T>
uint CMemoryPoolObj<T>::Release()
{
	return _vPool.Release();
}

NS_TOOL_FRAME_END
