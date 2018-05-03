#include "DataSessionNetUdp.h"
#include "MProtocol.h"
#include "ToolStd.h"
#include "ApiBoost.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

bool InitDataSessionNetUdp(){
	MProtocol::Singleton().InsertFunSessionCreator	(LINK_TYPE_NET_UDP,	CDataSessionNetUdp::CreateClass);
	MProtocol::Singleton().InsertFunAcceptorCreator	(LINK_TYPE_NET_UDP,	CDataAcceptorNetUdp::CreateClass);
	MProtocol::Singleton().InsertFunSessionInit		(LINK_TYPE_NET_UDP,	CDataSessionNetUdp::Init);
	MProtocol::Singleton().InsertFunSessionRunOnce	(LINK_TYPE_NET_UDP,	CDataSessionNetUdp::RunOnce);
	MProtocol::Singleton().InsertFunBroadCast		(LINK_TYPE_NET_UDP,	CDataSessionNetUdp::BroadCast);
	
	return true;
}//仅仅绕过编译器完全链接的执行代码 

//会话
//////////////////////////////////////////////////////////////////////////
CDataSessionNetUdp::CDataSessionNetUdp(void)
	: _udpSocket(ApiBoost::GetGlobeIoService())
	, _udpResolver(ApiBoost::GetGlobeIoService())
{
	SetLinkType(LINK_TYPE_NET_UDP);
}

CDataSessionNetUdp::~CDataSessionNetUdp(void)
{
}

bool CDataSessionNetUdp::Connect()
{
	if (_vAddress.empty())
	{
		LOG_NET_ERR("ClientID:"<<GetClientID()<<" WaitConnect:Faild");

		MProtocol::Singleton().ReqClosing(shared_from_this(),NET_ERRCODE_CONNECT);
		return true;
	}

	SetAddress(ToolFrame::PopFront(_vAddress));

	//进行连接
	std::string sIP; std::string sPort;
	ASSERT_LOG_ERROR(ToolFrame::ResolveAddress(sIP, sPort, _sAddress));

	LOG_NET_DEBUG("ClientID:" << GetClientID() << " ReqConnect: IP:" << sIP << ":" << sPort);

	udp::resolver::query query(sIP, sPort);
	_udpResolver.async_resolve(query,
		boost::bind(&CDataSessionNetUdp::HandleResolve, this,
		boost::asio::placeholders::error, boost::asio::placeholders::iterator));
	return true;
}

void CDataSessionNetUdp::HandleResolve(const boost::system::error_code& error, udp::resolver::iterator itrResolver)
{
	if (error)
	{
		LOG_NET_ERR("ClientID:" << GetClientID() << " ReqConnect:" << error.message() << " Address:" << _sAddress);
		MProtocol::Singleton().ReqClosing(shared_from_this(), NET_ERRCODE_CONNECT);
		return;
	}
	WaitConnect(itrResolver);
}

void CDataSessionNetUdp::WaitConnect( udp::resolver::iterator& itrResolver )
{
	//如果所有连接全失败了
	if (itrResolver == udp::resolver::iterator())
	{
		//尝试新的一轮
		Connect();
		return;
	}

	LOG_NET_DEBUG("ClientID:"<<GetClientID()<<" WaitConnect");
	_epReceiver = *itrResolver;
	return _udpSocket.async_connect(_epReceiver,
		boost::bind(&CDataSessionNetUdp::OnConnect, shared_from_this(),
		boost::asio::placeholders::error, ++itrResolver));
}

void CDataSessionNetUdp::OnConnect( const boost::system::error_code& error, udp::resolver::iterator& itrResolver )
{
	LOG_NET_DEBUG("ClientID:"<<GetClientID()<<" WaitConnect");

	ASSERT_LOG_ERROR(INVALID_ID != GetClientID());

	if(error){
		LOG_NET_ERR("ClientID:"<<GetClientID()<<" OnConnect:"<<error.message());
		WaitConnect(itrResolver);
		return;
	}

	//连接成功
	MProtocol::Singleton().OnConnected(shared_from_this());
}

size_t CDataSessionNetUdp::Send()
{
	if (_epReceiver  == udp::endpoint())return 0;
	if (!SwapSendBuffer())return 0;

	ASSERT_LOG_ERROR(!_pSending->IsEmpty());

	size_t uSend = _pSending->GetLength();

	try
	{
		ASSERT_LOG_ERROR(uSend > 0);

		LOG_NET_DEBUG("ClientID:"<<GetClientID()<<" ReqSend");

		_udpSocket.async_send_to(boost::asio::buffer(_pSending->GetBuffer(), _pSending->GetLength()),
			_epReceiver,
			boost::bind(&CDataSessionNetUdp::OnSend, shared_from_this(),
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

	return uSend;
}

void CDataSessionNetUdp::OnSend( const boost::system::error_code& error ,size_t uLen )
{
	LOG_NET_DEBUG("ClientID:"<<GetClientID()<<" OnSend");
	if (error)
	{
		LOG_NET_DEBUG("ClientID:"<<GetClientID()<<" OnSend:"<<error.message());

		MProtocol::Singleton().ReqClosing(shared_from_this(),NET_ERRCODE_SEND);
		return;
	}

	ClearSendingBuffer();
}

bool CDataSessionNetUdp::Recv()
{
	//不能接收
	return true;
}

bool CDataSessionNetUdp::Close()
{
	boost::system::error_code ec;
	_udpSocket.close(ec);
	if (ec)
	{
		LOG_NET_ERR(ec.message());
		return false;
	}
	return true;
}

udp::socket& CDataSessionNetUdp::GetSocket()
{
	return _udpSocket;
}

bool CDataSessionNetUdp::DebugQuery( const udp::resolver::iterator& itrResolver )
{
	LOG_NET_DEBUG("ClientID:"<<GetClientID()<<" Query:");
	udp::resolver::iterator itr = itrResolver;
	while(itr != udp::resolver::iterator()){
		udp::endpoint endPoint = *itr;
		LOG_NET_DEBUG("ClientID:"<<GetClientID()<<" IP:"<<endPoint.address().to_string()<<" Port:"<<endPoint.port());
		++itr;
	}

	return true;
}

void CDataSessionNetUdp::SetReceiver( const udp::endpoint& epReceiver )
{
	_epReceiver = epReceiver;
}

bool CDataSessionNetUdp::Init()
{
	//常驻工作(没有实际意义,目的始终保持ioService有工作 从而不去清理工作任务。使得其能够在IOS平台正确运行)
	ApiBoost::SetGlobeServiceWork();
	return true;
}

bool CDataSessionNetUdp::RunOnce()
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

bool CDataSessionNetUdp::BroadCast(const std::string& sPort,StreamBufferPtr ptr)
{
	UINT uPort = 0;
	if (!ToolFrame::ToValue(sPort,uPort))return false;
	udp::socket udpSocket(ApiBoost::GetGlobeIoService(),udp::endpoint(udp::v4(),uPort));  
	boost::asio::socket_base::broadcast option(true);
	udpSocket.set_option(option);

	udp::endpoint epDest(boost::asio::ip::address::from_string("255.255.255.255"), uPort);
	udpSocket.send_to(boost::asio::buffer(ptr->GetBuffer(),ptr->GetLength()),epDest);

	return true;		 
}

//接受器
//////////////////////////////////////////////////////////////////////////
CDataAcceptorNetUdp::CDataAcceptorNetUdp()
{
	_udpSocket = nullptr;
	SetLinkType(LINK_TYPE_NET_UDP);
}

CDataAcceptorNetUdp::~CDataAcceptorNetUdp()
{
	Close();
	ToolFrame::Delete(_udpSocket);
}

bool CDataAcceptorNetUdp::WaitAccept( const std::string& sAddress )
{
	ASSERT_LOG_ERROR(nullptr == _udpSocket);

	UINT uPort = 0;
	if (!ToolFrame::ToValue(sAddress,uPort))return false;

	try
	{
		_udpSocket = new udp::socket(ApiBoost::GetGlobeIoService(), udp::endpoint(udp::v6(), uPort));
		_pSession = CDataSessionNetUdp::CreateClass();
		_pSession->SetReceiver(GetReceiver());
		_pSession->SetAccepterKey(GetAccepterKey());
	}
	catch (boost::system::error_code& err){
		LOG_NET_ERR(err.message());
		return false;
	}
	catch (std::exception& e)
	{
		LOG_NET_ERR(e.what());
		return false;
	}

	if (!MProtocol::Singleton().AddSession(_pSession))
	{
		MProtocol::Singleton().DestroySession(_pSession);
		MProtocol::Singleton().CloseServer(GetAddress(),GetLinkType());
		return false;
	}

	//连接成功
	if (MProtocol::Singleton().OnConnected(_pSession))
		WaitRecv();
	return true;
}

bool CDataAcceptorNetUdp::InitRecvBuffer()
{
	ASSERT_LOG_ERROR(!_pRecvBuffer);
	_pRecvBuffer = StreamBufferMallocPtr(new CStreamBufferMalloc(GetRecvBufferSize()));
	return true;
}

void CDataAcceptorNetUdp::WaitRecv()
{
	ASSERT_LOG_ERROR(_udpSocket);

	_epSender = udp::endpoint();

	try
	{
		InitRecvBuffer();

		_udpSocket->async_receive_from(
			boost::asio::buffer(_pRecvBuffer->GetBuffer(), _pRecvBuffer->GetMaxSize()),
			_epSender,
			boost::bind(&CDataAcceptorNetUdp::OnRecv, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			));
	}
	catch (std::exception& error)
	{
		LOG_NET_ERR("CDataAcceptorNetUdp:"<< error.what());
	}
	catch (...)
	{
		LOG_NET_ERR("CDataAcceptorNetUdp:");
	}
}

void CDataAcceptorNetUdp::OnRecv( const boost::system::error_code& error ,size_t uLen)
{
	ASSERT_LOG_ERROR(_pSession);
	_pSession->SetReceiver(GetReceiver());

	_pRecvBuffer->SetSize(uLen);
	_pRecvBuffer->ResetCursor();
	ASSERT_LOG_ERROR(RecvDataSplice(_pRecvBuffer));
	ToolFrame::SetPtrNull(_pRecvBuffer);

	//连接成功
	MProtocol::Singleton().OnRecved(_pSession);

	WaitRecv();
}

bool CDataAcceptorNetUdp::Close()
{
	ASSERT_LOG_ERROR(_udpSocket);
	boost::system::error_code eErrCode;
	eErrCode = _udpSocket->close(eErrCode);
	if (eErrCode)
	{
		LOG_NET_ERR(" CDataAcceptorNetUdp::Close():"<<eErrCode.message());
	}

	ASSERT_LOG_ERROR(_pSession);
	ASSERT_LOG_ERROR(MProtocol::Singleton().RemoveSession(_pSession->GetClientID()));
	MProtocol::Singleton().ReqClosing(_pSession,NET_ERRCODE_INVAILD);
	return true;
}

bool CDataAcceptorNetUdp::InitBuffSize(size_t uRecvSize, size_t uSendSize, size_t uBlockSize)
{
	return InitBuffSize(uRecvSize, uSendSize, uBlockSize);
}

NS_TOOL_FRAME_END
