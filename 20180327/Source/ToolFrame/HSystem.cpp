#include "HSystem.h"

NS_TOOL_FRAME_BEGIN

HSystem::HSystem(void)
{
}

HSystem::~HSystem(void)
{
}

bool HSystem::OnSystemInit()
{
	return true;
}

bool HSystem::OnSystemProcess(uint64 uTime)
{
	return true;
}

bool HSystem::OnSystemCleanUp()
{
	return true;
}

bool HSystem::OnSystemMemoryLow()
{
	return true;
}

NS_TOOL_FRAME_END
