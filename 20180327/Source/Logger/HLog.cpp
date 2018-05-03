#include "HLog.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

HLog::HLog(void)
{
}

HLog::~HLog(void)
{
}

bool HLog::OnLogInited()
{
	LOG_SYSTEM("--------------------Start!------------------------");
	return true;
}

bool HLog::OnLogMsg( const std::string& sLogLevel,const std::stringstream& sStreamLog )
{
	return true;
}

NS_TOOL_FRAME_END
