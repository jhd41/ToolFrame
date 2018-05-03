#include "ConnectMonitor.h"

#include "MLoger.h"
#include "ToolFrame.h"

#include "MProtocol.h"
#include "MSystem.h"

NS_TOOL_FRAME_BEGIN

CConnectMonitor::CConnectMonitor(void)
{
	_uRealClientID	= INVALID_ID;
	_uClientID	= INVALID_ID;
	_eState		= STATE_INVAILD;
	_uRecvSize	= MProtocol::Singleton().GetRecvSize();
	_uSendSize	= MProtocol::Singleton().GetSendSize();
	_uBlockSize = MProtocol::Singleton().GetBlockSize();
	_bConnected = false;
	_bShutDown = false;

	_uFlushBegin = 0;
	_uFlushEnd = 0;

	SetID(INVALID_ID);
	SetUserInt(0);
	SetUserPtrNull();
	SetReconnectCount(0);
	SetReconnectMax(-1);
	SetHandler(nullptr);

	SetState(STATE_STOP);
}

CConnectMonitor::~CConnectMonitor(void)
{
	MSystem::Singleton().GetTimeOutQueque().RemoveTimer(_pTimerFlush);
	ToolFrame::SetPtrNull(_pTimerFlush);
	
	ShutDown(false);
}

bool CConnectMonitor::Start()
{
	if (IsShutDown())return false;
	if (STATE_STOP != GetState())return false;

	ToolFrame::TrimAddress(_vServerAddress);//再次整理
	if (GetServerAddress().empty())return false;
	
	SetReconnectCount(0);
	SetState(STATE_CONNECT);
	return true;
}

bool CConnectMonitor::Reconnect()
{
	//连接至中心服务器
	ASSERT_LOG_ERROR(INVALID_ID == _uRealClientID);
	_uRealClientID = MProtocol::Singleton().Connect(this,_vServerAddress,LINK_TYPE_NET_TCP,_uRecvSize,_uSendSize, _uBlockSize);
	ASSERT_LOG_ERROR(INVALID_ID != _uRealClientID);

	//重置最后一次
	_uClientID = _uRealClientID;
	ToolFrame::Clear(_sConnectedAddress);
	ToolFrame::Clear(_sRomoteIP);
	return true;
}

CConnectMonitor::EState CConnectMonitor::GetState() const
{
	return _eState;
}

bool CConnectMonitor::SetState( EState eState )
{
	if (_eState == eState)return true;

	//回收

	_eState = eState;

	//启动
	switch(_eState)
	{
	case STATE_CONNECT:
		{
			ASSERT_LOG_ERROR(Reconnect());
		}
		break;
	case STATE_STOPING:
		{

		}
		break;
	case STATE_STOP:
		{
			_uRealClientID = INVALID_ID;
		}
		break;
	case STATE_NORMAL:
		{

		}
		break;
	case STATE_RECONNECT:
		{
			ASSERT_LOG_DEBUG_ERR(IsCanReconnect());
			
			_uRealClientID = INVALID_ID;
			SetReconnectCount(GetReconnectCount() + 1 );
			SetState(STATE_CONNECT);
		}
		break;
	}

	if (GetHandler())
		GetHandler()->OnStateChanged(this,_eState);

	return true;
}

bool CConnectMonitor::RandTimer()
{
	//如果不随机 只 需要创建一个精确的计时器即可
	if (_uFlushBegin == _uFlushEnd) {
		if (!_pTimerFlush && _uFlushBegin >0)
			_pTimerFlush = MSystem::Singleton().GetTimeOutQueque().CreateTimerByAfterMil(this, _uFlushBegin,true, _uFlushBegin);
		return true;
	}

	//如果需要随机 为了防止性能大幅度降低，最多只为每秒创建一个计时器

	//清除计时器
	if (_pTimerFlush)
	{
		MSystem::Singleton().GetTimeOutQueque().RemoveTimer(_pTimerFlush);
		ToolFrame::SetPtrNull(_pTimerFlush);
	}

	//创建计时器
	uint uFlushTime = ToolFrame::Rand(_uFlushBegin, _uFlushEnd);
	if (uFlushTime > 0)
		_pTimerFlush = MSystem::Singleton().GetTimeOutQueque().CreateTimerByAfterSec(this, uFlushTime / 1000, true, uFlushTime / 1000);
	return true;
}

bool CConnectMonitor::OnConnected(UINT uClientID)
{
	ASSERT_LOG_ERROR(_uRealClientID == uClientID);	
	ASSERT_LOG_ERROR(!_bConnected);
	_bConnected				= true;

	if (STATE_CONNECT == GetState())
	{
		SetState(STATE_NORMAL);
		
		if (GetHandler())
			GetHandler()->OnConnected(this);
		return true;
	}
	LOG_ERROR_MSG(GetState());
	return true;
}

bool CConnectMonitor::OnConnectFailed( UINT uClientID )
{
	ASSERT_LOG_ERROR(_uRealClientID == uClientID);
	ASSERT_LOG_ERROR(!_bConnected);

	if (STATE_CONNECT == GetState())
	{
		SetState(STATE_STOP);

		if (!IsCanReconnect())
		{
			if (GetHandler())
				GetHandler()->OnConnectFaild(this);
			return true;
		}

		SetState(STATE_RECONNECT);
		return true;
	}
	if (STATE_STOPING == GetState())
	{
		SetState(STATE_STOP);
		
		if (GetHandler())
			GetHandler()->OnConnectFaild(this);
		return true;
	}
	LOG_ERROR_MSG(GetState());
	return true;
}

bool CConnectMonitor::OnDisconnected( UINT uClientID )
{
	ASSERT_LOG_ERROR(_uRealClientID == uClientID);
	
	_bConnected = false;

	if (STATE_NORMAL == GetState())
	{
		SetState(STATE_STOP);

		bool bCanReconnect = IsCanReconnect();
		
		if (GetHandler())
			GetHandler()->OnDisconnected(this);

		if (bCanReconnect)
			SetState(STATE_RECONNECT);
		return true;

	}
	if (STATE_STOPING == GetState())
	{
		SetState(STATE_STOP);

		if (GetHandler())
			GetHandler()->OnDisconnected(this);
		return true;
	}

	ASSERT_LOG_ERROR(GetState());
	return true;
}

bool CConnectMonitor::OnRecv( uint uClientID,IMsgStream& msgStream)
{
	ASSERT_LOG_ERROR(_uRealClientID == uClientID);

	if (GetHandler())
		return GetHandler()->OnRecved(this,msgStream);
	return true;
}

uint CConnectMonitor::OnRecv(IDataSession* pSession)
{
	if (GetHandler()) {
		uint uProcessed = GetHandler()->OnRecved(this, pSession);
		if (uProcessed > 0)
			return uProcessed;
	}

	return IDataReceiverStream::OnRecv(pSession);
}

bool CConnectMonitor::IsConnected() const
{
	return _bConnected;
}

bool CConnectMonitor::IsStoped() const
{
	return STATE_STOP == GetState();
}

bool CConnectMonitor::IsShutDown() const
{
	return _bShutDown;
}

bool CConnectMonitor::Send(StreamBinaryPtr ptr )const
{
	if (!ptr)return false;
	if (!IsConnected())return false;

	ASSERT_LOG_ERROR(INVALID_ID != _uRealClientID);

	return  MProtocol::Singleton().Send(_uRealClientID,ptr);
}

bool CConnectMonitor::Send(const void* pMsg, size_t uLen) const
{
	if (!pMsg)return false;
	if (uLen <= 0)return false;
	if (!IsConnected())return false;

	ASSERT_LOG_ERROR(INVALID_ID != _uRealClientID);

	return  MProtocol::Singleton().Send(_uRealClientID, pMsg, uLen);
}

bool CConnectMonitor::Send(const IDataSerialize& serialize) const
{
	if (!IsConnected())return false;

	ASSERT_LOG_ERROR(INVALID_ID != _uRealClientID);

	return  MProtocol::Singleton().Send(_uRealClientID, serialize);
}

bool CConnectMonitor::Send(const std::string& sMsg) const
{
	if (!IsConnected())return false;

	return  MProtocol::Singleton().Send(_uRealClientID, sMsg);
}

bool CConnectMonitor::Stop(int nNetErrCode /*= NET_ERRCODE_ACTIVE*/)
{
	switch (GetState())
	{
	case STATE_CONNECT:
		ASSERT_LOG_ERROR(INVALID_ID != _uRealClientID);
		MProtocol::Singleton().Disconnect(_uRealClientID, !_bShutDown,nNetErrCode);
		SetState(STATE_STOPING);
		return true;
		break;
	case STATE_NORMAL:
		ASSERT_LOG_ERROR(INVALID_ID != _uRealClientID);
		MProtocol::Singleton().Disconnect(_uRealClientID, !_bShutDown,nNetErrCode);
		SetState(STATE_STOPING);
		return true;
		break;
	case STATE_STOPING:
		return true;
		break;
	case STATE_STOP:
		return true;
		break;
	default:
		{
			LOG_ERROR();
			return false;
		}
		break;
	}

	return true;
}

uint CConnectMonitor::GetClientID() const
{
	return _uClientID;
}

uint ToolFrame::CConnectMonitor::GetRealClientID() const
{
	return _uRealClientID;
}

bool CConnectMonitor::SetRecvSize(size_t uSize)
{
	_uRecvSize = uSize;
	return true;
}

bool CConnectMonitor::SetSendSize(size_t uSize )
{
	_uSendSize = uSize;
	return true;
}

bool CConnectMonitor::SetBlockSize(size_t uSize)
{
	if (0 == uSize)return false;

	_uBlockSize = uSize;
	return true;
}

bool CConnectMonitor::ShutDown( bool bCallBack /*= true*/ )
{
	if (_bShutDown)return false;
	_bShutDown = true;

	if (!bCallBack)
		SetHandlerNull();

	Stop();
	if (INVALID_ID != _uRealClientID)
	{
		MProtocol::Singleton().Disconnect(_uRealClientID,false);
		OnDisconnected(_uRealClientID);
	}

	return true;
}

bool CConnectMonitor::IsCanReconnect() const
{
	if (GetReconnectMax() < 0)return true;

	return GetReconnectCount() + 1 < GetReconnectMax();
}

bool CConnectMonitor::Disconnect( int nNetErrCode /*= NET_ERRCODE_ACTIVE*/ )
{
	if (!IsConnected())return false;
	return MProtocol::Singleton().Disconnect(_uRealClientID, !_bShutDown,nNetErrCode);
}

bool CConnectMonitor::SetServerAddress( const std::string& sServerAddress )
{
	ToolFrame::Clear(_vServerAddress);
	_vServerAddress = ToolFrame::SplitAddress(sServerAddress);
	return true;
}

const std::string& CConnectMonitor::GetRomoteIP() const
{
	return ToolFrame::ConstCast(this)->GetRomoteIP();
}

const std::string& CConnectMonitor::GetRomoteIP()
{
	if (_sRomoteIP.empty() && INVALID_ID != _uRealClientID)
		_sRomoteIP = MProtocol::Singleton().GetRemoteAddress(_uRealClientID);

	return _sRomoteIP;
}

const std::string& CConnectMonitor::GetConnectedAddress() const
{
	return ToolFrame::ConstCast(this)->GetConnectedAddress();
}

const std::string& CConnectMonitor::GetConnectedAddress()
{
	if (_sConnectedAddress.empty() && INVALID_ID != _uRealClientID)
		_sConnectedAddress = MProtocol::Singleton().GetConnectedAddress(_uRealClientID);
	return _sConnectedAddress;
}

int CConnectMonitor::GetNetErrCode() const
{
	return MProtocol::Singleton().GetErrCode(_uClientID);//_uRealClientID
}

bool CConnectMonitor::SetFlushTime(uint uMillSec)
{
	return SetFlushTime(uMillSec, uMillSec);
}

bool CConnectMonitor::SetFlushTime(uint uMillSecBegin, uint uMillSecEnd)
{
	if (uMillSecBegin > uMillSecEnd)return false;

	_uFlushBegin = uMillSecBegin;
	_uFlushEnd	 = uMillSecEnd;

	RandTimer();
	return true;
}

bool CConnectMonitor::Push(StreamBinaryPtr ptr)
{
	return _xFlushBuffer.PushBack(ptr);
}

bool CConnectMonitor::OnTimeOut( const CTimeNodePtr& pTimeNode )
{
	if (_pTimerFlush == pTimeNode)
	{
		if (IsConnected())
		{
			StreamBinaryPtr ptr;
			while (ptr = _xFlushBuffer.PopFront<StreamBinaryPtr>())
				Send(ptr);
		}
		RandTimer();
		return true;
	}

	return false;
}

NS_TOOL_FRAME_END
