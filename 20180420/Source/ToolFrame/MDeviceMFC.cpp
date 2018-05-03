#include "MDeviceMFC.h"

#ifdef MACRO_LIB_MFC

#include "MSystem.h"

NS_TOOL_FRAME_BEGIN

MDeviceMFC::MDeviceMFC(void)
{
}

MDeviceMFC::~MDeviceMFC(void)
{
}

uint MDeviceMFC::SetTimer( uint uElapse/*=0*/,uint uEventID/*=0*/ )
{
	return ::SetTimer(nullptr,uEventID,uElapse,MDeviceMFC::OnTimer);
}

void CALLBACK MDeviceMFC::OnTimer( HWND, UINT, UINT_PTR, DWORD )
{
	MSystem::Singleton().RunOnce();
}

NS_TOOL_FRAME_END

#endif // MACRO_LIB_MFC