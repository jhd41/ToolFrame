#pragma once
#include "MacroMySql.h"

#ifdef MACRO_LIB_MY_SQL

NS_TOOL_FRAME_BEGIN
//数据库线程处理器(多线程返回,继承回调时务必注意)
class CMySqlWorkThread;
//////////////////////////////////////////////////////////////////////////
class HMySql
{
public:
	virtual bool OnInitFaild(CMySqlWorkThread* pThread){return false;}
	virtual bool OnInitConnectFaild(CMySqlWorkThread* pThread) { return false; }
	virtual bool OnInited(CMySqlWorkThread* pThread){return false;}
	virtual bool OnReconnectFaild(CMySqlWorkThread* pThread){return false;}
	virtual bool OnReconnected(CMySqlWorkThread* pThread){return false;}
	virtual bool OnDisconnected(CMySqlWorkThread* pThread){return false;}
	virtual bool OnSqlPrepareErr(IMySqlQueryPtr pQuery) { return false; }							//执行前错误
	virtual bool OnExcuteError(CMySqlWorkThread* pThread,IMySqlQueryPtr ptr){return false;}	//执行时错误
	virtual bool OnExecuteSql(CMySqlWorkThread* pThread,IMySqlQueryPtr ptr){return false;}
	virtual bool OnPushSqlFaild(IMySqlQueryPtr ptr){return false;}
	virtual bool OnRePushSql(CMySqlWorkThread* pThread,IMySqlQueryPtr ptr){return false;}		//重新压请求回队列
	virtual bool OnSqlExecutedErr(CMySqlWorkThread* pThread,IMySqlQueryPtr ptr){return false;}	//执行回调后错误
public:
	HMySql(){}
	virtual ~HMySql(){}
};

//////////////////////////////////////////////////////////////////////////
class HMySqlLog
	:public HMySql
{
public:
	virtual bool OnInitFaild(CMySqlWorkThread* pThread)override;
	virtual bool OnInitConnectFaild(CMySqlWorkThread* pThread)override;
	virtual bool OnInited(CMySqlWorkThread* pThread)override;
	virtual bool OnReconnectFaild(CMySqlWorkThread* pThread)override;
	virtual bool OnReconnected(CMySqlWorkThread* pThread)override;
	virtual bool OnDisconnected(CMySqlWorkThread* pThread)override;
	virtual bool OnSqlPrepareErr(IMySqlQueryPtr pQuery)override;	//数据库名字为空
	virtual bool OnExcuteError(CMySqlWorkThread* pThread, IMySqlQueryPtr ptr)override;
	virtual bool OnExecuteSql(CMySqlWorkThread* pThread, IMySqlQueryPtr ptr)override;
	virtual bool OnPushSqlFaild(IMySqlQueryPtr ptr)override;
	virtual bool OnRePushSql(CMySqlWorkThread* pThread, IMySqlQueryPtr ptr)override;
	virtual bool OnSqlExecutedErr(CMySqlWorkThread* pThread, IMySqlQueryPtr ptr)override;
};

NS_TOOL_FRAME_END

#endif
