#include "IUrlRequest.h"

NS_TOOL_FRAME_BEGIN

IUrlRequest::IUrlRequest()
{
	_sUrl = "";
	_bPost = false;
	_sResponseData = "";
	_bFinish = false;

	_uID = INVALID_ID;
	_nType = 0;
	_nUserInt = 0;
	_uUserUint = 0;
	_uTimeout = 0;

	_hHandler = nullptr;
}

IUrlRequest::~IUrlRequest()
{
}

bool IUrlRequest::SetHandler(HUrlRequest* hHandler)
{
	_hHandler = hHandler;
	return true;
}

bool IUrlRequest::SetUrl(const std::string& sUrl)
{
	_sUrl = sUrl;
	return true;
}

bool IUrlRequest::SetPost(bool bPostMethod)
{
	_bPost = bPostMethod;
	return true;
}

bool IUrlRequest::SetPostFeilds(const std::string& sFeilds)
{
	_sPostFields = sFeilds;
	return true;
}

bool IUrlRequest::SetFileName(const std::string& sFileName)
{
	_sFileName = sFileName;
	return true;
}

const std::string& IUrlRequest::GetUrl() const
{
	return _sUrl;
}

const std::string& IUrlRequest::GetFileName() const
{
	return _sFileName;
}

bool IUrlRequest::IsPost() const
{
	return _bPost;
}

const std::string& IUrlRequest::GetPostFeilds() const
{
	return _sPostFields;
}

bool IUrlRequest::SetTimeOut(const size_t uTimeOut)
{
	_uTimeout = uTimeOut;
	return true;
}

size_t IUrlRequest::GetTimeOut() const
{
	return _uTimeout;
}

const std::string& IUrlRequest::GetResponseData() const
{
	return _sResponseData;
}

bool IUrlRequest::IsFinished() const
{
	return _bFinish;
}

bool IUrlRequest::MarkFinished()
{
	if (_bFinish)return false;
	_bFinish = true;
	return true;
}

bool IUrlRequest::OnProcess(double fTotalDownload, double fNowDownloaded, double fTotalToUpLoad, double fNowUpLoaded)
{
	if (_hHandler)
		_hHandler->OnProcess(shared_from_this(), fTotalDownload, fNowDownloaded, fTotalToUpLoad, fNowUpLoaded);
	return true;
}

bool IUrlRequest::CallBackFinished(const std::string& sResponse)
{
	_sResponseData = sResponse;

	if (MarkFinished())
		return OnFinished();
	
	return true;
}

bool IUrlRequest::CallBackTimeOut()
{
	OnTimeOut();

	if (MarkFinished())
		return OnFinished();
	
	return true;
}

bool IUrlRequest::OnTimeOut()
{
	if (_hHandler)
		_hHandler->OnTimeOut(shared_from_this());
	return true;
}

bool IUrlRequest::OnFinished()
{
	if (_hHandler)
		_hHandler->OnFinished(shared_from_this());
	return true;
}

NS_TOOL_FRAME_END
