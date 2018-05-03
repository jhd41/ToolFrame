#pragma once
#include "IStreamBase.h"

NS_TOOL_FRAME_BEGIN
class CStreamBuffer
	:public IStreamBase
{
	//子类接口
public:
	virtual const char* GetBuffer(size_t uCursor)const;					//获取指定位置的指针
	virtual char*		GetBuffer(size_t uCursor);						//获取指定位置的指针

	virtual const char*	GetBuffer()const;
	virtual char*		GetBuffer();									//获取读取游标位置指针
	
	virtual char*		GetWriteBuffer()const;
	virtual char*		GetWriteBuffer();								//获取写入游标位置指针
	
	virtual char*		GetUnusedBuffer();								//获得还未使用空间的缓存起点
	virtual char*		GetMallocBuffer();								//获取真正的内存空间首地址
	virtual const char* GetMallocBuffer()const;

	virtual bool		Copy(const CStreamBuffer& iStream);

	virtual bool		IsEqual(const CStreamBuffer& iStream)const;		//是否相等(数据部分)
	virtual bool		CloneData(const CStreamBuffer& iStream);		//复制数据到本地设置相同的
	
	virtual bool		TrimBuffer();									//规整化流 使得起点和终点刚好是有效数据的起点终点																	//父类接口
public:
	virtual	size_t		WriteSome(const void* pBuff, size_t uSize)override;		//存储 从游标处开始(加入权限控制 )
	virtual	size_t		ReadSome(void* pBuff, size_t uSize)override;			//读取 从游标处开始(加入权限控制)
protected:
	virtual bool	_Read(size_t uCursor, void* pBuff, size_t uSize);			//读取
	virtual bool	_Write(size_t uCursor, const void* pBuff, size_t uSize) ;	//写入
	virtual bool	_Insert(size_t uCursor, const void* pBuff, size_t uSize);	//插入
	virtual	bool	_Write(IStreamBase& stream, size_t uSize);					//存储 从游标处开始
public:
	virtual CStreamBuffer& operator =(const CStreamBuffer& buffer);
public:
	CStreamBuffer(void);

	//读写
	CStreamBuffer(size_t uSizeMax);
	CStreamBuffer(void* pBuff,size_t uSizeMax);
	CStreamBuffer(void* pBuff,size_t uSizeMax,size_t uSizeUse);

	//只读
	CStreamBuffer(const void* const pBuff,size_t uSizeUse);
	CStreamBuffer(const void* const pBuff,size_t uSizeMax,size_t uSizeUse);

	//拷贝构造
	CStreamBuffer(const CStreamBuffer& buffer);
	virtual ~CStreamBuffer(void);
protected:
	char* _pBuffer;
};
NS_TOOL_FRAME_END

