#pragma once
#include "Macro.h"
#include "MacroTopology.h"
#include "ISyncProcesserManager.h"
#include "IMsgStream.h"
#include "IUserClient.h"
#include "IDMaker.h"
#include "HTimeOut.h"

NS_TOOL_FRAME_BEGIN

class IUserClientManager
	:protected ISyncProcesserManager
	,public HTimeOut
{
public:
	virtual bool SetCheckTime(uint uTimeOut);				//������ѯʱ��
	virtual bool SetTimeOut(uint uTimeOut);					//���ó�ʱʱ��
	virtual bool SetRecvPack(uint uRecvMax, uint uRecvPer);	//�������ÿX����Խ���Y����
	virtual bool Init();
	virtual bool SyncDisconnectAll(bool bActive = true);			//�Ͽ�����
	virtual bool SyncDisconnect(uint uAssID, bool bActive = true);	//�Ͽ�����
	virtual bool SyncServerRecved(const XServerArg& xServerArg, const IMsgStream& msgBase);
	virtual bool SyncClientConnected(uint uClientID);
	virtual bool SyncClientDisconnect(uint uClientID);
	virtual bool SyncClientRecved(uint uClientID, const IMsgStream& msgStream);
	virtual bool SyncClientRecved(uint uClientID, IDataSession* pSession);

	virtual bool SyncSendClient(uint uClientID, const IMsgStream& msgStream, bool bSecret = true);			//�������ͻ��ˣ����ͻ��˵��� ��Ỻ��
	virtual bool SyncSendClient(uint uClientID, StreamBinaryPtr ptr, bool bSecret = true);
	virtual bool SyncSendClient(uint uClientID, const std::string& sMsg, bool bSecret = true);
	virtual bool SyncSendClient(uint uClientID, const void* pBuffer, size_t uLen, bool bSecret = true);

	virtual bool SyncCalState(uint& uTotal, uint& uVaild, uint& uNormal, uint& uQueue, uint& uDelete, uint& uPerpairing, uint& uCache) const;//ͳ�ƻ����״̬(��������Ч���������� ������ ������)
public:
	virtual time_t			GetTimeOut()const;
	virtual time_t			GetCheckTime()const;
	virtual size_t			GetClientCount()const;
	virtual size_t			GetAssCount()const;
	virtual size_t			GetQueueSize()const;
	virtual bool			ProcessRetry(uint64 uMillTime);
private:
	virtual bool				OnTimeOut(const CTimeNodePtr& pTimeNode)override;
	virtual ISyncProcesserPtr	OnCreateProcesser(int nUserInt, void* pUserData)override;
	virtual bool				OnDestoryProcesser(ISyncProcesserPtr pProcesser)override;
public:
	CFIELD_UINT(SrvID);
public:
	IUserClientManager();
	virtual ~IUserClientManager();
public:
	CTimeNodePtr			_pTimerCheck;
	uint					_uCheckTime;//��ѯ ���ʱ����
	uint					_uTimeOut;	//������ʱʱ��
	uint					_uRecvMax;	//�����հ���
	uint					_uRecvPer;	//�����հ���ˢ��ʱ����

	bool					_bInit;		//��ʼ��
};

NS_TOOL_FRAME_END