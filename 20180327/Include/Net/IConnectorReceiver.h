#pragma once
#include "Macro.h"
#include "MacroDefineEx.h"
#include "TThreadSaftyMap.h"
#include "IDataSession.h"

NS_TOOL_FRAME_BEGIN

DECLARE_SHARE_PTR(IConnector);
class IConnectorReceiver
	:public IDataReceiver
{
	typedef TThreadSaftyMap<uint,IConnectorPtr> MapConnector;
public:
	virtual IConnectorPtr CreateConnector();
public:
	virtual bool OnConnected(UINT uClientID)override;
	virtual bool OnConnectFailed(UINT uClientID)override;
	virtual bool OnDisconnected(UINT uClientID)override;
	virtual uint OnRecv(IDataSession* pSession) override;//返回处理了包的个数
public:
	IConnectorReceiver(void);
	virtual ~IConnectorReceiver(void);
private:
	MapConnector _vConnector;//<uClientID,IConnectorPtr>
};

NS_TOOL_FRAME_END