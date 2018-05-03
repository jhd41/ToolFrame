#include "StreamBinary.h"
#include "StreamBufferMalloc.h"
#include "ToolStd.h"
#include "MLoger.h"

//�ڲ��Ļ��������α�һ�ɲ����� Ĭ�Ͼ���Ϊ �����0 �յ������ݽ���

NS_TOOL_FRAME_BEGIN

CStreamBinary::CStreamBinary()
{
	_eAlloc = ALLOC_BUFFER_POWER_SIZE;
	_uBlockSize = 4096;
	SetMaxSize(ToolFrame::GetLimitMax<size_t>());
}

CStreamBinary::CStreamBinary(size_t uSizeMax)
{
	_eAlloc = ALLOC_BUFFER_POWER_SIZE;
	_uBlockSize = 4096;
	SetMaxSize(uSizeMax);
}

CStreamBinary::CStreamBinary(const void* pBuff, size_t uSizeMax)
{
	_eAlloc = ALLOC_BUFFER_POWER_SIZE;
	_uBlockSize = 4096;
	SetMaxSize(uSizeMax);

	Write(pBuff, uSizeMax);
}

CStreamBinary::CStreamBinary(const void* pBuff, size_t uSizeMax, size_t uSizeUse)
{
	_eAlloc = ALLOC_BUFFER_POWER_SIZE;
	_uBlockSize = 4096;
	SetMaxSize(uSizeMax);

	Write(pBuff, uSizeUse);
}

CStreamBinary::CStreamBinary(const StreamBufferPtr ptr)
{
	_eAlloc = ALLOC_BUFFER_POWER_SIZE;
	_uBlockSize = 4096;
	SetMaxSize(ToolFrame::GetLimitMax<size_t>());

	Write(ptr->GetBuffer(), ptr->GetLength());
}

CStreamBinary::CStreamBinary(const StreamBufferPtr ptr, size_t uSizeMax)
{
	_eAlloc = ALLOC_BUFFER_POWER_SIZE;
	_uBlockSize = 4096;
	SetMaxSize(uSizeMax);

	Write(ptr->GetBuffer(), ptr->GetLength());
}

CStreamBinary::CStreamBinary(const CStreamBinary& iStream)
{
	if (!Copy(iStream))
		SetError();
}


CStreamBinary::~CStreamBinary()
{
}

bool CStreamBinary::SetAlloc(int eAlloc)
{
	_eAlloc = eAlloc;
	return true;
}

bool CStreamBinary::SetBlockSize(size_t uSize)
{
	_uBlockSize = uSize;
	return true;
}

bool CStreamBinary::Copy(const CStreamBinary& iStream)
{
	Clear();

	ListStreamBufferPtr::const_iterator itr;
	foreach(itr, iStream._vBuffer) {
		const StreamBufferPtr& ptr = *itr;
		ASSERT_LOG_ERROR(ptr);

		StreamBufferPtr ptrNew(new CStreamBufferMalloc(*ptr));
		_vBuffer.push_back(ptrNew);
	}

	_eAlloc = iStream._eAlloc;
	_uBlockSize = iStream._uBlockSize;

	ASSERT_LOG_ERROR(IStreamBase::Copy(iStream));
	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return true;
}

int CStreamBinary::GetAlloc() const
{
	return _eAlloc;
}

size_t CStreamBinary::GetBlockSize() const
{
	return _uBlockSize;
}

CStreamBinary& CStreamBinary::operator=(const CStreamBinary& iStream)
{
	if (ToolFrame::IsSelf(*this, iStream))return *this;

	if (!Copy(iStream))
		SetError();

	return *this;
}

bool CStreamBinary::_Read(size_t uCursor, void* pBuff, size_t uSize)
{
	ListStreamBufferPtr::iterator itrCur; size_t uCursorLess = 0;
	ASSERT_LOG_ERROR(FindBuffer(itrCur, uCursorLess, uCursor));

	size_t uRead = 0;//�Ѷ�ȡ������
	char* pBuffChar = (char*)pBuff;

	//��ȡ��ǰ ������
	{
		StreamBufferPtr ptr = *itrCur;
		ASSERT_LOG_ERROR(ptr);
		ptr->SetReadCursor(uCursorLess);
		ptr->SetWriteCursorEnd();
		uRead += ptr->ReadSome(&pBuffChar[uRead], uSize - uRead);

		if (uRead >= uSize) {
			ASSERT_LOG_DEBUG_ERR(uRead == uSize);
			return true;
		}
	}
	
	//������ȡ���໺����
	++itrCur;
	for (; itrCur != _vBuffer.end();++itrCur)
	{
		StreamBufferPtr ptr = *itrCur;
		ASSERT_LOG_ERROR(ptr);
		ptr->ResetCursor();
		uRead += ptr->ReadSome(&pBuffChar[uRead], uSize - uRead);

		if (uRead >= uSize) {
			ASSERT_LOG_DEBUG_ERR(uRead == uSize);
			return true;
		}
	}

	LOG_ERROR();
	return false;
}

bool CStreamBinary::_Write(size_t uCursor, const void* pBuff, size_t uSize)
{
	const char* pBuffChar = (const char*)pBuff;
	size_t uWrited = 0;//��д��������

	//�ҵ�д������
	ListStreamBufferPtr::iterator itrCur; size_t uLessCursor = 0;
	if (!FindBuffer(itrCur, uLessCursor, uCursor))
	{
		//����Ҳ��� �� �����¿ռ�
		do
		{
			StreamBufferPtr ptr = MallocBuffer(uSize);
			ASSERT_LOG_ERROR(ptr);
			_vBuffer.push_back(ptr);

			uWrited += ptr->WriteSome(&pBuffChar[uWrited], uSize - uWrited);
		} while (uWrited < uSize);
		ASSERT_LOG_DEBUG_ERR(uWrited == uSize);
		return true;
	}

	//�����������Ҫ�޸�(������������������ǰ������ԭ�� �����޸�)
	if (uCursor < GetSize())
	{
		StreamBufferPtr pBuffer = *itrCur;
		ASSERT_LOG_ERROR(pBuffer);

		//���޸ĵ�ǰ�Ļ�����
		//���㵱ǰ�޸ĵĳ���
		size_t uModify = ToolFrame::Min(uSize, pBuffer->GetSize() - uLessCursor);
		ASSERT_LOG_ERROR(pBuffer->Modify(uLessCursor, &pBuffChar[uWrited], uModify));

		uWrited += uModify;
		if (uWrited >= uSize) {
			ASSERT_LOG_DEBUG_ERR(uWrited == uSize);
			return true;
		}

		//�����л��棬���޸�
		++itrCur;
		while (itrCur != _vBuffer.end())
		{
			StreamBufferPtr ptr = *itrCur;
			ASSERT_LOG_ERROR(ptr);

			//�����޸ĵĳ���
			size_t uModify = ToolFrame::Min(ptr->GetSize(), uSize - uWrited);

			ASSERT_LOG_ERROR(ptr->Modify(0, &pBuffChar[uWrited], uModify));

			uWrited += uModify;
			if (uWrited >= uSize) {
				ASSERT_LOG_DEBUG_ERR(uWrited == uSize);
				return true;
			}
		}

		//���ಿ�ֽ������
		do
		{
			StreamBufferPtr ptr = MallocBuffer(uSize - uWrited);
			ASSERT_LOG_ERROR(ptr);
			_vBuffer.push_back(ptr);

			uWrited += ptr->WriteSome(&pBuffChar[uWrited], uSize - uWrited);
		} while (uWrited < uSize);
		ASSERT_LOG_DEBUG_ERR(uWrited == uSize);
	}

	//�������û����Ҫ�޸�
	//���ݲ�ͬ���䷽�����з��ű���д��
	switch (_eAlloc) {
		case ALLOC_WRITE_SIZE:
		case ALLOC_WRITE_POWER_SIZE:
			{
				//�����¿ռ�
				do
				{
					StreamBufferPtr ptr = MallocBuffer(uSize);
					ASSERT_LOG_ERROR(ptr);
					_vBuffer.push_back(ptr);

					uWrited += ptr->WriteSome(&pBuffChar[uWrited], uSize - uWrited);
				} while (uWrited < uSize);
				ASSERT_LOG_DEBUG_ERR(uWrited == uSize);
				return true;
			}
			break;
		case ALLOC_BUFFER_POWER_SIZE:
		case ALLOC_BLOCK_SIZE:
			{
				//���������ǰ
				StreamBufferPtr pBuffer = *itrCur;
				ASSERT_LOG_ERROR(pBuffer);
				pBuffer->SetWriteCursorEnd();
				uWrited += pBuffer->WriteSome(&pBuffChar[uWrited], uSize - uWrited);
				if (uWrited >= uSize)
				{
					ASSERT_LOG_DEBUG_ERR(uWrited == uSize);
					return true;
				}

				//�ٷ����¿ռ�
				do
				{
					StreamBufferPtr ptr = MallocBuffer(uSize);
					ASSERT_LOG_ERROR(ptr);
					_vBuffer.push_back(ptr);

					uWrited += ptr->WriteSome(&pBuffChar[uWrited], uSize - uWrited);
				} while (uWrited < uSize);
				ASSERT_LOG_DEBUG_ERR(uWrited == uSize);
				return true;
			}
			break;
	}
	return false;
}

bool CStreamBinary::_Insert(size_t uCursor, const void* pBuff, size_t uSize)
{
	ListStreamBufferPtr::iterator itrCur; size_t uCursorLess = 0;
	if (!FindBuffer(itrCur, uCursorLess, uCursor))
	{
		const char* pBuffChar = (const char*)pBuff;
		//����Ҳ��� �� �����¿ռ�
		size_t uWrited = 0;//��д��������
		do 
		{
			StreamBufferPtr ptr = MallocBuffer(uSize);
			ASSERT_LOG_ERROR(ptr);
			_vBuffer.push_back(ptr);

			uWrited += ptr->WriteSome(&pBuffChar[uWrited], uSize - uWrited);
		} while (uWrited < uSize);
		ASSERT_LOG_DEBUG_ERR(uWrited == uSize);
		return true;
	}

	//���ݲ�ͬ���䷽�����з��ű���д��
	switch (_eAlloc)
	{
		case ALLOC_WRITE_SIZE:
		case ALLOC_WRITE_POWER_SIZE:
			{
				StreamBufferPtr pBufferCur = *itrCur;
				ASSERT_LOG_ERROR(pBufferCur);

				//��ʼд�뻺����
				ListStreamBufferPtr vTemp;

				//�����α� ���������ֳ�������
				CStreamBuffer streamBegin(pBuff, uCursorLess);
				CStreamBuffer streamEnd(pBufferCur->GetBuffer(uCursorLess), pBufferCur->GetSize() - uCursorLess);

				//�����ɻ�����
				if (!streamBegin.IsEmpty())
				{
					StreamBufferPtr pBufferBegin = MallocBuffer(streamBegin.GetSize());
					ASSERT_LOG_ERROR(pBufferBegin);
					ToolFrame::PushBack(vTemp, pBufferBegin);
					pBufferBegin->Write(streamBegin.GetBuffer(), streamBegin.GetSize());
				}

				StreamBufferPtr pBufferMiddle = MallocBuffer(uSize);
				ASSERT_LOG_ERROR(pBufferMiddle);
				ToolFrame::PushBack(vTemp, pBufferMiddle);
				pBufferMiddle->Write(pBuff, uSize);

				if (!streamEnd.IsEmpty())
				{
					StreamBufferPtr pBufferEnd = MallocBuffer(streamEnd.GetSize());
					ASSERT_LOG_ERROR(pBufferEnd);
					ToolFrame::PushBack(vTemp, pBufferEnd);
					pBufferEnd->Write(streamEnd.GetBuffer(), streamEnd.GetSize());
				}

				//�滻ԭ�ȵĵ�����
				ToolFrame::Replace(_vBuffer, itrCur, vTemp);
				return true;
			}
			break;
		case ALLOC_BUFFER_POWER_SIZE:
			{
				//�����ǰ�ҵ��Ļ���������д����д��
				StreamBufferPtr pBufferCur = *itrCur;
				ASSERT_LOG_ERROR(pBufferCur);

				if (pBufferCur->Insert(uCursorLess, pBuff, uSize))return true;

				//�����α� ���������ֳ�������
				CStreamBuffer streamBegin(pBuff, uCursorLess);
				CStreamBuffer streamEnd(pBufferCur->GetBuffer(uCursorLess), pBufferCur->GetSize() - uCursorLess);

				//������ʵĴ�С�����ǰ�Ļ�����
				size_t uNeedSize = ToolFrame::Max(ToolFrame::SmartMemoryLength(pBufferCur->GetSize() + uSize), (size_t)8);
				StreamBufferPtr pBufferNew(new CStreamBufferMalloc(uNeedSize));
				ASSERT_LOG_ERROR(pBufferNew);

				//д��
				ASSERT_LOG_ERROR(pBufferNew->Write(streamBegin.GetBuffer(), streamBegin.GetSize()));
				ASSERT_LOG_ERROR(pBufferNew->Write(pBuff, uSize));
				ASSERT_LOG_ERROR(pBufferNew->Write(streamEnd.GetBuffer(), streamEnd.GetSize()));

				//�滻
				ToolFrame::Replace(_vBuffer, itrCur, pBufferNew);
				return true;
				break;
			}
		case ALLOC_BLOCK_SIZE:
			{
				//�����ǰ�ҵ��Ļ���������д����д��
				StreamBufferPtr pBufferCur = *itrCur;
				ASSERT_LOG_ERROR(pBufferCur);

				if (pBufferCur->Insert(uCursorLess, pBuff, uSize))return true;

				//�����α� ���������ֳ�������
				CStreamBuffer streamBegin(pBuff, uCursorLess);
				CStreamBuffer streamEnd(pBufferCur->GetBuffer(uCursorLess), pBufferCur->GetSize() - uCursorLess);

				//��ʼд�뻺����
				ListStreamBufferPtr vTemp;
				
				//��д���һ������
				if (!streamBegin.IsEmpty())
				{
					StreamBufferPtr pBufferNew = MallocBuffer(uSize);
					ASSERT_LOG_ERROR(pBufferNew);
					ToolFrame::PushBack(vTemp, pBufferNew);

					ASSERT_LOG_ERROR(pBufferNew->Write(streamBegin.GetBuffer(), streamBegin.GetSize()));
				}

				//Ȼ�󷴸����Բ���������ֱ��д��
				const char* pBuffChar = (const char*)pBuff;
				size_t uWrited = 0;//��д��������
				do
				{
					StreamBufferPtr ptr = MallocBuffer(uSize);
					ASSERT_LOG_ERROR(ptr);
					vTemp.push_back(ptr);

					uWrited += ptr->WriteSome(&pBuffChar[uWrited], uSize - uWrited);
				} while (uWrited < uSize);
				ASSERT_LOG_DEBUG_ERR(uWrited == uSize);
				
				//���д���������
				if (!streamEnd.IsEmpty())
				{
					StreamBufferPtr pBufferNew = MallocBuffer(uSize);
					ASSERT_LOG_ERROR(pBufferNew);
					ToolFrame::PushBack(vTemp, pBufferNew);

					ASSERT_LOG_ERROR(pBufferNew->Write(streamEnd.GetBuffer(), streamEnd.GetSize()));
				}

				//�滻ԭ�ȵĵ�����
				ToolFrame::Replace(_vBuffer,itrCur,vTemp);
				return true;
			}
			break;
	}

	return false;
}

bool CStreamBinary::_Clear()
{
	_vBuffer.clear();
	return IStreamBase::_Clear();
}

StreamBufferPtr CStreamBinary::MallocBuffer(size_t uSize)
{
	size_t uNeedSize = 0;
	switch (_eAlloc)
	{
		case ALLOC_WRITE_SIZE:
			uNeedSize = uSize;
			break;
		case ALLOC_WRITE_POWER_SIZE:
			uNeedSize = ToolFrame::SmartMemoryLength(uSize);
			break;
		case ALLOC_BUFFER_POWER_SIZE:
			{
				if (_vBuffer.empty())
				{
					uNeedSize = ToolFrame::Max(ToolFrame::SmartMemoryLength(uSize),(size_t)8);
					break;
				}

				StreamBufferPtr ptrBack = ToolFrame::GetBack(_vBuffer);
				ASSERT_LOG_ERROR(ptrBack);
				uNeedSize = ToolFrame::SmartMemoryLengthNextLevel(ptrBack->GetMaxSize());
			}
			break;
		case ALLOC_BLOCK_SIZE:
			uNeedSize = _uBlockSize;
			break;
	}

	ASSERT_LOG_ERROR(uNeedSize > 0);

	StreamBufferPtr ptr(new CStreamBufferMalloc(uNeedSize));
	return ptr;
}

bool CStreamBinary::FindBuffer(ListStreamBufferPtr::iterator& itrCursor, size_t& uCursorLess, size_t uCursor)
{
	//����ָ�����ڵ�Buff
	//����������л������ڣ�ֱ�ӷ������һ��������
	if (GetSize() <= uCursor)
	{
		if (_vBuffer.empty())return false;

		ListStreamBufferPtr::iterator itr = --_vBuffer.end();
		StreamBufferPtr ptr = *itr;
		ASSERT_LOG_ERROR(ptr);
		if (ptr->IsDataFull())return false;
	
		itrCursor = itr;
		uCursorLess = ptr->GetSize();
		return true;
	}

	//�������л��������ҵ��α�����λ�õĻ�����
	//����ָ����µ�λ�ý���ѡ����ʵķ�ʽ������������Ч��
	//һ����Ϊ�����Buffer��С��ǰ��Ĵ�СҪ�� ��� �Ӻ���ǰ���ܻ������Ը�
	//�Ż�ԭ��:�������ܲ���������Э��ĸ������л� ��������ȡ���ڲ���Buffer,����б�Ҫ����Ч��
	if (uCursor < GetSize()/2)
	{
		//��ǰ����
		size_t uCur = 0;
		ListStreamBufferPtr::iterator itr;
		foreach(itr, _vBuffer)
		{
			StreamBufferPtr ptr = *itr;
			ASSERT_LOG_ERROR(ptr);

			if (uCur + ptr->GetSize() >= uCursor) {
				itrCursor = itr;
				uCursorLess = uCursor - uCur;//���� ����ڵ�ǰ���ڴ�ص��α�λ��
				return true;
				break;
			}

			uCur += ptr->GetSize();
		}
	}
	else {
		//�Ӻ���ǰ
		size_t uCur = GetSize();
		ListStreamBufferPtr::iterator itr;
		foreachReverse(itr, _vBuffer)
		{
			StreamBufferPtr ptr = *itr;
			ASSERT_LOG_ERROR(ptr);

			ASSERT_LOG_DEBUG_ERR(uCur >= ptr->GetSize());

			uCur -= ptr->GetSize();
			if (uCur <= uCursor) {
				itrCursor = itr;
				uCursorLess = uCursor - uCur;//���� ����ڵ�ǰ���ڴ�ص��α�λ��
				return true;
				break;
			}

			
		}
	}

	return false;
}

StreamBufferPtr CStreamBinary::ToStreamBuffer()
{
	return ToStreamBuffer(GetLength());
}

StreamBufferPtr CStreamBinary::ToStreamBuffer(size_t uLength)
{
	if (IsEmpty())return StreamBufferPtr();
	if (uLength <= 0 || uLength>GetLength())return StreamBufferPtr();

	StreamBufferPtr pBuffer = StreamBufferPtr(new CStreamBufferMalloc(uLength));
	ASSERT_LOG_ERROR(pBuffer);

	pBuffer->Write(*this, pBuffer->GetMaxSize());

	ASSERT_LOG_DEBUG_ERR(DebugCheck());

	return pBuffer;
}

StreamBufferPtr CStreamBinary::MoveToStreamBuffer()
{
	if (IsEmpty())return StreamBufferPtr();
	
	if (_vBuffer.size() == 1 && IsTrimed())
	{
		StreamBufferPtr pBuffer = ToolFrame::GetFront(_vBuffer);
		ASSERT_LOG_ERROR(pBuffer);

		pBuffer->ResetCursor();

		ASSERT_LOG_DEBUG_ERR(!pBuffer->IsEmpty());

		Clear();
		ASSERT_LOG_DEBUG_ERR(DebugCheck());
		return pBuffer;
	}

	StreamBufferPtr pBuffer = ToStreamBuffer();
	ASSERT_LOG_ERROR(pBuffer);
	ASSERT_LOG_DEBUG_ERR(!pBuffer->IsEmpty());

	Clear();
	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return pBuffer;
}

StreamBufferPtr CStreamBinary::ResetToStreamBuffer()
{
	StreamBufferPtr pBuffer = MoveToStreamBuffer();
	if (!pBuffer)return StreamBufferPtr();

	StreamBufferPtr pTemp = pBuffer;
	ASSERT_LOG_ERROR(Splice(pTemp));

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return pBuffer;
}

bool CStreamBinary::Splice(StreamBufferPtr& ptr, bool bBack)
{
	if (!IsWriteable())return false;
	if (IsError())return false;

	if (!ptr)return true;
	if (ptr->IsEmpty())return true;
	if (ptr->GetLength() + GetWriteCursor() > GetMaxSize())return false;

	size_t uLength = ptr->GetLength();
	
	//������
	ASSERT_LOG_ERROR(ptr->TrimBuffer());
	ptr->SetWriteOnly(false);//��Ȼ�Ǹ�������Ϊ�����ڲ�ʹ���ˣ���ô��ȫ�����ǵ�ָ�� ��״̬�޸���
	
	ToolFrame::Merge(_vBuffer, ptr, bBack);

	//�����α�ָ��
	bool bReadCursorBegin = IsReadCursorBegin();
	bool bWriteCursorEnd = IsWriteCursorEnd();

	SetSize(GetSize() + uLength);

	if (bWriteCursorEnd)
		SkipWriteCursor(uLength);

	if (!bBack && !bReadCursorBegin)
		SkipReadCursor(uLength);

	ToolFrame::SetPtrNull(ptr);

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return true;
}

bool CStreamBinary::Splice(CStreamBinary& iStream, bool bBack)
{
	if (!IsWriteable())return false;
	if (IsError())return false;

	if (iStream.IsEmpty())return true;
	if (iStream.GetLength() + GetWriteCursor() > GetMaxSize())return false;

	ListStreamBufferPtr::iterator itr; size_t uCursorLess = 0;
	ASSERT_LOG_ERROR(iStream.FindBuffer(itr, uCursorLess, iStream.GetReadCursor()));

	ListStreamBufferPtr vBuffer;

	size_t uLength = iStream.GetLength();
	size_t uWrite = uLength;

	//����һ��д�뵱ǰ�ڴ�
	{
		StreamBufferPtr pBuffer = *itr;
		ASSERT_LOG_ERROR(pBuffer);

		pBuffer->SetReadCursor(uCursorLess);
		pBuffer->SetWriteCursorEnd();
		ASSERT_LOG_ERROR(pBuffer->TrimBuffer());

		ToolFrame::PushBack(vBuffer, pBuffer);

		uWrite -= pBuffer->GetSize();
	}

	//������д���ڴ�
	if (uWrite > 0)
	{
		++itr;
		for (; itr != iStream._vBuffer.end(); ++itr)
		{
			StreamBufferPtr pBuffer = *itr;
			ASSERT_LOG_ERROR(pBuffer);
			pBuffer->ResetCursor();

			if (uWrite < pBuffer->GetSize())
			{
				pBuffer->SetWriteCursor(uWrite);
				ASSERT_LOG_ERROR(pBuffer->TrimBuffer());
			}

			ToolFrame::PushBack(vBuffer, pBuffer);
			uWrite -= pBuffer->GetSize();

			if (uWrite <= 0)
				break;
		}
	}

	iStream.Clear();

	ToolFrame::Merge(_vBuffer, vBuffer, bBack);

	//�����α�ָ��
	bool bReadCursorBegin = IsReadCursorBegin();
	bool bWriteCursorEnd = IsWriteCursorEnd();

	SetSize(GetSize() + uLength);

	if (bWriteCursorEnd)
		SkipWriteCursor(uLength);

	if (!bBack && !bReadCursorBegin)
		SkipReadCursor(uLength);

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return true;
}

StreamBufferPtr CStreamBinary::PopFrontBuffer()
{
	if (_vBuffer.empty())return StreamBufferPtr();

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	
	StreamBufferPtr pBuffer = ToolFrame::PopFront(_vBuffer);
	ASSERT_LOG_ERROR(pBuffer);
	
	//��������
	int uSize = (int)pBuffer->GetSize();

	//�����α�ָ��
	SetSize(GetSize() - uSize);

	SkipReadCursor(-uSize);
	SkipWriteCursor(-uSize);

	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return pBuffer;
}

bool CStreamBinary::Drop(size_t uSize)
{
	if (uSize > GetSize())return false;

	SetSize(GetSize() - uSize);

	//������дָ��
	if (GetReadCursor() > GetSize())
		SetReadCursor(GetSize());
	if (GetWriteCursor() > GetSize())
		SetWriteCursor(GetSize());

	size_t uDroped = uSize;//ʣ����Ҫ������������

	 //�������������
	ListStreamBufferPtr::iterator itr = _vBuffer.end();
	--itr;

	do {
		StreamBufferPtr pBuffer = *itr;
		ASSERT_LOG_ERROR(pBuffer);

		if (pBuffer->GetSize() >= uDroped)
		{
			//������������
			itr = _vBuffer.erase(itr);
			uDroped -= pBuffer->GetSize();
			if (_vBuffer.empty())
				break;

			--itr;
			continue;
		}

		ASSERT_LOG_ERROR(pBuffer->Drop(uDroped));
		uDroped -= uDroped;
	} while (uDroped > 0);
	
	ASSERT_LOG_DEBUG_ERR(uDroped == 0);
	ASSERT_LOG_DEBUG_ERR(DebugCheck());
	return true;
}

bool CStreamBinary::DebugCheck() const
{
	size_t uSize = 0;
	ListStreamBufferPtr::const_iterator itr;
	foreach(itr, _vBuffer) {
		const StreamBufferPtr& ptr = *itr;
		ASSERT_LOG_ERROR(ptr);

		uSize += ptr->GetSize();
	}

	ASSERT_LOG_ERROR_MSG(GetSize() == uSize," Size:"<<GetSize()<<" CalSize:"<<uSize);
	if (GetSize() != uSize)return false;
	return IStreamBase::DebugCheck();
}

NS_TOOL_FRAME_END

