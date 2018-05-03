#include "UserActionSql.h"

#ifdef MACRO_LIB_MY_SQL

#include "MProtocol.h"

#include "SqlProtocol.h"

#include "MMySql.h"
#include "IMySqlQuery.h"

NS_TOOL_FRAME_BEGIN

CUserActionSql::CUserActionSql(void)
{
	SetResolveRange(RESOLVE_INIT,RESOLVE_MAX);
}

CUserActionSql::~CUserActionSql(void)
{
}

bool CUserActionSql::OnResolve()
{
	switch(GetResolve())
	{
	case RESOLVE_INIT:
		{
			//发送秘钥
			CSqlUserClient* pUser = GetUserClient();
			ASSERT_LOG_ERROR(pUser);

			MsgSqlSecret msg;
			msg.uSecretKey	= pUser->GetSecretKey();
			msg.uTimeNow	= (uint32)ToolFrame::GetNowTime();
			msg.uAssID		= (uint32)pUser->GetAssID();
			SendClient(msg,false);

			LOG_DEBUG("OnClientConnected");
		}
		SetResolve(RESOLVE_QUERY);
		break;
	case RESOLVE_QUERY:
		WaitForever();
		break;
	}

	return false;
}

bool CUserActionSql::OnClientRecv(const IMsgStream& msgStream)
{
	if (ISqlUserAction::OnClientRecv(msgStream))return true;

	switch (GetResolve())
	{
		case RESOLVE_QUERY:
		{
			ClearWait();

			switch (msgStream.GetOpCode())
			{
				case MSG_MYSQL_DATABASE_OPEN:
				{
					MsgSqlDatabaseOpen msg(msgStream);
					if (!msg.Load())return false;

					MMySql::Singleton().AddDataBase(msg.sIP, msg.uPort, msg.sDBName, msg.sUserName, msg.sPwd, msg.uConcurrent);
					return true;
				}
				break;
				case MSG_MYSQL_DATABASE_CLOSE:
				{
					MsgSqlDatabaseClose msg(msgStream);
					if (!msg.Load())return false;

					return true;
				}
					break;
				case MSG_MYSQL_QUERY:
				{
					MsgSqlQuery msg(msgStream);
					if (!msg.Load())return false;

					DEBUG_POINT();

					IMySqlQueryPtr ptr(new IMySqlQuery());
					ASSERT_LOG_ERROR(ptr);

					ptr->SetID(msg.uSqlID);
					ptr->SetDBName(msg.sDBName);
					ptr->SetSql(msg.sSql);
					ptr->SetTimeOut(msg.uTimeOut);
					ptr->SetClientID(GetUserClient()->GetClientID());
					MMySql::Singleton().Query(ptr);
					return true;

				}
				break;
			}

			LOG_CLIENT_ERR_MSG("ErrMsg OpCode:"<< msgStream.GetOpCode());

			//不正确的协议
			GetUserClient()->Disconnect();
			MarkResolveOver();
			SetResolve(RESOLVE_MAX);
			return true;
		}
		break;
	}

	return false;
}

bool CUserActionSql::OnClientDisconnected()
{
	ISqlUserAction::OnClientDisconnected();

	LOG_DEBUG("OnClientDisconnected");

	ClearWait();
	MarkResolveOver();
	SetResolve(RESOLVE_MAX);
	return true;
}

CUserActionSql* CUserActionSql::Create(IUserClient* pUser )
{
	CUserActionSql* pAc = pUser->CreateTopResolver<CUserActionSql>(nullptr);

	ASSERT_LOG_ERROR(pAc);
	pAc->SetUser(pUser);

	return pAc;
}

NS_TOOL_FRAME_END

#endif
