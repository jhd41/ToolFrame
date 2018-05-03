#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"
#include "MemoryPool.h"

NS_TOOL_FRAME_BEGIN

class CMemoryPoolMgr
{
	//�ڴ��
	struct XMemoryBlock
	{
		CMemoryPool* pPool;
	};

	typedef std::map<size_t, CMemoryPool*> MapMemoryPool;
public:
	void*	Malloc(size_t uSize, bool bSmartLength = true, bool bMemClear = false);
	bool	Free(void* pMem);
	uint	ReleaseMemory();//�ͷ�û��ʹ�õ��ڴ�(�����Ƿ��ͷ����ڴ�)
	bool	IsEmpty()const;
public:
public:
	virtual std::string DebugString()const;//��ȡ������Ϣ
private:
	void*	RealMalloc(size_t uMalloc);//��������
public:
	CMemoryPoolMgr();
	virtual ~CMemoryPoolMgr();
private:
	MapMemoryPool _vPool;

	mutable CMutexReadWrite	_mutex;
};

NS_TOOL_FRAME_END
