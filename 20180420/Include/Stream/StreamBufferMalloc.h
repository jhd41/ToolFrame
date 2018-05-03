#pragma once
#include "StreamBuffer.h"

NS_TOOL_FRAME_BEGIN
class CStreamBufferMalloc
	:public CStreamBuffer
{
public:
	bool				Copy(const CStreamBufferMalloc& iStream);	//¸´ÖÆ
	bool				Copy(const CStreamBuffer& iStream);	//¸´ÖÆ
public:
	virtual bool		Resize(size_t uSize);
	virtual char*		GetMallocBuffer()override;
	virtual const char*	GetMallocBuffer()const override;
public:
	virtual CStreamBufferMalloc& operator = (const CStreamBufferMalloc& iStream);
public:
	CStreamBufferMalloc(void);
	CStreamBufferMalloc(size_t uSizeMax);
	CStreamBufferMalloc(const void* pBuff,size_t uSizeUse);
	CStreamBufferMalloc(const void* pBuff,size_t uSizeMax,size_t uSizeUse);
	CStreamBufferMalloc(const CStreamBuffer& iStream);
	CStreamBufferMalloc(const CStreamBufferMalloc& iStream);
	virtual ~CStreamBufferMalloc(void);
};
NS_TOOL_FRAME_END
