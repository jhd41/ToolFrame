#include "IMsgStreamSpliter.h"

#include "IMsgStream.h"
#include "MLoger.h"
#include "MProtocol.h"

NS_TOOL_FRAME_BEGIN

IMsgStreamSpliter::IMsgStreamSpliter(void)
{
}

IMsgStreamSpliter::~IMsgStreamSpliter(void)
{
}

uint IMsgStreamSpliter::SpliteMsgStream(IDataSession* pSession)
{
	ASSERT_LOG_ERROR(pSession);
  	uint uCount = 0;

	StreamBinaryPtr pBufRecv = pSession->GetRecvedBuffer();
	ASSERT_LOG_ERROR(pBufRecv);
	
  	//流读取
  	while (!pBufRecv->IsEmpty()) {
  
		//需要跳转的长度
		size_t uSkipLength = 0;

		//进入单包解析 这个花括号不能删除 因为 IMsgStream 析构时 会还原 对 BufRev的操作
		{
			//进入单包解析
			IMsgStream msgStream(pBufRecv);

			//加载消息头
			if (!msgStream.LoadBegin())
			{
				ASSERT_LOG_ERROR(msgStream.ResetLoadStream());
				if (!pSession->RecvDataSplice(pBufRecv, false))
				{
					LOG_NET_ERR("ClientID:" << pSession->GetClientID() << " OnRecv: Err:" << NET_ERRCODE_REQ_RECV_BUFF_FULL);
					MProtocol::Singleton().Disconnect(pSession->GetClientID(), true, NET_ERRCODE_REQ_RECV_BUFF_FULL);
					return uCount;
				}
				return uCount;
			}

			//校验头的有效性
			if (!msgStream.IsVaildBegin())
			{
				LOG_NET_ERR("ClientID:" << pSession->GetClientID() << "无效包 断开连接");
				MProtocol::Singleton().Disconnect(pSession->GetClientID(), true, NET_ERRCODE_VAILD_PACK);
				return uCount;
			}

			//如果协议未接收完
			if (msgStream.GetLength() > pBufRecv->GetLength() + IMsgStream::GetBeginLength())
			{
				//如果包长超过缓冲区大小
				if (msgStream.GetLength() > pBufRecv->GetMaxSize())
				{
					LOG_NET_ERR("ClientID:" << pSession->GetClientID() <<" OpCode:"<< msgStream.GetOpCode()<< " 长度超过包极限,关闭连接");
					MProtocol::Singleton().Disconnect(pSession->GetClientID(), true, NET_ERRCODE_LENGTH_LIMIT);
					return uCount;
				}

				LOG_NET_DEBUG("ClientID:" << pSession->GetClientID() << "协议未接收完 长度:"<< msgStream.GetLength() << " OpCode:" << msgStream.GetOpCode() <<" 缓冲池剩余:"<< pBufRecv->GetLength());
				ASSERT_LOG_ERROR(msgStream.ResetLoadStream());
				if (!pSession->RecvDataSplice(pBufRecv, false))
				{
					LOG_NET_ERR("ClientID:" << pSession->GetClientID() << " OnRecv: Err:" << NET_ERRCODE_REQ_RECV_BUFF_FULL);
					MProtocol::Singleton().Disconnect(pSession->GetClientID(), true, NET_ERRCODE_REQ_RECV_BUFF_FULL);
					return uCount;
				}
				return uCount;
			}

			//记录包
			LOG_NET_DEBUG("ClientID:" << pSession->GetClientID() << " Len:" << msgStream.GetLength() << " OpCode:" << msgStream.GetOpCode());

			//回调
			if (!OnRecv(pSession, msgStream)) {
				LOG_NET_ERR("ClientID:" << pSession->GetClientID() << " 上层逻辑消息处理失败,关闭连接");
				MProtocol::Singleton().Disconnect(pSession->GetClientID(), true, NET_ERRCODE_RECVED_ERR);
				return uCount;
			}

			//延迟接收
			if (pSession->IsDelayRecv())
			{
				//恢复到读取之前的状态
				ASSERT_LOG_ERROR(msgStream.ResetLoadStream());
				return uCount;
			}

			//增加包数
			++uCount;

			//设置跳过的长度
			uSkipLength = msgStream.GetLength();
		}

  		//跳过已经解析的部分
  		ASSERT_LOG_ERROR(pBufRecv->Skip(uSkipLength));
  	}
 
 	return uCount;
}

bool IMsgStreamSpliter::OnRecv(IDataSession* pSession, IMsgStream& msgStream)
{
	ASSERT_LOG_ERROR(pSession);
	return OnRecv(pSession->GetClientID(), msgStream);
}

bool IMsgStreamSpliter::OnRecv(uint uClientID, IMsgStream& msgStream)
{
	return true;
}

NS_TOOL_FRAME_END

