#pragma once
#include "Macro.h"
#include "MacroDefineEx.h"
#include "IDataSession.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IMsgStream
	:public IDataSerialize
{
	//NO_COPY(IMsgStream);
	//逻辑层调用
public:
	UINT16			GetLength()const;
	UINT16			GetOpCode()const;
	bool			Load();
	bool			IsInvaild()const;	//无效
	bool			IsLoad()const;		//是否是读取
	
	//系统层调用(发送类函数)
public:
	StreamBinaryPtr	GetSendStream()const;					//获取发送数据缓冲
	StreamBinaryPtr	GetSendStream();						//获取发送数据缓冲
	static size_t	GetBodyLength(StreamBufferPtr ptr);		//获取身体长度
	static void* 	GetBodyBuffer(StreamBufferPtr ptr);		//获取身体数据指针

	//系统层调用(接收类函数)
public:
	StreamBinaryPtr	CloneLoadStream()const;	//复制一份源流
	bool			ResetLoadStream();		//重置读取流
	bool			LoadBegin();			//读取头
	bool			IsVaildBegin()const;	//是有效头
	size_t			GetBodyLength()const;	//获取身体长度
	StreamBufferPtr	ResetLoadStreamBuffer();
	bool			SetLoadStream(IStreamPtr ptr);

	IStreamPtr		GetStream()const;		//获取内部的数据流(外部不要轻易调用)
	static uint16	GetBeginLength();		//获取包头长度
protected:
	virtual bool	Save();
	virtual void	Serialize();
public:
	virtual bool	OnSerialize(IStreamPtr ptr)const;
	virtual bool	OnSerialize(IStreamPtr ptr);
public:
	IMsgStream(UINT16 uOpCode);//写
	IMsgStream(StreamBinaryPtr pStream);//读
	IMsgStream(const IMsgStream& msgStream,UINT16 uOpCode);//读
	IMsgStream(const IMsgStream& msgStream);				//拷贝构造函数
	virtual ~IMsgStream();
protected:
	UINT16 _uLength;
	UINT16 _uOpCode;
private:
	IStreamPtr		_pStreamLoad;	//加载流
	IStreamPtr		_pStream;		//序列化流
	size_t			_uLoadingCursor;//加载前指针位置
	bool			_bLoadBody;		//加载过身体的标记
};

NS_TOOL_FRAME_END

//创建消息构造函数
#define	MSG_CONSTRUCT(className,opCode)	className():IMsgStream(opCode){}className(const IMsgStream& msgStream):IMsgStream(msgStream,opCode){}virtual ~className(){}
//创建消息序列化函数(分步)
#define MSG_SERIALIZE_BEGIN					virtual void Serialize(){
#define MSG_SERIALIZE_ARG(msg)				*GetStream() & msg;
#define MSG_SERIALIZE_IF(opt,arg,msg)		if (arg == opt)*GetStream() & msg;
#define MSG_SERIALIZE_END					}

//创建消息序列化函数
#define MSG_SERIALIZE(msg)				MSG_SERIALIZE_BEGIN MSG_SERIALIZE_ARG(msg) MSG_SERIALIZE_END 
//同时创建消息构造函数以及序列化函数
#define MSG_CONSTRUCT_SERIALIZE(className,opCode,msg) MSG_CONSTRUCT(className,opCode) MSG_SERIALIZE(msg)
