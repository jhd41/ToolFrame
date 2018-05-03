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
	
  	//����ȡ
  	while (!pBufRecv->IsEmpty()) {
  
		//��Ҫ��ת�ĳ���
		size_t uSkipLength = 0;

		//���뵥������ ��������Ų���ɾ�� ��Ϊ IMsgStream ����ʱ �ỹԭ �� BufRev�Ĳ���
		{
			//���뵥������
			IMsgStream msgStream(pBufRecv);

			//������Ϣͷ
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

			//У��ͷ����Ч��
			if (!msgStream.IsVaildBegin())
			{
				LOG_NET_ERR("ClientID:" << pSession->GetClientID() << "��Ч�� �Ͽ�����");
				MProtocol::Singleton().Disconnect(pSession->GetClientID(), true, NET_ERRCODE_VAILD_PACK);
				return uCount;
			}

			//���Э��δ������
			if (msgStream.GetLength() > pBufRecv->GetLength() + IMsgStream::GetBeginLength())
			{
				//�������������������С
				if (msgStream.GetLength() > pBufRecv->GetMaxSize())
				{
					LOG_NET_ERR("ClientID:" << pSession->GetClientID() <<" OpCode:"<< msgStream.GetOpCode()<< " ���ȳ���������,�ر�����");
					MProtocol::Singleton().Disconnect(pSession->GetClientID(), true, NET_ERRCODE_LENGTH_LIMIT);
					return uCount;
				}

				LOG_NET_DEBUG("ClientID:" << pSession->GetClientID() << "Э��δ������ ����:"<< msgStream.GetLength() << " OpCode:" << msgStream.GetOpCode() <<" �����ʣ��:"<< pBufRecv->GetLength());
				ASSERT_LOG_ERROR(msgStream.ResetLoadStream());
				if (!pSession->RecvDataSplice(pBufRecv, false))
				{
					LOG_NET_ERR("ClientID:" << pSession->GetClientID() << " OnRecv: Err:" << NET_ERRCODE_REQ_RECV_BUFF_FULL);
					MProtocol::Singleton().Disconnect(pSession->GetClientID(), true, NET_ERRCODE_REQ_RECV_BUFF_FULL);
					return uCount;
				}
				return uCount;
			}

			//��¼��
			LOG_NET_DEBUG("ClientID:" << pSession->GetClientID() << " Len:" << msgStream.GetLength() << " OpCode:" << msgStream.GetOpCode());

			//�ص�
			if (!OnRecv(pSession, msgStream)) {
				LOG_NET_ERR("ClientID:" << pSession->GetClientID() << " �ϲ��߼���Ϣ����ʧ��,�ر�����");
				MProtocol::Singleton().Disconnect(pSession->GetClientID(), true, NET_ERRCODE_RECVED_ERR);
				return uCount;
			}

			//�ӳٽ���
			if (pSession->IsDelayRecv())
			{
				//�ָ�����ȡ֮ǰ��״̬
				ASSERT_LOG_ERROR(msgStream.ResetLoadStream());
				return uCount;
			}

			//���Ӱ���
			++uCount;

			//���������ĳ���
			uSkipLength = msgStream.GetLength();
		}

  		//�����Ѿ������Ĳ���
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

