#pragma once
#include "Macro.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL HLog
{
public:
	virtual bool OnLogInited();
	virtual bool OnLogMsg(const std::string& sLogLevel,const std::stringstream& sStreamLog);//������־ʱ(����false��ֹд��־)
public:
	HLog(void);
	virtual ~HLog(void);
};

NS_TOOL_FRAME_END
