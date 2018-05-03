#pragma once
#include "MacroServerCache.h"
#include "ISyncProcesser.h"
#include "DateTime.h"
#include "IHttpResponse.h"

NS_TOOL_FRAME_BEGIN

class IServerCache;
class HServerCache {
public:
	virtual bool OnCacheCreate(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return true; }
	virtual bool OnCacheDestory(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return true; }

	virtual bool OnCacheConnect(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return true; }			//��������(����������б� ���ر�Ҫ����)
	virtual bool OnCacheConnected(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return true; }			//���ӳɹ�(���ض�������)
	virtual bool OnCacheDisconnect(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return true; }			//�Ͽ�����(�Ƴ������б�)

	virtual bool OnCacheProcessMsg(IServerCachePtr pCache, const XTopologyID& xSrcID, const XServerArg& xServerArg, const IMsgStream& msgBase) { return false; }
	virtual bool OnCacheProcessMsg(IServerCachePtr pCache, const XTopologyID& xSrcID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer) { return false; }

	virtual bool OnCacheSave(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }

	virtual bool OnCacheKick(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }
	virtual bool OnCacheLogin(IServerCachePtr pCache, const XTopologyID& xSrcID,void* pUserData = nullptr, int nUserInt = 0) { return false; }		//��¼�ɹ�

	virtual bool OnCacheSend(IServerCachePtr pCache, const XTopologyID& xSrcID, const IMsgStream& msgBase) { return false; }
	virtual bool OnCacheSend(IServerCachePtr pCache, const XTopologyID& xSrcID, StreamBinaryPtr pBuffer) { return false; }

	virtual bool OnCacheProcessHttp(IServerCachePtr pCache, const IHttpResponse& xResponse) { return false; }

	virtual bool OnCacheOperate(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }//�Զ������
	
	//����
public:
	virtual bool OnCacheCreateErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }
	virtual bool OnCacheDestoryErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }

	virtual bool OnCacheConnectErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }			//��������(����������б� ���ر�Ҫ����)
	virtual bool OnCacheConnectedErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }			//���ӳɹ�(���ض�������)
	virtual bool OnCacheDisconnectErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }			//�Ͽ�����(�Ƴ������б�)

	virtual bool OnCacheProcessMsgErr	(IServerCachePtr pCache, const XTopologyID& xSrcID, const XServerArg& xServerArg, const IMsgStream& msgBase) { return false; }
	virtual bool OnCacheProcessMsgErr	(IServerCachePtr pCache, const XTopologyID& xSrcID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer) { return false; }

	virtual bool OnCacheSaveErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }

	virtual bool OnCacheKickErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }
	virtual bool OnCacheLoginErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }		//��¼�ɹ�

	virtual bool OnCacheSendErr(IServerCachePtr pCache, const XTopologyID& xSrcID, const IMsgStream& msgBase) { return false; }
	virtual bool OnCacheSendErr(IServerCachePtr pCache, const XTopologyID& xSrcID, StreamBinaryPtr pBuffer) { return false; }

	virtual bool OnCacheProcessHttpErr(IServerCachePtr pCache, const IHttpResponse& xResponse) { return false; }

	virtual bool OnCacheOperateErr		(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }//�Զ������
public:
	HServerCache(){}
	virtual ~HServerCache(){}
};

class HServerCacheLog
	:public HServerCache
{
public:
	virtual bool OnCacheCreateErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;
	virtual bool OnCacheDestoryErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;

	virtual bool OnCacheConnectErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;			//��������(����������б� ���ر�Ҫ����)
	virtual bool OnCacheConnectedErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;			//���ӳɹ�(���ض�������)
	virtual bool OnCacheDisconnectErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;			//�Ͽ�����(�Ƴ������б�)

	virtual bool OnCacheProcessMsgErr(IServerCachePtr pCache, const XTopologyID& xSrcID, const XServerArg& xServerArg, const IMsgStream& msgBase)override;
	virtual bool OnCacheProcessMsgErr(IServerCachePtr pCache, const XTopologyID& xSrcID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer)override;

	virtual bool OnCacheSaveErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;

	virtual bool OnCacheKickErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;
	virtual bool OnCacheLoginErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;		//��¼�ɹ�

	virtual bool OnCacheSendErr(IServerCachePtr pCache, const XTopologyID& xSrcID, const IMsgStream& msgBase)override;
	virtual bool OnCacheSendErr(IServerCachePtr pCache, const XTopologyID& xSrcID, StreamBinaryPtr pBuffer)override;

	virtual bool OnCacheProcessHttpErr(IServerCachePtr pCache, const IHttpResponse& xResponse)override;

	virtual bool OnCacheOperateErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;//�Զ������
public:
	HServerCacheLog() {}
	virtual ~HServerCacheLog() {}
};

class IServerCache
	:public ISyncProcesser
	,public HServerCacheLog
{
public:
	virtual bool					SetCacheID(uint uCacheID);
	virtual bool					SetCacheHandler(HServerCache* hHandler);

	virtual uint					GetCacheID()const;
	virtual IServerCachePtr			GetCachePtr();

	virtual bool					SetSingle(bool bSingle);		//�����¼(Ĭ�� true)
	virtual bool					IsSingle()const;				//�Ƿ��ǵ����¼

	virtual const VectorTopologyID&	GetTopologyID()const;
	virtual bool					AddTopologyID(const XTopologyID& xTopologyID);
	virtual bool					RemoveTopologyID(const XTopologyID& xTopologyID);
	virtual bool					ClearTopologyID();				//��������ID��Ч
	virtual bool					IsTopologyIDEmpty()const;		//����ID�Ƿ���Ч
	virtual bool					IsHasTopologyID(const XTopologyID& xTopologyID)const;		//�Ƿ��������ID
	virtual const XTopologyID&		GetTopologyIDSingle()const;					//��ȡΨһ������ID
	
	virtual bool					MarkUpdated();	//����и���
	virtual const CDateTime&		GetTimeUpdate()const;

	virtual bool					MarkSaved();//��Ǵ洢��
	virtual const CDateTime&		GetTimeSave()const;
public:
	virtual bool SyncCreate(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool SyncDestory(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);

	virtual bool SyncConnect(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);			//��������(����������б� ���ر�Ҫ����)
	virtual bool SyncConnected(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);			//���ӳɹ�(���ض�������)
	virtual bool SyncDisconnect(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);			//�Ͽ�����(�Ƴ������б�)

	virtual bool SyncProcessMsg(const XTopologyID& xSrcID,  const XServerArg& xServerArg, const IMsgStream& msgBase);
	virtual bool SyncProcessMsg(const XTopologyID& xSrcID,  const XServerArg& xServerArg, StreamBinaryPtr pBuffer);

	virtual bool SyncSave(const XTopologyID& xSrcID,  void* pUserData = nullptr, int nUserInt = 0);

	virtual bool SyncKick (const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool SyncLogin(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);		//��¼�ɹ�

	virtual bool SyncSend(const XTopologyID& xSrcID, const IMsgStream& msgBase);
	virtual bool SyncSend(const XTopologyID& xSrcID, StreamBinaryPtr pBuffer);

	virtual bool SyncProcessHttp(const IHttpResponse& xResponse);	//����Http

	virtual bool SyncOperate(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);//�Զ������
public:
	virtual bool OnCreate(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool OnCacheDestory(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);

	virtual bool OnCacheConnect(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);			//��������(����������б� ���ر�Ҫ����)
	virtual bool OnCacheConnected(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);			//���ӳɹ�(���ض�������)
	virtual bool OnCacheDisconnect(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);			//�Ͽ�����(�Ƴ������б�)

	virtual bool OnCacheProcessMsg(const XTopologyID& xSrcID, const XServerArg& xServerArg, const IMsgStream& msgBase);
	virtual bool OnCacheProcessMsg(const XTopologyID& xSrcID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer);

	virtual bool OnCacheSave(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);

	virtual bool OnCacheKick(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool OnCacheLogin(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);		//��¼�ɹ�

	virtual bool OnCacheSend(const XTopologyID& xSrcID, const IMsgStream& msgBase);
	virtual bool OnCacheSend(const XTopologyID& xSrcID, StreamBinaryPtr pBuffer);

	virtual bool OnCacheProcessHttp(const IHttpResponse& xResponse);	//����Http

	virtual bool OnCacheOperate(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);//�Զ������
public:
	IServerCache();
	virtual ~IServerCache();
private:
	HServerCache* _hCacheHandler;

	bool			_bSingle;		//�����¼
	CDateTime		_tTimeUpdate;	//�������ʱ��
	CDateTime		_tTimeSave;		//�������ʱ��

	VectorTopologyID _vTopologyID;	//����ID
};

NS_TOOL_FRAME_END
