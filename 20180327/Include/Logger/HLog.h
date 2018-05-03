#pragma once
#include "Macro.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL HLog
{
public:
	virtual bool OnLogInited();
	virtual bool OnLogMsg(const std::string& sLogLevel,const std::stringstream& sStreamLog);//产生日志时(返回false阻止写日志)
public:
	HLog(void);
	virtual ~HLog(void);
};

NS_TOOL_FRAME_END
