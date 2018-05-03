#include "IConnectorReceiver.h"

#include "ToolFrame.h"
#include "MLoger.h"

#include "IConnector.h"

NS_TOOL_FRAME_BEGIN

IConnectorReceiver::IConnectorReceiver(void)
{
}

IConnectorReceiver::~IConnectorReceiver(void)
{
}

bool IConnectorReceiver::OnConnected( UINT uClientID )
{
	IConnectorPtr pConnector = CreateConnector();
	ASSERT_LOG_ERROR(pConnector);
	pConnector->SetClientID(uClientID);
	pConnector->OnConnected(uClientID);

	ASSERT_LOG_ERROR(_vConnector.Insert(uClientID,pConnector));	
	return true;
}

bool IConnectorReceiver::OnConnectFailed( UINT uClientID )
{
	LOG_ERROR();
	return true;
}

bool IConnectorReceiver::OnDisconnected( UINT uClientID )
{
	IConnectorPtr pConnector = _vConnector.GetValueByKey(uClientID);
	ASSERT_LOG_ERROR(pConnector);
	pConnector->OnDisconnected(uClientID);
	ASSERT_LOG_ERROR(_vConnector.EraseByKey(uClientID));	
	return true;
}

uint IConnectorReceiver::OnRecv(IDataSession* pSession)
{
	ASSERT_LOG_ERROR(pSession);
	IConnectorPtr pConnector = _vConnector.GetValueByKey(pSession->GetClientID());
	ASSERT_LOG_ERROR(pConnector);
	return pConnector->OnRecv(pSession);
}

IConnectorPtr IConnectorReceiver::CreateConnector()
{
	return IConnectorPtr(new IConnector());
}

NS_TOOL_FRAME_END
