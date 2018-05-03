#pragma once
#include "IStreamBase.h"
#include "MacroDefineBoost.h"

//������������
//�ڲ�֧�����޴���ڴ�ռ䣬�ڼ��Ҫ�漰����̬���䵥�ڴ���С�����⡣��̬�������������ַ���
//1.�� д���С �Ĵ�С						����д��������ơ� 
//2.�� д���С �Ľ��ݴ�С					����д��������ơ� (����ǰ��϶�㹻 �� �� ֱ��д�룬������ �� ֱ�ӷ����¿ռ�)
//3.���һ������ش�С�ĺ�һ��2����С����	����ʡ�ռ���ơ�(Ŀǰ��׼����)(����ǰ��϶�㹻����ֱ��д�룬���������������д�����ٷ����¿ռ�)
//4.�̶�������С							����ʡ�ռ���ơ�(����ǰ��϶�㹻�����ֱ��д�룬���������д����Ȼ���ٷ����¿ռ�)

NS_TOOL_FRAME_BEGIN

class CStreamBuffer;
typedef CSharePtr<CStreamBuffer>			StreamBufferPtr;
typedef std::list<StreamBufferPtr>			ListStreamBufferPtr;

class CStreamBinary
	:public IStreamBase
{
public:
	enum 
	{
		ALLOC_WRITE_SIZE,			//д���С
		ALLOC_WRITE_POWER_SIZE,		//д���С�Ľ��ݴ�С
		ALLOC_BUFFER_POWER_SIZE,	//���һ������ص�2����С
		ALLOC_BLOCK_SIZE,			//�̶���С
	};
public:
	bool			SetAlloc(int eAlloc);						//���÷��䷽��
	bool			SetBlockSize(size_t uSize);					//���õ�Ԫ���С
	bool			Copy(const CStreamBinary& iStream);			//����
	StreamBufferPtr ToStreamBuffer();							//ת����StreamBuffer��(ȫ��)
	StreamBufferPtr ToStreamBuffer(size_t uLength);				//ת����StreamBuffer��(ָ������)
public:
	int				GetAlloc()const;							//��ȥ���䷽��
	size_t			GetBlockSize()const;						//��ȡ��Ԫ���С
public:
	bool			Splice(StreamBufferPtr& ptr,bool bBack =true);			//ƴ����(������ ��������ᱻֱ��ʹ���ڱ��࣬���޸�ԭ�� ������std::list��Splice
	bool			Splice(CStreamBinary& iStream, bool bBack = true);
	StreamBufferPtr	MoveToStreamBuffer();									//����ǰ���ƶ���StreamBuffer ���޸ĵ�ǰ����
	StreamBufferPtr ResetToStreamBuffer();									//�ڲ����������Ϊ����StreamBuffer;
	
	StreamBufferPtr	PopFrontBuffer();							//����ǰ��Buffer
public:
	virtual CStreamBinary&	operator =(const CStreamBinary& iStream);
public:
	virtual bool	Drop(size_t uSize)override;					//����ĩβ��ָ����С����
protected:
	virtual bool	_Read(size_t uCursor, void* pBuff, size_t uSize);			//��ȡ
	virtual bool	_Write(size_t uCursor, const void* pBuff, size_t uSize);	//д��
	virtual bool	_Insert(size_t uCursor, const void* pBuff, size_t uSize) ;	//����
	virtual bool	_Clear();
protected:
	virtual bool	DebugCheck()const;								//���ݼ��(������)
	virtual StreamBufferPtr	MallocBuffer(size_t uSize);				//�����¿ռ�
	virtual bool	FindBuffer(ListStreamBufferPtr::iterator& itrCursor, size_t& uCursorLess, size_t uCursor);//���ҵ�ǰָ��λ�����ڵĻ���أ������Ƿ��ҵ������������ҵ�ʱ�ĵ�����λ�ã��Լ� ʣ�� ָ��ƫ����
public:
	CStreamBinary();
	CStreamBinary(size_t uSizeMax);
	CStreamBinary(const void* pBuff, size_t uSizeMax);
	CStreamBinary(const void* pBuff, size_t uSizeMax, size_t uSizeUse);
	CStreamBinary(const StreamBufferPtr ptr);
	CStreamBinary(const StreamBufferPtr ptr, size_t uSizeMax);
	CStreamBinary(const CStreamBinary& iStream);
	virtual ~CStreamBinary();
protected:
	int							_eAlloc;
	size_t						_uBlockSize;//������Ԫ���С

	ListStreamBufferPtr			_vBuffer;
};

NS_TOOL_FRAME_END
