#include "MProtocol.h"

#include "ToolBoost.h"
#include "ToolPlat.h"
#include "TimeOut.h"
#include "TimeElapse.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN
MProtocol::MProtocol(void)
{
	_bStartUp = false;

	SetRecvSize(65535);
	SetSendSize(65535);
	SetBlockSize(4096);
}

MProtocol::~MProtocol(void)
{
	StopThread();
}

UINT MProtocol::Connect(IDataReceiver* pReceiver, const VectorString& vAddress, ELinkType eLinkType, size_t uRecvSize/*= 0xFFFF*/, size_t uSendSize/*= 0xFFFF*/, size_t uBlockSize /*= 0xFFFF*/)
{
	if (uBlockSize <= 0)return INVALID_ID;

	VectorString vIP;
	VectorString::const_iterator itr;
	foreach(itr, vAddress) {
		ToolFrame::Merge(vIP, ToolFrame::SplitAddress(*itr));
	}

	return PushConnect(pReceiver, vIP, eLinkType, uRecvSize, uSendSize, uBlockSize);
}

UINT MProtocol::Connect(IDataReceiver* pReceiver, const std::string& sAddress, ELinkType eLinkType, size_t uRecvSize/*= 0xFFFF*/, size_t uSendSize/*= 0xFFFF*/, size_t uBlockSize /*= 0xFFFF*/)
{
	if (uBlockSize <= 0)return INVALID_ID;
	return PushConnect(pReceiver, ToolFrame::SplitAddress(sAddress), eLinkType, uRecvSize, uSendSize, uBlockSize);
}

bool MProtocol::Disconnect( UINT uClientID,bool bCallBack /*= true*/,int nErrCode /*= INVALID_ID*/ )
{
	if (INVALID_ID == uClientID)return false;
	DataSessionPtr ptr = GetSession(uClientID);
	if (!ptr)return false;

	return ReqClosing(ptr,nErrCode,bCallBack,false);
}

bool MProtocol::Send( UINT uClientID, const void* pMsg,size_t uLen )
{
	if (INVALID_ID == uClientID)return false;
	if (!pMsg)return false;
	if (uLen<=0)return false;

	DataSessionPtr ptrSession = GetSession(uClientID);
	if (!ptrSession)return false;

	//写入发送缓冲区
	if (ptrSession->SendData(pMsg, uLen) <= 0)
	{
		LOG_NET_ERR("ClientID:"<< uClientID<<" SendBuffFull!");
		ReqClosing(ptrSession, NET_ERRCODE_REQ_SEND_BUFF_FULL);
		return false;
	}

	ptrSession->TryMarkNet(IDataSession::REQ_SEND);
	PushQueueNet(ptrSession);

	return true;
}

bool MProtocol::Send( const VectorUint& vClientID, const void* pMsg,size_t uLen )
{
	VectorUint::const_iterator itr;
	foreach(itr,vClientID){
		Send(*itr,pMsg,uLen);
	}

	return true;
}

bool MProtocol::Send( UINT uClientID, StreamBinaryPtr ptr )
{
	if (INVALID_ID == uClientID)return false;
	if (!ptr)return false;
	if (ptr->IsEmpty())return false;

	DataSessionPtr ptrSession = GetSession(uClientID);
	if (!ptrSession)return false;

	//写入发送缓冲区
	if (ptrSession->SendData(ptr) <= 0)
	{
		LOG_NET_ERR("ClientID:" << uClientID << " SendBuffFull!");
		ReqClosing(ptrSession, NET_ERRCODE_REQ_SEND_BUFF_FULL);
		return false;
	}

	ptrSession->TryMarkNet(IDataSession::REQ_SEND);
	PushQueueNet(ptrSession);

	return true;
}

bool MProtocol::Send( const VectorUint& vClientID, StreamBinaryPtr ptr )
{
	if (!ptr)return false;
	
	VectorUint::const_iterator itr;
	foreach(itr,vClientID){
		Send(*itr,ptr);
	}

	return true;
}

bool MProtocol::Send(UINT uClientID, const IDataSerialize& xSerialize)
{
	if (INVALID_ID == uClientID)return false;

	DataSessionPtr ptrSession = GetSession(uClientID);
	if (!ptrSession)return false;

	//写入发送缓冲区
	if (ptrSession->SendData(xSerialize) <= 0)
	{
		LOG_NET_ERR("ClientID:" << uClientID << " SendBuffFull!");
		ReqClosing(ptrSession, NET_ERRCODE_REQ_SEND_BUFF_FULL);
		return false;
	}

	ptrSession->TryMarkNet(IDataSession::REQ_SEND);
	PushQueueNet(ptrSession);
	return true;
}

bool MProtocol::Send(const VectorUint& vClientID, const IDataSerialize& xSerialize)
{
	VectorUint::const_iterator itr;
	foreach(itr, vClientID) {
		Send(*itr, xSerialize);
	}

	return true;
}

bool MProtocol::Send(const VectorUint& vClientID, const std::string& sMsg)
{
	return Send(vClientID, sMsg.c_str(), sMsg.length());
}

bool MProtocol::Send(UINT uClientID, const std::string& sMsg)
{
	return Send(uClientID, sMsg.c_str(), sMsg.length());
}

DataSessionPtr MProtocol::GetSession(UINT uClientID)const
{
	return _vSession.GetPtrValueByKey(uClientID);
}

DataSessionPtr MProtocol::CreateSession( ELinkType eLinkType )
{
	FunDataSessionCreator fn = ToolFrame::GetPtrValueByKey(_vFunSessionCreator,eLinkType);
	if (!fn)return DataSessionPtr();

	return fn();
}

bool MProtocol::DestroySession( DataSessionPtr ptr )
{
	return true;
}

bool MProtocol::AddSession( DataSessionPtr ptr )
{
	if (!TryAddConnect(ptr->GetAccepterKey()))
		return false;

	ASSERT_LOG_ERROR(INVALID_ID == ptr->GetClientID());

	//分配ID 并且 添加至会话列表
	CLockWrite lock(_vSession.GetMutex());
	
	UINT uClientID = _imClientID.MakeID(_vSession.GetMap());
	if (INVALID_ID == uClientID)return false;
	ptr->SetClientID(uClientID);

	ASSERT_LOG_ERROR(ToolFrame::Insert(_vSession.GetMap(), uClientID, ptr));

	return true;
}

bool MProtocol::RemoveSession( UINT uClientID )
{
	if (INVALID_ID == uClientID)return false;

	DataSessionPtr ptr = _vSession.GetValueByKey(uClientID);
	if (!ptr)return false;
	
	//移除有效会话
	ASSERT_LOG_ERROR(_vSession.EraseByKey(uClientID));
	ASSERT_LOG_ERROR(TryRemoveConnect(ptr->GetAccepterKey()));

	return true;
}

bool MProtocol::ProcessNet( UINT64 nMillSecond )
{
	size_t uCount=0;
	QueueSession vProcessFail;//处理失败的队列

	CTimeOut timeOut(nMillSecond);

	//循环取出队列头的会话
	while(!timeOut.IsTimeOut()){
		DataSessionPtr ptrSession = _vQueueNet.PopFrontPtr();
		if (!ptrSession)break;

		CLockScoped lockScoped(ptrSession->GetMutex(),true);
		if (!lockScoped.IsLocked())
		{
			vProcessFail.Push(ptrSession);
			continue;
		}

		if (ptrSession->TryClearNet(IDataSession::REQ_NET_QUEUE))
		{
			if (ptrSession->TryClearNet(IDataSession::REQ_CONNECT)){
				if (!ptrSession->Connect()){
					ASSERT_LOG_ERROR(ReqClosing(ptrSession,NET_ERRCODE_CONNECT));
				}
			}
			if (ptrSession->TryClearNet(IDataSession::REQ_SEND)){
				_xSendCount.AddCount( ptrSession->Send());
			}
			if (ptrSession->TryClearNet(IDataSession::REQ_RECV)){
				ptrSession->Recv();
			}
			if (ptrSession->TryClearNet(IDataSession::REQ_CLOSE)){
				ASSERT_LOG_ERROR(ptrSession->IsClosing());
				ptrSession->Close();

				ptrSession->TryMarkLogic(IDataSession::REQ_CLOSED);
				PushQueueLogic(ptrSession);
			}

			//如果仍未处理完
			if (ptrSession->IsNetMarked()){
				if (ptrSession->TryMarkNet(IDataSession::REQ_NET_QUEUE))
					vProcessFail.Push(ptrSession);
			}
		}

		++uCount;
	}

	//添加到未处理队列
	_vQueueNet.Splice(vProcessFail);

	_xNetCounter.AddCount(uCount);


	//执行网络Runonce如果还有时间再执行cmd
	MapFunSessionRunOnce::const_iterator itr;
	foreach(itr,_vFunSessionRunOnce){
		FunDataSessionRunOnce	fpFun = itr->second;
		if (fpFun)
			fpFun();
	}

	return timeOut.IsTimeOut();
}

bool MProtocol::ProcessLogic( UINT64 nMillSecond )
{
	size_t uCount=0;
	size_t uPackCount=0;

	QueueSession vProcessFail;//处理失败的队列

	CTimeOut timeOut(nMillSecond);

	//循环取出队列头的会话
	while(!timeOut.IsTimeOut()){
		DataSessionPtr ptrSession = _vQueueLogic.PopFrontPtr();
		if (!ptrSession)break;

		CLockScoped lockScoped(ptrSession->GetMutex(),true);
		if (!lockScoped.IsLocked())
		{
			vProcessFail.Push(ptrSession);
			continue;
		}

		if (ptrSession->TryClearLogic(IDataSession::REQ_LOGIC_QUEUE)){
			if (ptrSession->TryClearLogic(IDataSession::REQ_CONNECTED)){
				ASSERT_LOG_ERROR(ptrSession->SetConnected(true));
				if (ptrSession->GetReceiver()){

					//回调
					ASSERT_LOG_ERROR(ptrSession->GetReceiver()->OnConnected(ptrSession->GetClientID()));
				}

				//连接成功后请求接收数据
				if (!ptrSession->IsClosing()){
					ptrSession->TryMarkNet(IDataSession::REQ_RECV);
					PushQueueNet(ptrSession);
				}
			}
			//接收
			if (ptrSession->IsConnected() && ptrSession->IsCallBackRecv() && ptrSession->GetReceiver() && ptrSession->TryClearLogic(IDataSession::REQ_RECVED)){
				
				//回调
				if (ptrSession->SwapRecvBuffer())
				{
					StreamBinaryPtr ptrBuffer = ptrSession->GetRecvedBuffer();
					ASSERT_LOG_ERROR(ptrBuffer);
					ASSERT_LOG_ERROR(ptrBuffer->GetLength());
					
					_xRecvCount.AddCount(ptrBuffer->GetLength());
					uPackCount += ptrSession->GetReceiver()->OnRecv(ptrSession.get());
					ptrSession->ClearRecvedBuffer();

					//延迟接收
					if (ptrSession->IsDelayRecv())
					{
						//将剩余数据写入接收中缓冲区
						if (!ptrSession->RecvDataSplice(ptrBuffer, false))
						{
							LOG_NET_ERR("ClientID:" << ptrSession->GetClientID() << " SendBuffFull!");
							ReqClosing(ptrSession, NET_ERRCODE_REQ_SEND_BUFF_FULL);
						}
						else {
							ptrSession->ClearDelayRecv();
							ptrSession->TryMarkLogic(IDataSession::REQ_RECVED);
						}
					}
				}
			}

			if (ptrSession->TryClearLogic(IDataSession::REQ_CLOSED)) {
				ASSERT_LOG_ERROR(ptrSession->IsClosing());
				if (!ptrSession->IsConnected())
				{
					if (ptrSession->GetReceiver())
					{
						//回调
						ASSERT_LOG_ERROR(ptrSession->GetReceiver()->OnConnectFailed(ptrSession->GetClientID()));
					}
				}
				else {
					ptrSession->SetConnected(false);
					if (ptrSession->GetReceiver())
					{
						//回调
						ASSERT_LOG_ERROR(ptrSession->GetReceiver()->OnDisconnected(ptrSession->GetClientID()));
					}
				}

				ASSERT_LOG_ERROR(ptrSession->SetClosed(true));
				ASSERT_LOG_ERROR(RemoveSession(ptrSession->GetClientID()));
			}

			if (ptrSession->IsLogicMarked()){
				if (ptrSession->TryMarkLogic(IDataSession::REQ_LOGIC_QUEUE))
					vProcessFail.Push(ptrSession);
			}
		}
		++uCount;
	}

	//将需要继续处理的压入队列
	_vQueueLogic.Splice(vProcessFail);

	_xLogicCounter.AddCount(uCount);
	_xPackCounter.AddCount(uPackCount);
	return timeOut.IsTimeOut();
}

bool MProtocol::ReqClosing(DataSessionPtr ptr, int nErrCode, bool bCallBack, bool bCallBackRecv)
{
	ASSERT_LOG_ERROR(ptr);

	CLockScoped lockScoped(ptr->GetMutex());

	//调整是否需要回调
	if (!bCallBack)
		ptr->SetReceiver(nullptr);

	if (!bCallBackRecv)
		ptr->SetCallBackRecv(false);

	if (!ptr->TryClosing())return false;

	LOG_NET_DEBUG("ReqClosing ClientID" << ptr->GetClientID() <<" ErrCode:"<< nErrCode);
	
	ptr->SetErrCode(nErrCode);
	ptr->TryMarkNet(IDataSession::REQ_CLOSE);
	PushQueueNet(ptr);
	return true;
}

bool MProtocol::OnConnected( DataSessionPtr ptr )
{
	ASSERT_LOG_ERROR(ptr);

	CLockScoped lockScoped(ptr->GetMutex());
	if (ptr->IsClosing())return false;
	ptr->TryMarkLogic(IDataSession::REQ_CONNECTED);
	PushQueueLogic(ptr);
	return true;
}

bool MProtocol::OnRecved( DataSessionPtr ptr )
{
	ASSERT_LOG_ERROR(ptr);

	CLockScoped lockScoped(ptr->GetMutex());
	if (ptr->IsClosing())return false;
	ptr->TryMarkLogic(IDataSession::REQ_RECVED);
	PushQueueLogic(ptr);
	return true;
}

bool MProtocol::CreateServer(IDataReceiver* pReceiver, const VectorString& vAddress, ELinkType eLinkType, size_t uRecvSize/*= 0xFFFF*/, size_t uSendSize/*= 0xFFFF*/, size_t uBlockSize /*= 0xFFFF*/)
{
	if (!pReceiver)return false;
	if (vAddress.empty())return false;
	if (uBlockSize <= 0)return false;
	
	bool bSucceed = true;
	VectorString::const_iterator itr;
	foreach(itr, vAddress) {
		const std::string& sAddress = *itr;
		bSucceed &= CreateServer(pReceiver, sAddress, eLinkType, uRecvSize, uSendSize, uBlockSize);
	}

	return bSucceed;
}

bool MProtocol::CreateServer(IDataReceiver* pReceiver, const std::string& sAddress, ELinkType eLinkType, size_t uRecvSize/*= 0xFFFF*/, size_t uSendSize/*= 0xFFFF*/, size_t uBlockSize /*= 0xFFFF*/)
{
	if (!pReceiver)return false;
	if (sAddress.empty())return false;
	if (uBlockSize <= 0)return false;

	//检查启动
	if (!_bStartUp)
		StartUp();

	XAcceptorKey key;
	key.nLinkType = eLinkType;
	key.sAddress = sAddress;

	if (_vAcceptor.IsHasKey(key))return false;

	CLockWrite lock(_vAcceptor.GetMutex());

	if (ToolFrame::IsHasKey(_vAcceptor.GetMap(), key))return false;

	//初始化接受器
	DataAcceptorPtr ptr = CreateAcceptor(eLinkType);
	if (!ptr)return false;
	ASSERT_LOG_ERROR(ptr);
	ptr->SetReceiver(pReceiver);
	ptr->SetAddress(sAddress);
	ptr->SetAccepterKey(key);
	ptr->InitBuffSize(uRecvSize, uSendSize, uBlockSize);

	if (!ptr->WaitAccept(sAddress))return false;

	ASSERT_LOG_ERROR(ToolFrame::Insert(_vAcceptor.GetMap(), key, ptr));
	return true;
}

bool MProtocol::CreateServer(IDataReceiver* pReceiver, uint uPort, ELinkType eLinkType, size_t uRecvSize/*= 0xFFFF*/, size_t uSendSize/*= 0xFFFF*/, size_t uBlockSize /*= 0xFFFF*/)
{
	return CreateServer(pReceiver, MAKE_STRING(uPort), eLinkType, uRecvSize, uSendSize, uBlockSize);
}

bool MProtocol::CloseServer( const std::string& sAddress,ELinkType eLinkType )
{
	XAcceptorKey key;
	key.nLinkType = eLinkType;
	key.sAddress = sAddress;

	DataAcceptorPtr ptr = _vAcceptor.GetPtrValueByKey(key);
	if (!ptr)return false;

	ASSERT_LOG_ERROR(ptr->ReqClose());

	return _vAcceptor.EraseByKey(key);
}

bool MProtocol::CloseServer( int nPort ,ELinkType eLinkType)
{
	return CloseServer(MAKE_STRING(nPort),eLinkType);
}

DataAcceptorPtr MProtocol::GetDataAcceptor( const std::string& sAddress,int eLinkType )
{
	XAcceptorKey key;
	key.nLinkType = eLinkType;
	key.sAddress = sAddress;

	return _vAcceptor.GetPtrValueByKey(key);
}

bool MProtocol::RecvDataSplice(UINT uClientID, StreamBinaryPtr pBuffer, bool bBack/*=true*/)
{
	if (INVALID_ID == uClientID)return false;
	if (!pBuffer)return false;
	if (pBuffer->IsEmpty())return false;

	DataSessionPtr ptr = GetSession(uClientID);
	ASSERT_LOG_ERROR(ptr);
	if (!ptr)return false;

	return ptr->RecvDataSplice(pBuffer, bBack);
}

bool MProtocol::StartUp()
{
	if (_bStartUp)return false;

	MapFunSessionInit::const_iterator itr;
	foreach(itr, _vFunSessionInit) {
		FunDataSessionInit fpFun = itr->second;
		if (fpFun)
			fpFun();
	}
	_bStartUp = true;
	return true;
}

bool MProtocol::ShutDown()
{
	if (!_vAcceptor.Empty() || !_vSession.Empty())return false;

	StopThread();
	return true;
}

bool MProtocol::AddNetTaskThread( uint uCount,uint uTimeInterval )
{
	StartThread(-1,uCount,uTimeInterval);
	return true;
}

bool MProtocol::InitThread()
{
	return true;
}

bool MProtocol::RunOnceThread()
{
	ProcessNet(100);
	return true;
}

int MProtocol::GetLinkType( UINT uClientID )const
{
	DataSessionPtr ptr = GetSession(uClientID);
	if (!ptr)return INVALID_ID;
	
	return ptr->GetLinkType();
}

bool MProtocol::BroadCast( const std::string& sPort,ELinkType eLinkType, StreamBinaryPtr ptr )
{
	return BroadCast(sPort, eLinkType,ptr->MoveToStreamBuffer());
}

bool MProtocol::BroadCast( const std::string& sPort,ELinkType eLinkType,const void* pMsg,size_t uLen )
{
	StreamBufferMallocPtr pBuffer(new CStreamBufferMalloc(pMsg,uLen,uLen));
	return BroadCast(sPort,eLinkType,pBuffer);
}

bool MProtocol::BroadCast(const std::string& sPort, ELinkType eLinkType, StreamBufferPtr ptr)
{
	if (!ptr)return false;
	if (ptr->IsEmpty())return false;
	
	FunBroadCast fnBroadCast = ToolFrame::GetPtrValueByKey(_vFunBroadCast, eLinkType);
	if (!fnBroadCast)
		return false;

	return fnBroadCast(sPort, ptr);
}

size_t MProtocol::GetSessionNum()const
{
	return _vSession.Size();
}

std::string MProtocol::GetRemoteAddress( uint uClientID ) const
{
	if (INVALID_ID == uClientID)return "";
	DataSessionPtr ptr = GetSession(uClientID);
	if (!ptr)return "";

	return ptr->GetRemoteAddress();
}

int MProtocol::GetErrCode( uint uClientID ) const
{
	if (INVALID_ID == uClientID)return INVALID_ID;
	DataSessionPtr ptr = GetSession(uClientID);
	if (!ptr)return INVALID_ID;

	return ptr->GetErrCode();
}

bool MProtocol::MarkDelayRecv(uint uClientID)
{
	if (INVALID_ID == uClientID)return false;
	DataSessionPtr ptr = GetSession(uClientID);
	if (!ptr)return false;

	ptr->MarkDelayRecv();
	return true;
}

StreamBinaryPtr MProtocol::GetSendData( uint uClientID ) const
{
	if (INVALID_ID == uClientID)return StreamBinaryPtr();
	DataSessionPtr ptr = GetSession(uClientID);
	if (!ptr)return StreamBinaryPtr();

	return ptr->GetSendData();
}

size_t MProtocol::GetLogicQueueSize() const
{
	return _vQueueLogic.Size();
}

size_t MProtocol::GetNetQueueSize() const
{
	return _vQueueNet.Size();
}

size_t MProtocol::ClearNetCounter()
{
	return _xNetCounter.ClearCounter();
}

size_t MProtocol::ClearLogicCounter()
{
	return _xLogicCounter.ClearCounter();
}

size_t MProtocol::GetNetCounter() const
{
	return _xNetCounter.GetCount();
}

size_t MProtocol::GetLogicCounter()const
{
	return _xLogicCounter.GetCount();
}

size_t MProtocol::GetPackCounter() const
{
	return _xPackCounter.GetCount();
}

size_t MProtocol::ClearPackCounter()
{
	return _xPackCounter.ClearCounter();
}
size_t MProtocol::GetSendCount() const
{
	return _xSendCount.GetCount();
}

size_t MProtocol::ClearSendCounter()
{
	return _xSendCount.ClearCounter();
}

size_t MProtocol::GetRecvCount() const
{
	return _xRecvCount.GetCount();
}


size_t MProtocol::ClearRecvCounter()
{
	return _xRecvCount.ClearCounter();
}

int64 MProtocol::ClearFreeTime( uint uClientID )
{
	DataSessionPtr ptr = GetSession(uClientID);
	if (!ptr)return -1;

	return ptr->ClearFreeTime();
}

bool MProtocol::IsCreatedServer( uint uPort,ELinkType eLinkType ) const
{
	return IsCreatedServer(MAKE_STRING(uPort),eLinkType);
}

bool MProtocol::IsCreatedServer( const std::string& sAddress,ELinkType eLinkType ) const
{
	XAcceptorKey key;
	key.nLinkType = eLinkType;
	key.sAddress = sAddress;

	return _vAcceptor.IsHasKey(key);
}

bool MProtocol::ProcessBalance(uint64 uProcessTime /*= 0*/, uint64 uNetResloved)
{
	//我们应该使得服务器处理 逻辑 和 网络 趋向于平衡。有必要时 应该 更趋向于 网络.
	//我们设置 总处理时间数。然后我们按照 之前获得的 逻辑 和 网络数 进行配比
	//网络部分 由于 底层需要Poll所以无论如何都得执行.另外 不得传0进入，因为那是无限时间 我们要均衡 就不可以传
	//为了能够使得协议更快的被处理 完成,所以 应该 先执行 网络 然后 执行 逻辑 然后再执行网络 至少这样才算一次 完整循环
	bool bTimeOut = false;
	if (0 == uProcessTime)
	{
		bTimeOut |= ProcessNet(uProcessTime);
		bTimeOut |= ProcessLogic(uProcessTime);
		bTimeOut |= ProcessNet(uProcessTime);
		return bTimeOut;
	}

	//修正 uNetResloved 的值(网络保留时间)
	if (uNetResloved<=0)
		uNetResloved = uProcessTime;

	size_t uCountNet	= _vQueueNet.Size();
	size_t uCountLogic	= _vQueueLogic.Size();

	size_t uCountTotal	= uCountLogic + uCountNet;

	if (0 == uCountTotal){
		uint64 uProcessTimeLogic = uProcessTime / 3;
		uint64 uProcessTimeNet	 = uProcessTimeLogic + uNetResloved/2;
		bTimeOut |= ProcessNet(uProcessTimeNet);
		bTimeOut |= ProcessLogic(uProcessTimeLogic);
		bTimeOut |= ProcessNet(uProcessTimeNet);
		return bTimeOut;
	}

	uint64 uProcessTimeNet	= (uProcessTime * uCountNet/uCountTotal + uNetResloved)/2;
	uint64 uProcessTimeLogic= uProcessTime * uCountLogic/uCountTotal;

	bTimeOut |= ProcessNet(uProcessTimeNet);

	if (uProcessTimeLogic>0)
		 bTimeOut |= ProcessLogic(uProcessTimeLogic);

	bTimeOut |= ProcessNet(uProcessTimeNet);
	return bTimeOut;
}

bool MProtocol::PushQueueNet( DataSessionPtr ptr)
{
	if(!ptr)return false;
	if (!ptr->TryMarkNet(IDataSession::REQ_NET_QUEUE))return false;
	return _vQueueNet.Push(ptr);
}

bool MProtocol::PushQueueLogic( DataSessionPtr ptr )
{
	if(!ptr)return false;

	if (!ptr->TryMarkLogic(IDataSession::REQ_LOGIC_QUEUE))return false;
	return _vQueueLogic.Push(ptr);
}

bool MProtocol::InsertFunSessionCreator( ELinkType eLinkType,FunDataSessionCreator fn )
{
	return ToolFrame::Insert(_vFunSessionCreator,eLinkType,fn);
}

bool MProtocol::InsertFunAcceptorCreator( ELinkType eLinkType,FunDataAcceptorCreator fn )
{
	return ToolFrame::Insert(_vFunAcceptorCreator,eLinkType,fn);
}

bool MProtocol::InsertFunSessionInit( ELinkType eLinkType,FunDataSessionInit fn )
{
	return ToolFrame::Insert(_vFunSessionInit,eLinkType,fn);
}

bool MProtocol::InsertFunSessionRunOnce( ELinkType eLinkType,FunDataSessionRunOnce fn )
{
	return ToolFrame::Insert(_vFunSessionRunOnce,eLinkType,fn);
}

bool MProtocol::InsertFunBroadCast( ELinkType eLinkType,FunBroadCast fn )
{
	return ToolFrame::Insert(_vFunBroadCast,eLinkType,fn);
}

UINT MProtocol::PushConnect(IDataReceiver* pReceiver, const VectorString& vAddress, ELinkType eLinkType, size_t uRecvSize, size_t uSendSize, size_t uBlockSize)
{
	if (!pReceiver)return INVALID_ID;
	if (vAddress.empty())return INVALID_ID;
	if (uBlockSize <= 0)return INVALID_ID;

	//检查启动
	if (!_bStartUp)
		StartUp();

	DataSessionPtr ptr = CreateSession(eLinkType);
	if (!ptr)return INVALID_ID;

	ptr->SetReceiver(pReceiver);
	ptr->InitBuffSize(uRecvSize, uSendSize, uBlockSize);
	ptr->SetAddress(vAddress);

	if (!AddSession(ptr))return INVALID_ID;

	//此处上锁 保证 返回之后 才会回调OnConnected
	CLockScoped lock(ptr->GetMutex());
	ptr->TryMarkNet(IDataSession::REQ_CONNECT);
	PushQueueNet(ptr);
	return ptr->GetClientID();
}

DataAcceptorPtr MProtocol::CreateAcceptor(ELinkType eLinkType)
{
	FunDataAcceptorCreator fn = ToolFrame::GetPtrValueByKey(_vFunAcceptorCreator,eLinkType);
	if (!fn)return DataAcceptorPtr();

	return fn();
}

const std::string& MProtocol::GetConnectedAddress(uint uClientID) const
{
	if (INVALID_ID == uClientID)return ToolFrame::EmptyString();
	DataSessionPtr ptr = GetSession(uClientID);
	if (!ptr)return ToolFrame::EmptyString();

	return ptr->GetConnectedAddress();
}

bool MProtocol::TimeElapsedSend( uint64 uTime )
{
	return _xSendAvg.AddCount(uTime);
}

bool MProtocol::TimeElapsedSending( uint64 uTime )
{
	return _xSendingAvg.AddCount(uTime);
}

bool MProtocol::TryAddConnect(const XAcceptorKey& key)
{
	//判断是否达到最大连接数
	if (_vConnect.Empty())return true;

	//判断是否超过限制
	{
		CLockRead lock(_vConnect.GetMutex());
		const XAcceptorConnect* pAcceptor = ToolFrame::GetValuePtrByKey(_vConnect.GetMap(), key);
		if (!pAcceptor)return true;
		if (pAcceptor->nCountMax <= 0)return true;

		if (pAcceptor->nCount >= pAcceptor->nCountMax)
			return false;
	}

	//增加1
	{
		CLockWrite lock(_vConnect.GetMutex());
		XAcceptorConnect* pAcceptor = ToolFrame::GetValuePtrByKey(_vConnect.GetMap(), key);
		if (!pAcceptor)return true;
		if (pAcceptor->nCountMax <= 0)return true;
		if (pAcceptor->nCount >= pAcceptor->nCountMax)
			return false;

		++(pAcceptor->nCount);
	}

	return true;
}

bool MProtocol::TryRemoveConnect(const XAcceptorKey& key)
{
	//然后最大连接数减少1
	if (_vConnect.Empty())return true;

	//判断是否为必要
	{
		CLockRead lock(_vConnect.GetMutex());
		const XAcceptorConnect* pAcceptor = ToolFrame::GetValuePtrByKey(_vConnect.GetMap(), key);
		if (!pAcceptor)return true;
		if (pAcceptor->nCountMax <= 0)return true;
	}

	//减少1
	{
		CLockWrite lock(_vConnect.GetMutex());
		XAcceptorConnect* pAcceptor = ToolFrame::GetValuePtrByKey(_vConnect.GetMap(), key);
		if (!pAcceptor)return true;
		if (pAcceptor->nCountMax <= 0)return true;

		--(pAcceptor->nCount);
	}
	
	return true;
}

uint MProtocol::GetConnectMax(const std::string& sAddress, ELinkType eLinkType) const
{
	XAcceptorKey key;
	key.nLinkType = eLinkType;
	key.sAddress = sAddress;

	CLockRead lock(_vConnect.GetMutex());
	const XAcceptorConnect* pAcceptor = ToolFrame::GetValuePtrByKey(_vConnect.GetMap(), key);
	if (!pAcceptor)return 0;
	return pAcceptor->nCountMax;
}

bool MProtocol::SetConnectMax(const std::string& sAddress, ELinkType eLinkType, uint uConnectMax)
{
	XAcceptorKey key;
	key.nLinkType = eLinkType;
	key.sAddress = sAddress;

	//初始化最大连接数
	XAcceptorConnect xConnect;
	xConnect.key = key;
	xConnect.nCount = 0;
	xConnect.nCountMax = uConnectMax;
	return _vConnect.Insert(key, xConnect);
}

bool MProtocol::SetConnectMax(uint uPort, ELinkType eLinkType, uint uConnectMax)
{
	return SetConnectMax(MAKE_STRING(uPort), eLinkType, uConnectMax);
}

bool MProtocol::RemoveConnectMax(const std::string& sAddress, ELinkType eLinkType)
{
	XAcceptorKey key;
	key.nLinkType = eLinkType;
	key.sAddress = sAddress;

	return _vConnect.EraseByKey(key);
}

bool MProtocol::RemoveConnectMax(uint uPort, ELinkType eLinkType)
{
	return RemoveConnectMax(MAKE_STRING(uPort), eLinkType);
}

uint MProtocol::GetConnected(const std::string& sAddress, ELinkType eLinkType) const
{
	XAcceptorKey key;
	key.nLinkType = eLinkType;
	key.sAddress = sAddress;

	CLockRead lock(_vConnect.GetMutex());
	const XAcceptorConnect* pAcceptor = ToolFrame::GetValuePtrByKey(_vConnect.GetMap(), key);
	if (!pAcceptor)return 0;
	return pAcceptor->nCount;
}

uint MProtocol::GetTimeSendAvg(uint64* uMax, uint64* uAvg)
{
	return _xSendAvg.Clear(nullptr,nullptr,uMax,uAvg);
}

uint MProtocol::GetTimeSendingAvg( uint64* uMax,uint64* uAvg )
{
	return _xSendingAvg.Clear(nullptr,nullptr,uMax,uAvg);
}

NS_TOOL_FRAME_END
