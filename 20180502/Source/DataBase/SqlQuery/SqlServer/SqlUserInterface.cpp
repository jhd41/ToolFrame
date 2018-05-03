#include "IUserClient.h"

#ifdef MACRO_LIB_MY_SQL

#include "MProtocol.h"
#include "SqlEncryptLib.h"
#include "UserActionSql.h"
#include "SqlServer.h"

NS_TOOL_FRAME_BEGIN

ISqlUserAction::ISqlUserAction(void)
{
}

ISqlUserAction::~ISqlUserAction(void)
{
}

bool ISqlUserAction::Init( ISqlUserAction* pAc )
{
	ASSERT_LOG_ERROR(pAc);

	SetUser(pAc->GetUser());

	return true;
}

CSqlUserClient* ISqlUserAction::GetUserClient() const
{
	return dynamic_cast<CSqlUserClient*>(GetUser());
}

bool ISqlUserAction::OnClientRecv(const IMsgStream& msgStream)
{
	switch (msgStream.GetOpCode())
	{
	case MSG_MYSQL_PING:
	{
		LOG_DEBUG("Ping");

		MsgSqlPong msg;
		SendClient(msg);
		return true;
	}
	break;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
CSqlUserClient::CSqlUserClient( void )
{
	SetEncryptTransmission(false);
}

CSqlUserClient::~CSqlUserClient( void )
{

}

bool CSqlUserClient::OnEncrypt(void* pBuffer, size_t uLength) {
	return CSqlEncryptLib::OnEncrypt(GetSecretKey(), (char*)pBuffer, uLength);
}

bool CSqlUserClient::OnDecrypt(void* pBuffer, size_t uLength) {
	return CSqlEncryptLib::OnDecrypt(GetSecretKey(), (char*)pBuffer, uLength);
}

//////////////////////////////////////////////////////////////////////////
CSqlUserManager::CSqlUserManager(void)
{
}

CSqlUserManager::~CSqlUserManager(void)
{
}

ISyncProcesserPtr CSqlUserManager::OnCreateProcesser(int nUserInt, void* pUserData)
{
	CSqlUserClient* pUser = new CSqlUserClient();
	ASSERT_LOG_ERROR(pUser);

	CUserActionSql* pAc = CUserActionSql::Create(pUser);
	ASSERT_LOG_ERROR(pAc);

	return ISyncProcesserPtr(pUser);
}

NS_TOOL_FRAME_END

#endif
