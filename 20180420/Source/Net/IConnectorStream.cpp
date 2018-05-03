#include "IConnectorStream.h"

NS_TOOL_FRAME_BEGIN

IConnectorStream::IConnectorStream(void)
{
}

IConnectorStream::~IConnectorStream(void)
{
}

uint IConnectorStream::OnRecv(IDataSession* pSession)
{
	return SpliteMsgStream(pSession);
}

NS_TOOL_FRAME_END
