#include "IUserClientResolver.h"
#include "IUserClient.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

IUserClientResolver::IUserClientResolver()
{
	SetUserNull();
}

IUserClientResolver::~IUserClientResolver()
{
}

IUserClient* IUserClientResolver::GetIUserClient() const
{
	return dynamic_cast<IUserClient*>(GetUser());
}

bool IUserClientResolver::SendClient(const IMsgStream& msgStream, bool bSecret /*= true*/)
{
	IUserClient* pUser = GetIUserClient();
	ASSERT_LOG_ERROR(pUser);

	return pUser->SendClient(msgStream, bSecret);
}

bool IUserClientResolver::SendClient(StreamBinaryPtr ptr, bool bSecret /*= true*/)
{
	if (!ptr)return false;

	IUserClient* pUser = GetIUserClient();
	ASSERT_LOG_ERROR(pUser);

	return pUser->SendClient(ptr, bSecret);
}

bool IUserClientResolver::SendClient(const std::string& sMsg, bool bSecret /*= true*/)
{
	if (sMsg.empty())return false;

	IUserClient* pUser = GetIUserClient();
	ASSERT_LOG_ERROR(pUser);

	return pUser->SendClient(sMsg, bSecret);
}

bool IUserClientResolver::SendClient(const void* pBuffer, size_t uLen, bool bSecret /*= true*/)
{
	if (!pBuffer)return false;
	if (uLen <= 0)return false;

	IUserClient* pUser = GetIUserClient();
	ASSERT_LOG_ERROR(pUser);

	return pUser->SendClient(pBuffer, uLen, bSecret);
}

bool IUserClientResolver::OnClientRecvErr(const IMsgStream& msgStream)
{
	LOG_CLIENT_ERR_MSG("ClientID:" << GetUser()->GetClientID()<<" OpCode:"<<msgStream.GetOpCode());
	return false;
}

bool IUserClientResolver::OnClientRecvErr(StreamBinaryPtr pMsgStream)
{
	LOG_CLIENT_ERR_MSG("ClientID:"<< GetUser()->GetClientID());
	return false;
}

NS_TOOL_FRAME_END
