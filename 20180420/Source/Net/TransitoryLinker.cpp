#include "TransitoryLinker.h"
#include "MProtocol.h"

NS_TOOL_FRAME_BEGIN

CTransitoryLinker::CTransitoryLinker(void)
{
	_bKeepLink =false;
	_hHandler = nullptr;
	_bEnable = true;
	_bResend = false;
	_xMonitor.SetHandler(this);
}

CTransitoryLinker::~CTransitoryLinker(void)
{
}

bool CTransitoryLinker::SetServerAddress( const std::string& sAddress )
{
	return _xMonitor.SetServerAddress(sAddress);
}

bool CTransitoryLinker::SetServerAddress( const VectorString& vAddress )
{
	return _xMonitor.SetServerAddress(vAddress);
}

bool CTransitoryLinker::SetHandler( HTransitoryLinker* hHandler )
{
	_hHandler = hHandler;
	return true;
}

bool CTransitoryLinker::PushMsg(StreamBinaryPtr ptr,bool bSecret /*= true*/ )
{
	if (!ptr)return false;
	ptr->SetUserInt(bSecret);

	if (!_vCache.PushBack(ptr))
	{
		if (_hHandler)
			_hHandler->OnErrCacheFull(this,ptr);
		return false;
	}

	return CheckSendMsg();
}

bool CTransitoryLinker::TrySend()
{
	if (_vCache.IsEmpty())return true;
	if (!_xMonitor.IsConnected())
	{
		_xMonitor.Start();
		return false;
	}

	if (!_bEnable)return false;
	
	//发送之前发送失败的协议
	_xMonitor.Send(_pSendBuffer);

	//发送待发送协议
	StreamBinaryPtr ptr;
	while (ptr = _vCache.PopFront<StreamBinaryPtr>())
		SendMsg(ptr,!!ptr->GetUserInt());

	return true;
}

bool CTransitoryLinker::TryClose()
{
	if (_bKeepLink)return false;

	if (_vCache.IsEmpty())
		_xMonitor.Stop();

	return true;
}

bool CTransitoryLinker::OnConnected( CConnectMonitor* pConnectMonitor )
{
	if (_hHandler)
		_hHandler->OnConnected(this);

	CheckSendMsg();
	return true;
}

bool CTransitoryLinker::OnConnectFaild( CConnectMonitor* pConnectMonitor )
{
	if (_hHandler)
		_hHandler->OnConnectFaild(this);
	return true;
}

bool CTransitoryLinker::OnDisconnected( CConnectMonitor* pConnectMonitor )
{
	if (_bResend)
		_pSendBuffer = MProtocol::Singleton().GetSendData(pConnectMonitor->GetClientID());

	if (_hHandler)
		_hHandler->OnDisconnected(this);

	CheckSendMsg();
	return true;
}

bool CTransitoryLinker::OnRecved( CConnectMonitor* pConnectMonitor,ToolFrame::IMsgStream& msgStream)
{
	if (_hHandler)
		_hHandler->OnRecved(this,msgStream);

	CheckSendMsg();
	return true;
}

bool CTransitoryLinker::SetKeepLink( bool bKeepLink /*= true*/ )
{
	if (_bKeepLink == bKeepLink)return false;

	_bKeepLink = bKeepLink;
	return true;
}

bool CTransitoryLinker::IsKeepLink() const
{
	return _bKeepLink;
}

bool CTransitoryLinker::CheckSendMsg()
{
	CLockScoped lock(_mutex);

	TrySend();
	TryClose();
	return true;
}

size_t CTransitoryLinker::GetCacheCount() const
{
	return _vCache.GetCount();
}

bool CTransitoryLinker::Connect()
{
	return _xMonitor.Start();
}

bool CTransitoryLinker::Stop( int nNetErrCode /*= NET_ERRCODE_ACTIVE*/ )
{
	return _xMonitor.Stop(nNetErrCode);
}

bool CTransitoryLinker::SetEnabled( bool bEnabled )
{
	CLockScoped lock(_mutex);

	if (_bEnable == bEnabled)
		return _bEnable;

	_bEnable = bEnabled;

	if (_bEnable)
		TrySend();

	return _bEnable;
}

bool CTransitoryLinker::SetReconnectMax( int nCount )
{
	return _xMonitor.SetReconnectMax(nCount);
}

bool CTransitoryLinker::IsConnected() const
{
	return _xMonitor.IsConnected();
}

const VectorString& CTransitoryLinker::GetServerAddress() const
{
	return _xMonitor.GetServerAddress();
}

uint CTransitoryLinker::GetClientID() const
{
	return _xMonitor.GetClientID();
}

bool CTransitoryLinker::IsStoped() const
{
	return _xMonitor.IsStoped();
}

bool CTransitoryLinker::ShutDown( bool bCallBack /*= true*/ )
{
	return _xMonitor.ShutDown(bCallBack);
}

bool CTransitoryLinker::SetCacheMax( uint uCount )
{
	return _vCache.SetSizeMax(uCount);
}

size_t CTransitoryLinker::GetCacheMax() const
{
	return _vCache.GetSizeMax();
}

size_t CTransitoryLinker::GetCacheSize() const
{
	return _vCache.GetSize();
}

bool CTransitoryLinker::ClearMsg()
{
	return _vCache.Clear();
}

bool CTransitoryLinker::SetResend( bool bResend )
{
	_bResend = bResend;
	return true;
}

bool CTransitoryLinker::SetSendSize(size_t uSize)
{
	return _xMonitor.SetSendSize(uSize);
}

bool CTransitoryLinker::SetRecvSize(size_t uSize)
{
	return _xMonitor.SetRecvSize(uSize);
}

bool CTransitoryLinker::SetBlockSize(size_t uSize)
{
	return _xMonitor.SetBlockSize(uSize);
}

bool CTransitoryLinker::Disconnect( int nNetErrCode /*= NET_ERRCODE_ACTIVE*/ )
{
	return _xMonitor.Disconnect(nNetErrCode);
}

bool CTransitoryLinker::ClearSendFaildBuffer()
{
	return ToolFrame::SetPtrNull(_pSendBuffer);
}

int CTransitoryLinker::GetNetErrCode() const
{
	return _xMonitor.GetNetErrCode();
}

bool CTransitoryLinker::SendMsg(StreamBinaryPtr ptr, bool bSecret /*= true*/)
{
	if (_hHandler && !_hHandler->OnSend(this,ptr,bSecret))return false;

	return _xMonitor.Send(ptr);
}

bool CTransitoryLinker::OnStateChanged( CConnectMonitor* pConnectMonitor,int eState )
{
	int eStateThis = STATE_INVAILD;
	switch (eState)
	{
	case CConnectMonitor::STATE_INVAILD:
		eStateThis = STATE_INVAILD;
		break;
	case CConnectMonitor::STATE_CONNECT:
		eStateThis = STATE_CONNECT;
		break;
	case CConnectMonitor::STATE_NORMAL:
		eStateThis = STATE_NORMAL;
		break;
	case CConnectMonitor::STATE_STOPING:
		eStateThis = STATE_STOPING;
		break;
	case CConnectMonitor::STATE_STOP:
		eStateThis = STATE_STOP;
		break;
	case CConnectMonitor::STATE_RECONNECT:
		eStateThis = STATE_RECONNECT;
		break;
	}

	if (_hHandler)
		_hHandler->OnStateChanged(this,eStateThis);
	return true;
}

bool CTransitoryLinker::IsEnabled() const
{
	CLockScoped lock(_mutex);
	return _bEnable;
}

const std::string& CTransitoryLinker::GetConnectedAddress() const
{
	return _xMonitor.GetConnectedAddress();
}

NS_TOOL_FRAME_END
