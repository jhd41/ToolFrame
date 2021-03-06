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
	virtual bool AddDataBase(const std::string& sIp, uint uPort, const std::string& sDBName, const std::string& sUserName, const std::string& sPwd, uint uConcurrent);//添加一个数据库 要求 数据库名称不能重复
	virtual bool AddPublicPort(uint uPort);
	virtual bool SetPublicPort(const VectorUint& vPort);
	virtual bool SetServerID(uint uSrvID);
	virtual bool Init();					//初始化
	virtual bool OnRunOnce();				//执行弹性线程，返回是否超时
public:
	virtual size_t	GetClientCount()const;		//连接数
	virtual size_t	GetAssCount()const;			//分配总数
	virtual size_t	GetQueryCount()const;		//获取查询中的数量
	virtual size_t	ClearProcessCount();		//清除本次处理量
	virtual bool	IsEmpty()const;			//是否空转(请求队列 处理线程均为空)
private:
	virtual bool OnConnected(uint uClientID)override;
	virtual bool OnConnectFailed(uint uClientID)override;
	virtual bool OnDisconnected(uint uClientID)override;
	virtual bool OnRecv(IDataSession* pSession, IMsgStream& msgStream);
private:
	virtual bool OnSqlExecuted(IMySqlQuery* pSqlQuery, CMySqlResults& results)override;
private:
	virtual bool OnSqlPrepareErr(IMySqlQueryPtr pQuery)override;							//执行前错误
	virtual bool OnPushSqlFaild(IMySqlQueryPtr pQuery)override;
private:
	CFIELD_SIZE(RecvSize);	//接收缓冲区大小(默认 无限0)
	CFIELD_SIZE(SendSize);	//发送缓冲区大小(默认 无限0)
	CFIELD_SIZE(BlockSize);	//缓冲区每次分配大小(默认 65535)
public:
	CSqlServer(void);
	virtual ~CSqlServer(void);
private:
	CSqlUserManager	_vUserMgr;
	VectorUint		_vPublicPort;
};

NS_TOOL_FRAME_END

#endif
