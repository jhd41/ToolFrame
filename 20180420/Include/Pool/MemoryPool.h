#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN

//�ڴ��
//���ٷ���ÿ�ι̶���С���ڴ�(���ص��ڴ��ַ����O2��ַ�Ż�����)
class CMemoryPool
{
public:
	//�ڴ��
	struct XMemoryBlock
	{
		CMemoryPool*	pPool;		//����ĳ�
		void*			pUserPtr;	//�����û������ַ
		void*			pReal;		//ʵ���ڴ�����ַ
	};

	typedef std::list<XMemoryBlock*> QueueMemoryPool;
public:
	bool	SetMallocSize(size_t uSize);//����ÿ�η���Ĵ�С �ȵ��ú�ʹ�ã����ú󲻵��޸�
	void*	Malloc();
	bool	Free(const void* mem);
public:
	static bool	AutoFree(const void* mem);//�Զ��ͷ�(�����ҵ������)
public:
	bool	IsEmpty()const;			//�Ƿ���Ч
	
	size_t	GetMallocSize()const;	//��ȡ��Ԫ�����С
	int		GetInvaildCount()const;	//��ȡ��Ч��
	int		GetVaildCount()const;	//��ȡ��Ч��
	int		GetTotalCount()const;	//��ȡ�ܹ����е�����(������Ч��)

	uint	Release();				//������Ч���ڴ�

	//������
public:
	const QueueMemoryPool&	GetInvaild()const;
	CMutexReadWrite&		GetMutex()const;
	void*					UnlockMalloc();
	bool					UnlockFree(const void* mem);
private:
	bool	Free(XMemoryBlock* pBlock);//�ڲ����� �����ͷ�
public:
	CMemoryPool(void);
	CMemoryPool(uint uSizeMalloc);
	virtual ~CMemoryPool(void);
private:
	size_t			_uMallocSize;
	QueueMemoryPool	_vInvaild;		//���յ�
	int				_nTotalCount;	//�ܹ�������ڴ��С

	mutable CMutexReadWrite	_mutex;
};

NS_TOOL_FRAME_END
