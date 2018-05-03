#pragma once

//�ڴ������:
//Ŀǰ������Ҫ��Ϊ���ڴ�� �� �Ժ�ķ�չ������ܻ����� �ڴ���ո��

#include "Macro.h"
#include "MemoryPoolMgr.h"
NS_TOOL_FRAME_BEGIN
class MMemory
{
	ST_INTANCE(MMemory)

public:
	void*	Malloc(size_t uSize,bool bGroup,bool bSmartLength = true,bool bMemClear = false );
	bool	Free(void* pMem,bool bGroup);
	uint	ReleaseMemory();//�ͷ�û��ʹ�õ��ڴ�(�����Ƿ��ͷ����ڴ�)
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
