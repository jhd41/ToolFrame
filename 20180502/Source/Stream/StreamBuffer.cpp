#include "StreamBuffer.h"
#include "ToolStd.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN
CStreamBuffer::CStreamBuffer(void)
{
	_pBuffer = nullptr;
}

CStreamBuffer::CStreamBuffer( size_t uSizeMax )
{
	_pBuffer = nullptr;

	SetMaxSize(uSizeMax);
}

CStreamBuffer::CStreamBuffer( void* pBuff,size_t uSizeMax )
{
	_pBuffer = (char*)pBuff;

	SetMaxSize(uSizeMax);
	SetSize(uSizeMax);
	SetWriteCursor(uSizeMax);
}

CStreamBuffer::CStreamBuffer( void* pBuff,size_t uSizeMax,size_t uSizeUse )
{
	_pBuffer = (char*)pBuff;

	SetMaxSize(uSizeMax);
	SetSize(uSizeUse);
	SetWriteCursor(uSizeUse);
}

CStreamBuffer::CStreamBuffer( const CStreamBuffer& buffer )
{
	*this = buffer;
}

CStreamBuffer::CStreamBuffer(const void* const pBuff,size_t uSizeUse )
{
	_pBuffer = (char*)pBuff;
	SetReadOnly(true);

	SetMaxSize(uSizeUse);
	SetSize(uSizeUse);
	SetWriteCursor(uSizeUse);
}

CStreamBuffer::CStreamBuffer(const void* const pBuff,size_t uSizeMax,size_t uSizeUse )
{
	ASSERT_LOG_ERROR(uSizeMax>0);

	_pBuffer = (char*)pBuff;
	SetReadOnly(true);

	SetMaxSize(uSizeMax);
	SetSize(uSizeUse);
	SetWriteCursor(uSizeUse);
}

CStreamBuffer::~CStreamBuffer(void)
{
}

char* CStreamBuffer::GetUnusedBuffer()
{
	char* pBuffer = (char*)GetMallocBuffer();
	ASSERT_LOG_ERROR(pBuffer);

	return &pBuffer[GetSize()];
}

char* CStreamBuffer::GetMallocBuffer()
{
	if (GetMaxSize() <= 0)return nullptr;

	ASSERT_LOG_ERROR(_pBuffer);
	return _pBuffer;
}

const char* CStreamBuffer::GetMallocBuffer() const
{
	return ToolFrame::ConstCast(this)->GetBuffer();
}

size_t CStreamBuffer::WriteSome(const void* pBuff, size_t uSize)
{
	if (uSize <= 0)return 0;
	if (!pBuff)return 0;
	
	if (!IsWriteable())return 0;
	if (IsFull())return 0;

	size_t uWrite = ToolFrame::Min(GetMaxSize() - GetWriteCursor(), uSize);	//计算能够写入的长度
	size_t uCursor = GetWriteCursor() + uWrite;								//计算新游标位置
	size_t uNewSize = ToolFrame::Max(GetWriteCursor() + uWrite, GetSize());	//计算新大小

	if (!ToolFrame::MemCopyPtr(GetWriteBuffer(), pBuff, uWrite))return 0;

	SetWriteCursor(uCursor);
	SetSize(uNewSize);

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return uWrite;
}

char* CStreamBuffer::GetBuffer()
{
	return GetBuffer(GetReadCursor());
}

const char* CStreamBuffer::GetBuffer() const
{
	return ToolFrame::ConstCast(this)->GetBuffer();
}

char* CStreamBuffer::GetBuffer(size_t uCursor)
{
	if (uCursor >= GetMaxSize())return nullptr;

	char* pBuffer = GetMallocBuffer();
	ASSERT_LOG_ERROR(pBuffer);
	if (!pBuffer)return nullptr;
	return &pBuffer[uCursor];//计算游标的偏移量
}

const char* CStreamBuffer::GetBuffer(size_t uCursor) const
{
	return ToolFrame::ConstCast(this)->GetBuffer(uCursor);
}

char* CStreamBuffer::GetWriteBuffer() const
{
	return ToolFrame::ConstCast(this)->GetWriteBuffer();
}

char* CStreamBuffer::GetWriteBuffer()
{
	if (IsFull())return nullptr;

	return GetBuffer(GetWriteCursor());
}

bool CStreamBuffer::_Insert(size_t uCursor, const void* pBuff, size_t uSize)
{
	char* pBufferCur = GetBuffer(uCursor);
	if (!pBufferCur)return false;

	//所有的数据往后偏移
	if (!ToolFrame::MemCopyPtr(&pBufferCur[uSize], pBufferCur, GetSize()- uCursor))return false;

	//覆盖数据
	return ToolFrame::MemCopyPtr(pBufferCur, pBuff, uSize);
}

bool CStreamBuffer::_Read(size_t uCursor, void* pBuff, size_t uSize)
{
	char* pBufferCur = GetBuffer(uCursor);
	if (!pBufferCur)return false;

	return ToolFrame::MemCopyPtr(pBuff,pBufferCur, uSize);
}

bool CStreamBuffer::_Write(size_t uCursor, const void* pBuff, size_t uSize)
{
	char* pBufferCur = GetBuffer(uCursor);
	if (!pBufferCur)return false;

	return ToolFrame::MemCopyPtr(pBufferCur, pBuff, uSize);
}

bool CStreamBuffer::_Write(IStreamBase& stream, size_t uSize)
{
	return stream.Read(GetWriteBuffer(), uSize);
}

bool CStreamBuffer::Copy(const CStreamBuffer& iStream)
{
	if (ToolFrame::IsSelf(*this, iStream))return false;

	_pBuffer = iStream._pBuffer;
	
	ASSERT_LOG_ERROR(IStreamBase::Copy(iStream));

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return true;
}

bool CStreamBuffer::IsEqual(const CStreamBuffer& iStream) const
{
	if (GetLength() != iStream.GetLength())return false;
	if (GetLength() == 0)return true;
	return ToolFrame::MemCmp(GetBuffer(),GetLength(), iStream.GetBuffer(), iStream.GetLength());
}

bool CStreamBuffer::CloneData(const CStreamBuffer& iStream)
{
	if (iStream.IsEmpty())return false;
	if (nullptr == GetMallocBuffer())return false;
	if (!CStreamBuffer::Write(iStream.GetMallocBuffer(), iStream.GetSize()))return false;
	SetWriteCursor(iStream.GetWriteCursor());
	SetReadCursor(iStream.GetReadCursor());

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return true;
}

bool CStreamBuffer::TrimBuffer()
{
	if (!IsWriteable())return false;
	if (IsTrimed())return true;

	if (IsEmpty())
	{
		SetSize(0);
		ResetCursor();
		ASSERT_LOG_DEBUG_ERR(DebugCheck());
		return true;
	}

	if (!IsReadCursorBegin())
	{
		char* pBuffer = GetMallocBuffer();
		if (!pBuffer)return false;

		size_t uLength = GetLength();

		//所有的数据偏移
		ASSERT_LOG_ERROR(ToolFrame::MemCopyPtr(pBuffer, &pBuffer[GetReadCursor()], uLength));

		SetSize(uLength);
		ResetCursor();
	
		ASSERT_LOG_DEBUG_ERR(GetSize() == GetLength());
		ASSERT_LOG_DEBUG_ERR(DebugCheck());
		return true;
	}
	
	//后半部分数据进行丢弃
	if (GetSize() < GetWriteCursor())return false;
	
	Drop(GetSize() - GetWriteCursor());

	ASSERT_LOG_DEBUG_ERR(GetSize() == GetLength());

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return true;
}

CStreamBuffer& CStreamBuffer::operator=(const CStreamBuffer& buffer)
{
	Copy(buffer);
	return *this;
}

size_t CStreamBuffer::ReadSome(void* pBuff, size_t uSize)
{
	if (!IsReadable())return 0;

	if (0 == uSize)return 0;
	if (!pBuff)return 0;

	if (IsEmpty())return 0;

	size_t uRead = ToolFrame::Min(GetLength(), uSize);	//计算能够写入的长度
	size_t uCursor = GetReadCursor() + uRead;				//计算新游标位置
	
	if (!ToolFrame::MemCopyPtr(pBuff, GetBuffer(), uRead))return 0;

	SetReadCursor(uCursor);

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return uRead;
}

NS_TOOL_FRAME_END

