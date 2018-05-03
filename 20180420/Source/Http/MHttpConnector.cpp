#include "MHttpConnector.h"

#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

MHttpConnector::MHttpConnector()
{
	_uConnectorCount = 1;
	_hHandler = nullptr;
}

MHttpConnector::~MHttpConnector()
{
	ToolFrame::Delete(_vConnector);
}

bool MHttpConnector::SetHandler(HHttpConnector* hHandler)
{
	_hHandler = hHandler;
	return true;
}

bool MHttpConnector::SetConnectorCount(uint uCount)
{
	_uConnectorCount = uCount;
	return true;
}

bool MHttpConnector::Init()
{
	for (uint uIndex =0 ;uIndex < _uConnectorCount;++uIndex)
	{
		CHttpConnector* pConnector = new CHttpConnector();
		ASSERT_LOG_ERROR(pConnector);

		pConnector->SetHandler(_hHandler);
		pConnector->Init();

		ToolFrame::Insert(_vConnector, pConnector);
	}

	return true;
}

bool MHttpConnector::Request(const IHttpRequest& request)
{
	if (_vConnector.empty())return false;

	CHttpConnector* pConnector = ToolFrame::RandValue(_vConnector);
	ASSERT_LOG_ERROR(pConnector);
	return pConnector->Request(request);
}

bool MHttpConnector::UrlPost(const std::string& sUrl)
{
	return UrlPost(sUrl, ToolFrame::EmptyString(), nullptr);
}

bool MHttpConnector::UrlPost(const std::string& sUrl, const std::string& sContent)
{
	return UrlPost(sUrl, sContent, nullptr);
}

bool MHttpConnector::UrlPost(const std::string& sUrl, const FnHttpCallBack& fn)
{
	return UrlPost(sUrl,ToolFrame::EmptyString(), fn);
}

bool MHttpConnector::UrlPost(const std::string& sUrl, const std::string& sContent, const FnHttpCallBack& fn)
{
	if (sUrl.empty())return false;

	IHttpRequest request;
	if (!request.InitWithUrl(sUrl))return false;
	request.SetRequestType(IHttpRequest::REQUEST_TYPE_POST);
	request.SetContent(sContent);
	request.SetCallBack(fn);
	return Request(request);
}

bool MHttpConnector::UrlPost(const std::string& sUrl, const MapStringString& vArg)
{
	return UrlPost(sUrl, vArg, nullptr);
}

bool MHttpConnector::UrlPost(const std::string& sUrl, const MapStringString& vArg, const FnHttpCallBack& fn)
{
	if (sUrl.empty())return false;

	IHttpRequest request;
	if (!request.InitWithUrl(sUrl))return false;
	request.SetRequestType(IHttpRequest::REQUEST_TYPE_POST);
	request.SetArg(vArg);
	request.SetCallBack(fn);
	return Request(request);
}

bool MHttpConnector::UrlGet(const std::string& sUrl)
{
	return UrlGet(sUrl, nullptr);
}

bool MHttpConnector::UrlGet(const std::string& sUrl, const FnHttpCallBack& fn)
{
	if (sUrl.empty())return false;

	IHttpRequest request;
	if (!request.InitWithUrl(sUrl))return false;
	request.SetCallBack(fn);
	return Request(request);
}

bool MHttpConnector::UrlGet(const std::string& sUrl, const MapStringString& vArg)
{
	return UrlGet(sUrl, vArg, nullptr);
}

bool MHttpConnector::UrlGet(const std::string& sUrl, const MapStringString& vArg, const FnHttpCallBack& fn)
{
	if (sUrl.empty())return false;

	IHttpRequest request;
	if (!request.InitWithUrl(sUrl))return false;
	request.SetArg(vArg);
	request.SetCallBack(fn);
	return Request(request);
}

size_t MHttpConnector::DebugRequestCount() const
{
	size_t uCount = 0;

	VectorConnector::const_iterator itr;
	foreach(itr, _vConnector) {
		CHttpConnector* pConnector = *itr;
		ASSERT_LOG_ERROR(pConnector);

		uCount += pConnector->GetRequestCount();
	}

	return uCount;
}

bool MHttpConnector::IsOver() const
{
	VectorConnector::const_iterator itr;
	foreach(itr,_vConnector) {
		const CHttpConnector* pConntecor = *itr;
		ASSERT_LOG_ERROR(pConntecor);
		if (!pConntecor->IsOver())
			return false;
	}

	return true;
}

NS_TOOL_FRAME_END
