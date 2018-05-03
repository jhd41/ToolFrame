#include "IConnector.h"

NS_TOOL_FRAME_BEGIN

IConnector::IConnector(void)
{
	SetClientID(INVALID_ID);
}

IConnector::~IConnector(void)
{
}

bool IConnector::OnConnected( uint uClientID )
{
	return false;
}

bool IConnector::OnConnectFailed( uint uClientID )
{
	return false;
}

bool IConnector::OnDisconnected( uint uClientID )
{
	return false;
}

uint IConnector::OnRecv(IDataSession* pSession)
{
	return 0;
}

NS_TOOL_FRAME_END
