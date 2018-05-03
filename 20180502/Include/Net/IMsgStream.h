#pragma once
#include "Macro.h"
#include "MacroDefineEx.h"
#include "IDataSession.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IMsgStream
	:public IDataSerialize
{
	//NO_COPY(IMsgStream);
	//�߼������
public:
	UINT16			GetLength()const;
	UINT16			GetOpCode()const;
	bool			Load();
	bool			IsInvaild()const;	//��Ч
	bool			IsLoad()const;		//�Ƿ��Ƕ�ȡ
	
	//ϵͳ�����(�����ຯ��)
public:
	StreamBinaryPtr	GetSendStream()const;					//��ȡ�������ݻ���
	StreamBinaryPtr	GetSendStream();						//��ȡ�������ݻ���
	static size_t	GetBodyLength(StreamBufferPtr ptr);		//��ȡ���峤��
	static void* 	GetBodyBuffer(StreamBufferPtr ptr);		//��ȡ��������ָ��

	//ϵͳ�����(�����ຯ��)
public:
	StreamBinaryPtr	CloneLoadStream()const;	//����һ��Դ��
	bool			ResetLoadStream();		//���ö�ȡ��
	bool			LoadBegin();			//��ȡͷ
	bool			IsVaildBegin()const;	//����Чͷ
	size_t			GetBodyLength()const;	//��ȡ���峤��
	StreamBufferPtr	ResetLoadStreamBuffer();
	bool			SetLoadStream(IStreamPtr ptr);

	IStreamPtr		GetStream()const;		//��ȡ�ڲ���������(�ⲿ��Ҫ���׵���)
	static uint16	GetBeginLength();		//��ȡ��ͷ����
protected:
	virtual bool	Save();
	virtual void	Serialize();
public:
	virtual bool	OnSerialize(IStreamPtr ptr)const;
	virtual bool	OnSerialize(IStreamPtr ptr);
public:
	IMsgStream(UINT16 uOpCode);//д
	IMsgStream(StreamBinaryPtr pStream);//��
	IMsgStream(const IMsgStream& msgStream,UINT16 uOpCode);//��
	IMsgStream(const IMsgStream& msgStream);				//�������캯��
	virtual ~IMsgStream();
protected:
	UINT16 _uLength;
	UINT16 _uOpCode;
private:
	IStreamPtr		_pStreamLoad;	//������
	IStreamPtr		_pStream;		//���л���
	size_t			_uLoadingCursor;//����ǰָ��λ��
	bool			_bLoadBody;		//���ع�����ı��
};

NS_TOOL_FRAME_END

//������Ϣ���캯��
#define	MSG_CONSTRUCT(className,opCode)	className():IMsgStream(opCode){}className(const IMsgStream& msgStream):IMsgStream(msgStream,opCode){}virtual ~className(){}
//������Ϣ���л�����(�ֲ�)
#define MSG_SERIALIZE_BEGIN					virtual void Serialize(){
#define MSG_SERIALIZE_ARG(msg)				*GetStream() & msg;
#define MSG_SERIALIZE_IF(opt,arg,msg)		if (arg == opt)*GetStream() & msg;
#define MSG_SERIALIZE_END					}

//������Ϣ���л�����
#define MSG_SERIALIZE(msg)				MSG_SERIALIZE_BEGIN MSG_SERIALIZE_ARG(msg) MSG_SERIALIZE_END 
//ͬʱ������Ϣ���캯���Լ����л�����
#define MSG_CONSTRUCT_SERIALIZE(className,opCode,msg) MSG_CONSTRUCT(className,opCode) MSG_SERIALIZE(msg)
