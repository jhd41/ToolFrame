#include "IMsgStream.h"
#include "ToolFrame.h"
#include "MLoger.h"
#include "MProtocol.h"

NS_TOOL_FRAME_BEGIN

IMsgStream::IMsgStream( UINT16 uOpCode )
{
	_uLength = 0;
	_uOpCode = uOpCode;
	
	_uLoadingCursor = 0;
	_bLoadBody = false;
}

IMsgStream::IMsgStream(StreamBinaryPtr pStream)
{
	ASSERT_LOG_ERROR(pStream);

	_uLength = 0;
	_uOpCode = 0;
	
	_pStreamLoad = pStream;
	_uLoadingCursor = pStream->GetReadCursor();
	_bLoadBody = false;
}

IMsgStream::IMsgStream(const IMsgStream& msgStream,UINT16 uOpCode )
{
	ASSERT_LOG_ERROR(!_pStreamLoad);
	ASSERT_LOG_ERROR_MSG(uOpCode == msgStream.GetOpCode(),"uOpCode:"<<uOpCode<<" msgStream.GetOpCode():"<<msgStream.GetOpCode());

	_uLength = msgStream.GetLength();
	_uOpCode = msgStream.GetOpCode();

	_pStreamLoad = msgStream._pStreamLoad;
	_uLoadingCursor = msgStream._uLoadingCursor;
	_bLoadBody = false;
}

IMsgStream::IMsgStream(const IMsgStream& msgStream)
{
	_uLength = msgStream._uLength;
	_uOpCode = msgStream._uOpCode;

	_uLoadingCursor = 0;
	_bLoadBody		= false;

	//����ָ��ƫ����
	if (msgStream._pStreamLoad)
	{
		_pStreamLoad = msgStream.GetSendStream();
		LoadBegin();
	}
}

IMsgStream::~IMsgStream()
{
	ResetLoadStream();
}

StreamBinaryPtr IMsgStream::CloneLoadStream()const
{
	if (!_pStreamLoad)return StreamBinaryPtr();

	IStreamPtr ptr = _pStreamLoad;
	ASSERT_LOG_ERROR(ptr);

	ptr->SetReadCursor(_uLoadingCursor);//��Ϊ���

	if (ptr->GetLength() < GetLength())
		return StreamBinaryPtr();

	ASSERT_LOG_DEBUG_ERR_MSG(GetLength()<=0xFFFF,"Length Too Long! :"<< GetLength());

	//����һ��
	StreamBinaryPtr pCopy(new CStreamBinary());
	ASSERT_LOG_ERROR(pCopy->Write(*ptr, GetLength()));

	return pCopy;
}

bool IMsgStream::ResetLoadStream()
{
	//��ԭ����ʱ��ָ��
	if (!_pStreamLoad)return false;

	_pStreamLoad->SetReadCursor(_uLoadingCursor);
	return true;
}

StreamBinaryPtr IMsgStream::GetSendStream()const
{
	return ToolFrame::ConstCast(this)->GetSendStream();
}

StreamBinaryPtr IMsgStream::GetSendStream()
{
	//���û�м��ع����� ��ֱ�ӷ���һ�����Ϳ����� ����͵��������л�
	if (_pStreamLoad && !_bLoadBody)
		return CloneLoadStream();

	ToolFrame::SetPtrNull(_pStream);

	StreamBinaryPtr pBuffer(new CStreamBinary());
	ASSERT_LOG_ERROR(pBuffer);

	pBuffer->SetAlloc(CStreamBinary::ALLOC_BLOCK_SIZE);
	pBuffer->SetBlockSize(MProtocol::Singleton().GetBlockSize());
	pBuffer->SetMaxSize(0xFFFF);//��ΪЭ�������ܳ���0xFFFF����ͷ��ʾ����

	if (!OnSerialize(pBuffer)) {
		LOG_NET_ERR("OnSerialize Faild");
		return StreamBinaryPtr();
	}

	return pBuffer;
}

bool IMsgStream::Save()
{
	ASSERT_LOG_ERROR(_pStream);

	if (_pStream->IsError())return false;

	_pStream->SetDirection(CStreamBuffer::STREAM_INPUT);
	
	size_t uCursorBegin =_pStream->GetWriteCursor();
	*_pStream<<_uLength<<_uOpCode;
	Serialize();
	if (_pStream->IsError())return false;

	ASSERT_LOG_ERROR(_pStream->GetWriteCursor() >= uCursorBegin);

	_uLength = (uint16)(_pStream->GetWriteCursor() - uCursorBegin);

	//�޸İ�����
	_pStream->Modify(uCursorBegin, &_uLength, sizeof(_uLength));

	return !_pStream->IsError();
}

void IMsgStream::Serialize()
{

}

bool IMsgStream::LoadBegin()
{
	if (!_pStreamLoad)return false;
	if (_pStreamLoad->IsError())return false;

	*_pStreamLoad >>_uLength>>_uOpCode;
	return !_pStreamLoad->IsError();
}

UINT16 IMsgStream::GetLength() const
{
	return _uLength;
}

UINT16 IMsgStream::GetOpCode() const
{
	return _uOpCode;
}

bool IMsgStream::Load()
{
	if (!_pStreamLoad)return false;
	if (_pStreamLoad->IsError())return false;

	_pStream = _pStreamLoad;

	//����ָ��
	_pStream->SetReadCursor(_uLoadingCursor);

	//����ͷ
	if (!LoadBegin())return false;

	//��������
	Serialize();

	_bLoadBody = true;

	//��ԭ������
	bool bError = _pStream->IsError();
	_pStream->ClearError();
	return !bError;
}

bool IMsgStream::IsInvaild() const
{
	return INVALID_ID == _uOpCode;
}

bool IMsgStream::SetLoadStream(IStreamPtr ptr)
{
	if (!ptr)return false;

	//���֮ǰ���ڶ�ȡ�� ��ԭ
	if (_pStreamLoad)
		ResetLoadStream();

	//ʹ���µ���
	_pStreamLoad = ptr;
	_uLoadingCursor = ptr->GetReadCursor();
	return true;
}

StreamBufferPtr IMsgStream::ResetLoadStreamBuffer()
{
	if (!_pStreamLoad)return StreamBufferPtr();
	if (_pStreamLoad->IsEmpty())return StreamBufferPtr();

	ResetLoadStream();
	
	//�����ܿ��� ����ת���� ��������
	StreamBinaryPtr pBinary = ToolFrame::DynamicCast<StreamBinaryPtr>(_pStreamLoad);
	if (pBinary)
	{
		StreamBufferPtr pStreamBuffer = pBinary->ToStreamBuffer(GetLength());
		ASSERT_LOG_ERROR(pStreamBuffer);

		//���ûؼ�����
		SetLoadStream(pStreamBuffer);
		return pStreamBuffer;
	}

	StreamBufferPtr pBuffer = ToolFrame::DynamicCast<StreamBufferPtr>(_pStreamLoad);
	if (pBuffer)return pBuffer;

	return StreamBufferPtr();
}

IStreamPtr IMsgStream::GetStream()const
{
	return _pStream;
}

uint16 IMsgStream::GetBeginLength()
{
	return sizeof(uint16) + sizeof(uint16);
}

bool IMsgStream::IsVaildBegin() const
{
	return INVALID_ID != _uOpCode && _uLength >= GetBeginLength();
}

size_t IMsgStream::GetBodyLength() const
{
	uint16 uLength = GetLength();
	uint16 uLengthBegin = GetBeginLength();
	if (uLength < uLengthBegin)return 0;

	return uLength - uLengthBegin;
}

//�����ຯ��
size_t IMsgStream::GetBodyLength( StreamBufferPtr ptr )
{
	if (!ptr)return 0;

	size_t uUsedSize =ptr->GetSize();
	uint16 uLengthBegin = GetBeginLength();

	if (uUsedSize < uLengthBegin)return 0;
	return uUsedSize - uLengthBegin; 
}

void* IMsgStream::GetBodyBuffer( StreamBufferPtr ptr )
{
	if (!ptr)return nullptr;

	uint uBeginLength = GetBeginLength();
	if (uBeginLength >= ptr->GetSize())return nullptr;

	char* pBuffer = (char*)ptr->GetMallocBuffer();
	return &pBuffer[uBeginLength];
}

bool IMsgStream::IsLoad() const
{
	return !!_pStreamLoad;
}

bool IMsgStream::OnSerialize(IStreamPtr ptr) const
{
	return ToolFrame::ConstCast(this)->OnSerialize(ptr);
}

bool IMsgStream::OnSerialize(IStreamPtr ptr)
{
	if (!ptr)return false;
	
	ASSERT_LOG_ERROR(!_pStream);
	_pStream = ptr;
	
	if (!Save())return false;

	ToolFrame::SetPtrNull(_pStream);
	return true;
}

NS_TOOL_FRAME_END
