#include "IUserClient.h"
#include "ToolCPlus11.h"
#include "ToolStd.h"
#include "MProtocol.h"
#include "MDebug.h"

NS_TOOL_FRAME_BEGIN

IUserClient::IUserClient()
{
	_bEncryptTransmission = true;

	SetClientID(INVALID_ID);
	SetAssID(INVALID_ID);
	SetSrvID(INVALID_ID);
	SetConnected(false);
	SetClosed(false);
	SetActiveDisconnect(false);
	SetUserID(INVALID_ID);

	_tRecvMax = 0;
	_tRecvCount = 0;
	_uTimeOut = 300;
	_uSecretKey = MakeSecretKey();
}

IUserClient::~IUserClient()
{
	if (INVALID_ID != GetClientID()) {
		MProtocol::Singleton().Disconnect(_uClientID, false);
		_uClientID = INVALID_ID;
	}
}

bool IUserClient::SetTimeOut(uint uTimeOut)
{
	_uTimeOut = uTimeOut;
	return true;
}

bool IUserClient::SetRecvPack(uint uRecvMax, uint uRecvPer)
{
	_tRecvBegin.SetIntervalSec(uRecvPer);
	_tRecvMax = uRecvMax;
	return true;
}

bool IUserClient::SetEncryptTransmission(bool bEncrypt)
{
	_bEncryptTransmission = bEncrypt;
	return true;
}

bool IUserClient::Init(uint uSrvID, uint uClientID, uint uAssID)
{
	SetAssID(uAssID);
	SetSrvID(uSrvID);
	SetTopologyID(XTopologyID(uSrvID, uAssID));
	return true;
}

bool IUserClient::IsEncryptTransmission() const
{
	return _bEncryptTransmission;
}

uint32 IUserClient::MakeSecretKey()
{
	_uSecretKey = ToolFrame::Rand32();
	return _uSecretKey;
}

uint32 IUserClient::GetSecretKey() const
{
	return _uSecretKey;
}

bool IUserClient::SyncClientConnected(uint uClientID)
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IUserClient::OnClientConnected, this), uClientID);
}

bool IUserClient::SyncClientDisconnected()
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IUserClient::OnClientDisconnected, this));
}

bool IUserClient::SyncClientRecvStream(const IMsgStream& msgStream)
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IUserClient::OnClientRecvStream, this), msgStream);
}

bool IUserClient::SyncClientRecvBuffer(StreamBinaryPtr pMsgStream)
{
	if (!pMsgStream)return false;
	return GetOperateQueue().Operate(ToolFrame::Bind(&IUserClient::OnClientRecvBuffer, this), pMsgStream);
}

bool IUserClient::SyncClientUrlResponce(CUrlRequestTopologyPtr pRequest)
{
	if (!pRequest)return false;
	return GetOperateQueue().Operate(ToolFrame::Bind(&IUserClient::OnClientUrlResponce, this), pRequest);
}

bool IUserClient::SyncServerRecved(const XServerArg& xServerArg,const IMsgStream& msgBase)
{
	DEBUG_POINT_FUN();
	//校验UserID是否一样
	if (INVALID_ID != GetTopologyID().uUserID && GetTopologyID().uUserID != xServerArg.xSrcID.uUserID)return false;

	return GetOperateQueue().Operate(ToolFrame::Bind(&IUserClient::OnServerRecved, this), xServerArg, msgBase);
}

bool IUserClient::SyncCheck(time_t uTimeNow)
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IUserClient::OnCheck, this), uTimeNow);
}

bool IUserClient::SyncTimeOut(const CTimeNodePtr& pTimeNode)
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IUserClient::OnResolverTimeOut, this), pTimeNode);
}

bool IUserClient::SyncDisconnected(bool bActive /*= true*/)
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IUserClient::Disconnect, this), bActive);
}

bool IUserClient::SyncSendClient(const StreamBinaryPtr ptr, bool bSecret /*= true*/)
{
	return GetOperateQueue().Operate(ToolFrame::Bind((bool(IUserClient::*)(const StreamBinaryPtr, bool))&IUserClient::SendClient, this), ptr, bSecret);
}

bool IUserClient::SyncSendClient(const IMsgStream& msgStream, bool bSecret /*= true*/)
{
	return GetOperateQueue().Operate(ToolFrame::Bind((bool(IUserClient::*)(const IMsgStream&, bool))&IUserClient::SendClient, this), msgStream, bSecret);
}

bool IUserClient::SyncSendClient(const std::string& sMsg, bool bSecret /*= true*/)
{
	return GetOperateQueue().Operate(ToolFrame::Bind((bool(IUserClient::*)(const std::string&, bool))&IUserClient::SendClient, this), sMsg, bSecret);
}

bool IUserClient::SyncSendClient(const void* pBuffer, size_t uLen, bool bSecret /*= true*/)
{
	return GetOperateQueue().Operate(ToolFrame::Bind((bool(IUserClient::*)(const void*, size_t, bool))&IUserClient::SendClient, this), pBuffer, uLen, bSecret);
}

bool IUserClient::OnClientConnected(uint uClientID)
{
	ASSERT_LOG_ERROR(INVALID_ID == GetClientID());
	SetClientID(uClientID);

	ASSERT_LOG_ERROR(!IsConnected());
	SetConnected(true);

	//回调
	IUserClientResolver* pAc = FindTopUserClientResolver();
	if (!pAc)return false;
	if (!pAc->OnClientConnected())return false;
	Process();
	return true;
}

bool IUserClient::OnClientDisconnected()
{
	//回调
	IUserClientResolver* pAc = FindTopUserClientResolver();
	if (!pAc)return false;
	if (!pAc->OnClientDisconnected())return false;

	//回收
	{
		ASSERT_LOG_ERROR(IsConnected());
		SetConnected(false);

		ASSERT_LOG_ERROR(INVALID_ID != GetClientID());
		SetClientID(INVALID_ID);
	}

	Process();
	return true;
}

bool IUserClient::OnClientRecvStream(const IMsgStream& msgStream)
{
	//解密
	if (IsEncryptTransmission())
	{
		size_t uLength = msgStream.GetBodyLength();
		if (uLength > 0)
		{
			//取出来
			StreamBufferPtr	pBuffer = ToolFrame::ConstCast(msgStream).ResetLoadStreamBuffer();

			void* pBufferBody = msgStream.GetBodyBuffer(pBuffer);
			if (!OnDecrypt(pBufferBody, uLength))
			{
				OnDecryptFaild(pBufferBody, uLength);
				return false;
			}
		}
	}

	_tLastRecv.ReStart();//重置

	 //检测是否超过包上限
	if (!_tRecvBegin.IsNeverTimeout())
	{
		if (_tRecvBegin.IsTimeOut()) {
			_tRecvCount = 0;
			_tRecvBegin.ReStart();
		}
		++_tRecvCount;
		if (_tRecvCount > _tRecvMax)
		{
			LOG_CLIENT_ERR_MSG("ClientID:" << GetClientID() << " Too Many Recv!");
			Disconnect();
			return false;
		}
	}

	//回调上层逻辑
	IUserClientResolver* pAc = FindTopUserClientResolver();
	if (!pAc)return false;
	if (!pAc->OnClientRecv(msgStream))
		return pAc->OnClientRecvErr(msgStream);

	Process();
	return true;
}

bool IUserClient::OnClientRecvBuffer(StreamBinaryPtr pMsgStream)
{
	_tLastRecv.ReStart();//重置

						 //检测是否超过包上限
	if (!_tRecvBegin.IsNeverTimeout())
	{
		if (_tRecvBegin.IsTimeOut()) {
			_tRecvCount = 0;
			_tRecvBegin.ReStart();
		}
		++_tRecvCount;
		if (_tRecvCount > _tRecvMax)
		{
			LOG_CLIENT_ERR_MSG("ClientID:" << GetClientID() << " Too Many Recv!");
			Disconnect();
			return false;
		}
	}

	//回调上层逻辑
	IUserClientResolver* pAc = FindTopUserClientResolver();
	if (!pAc)return false;
	if (!pAc->OnClientRecv(pMsgStream))
		return pAc->OnClientRecvErr(pMsgStream);
	Process();
	return true;
}

bool IUserClient::OnClientUrlResponce(CUrlRequestTopologyPtr pRequest)
{
	//回调上层逻辑
	IUserClientResolver* pAc = FindTopUserClientResolver();
	if (!pAc)return false;
	if (!pAc->OnClientUrlResponce(pRequest))
		return pAc->OnClientUrlResponceErr(pRequest);
	Process();
	return true;
}

bool IUserClient::OnServerRecved(const XServerArg& xServerArg,const IMsgStream& msgBase)
{
	DEBUG_POINT_FUN();

	IUserClientResolver* pAc = FindTopUserClientResolver();
	if (!pAc)return false;
	if (!pAc->OnServerRecved(xServerArg, msgBase))return false;

	Process();
	return true;
}

bool IUserClient::OnCheck(time_t uTimeNow)
{
	if (_tLastRecv.IsTimeOutSec(uTimeNow, _uTimeOut))
	{
		LOG_CLIENT_ERR_MSG("ClientID:" << GetClientID() << " HeartOut!");
		Disconnect();
		return true;
	}

	return false;
}

bool IUserClient::OnResolverTimeOut(const CTimeNodePtr& pTimeNode)
{
	return IResolverManager::ResolveTimeOut(pTimeNode);
}

bool IUserClient::SendClient(const IMsgStream& msgStream, bool bSecret /*= true*/)
{
	return Send(msgStream, bSecret);
}

bool IUserClient::SendClient(const StreamBinaryPtr ptr, bool bSecret /*= true*/)
{
	if (!ptr)return false;
	if (!IsConnected())
	{
		if (IsActiveDisconnect())return false;

		//如果有缓存 添加至缓存
		return false;

	}
	return Send(ptr, bSecret);
}

bool IUserClient::SendClient(const std::string& sMsg, bool bSecret /*= true*/)
{
	if (sMsg.empty())return false;

	return SendClient(StreamBinaryPtr(new CStreamBinary(sMsg.c_str(), sMsg.length())), bSecret);
}

bool IUserClient::SendClient(const void* pBuffer, size_t uLen, bool bSecret /*= true*/)
{
	if (!pBuffer)return false;
	if (uLen <= 0)return false;

	return SendClient(StreamBinaryPtr(new CStreamBinary(pBuffer, uLen)), bSecret);
}

bool IUserClient::Disconnect(bool bActive)
{
	if (!IsConnected())return false;

	SetActiveDisconnect(bActive);
	MProtocol::Singleton().Disconnect(_uClientID);
	return true;
}

int IUserClient::FindConnectServer(int eSrvType)
{
	return ToolFrame::GetValueByKey(_vServerConnect, eSrvType, INVALID_ID);
}

bool IUserClient::RemoveConnectServer(int eSrvType)
{
	return ToolFrame::EraseByKey(_vServerConnect, eSrvType) > 0;
}

bool IUserClient::AddConnectServer(int eSrvType, int nSrvID)
{
	return ToolFrame::Insert(_vServerConnect, eSrvType, nSrvID);
}

bool IUserClient::SetConnectServer(const MapIntInt& vServerConnect)
{
	_vServerConnect = vServerConnect;
	return true;
}

bool IUserClient::Send(const IMsgStream& msgStream, bool bSecret /*= true*/)
{
	return Send(msgStream.GetSendStream(), bSecret);
}

bool IUserClient::Send(const StreamBinaryPtr ptr, bool bSecret /*= true*/)
{
	if (!ptr)return false;
	if (!OnSend(ptr, bSecret))return false;
	
	DEBUG_POINT();
	return MProtocol::Singleton().Send(GetClientID(), ptr);
}

bool IUserClient::OnSend(StreamBinaryPtr ptr, bool bSecret)
{
	//加密
	if (bSecret && IsEncryptTransmission())
	{
		//取出流
		StreamBufferPtr pBuffer = ptr->ResetToStreamBuffer();
		ASSERT_LOG_ERROR(pBuffer);

		size_t uLength = IMsgStream::GetBodyLength(pBuffer);
		if (uLength > 0)
		{
			void* pBufferBody = IMsgStream::GetBodyBuffer(pBuffer);
			if (!OnEncrypt(pBufferBody, uLength))
			{
				OnEncryptFaild(pBufferBody, uLength);
				return false;
			}
		}
	}

	return true;
}

bool IUserClient::OnEncrypt(void* pBuffer, size_t uLength)
{
	return true;
}

bool IUserClient::OnDecrypt(void* pBuffer, size_t uLength)
{
	return true;
}

bool IUserClient::OnEncryptFaild(void* pBuffer, size_t uLength)
{
	LOG_ERROR_MSG_CLASS(uLength);
	return true;
}

bool IUserClient::OnDecryptFaild(void* pBuffer, size_t uLength)
{
	LOG_ERROR_MSG_CLASS(uLength);
	return true;
}

IUserClientResolver* IUserClient::FindTopUserClientResolver()
{
	return dynamic_cast<IUserClientResolver*>(FindTopResolver());
}

bool IUserClient::OnResolveTimeOut(IResolverManager* pMgrResolver, const CTimeNodePtr& pTimeNode)
{
	GetOperateQueue().PushOperate(ToolFrame::Bind(&IUserClient::OnResolverTimeOut, this), pTimeNode);
	ReqMgrOperate();
	return true;
}

bool IUserClient::OnResolveOver(IResolverManager* pMgrResolver)
{
	return MarkDeleted();
}

NS_TOOL_FRAME_END

