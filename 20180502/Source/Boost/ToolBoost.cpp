#include "ToolBoost.h"
#include "ApiBoost.h"

NS_TOOL_FRAME_BEGIN

bool IsEmail( const std::string& sAddress )
{
	return ApiBoost::IsEmail(sAddress);
}

std::string GetLocalIp()
{
	return ApiBoost::GetLocalIp();
}

std::string GetHostName()
{
	return ApiBoost::GetHostName();
}

NS_TOOL_FRAME_END

