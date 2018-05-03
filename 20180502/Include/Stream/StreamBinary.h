#pragma once
#include "IStreamBase.h"
#include "MacroDefineBoost.h"

//二进制数据流
//内部支持无限大的内存空间，期间就要涉及到动态分配单内存块大小的问题。动态分配有以下三种方案
//1.新 写入大小 的大小						面向写入性能设计。 
//2.新 写入大小 的阶梯大小					面向写入性能设计。 (若当前空隙足够 则 会 直接写入，若不够 则 直接分配新空间)
//3.最近一个缓冲池大小的后一个2倍大小阶梯	面向省空间设计。(目前标准常用)(若当前空隙足够，则直接写入，若不够，则会连续写满后，再分配新空间)
//4.固定常量大小							面向省空间设计。(若当前空隙足够，则会直接写入，若不够则会写满，然后再分配新空间)

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
		ALLOC_WRITE_SIZE,			//写入大小
		ALLOC_WRITE_POWER_SIZE,		//写入大小的阶梯大小
		ALLOC_BUFFER_POWER_SIZE,	//最近一个缓冲池的2倍大小
		ALLOC_BLOCK_SIZE,			//固定大小
	};
public:
	bool			SetAlloc(int eAlloc);						//设置分配方案
	bool			SetBlockSize(size_t uSize);					//设置单元块大小
	bool			Copy(const CStreamBinary& iStream);			//复制
	StreamBufferPtr ToStreamBuffer();							//转换成StreamBuffer流(全部)
	StreamBufferPtr ToStreamBuffer(size_t uLength);				//转换成StreamBuffer流(指定长度)
public:
	int				GetAlloc()const;							//后去分配方案
	size_t			GetBlockSize()const;						//获取单元块大小
public:
	bool			Splice(StreamBufferPtr& ptr,bool bBack =true);			//拼接流(高性能 传入的流会被直接使用于本类，会修改原流 类似于std::list的Splice
	bool			Splice(CStreamBinary& iStream, bool bBack = true);
	StreamBufferPtr	MoveToStreamBuffer();									//将当前流移动到StreamBuffer 会修改当前的流
	StreamBufferPtr ResetToStreamBuffer();									//内部缓冲池重置为单条StreamBuffer;
	
	StreamBufferPtr	PopFrontBuffer();							//弹出前端Buffer
public:
	virtual CStreamBinary&	operator =(const CStreamBinary& iStream);
public:
	virtual bool	Drop(size_t uSize)override;					//丢弃末尾的指定大小数据
protected:
	virtual bool	_Read(size_t uCursor, void* pBuff, size_t uSize);			//读取
	virtual bool	_Write(size_t uCursor, const void* pBuff, size_t uSize);	//写入
	virtual bool	_Insert(size_t uCursor, const void* pBuff, size_t uSize) ;	//插入
	virtual bool	_Clear();
protected:
	virtual bool	DebugCheck()const;								//数据检查(调试用)
	virtual StreamBufferPtr	MallocBuffer(size_t uSize);				//分配新空间
	virtual bool	FindBuffer(ListStreamBufferPtr::iterator& itrCursor, size_t& uCursorLess, size_t uCursor);//查找当前指针位置所在的缓冲池，返回是否找到，参数表返回找到时的迭代器位置，以及 剩余 指针偏移量
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
	size_t						_uBlockSize;//常量单元块大小

	ListStreamBufferPtr			_vBuffer;
};

NS_TOOL_FRAME_END
