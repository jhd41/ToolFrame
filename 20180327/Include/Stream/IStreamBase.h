#pragma once
#include "Macro.h"

//����:���д洢������Ķ�������
//��Ч����:�ӵ�ǰ�α꿪ʼ���𵽽�β�����ݳ�Ϊ��Ч����
//�ڲ����� �������α�λ�ý��в���
//�α����������� ���α꣬�� д�α꣬�������� Ĭ�� ��ȡ д��ʱ���λ��
//���Ĵ�С����
//��Ч��С �� д�α� ��ȥ ���α�� ��Ч�ռ䣬Ĭ�ϵ��ж϶��ǻ��������ж�
//���ݴ�С �� ��д�α�û�й�ϵ���ڲ������0 �� �յ� �ܹ�ӵ�е����ݴ�С

NS_TOOL_FRAME_BEGIN
class IStreamBase
{
public:
	//����������
	enum EStreamDirection
	{
		STREAM_INVAILD = INVALID_ID,
		STREAM_INPUT,
		STREAM_OUTPUT,
		STREAM_MAX,
	};
	//��������
public:
	virtual	bool	IsEmpty()const;								//�Ƿ�Ϊ��(��Ч����)
	virtual bool	IsFull()const;								//����(��Ч����)
	virtual size_t	GetLength()const;							//��ȡ��Ч���ݳ���
	virtual bool	Skip(int nOffset);							//����ָ������(�ƶ�ֻ��ָ��)
	virtual bool	IsReadable();								//�Ƿ�ɶ�
	virtual	bool	IsWriteable();								//�Ƿ��д
	virtual	bool	IsVaildCursor(size_t uCursor)const;			//�Ƿ�����Ч�α�
	virtual bool	IsTrimed()const;							//�Ƿ����(�ڲ�������ȫ��δ��ȡ)

	virtual bool	IsDataEmpty()const;							//�����Ƿ�Ϊ��
	virtual bool	IsDataFull()const;							//�����Ƿ�����
	virtual	size_t	GetSize()const;								//��ȡ�����ܳ���
	virtual size_t	GetUnusedSize()const;						//���㻹δʹ�õĿռ��С
	virtual bool	Drop(size_t uSize);							//����ĩβ��ָ����С����
	//��������
public:
	virtual bool	Resize(size_t uSize);						//���·���ռ�
	virtual bool	Clear();									//�����
	virtual	bool	Read(void* pBuff, size_t uSize);			//��ȡ ���α괦��ʼ(����Ȩ�޿���)
	virtual	bool	Write(const void* pBuff, size_t uSize);		//�洢 ���α괦��ʼ(����Ȩ�޿��� )
	virtual	bool	Write(IStreamBase& stream, size_t uSize);	//�洢 ���α괦��ʼ(����Ȩ�޿���)
	virtual	bool	Write(IStreamBase& stream);
	virtual	size_t	WriteSome(const void* pBuff, size_t uSize);	//�洢 ���α괦��ʼ(����Ȩ�޿��� )	����д���˶����ֽ�
	virtual	size_t	ReadSome(void* pBuff, size_t uSize);		//��ȡ ���α괦��ʼ(����Ȩ�޿���)	���ض�ȡ�˶����ֽ�
	virtual	bool	Insert(size_t uCursor,const void* pBuff, size_t uSize);//���� ��ָ���α괦��ʼ(����Ȩ�޿���)
	virtual bool	Modify(size_t uCursor,const void* pBuff, size_t uSize);//�޸� �޸�ָ���α�λ�õ�����(����Ȩ�޿���)

	//�α����
public:
	virtual	bool	SkipReadCursor(int nOffset,bool bFix = true);	//���ö�ȡ�α���Ծָ����λ(����������� �� �Զ�����)
	virtual	bool	SkipWriteCursor(int nOffset, bool bFix = true);	//����д���α���Ծָ����λ
	virtual bool	SetReadCursorBegin();							//���ö�ȡ�α������ݿ�ͷ
	virtual bool	SetWriteCursorEnd();							//����д���α�������ĩβ
	virtual bool	IsReadCursorBegin()const;						//�Ƿ��ȡ�α������ݿ�ͷ
	virtual bool	IsWriteCursorEnd()const;						//�Ƿ�д���α�������ĩβ
	virtual bool	ResetCursor();									//�����α�(���α��ڿ����ݿ�ͷ��д�α������ݽ�β)

	//�������
public:
	virtual	void	SetError();									//���ó���
	virtual	bool	IsError()const;								//�ж��Ƿ����
	virtual	void	ClearError();								//�������

	virtual bool	Copy(const IStreamBase& stream);			//���ƻ�������
	virtual bool	Reset();									//���û�������

	//�ⲿ��Ҫʹ��
public:
	virtual bool	SetSize(size_t uSize);						//�������ݳ���
protected:
	virtual bool	DebugCheck()const;							//���ݼ��(������)
protected:
	virtual bool	_Read(size_t uCursor, void* pBuff,size_t uSize)=0;				//��ȡ
	virtual bool	_Write(size_t uCursor, const void* pBuff, size_t uSize) = 0;	//д��
	virtual bool	_Insert(size_t uCursor, const void* pBuff, size_t uSize) = 0;	//����
	virtual bool	_Clear();														//���
	virtual	bool	_Write(IStreamBase& stream, size_t uSize);						//�洢 ���α괦��ʼ
public:
	virtual IStreamBase& operator =(const IStreamBase& iStream);
public:
	IStreamBase(void);
	virtual ~IStreamBase(void);
private:
	CFIELD_INT(Direction);
	CFIELD_BOOL(ReadOnly);		//ֻ��
	CFIELD_BOOL(WriteOnly);		//ֻд
	CFIELD_SIZE(ReadCursor);	//���α�(Ĭ��0)
	CFIELD_SIZE(WriteCursor);	//д�α�(Ĭ��0)
	CFIELD_INT(UserInt);		//�û��Զ�������
	CFIELD_STRING(UserString);	//�û��Զ�������
	CFIELD_SIZE(MaxSize);		//���ߴ�
protected:
	bool		_bError;	//������
	size_t		_uSize;		//���ݳ���
};
NS_TOOL_FRAME_END
