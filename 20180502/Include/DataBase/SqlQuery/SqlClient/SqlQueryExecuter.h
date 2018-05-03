#pragma once
#include "Macro.h"

#ifdef MACRO_LIB_MY_SQL

#include "UserConnector.h"
#include "HSqlClient.h"

#include "IQueryExecuter.h"

NS_TOOL_FRAME_BEGIN
class CSqlClient;

//Sql客户端连接
class CSqlQueryExecuter
	:public IQueryExecuter
	,public HUserConnectorLog
	,public HSqlClient
{
public:
	virtual bool SetServerAddress(const std::string& sAddress);
	virtual bool SetHandler(HSqlClient* hHandler);
	virtual bool SetClient(CSqlClient* pClient);
	virtual bool SetNetBuffer(uint uRecvSize,uint uSendSize,uint uBlockSize);
	virtual bool Init()override;
	virtual bool Connect();
	virtual bool Query(IQueryPtr ptr);
	virtual bool OpenDataBase(const std::string& sIP, uint uPort, const std::string& sDBName, const std::string& sUserName, const std::string& sPwd, uint uConcurrent);//添加一个数据库
	virtual bool CloseDataBase(const std::string& sDBName);
private:
	virtual bool OnConnected(CUserConnector* pConnector)override;
	virtual bool OnConnectFaild(CUserConnector* pConnector)override;
	virtual bool OnDisconnected(CUserConnector* pConnector)override;
	virtual bool OnRecvEncrypted(CUserConnector* pConnector, IMsgStream& msgStream)override;				//处理明文
	virtual bool OnRecvDecrypted(CUserConnector* pConnector, IMsgStream& msgStream)override;				//处理密文
	virtual bool OnEncrypt(CUserConnector* pConnector, void* pBuffer, size_t uLength)override;
	virtual bool OnEncryptFailed(CUserConnector* pConnector, void* pBuffer, size_t uLength)override;
	virtual bool OnDecrypt(CUserConnector* pConnector, void* pBuffer, size_t uLength)override;
	virtual bool OnDecryptFailed(CUserConnector* pConnector, void* pBuffer, size_t uLength)override;
	virtual bool OnKeepHeartTimeOut(CUserConnector* pConnector)override;
public:
	CSqlQueryExecuter();
	virtual ~CSqlQueryExecuter();
private:
	CUserConnector	_xConnect;
	HSqlClient*		_hHandler;	//处理器
	CSqlClient*		_pClient;
};

NS_TOOL_FRAME_END

#endif
