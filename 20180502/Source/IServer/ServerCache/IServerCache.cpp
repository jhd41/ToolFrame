#include "IServerCache.h"

#include "MLoger.h"
#include "ServerCacheManager.h"
#include "ToolFrame.h"
#include "MDebug.h"

NS_TOOL_FRAME_BEGIN
//////////////////////////////////////////////////////////////////////////
bool HServerCacheLog::OnCacheCreateErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	LOG_ERROR_MSG("UserID:" << xSrcID.uUserID << " UserInt:" << nUserInt);
	return true;
}

bool HServerCacheLog::OnCacheDestoryErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	LOG_ERROR_MSG("UserID:" << xSrcID.uUserID << " UserInt:" << nUserInt);
	return true;
}

bool HServerCacheLog::OnCacheConnectedErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	LOG_ERROR_MSG("UserID:" << xSrcID.uUserID << " UserInt:" << nUserInt);
	return true;
}

bool HServerCacheLog::OnCacheConnectErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	LOG_ERROR_MSG("UserID:" << xSrcID.uUserID << " UserInt:" << nUserInt);
	return true;
}

bool HServerCacheLog::OnCacheDisconnectErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	LOG_ERROR_MSG("UserID:" << xSrcID.uUserID << " UserInt:" << nUserInt);
	return true;
}

bool HServerCacheLog::OnCacheProcessMsgErr(IServerCachePtr pCache, const XTopologyID& xSrcID, const XServerArg& xServerArg, const IMsgStream& msgBase)
{
	LOG_CLIENT_ERR_MSG("UserID:"<< xSrcID.uUserID<<" OpCode:"<< msgBase.GetOpCode());
	return true;
}

bool HServerCacheLog::OnCacheProcessMsgErr(IServerCachePtr pCache, const XTopologyID& xSrcID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer)
{
	ASSERT_LOG_ERROR(pBuffer);
	LOG_CLIENT_ERR_MSG("UserID:" << xSrcID.uUserID << " BufferSize:" << pBuffer->GetSize());
	return true;
}

bool HServerCacheLog::OnCacheUrlResponceErr(IServerCachePtr pCache, CUrlRequestTopologyPtr pRequest)
{
	LOG_ERROR_MSG("UserID:" << pCache->GetCacheID() << " Url:" << pRequest->GetUrl()<<" Responce:"<< pRequest->GetResponseData());
	return true;
}

bool HServerCacheLog::OnCacheLoginErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	LOG_ERROR_MSG("UserID:" << xSrcID.uUserID << " UserInt:" << nUserInt);
	return true;
}

bool HServerCacheLog::OnCacheKickErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	LOG_ERROR_MSG("UserID:" << xSrcID.uUserID << " UserInt:" << nUserInt);
	return true;
}

bool HServerCacheLog::OnCacheSaveErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	LOG_ERROR_MSG("UserID:" << xSrcID.uUserID << " UserInt:" << nUserInt);
	return true;
}

bool HServerCacheLog::OnCacheSendErr(IServerCachePtr pCache, const XTopologyID& xSrcID, const IMsgStream& msgBase)
{
	LOG_ERROR_MSG("UserID:" << xSrcID.uUserID << " OpCode:" << msgBase.GetOpCode());
	return true;
}

bool HServerCacheLog::OnCacheSendErr(IServerCachePtr pCache, const XTopologyID& xSrcID, StreamBinaryPtr pBuffer)
{
	LOG_ERROR_MSG("UserID:" << xSrcID.uUserID << " BufferSize:" << pBuffer->GetSize());
	return true;
}

bool HServerCacheLog::OnCacheOperateErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	LOG_ERROR_MSG("UserID:" << xSrcID.uUserID << " nUserInt:" << nUserInt);
	return true;
}
//////////////////////////////////////////////////////////////////////////
IServerCache::IServerCache()
{
	_hCacheHandler = this;

	_bSingle = true;
	_bCreated = false;

	SetOperateDelay(true);
}

IServerCache::~IServerCache()
{
}

bool IServerCache::SetCacheID(uint uCacheID)
{
	return SetProcesserID(uCacheID);
}

bool IServerCache::SetCacheHandler(HServerCache* hHandler)
{
	_hCacheHandler = hHandler;
	return true;
}

uint IServerCache::GetCacheID() const
{
	return GetProcesserID();
}

IServerCachePtr IServerCache::GetCachePtr()
{
	return ToolFrame::DynamicCast<IServerCachePtr>(shared_from_this());
}

bool IServerCache::SetSingle(bool bSingle)
{
	_bSingle = bSingle;
	return true;
}

bool IServerCache::IsSingle() const
{
	return _bSingle;
}

bool IServerCache::RemoveTopologyID(const XTopologyID& xTopologyID)
{
	if (TOPOLOGY_ID_INVAILD == xTopologyID)return false;

	return ToolFrame::EraseByValue(_vTopologyID, xTopologyID);
}

bool IServerCache::AddTopologyID(const XTopologyID& xTopologyID)
{
	if (TOPOLOGY_ID_INVAILD == xTopologyID)return false;
	
	return ToolFrame::Insert(_vTopologyID, xTopologyID);
}

const VectorTopologyID& IServerCache::GetTopologyID() const
{
	return _vTopologyID;
}

bool IServerCache::ClearTopologyID()
{
	return ToolFrame::Clear(_vTopologyID);
}

bool IServerCache::IsTopologyIDEmpty() const
{
	return ToolFrame::IsEmpty(_vTopologyID);
}

bool IServerCache::IsHasTopologyID(const XTopologyID& xTopologyID) const
{
	return ToolFrame::IsHasValue(_vTopologyID, xTopologyID);
}

const XTopologyID& IServerCache::GetTopologyIDSingle() const
{
	return ToolFrame::IsEmpty(_vTopologyID) ? TOPOLOGY_ID_INVAILD : ToolFrame::GetFront(_vTopologyID);
}

const CDateTime& IServerCache::GetTimeUpdate() const
{
	return _tTimeUpdate;
}

bool IServerCache::MarkUpdated()
{
	_tTimeUpdate.SetNowTime();
	return true;
}

bool IServerCache::MarkSaved()
{
	_tTimeSave.SetNowTime();
	return true;
}

const CDateTime& IServerCache::GetTimeSave() const
{
	return _tTimeSave;
}

bool IServerCache::SyncCreate(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IServerCache::OnCreate, this), xSrcID, pUserData, nUserInt);
}

bool IServerCache::SyncDestory(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IServerCache::OnCacheDestory, this), xSrcID, pUserData, nUserInt);
}

bool IServerCache::SyncConnect(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IServerCache::OnCacheConnect, this), xSrcID, pUserData, nUserInt);
}

bool IServerCache::SyncConnected(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IServerCache::OnCacheConnected, this), xSrcID, pUserData, nUserInt);
}

bool IServerCache::SyncDisconnect(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IServerCache::OnCacheDisconnect, this), xSrcID, pUserData, nUserInt);
}

bool IServerCache::SyncProcessMsg(const XTopologyID& xSrcID, const XServerArg& xServerArg, const IMsgStream& msgBase)
{
	DEBUG_POINT_TAG("IServerCache::SyncProcessMsg IMsgStream");
	return GetOperateQueue().Operate(ToolFrame::Bind((bool(IServerCache::*)(const XTopologyID&, const XServerArg&, const IMsgStream&))&IServerCache::OnCacheProcessMsg, this), xSrcID, xServerArg, msgBase);
}

bool IServerCache::SyncProcessMsg(const XTopologyID& xSrcID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer)
{
	DEBUG_POINT_TAG("IServerCache::SyncProcessMsg StreamBinaryPtr");
	return GetOperateQueue().Operate(ToolFrame::Bind((bool(IServerCache::*)(const XTopologyID&, const XServerArg&, StreamBinaryPtr))&IServerCache::OnCacheProcessMsg, this), xSrcID, xServerArg, pBuffer);
}

bool IServerCache::SyncUrlResponce(CUrlRequestTopologyPtr pRequest)
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IServerCache::OnCacheUrlResponce, this), pRequest);
}

bool IServerCache::SyncSave(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IServerCache::OnCacheSave, this), xSrcID, pUserData, nUserInt);
}

bool IServerCache::SyncKick(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IServerCache::OnCacheKick, this), xSrcID,pUserData, nUserInt);
}

bool IServerCache::SyncLogin(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IServerCache::OnCacheLogin, this), xSrcID, pUserData, nUserInt);
}

bool IServerCache::SyncSend(const XTopologyID& xSrcID, const IMsgStream& msgBase)
{
	return GetOperateQueue().Operate(ToolFrame::Bind((bool(IServerCache::*)(const XTopologyID&, const IMsgStream&))&IServerCache::OnCacheSend, this), xSrcID, msgBase);
}

bool IServerCache::SyncSend(const XTopologyID& xSrcID, StreamBinaryPtr pBuffer)
{
	return GetOperateQueue().Operate(ToolFrame::Bind((bool(IServerCache::*)(const XTopologyID&, StreamBinaryPtr))&IServerCache::OnCacheSend, this), xSrcID, pBuffer);
}

bool IServerCache::SyncOperate(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return GetOperateQueue().Operate(ToolFrame::Bind(&IServerCache::OnCacheOperate, this), xSrcID, pUserData, nUserInt);
}

bool IServerCache::OnCreate(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	ClearDeleted();

	if (!_bCreated)
	{
		_bCreated = true;

		if (!_hCacheHandler->OnCacheCreate(GetCachePtr(), xSrcID, pUserData, nUserInt))
			_hCacheHandler->OnCacheCreateErr(GetCachePtr(), xSrcID, pUserData, nUserInt);
	}

	return true;
}

bool IServerCache::OnCacheDestory(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	//如果还有效则不能删除
	if (IsVaild())
		return true;

	if (_bCreated)
	{
		_bCreated = false;
		if (!_hCacheHandler->OnCacheDestory(GetCachePtr(), xSrcID, pUserData, nUserInt))
			_hCacheHandler->OnCacheDestoryErr(GetCachePtr(), xSrcID, pUserData, nUserInt);
	}

	ClearVaild();
	ClearNormal();
	MarkDeleted();
	return true;
}

bool IServerCache::OnCacheConnect(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	//如果单点登录 需要踢下线
	if (IsSingle() && !IsTopologyIDEmpty()) {
		OnCacheKick			(GetTopologyIDSingle(), pUserData, nUserInt);
		OnCacheDisconnect	(GetTopologyIDSingle(), pUserData, nUserInt);
	}

	//连接成功就标记为需要(自增1)
	if (IsTopologyIDEmpty())
		MarkVaild();

	ASSERT_LOG_ERROR(AddTopologyID(xSrcID));
	
	if (!_hCacheHandler->OnCacheConnect(GetCachePtr(), xSrcID, pUserData, nUserInt)) {
		_hCacheHandler->OnCacheConnectErr(GetCachePtr(), xSrcID, pUserData, nUserInt);
		return true;
	}
		
	MarkUpdated();
	return true;
}

bool IServerCache::OnCacheConnected(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	if (!_hCacheHandler->OnCacheConnected(GetCachePtr(), xSrcID, pUserData, nUserInt)) {
		_hCacheHandler->OnCacheConnectedErr(GetCachePtr(), xSrcID, pUserData, nUserInt);
		return true;
	}
		
	MarkUpdated();
	return true;
}

bool IServerCache::OnCacheDisconnect(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	if (!IsVaild())return true;

	if (IsTopologyIDEmpty())return true;

	//断线兼容性修复
	//如果是单点登录，需要把之前的断开连接
	XTopologyID xTopologyID = xSrcID;
	if (IsSingle() && TOPOLOGY_ID_INVAILD == xTopologyID) {
		if (TOPOLOGY_ID_INVAILD == GetTopologyIDSingle())
			return true;

		xTopologyID = GetTopologyIDSingle();
	}

	if (!_hCacheHandler->OnCacheDisconnect(GetCachePtr(), xSrcID, pUserData, nUserInt))
		_hCacheHandler->OnCacheDisconnectErr(GetCachePtr(), xSrcID, pUserData, nUserInt);

		MarkUpdated();
	if (!RemoveTopologyID(xSrcID))return true;

	//全部断开连接就标记为不需要(自减1)
	if (IsTopologyIDEmpty())
		ClearVaild();
	return true;
}

bool IServerCache::OnCacheProcessMsg(const XTopologyID& xSrcID, const XServerArg& xServerArg, const IMsgStream& msgBase)
{
	DEBUG_POINT_TAG("IServerCache::OnCacheProcessMsg");

	if (!_hCacheHandler->OnCacheProcessMsg(GetCachePtr(), xSrcID, xServerArg, msgBase)) {
		if (!IsNormal() && IsOperateDelay())
			return false;

		_hCacheHandler->OnCacheProcessMsgErr(GetCachePtr(), xSrcID, xServerArg, msgBase);
		return true;
	}	

	MarkUpdated();
	return true;
}

bool IServerCache::OnCacheProcessMsg(const XTopologyID& xSrcID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer)
{
	if (!_hCacheHandler->OnCacheProcessMsg(GetCachePtr(), xSrcID, xServerArg, pBuffer)) {
		if (!IsNormal() && IsOperateDelay())
			return false;

		_hCacheHandler->OnCacheProcessMsgErr(GetCachePtr(), xSrcID, xServerArg, pBuffer);
		return true;
	}

	MarkUpdated();
	return true;
}

bool IServerCache::OnCacheUrlResponce(CUrlRequestTopologyPtr pRequest)
{
	if (!_hCacheHandler->OnCacheUrlResponce(GetCachePtr(), pRequest))
		_hCacheHandler->OnCacheUrlResponceErr(GetCachePtr(), pRequest);

	MarkUpdated();
	return true;
}

bool IServerCache::OnCacheSave(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	if (GetTimeSave() < GetTimeUpdate()) {
		if (!_hCacheHandler->OnCacheSave(GetCachePtr(), xSrcID, pUserData, nUserInt)) {
			_hCacheHandler->OnCacheSaveErr(GetCachePtr(), xSrcID, pUserData, nUserInt);
			return true;
		}
			
		MarkSaved();
		return true;
	}
	return true;
}

bool IServerCache::OnCacheKick(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	if (!_hCacheHandler->OnCacheKick(GetCachePtr(), xSrcID,pUserData, nUserInt)) {
		_hCacheHandler->OnCacheKickErr(GetCachePtr(), xSrcID, pUserData, nUserInt);
		return true;
	}
	MarkUpdated();
	return true;
}

bool IServerCache::OnCacheLogin(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	if (!_hCacheHandler->OnCacheLogin(GetCachePtr(), xSrcID,pUserData, nUserInt)) {
		_hCacheHandler->OnCacheLoginErr(GetCachePtr(), xSrcID, pUserData, nUserInt);
		return true;
	}
	MarkUpdated();
	return true;
}

bool IServerCache::OnCacheSend(const XTopologyID& xSrcID, const IMsgStream& msgBase)
{
	if (!_hCacheHandler->OnCacheSend(GetCachePtr(), xSrcID, msgBase)) {
		_hCacheHandler->OnCacheSendErr(GetCachePtr(), xSrcID, msgBase);
		return true;
	}
	MarkUpdated();
	return true;
}

bool IServerCache::OnCacheSend(const XTopologyID& xSrcID, StreamBinaryPtr pBuffer)
{
	if (!_hCacheHandler->OnCacheSend(GetCachePtr(), xSrcID, pBuffer)) {
		_hCacheHandler->OnCacheSendErr(GetCachePtr(), xSrcID, pBuffer);
		return true;
	}
	MarkUpdated();
	return true;
}

bool IServerCache::OnCacheOperate(const XTopologyID& xSrcID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	if (!_hCacheHandler->OnCacheOperate(GetCachePtr(), xSrcID, pUserData, nUserInt)) {
		_hCacheHandler->OnCacheOperateErr(GetCachePtr(), xSrcID, pUserData, nUserInt);
		return true;
	}
		
	MarkUpdated();
	return true;
}

NS_TOOL_FRAME_END
