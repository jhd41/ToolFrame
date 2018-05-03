#pragma once

#include "Macro.h"

#ifdef MACRO_LIB_MFC

#include <afxwin.h>

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL MDeviceMFC
{
	ST_INTANCE(MDeviceMFC);
public:
	uint	SetTimer(uint uElapse=10,uint uEventID=0);
private:
	static void CALLBACK OnTimer(HWND, UINT, UINT_PTR, DWORD);
public:
	MDeviceMFC(void);
	virtual ~MDeviceMFC(void);
};

NS_TOOL_FRAME_END

#endif // MACRO_LIB_MFC

