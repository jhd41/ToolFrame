#include "SqlServer.h"

#ifdef MACRO_LIB_MY_SQL

#include "MMySql.h"

#include "SqlProtocol.h"

#include "MProtocol.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

CSqlServer::CSqlServer(void)
{
	SetRecvSize(MProtocol::Singleton().GetRecvSize());
	SetSendSize(MProtocol::Singleton().GetSendSize());
	SetBlockSize(MProtocol::Singleton().GetBlockSize());
}

CSqlServer::~CSqlServer(void)
{
}

bool CSqlServer::AddDataBase(const std::string& sIp, uint uPort, const std::string& sDBName, const std::string& sUserName, const std::string& sPwd, uint uConcurrent)
{
	return MMySql::Singleton().AddDataBase(sIp, uPort, sDBName, sUserName, sPwd, uConcurrent);
}

bool CSqlServer::AddPublicPort(uint uPort)
{
	_vPublicPort.push_back(uPort);
	return true;
}

bool CSqlServer::SetPublicPort(const VectorUint& vPort)
{
	_vPublicPort = vPort;
	return true;
}

bool CSqlServer::SetServerID(uint uSrvID)
{
	return _vUserMgr.SetSrvID(uSrvID);
}

uint CSqlServer::GetQueryCount() const
{
	return MMySql::Singleton().GetQueryCount();
}

bool CSqlServer::Init()
{
	//启动数据库
	MMySql::Singleton().SetHandler(this);
	MMySql::Singleton().SetProcess(this);
	if (!MMySql::Singleton().Init())return false;

	//启动服务器
	{
		VectorUint::const_iterator itr;
		foreach(itr, _vPublicPort) {
			uint uPort = *itr;
			if (!MProtocol::Singleton().CreateServer(this, uPort, LINK_TYPE_NET_TCP, GetRecvSize(),GetSendSize(),GetBlockSize()))
			{
				LOG_FATAL("OnServerCreatePublicFaild Port:" << uPort);
				LOG_FATAL(ToolFrame::GetPortInfoString(uPort));
			}
			else
			{
				LOG_SYSTEM("OnServerCreatePublicSucceed Port:" << uPort);
			}
		}
	}

	_vUserMgr.Init();
	return true;
}

bool CSqlServer::OnRunOnce()
{
	return _vUserMgr.ProcessRetry(300);
}

uint CSqlServer::GetClientCount() const
{
	return _vUserMgr.GetClientCount();
}

uint CSqlServer::GetAssCount() const
{
	return _vUserMgr.GetAssCount();
}

bool CSqlServer::OnConnected(uint uClientID)
{
	_vUserMgr.SyncClientConnected(uClientID);
	return true;
}

bool CSqlServer::OnConnectFailed(uint uClientID)
{
	return true;
}

bool CSqlServer::OnDisconnected(uint uClientID)
{
	_vUserMgr.SyncClientDisconnect(uClientID);
	return true;
}

bool CSqlServer::OnRecv(IDataSession* pSession, IMsgStream& msgStream)
{
	LOG_DEBUG("OnClientRecv ClientID:" << pSession->GetClientID() << " OpCode:" << msgStream.GetOpCode());
	if (!_vUserMgr.SyncTryClientRecved(pSession->GetClientID(), msgStream))
		pSession->MarkDelayRecv();
	return true;
}

bool CSqlServer::OnSqlExecuted(IMySqlQuery* pSqlQuery, CMySqlResults& results)
{
	ASSERT_LOG_ERROR(pSqlQuery);

	MsgSqlResponse msg;
	msg.uSqlID	= pSqlQuery->GetID();
	msg.uErr	= results.IsError() ? ERR_SQL_EXECUTE_FAILD : ERR_SQL_SUCCEED;
	foreachResult(results) {
		SqlResult dbResult;
		foreachRecord(results) {
			SqlRecord dbRecord;
			uint uField = results.GetFieldCount();
			for (uint uFieldIndex = 0; uFieldIndex < uField;++uFieldIndex) {
				const char* pFieldValue = results.GetFieldValue(uFieldIndex);
				int nFieldLength		= results.GetFieldLength(uFieldIndex);
				char ch = '\0';

				//添加到字段末尾补0
				StreamBufferPtr pBuffer(new CStreamBufferMalloc(pFieldValue, nFieldLength + sizeof(ch), nFieldLength));
				ASSERT_LOG_ERROR(pBuffer);
				pBuffer->Write(&ch,sizeof(ch));
				dbRecord.push_back(pBuffer);
			}

			dbResult.push_back(dbRecord);
		}

		msg.vResult.push_back(dbResult);
	}
	
	DEBUG_POINT();
	_vUserMgr.SyncSendClient(pSqlQuery->GetClientID(),msg);
	return true;
}

bool CSqlServer::OnSqlPrepareErr(IMySqlQueryPtr pQuery)
{
	MsgSqlResponse msg;
	msg.uSqlID = pQuery->GetID();
	msg.uErr = pQuery->GetErrCode();

	DEBUG_POINT();
	_vUserMgr.SyncSendClient(pQuery->GetClientID(), msg);

	return HMySqlLog::OnSqlPrepareErr(pQuery);
}

bool CSqlServer::OnPushSqlFaild(IMySqlQueryPtr pQuery)
{
	MsgSqlResponse msg;
	msg.uSqlID = pQuery->GetID();
	msg.uErr = pQuery->GetErrCode();

	DEBUG_POINT();
	_vUserMgr.SyncSendClient(pQuery->GetClientID(), msg);

	return HMySqlLog::OnPushSqlFaild(pQuery);
}

NS_TOOL_FRAME_END

#endif
