#pragma once
#include "Macro.h"

#ifdef MACRO_LIB_MY_SQL

#include "IQueryClient.h"

#include "ISqlQuery.h"
#include "SqlQueryExecuter.h"

#include "HSqlClient.h"

NS_TOOL_FRAME_BEGIN

//Sql客户端
class CSqlClient
	:public IQueryClient
	,public HSqlClientLog
{
public:
	virtual bool SetHandler(HSqlClient* hHandler);			//设置处理回调
	virtual bool AddServer(const std::string& sAddress, uint uConcurrent = 1);
	virtual bool Init();
public:
	virtual bool OpenDataBase(const std::string& sIP, uint uPort, const std::string& sDBName, const std::string& sUserName, const std::string& sPwd, uint uConcurrent);//添加一个数据库
	virtual bool CloseDataBase(const std::string& sDBName);
public:
	virtual ISqlQueryPtr	Query(const std::string& sDBName,const std::string& sSql);
	virtual ISqlQueryPtr	Query(ISqlQueryPtr ptr, size_t uKey = INVALID_ID);

	//内部调用 外部不要访问
public:
	virtual bool			OnSqlExecuted(CSqlQueryExecuter* pConnector, uint uSqlID, CSqlResults& sqlResults);
	
private:
	CFIELD_SIZE(RecvSize);	//接收缓冲区大小(默认 无限0)
	CFIELD_SIZE(SendSize);	//发送缓冲区大小(默认 无限0)
	CFIELD_SIZE(BlockSize);	//缓冲区每次分配大小(默认 65535)
public:
	CSqlClient();
	virtual ~CSqlClient();
private:
	HSqlClient*			_hHandler;	//处理器
};

NS_TOOL_FRAME_END

#endif


