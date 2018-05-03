#include "HEventTrigger.h"
NS_TOOL_FRAME_BEGIN
HEventTrigger::HEventTrigger(void)
{
}

HEventTrigger::~HEventTrigger(void)
{
}

bool HEventTrigger::OnEvent( int nEvent,const XEvent& xEvent )
{
	return true;
}

bool HEventTrigger::OnEvent( const std::string& sEvent, const XEvent& xEvent )
{
	return true;
}

NS_TOOL_FRAME_END