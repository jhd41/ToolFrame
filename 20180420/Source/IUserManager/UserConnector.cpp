#include "UserConnector.h"
#include "MSystem.h"
#include "ToolFrame.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN
//////////////////////////////////////////////////////////////////////////
bool HUserConnectorLog::OnConnected(CUserConnector* pConnector)
{
	ASSERT_LOG_ERROR(pConnector);
	LOG_SYSTEM("OnConnected"<<pConnector->GetConnectedAddress());
	return true;
}

bool HUserConnectorLog::OnConnectFaild(CUserConnector* pConnector)
{
	ASSERT_LOG_ERROR(pConnector);
	if (pConnector->GetServerAddress().empty())
	{
		LOG_SYSTEM("OnConnectFaild:ServerAddress Empty");
	}
	else
	{
		LOG_SYSTEM("OnConnectFaild" << ToolFrame::GetFront(pConnector->GetServerAddress()));
	}

	return true;
}

bool HUserConnectorLog::OnKeepHeartTimeOut(CUserConnector* pConnector)
{
	ASSERT_LOG_ERROR(pConnector);
	LOG_SYSTEM("OnKeepHeartTimeOut" << pConnector->GetConnectedAddress());
	return true;
}

bool ToolFrame::HUserConnectorLog::OnErrCacheFull(CUserConnector* pConnector, StreamBinaryPtr pBuffer)
{
	LOG_SYSTEM("OnErrCacheFull" << pConnector->GetConnectedAddress());
	return true;
}

bool HUserConnectorLog::OnHeartTimeOut(CUserConnector* pConnector)
{
	ASSERT_LOG_ERROR(pConnector);
	LOG_SYSTEM("OnHeartTimeOut" << pConnector->GetConnectedAddress());
	return true;
}

bool HUserConnectorLog::OnRefused(CUserConnector* pConnector)
{
	ASSERT_LOG_ERROR(pConnector);
	LOG_SYSTEM("OnRefused" << pConnector->GetConnectedAddress());
	return true;
}

bool HUserConnectorLog::OnSend(CUserConnector* pConnector, StreamBinaryPtr ptr, bool bSecret)
{
	return true;
}

bool HUserConnectorLog::OnRecved(CUserConnector* pConnector, IMsgStream& msgStream)
{
	return false;
}

bool HUserConnectorLog::OnStateChanged(CUserConnector* pConnector, int eState)
{
	return false;
}

bool HUserConnectorLog::OnDecryptFailed(CUserConnector* pConnector, void* pBuffer, size_t uLength)
{
	ASSERT_LOG_ERROR(pConnector);
	LOG_ERROR_MSG("OnDecryptFailed:" << pConnector->GetConnectedAddress());
	return true;
}

bool HUserConnectorLog::OnDecrypt(CUserConnector* pConnector, void* pBuffer, size_t uLength)
{
	return false;
}

bool HUserConnectorLog::OnEncryptFailed(CUserConnector* pConnector, void* pBuffer, size_t uLength)
{
	ASSERT_LOG_ERROR(pConnector);
	LOG_ERROR_MSG("OnEncryptFailed:" << pConnector->GetConnectedAddress());
	return true;
}

bool HUserConnectorLog::OnEncrypt(CUserConnector* pConnector, void* pBuffer, size_t uLength)
{
	return false;
}

bool HUserConnectorLog::OnRecvDecrypted(CUserConnector* pConnector, IMsgStream& msgStream)
{
	return false;
}

bool HUserConnectorLog::OnRecvEncrypted(CUserConnector* pConnector, IMsgStream& msgStream)
{
	return false;
}

bool HUserConnectorLog::OnDisconnected(CUserConnector* pConnector)
{
	ASSERT_LOG_ERROR(pConnector);
	LOG_SYSTEM("OnDisconnected" << pConnector->GetConnectedAddress());
	return true;
}

//////////////////////////////////////////////////////////////////////////
CUserConnector::CUserConnector(void)
{
	_hHandler	= nullptr;

	_uAssID		= INVALID_ID;
	_uSecretKey = 0;
	_uTimeServer= 0;
	_eState		= STATE_INVAILD;
	_bResend	= false;
	_nNetErrCode = NET_ERRCODE_INVAILD;
	_bEncryptTransmission = true;

	_bAutoKeepHeart = true;
	_tTimeCheck = 5;
	_tTimePing	= 250;
	_tTimeHeart.SetIntervalSec(270);

	_xTransitory.SetHandler(this);
	_xTransitory.SetEnabled(false);
	_xTransitory.SetResend(false);
	_xTransitory.SetKeepLink(true);
	_xTransitory.SetReconnectMax(-1);

	SetHandler(this);//仅仅为了防止崩溃 给定默认值
}

CUserConnector::~CUserConnector(void)
{
	_xTransitory.ShutDown(false);

	StopHeartCheck();
	StopKeepHeart();
}

bool CUserConnector::OnConnected( const CTransitoryLinker* pLinker )
{
	_tTimeHeart.ReStart();
	return _hHandler->OnConnected(this);
}

bool CUserConnector::OnConnectFaild( const CTransitoryLinker* pLinker )
{
	_nNetErrCode = pLinker->GetNetErrCode();
	return _hHandler->OnConnectFaild(this);
}

bool CUserConnector::OnDisconnected( const CTransitoryLinker* pLinker )
{
	//如果还未初始化完成就断开连接 则 认为服务器主动拒绝
	if (!_bResend)
		_xTransitory.ClearMsg();

	if (!_xTransitory.IsEnabled())
	{
		InvaildSecret(NET_ERRCODE_REFUSED);

		_hHandler->OnRefused(this);
		return _hHandler->OnDisconnected(this);
	}

	InvaildSecret(pLinker->GetNetErrCode());
	_xTransitory.SetEnabled(false);
	return _hHandler->OnDisconnected(this);
}

bool CUserConnector::OnSend( const CTransitoryLinker* pLinker, StreamBinaryPtr ptr,bool bSecret )
{
	if (!_hHandler->OnSend(this,ptr,bSecret))return false;

	_tTimeHeart.ReStart();//心跳包重新计时

	if (bSecret && IsEncryptTransmission())
	{
		//加密
		StreamBufferPtr pBuffer = ptr->ResetToStreamBuffer();
		size_t uLength = IMsgStream::GetBodyLength(pBuffer);
		if (uLength>0)
		{
			void* pBufferBody = IMsgStream::GetBodyBuffer(pBuffer);
			if ( !IsHasSecretKey() || !_hHandler->OnEncrypt(this, pBufferBody,uLength))
			{
				_hHandler->OnEncryptFailed(this, pBufferBody,uLength);
				return true;
			}
		}
	}
	return true;
}

bool CUserConnector::OnErrCacheFull(const CTransitoryLinker* pLinker, StreamBinaryPtr pBuffer)
{
	return _hHandler->OnErrCacheFull(this, pBuffer);
}

uint32 CUserConnector::GetSecretKey() const
{
	return _uSecretKey;
}

bool CUserConnector::IsHasSecretKey() const
{
	return INVALID_ID != _uAssID;
}

bool CUserConnector::SetServerAddress( const VectorString& vAddress )
{
	return _xTransitory.SetServerAddress(vAddress);
}

bool CUserConnector::SetServerAddress(const std::string& sAddress)
{
	if (sAddress.empty())return false;
	
	VectorString vAddress;
	vAddress.push_back(sAddress);
	return SetServerAddress(vAddress);
}

bool CUserConnector::OnRecved(const CTransitoryLinker* pLinker, IMsgStream& msgStream)
{
	if (_hHandler->OnRecved(this,msgStream))return true;

	if (_hHandler->OnRecvEncrypted(this, msgStream))return true;

	if (IsEncryptTransmission())
	{
		size_t uLength = msgStream.GetBodyLength();
		if (uLength > 0)
		{
			//取出来
			StreamBufferPtr	pBuffer = msgStream.ResetLoadStreamBuffer();

			void* pBufferBody = msgStream.GetBodyBuffer(pBuffer);
			if (!IsHasSecretKey() || !_hHandler->OnDecrypt(this, pBufferBody, uLength)) {
				_hHandler->OnDecryptFailed(this, pBufferBody, uLength);
				return true;
			}
		}
	}

	return _hHandler->OnRecvDecrypted(this, msgStream);
}

bool CUserConnector::SetHandler( HUserConnector* hHandler )
{
	_hHandler = hHandler;
	return true;
}

bool CUserConnector::Push(StreamBinaryPtr ptr,bool bSecret /*= true*/ )
{
	return _xTransitory.PushMsg(ptr,bSecret);
}

bool CUserConnector::Push(const IMsgStream& msgStream, bool bSecret /*= true*/)
{
	return Push(msgStream.GetSendStream(), bSecret);
}

bool CUserConnector::Disconnect(int nNetErrCode /*= NET_ERRCODE_ACTIVE*/, bool bClear /*= true*/)
{
	if (bClear)
		_xTransitory.ClearMsg();

	StopHeartCheck();
	StopKeepHeart();
	return _xTransitory.Stop(nNetErrCode);
}

bool CUserConnector::SetSecretKey(uint32 uAssID, uint32 uSecretKey, uint32 uTimeServer)
{
	_uAssID		= uAssID;
	_uSecretKey	= uSecretKey;
	_uTimeServer= uTimeServer;
	return true;
}

bool CUserConnector::SetEnabled(bool bEnabled)
{
	return _xTransitory.SetEnabled(bEnabled);
}

uint32 CUserConnector::GetAssID() const
{
	return _uAssID;
}

int CUserConnector::GetNetErrCode() const
{
	return _nNetErrCode;
}

bool CUserConnector::MarkReconnectFailed(int nNetErrCode /*= NET_ERRCODE_USER_RECONNECT_FAILD*/)
{
	InvaildSecret(nNetErrCode);
	return SetState(STATE_RECONNECT_FAILD);
}

bool CUserConnector::InvaildSecret( int nNetErrCode /*= NET_ERRCODE_ACTIVE*/ )
{
	_nNetErrCode	= nNetErrCode;
	_uAssID			= INVALID_ID;
	_xTransitory.ClearSendFaildBuffer();
	_xTransitory.Disconnect(nNetErrCode);
	return true;
}

bool CUserConnector::IsEncryptTransmission() const
{
	return _bEncryptTransmission;
}

bool CUserConnector::IsAutoKeepHeart() const
{
	return _bAutoKeepHeart;
}

bool CUserConnector::Send(StreamBinaryPtr ptr, bool bSecret /*= true*/)
{
	if (!ptr)return false;
	return _xTransitory.SendMsg(ptr,bSecret);
}

bool CUserConnector::Send(const IMsgStream& msgStream, bool bSecret /*= true*/)
{
	return Send(msgStream.GetSendStream(), bSecret);
}

bool CUserConnector::OnStateChanged(CTransitoryLinker* pLinker, int eState)
{
	switch (eState)
	{
	case CTransitoryLinker::STATE_CONNECT:
		SetState(STATE_CONNECT);
		break;
	case CTransitoryLinker::STATE_NORMAL:
		SetState(STATE_CONNECTED);
		break;
	case CTransitoryLinker::STATE_STOPING:
		SetState(STATE_STOPING);
		break;
	case CTransitoryLinker::STATE_STOP:
		_uAssID = INVALID_ID;
		SetState(STATE_STOP);
		break;
	default:
		break;
	}
	return true;
}

bool CUserConnector::SetState( EState eState )
{
	_eState = eState;
	_hHandler->OnStateChanged(this,eState);
	return true;
}

bool CUserConnector::MarkReconnect()
{
	return SetState(STATE_RECONNECT);
}

bool CUserConnector::MarkNormal()
{
	if (!SetEnabled(true))return false;
	SetState(STATE_NORMAL);

	if (IsAutoKeepHeart())
	{
		StartHeartCheck();
		StartKeepHeart();
	}
	return true;
}

bool CUserConnector::Connect()
{
	if (!_xTransitory.IsStoped())return false;
	_nNetErrCode = NET_ERRCODE_INVAILD;
	return _xTransitory.Connect();
}

bool CUserConnector::IsConnected() const
{
	return _xTransitory.IsConnected();
}

bool CUserConnector::ClearMsg()
{
	return _xTransitory.ClearMsg();
}

bool CUserConnector::SetReconnectMax(int nCount)
{
	return _xTransitory.SetReconnectMax(nCount);
}

bool CUserConnector::SetCacheMax( uint uCount )
{
	return _xTransitory.SetCacheMax(uCount);
}

bool CUserConnector::SetReSend(bool bResend)
{
	_bResend = bResend;
	return true;
}

bool CUserConnector::SetKeepLink(bool bKeepLink /*= true*/)
{
	return _xTransitory.SetKeepLink(bKeepLink);
}

bool CUserConnector::SetNetErrCode(int nNetErrCode)
{
	_nNetErrCode = nNetErrCode;
	return true;
}

bool CUserConnector::SetSendSize(size_t uSize)
{
	return _xTransitory.SetSendSize(uSize);
}

bool CUserConnector::SetRecvSize(size_t uSize)
{
	return _xTransitory.SetRecvSize(uSize);
}

bool CUserConnector::SetBlockSize(size_t uSize)
{
	return _xTransitory.SetBlockSize(uSize);
}

bool CUserConnector::SetEncryptTransmission(bool bEncrypt)
{
	_bEncryptTransmission = bEncrypt;
	return true;
}

bool CUserConnector::AutoKeepHeart(bool bAuto)
{
	_bAutoKeepHeart = bAuto;
	return true;
}

int CUserConnector::GetState() const
{
	return _eState;
}

bool CUserConnector::IsReSend() const
{
	return _bResend;
}

uint CUserConnector::GetClientID() const
{
	return _xTransitory.GetClientID();
}

bool CUserConnector::IsStoped() const
{
	return _xTransitory.IsStoped();
}

bool CUserConnector::StartHeartCheck()
{
	StopHeartCheck();

	if (_tTimeCheck <= 0)return false;
	if (_tTimeHeart.IsNeverTimeout())return false;

	_pTimerHeart = MSystem::Singleton().GetTimeOutQueque().CreateTimerByAfterSec(this,_tTimeCheck,true,_tTimeCheck);
	return true;
}

bool CUserConnector::StopHeartCheck()
{
	if (!_pTimerHeart)return false;

	MSystem::Singleton().GetTimeOutQueque().RemoveTimer(_pTimerHeart);
	ToolFrame::SetPtrNull(_pTimerHeart);
	return true;
}

bool CUserConnector::OnTimeOut( const CTimeNodePtr& pTimeNode )
{
	if (pTimeNode == _pTimerHeart)
	{
		//检查心跳是否超时
		if (IsConnected() && _tTimeHeart.IsTimeOut())
			_hHandler->OnHeartTimeOut(this);

		//检查保持心跳
		if (IsConnected() && _tTimeKeep.IsVaild() && !_tTimeKeep.IsTimeOut())
		{
			if (_tTimeHeart.IsTimeOutSec(ToolFrame::GetNowTime(),_tTimePing))
				_hHandler->OnKeepHeartTimeOut(this);
		}
		return true;
	}

	return false;
}

bool CUserConnector::SetHeartCheck( time_t tTimeCheck )
{
	_tTimeCheck = tTimeCheck;
	return true;
}

bool CUserConnector::SetHeartTimeOut( time_t tTimeOut )
{
	return _tTimeHeart.SetIntervalSec(tTimeOut);
}

bool CUserConnector::StartKeepHeart( time_t tTime/*= 0*/ )
{
	_tTimeKeep.SetVaild(true);
	_tTimeKeep.SetIntervalSec(tTime);
	_tTimeKeep.ReStart();
	return true;
}

bool CUserConnector::StopKeepHeart()
{
	return _tTimeKeep.SetVaild(false);
}

bool CUserConnector::SetHeartPing( time_t tTime )
{
	_tTimePing = tTime;
	return true;
}

const std::string& CUserConnector::GetConnectedAddress() const
{
	return _xTransitory.GetConnectedAddress();
}

const VectorString& CUserConnector::GetServerAddress() const
{
	return _xTransitory.GetServerAddress();
}

NS_TOOL_FRAME_END
