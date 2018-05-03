#include "DataSessionMemory.h"
#include "MProtocol.h"
#include "ToolBoost.h"

NS_TOOL_FRAME_BEGIN

bool InitDataSessionMemory(){
	MProtocol::Singleton().InsertFunSessionCreator	(LINK_TYPE_MEM,	CDataSessionMemory::CreateClass);
	MProtocol::Singleton().InsertFunAcceptorCreator	(LINK_TYPE_MEM,	CDataAcceptorMemory::CreateClass);
	return true;
}//仅仅绕过编译器完全链接的执行代码 

//会话
//////////////////////////////////////////////////////////////////////////
CDataSessionMemory::CDataSessionMemory(void)
{
	SetLinkType(LINK_TYPE_MEM);
}

CDataSessionMemory::~CDataSessionMemory(void)
{
}

bool CDataSessionMemory::Connect()
{
	while (!_vAddress.empty())
	{
		SetAddress(ToolFrame::PopFront(_vAddress));

		DataAcceptorPtr ptrBase= MProtocol::Singleton().GetDataAcceptor(_sAddress,GetLinkType());
		DataAcceptorMemoryPtr ptrAcceptor;
		ASSERT_LOG_ERROR(ToolFrame::DynamicCast(ptrAcceptor, ptrBase));

		//连接接受器
		if (ptrAcceptor)
		{
			DataSessionMemoryPtr ptrTarget = ptrAcceptor->OnAccept(shared_from_this());
			ASSERT_LOG_ERROR(ptrTarget);
			if (!ptrTarget)return false;

			SetTargetSession(ptrTarget);

			MProtocol::Singleton().OnConnected(shared_from_this());

			return true;
		}
	}

	return MProtocol::Singleton().ReqClosing(shared_from_this(), NET_ERRCODE_CONNECT);
}

size_t CDataSessionMemory::Send()
{
	DataSessionMemoryPtr ptrTarget = GetTargetSession().lock();
	if (!ptrTarget)return 0;
	if (!SwapSendBuffer())return 0;
	ASSERT_LOG_ERROR(!_pSending->IsEmpty());
	
	//接收成功
	size_t uSend = _pSending->GetLength();
	if (!RecvDataSplice(_pSending))
	{
		LOG_NET_ERR("ClientID:" << GetClientID() << " OnRecv: Err:" << NET_ERRCODE_REQ_RECV_BUFF_FULL);
		MProtocol::Singleton().ReqClosing(shared_from_this(), NET_ERRCODE_REQ_RECV_BUFF_FULL);
		return 0;
	}

	ToolFrame::SetPtrNull(_pSending);

	ptrTarget->OnRecv();
	ClearSendingBuffer();
	return uSend;
}

bool CDataSessionMemory::Recv()
{
	return true;
}

bool CDataSessionMemory::Close()
{
	DataSessionMemoryPtr ptrTarget = GetTargetSession().lock();
	if (ptrTarget)
	{
		MProtocol::Singleton().ReqClosing(ptrTarget,INVALID_ID);
	}

	SetTargetSessionNull();
	return true;
}

bool CDataSessionMemory::OnRecv()
{
	MProtocol::Singleton().OnRecved(shared_from_this());
	return true;
}

//接受器
//////////////////////////////////////////////////////////////////////////;
CDataAcceptorMemory::CDataAcceptorMemory()
{
	SetLinkType(LINK_TYPE_MEM);
}

CDataAcceptorMemory::~CDataAcceptorMemory()
{

}

bool CDataAcceptorMemory::WaitAccept( const std::string& sAddress )
{
	ASSERT_LOG_ERROR(!_pSession);
	ToolFrame::DynamicCast(_pSession,MProtocol::Singleton().CreateSession(GetLinkType()));

	ASSERT_LOG_ERROR(_pSession);
	_pSession->SetReceiver(GetReceiver());
	_pSession->SetAccepterKey(GetAccepterKey());

	if (!MProtocol::Singleton().AddSession(_pSession))
	{
		MProtocol::Singleton().DestroySession(_pSession);
		MProtocol::Singleton().CloseServer(GetAddress(),GetLinkType());
		return INVALID_ID;
	}

	return true;
}

DataSessionMemoryPtr CDataAcceptorMemory::OnAccept( DataSessionMemoryPtr ptr )
{
	ASSERT_LOG_ERROR(_pSession);
	_pSession->SetTargetSession(ptr);

	MProtocol::Singleton().OnConnected(_pSession);

	DataSessionMemoryPtr ptrOld = _pSession;
	_pSession = DataSessionMemoryPtr();
	WaitAccept(GetAddress());
	return ptrOld;
}

bool CDataAcceptorMemory::Close()
{
	ASSERT_LOG_ERROR(_pSession);
	ASSERT_LOG_ERROR(MProtocol::Singleton().RemoveSession(_pSession->GetClientID()));
	MProtocol::Singleton().DestroySession(_pSession);
	_pSession = DataSessionMemoryPtr();
	return true;
}

NS_TOOL_FRAME_END
