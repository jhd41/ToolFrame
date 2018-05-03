#pragma once
#include "Macro.h"
#include <boost/asio.hpp>
#include "IDataSession.h"
#include "MacroDefineBoost.h"
#include "MacroDefineEx.h"
#include "TimeElapse.h"
#include "Mark.h"

using boost::asio::ip::tcp;
NS_TOOL_FRAME_BEGIN

//会话
//////////////////////////////////////////////////////////////////////////
class CDataSessionNetTcp;
typedef CSharePtr<CDataSessionNetTcp> DataSessionNetTcpPtr;

class CDataSessionNetTcp
	:public IDataSession
	,public CShareFromThis<CDataSessionNetTcp>
{
	FUN_CREATE_DATA_SESSION(CDataSessionNetTcp,DataSessionNetTcpPtr);
public:
	virtual	bool	Connect()override;
	virtual size_t	Send()override;
	virtual bool	Recv()override;
	virtual bool	Close()override;

	virtual std::string GetRemoteIP()const;
	virtual uint		GetRemotedPort()const;
	virtual std::string GetRemoteAddress()const;
public:
	virtual bool	OnConnectSucceed();
public:
	static bool		Init();
	static bool		RunOnce();
public:
	tcp::socket&	GetSocket();
private:
	bool	InitRecvBuffer();
private:
	bool	InitSocket();

	void	HandleResolve(const boost::system::error_code& error, tcp::resolver::iterator itrResolver);

	void	WaitConnect( tcp::resolver::iterator& itrResolver );
	void	OnConnect( const boost::system::error_code& error, tcp::resolver::iterator& itrResolver );

	size_t	SocketSend();
	void	OnSocketSend( const boost::system::error_code& error ,size_t uLen);

	bool	SocketRecv();
	void	OnSocketRecv( const boost::system::error_code& error ,size_t uLen );
private:
	void	DebugQuery(const tcp::resolver::iterator& itrResolver);
public:
	CDataSessionNetTcp(void);
	virtual ~CDataSessionNetTcp(void);
private:
	tcp::resolver				_tcpResolver;
	tcp::socket					_tcpSocket;
	StreamBufferPtr				_pRecvBuffer;
	CMark						_bRecv;

	std::string					_sRemoteIP;
	uint						_uRemotePort;
};

//接受器
//////////////////////////////////////////////////////////////////////////
class CDataAcceptorNetTcp;
typedef CSharePtr<CDataAcceptorNetTcp> DataAcceptorNetPtr;

class CDataAcceptorNetTcp
	:public IDataAcceptor
	,public CShareFromThis<CDataAcceptorNetTcp>
{
	FUN_CREATE_DATA_ACCEPTOR(CDataAcceptorNetTcp,DataAcceptorNetPtr);
public:
	virtual bool WaitAccept(const std::string& sAddress)override;
	virtual	bool Close()override;
private:
	bool WaitAccept();
	void OnAccept( const boost::system::error_code& error);
public:
	CDataAcceptorNetTcp();
	virtual ~CDataAcceptorNetTcp();
private:
	tcp::acceptor*				_ptcpAcceptor;
	DataSessionNetTcpPtr		_pSession;
	UINT						_uPort;
};

NS_TOOL_FRAME_END
