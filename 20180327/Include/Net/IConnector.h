#pragma once

#include "Macro.h"
#include "IDataSession.h"

NS_TOOL_FRAME_BEGIN

class IConnector
	:public IDataReceiver
{
public:
	virtual bool OnConnected(uint uClientID)override;
	virtual bool OnConnectFailed(uint uClientID)override;
	virtual bool OnDisconnected(uint uClientID)override;
	virtual uint OnRecv(IDataSession* pSession) override;//返回处理了包的个数
public:
	IConnector(void);
	virtual ~IConnector(void);
private:
	CFIELD_UINT(ClientID);
};

NS_TOOL_FRAME_END
