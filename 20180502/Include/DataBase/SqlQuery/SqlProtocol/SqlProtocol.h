#pragma once

#include "Macro.h"

#include "ToolFrame.h"
#include "IMsgStream.h"

#include "Date.h"
#include "DateTime.h"

#include "SqlConst.h"
#include "SqlStruct.h"

enum ESqlOpCode{

	//系统协议
	PROTOCOL_MYSQL_SYSTEM_BEGIN = 0x5000,

	MSG_MYSQL_PING,
	MSG_MYSQL_PONG,
	MSG_MYSQL_SECRET,

	PROTOCOL_MYSQL_SYSTEM_END,

	//MYSQL协议
	PROTOCOL_MYSQL_CLIENT_BEGIN = 0x6000,

	MSG_MYSQL_DATABASE_OPEN,
	MSG_MYSQL_DATABASE_CLOSE,

	MSG_MYSQL_QUERY,		//请求
	MSG_MYSQL_RESPONSE,		//应答

	PROTOCOL_MYSQL_CLIENT_END,
};

//////////////////////////////////////////////////////////////////////////
struct MsgSqlPing
	:public ToolFrame::IMsgStream
{
	MSG_CONSTRUCT(MsgSqlPing,MSG_MYSQL_PING);
};

struct MsgSqlPong
	:public ToolFrame::IMsgStream
{
	MSG_CONSTRUCT(MsgSqlPong,MSG_MYSQL_PONG);
};

struct MsgSqlSecret
	:public ToolFrame::IMsgStream
{
	uint32 uSecretKey;
	uint32 uTimeNow;
	uint32 uAssID;
	MSG_CONSTRUCT_SERIALIZE(MsgSqlSecret,MSG_MYSQL_SECRET,uSecretKey & uTimeNow & uAssID);
};

//////////////////////////////////////////////////////////////////////////
//添加数据库
struct MsgSqlDatabaseOpen
	:public ToolFrame::IMsgStream
{
	std::string sIP;
 	uint16		uPort;
 	std::string sDBName;
 	std::string sUserName;
 	std::string sPwd;
 	uint8		uConcurrent;
 	MSG_CONSTRUCT_SERIALIZE(MsgSqlDatabaseOpen, MSG_MYSQL_DATABASE_OPEN, sIP & uPort & sDBName & sUserName & sPwd & uConcurrent);
};

struct MsgSqlDatabaseClose
	:public ToolFrame::IMsgStream
{
	std::string sDBName;
	MSG_CONSTRUCT_SERIALIZE(MsgSqlDatabaseClose, MSG_MYSQL_DATABASE_CLOSE, sDBName);
};

//请求协议
struct MsgSqlQuery
	:public ToolFrame::IMsgStream
{
	uint32		uSqlID;		//ID
	std::string sDBName;	//数据库名称
	std::string sSql;		//SQL语句
	uint32		uTimeOut;	//超时时间
	std::string sTag;		//标记
	MSG_CONSTRUCT_SERIALIZE(MsgSqlQuery, MSG_MYSQL_QUERY, uSqlID & sDBName & sSql & uTimeOut & sTag);
};

//应答协议
struct MsgSqlResponse
	:public ToolFrame::IMsgStream
{
	uint32					uSqlID;
	uint8					uErr;
	ToolFrame::SqlResults	vResult;
	MSG_CONSTRUCT_SERIALIZE(MsgSqlResponse, MSG_MYSQL_RESPONSE, uSqlID & uErr & vResult);
};
