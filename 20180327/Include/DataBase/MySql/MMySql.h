#pragma once

#include "MacroMySql.h"

#ifdef MACRO_LIB_MY_SQL

#include "TThreadSaftyList.h"
#include "TThreadSaftyMap.h"
#include "IMySqlProcess.h"
#include "ThreadGroup.h"
#include "CalCounter.h"
#include "MySqlWorkThread.h"
#include "TimeAvg.h"

NS_TOOL_FRAME_BEGIN

class MMySql
	:public HMySqlLog
{
	typedef TThreadSaftyListValue<IMySqlQueryPtr>			QueueRequest;
	typedef TThreadSaftyMapValue<std::string,QueueRequest>	MapRequest;

public:
	ST_INTANCE(MMySql);
public:
	IMySqlQueryPtr Query( IMySqlQueryPtr pQuery);
	IMySqlQueryPtr Query(const std::string& sDataBaseName,const std::string& sSql,IMySqlProcess* pDBProcess = nullptr);

	uint		 GetQueryCount()const;		//获取查询中的数量
	uint		 GetQueryTotal()const;		//获取完成查询总数
	uint		 GetQueryAvgTime()const;	//获取平均执行时间	
	bool		 IsEmpty()const;			//是否空转(请求队列 处理线程均为空)
public:
	bool			Init();
	bool			AddDataBase(const std::string& sIp,uint uPort,const std::string& sDBName,const std::string& sUserName,const std::string& sPwd,uint uConcurrent);//添加一个数据库 要求 数据库名称不能重复

	//外部不要调用
public:
	IMySqlQueryPtr	Pop(const std::string& sDataBaseName);
	IMySqlQueryPtr	Push(IMySqlQueryPtr pQuery);		//压入队尾
	IMySqlQueryPtr	PushFront(IMySqlQueryPtr pQuery);	//压入队首

	bool			OnQueryOver(IMySqlQueryPtr pSqlQuery);
public:
	MMySql(void);
	virtual ~MMySql(void);
private:
	MapRequest		_vRequest;
	CThreadGroup	_vThread;
	CCalCounter		_uQuerying;	//执行中的数量
	CCalCounter		_uTotal;	//总共完成的数量
	CTimeAvg		_uTimeAvg;	//平均执行时间
private:
	CFIELD_PTR(IMySqlProcess*,Process,p);
	CFIELD_PTR(HMySql*,Handler,h);
};

NS_TOOL_FRAME_END

#endif
