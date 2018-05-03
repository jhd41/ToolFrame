#pragma once

#include "IServer.h"
#include "TopologyLogic.h"
#include "IThreadTask.h"
#include "HLog.h"
#include "HSystem.h"
#include "ServerCacheManager.h"
#include "UrlRequestTopology.h"

NS_TOOL_FRAME_BEGIN

class IServerLogic
	:public IServer
	,public HTopologyLogic
	,public HLog
	,public HSystem
	,public HServerCacheLog
	,public HUrlRequest
{
public:
	virtual bool Init();	//��ʼ��
public:
	virtual int		GetServerID()const;
	virtual int		GetServerType()const;
	virtual bool	SetStateNormal();
	virtual bool	SetStateStop();
	virtual bool	SetCacheVaild(size_t uCacheVaild);
	virtual bool	SetCacheTotal(size_t uCacheTotal);
	virtual bool	SetProcesserCount(size_t uCacheTotal);
	virtual bool	SetQueueSize(size_t uQueueSize);//���ö��г���
	virtual bool	SetQueueProcess(size_t uQueueProcess );//���ö��д�����
	virtual bool	SetDebugReport(bool bReport);
	virtual bool	IsDebugReport()const;
	virtual bool	IsInited()const;
	virtual bool	SetInited(bool bInited);
	
	virtual CServerCacheManager&		GetCacheManager();
	virtual const CServerCacheManager&	GetCacheManager()const;
public:
	virtual uint	FindServerID(uint uClientID)const;
	virtual uint	FindClientID(uint uServerID)const;									//�Ҹ�ClientID

	virtual uint	SendClientID(uint uClientID,const IMsgStream& msg,const XTopologyID& uID,uint32 uUserID)const;
	virtual uint	SendClientID(uint uClientID,const IMsgStream& msg,const XTopologyID& uID)const;
	virtual uint	SendClientID(uint uClientID,const IMsgStream& msg)const;

	virtual uint	SendClientID(uint uClientID,StreamBinaryPtr ptr,const XTopologyID& uID,uint32 uUserID)const;

	virtual uint	SendSrvID(int nServerID,const IMsgStream& msg,const XTopologyID& uID = TOPOLOGY_ID_INVAILD)const;//���͸�ָ�������� ���� ClientID
	virtual uint	SendSrvID(int nServerID, StreamBinaryPtr ptr,const XTopologyID& uID = TOPOLOGY_ID_INVAILD)const;
	virtual uint	SendSrvID(int nServerID,const IMsgStream& msg,const XTopologyID& uID,uint32 uUserID)const;
	virtual uint	SendSrvID(int nServerID, StreamBinaryPtr ptr,const XTopologyID& uID,uint32 uUserID)const;

	virtual uint	SendSrvID(const XTopologyID& xSrcID, StreamBinaryPtr ptr,uint32 uUserID)const;
	virtual uint	SendSrvID(const XTopologyID& xSrcID, StreamBinaryPtr ptr)const;
	virtual uint	SendSrvID(const XTopologyID& xSrcID,const IMsgStream& msg,uint32 uUserID)const;
	virtual uint	SendSrvID(const XTopologyID& xSrcID,const IMsgStream& msg)const;

	//�Ը��ݷ���������������Ѱ�Һ��ʵķ��ͷ�ʽ���з���
	virtual uint	SendSrvType(int eSrvType, const IMsgStream& msg)const;										//����ClientID
	virtual uint	SendSrvType(int eSrvType, const XTopologyID& xSrcID, const IMsgStream& msg)const;				//����ClientID
	virtual uint	SendSrvType(int eSrvType, const XTopologyID& xSrcID, const IMsgStream& msg, uint uUserID)const;//����ClientID

	//������ķ�ʽ���з���
	virtual uint	SendRandom(int eSrvType,const IMsgStream& msg)const;										//����ClientID
	virtual uint	SendRandom(int eSrvType,const XTopologyID& xSrcID,const IMsgStream& msg)const;					//����ClientID
	virtual uint	SendRandom(int eSrvType,const XTopologyID& xSrcID,const IMsgStream& msg,uint uUserID)const;	//����ClientID
	
	//��ƽ��ķ�ʽ���з���
	virtual uint	SendBalance(int eSrvType, const IMsgStream& msg)const;										//����ClientID
	virtual uint	SendBalance(int eSrvType, const XTopologyID& xSrcID, const IMsgStream& msg)const;				//����ClientID
	virtual uint	SendBalance(int eSrvType, const XTopologyID& xSrcID, const IMsgStream& msg, uint uUserID)const;//����ClientID

	//�㲥
	virtual bool	BoardCast(int eSrvType,const IMsgStream& msg,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID=INVALID_ID)const;

	//����������
	virtual uint	SendGateWaySrv(const XTopologyID& uID, const IMsgStream& msg)const;
	virtual uint	SendGateWaySrv(const XTopologyID& uID, StreamBinaryPtr ptr)const;
	virtual bool	SendGateWaySrv(const VectorTopologyID& vTopologyID, const IMsgStream& msg)const;
	virtual bool	SendGateWaySrv(const VectorTopologyID& vTopologyID, StreamBinaryPtr ptr)const;

	//����Url����
	virtual CUrlRequestTopologyPtr	UrlRequest(const XTopologyID& xSrcID, uint uID, int eType, const std::string& sUrl, uint uSrvID = INVALID_ID);
	virtual CUrlRequestTopologyPtr	UrlRequest(const XTopologyID& xSrcID, uint uID, CUrlRequestTopologyPtr pRequest);
	virtual CUrlRequestTopologyPtr	UrlRequest(const XTopologyID& xSrcID, const std::string& sUrl);
	virtual CUrlRequestTopologyPtr	UrlRequest(const std::string& sUrl);
	//����
	virtual bool DebugReport();
protected:
	virtual bool OnFinished(IUrlRequestPtr pRequest) override;
protected:
	virtual bool OnServerAllConnected()override;
	virtual bool OnServerReport()override;
	virtual bool OnServerSave()override;
	virtual bool OnServerCleanUp()override;		//������
	virtual bool OnServerStopService()override;
	virtual bool OnServerShutDown()override;
	virtual bool OnServerRecved(const XServerArg& xServerArg, IMsgStream& msgBase)override;
	virtual std::string OnServerDebug(const VectorString& vDebug)override;//���Խ���
public:
	virtual bool OnSendFaild(int nServerID,const XTopologyID& uID, StreamBinaryPtr ptr)const;
public:
	virtual bool OnRunElasticThread()override;		//ִ�е����̣߳������Ƿ�ʱ
	virtual bool OnRunElasticThreadExtra();	//���ⲿ�� �����Ƿ�ʱ(������Ҫ�̳��������)
public:
	IServerLogic(void);
	virtual ~IServerLogic(void);
protected:
	CTopologyLogic			_xTopologyLogic;
	bool					_bInited;
	bool					_bDebugReport;
	CServerCacheManager		_mgrCache;
};

NS_TOOL_FRAME_END
