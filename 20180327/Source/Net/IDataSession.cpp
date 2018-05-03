#include "IDataSession.h"
#include "MLoger.h"
#include "MProtocol.h"

NS_TOOL_FRAME_BEGIN
//////////////////////////////////////////////////////////////////////////
IDataReceiver::IDataReceiver()
{
}

IDataReceiver::~IDataReceiver()
{

}

//////////////////////////////////////////////////////////////////////////
IDataSerialize::IDataSerialize()
{

}

IDataSerialize::~IDataSerialize()
{

}

bool IDataSerialize::OnSerialize(IStreamPtr ptr) const
{
	return false;
}

//////////////////////////////////////////////////////////////////////////
IDataNet::IDataNet()
{
	_uRecvSize = MProtocol::Singleton().GetRecvSize();
	_uSendSize = MProtocol::Singleton().GetSendSize();
	_uBlockSize = MProtocol::Singleton().GetBlockSize();
}

IDataNet::~IDataNet()
{

}

bool IDataNet::SetAddress( const VectorString& vAddress )
{
	_vAddress = vAddress;
	return true;
}

bool IDataNet::SetAddress( const std::string& sAddress )
{
	_sAddress = sAddress;
	return true;
}

bool IDataNet::SetAccepterKey(const XAcceptorKey& key)
{
	_xAcceptorKey = key;
	return true;
}

bool IDataNet::InitBuffSize(size_t uRecvSize, size_t uSendSize, size_t uBlockSize)
{
	ASSERT_LOG_ERROR(uBlockSize > 0 );

	_uSendSize = uSendSize;
	_uRecvSize = uRecvSize;
	_uBlockSize = uBlockSize;

	//初始化发送
	{
		CLockScoped lock(_mutexSend);
		_pSendWait = StreamBinaryPtr(new CStreamBinary());
		_pSendWait->SetAlloc(CStreamBinary::ALLOC_BLOCK_SIZE);
		_pSendWait->SetBlockSize(_uBlockSize);
		if (_uSendSize > 0) {
			_pSendWait->SetBlockSize(_uSendSize);
			_pSendWait->SetMaxSize(_uSendSize);
		}
	}

	return true;
}

size_t IDataNet::SendData(const void* pBuffer, size_t uLen)
{
	if (!pBuffer)return 0;
	if (uLen <= 0)return 0;

	CLockScoped lock(_mutexSend);
	ASSERT_LOG_ERROR(_pSendWait);
	if (!_pSendWait->Write(pBuffer, uLen))return 0;

	//写入成功后
	_xElapseSend.ReStart();
	return uLen;
}

size_t IDataNet::SendData(const StreamBinaryPtr pBuffer)
{
	if (!pBuffer)return 0;
	if (pBuffer->IsEmpty())return 0;

	size_t uReadCursor = pBuffer->GetReadCursor();
	size_t uWriteCursor = pBuffer->GetWriteCursor();

	size_t uSize = pBuffer->GetLength();
	
	CLockScoped lock(_mutexSend);
	ASSERT_LOG_ERROR(_pSendWait);
	if (!_pSendWait->Write(*pBuffer)) {

		//还原
		pBuffer->SetReadCursor(uReadCursor);
		pBuffer->SetWriteCursor(uWriteCursor);
		return 0;
	}
	
	//还原
	pBuffer->SetReadCursor(uReadCursor);
	pBuffer->SetWriteCursor(uWriteCursor);
	
	//写入成功后
	_xElapseSend.ReStart();
	return uSize;
}

size_t IDataNet::SendData(const IDataSerialize& xSerialize)
{
	CLockScoped lock(_mutexSend);

	ASSERT_LOG_ERROR(_pSendWait);
	size_t uSizeBefore = _pSendWait->GetSize();
	if (!xSerialize.OnSerialize(_pSendWait)) {
		_pSendWait->Drop(_pSendWait->GetSize() - uSizeBefore);
		return 0;
	}

	//写入成功后
	_xElapseSend.ReStart();
	return _pSendWait->GetSize() - uSizeBefore;
}

bool IDataNet::RecvDataSplice(StreamBinaryPtr pBuffer, bool bBack /*= true*/)
{
	if (!pBuffer)return false;
	if (pBuffer->IsEmpty())return false;

	CLockScoped lock(_mutexRecv);

	//初始化接收缓冲区
	if (!_pRecving)
	{
		_pRecving = StreamBinaryPtr(new CStreamBinary());
		_pRecving->SetAlloc(CStreamBinary::ALLOC_WRITE_SIZE);
		_pRecving->SetBlockSize(_uBlockSize);
		if (_uRecvSize > 0) {
			_pRecving->SetAlloc(CStreamBinary::ALLOC_BLOCK_SIZE);
			_pRecving->SetBlockSize(_uRecvSize);
			_pRecving->SetMaxSize(_uRecvSize);
		}
	}
	return _pRecving->Splice(*pBuffer, bBack);
}

bool IDataNet::RecvDataSplice(StreamBufferPtr& pBuffer, bool bBack /*= true*/)
{
	if (!pBuffer)return false;
	if (pBuffer->IsEmpty())return false;
	
	StreamBinaryPtr ptr(new CStreamBinary());
	ptr->Splice(pBuffer);

	ToolFrame::SetPtrNull(pBuffer);

	return RecvDataSplice(ptr, bBack);
}

bool IDataNet::SwapSendBuffer()
{
	CLockScoped lock(_mutexSend);
	if (_pSending)return false;
	if (!_pSendWait)return false;
	if (_pSendWait->IsEmpty())return false;

	_pSending = _pSendWait->PopFrontBuffer();
	if (!_pSending)return false;
	if (_pSending->IsEmpty())return false;

	//统计发送用时
	MProtocol::Singleton().TimeElapsedSend(_xElapseSend.TimeElapsed());
	_xElapseSending.ReStart();
	return true;
}

bool IDataNet::SwapRecvBuffer()
{
	CLockScoped lock(_mutexRecv);
	if (!_pRecving)return false;
	if (_pRecving->IsEmpty())return false;
	if (_pRecved)return false;

	_pRecved = _pRecving;
	ToolFrame::SetPtrNull(_pRecving);
	return true;
}

bool IDataNet::IsRecvingEmpty() const
{
	CLockScoped lock(_mutexRecv);
	if (!_pRecving)return true;
	return _pRecving->IsEmpty();
}

bool IDataNet::ClearSendingBuffer()
{
	CLockScoped lock(_mutexSend);

	ToolFrame::SetPtrNull(_pSending);

	//统计发送用时
	MProtocol::Singleton().TimeElapsedSending(_xElapseSending.TimeElapsed());
	return true;
}

StreamBinaryPtr IDataNet::GetRecvedBuffer() const
{
	return _pRecved;
}

bool IDataNet::ClearRecvedBuffer()
{
	ToolFrame::SetPtrNull(_pRecved);
	return true;
}

StreamBinaryPtr IDataNet::GetSendData() const
{
// 	CLockScoped lock(_mutexSend);
// 	uint uSendSize		= _pSend	? _pSend->GetUsedSize():0;
// 	uint uSendingSize	= _pSending ? _pSending->GetUsedSize():0;
// 	uint uSendTotal		= uSendSize + uSendingSize;
// 	if (uSendTotal<=0)return StreamBufferPtr();
// 
// 	StreamBufferPtr ptr(new CStreamBufferMalloc(uSendTotal));
// 	if (_pSending)
// 		ptr->Write(_pSending->GetBuffer(),_pSending->GetUsedSize());
// 	if (_pSend)
// 		ptr->Write(_pSend->GetBuffer(),_pSend->GetUsedSize());
// 	return ptr;
	//SongJ
	return StreamBinaryPtr();
}

const XAcceptorKey& IDataNet::GetAccepterKey() const
{
	return _xAcceptorKey;
}

const std::string& IDataNet::GetConnectedAddress() const
{
	return _sAddress;
}

size_t IDataNet::GetSendBufferSize() const
{
	return _uSendSize;
}

size_t IDataNet::GetRecvBufferSize() const
{
	return _uRecvSize;
}

size_t IDataNet::GetBlockSize() const
{
	return _uBlockSize;
}

//数据会话
//////////////////////////////////////////////////////////////////////////
IDataSession::IDataSession(void)
{
	_bClosing = false;
	_bDelayRecv = false;
	
	SetClientID(INVALID_ID);
	SetLinkType(LINK_TYPE_INVAILD);
	SetErrCode(INVALID_ID);
	SetClosed(false);
	SetReceiver(nullptr);
	SetConnected(false);
	SetCallBackRecv(true);
}

IDataSession::~IDataSession(void)
{
	Close();
}

bool IDataSession::Close()
{
	return true;
}

bool IDataSession::IsDelayRecv() const
{
	return _bDelayRecv;
}

bool IDataSession::MarkDelayRecv()
{
	_bDelayRecv = true;
	return true;
}

bool IDataSession::ClearDelayRecv()
{
	_bDelayRecv = false;
	return true;
}

std::string IDataSession::GetRemoteAddress() const
{
	return "";
}

int64 IDataSession::ClearFreeTime()
{
	return _xTimeFree.ReStart();
}

CMutexRecursive & IDataSession::GetMutex() const
{
	return _mutex;
}

bool IDataSession::TryClosing()
{
	if (_bClosing)return false;
	_bClosing = true;
	return true;
}

bool IDataSession::IsClosing() const
{
	return _bClosing;
}

bool IDataSession::TryMarkNet( int eMarkNet )
{
	return _xBitNet.TryMark(eMarkNet);
}

bool IDataSession::TryClearNet( int eMarkNet ) 
{
	return _xBitNet.TryClear(eMarkNet);
}

bool IDataSession::TryMarkLogic( int eMarkLogic )
{
	return _xBitLogic.TryMark(eMarkLogic);
}

bool IDataSession::TryClearLogic( int eMarkLogic )
{
	return _xBitLogic.TryClear(eMarkLogic);
}

bool IDataSession::IsNetMarked( int eMarkNet ) const
{
	return _xBitNet.IsMarked(eMarkNet);
}

bool IDataSession::IsNetMarked() const
{
	return _xBitNet.IsMarked();
}

bool IDataSession::IsLogicMarked( int eMarkLogic ) const
{
	return _xBitLogic.IsMarked(eMarkLogic);
}

bool IDataSession::IsLogicMarked() const
{
	return _xBitLogic.IsMarked();
}

//接受器
//////////////////////////////////////////////////////////////////////////
IDataAcceptor::IDataAcceptor( void )
{
	SetLinkType(LINK_TYPE_INVAILD);
	SetReceiver(nullptr);
	_bClosed = false;
}

IDataAcceptor::~IDataAcceptor( void )
{

}

bool IDataAcceptor::ReqClose()
{
	CLockWrite lock(_mutexClosed);

	ASSERT_LOG_ERROR(!_bClosed);
	
	bool bResult = this->Close();
	_bClosed = true;
	return bResult;
}

bool IDataAcceptor::IsClosed()
{
	CLockRead lock(_mutexClosed);

	return _bClosed;
}

NS_TOOL_FRAME_END
