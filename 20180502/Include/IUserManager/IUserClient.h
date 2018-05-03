#pragma once

#include "Macro.h"
#include "MacroTopology.h"
#include "ISyncProcesser.h"
#include "IMsgStream.h"
#include "IUserClientResolver.h"
#include "IResolverManager.h"
#include "UrlRequestTopology.h"

NS_TOOL_FRAME_BEGIN

class IUserClient
	:public ISyncProcesser
	,public IResolverManager
{
public:
	virtual bool	SetTimeOut(uint uTimeOut);					//���ó�ʱʱ��
	virtual bool	SetRecvPack(uint uRecvMax, uint uRecvPer);	//�������ÿX����Խ���Y����
	virtual bool	SetEncryptTransmission(bool bEncrypt);		//���� ���ܴ��� Ĭ�Ͽ���
	virtual bool	Init(uint uSrvID,uint uClientID, uint uAssID);
public:
	virtual bool	IsEncryptTransmission()const;				//�Ƿ���ܴ���
	virtual uint32  MakeSecretKey();	//������Կ
	virtual uint32	GetSecretKey()const;//��ȡ��Կ
public:
	virtual bool SyncClientConnected(uint uClientID);
	virtual bool SyncClientDisconnected();
	virtual bool SyncClientRecvStream(const IMsgStream& msgStream);
	virtual bool SyncClientRecvBuffer(StreamBinaryPtr pMsgStream);
	virtual bool SyncClientUrlResponce(CUrlRequestTopologyPtr pRequest);

	virtual bool SyncServerRecved(const XServerArg& xServerArg,const IMsgStream& msgBase);

	virtual bool SyncCheck(time_t uTimeNow);
	virtual bool SyncTimeOut(const CTimeNodePtr& pTimeNode);
	virtual bool SyncDisconnected(bool bActive = true);

	virtual bool SyncSendClient(const IMsgStream& msgStream, bool bSecret = true);			//�������ͻ��ˣ����ͻ��˵��� ��Ỻ��
	virtual bool SyncSendClient(const StreamBinaryPtr ptr, bool bSecret = true);
	virtual bool SyncSendClient(const std::string& sMsg, bool bSecret = true);
	virtual bool SyncSendClient(const void* pBuffer, size_t uLen, bool bSecret = true);
public:
	virtual bool OnClientConnected(uint uClientID);
	virtual bool OnClientDisconnected();
	virtual bool OnClientRecvStream(const IMsgStream& msgStream);
	virtual bool OnClientRecvBuffer(StreamBinaryPtr pMsgStream);
	virtual bool OnClientUrlResponce(CUrlRequestTopologyPtr pRequest);

	virtual bool OnServerRecved(const XServerArg& xServerArg, const IMsgStream& msgBase);

	virtual bool OnCheck(time_t uTimeNow);
	virtual bool OnResolverTimeOut(const CTimeNodePtr& pTimeNode);

	virtual bool SendClient(const IMsgStream& msgStream, bool bSecret = true);			//�������ͻ��ˣ����ͻ��˵��� ��Ỻ��
	virtual bool SendClient(const StreamBinaryPtr ptr, bool bSecret = true);
	virtual bool SendClient(const std::string& sMsg, bool bSecret = true);
	virtual bool SendClient(const void* pBuffer, size_t uLen, bool bSecret = true);

	virtual bool Disconnect(bool bActive = true);

public:
	virtual bool	SetConnectServer(const MapIntInt& vServerConnect);
	virtual bool	AddConnectServer(int eSrvType, int nSrvID);
	virtual bool	RemoveConnectServer(int eSrvType);
	virtual int		FindConnectServer(int eSrvType);
private:
	virtual bool Send(const IMsgStream& msgStream, bool bSecret = true);
	virtual bool Send(const StreamBinaryPtr ptr, bool bSecret = true);
	virtual IUserClientResolver* FindTopUserClientResolver();
private:
	virtual bool OnResolveTimeOut(IResolverManager* pMgrResolver, const CTimeNodePtr& pTimeNode);						//���㳬ʱ(�����Ƕ��̻߳ص�)
	virtual bool OnResolveOver(IResolverManager* pMgrResolver)override;

	//����ص�
protected:
	virtual bool	OnSend(StreamBinaryPtr ptr, bool bSecret);
	virtual bool	OnEncrypt(void* pBuffer, size_t uLength);	//����
	virtual bool	OnDecrypt(void* pBuffer, size_t uLength);	//����
	virtual bool	OnEncryptFaild(void* pBuffer, size_t uLength);	//����
	virtual bool	OnDecryptFaild(void* pBuffer, size_t uLength);	//����
public:
	IUserClient();
	virtual ~IUserClient();
private:
	CFIELD_UINT(ClientID);
	CFIELD_UINT(AssID);
	CFIELD_UINT(SrvID);
	CFIELD_REF(XTopologyID, TopologyID, x);
	CFIELD_UINT(UserID);
	CFIELD_BOOL(Connected);					//����ͨ
	CFIELD_BOOL(Closed);					//�ѹر�
	CFIELD_BOOL(ActiveDisconnect);			//��������
	CFIELD_REF(MapIntInt, ServerConnect, v);	//���������ӱ�	
private:
	uint			_uTimeOut;		//��ʱʱ��
	CTimeOut		_tLastRecv;		//����ʱ��(����հ�ʱ��)
	uint			_tRecvMax;		//��ȡ������
	CTimeOut		_tRecvBegin;	//��ȡ����ʱ(�涨ʱ����ֻ����ȡX����)
	uint			_tRecvCount;	//��ȡ����
	uint32			_uSecretKey;	//��Կ
	bool			_bEncryptTransmission; //���ܴ���
};

NS_TOOL_FRAME_END
