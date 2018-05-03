#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"
#include "MacroDefineEx.h"
#include "ToolBoost.h"

//����� �̰߳�ȫ

NS_TOOL_FRAME_BEGIN

class CBufferStream
{
public:
	virtual bool IsInfiniteSize()const;					//�Ƿ������޿ռ�
	virtual bool SetSizeMax(size_t uSize);
	virtual bool PushFront(IStreamPtr ptr);
	virtual bool PushBack(IStreamPtr ptr);
	virtual IStreamPtr PopFront();
	virtual IStreamPtr PopBack();
	
	template<typename T>
	T PopFront();
	template<typename T>
	T PopBack();

	virtual bool Clear(ListStreamPtr& vBuffer);	//��ȡ���е�Buffer������
	virtual bool Clear();
	virtual bool IsEmpty()const;						//�Ƿ�Ϊ��
	virtual size_t GetCount()const;						//��ȡ������
public:
	virtual size_t GetSizeMax()const;	//����0 Ϊ����
	virtual size_t GetSize()const;	//��ȡ��ʹ�õĿռ�
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
