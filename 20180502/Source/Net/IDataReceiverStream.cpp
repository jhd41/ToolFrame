#include "IDataReceiverStream.h"
#include "IMsgStream.h"
#include "MLoger.h"
#include "MProtocol.h"

NS_TOOL_FRAME_BEGIN

IDataReceiverStream::IDataReceiverStream(void)
{
}

IDataReceiverStream::~IDataReceiverStream(void)
{
}

uint IDataReceiverStream::OnRecv(IDataSession* pSession)
{
	return SpliteMsgStream(pSession);
}

NS_TOOL_FRAME_END
