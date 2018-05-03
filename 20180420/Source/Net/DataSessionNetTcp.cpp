#include "DataSessionNetTcp.h"
#include "MProtocol.h"
#include "ToolStd.h"
#include "ToolBoost.h"
#include "ToolPlat.h"

#include "ApiBoost.h"

NS_TOOL_FRAME_BEGIN

bool InitDataSessionNetTcp(){
	MProtocol::Singleton().InsertFunSessionCreator	(LINK_TYPE_NET_TCP,	CDataSessionNetTcp::CreateClass);
	MProtocol::Singleton().InsertFunAcceptorCreator	(LINK_TYPE_NET_TCP,	CDataAcceptorNetTcp::CreateClass);
	MProtocol::Singleton().InsertFunSessionInit		(LINK_TYPE_NET_TCP,	CDataSessionNetTcp::Init);
	MProtocol::Singleton().InsertFunSessionRunOnce	(LINK_TYPE_NET_TCP,	CDataSessionNetTcp::RunOnce);
	return true;
}//仅仅绕过编译器完全链接的执行代码 

//会话
//////////////////////////////////////////////////////////////////////////
CDataSessionNetTcp::CDataSessionNetTcp(void)
	:_tcpResolver(ApiBoost::GetGlobeIoService())
	,_tcpSocket(ApiBoost::GetGlobeIoService())
{
	_uRemotePort = 0;

	SetLinkType(LINK_TYPE_NET_TCP);
}

CDataSessionNetTcp::~CDataSessionNetTcp(void)
{
}

bool CDataSessionNetTcp::Connect()
{
	if (_vAddress.empty())
	{
		LOG_NET_ERR("ClientID:"<<GetClientID()<<" WaitConnect:AllFaild");
		MProtocol::Singleton().ReqClosing(shared_from_this(), NET_ERRCODE_CONNECT);
		return true;
	}

	SetAddress(ToolFrame::PopFront(_vAddress));

	//进行连接
	std::string sIP; std::string sPort;
	ASSERT_LOG_ERROR(ToolFrame::ResolveAddress(sIP, sPort, _sAddress));

	LOG_NET_DEBUG("ClientID:" << GetClientID() << " ReqConnect: IP:" << sIP << ":" << sPort);

	try
	{

		tcp::resolver::query query(sIP, sPort);
		_tcpResolver.async_resolve(query,
			boost::bind(&CDataSessionNetTcp::HandleResolve, this,
				boost::asio::placeholders::error, boost::asio::placeholders::iterator));
	}
	catch (std::exception& error)
	{
		LOG_NET_ERR("ClientID:" << GetClientID() <<" IP:"<< sIP <<" Port:"<< sPort <<" Err:" << error.what());
		MProtocol::Singleton().ReqClosing(shared_from_this(), NET_ERRCODE_CONNECT);
		return true;
	}
	catch (...)
	{
		LOG_NET_ERR("ClientID:" << GetClientID() << " IP:" << sIP << " Port:" << sPort);
		MProtocol::Singleton().ReqClosing(shared_from_this(), NET_ERRCODE_CONNECT);
		return true;
	}
	return true;
}

void CDataSessionNetTcp::HandleResolve(const boost::system::error_code& error, tcp::resolver::iterator itrResolver)
{
	if (error)
	{
		LOG_NET_ERR("ClientID:" << GetClientID() << " ReqConnect:" << error.message() << " Address:" << _sAddress);
		MProtocol::Singleton().ReqClosing(shared_from_this(), NET_ERRCODE_CONNECT);
		return ;
	}
	WaitConnect(itrResolver);
}

void CDataSessionNetTcp::WaitConnect( tcp::resolver::iterator& itrResolver )
{
	//如果所有连接全失败了
	if (itrResolver == tcp::resolver::iterator())
	{
		//尝试新的一轮
		Connect();
		return;
	}

	try
	{
		tcp::endpoint endPoint = *itrResolver;

		LOG_NET_DEBUG("ClientID:" << GetClientID() << " WaitConnect IP:" << endPoint.address().to_string() << ":" << endPoint.port());
		_tcpSocket.async_connect(endPoint,
			boost::bind(&CDataSessionNetTcp::OnConnect, shared_from_this(),
				boost::asio::placeholders::error, itrResolver));
	}
	catch (std::exception& error)
	{
		LOG_NET_ERR("ClientID:" << GetClientID() << " Err:" << error.what());
		MProtocol::Singleton().ReqClosing(shared_from_this(), NET_ERRCODE_CONNECT);
	}
	catch (...)
	{
		LOG_NET_ERR("ClientID:" << GetClientID());
		MProtocol::Singleton().ReqClosing(shared_from_this(), NET_ERRCODE_CONNECT);
	}
	return;
}

void CDataSessionNetTcp::OnConnect( const boost::system::error_code& error, tcp::resolver::iterator& itrResolver )
{
	ASSERT_LOG_ERROR(INVALID_ID != GetClientID());

	tcp::endpoint endPoint = *itrResolver;

	if(error){
		LOG_NET_ERR("ClientID:"<<GetClientID()<<" OnConnectFaild IP:"<<endPoint.address().to_string()<<":"<<endPoint.port()<<" Err:"<<error.message());
		WaitConnect(++itrResolver);
		return;
	}

	OnConnectSucceed();
}

size_t CDataSessionNetTcp::Send()
{
	if (!SwapSendBuffer())return 0;

	return SocketSend();
}

size_t CDataSessionNetTcp::SocketSend()
{
	ASSERT_LOG_ERROR(!_pSending->IsEmpty());

	size_t uSend = _pSending->GetLength();

	try
	{
		ASSERT_LOG_ERROR(uSend > 0);

		LOG_NET_DEBUG("ClientID:" << GetClientID() << " ReqSend");
		_tcpSocket.async_send(boost::asio::buffer(_pSending->GetBuffer(), _pSending->GetLength()),
			boost::bind(&CDataSessionNetTcp::OnSocketSend, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			));
	}
	catch (std::exception& error)
	{
		LOG_NET_ERR("ClientID:" << GetClientID() << " ReqSend:" << error.what());

		MProtocol::Singleton().ReqClosing(shared_from_this(), NET_ERRCODE_REQ_SEND);
		return 0;
	}
	catch (...)
	{
		LOG_NET_ERR("ClientID:" << GetClientID());
		MProtocol::Singleton().ReqClosing(shared_from_this(), NET_ERRCODE_REQ_SEND);
	}
	return uSend;
}

void CDataSessionNetTcp::OnSocketSend(const boost::system::error_code& error, size_t uLen)
{
	LOG_NET_DEBUG("ClientID:"<<GetClientID()<<" OnSend");
	if (error)
	{
		LOG_NET_DEBUG("ClientID:"<<GetClientID()<<" OnSend:"<<error.message());
		MProtocol::Singleton().ReqClosing(shared_from_this(),NET_ERRCODE_SEND);
		return;
	}

	ClearSendingBuffer();
	Send();
}

bool CDataSessionNetTcp::Recv()
{
	if (!_bRecv.TryMark())return false;

	return SocketRecv();
}

bool CDataSessionNetTcp::SocketRecv()
{
	//重置时间条
	_xTimeFree.Resume();

	try
	{
		InitRecvBuffer();

		ASSERT_LOG_ERROR(_pRecvBuffer);
		_tcpSocket.async_receive(
			boost::asio::buffer(_pRecvBuffer->GetBuffer(), _pRecvBuffer->GetMaxSize()),
			boost::bind(&CDataSessionNetTcp::OnSocketRecv, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
	catch (std::exception& error)
	{
		LOG_NET_ERR("ClientID:" << GetClientID() << " ReqSend:" << error.what());

		MProtocol::Singleton().ReqClosing(shared_from_this(), NET_ERRCODE_REQ_RECV);
	}
	catch (...)
	{
		LOG_NET_ERR("ClientID:" << GetClientID());
		MProtocol::Singleton().ReqClosing(shared_from_this(), NET_ERRCODE_REQ_RECV);
	}
	return true;
}

void CDataSessionNetTcp::OnSocketRecv( const boost::system::error_code& error ,size_t uLen )
{
	//暂停空闲时间
	_xTimeFree.Pause();

	LOG_NET_DEBUG("ClientID:"<<GetClientID()<<" OnRecv");

	if (error)
	{
		LOG_NET_DEBUG("ClientID:"<<GetClientID()<<" OnRecv:"<<error.message());
		MProtocol::Singleton().ReqClosing(shared_from_this(),NET_ERRCODE_RECV);
		return;
	}

	//接收成功
	_pRecvBuffer->SetSize(uLen);
	_pRecvBuffer->ResetCursor();
	if (!RecvDataSplice(_pRecvBuffer))
	{
		LOG_NET_ERR("ClientID:"<<GetClientID()<<" OnRecv: Err:"<<NET_ERRCODE_REQ_RECV_BUFF_FULL);
		MProtocol::Singleton().ReqClosing(shared_from_this(),NET_ERRCODE_REQ_RECV_BUFF_FULL);
		return;
	}

	ToolFrame::SetPtrNull(_pRecvBuffer);

	MProtocol::Singleton().OnRecved(shared_from_this());
	SocketRecv();
}

bool CDataSessionNetTcp::Close()
{
	boost::system::error_code ec;
	_tcpSocket.close(ec);
	if (ec)
	{
		LOG_NET_ERR(ec.message());
		return false;
	}
	return true;
}

tcp::socket& CDataSessionNetTcp::GetSocket()
{
	return _tcpSocket;
}

void CDataSessionNetTcp::DebugQuery( const tcp::resolver::iterator& itrResolver )
{
	LOG_NET_DEBUG("ClientID:"<<GetClientID()<<" Query:");
	tcp::resolver::iterator itr = itrResolver;
	while(itr != tcp::resolver::iterator()){
		tcp::endpoint endPoint = *itr;
		LOG_NET_DEBUG("ClientID:"<<GetClientID()<<" IP:"<<endPoint.address().to_string()<<" Port:"<<endPoint.port());
		++itr;
	}
}

bool CDataSessionNetTcp::Init()
{
	//常驻工作(没有实际意义,目的始终保持ioService有工作 从而不去清理工作任务。使得其能够在IOS平台正确运行)
	ApiBoost::SetGlobeServiceWork();
	return true;
}

bool CDataSessionNetTcp::RunOnce()
{
	boost::asio::io_service& ioService = ApiBoost::GetGlobeIoService();
	boost::system::error_code error;
	ioService.poll(error);
	if (error)
	{
		LOG_ERROR_MSG("Run:"<<error.message());
	}
	return true;
}

std::string CDataSessionNetTcp::GetRemoteIP() const
{
	return _sRemoteIP;
}

uint CDataSessionNetTcp::GetRemotedPort() const
{
	return _uRemotePort;
}

std::string CDataSessionNetTcp::GetRemoteAddress() const
{
	return MAKE_STRING(_sRemoteIP<<":"<<_uRemotePort);
}

bool CDataSessionNetTcp::InitRecvBuffer()
{
	ASSERT_LOG_ERROR(!_pRecvBuffer);

	//设置接收缓冲区
	_pRecvBuffer = StreamBufferPtr(new CStreamBufferMalloc(_uRecvSize > 0 ? _uRecvSize : _uBlockSize));
	return true;
}

bool CDataSessionNetTcp::InitSocket()
{
 	boost::system::error_code ec;
 
	//设置接收缓冲区
	if (_uRecvSize>0)
	{
		boost::asio::socket_base::receive_buffer_size optionRecvBuffer((int)_uRecvSize);
		_tcpSocket.set_option(optionRecvBuffer, ec);
		if (ec)
		{
			LOG_NET_ERR(ec.message());
			return false;
		}
	}

//	IOS 发送缓冲区 必须设置不为 0 也不能为1,欺骗ios,能够连接上 但发送显示成功 但实际收不到
//  boost::asio::socket_base::send_buffer_size optionSendBuffer(0);//_uSendSize
//  _tcpSocket.set_option(optionSendBuffer,ec);
//  if (ec)
//  {
//  	LOG_NET_ERR(ec.message());
//  	return false;
//	}
// 
//	 boost::asio::ip::tcp::no_delay optionNoDelay;
//	_tcpSocket.set_option(optionNoDelay,ec);
// 	if (ec)
//  {
// 		LOG_NET_ERR(ec.message());
//  	return false;
//  }
	return true;
}

bool CDataSessionNetTcp::OnConnectSucceed()
{
	//连接成功 初始化Socket
	if (!InitSocket())
	{
		LOG_NET_ERR("ClientID:"<<GetClientID()<<" InitSocketFaild. OnConnectFailed");
		MProtocol::Singleton().ReqClosing(shared_from_this(), NET_ERRCODE_CONNECT);
		return false;
	}

	//获取基本信息
	try {
		_sRemoteIP	 = _tcpSocket.remote_endpoint().address().to_string();
		_uRemotePort = _tcpSocket.remote_endpoint().port();
	}
	catch (boost::system::system_error &ec) {
		LOG_NET_ERR("ClientID:" << GetClientID()<<" RemoteIP:"<<ec.what());
	}
	catch (...)
	{
		LOG_NET_ERR("ClientID:" << GetClientID());
	}

	//连接成功
	LOG_NET_DEBUG("ClientID:"<<GetClientID()<<" OnConnectSucceed IP: "<<GetRemoteAddress());
	MProtocol::Singleton().OnConnected(shared_from_this());
	return true;
}

//接受器
//////////////////////////////////////////////////////////////////////////
CDataAcceptorNetTcp::CDataAcceptorNetTcp()
{
	_uPort = 0;
	_ptcpAcceptor = nullptr;
	SetLinkType(LINK_TYPE_NET_TCP);
}

CDataAcceptorNetTcp::~CDataAcceptorNetTcp()
{
	ToolFrame::Delete(_ptcpAcceptor);
}

bool CDataAcceptorNetTcp::WaitAccept( const std::string& sAddress )
{
	ASSERT_LOG_ERROR(nullptr == _ptcpAcceptor);

	if (!ToolFrame::ToValue(sAddress,_uPort))return false;

	LOG_NET_DEBUG( "Port:"<<_uPort<<" CreateAcceptor");

	if (ToolFrame::IsPortOccupied(_uPort))
	{
		LOG_NET_ERR("Port:" << _uPort << " 端口被占用了!");
		return false;
	}

	try
	{
 		_ptcpAcceptor = new tcp::acceptor(ApiBoost::GetGlobeIoService(), tcp::endpoint(tcp::v6(), _uPort),false);
 		ASSERT_LOG_ERROR(_ptcpAcceptor);
	}
	catch (boost::system::error_code& err){
		LOG_NET_ERR("Port:"<<_uPort<<" "<<err.message());
		return false;
	}
	catch (boost::exception& err)
	{
		LOG_NET_ERR("Port:"<<_uPort);
		err;
		return false;
	}
	catch (boost::asio::error::basic_errors& err)
	{
		LOG_NET_ERR("Port:"<<_uPort<<" "<<"basic_errors:"<<err);
		return false;
	}
	catch (boost::asio::error::netdb_errors& err)
	{
		LOG_NET_ERR("Port:"<<_uPort<<" "<<"netdb_errors:"<<err);
		return false;
	}
	catch (boost::asio::error::addrinfo_errors& err)
	{
		LOG_NET_ERR("Port:"<<_uPort<<" "<<"addrinfo_errors:"<<err);
		return false;
	}
	catch (boost::asio::error::misc_errors& err)
	{
		LOG_NET_ERR("Port:"<<_uPort<<" "<<"misc_errors:"<<err);
		return false;
	}
	catch (...)
	{
		LOG_NET_ERR("Port:"<<_uPort);
		return false;
	}

	return WaitAccept();
}

bool CDataAcceptorNetTcp::WaitAccept()
{
	try
	{
		ASSERT_LOG_ERROR(!_pSession);
		ToolFrame::DynamicCast(_pSession, MProtocol::Singleton().CreateSession(GetLinkType()));

		ASSERT_LOG_ERROR(_pSession);
		_pSession->SetAccepterKey(GetAccepterKey());
		_pSession->SetReceiver(GetReceiver());
		_pSession->InitBuffSize(_uRecvSize, _uSendSize, _uBlockSize);

		LOG_NET_DEBUG("Port:" << _uPort << " WaitAccept");

		ASSERT_LOG_ERROR(_ptcpAcceptor);
		_ptcpAcceptor->async_accept(_pSession->GetSocket(),
			boost::bind(&CDataAcceptorNetTcp::OnAccept, shared_from_this(),
				boost::asio::placeholders::error
			));
	}
	catch (std::exception& error)
	{
		LOG_NET_ERR("Port:"<< _uPort << error.what());
	}
	catch (...)
	{
		LOG_NET_ERR("Port:" << _uPort);
	}
	return true;
}

void CDataAcceptorNetTcp::OnAccept( const boost::system::error_code& error)
{
	if (IsClosed())
	{
		LOG_NET_DEBUG("Port:"<<_uPort<<" OnAccept:Closed");
		MProtocol::Singleton().DestroySession(_pSession);
		_pSession = DataSessionNetTcpPtr();
		return ;
	}
	ASSERT_LOG_ERROR(_pSession);
	if (error){
		LOG_NET_ERR("Port:"<<_uPort<<" OnAccept:"<<error.message());
		MProtocol::Singleton().DestroySession(_pSession);
		_pSession = DataSessionNetTcpPtr();
		WaitAccept();
		return ;
	}

	//尝试添加到回话列表
	if (!MProtocol::Singleton().AddSession(_pSession))
	{
		LOG_NET_ERR("Port:" << _uPort << "Max!");
		MProtocol::Singleton().DestroySession(_pSession);
		_pSession = DataSessionNetTcpPtr();
		WaitAccept();
		return;
	}

	UINT uClientID = _pSession->GetClientID();
	ASSERT_LOG_ERROR(INVALID_ID !=  uClientID);

	LOG_NET_DEBUG("Port:"<<_uPort<<" OnAcceptSucceed");
	_pSession->OnConnectSucceed();

	//等待新连接
	ToolFrame::SetPtrNull(_pSession);
	WaitAccept();
}

bool CDataAcceptorNetTcp::Close()
{
	ASSERT_LOG_ERROR(_ptcpAcceptor);
	boost::system::error_code eErrCode;
	eErrCode = _ptcpAcceptor->close(eErrCode);
	if (eErrCode)
	{
		LOG_NET_ERR(" CDataAcceptorNet::Close():"<<eErrCode.message());
	}

	ASSERT_LOG_ERROR(_pSession);
	ASSERT_LOG_ERROR(INVALID_ID != _pSession->GetClientID());
	ASSERT_LOG_ERROR_MSG(MProtocol::Singleton().RemoveSession(_pSession->GetClientID())," ClientID:"<< _pSession->GetClientID());
	MProtocol::Singleton().DestroySession(_pSession);
	ToolFrame::SetPtrNull(_pSession);
	return true;
}

NS_TOOL_FRAME_END
