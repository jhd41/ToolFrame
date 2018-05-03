#pragma once
#include "Macro.h"
#include <boost/asio.hpp>

#include "IDataSession.h"
#include "MacroDefineBoost.h"

using boost::asio::ip::udp;
NS_TOOL_FRAME_BEGIN
//会话
//////////////////////////////////////////////////////////////////////////
class CDataSessionNetUdp;
typedef CSharePtr<CDataSessionNetUdp> DataSessionNetUdpPtr;

class CDataSessionNetUdp
	:public IDataSession
	,public CShareFromThis<CDataSessionNetUdp>
{
	FUN_CREATE_DATA_SESSION(CDataSessionNetUdp,DataSessionNetUdpPtr);
public:
	virtual	bool	Connect()override;
	virtual size_t	Send()override;
	virtual bool	Recv()override;
	virtual bool	Close()override;
public:
	static	bool	Init();
	static	bool	RunOnce();
	static	bool	BroadCast(const std::string& sPort,StreamBufferPtr ptr);
public:
	udp::socket&	GetSocket();
	void			SetReceiver(const udp::endpoint& epReceiver);
private:
	void	HandleResolve(const boost::system::error_code& error, udp::resolver::iterator itrResolver);

	void	WaitConnect( udp::resolver::iterator& itrResolver );
	void	OnConnect( const boost::system::error_code& error, udp::resolver::iterator& itrResolver );

	void	OnSend( const boost::system::error_code& error ,size_t uLen );
private:
	bool	DebugQuery(const udp::resolver::iterator& itrResolver);
public:
	CDataSessionNetUdp(void);
	virtual ~CDataSessionNetUdp(void);
private:
	udp::resolver				_udpResolver;
	udp::socket					_udpSocket;
	udp::endpoint				_epReceiver;
};

//接受器
//////////////////////////////////////////////////////////////////////////
class CDataAcceptorNetUdp;
typedef CSharePtr<CDataAcceptorNetUdp> DataAcceptorNetPtr;

class CDataAcceptorNetUdp
	:public IDataAcceptor
	,public CShareFromThis<CDataAcceptorNetUdp>
{
	FUN_CREATE_DATA_ACCEPTOR(CDataAcceptorNetUdp,DataAcceptorNetPtr);
public:
	virtual bool InitBuffSize(size_t uRecvSize, size_t uSendSize, size_t uBlockSize)override;
	virtual bool WaitAccept(const std::string& sAddress)override;
	virtual	bool Close()override;
private:
	bool InitRecvBuffer();
	void WaitRecv();
	void OnRecv(const boost::system::error_code& error ,size_t uLen);
public:
	CDataAcceptorNetUdp();
	virtual ~CDataAcceptorNetUdp();
private:
	udp::socket*		_udpSocket;
	udp::endpoint		_epSender;
	DataSessionPtr		_pSession;
	StreamBufferPtr		_pRecvBuffer;
};
NS_TOOL_FRAME_END
