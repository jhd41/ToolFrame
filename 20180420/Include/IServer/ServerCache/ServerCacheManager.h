#pragma once
#include "MacroServerCache.h"
#include "ISyncProcesserManager.h"
#include "IDMaker.h"
#include "HTimeOut.h"
#include "IServerCache.h"

NS_TOOL_FRAME_BEGIN

class CServerCacheManager
	:protected ISyncProcesserManager
	,public HTimeOut
	,public HServerCache
{
public:
	typedef ISyncProcesserManager::MapSyncProcesser			MapServerCache;
public:
	virtual bool SetManagerHandler(HSyncProcesserManager* hHandler);
	virtual bool SetCacheHandler(HServerCache* hHandler);
	virtual bool SetNeedSave(bool bSave);
	virtual bool SetAutoDelete(bool bAuto);				//�����Զ�������(Ĭ�Ϲر�)
	virtual bool SetDeleteTime(time_t uDelete = 1200);	//ɾ�������ʱ�� ��(����ָ��ʱ�� ����Ч ���Զ����� Ĭ��20����)
	virtual bool SetCheckTime(time_t uCheck = 300);		//���ʱ�� ��(Ĭ�� 5����)
	virtual bool Init();
	virtual bool Run(uint64 uMillTime);
public:
	virtual size_t	GetVaildCount()const;			//��ȡ��Ч�û�����
	virtual size_t	GetNormalCount()const;			//��ȡ�����û���
	virtual size_t	GetTotalCount()const;			//��ȡ�ܻ�����Ҹ���
	virtual size_t	GetOperateCount()const;			//��ȡ������������
	virtual size_t	ClearOperateProcess();			//�������������
	virtual bool	IsCached(uint uCacheID)const;	//�Ƿ����ָ������
public:
	virtual uint SyncCreateMakeID(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);//�Զ�����ID

	virtual bool SyncCreate(const XTopologyID& xSrcID, uint uCacheID, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool SyncCreate(const XTopologyID& xSrcID, uint uCacheID, int nUserInt);
	virtual bool SyncDestory(const XTopologyID& xSrcID, uint uCacheID, void* pUserData = nullptr, int nUserInt = 0);

	virtual bool SyncConnect(const XTopologyID& xSrcID, uint uCacheID, void* pUserData = nullptr, int nUserInt = 0);			//��������(����������б� ���ر�Ҫ����)
	virtual bool SyncConnected(const XTopologyID& xSrcID, uint uCacheID, void* pUserData = nullptr, int nUserInt = 0);			//���ӳɹ�(���ض�������)
	virtual bool SyncDisconnect(const XTopologyID& xSrcID, uint uCacheID, void* pUserData = nullptr, int nUserInt = 0);			//�Ͽ�����(�Ƴ������б�)

	virtual bool SyncProcessMsg(const XTopologyID& xSrcID, uint uCacheID, const XServerArg& xServerArg, const IMsgStream& msgBase);
	virtual bool SyncProcessMsg(const XTopologyID& xSrcID, uint uCacheID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer);

	virtual bool AsyncSave(const XTopologyID& xSrcID, uint uCacheID,void* pUserData = nullptr, int nUserInt = 0);

	virtual bool AsyncKick (const XTopologyID& xSrcID, uint uCacheID, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool AsyncLogin(const XTopologyID& xSrcID, uint uCacheID, void* pUserData = nullptr, int nUserInt = 0);		//��¼�ɹ�

	virtual bool SyncSend(const XTopologyID& xSrcID, uint uCacheID, const IMsgStream& msgBase);
	virtual bool SyncSend(const XTopologyID& xSrcID, uint uCacheID, StreamBinaryPtr pBuffer);

	virtual bool SyncUrlResponce(uint uCacheID, CUrlRequestTopologyPtr pRequest);

	virtual bool SyncOperate(const XTopologyID& xSrcID, uint uCacheID, int nUserInt = 0);//�Զ������
	virtual bool SyncOperate(const XTopologyID& xSrcID, uint uCacheID, void* pUserData, int nUserInt = 0);//�Զ������

	virtual bool SyncAllProcessMsg(const XTopologyID& xSrcID, const XServerArg& xServerArg, const IMsgStream& msgBase);
	virtual bool SyncAllProcessMsg(const XTopologyID& xSrcID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer);
	virtual bool SyncAllSave(const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool SyncAllDestory(const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool SyncAllOperate(const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, int nUserInt = 0);//�Զ������
	virtual bool SyncAllOperate(const XTopologyID& xSrcID, void* pUserData, int nUserInt = 0);	//�Զ������
	virtual bool SyncAllSend(const XTopologyID& xSrcID, StreamBinaryPtr pBuffer);
	virtual bool SyncAllSend(const XTopologyID& xSrcID, const IMsgStream& msgBase);

	virtual bool SyncCalState(uint& uTotal, uint& uVaild, uint& uNormal, uint& uQueue, uint& uDelete, uint& uPerpairing, uint& uCache, uint& uOperateQueue, uint& uDelayOperateQueue) const;//ͳ�ƻ����״̬(��������Ч���������� ������ ������)
	//�������ⲿ�����ܲ�Ҫ����
public:
	virtual IServerCachePtr		FindServerCache(uint uCacheID);

	//��������
public:
	virtual CMutexReadWrite&		GetMutex()const;
	virtual const MapServerCache&	GetServerCache()const;
private:
	virtual ISyncProcesserPtr OnCreateProcesser(int nUserInt, void* pUserData)override;
private:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode)override;
public:
	CServerCacheManager();
	virtual ~CServerCacheManager();
protected:
	CIDMakerUint			_vMakeID;

	bool					_bNeedSave;
	bool					_bAutoDelete;		//�Զ�������
	time_t					_uTimeDelete;		//ɾ�������ʱ��
	time_t					_uTimeCheck;		//���ʱ����
	CTimeNodePtr			_pTimerCheck;		//���ļ�ʱ��

	HServerCache*			_hCacheHandler;
};

NS_TOOL_FRAME_END
