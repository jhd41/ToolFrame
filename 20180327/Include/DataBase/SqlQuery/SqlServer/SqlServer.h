#pragma once

#include "MacroSqlSrv.h"

#ifdef MACRO_LIB_MY_SQL

#include "IMySqlProcess.h"
#include "IMySqlQuery.h"
#include "HMySql.h"

#include "IDataReceiverStream.h"
#include "SqlUserInterface.h"

NS_TOOL_FRAME_BEGIN

class CSqlServer
	:public IMySqlProcess
	,public IDataReceiverStream
	,public HMySqlLog
{
public:
	virtual bool AddDataBase(const std::string& sIp, uint uPort, const std::string& sDBName, const std::string& sUserName, const std::string& sPwd, uint uConcurrent);//���һ�����ݿ� Ҫ�� ���ݿ����Ʋ����ظ�
	virtual bool AddPublicPort(uint uPort);
	virtual bool SetPublicPort(const VectorUint& vPort);
	virtual bool SetServerID(uint uSrvID);
	virtual bool Init();					//��ʼ��
	virtual bool OnRunOnce();				//ִ�е����̣߳������Ƿ�ʱ
public:
	virtual uint GetQueryCount()const;		//��ȡ��ѯ�е�����
private:
	virtual bool OnConnected(uint uClientID)override;
	virtual bool OnConnectFailed(uint uClientID)override;
	virtual bool OnDisconnected(uint uClientID)override;
	virtual bool OnRecv(uint uClientID, IMsgStream& msgStream)override;
private:
	virtual bool OnSqlExecuted(IMySqlQuery* pSqlQuery, CMySqlResults& results)override;
private:
	virtual bool OnSqlPrepareErr(IMySqlQueryPtr pQuery)override;							//ִ��ǰ����
private:
	CFIELD_SIZE(RecvSize);	//���ջ�������С(Ĭ�� ����0)
	CFIELD_SIZE(SendSize);	//���ͻ�������С(Ĭ�� ����0)
	CFIELD_SIZE(BlockSize);	//������ÿ�η����С(Ĭ�� 65535)
public:
	CSqlServer(void);
	virtual ~CSqlServer(void);
private:
	CSqlUserManager	_vUserMgr;
	VectorUint		_vPublicPort;
};

NS_TOOL_FRAME_END

#endif
