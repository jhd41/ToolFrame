#pragma once
#include "IDataSession.h"

NS_TOOL_FRAME_BEGIN
//会话
//////////////////////////////////////////////////////////////////////////
class CDataSessionMemory;
typedef CSharePtr<CDataSessionMemory>	DataSessionMemoryPtr;
typedef CWeakPtr<CDataSessionMemory>	WpMemoryPtr;

class CDataSessionMemory
	:public IDataSession
	,public CShareFromThis<CDataSessionMemory>
{
	FUN_CREATE_DATA_SESSION(CDataSessionMemory,DataSessionMemoryPtr);
public:
	virtual	bool	Connect();
	virtual size_t	Send();
	virtual bool	Recv();
	virtual bool	Close();
public:
	virtual bool	OnRecv();
public:
	CDataSessionMemory(void);
	virtual ~CDataSessionMemory(void);
private:
	CFIELD_PTR(WpMemoryPtr,TargetSession,p);
};

//接受器
//////////////////////////////////////////////////////////////////////////
class CDataAcceptorMemory;
typedef CSharePtr<CDataAcceptorMemory> DataAcceptorMemoryPtr;

class CDataAcceptorMemory
	:public IDataAcceptor
	,public CShareFromThis<CDataAcceptorMemory>
{
	FUN_CREATE_DATA_ACCEPTOR(CDataAcceptorMemory,DataAcceptorMemoryPtr);
public:
	virtual bool WaitAccept(const std::string& sAddress);
	virtual	bool Close();
public:
	DataSessionMemoryPtr	OnAccept(DataSessionMemoryPtr ptr);
public:
	CDataAcceptorMemory();
	virtual ~CDataAcceptorMemory();
private:
	DataSessionMemoryPtr _pSession;
};
NS_TOOL_FRAME_END
