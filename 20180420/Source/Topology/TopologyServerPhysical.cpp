#include "TopologyServerPhysical.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

CTopologyServerPhysical::CTopologyServerPhysical(void)
{
}

CTopologyServerPhysical::~CTopologyServerPhysical(void)
{
}

bool CTopologyServerPhysical::Init()
{
	return true;
}

bool CTopologyServerPhysical::Clear()
{
	_vPhysical.clear();
	return true;
}

bool CTopologyServerPhysical::AddServer( const XServerPhysical& xServer )
{
	XServerPhysical* pServer = (XServerPhysical*)FindPhysicalByPhysicalID(xServer.uPhysicalID);
	if (pServer){
		*pServer = xServer;
	}
	return ToolFrame::Insert(_vPhysical,xServer.uPhysicalID,xServer);	
}

bool CTopologyServerPhysical::AddServer( const VectorPhysical& vPhysical )
{
	bool bSucceed = true;
	VectorPhysical::const_iterator itr;
	foreach(itr,vPhysical){
		bSucceed &= AddServer(*itr);
	}

	return bSucceed;
}

bool CTopologyServerPhysical::RemovePhysicalByPhysicalID( uint uPhysicalID )
{
	XServerPhysical* pPhysical = ToolFrame::GetValuePtrByKey(_vPhysical,uPhysicalID);
	if (!pPhysical)return false;

	pPhysical->xUpdate.eState = CONNECT_STATE_OFFLINE;
	pPhysical->uClientID = INVALID_ID;
	return true;
}

const XServerPhysical* CTopologyServerPhysical::FindPhysicalByPhysicalID( uint uPhysicalID ) const
{
	return ToolFrame::GetValuePtrByKey(_vPhysical,uPhysicalID);
}

const XServerPhysical* CTopologyServerPhysical::FindPhysicalByClientID( uint uClientID ) const
{
	MapPhysical::const_iterator itr;
	foreach(itr,_vPhysical){
		const XServerPhysical& xPhysical = itr->second;
		if (xPhysical.uClientID == uClientID)
			return &xPhysical;
	}

	return nullptr;
}

bool CTopologyServerPhysical::UpdatePhysicalState( uint uPhysicalID,const XPhysicalUpdate& xUpdate )
{
	XServerPhysical* pServer = (XServerPhysical*)FindPhysicalByPhysicalID(uPhysicalID);
	if (!pServer)return false;

	pServer->bUpdated		= true;
	pServer->xUpdate		= xUpdate;
	return true;
}

bool CTopologyServerPhysical::IsPhysicalEmpty() const
{
	return _vPhysical.empty();
}

const MapPhysical& CTopologyServerPhysical::GetPhysical() const
{
	return _vPhysical;
}

CMutexReadWrite& CTopologyServerPhysical::GetMutexPhysical() const
{
	return _xMutexPhysical;
}

NS_TOOL_FRAME_END
	