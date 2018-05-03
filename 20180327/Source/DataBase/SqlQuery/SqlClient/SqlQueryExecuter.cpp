#include "SqlQueryExecuter.h"

#ifdef MACRO_LIB_MY_SQL

#include "SqlResults.h"
#include "SqlEncryptLib.h"
#include "SqlProtocol.h"

#include "ToolFrame.h"
#include "MLoger.h"
#include "SqlClient.h"

NS_TOOL_FRAME_BEGIN

CSqlQueryExecuter::CSqlQueryExecuter()
{
	_hHandler = nullptr;
	_pClient = nullptr;

	_xConnect.SetHandler(this);
	_xConnect.SetEncryptTransmission(false);
}

CSqlQueryExecuter::~CSqlQueryExecuter()
{

}

bool CSqlQueryExecuter::SetServerAddress(const std::string& sAddress)
{
	return _xConnect.SetServerAddress(sAddress);
}

bool CSqlQueryExecuter::SetHandler(HSqlClient* hHandler)
{
	_hHandler = hHandler;
	return true;
}

bool CSqlQueryExecuter::SetClient(CSqlClient* pClient)
{
	_pClient = pClient;
	return true;
}

bool CSqlQueryExecuter::SetNetBuffer(uint uRecvSize, uint uSendSize, uint uBlockSize)
{
	_xConnect.SetRecvSize(uRecvSize);
	_xConnect.SetSendSize(uSendSize);
	_xConnect.SetBlockSize(uBlockSize);
	return true;
}

bool CSqlQueryExecuter::Init()
{
	Connect();
	return true;
}

bool CSqlQueryExecuter::Connect()
{
	return _xConnect.Connect();
}

bool CSqlQueryExecuter::CloseDataBase(const std::string& sDBName)
{
	MsgSqlDatabaseClose msg;
	msg.sDBName = sDBName;

	return _xConnect.Push(msg);
}

bool CSqlQueryExecuter::OpenDataBase(const std::string& sIP, uint uPort, const std::string& sDBName, const std::string& sUserName, const std::string& sPwd, uint uConcurrent)
{
	MsgSqlDatabaseOpen msg;
	msg.sIP			= sIP;
	msg.uPort		= uPort;
	msg.sDBName		= sDBName;
	msg.sUserName	= sUserName;
	msg.sPwd		= sPwd;
	msg.uConcurrent = uConcurrent;

	return _xConnect.Push(msg);
}

bool CSqlQueryExecuter::OnConnected(CUserConnector* pConnector)
{
	_hHandler->OnSqlClientConnected(pConnector->GetConnectedAddress());
	return true;
}

bool CSqlQueryExecuter::OnConnectFaild(CUserConnector* pConnector)
{
	_hHandler->OnSqlClientFaild(pConnector->GetConnectedAddress());
	return true;
}

bool CSqlQueryExecuter::OnDisconnected(CUserConnector* pConnector)
{
	_hHandler->OnSqlClientDisconnected(pConnector->GetConnectedAddress());
	return true;
}

bool CSqlQueryExecuter::OnRecvEncrypted(CUserConnector* pConnector, IMsgStream& msgStream)
{
	//解析明文协议
	switch (msgStream.GetOpCode())
	{
		case MSG_MYSQL_SECRET:
		{
			MsgSqlSecret msg(msgStream);
			if (!msg.Load())return false;

			pConnector->SetSecretKey(msg.uAssID, msg.uSecretKey, msg.uTimeNow);
			pConnector->MarkNormal();
			return true;
		}
		break;
	}
	return false;
}

bool CSqlQueryExecuter::OnKeepHeartTimeOut(CUserConnector* pConnector)
{
	MsgSqlPing msg;

	DEBUG_POINT();
	pConnector->Push(msg);
	return true;
}

bool CSqlQueryExecuter::Query(IQueryPtr ptr)
{
	if (!ptr)return false;

	ISqlQueryPtr pQuerySql;
	ASSERT_LOG_ERROR(ToolFrame::DynamicCast(pQuerySql, ptr));
	
	MsgSqlQuery msg;
	msg.sDBName = pQuerySql->GetDBName();
	msg.sSql	= pQuerySql->GetSql();
	msg.uSqlID	= pQuerySql->GetID();
	msg.uTimeOut= pQuerySql->GetTimeOut();

	DEBUG_POINT();

	return _xConnect.Push(msg);
}

bool CSqlQueryExecuter::OnRecvDecrypted(CUserConnector* pConnector, IMsgStream& msgStream)
{
	DEBUG_POINT();

	LOG_DEBUG("OpCode:" << msgStream.GetOpCode());
	
	//解析密文协议
	switch (msgStream.GetOpCode())
	{
		case MSG_MYSQL_RESPONSE:
		{
			MsgSqlResponse msg(msgStream);
			if (!msg.Load())return false;

			DEBUG_POINT();
			
			uint uSqlID = msg.uSqlID;

			//回调
			{
				CSqlResults sqlResults;

				sqlResults.SetError(msg.uErr);
				sqlResults.SetResults(&msg.vResult);

				_pClient->OnSqlExecuted(this, uSqlID, sqlResults);
			}

			return true;
		}
		break;
	}
	return false;
}

bool CSqlQueryExecuter::OnEncrypt(CUserConnector* pConnector, void* pBuffer, size_t uLength)
{
	return CSqlEncryptLib::OnEncrypt(pConnector->GetSecretKey(), (char*)pBuffer, uLength);
}

bool CSqlQueryExecuter::OnEncryptFailed(CUserConnector* pConnector, void* pBuffer, size_t uLength)
{
	return false;
}

bool CSqlQueryExecuter::OnDecrypt(CUserConnector* pConnector, void* pBuffer, size_t uLength)
{
	return CSqlEncryptLib::OnDecrypt(pConnector->GetSecretKey(), (char*)pBuffer, uLength);
}

bool CSqlQueryExecuter::OnDecryptFailed(CUserConnector* pConnector, void* pBuffer, size_t uLength)
{
	return false;
}

NS_TOOL_FRAME_END

#endif
