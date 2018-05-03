#include "IStreamBase.h"
#include "ToolFrame.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

IStreamBase::IStreamBase(void)
{
	_bError = false;
	_uSize = 0;
	
	SetDirection(STREAM_INVAILD);
	SetReadOnly(false);
	SetWriteOnly(false);
	SetReadCursor(0);
	SetWriteCursor(0);
	SetUserInt(0);
	SetMaxSize(0);
}

IStreamBase::~IStreamBase(void)
{
}

void IStreamBase::SetError()
{
	_bError = true;
}

bool IStreamBase::IsError() const
{
	return _bError;
}

void IStreamBase::ClearError()
{
	_bError = false;
}

bool IStreamBase::Copy(const IStreamBase& stream)
{
	SetDirection	(stream.GetDirection());
	SetReadOnly		(stream.IsReadOnly());
	SetWriteOnly	(stream.IsWriteOnly());
	SetReadCursor	(stream.GetReadCursor());
	SetWriteCursor	(stream.GetWriteCursor());
	SetUserInt		(stream.GetUserInt());
	SetUserString	(stream.GetUserString());
	SetMaxSize		(stream.GetMaxSize());

	_bError = stream._bError;
	_uSize = stream._uSize;
	return true;
}

bool IStreamBase::Reset()
{
	SetReadCursor(0);
	SetWriteCursor(0);
	return true;
}

IStreamBase& IStreamBase::operator=(const IStreamBase& iStream)
{
	return *this;
}

bool IStreamBase::Write(const void* pBuff, size_t uSize)
{
	if (!IsWriteable())return false;
	if (IsError())return false;
	
	if (uSize <= 0)return true;
	if (!pBuff)return false;

	if (IsFull())return false;
	
	size_t uSizeUsed = GetWriteCursor() + uSize;
	if (uSizeUsed > GetMaxSize())return false;

	if (GetWriteCursor() > GetSize())return false;//游标位置允许在流任意处 以及 末尾

	size_t uCursor = GetWriteCursor() + uSize;//计算新游标位置
	size_t uNewSize = ToolFrame::Max(GetWriteCursor() + uSize,GetSize());//计算新大小

	if (!_Write(GetWriteCursor(),pBuff, uSize))return false;
	
	SetSize(uNewSize);
	SetWriteCursor(uCursor);
	
	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return true;
}

bool IStreamBase::Write(IStreamBase& stream)
{
	return Write(stream, stream.GetLength());
}

bool IStreamBase::Write(IStreamBase& stream, size_t uSize)
{
	if (!IsWriteable())return false;
	if (IsError())return false;

	//判断传入流是否正确
	if (uSize <= 0)return true;
	if (stream.IsError())return false;
	if (stream.GetLength() < uSize)return false;
	if (!stream.IsReadable())return false;

	if (IsFull())return false;

	size_t uSizeUsed = GetWriteCursor() + uSize;
	if (uSizeUsed > GetMaxSize())return false;
	
	if (GetWriteCursor() > GetSize())return false;//游标位置允许在流任意处 以及 末尾

	size_t uCursor = GetWriteCursor() + uSize;//计算新游标位置
	size_t uNewSize = ToolFrame::Max(GetWriteCursor() + uSize, GetSize());//计算新大小

	if (!_Write(stream, uSize))return false;

	SetSize(uNewSize);
	SetWriteCursor(uCursor);
	
	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return true;
}

bool IStreamBase::_Write(IStreamBase& stream, size_t uSize)
{
	char ch = 0;

	size_t uReadCursor = stream.GetReadCursor();
	size_t uWriteCursor = GetWriteCursor();
	for (uint uIndex = 0; uIndex < uSize; ++uIndex)
	{
		ASSERT_LOG_ERROR(stream._Read(uReadCursor + uIndex, &ch, sizeof(ch)));
		ASSERT_LOG_ERROR(_Write(uWriteCursor + uIndex, &ch, sizeof(ch)));
	}
	stream.SetReadCursor(uReadCursor + uSize);
	return true;
}

size_t IStreamBase::WriteSome(const void* pBuff, size_t uSize)
{
	if (!IsWriteable())return 0;
	if (IsError())return 0;

	if (uSize <= 0)return 0;
	if (!pBuff)return 0;
	
	if (IsFull())return 0;

	uint uCount = 0;
	const char* pChar = (const char*)pBuff;

	for (uint uIndex = 0; uIndex < uSize;++uIndex) {
		if (!Write(pChar, 1))
			return uCount;
		++pChar;
		++uCount;
	}

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return uCount;
}

size_t IStreamBase::ReadSome(void* pBuff, size_t uSize)
{
	if (!IsReadable())return false;
	if (IsError())return false;

	if (0 == uSize)return true;
	if (!pBuff)return false;

	if (IsEmpty())return 0;

	uint uCount = 0;
	char* pChar = (char*)pBuff;

	for (uint uIndex = 0; uIndex < uSize; ++uIndex) {
		if (!Read(pChar, 1))
			return uCount;
		++pChar;
		++uCount;
	}

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return uCount;
}

bool IStreamBase::Insert(size_t uCursor, const void* pBuff, size_t uSize)
{
	if (!IsWriteable())return false;
	if (IsError())return false;

	if (uSize <= 0)return true;
	if (!pBuff)return false;

	//如果写在末尾 则如同 写入
	if (GetWriteCursor() == uCursor)
		return Write(pBuff, uSize);

	if (IsFull())return false;

	size_t uSizeUsed = GetSize() + uSize;
	if (uSizeUsed > GetMaxSize())return false;

	if (uCursor >= GetSize())return false;//游标位置允许在流任意处

	size_t uNewCursor = uCursor <= GetWriteCursor() ? GetWriteCursor() + uSize: GetWriteCursor();//计算新游标位置
	size_t uNewSize	= ToolFrame::Max(GetWriteCursor() + uSize, GetSize());//计算新大小

	if (!_Insert(uCursor,pBuff, uSize))return false;

	SetWriteCursor(uNewCursor);
	SetSize(uNewSize);

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return true;
}

bool IStreamBase::Modify(size_t uCursor, const void* pBuff, size_t uSize)
{
	if (!IsWriteable())return false;
	if (IsError())return false;

	if (!pBuff)return false;

	size_t uNewSize = ToolFrame::Max(uCursor + uSize, GetSize());
	if (uNewSize > GetMaxSize())return false;

	if (uSize <= 0)return true;
		
	size_t uWriteCursor = GetWriteCursor();//保存原始位置
	SetWriteCursor(uCursor);

	bool bSucceed = Write(pBuff, uSize);

	SetWriteCursor(uWriteCursor);//还原
	SetSize(uNewSize);

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return bSucceed;
}

bool IStreamBase::SkipReadCursor(int nOffset, bool bFix /*= true*/)
{
	size_t uCursor = 0;
	if (!ToolFrame::Offset(uCursor, GetReadCursor(), nOffset, 0, GetSize(), bFix))return false;
	SetReadCursor(uCursor);
	return true;
}

bool IStreamBase::SkipWriteCursor(int nOffset, bool bFix /*= true*/)
{
	size_t uCursor = 0;
	if (!ToolFrame::Offset(uCursor,GetWriteCursor(), nOffset, 0, GetSize(), bFix))return false;
	SetWriteCursor(uCursor);
	return true;
}

bool IStreamBase::SetReadCursorBegin()
{
	return SetReadCursor(0);
}

bool IStreamBase::SetWriteCursorEnd()
{
	return SetWriteCursor(GetSize());
}

bool IStreamBase::IsReadCursorBegin()const
{
	return GetReadCursor() == 0;
}

bool IStreamBase::IsWriteCursorEnd()const
{
	return GetWriteCursor() == GetSize();
}

bool IStreamBase::ResetCursor()
{
	SetReadCursorBegin();
	SetWriteCursorEnd();
	return true;
}

bool IStreamBase::Read(void* pBuff, size_t uSize)
{
	if (!IsReadable())return false;
	if (IsError())return false;
	
	if (0 == uSize)return true;
	if (!pBuff)return false;

	if (IsEmpty())return false;

	size_t uCursor = GetReadCursor() + uSize;
	if (uCursor > GetSize())return false;
	if (!_Read(GetReadCursor(),pBuff, uSize))return false;

	SetReadCursor(uCursor);

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return true;
}

bool IStreamBase::IsEmpty() const
{
	return GetReadCursor() >= GetWriteCursor();
}

bool IStreamBase::Clear()
{
	if (!IsWriteable())return false;

	if (!_Clear())return false;

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return true;
}

size_t IStreamBase::GetLength() const
{
	if (GetReadCursor() >= GetWriteCursor())return 0;

	return GetWriteCursor() - GetReadCursor();
}

bool IStreamBase::Skip(int nOffset)
{
	return SkipReadCursor(nOffset);
}

size_t IStreamBase::GetSize() const
{
	return _uSize;
}

bool IStreamBase::SetSize(size_t uSize)
{
	_uSize = uSize;
	return true;
}

bool IStreamBase::DebugCheck() const
{
	ASSERT_LOG_ERROR(GetLength() <= GetSize());
	ASSERT_LOG_ERROR(GetWriteCursor()<=GetSize());
	ASSERT_LOG_ERROR(GetReadCursor()<=GetSize());
	ASSERT_LOG_ERROR(GetSize() <= GetMaxSize());
	return true;
}

bool IStreamBase::_Clear()
{
	_uSize = 0;
	ClearError();
	Reset();

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return true;
}

bool IStreamBase::IsReadable()
{
	if (IsWriteOnly())return false;

	return true;
}

bool IStreamBase::IsWriteable()
{
	if (IsReadOnly())return false;

	return true;
}

bool IStreamBase::IsVaildCursor(size_t uCursor) const
{
	return uCursor < GetMaxSize();
}

bool IStreamBase::IsDataEmpty() const
{
	return GetSize() <= 0;
}

bool IStreamBase::IsDataFull() const
{
	return GetSize() >= GetMaxSize();
}

bool IStreamBase::IsFull() const
{
	return GetWriteCursor() >= GetMaxSize();
}

size_t IStreamBase::GetUnusedSize() const
{
	return GetMaxSize() - GetSize();
}

bool IStreamBase::Drop(size_t uSize)
{
	if (uSize > GetSize())return false;

	SetSize(GetSize() - uSize);

	//修正读写指针
	if (GetReadCursor() > GetSize())
		SetReadCursor(GetSize());
	if (GetWriteCursor() > GetSize())
		SetWriteCursor(GetSize());

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return true;
}

bool IStreamBase::Resize(size_t uSize)
{
	ASSERT_LOG_ERROR(uSize > 0);

	//重新定义空间大小
	SetMaxSize(uSize);
	SetSize(0);
	Reset();

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return true;
}

bool IStreamBase::IsTrimed() const
{
	return IsReadCursorBegin() && IsWriteCursorEnd();
}

NS_TOOL_FRAME_END
