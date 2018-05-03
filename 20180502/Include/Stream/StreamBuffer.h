#pragma once
#include "IStreamBase.h"

NS_TOOL_FRAME_BEGIN
class CStreamBuffer
	:public IStreamBase
{
	//����ӿ�
public:
	virtual const char* GetBuffer(size_t uCursor)const;					//��ȡָ��λ�õ�ָ��
	virtual char*		GetBuffer(size_t uCursor);						//��ȡָ��λ�õ�ָ��

	virtual const char*	GetBuffer()const;
	virtual char*		GetBuffer();									//��ȡ��ȡ�α�λ��ָ��
	
	virtual char*		GetWriteBuffer()const;
	virtual char*		GetWriteBuffer();								//��ȡд���α�λ��ָ��
	
	virtual char*		GetUnusedBuffer();								//��û�δʹ�ÿռ�Ļ������
	virtual char*		GetMallocBuffer();								//��ȡ�������ڴ�ռ��׵�ַ
	virtual const char* GetMallocBuffer()const;

	virtual bool		Copy(const CStreamBuffer& iStream);

	virtual bool		IsEqual(const CStreamBuffer& iStream)const;		//�Ƿ����(���ݲ���)
	virtual bool		CloneData(const CStreamBuffer& iStream);		//�������ݵ�����������ͬ��
	
	virtual bool		TrimBuffer();									//�������� ʹ�������յ�պ�����Ч���ݵ�����յ�																	//����ӿ�
public:
	virtual	size_t		WriteSome(const void* pBuff, size_t uSize)override;		//�洢 ���α괦��ʼ(����Ȩ�޿��� )
	virtual	size_t		ReadSome(void* pBuff, size_t uSize)override;			//��ȡ ���α괦��ʼ(����Ȩ�޿���)
protected:
	virtual bool	_Read(size_t uCursor, void* pBuff, size_t uSize);			//��ȡ
	virtual bool	_Write(size_t uCursor, const void* pBuff, size_t uSize) ;	//д��
	virtual bool	_Insert(size_t uCursor, const void* pBuff, size_t uSize);	//����
	virtual	bool	_Write(IStreamBase& stream, size_t uSize);					//�洢 ���α괦��ʼ
public:
	virtual CStreamBuffer& operator =(const CStreamBuffer& buffer);
public:
	CStreamBuffer(void);

	//��д
	CStreamBuffer(size_t uSizeMax);
	CStreamBuffer(void* pBuff,size_t uSizeMax);
	CStreamBuffer(void* pBuff,size_t uSizeMax,size_t uSizeUse);

	//ֻ��
	CStreamBuffer(const void* const pBuff,size_t uSizeUse);
	CStreamBuffer(const void* const pBuff,size_t uSizeMax,size_t uSizeUse);

	//��������
	CStreamBuffer(const CStreamBuffer& buffer);
	virtual ~CStreamBuffer(void);
protected:
	char* _pBuffer;
};
NS_TOOL_FRAME_END

