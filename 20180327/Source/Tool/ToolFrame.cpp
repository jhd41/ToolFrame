#include "ToolFrame.h"
#include "MSystem.h"

NS_TOOL_FRAME_BEGIN

bool SystemInit()
{
	return MSystem::Singleton().Init();
}

bool SystemRunOnce(uint64 uTime)
{
	return MSystem::Singleton().RunOnce(uTime);
}

bool SystemRunOnce(int uTime )
{
	if (uTime < 0)return false;
	return SystemRunOnce(uint64(uTime));
}

NS_TOOL_FRAME_END
