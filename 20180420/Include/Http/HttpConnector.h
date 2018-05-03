#pragma once
#include "Macro.h"

#include "IHttpRequest.h"
#include "IHttpResponse.h"
#include "ConnectMonitor.h"

#include "LockMutex.h"
#include "HTimeOut.h"

NS_TOOL_FRAME_BEGIN
class CHttpConnector;
class HHttpConnector
{
public:
	virtual bool OnConnect(CHttpConnector* pConnector) { return false; }
	virtual bool OnDisconnect(CHttpConnector* pConnector) { return false; }
	virtual bool OnRequest(CHttpConnector* pConnector,const IHttpRequest& request) { return false; }
	virtual bool OnResponse(CHttpConnector* pConnector,const IHttpResponse& response) { return false; }
	virtual bool OnStateChanged(CHttpConnector* pConnector) { return false; }
public:
	virtual bool OnErrRequestNotSupport(CHttpConnector* pConnector,const::std::string& sUrl) { return false; }//������֧��
	virtual bool OnErrRequestFaild(CHttpConnector* pConnector) { return false; }
	virtual bool OnErrResponseTimeOut(CHttpConnector* pConnector) { return false; }
	virtual bool OnErrResponseParseFaild(CHttpConnector* pConnector,const std::string& sHttp) { return false; }
	virtual bool OnErrResponse(CHttpConnector* pConnector, const IHttpResponse& response) { return false; }
	virtual bool OnErrFollowMax(CHttpConnector* pConnector, const::std::string& sUrl) { return false; }
public:
	HHttpConnector() {}
	virtual ~HHttpConnector(){}
};

class HHttpConnectorLog
	:public HHttpConnector
{
public:
	virtual bool OnErrRequestNotSupport(CHttpConnector* pConnector, const::std::string& sUrl) override;//������֧��
	virtual bool OnErrRequestFaild(CHttpConnector* pConnector)override;
	virtual bool OnErrResponseTimeOut(CHttpConnector* pConnector)override;
	virtual bool OnErrResponseParseFaild(CHttpConnector* pConnector, const std::string& sHttp)override;
	virtual bool OnErrResponse(CHttpConnector* pConnector, const IHttpResponse& response)override;
	virtual bool OnErrFollowMax(CHttpConnector* pConnector, const::std::string& sUrl)override;
public:
	HHttpConnectorLog() {}
	virtual ~HHttpConnectorLog() {}
};

class CHttpConnector
	:public HConnectMonitor
	,public HHttpConnectorLog
	,public HTimeOut
{
public:
	ST_INTANCE(CHttpConnector);
public:
	enum {
		STATE_INVAILD,

		STATE_CHECK,		//���

		STATE_PERPAIRE,		//׼��
		STATE_CONNECT,		//����
		STATE_REQUEST,		//����
		STATE_RESPONSE,		//Ӧ��

		STATE_OVER,			//����

		STATE_REDIRECT,		//��ַ�л���

		STATE_STOPING,		//ֹͣ��
		STATE_STOP,			//ֹͣ

		STATE_FOLLOW,		//����

		STATE_MAX,
	};

	typedef std::list<IHttpRequest> VectorRequest;
public:
	virtual bool SetHandler(HHttpConnector* hHandler);	//���ô�����
	virtual bool SetFollowLocation(bool bFollow = true);//������ת���ҳ��
	virtual bool Init();								//��ʼ��
	virtual bool Request(const IHttpRequest& request);	//���һ������
	virtual bool IsOver()const;							//�Ƿ�������
	virtual size_t GetRequestCount()const;				//��ȡ��������
	virtual int GetState()const;						//��ȡ��ǰ״̬
	virtual const IHttpRequest* GetRequestCur()const;	//��ȡ��ǰ���ʵ�����
	virtual const std::string&	GetConnectedAddress()const;//��ȡ���ӳɹ���IP
	virtual CMutexRecursive&	GetMutex()const;		//��ȡ�ڲ�������
private:
	virtual bool OnConnected(CConnectMonitor* pConnectMonitor)override;
	virtual bool OnDisconnected(CConnectMonitor* pConnectMonitor)override;
	virtual bool OnConnectFaild(CConnectMonitor* pConnectMonitor) override { return true; }
	virtual uint OnRecved(CConnectMonitor* pConnectMonitor, IDataSession* pSession)override;
	virtual bool OnStateChanged(CConnectMonitor* pConnectMonitor, int eState) override { return true; }

	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode);
private:
	virtual bool SetState(int eState);
	virtual bool DoState(int eState);
private:
	virtual bool CreateTimer();
	virtual bool RemoveTimer();
public:
	CHttpConnector();
	virtual ~CHttpConnector();
private:
	HHttpConnector*	_hHandler;
	bool			_bFollow;
	int				_eState;

	VectorRequest	_vRequest;
	CConnectMonitor	_xConnector;

	const IHttpRequest* _pRequest;//��ǰ������

	mutable CMutexRecursive	_xMutex;

	std::string		_sUrlFollow;	//�����Url
	uint			_uFollowCount;	//����Ĵ���
	uint			_uFollowMax;	//����Ĵ���

	CTimeNodePtr	_pTimer;
};

NS_TOOL_FRAME_END
