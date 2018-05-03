#include "StreamBufferMalloc.h"
#include "MMemory.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN
CStreamBufferMalloc::CStreamBufferMalloc(void)
{
}

CStreamBufferMalloc::CStreamBufferMalloc( size_t uSizeMax )
:CStreamBuffer(uSizeMax)
{

}

CStreamBufferMalloc::CStreamBufferMalloc( const void* pBuff,size_t uSizeUse )
:CStreamBuffer(uSizeUse)
{
	if (pBuff && uSizeUse>0)
	{
		GetMallocBuffer();
		Write(pBuff,uSizeUse);
	}
}

CStreamBufferMalloc::CStreamBufferMalloc( const void* pBuff,size_t uSizeMax,size_t uSizeUse )
:CStreamBuffer(uSizeMax)
{
	if (pBuff && uSizeUse>0)
	{
		GetMallocBuffer();
		Write(pBuff,uSizeUse);
	}
}

CStreamBufferMalloc::CStreamBufferMalloc( const CStreamBufferMalloc& iStream )
{
	if (!Copy(iStream))
		SetError();
}

CStreamBufferMalloc::CStreamBufferMalloc(const CStreamBuffer& iStream)
{
	if (!Copy(iStream))
		SetError();
}

CStreamBufferMalloc::~CStreamBufferMalloc(void)
{
	//删除空指针是安全的
	if (_pBuffer)
	{
		MMemory::Singleton().Free(_pBuffer,false);
		_pBuffer = nullptr;
	}
}

bool CStreamBufferMalloc::Resize( size_t uSize )
{
	//调整内存
	if (_pBuffer)
	{
		MMemory::Singleton().Free(_pBuffer,false);
		_pBuffer = nullptr;
	}

	return CStreamBuffer::Resize(uSize);
}

char* CStreamBufferMalloc::GetMallocBuffer()
{
	if (!_pBuffer)
	{
		ASSERT_LOG_ERROR(GetMaxSize() > 0);
		_pBuffer = (char*)MMemory::Singleton().Malloc(GetMaxSize(), false);
	}
	return CStreamBuffer::GetMallocBuffer();
}

const char* CStreamBufferMalloc::GetMallocBuffer() const
{
	return CStreamBuffer::GetMallocBuffer();
}

CStreamBufferMalloc& CStreamBufferMalloc::operator=(const CStreamBufferMalloc& iStream)
{
	if (ToolFrame::IsSelf(*this,iStream))return *this;

	if (!Copy(iStream))
		SetError();

	return *this;
}

bool CStreamBufferMalloc::Copy( const CStreamBufferMalloc& iStream )
{
	if (!Resize(iStream.GetMaxSize()))return false;
	if (nullptr == GetMallocBuffer())return false;
	if (!CStreamBuffer::Write(iStream.GetMallocBuffer(),iStream.GetSize()))return false;
	return IStreamBase::Copy(iStream);
}

bool CStreamBufferMalloc::Copy(const CStreamBuffer& iStream)
{
	if (!Resize(iStream.GetMaxSize()))return false;
	if (nullptr == GetMallocBuffer())return false;
	if (!CStreamBuffer::Write(iStream.GetMallocBuffer(), iStream.GetSize()))return false;
	return IStreamBase::Copy(iStream);
}

NS_TOOL_FRAME_END
