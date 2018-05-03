#include "MDevice.h"

#include "MDeviceCocos2dx.h"
#include "MDeviceMFC.h"

NS_TOOL_FRAME_BEGIN

MDevice::MDevice()
{
}

MDevice::~MDevice()
{
}

bool MDevice::Init() {
#ifdef MACRO_LIB_MFC
	if (!MDeviceMFC::Singleton().SetTimer())return false;
#endif

#ifdef MACRO_LIB_COCOS2D
	if (!MDeviceCocos2dx::Singleton().Init())return false;
#endif

	return true;
}

NS_TOOL_FRAME_END
