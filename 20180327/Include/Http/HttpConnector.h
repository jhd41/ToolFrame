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
	virtual bool OnErrRequestNotSupport(CHttpConnector* pConnector,const::std::string& sUrl) { return false; }//该请求不支持
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
	virtual bool OnErrRequestNotSupport(CHttpConnector* pConnector, const::std::string& sUrl) override;//该请求不支持
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

		STATE_CHECK,		//检测

		STATE_PERPAIRE,		//准备
		STATE_CONNECT,		//连接
		STATE_REQUEST,		//请求
		STATE_RESPONSE,		//应答

		STATE_OVER,			//结束

		STATE_REDIRECT,		//地址切换中

		STATE_STOPING,		//停止中
		STATE_STOP,			//停止

		STATE_FOLLOW,		//跟随

		STATE_MAX,
	};

	typedef std::list<IHttpRequest> VectorRequest;
public:
	virtual bool SetHandler(HHttpConnector* hHandler);	//设置处理器
	virtual bool SetFollowLocation(bool bFollow = true);//跟随跳转后的页面
	virtual bool Init();								//初始化
	virtual bool Request(const IHttpRequest& request);	//添加一个请求
	virtual bool IsOver()const;							//是否均已完成
	virtual size_t GetRequestCount()const;				//获取请求数量
	virtual int GetState()const;						//获取当前状态
	virtual const IHttpRequest* GetRequestCur()const;	//获取当前访问的请求
	virtual const std::string&	GetConnectedAddress()const;//获取连接成功的IP
	virtual CMutexRecursive&	GetMutex()const;		//获取内部互斥锁
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

	const IHttpRequest* _pRequest;//当前的请求

	mutable CMutexRecursive	_xMutex;

	std::string		_sUrlFollow;	//跟随的Url
	uint			_uFollowCount;	//跟随的次数
	uint			_uFollowMax;	//跟随的次数

	CTimeNodePtr	_pTimer;
};

NS_TOOL_FRAME_END
