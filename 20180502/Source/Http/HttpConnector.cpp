#include "HttpConnector.h"

#include "TArray.h"

#include "MSystem.h"

NS_TOOL_FRAME_BEGIN
bool HHttpConnectorLog::OnErrRequestNotSupport(CHttpConnector* pConnector, const::std::string& sUrl)
{
	LOG_ERROR_MSG("OnErrRequestNotSupport Url:" << sUrl);
	return true;
}

bool HHttpConnectorLog::OnErrRequestFaild(CHttpConnector* pConnector)
{
	const IHttpRequest* pRequest = pConnector->GetRequestCur();
	ASSERT_LOG_ERROR(pRequest);

	LOG_ERROR_MSG("OnErrRequestFaild IP:" << pConnector->GetConnectedAddress()<<" Request:"<< pRequest->ToFormat());
	return true;
}

bool HHttpConnectorLog::OnErrResponseTimeOut(CHttpConnector* pConnector)
{
	const IHttpRequest* pRequest = pConnector->GetRequestCur();
	ASSERT_LOG_ERROR(pRequest);

	LOG_ERROR_MSG("OnErrResponseTimeOut IP:" << pConnector->GetConnectedAddress() << " Request:" << pRequest->ToFormat());
	return true;
}

bool HHttpConnectorLog::OnErrResponseParseFaild(CHttpConnector* pConnector, const std::string& sHttp)
{
	const IHttpRequest* pRequest = pConnector->GetRequestCur();
	ASSERT_LOG_ERROR(pRequest);

	LOG_ERROR_MSG("OnErrResponseParseFaild IP:" << pConnector->GetConnectedAddress()<<" Http:"<< sHttp << " Request:" << pRequest->ToFormat());
	return true;
}

bool HHttpConnectorLog::OnErrResponse(CHttpConnector* pConnector, const IHttpResponse& response)
{
	const IHttpRequest* pRequest = pConnector->GetRequestCur();
	ASSERT_LOG_ERROR(pRequest);
	
	LOG_ERROR_MSG("OnErrResponse IP:" << pConnector->GetConnectedAddress() << " Request:" << pRequest->ToFormat());
	return true;
}

bool ToolFrame::HHttpConnectorLog::OnErrFollowMax(CHttpConnector* pConnector, const::std::string& sUrl)
{
	const IHttpRequest* pRequest = pConnector->GetRequestCur();
	ASSERT_LOG_ERROR(pRequest);

	LOG_ERROR_MSG("OnErrFollowMax IP:" << pConnector->GetConnectedAddress() << " Request:" << pRequest->ToFormat()<<"Url:" << sUrl);
	return true;
}

//////////////////////////////////////////////////////////////////////////
CHttpConnector::CHttpConnector()
{
	_eState = STATE_STOP;
	_hHandler = this;
	_bFollow = true;
	_uFollowCount = 0;
	_uFollowMax = 50;
	_pRequest = nullptr;
	_xConnector.SetHandler(this);
	_xConnector.SetReconnectMax(1);
}

CHttpConnector::~CHttpConnector()
{
	RemoveTimer();
}

bool CHttpConnector::SetHandler(HHttpConnector* hHandler)
{
	if (!hHandler)return false;

	_hHandler = hHandler;
	return true;
}

bool CHttpConnector::SetFollowLocation(bool bFollow /*= true*/)
{
	_bFollow = bFollow;
	return true;
}

bool CHttpConnector::Init()
{
	return true;
}

bool CHttpConnector::Request(const IHttpRequest& request)
{
	CLockScoped lock(_xMutex);
	_vRequest.push_back(request);
	if (STATE_STOP == GetState())
		SetState(STATE_CHECK);
	return true;
}

bool CHttpConnector::IsOver() const
{
	CLockScoped lock(_xMutex);
	return _vRequest.empty();
}

size_t CHttpConnector::GetRequestCount() const
{
	CLockScoped lock(_xMutex);
	return _vRequest.size();
}

int CHttpConnector::GetState() const
{
	CLockScoped lock(_xMutex);
	return _eState;
}

const IHttpRequest* CHttpConnector::GetRequestCur() const
{
	CLockScoped lock(_xMutex);
	return _pRequest;
}

const std::string& CHttpConnector::GetConnectedAddress() const
{
	CLockScoped lock(_xMutex);
	return _xConnector.GetConnectedAddress();
}

CMutexRecursive& CHttpConnector::GetMutex() const
{
	return _xMutex;
}

bool CHttpConnector::OnConnected(CConnectMonitor* pConnectMonitor)
{
	CLockScoped lock(_xMutex);

	_hHandler->OnConnect(this);

	if (STATE_CONNECT == _eState) {
		SetState(STATE_REQUEST);
		return true;
	}
	
	if (STATE_STOP == GetState())
		SetState(STATE_CHECK);
	return true;
}

bool CHttpConnector::OnDisconnected(CConnectMonitor* pConnectMonitor)
{
	CLockScoped lock(_xMutex);

	_hHandler->OnDisconnect(this);

	switch (_eState)
	{
	case STATE_REQUEST:
		_hHandler->OnErrRequestFaild(this);
		SetState(STATE_OVER);
		break;
	case STATE_RESPONSE:
		_hHandler->OnErrRequestFaild(this);
		SetState(STATE_OVER);
		break;
	case STATE_REDIRECT:
		SetState(STATE_CONNECT);
		break;
	case STATE_STOPING:
		SetState(STATE_CHECK);
		break;
	default:
	{
		LOG_ERROR_MSG(_eState);
	}
	break;
	}
	return true;
}

uint CHttpConnector::OnRecved(CConnectMonitor* pConnectMonitor, IDataSession* pSession)
{
	StreamBinaryPtr ptrBuffer = pSession->GetRecvedBuffer();
	ASSERT_LOG_ERROR(ptrBuffer);

	CLockScoped lock(_xMutex);

	if (STATE_RESPONSE == _eState)
	{
		TArrayNew<char> szString(ptrBuffer->GetSize() + 1);
		ASSERT_LOG_ERROR(ptrBuffer->Read(szString, ptrBuffer->GetSize()));
		szString.SetZeroEnd();

		std::string sHttp = szString.GetPtr();

		ToolFrame::IHttpResponse response;
		if (!response.InitWithFormat(sHttp))
			_hHandler->OnErrResponseParseFaild(this, sHttp);

		//错误处理
		switch (response.GetResponseCode())
		{
			//重定向
			case IHttpResponse::RESPONSE_MOVED_PERMANENTLY:
			case IHttpResponse::RESPONSE_FOUND:
				{
					if (_bFollow)
					{
						const std::string& sUrl = response.FindHead("Location");
						if (IHttpRequest::IsUrl(sUrl))
						{
							++_uFollowCount;
							if (_uFollowCount <= _uFollowMax)
							{
								_sUrlFollow = sUrl;
								SetState(STATE_FOLLOW);
								return 1;
							}
							_hHandler->OnErrFollowMax(this, sUrl);
						}
					}
				}
				break;
			default:
				break;
		}

		ASSERT_LOG_ERROR(_pRequest);
		_pRequest->CallBack(response);

		//回调上层
		if (!_hHandler->OnResponse(this, response))
			_hHandler->OnErrResponse(this, response);

		SetState(STATE_OVER);
		return 1;
	}

	if (STATE_STOP == GetState())
		SetState(STATE_CHECK);
	return 1;
}

bool CHttpConnector::OnTimeOut(const CTimeNodePtr& pTimeNode)
{
	CLockScoped lock(_xMutex);

	if (STATE_RESPONSE == GetState())
	{
		_hHandler->OnErrResponseTimeOut(this);
		SetState(STATE_OVER);
		return true;
	}

	return true;
}

bool CHttpConnector::SetState(int eState)
{
	if (_eState == eState)return false;


	//回收状态
	switch (_eState)
	{
		case STATE_RESPONSE:
			{
				RemoveTimer();
			}
			break;
	}

	_eState = eState;

	ASSERT_LOG_ERROR(DoState(_eState));

	_hHandler->OnStateChanged(this);
	return true;
}

bool CHttpConnector::DoState(int eState)
{
	switch (eState)
	{
	case STATE_CHECK:
	{
		if (_vRequest.empty()) {
			if (_xConnector.IsStoped())
			{
				SetState(STATE_STOP);
				return true;
			}
			SetState(STATE_STOPING);
			return true;
		}
		SetState(STATE_PERPAIRE);
		return true;
	}
		break;
	case STATE_PERPAIRE:
	{
		//设置为下一个请求
		ASSERT_LOG_ERROR(!_pRequest);
		ASSERT_LOG_ERROR(!_vRequest.empty());
		if (_vRequest.empty()) {
			return true;
		}

		_pRequest = &_vRequest.front();
		ASSERT_LOG_ERROR(_pRequest);

		_uFollowCount = 0;

		if (!ToolFrame::IsEqual(_pRequest->GetFormat(),"http"))
		{
			_hHandler->OnErrRequestNotSupport(this, _pRequest->GetInitUrl());
			SetState(STATE_OVER);
			return true;
		}

		//如果没有连接 执行连接
		if (!_xConnector.IsConnected())
		{
			SetState(STATE_CONNECT);
			return true;
		}

		//如果已经连接的IP与新IP不符则断开
		if (_xConnector.GetConnectedAddress() != _pRequest->GetHost())
		{
			SetState(STATE_REDIRECT);
			return true;
		}

		SetState(STATE_REQUEST);
		return true;
	}
	break;
	case STATE_CONNECT:
	{
		_xConnector.SetServerAddress(_pRequest->GetHost());
		_xConnector.Start();
		return true;
	}
	break;
	case STATE_REDIRECT:
	{
		_xConnector.Stop();
		return true;
	}
	break;
	case STATE_REQUEST:
	{
		ASSERT_LOG_ERROR(_pRequest);
		_hHandler->OnRequest(this, *_pRequest);
		_xConnector.Send(_pRequest->ToFormat());

		CreateTimer();

		SetState(STATE_RESPONSE);
		return true;
	}
	break;
	case STATE_OVER:
	{
		_vRequest.pop_front();
		_pRequest = nullptr;

		SetState(STATE_CHECK);
		return true;
	}
	break;
	case STATE_STOPING:
	{
		if (_xConnector.IsStoped())
		{
			SetState(STATE_CHECK);
			return true;
		}
		_xConnector.Stop();
		return true;
	}
	break;
	case STATE_FOLLOW:
		{
			IHttpRequest request;
			ASSERT_LOG_ERROR(request.InitWithUrl(_sUrlFollow));

			if (!ToolFrame::IsEqual(request.GetFormat(), "http"))
			{
				_hHandler->OnErrRequestNotSupport(this, request.GetInitUrl());
				SetState(STATE_OVER);
				return true;
			}

			_xConnector.Send(request.ToFormat());

			SetState(STATE_RESPONSE);
		}
		break;
	}

	return true;
}

bool CHttpConnector::CreateTimer()
{
	ASSERT_LOG_ERROR(!_pTimer);
	_pTimer = MSystem::Singleton().GetTimeOutQueque().CreateTimerByAfterSec(this, 10);
	return true;
}

bool CHttpConnector::RemoveTimer()
{
	MSystem::Singleton().GetTimeOutQueque().RemoveTimer(_pTimer);
	ToolFrame::SetPtrNull(_pTimer);

	return true;
}


NS_TOOL_FRAME_END
