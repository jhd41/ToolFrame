#include "TopologyServerController.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

CTopologyServerController::CTopologyServerController(void)
{
}

CTopologyServerController::~CTopologyServerController(void)
{
}

bool CTopologyServerController::Init()
{
	return true;
}

bool CTopologyServerController::Clear()
{
	_vControl.clear();
	return true;
}

bool CTopologyServerController::AddControl( const XServerControl& xControl )
{
	return ToolFrame::Insert(_vControl,xControl.uClientID,xControl);
}

bool CTopologyServerController::AddControl( const VectorControl& vControl )
{
	VectorControl::const_iterator itr;
	foreach(itr,vControl){
		AddControl(*itr);
	}

	return true;
}

bool CTopologyServerController::RemoveControlByClientID( uint uClientID )
{
	return ToolFrame::EraseByKey(_vControl,uClientID)>0;
}

bool CTopologyServerController::IsControlEmpty() const
{
	return _vControl.empty();
}

const MapControl& CTopologyServerController::GetControls() const
{
	return _vControl;
}

CMutexReadWrite& CTopologyServerController::GetMutexControl() const
{
	return _xMutexControl;
}

NS_TOOL_FRAME_END