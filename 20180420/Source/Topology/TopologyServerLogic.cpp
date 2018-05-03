#include "TopologyServerLogic.h"
#include "MProtocol.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

CTopologyServerLogic::CTopologyServerLogic(void)
{
	_uServerID = INVALID_ID;
	_eSrvType = INVALID_ID;
	_uThread = 0;
	_uHash = 0;
	_uHashCount = 0;
	_uPort = 0;
	_uSendSize = MProtocol::Singleton().GetSendSize();
	_uRecvSize = MProtocol::Singleton().GetRecvSize();
	_uBlockSize= MProtocol::Singleton().GetBlockSize();
}

CTopologyServerLogic::~CTopologyServerLogic(void)
{
}

bool CTopologyServerLogic::Init()
{
	return true;
}

bool CTopologyServerLogic::Clear()
{
	_vLogic.clear();
	ClearConfig();
	return true;
}

bool CTopologyServerLogic::AddServer( const XServerLogic& xServer )
{
	//检查合法性
	XServerLogic* pLogic = (XServerLogic*)FindLogicByServerID(xServer.uServerID);
	if (pLogic){
		CLockWrite lock(pLogic->mutex);
		*pLogic = xServer;
		return true;
	}

	//插入
	if (!ToolFrame::Insert(_vLogic,xServer.uServerID,xServer))return false;

	pLogic = (XServerLogic*)FindLogicByServerID(xServer.uServerID);
	if (!pLogic)return false;

	return ToolFrame::InsertVector(_vTypeLogic,xServer.eSrvType,pLogic);
}

bool CTopologyServerLogic::AddServer( const VectorLogic& vLogic )
{
	bool bSucceed = true;
	VectorLogic::const_iterator itr;
	foreach(itr,vLogic){
		bSucceed &= AddServer(*itr);
	}

	return bSucceed;
}

bool CTopologyServerLogic::RemoveLogicByServerID( uint uServerID )
{
	XServerLogic* pLogic = ToolFrame::GetValuePtrByKey(_vLogic,uServerID);
	if (!pLogic)return false;

	CLockWrite lock(pLogic->mutex);
	pLogic->xUpdate.eState	= CONNECT_STATE_OFFLINE;
	pLogic->uClientID		= INVALID_ID;
	return true;
}

const XServerLogic* CTopologyServerLogic::FindLogicByServerID( uint uServerID ) const
{
	return ToolFrame::GetValuePtrByKey(_vLogic,uServerID);
}

const XServerLogic* CTopologyServerLogic::FindLogicByClientID( uint uClientID ) const
{
	MapLogic::const_iterator itr;
	foreach(itr,_vLogic){
		const XServerLogic& xLogic = itr->second;
		if (xLogic.uClientID == uClientID)
			return &xLogic;
	}

	return nullptr;
}

bool CTopologyServerLogic::UpdateLogicState(uint uServerID,const XLogicUpdate& xUpdate )
{
	XServerLogic* pLogic = (XServerLogic*)FindLogicByServerID(uServerID);
	if (!pLogic)return false;

	CLockWrite lock(pLogic->mutex);

	pLogic->bUpdated	= true;
	pLogic->xUpdate		= xUpdate;

	return true;
}

bool CTopologyServerLogic::UpdateDebugString(uint uServerID, const std::string& sDebugString)
{
	XServerLogic* pLogic = (XServerLogic*)FindLogicByServerID(uServerID);
	if (!pLogic)return false;

	CLockWrite lock(pLogic->mutex);

	pLogic->bUpdated = true;
	pLogic->sDebugString = sDebugString;
	
	return true;
}

std::string CTopologyServerLogic::GetDebugString() const
{
	CLockRead lockAll(_xMutexLogic);
	
	std::stringstream sStream;

	MapLogic::const_iterator itr;
	foreach(itr, _vLogic) {
		const XServerLogic& xLogic = itr->second;
		if (!xLogic.sDebugString.empty())
		{
			sStream << "ServerID:"<<xLogic.uServerID<<" ServerType:"<< (int)xLogic.eSrvType<<std::endl;
			sStream << xLogic.sDebugString<<std::endl;
		}
	}
	return sStream.str();
}

bool CTopologyServerLogic::IsLogicEmpty() const
{
	CLockRead lockAll(_xMutexLogic);
	return _vLogic.empty();
}

bool CTopologyServerLogic::SetServerID( uint uServerID )
{
	_uServerID = uServerID;
	return true;
}

bool CTopologyServerLogic::SetSrvType( int eSrvType )
{
	_eSrvType = eSrvType;
	return true;
}

bool CTopologyServerLogic::SetPort( uint uPort )
{
	_uPort = uPort;
	return true;
}

bool CTopologyServerLogic::SetHash( uint uHash )
{
	_uHash = uHash;
	return true;
}

bool CTopologyServerLogic::SetSendSize( uint uSize )
{
	_uSendSize = uSize;
	return true;
}

bool CTopologyServerLogic::SetRecvSize( uint uSize )
{
	_uRecvSize = uSize;
	return true;
}

bool CTopologyServerLogic::SetBlockSize(uint uSize)
{
	_uBlockSize = uSize;
	return true;
}

bool CTopologyServerLogic::SetServerGroupID( const std::string& sServerGroupID )
{
	_sServerGroupID = sServerGroupID;
	return true;
}

bool CTopologyServerLogic::SetServerZoneID( const std::string& sServerZoneID )
{
	_sServerZoneID = sServerZoneID;
	return true;
}

const std::string& CTopologyServerLogic::GetServerGroupID() const
{
	return _sServerGroupID;
}

const std::string& CTopologyServerLogic::GetServerZoneID() const
{
	return _sServerZoneID;
}

bool CTopologyServerLogic::SetHashCount( uint uHash )
{
	_uHashCount = uHash;
	return true;
}
uint CTopologyServerLogic::GetServerID() const
{
	return _uServerID;
}

int CTopologyServerLogic::GetServerType() const
{
	return _eSrvType;
}

uint CTopologyServerLogic::GetHash() const
{
	return _uHash;
}
uint CTopologyServerLogic::GetHashCount() const
{
	return _uHashCount;
}

uint CTopologyServerLogic::GetPort() const
{
	return _uPort;
}

uint CTopologyServerLogic::GetSendSize() const
{
	return _uSendSize;
}

uint CTopologyServerLogic::GetRecvSize() const
{
	return _uRecvSize;
}

uint CTopologyServerLogic::GetBlockSize() const
{
	return _uBlockSize;
}

bool CTopologyServerLogic::ClearConfig()
{
	_vConfigLink.clear();
	_vConfigLogic.clear();
	_vConfigServer.clear();
	return true;
}

bool CTopologyServerLogic::SetConfigLink( const MapConfigLink& vLinks )
{
	_vConfigLink = vLinks;
	return true;
}

bool CTopologyServerLogic::SetConfigLogic( const MapConfigLogic& vConfigLogic )
{
	_vConfigLogic = vConfigLogic;
	return true;
}

bool CTopologyServerLogic::SetConfigServer( const MapConfigServer& vConfigServer )
{
	_vConfigServer = vConfigServer;
	return true;
}

const XConfigLink* CTopologyServerLogic::FindConfigLink( int nSrc,int nTar ) const
{
	XConfigLink xLink;
	xLink.eSrcSrv = nSrc;
	xLink.eDesSrv = nTar;

	return ToolFrame::GetValuePtrByKey(_vConfigLink,xLink);
}

const XConfigLogic* CTopologyServerLogic::FindConfigLogic( uint eSrvType ) const
{
	return ToolFrame::GetValuePtrByKey(_vConfigLogic,eSrvType);
}

const XConfigServer* CTopologyServerLogic::FindConfigServer( uint uServerID ) const
{
	return ToolFrame::GetValuePtrByKey(_vConfigServer,uServerID);
}

const MapConfigLink& CTopologyServerLogic::GetConfigLinks() const
{
	return _vConfigLink;
}

const MapConfigLogic& CTopologyServerLogic::GetConfigLogic() const
{
	return _vConfigLogic;
}

CMutexReadWrite& CTopologyServerLogic::GetMutexLogic() const
{
	return _xMutexLogic;
}

CMutexReadWrite& CTopologyServerLogic::GetMutexConfig() const
{
	return _xMutexConfig;
}

bool CTopologyServerLogic::IsLogicOnline(uint uServerID) const
{
	const XServerLogic* pServer = FindLogicByServerID(uServerID);
	if (!pServer)return false;

	return CONNECT_STATE_OFFLINE != pServer->xUpdate.eState;
}

bool CTopologyServerLogic::FindOnlineServerList(VectorUint& vServerID) const
{
	MapLogic::const_iterator itr;
	foreach(itr, _vLogic) {
		const XServerLogic& xLogic = itr->second;
		if (CONNECT_STATE_OFFLINE != xLogic.xUpdate.eState)
			vServerID.push_back(xLogic.uServerID);
	}

	return true;
}

const MapLogic& CTopologyServerLogic::GetLogic() const
{
	return _vLogic;
}

MapLogic& CTopologyServerLogic::GetLogic()
{
	return _vLogic;
}

bool CTopologyServerLogic::SetServerName( const std::string& sServerName )
{
	_sServerName = sServerName;
	return true;
}

bool CTopologyServerLogic::SetServerOpen( const CDate& xServerOpen )
{
	_xServerOpen = xServerOpen;
	return true;
}

bool CTopologyServerLogic::SetServerTag(const std::string& sServerTag)
{
	_sServerTag = sServerTag;
	return true;
}

const std::string& CTopologyServerLogic::GetServerTag() const
{
	return _sServerTag;
}

const std::string& CTopologyServerLogic::GetServerName() const
{
	return _sServerName;
}

const CDate& CTopologyServerLogic::GetServerOpen() const
{
	return _xServerOpen;
}

bool CTopologyServerLogic::SetThread( uint uCount )
{
	_uThread = uCount;
	return true;
}

uint CTopologyServerLogic::GetThread() const
{
	return _uThread;
}

uint CTopologyServerLogic::FindServerIDHash( int eSrvType,uint uHash ) const
{
	if (INVALID_ID == eSrvType)return INVALID_ID;

	CLockRead lockAll(_xMutexLogic);

	XServerHashKey xHash;
	xHash.eSrvType	= eSrvType;
	xHash.uHash		= uHash;

	return ToolFrame::GetValueByKey(_vLogicHash,xHash,INVALID_ID);
}

bool CTopologyServerLogic::FindHashCount(uint* uHashCount,int eSrvType ) const
{
	if (INVALID_ID == eSrvType)return false;

	CLockRead lock(_xMutexConfig);

	const XConfigLogic* pConfig = FindConfigLogic(eSrvType);
	if (!pConfig)return false;

	*uHashCount = pConfig->uHashCount;
	return true;
}

const MapConfigServer& CTopologyServerLogic::GetConfigServer() const
{
	return _vConfigServer;
}

const MapTypeLogic& CTopologyServerLogic::GetTypeLogic() const
{
	return _vTypeLogic;
}

bool CTopologyServerLogic::OptimizeSrvTypeInit()
{
	ToolFrame::Clear(_vLogicHash);

	//初始化哈希
	MapConfigServer::const_iterator itr;
	foreach(itr,_vConfigServer){
		const XConfigServer& xConfigServer = itr->second;
		const XConfigLogic* pConfigLogic = FindConfigLogic(xConfigServer.eSrvType);
		if (!pConfigLogic)return false;
		if (RUN_TYPE_HASH == pConfigLogic->eRunType)
		{
			XServerHashKey xHash;
			xHash.eSrvType	= xConfigServer.eSrvType;
			xHash.uHash		= xConfigServer.uHash;
			ToolFrame::Insert(_vLogicHash,xHash,xConfigServer.uServerID);
		}
	}

	return true;
}

bool CTopologyServerLogic::OptimizeSrvType()
{
	ToolFrame::Clear(_vLogicBalance);
	ToolFrame::Clear(_vLogicSequence);

	MapTypeLogic::const_iterator itr;
	foreach(itr,_vTypeLogic){
		const XConfigLogic* pConfigLogic = FindConfigLogic(itr->first);
		if (!pConfigLogic)return false;

		if (RUN_TYPE_BALANCE == pConfigLogic->eRunType)
		{
			const VectorLogicPtr& vServers = itr->second;
			VectorLogicPtr::const_iterator itrServer;
			foreach(itrServer,vServers){
				const XServerLogic* pServer = *itrServer;
				ASSERT_LOG_ERROR(pServer);

				//求繁忙程度
				int uBusy = pServer->xUpdate.uFreeTime / pConfigLogic->uTimeInterval;
				if (uBusy>100)uBusy = 100;

				CRandomPack& vRandom = ToolFrame::GetValueByKeyForce(_vLogicBalance,pConfigLogic->eSrvType);
				vRandom.AddItem(pServer->uServerID,100 - uBusy);
			}
		}
		if (RUN_TYPE_SEQUENCE == pConfigLogic->eRunType)
		{
			//找到最繁忙的
			int nServerID = INVALID_ID;int uBusyMax = 0;
			const VectorLogicPtr& vServers = itr->second;
			VectorLogicPtr::const_iterator itrServer;
			foreach(itrServer,vServers){
				const XServerLogic* pServer = *itrServer;
				ASSERT_LOG_ERROR(pServer);

				//求繁忙程度
				int uBusy = pServer->xUpdate.uFreeTime / pConfigLogic->uTimeInterval;
				if (uBusy>100)uBusy = 100;

				if (uBusy > 85)
					continue;

				if (INVALID_ID == nServerID){
					uBusyMax = uBusy;
					nServerID = pServer->uServerID;

					continue;
				}

				if (uBusy > uBusyMax)
				{
					uBusyMax = uBusy;
					nServerID = pServer->uServerID;
				}
			}

			if (INVALID_ID != nServerID)
				ToolFrame::InsertVector(_vLogicSequence,pConfigLogic->eSrvType,nServerID);
			else
			{
				//如果服务器都满了，随机挑选服务器
				if (!vServers.empty())
				{
					foreach(itrServer,vServers){
						const XServerLogic* pServer = *itrServer;
						ASSERT_LOG_ERROR(pServer);

						ToolFrame::InsertVector(_vLogicSequence,pConfigLogic->eSrvType,pServer->uServerID);
					}
				}
			}
		}
	}

	return true;
}

uint CTopologyServerLogic::FindServerIDBalance( int eSrvType ) const
{
	if (INVALID_ID == eSrvType)return INVALID_ID;

	CLockRead lockAll(_xMutexLogic);

	const CRandomPack* vRandom = ToolFrame::GetValuePtrByKey(_vLogicBalance,eSrvType);
	if (!vRandom)return INVALID_ID;

	return vRandom->RandomItem();
}

uint CTopologyServerLogic::FindServerIDSequence( int eSrvType ) const
{
	if (INVALID_ID == eSrvType)return INVALID_ID;

	CLockRead lockAll(_xMutexLogic);
	const VectorInt* pServers = ToolFrame::GetValuePtrByKey(_vLogicSequence,eSrvType);
	if (!pServers)return INVALID_ID;

	return ToolFrame::RandValue(*pServers,INVALID_ID);
}

uint CTopologyServerLogic::FindServerRunType(int eSrvType) const
{
	if (INVALID_ID == eSrvType)return RUN_TYPE_INVAILD;

	CLockRead lock(_xMutexConfig);

	const XConfigLogic* pConfig = FindConfigLogic(eSrvType);
	if (!pConfig)return RUN_TYPE_INVAILD;

	return pConfig->eRunType;
}

NS_TOOL_FRAME_END
