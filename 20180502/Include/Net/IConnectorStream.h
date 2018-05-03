#pragma once

#include "Macro.h"
#include "IConnector.h"
#include "IMsgStreamSpliter.h"

NS_TOOL_FRAME_BEGIN

class IConnectorStream
	:public IConnector
	,public IMsgStreamSpliter
{
private:
	virtual uint OnRecv(IDataSession* pSession) override;//返回处理了包的个数
public:
	IConnectorStream(void);
	virtual ~IConnectorStream(void);
};

NS_TOOL_FRAME_END
