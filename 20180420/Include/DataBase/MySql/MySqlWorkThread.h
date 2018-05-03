#pragma once

#include "MacroMySql.h"

#ifdef MACRO_LIB_MY_SQL

#include "MySqlClient.h"
#include "IThreadTask.h"
#include "IThreadNew.h"
#include "HMySql.h"

NS_TOOL_FRAME_BEGIN

//数据库线程
class CMySqlWorkThread
	:public IThreadNew
{
public:
	virtual bool SetHandler(HMySql* hHandler);
	virtual bool SetDataBase(const std::string& sHostName,int nPort,const std::string& sDBName,const std::string& sUserName,const std::string& sPwd);
	virtual bool SetTimeWaitConnect(uint uTime);//连接等待时间
	virtual bool SetTimeExcute(uint uTime);		//单次执行时间
	virtual uint GetTimeWaitConnect()const;
	virtual uint GetTimeExcute()const;
public:
	const CMySqlClient& GetDbClient()const;
private:
	virtual	bool InitThread();
	virtual bool RunOnceThread();//系统调用
private:
	virtual bool QuerySql();//查询Sql 返回 是否有SQL被执行
public:
	CMySqlWorkThread(void);
	virtual ~CMySqlWorkThread(void);
private:
	CMySqlClient	_dbClient;
	CMySqlResults	_dbRecord;			//结果集
	HMySql*			_hHandler;			//处理器
	uint			_uTimeWaitConnect;	//连接等待时间
	uint			_uTimeExcute;		//单次执行时间
};

NS_TOOL_FRAME_END


#endif
