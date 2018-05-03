#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"
#include "MacroDefineEx.h"
#include "ToolBoost.h"

//缓冲池 线程安全

NS_TOOL_FRAME_BEGIN

class CBufferStream
{
public:
	virtual bool IsInfiniteSize()const;					//是否是无限空间
	virtual bool SetSizeMax(size_t uSize);
	virtual bool PushFront(IStreamPtr ptr);
	virtual bool PushBack(IStreamPtr ptr);
	virtual IStreamPtr PopFront();
	virtual IStreamPtr PopBack();
	
	template<typename T>
	T PopFront();
	template<typename T>
	T PopBack();

	virtual bool Clear(ListStreamPtr& vBuffer);	//获取所有的Buffer并清理
	virtual bool Clear();
	virtual bool IsEmpty()const;						//是否为空
	virtual size_t GetCount()const;						//获取缓冲数
public:
	virtual size_t GetSizeMax()const;	//返回0 为无限
	virtual size_t GetSize()const;	//获取已使用的空间
public:
	virtual CBufferStream& operator = (const CBufferStream& xStream);
public:
	CBufferStream(void);
	CBufferStream(const CBufferStream& xStream);
	virtual ~CBufferStream(void);
private:
	mutable CMutexReadWrite	_mutex;
	ListStreamPtr			_vBuffer;
	size_t					_uSize;
	size_t					_uSizeMax;
};

template<typename T>
T CBufferStream::PopFront() {
	return ToolFrame::DynamicCast<T>(PopFront());
}
template<typename T>
T CBufferStream::PopBack() {
	return ToolFrame::DynamicCast<T>(PopBack());
}

NS_TOOL_FRAME_END
