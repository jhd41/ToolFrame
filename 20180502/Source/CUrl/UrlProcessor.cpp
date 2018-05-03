#include "UrlProcessor.h"
#include "UrlExecutor.h"

NS_TOOL_FRAME_BEGIN

//////////////////////////////////////////////////////////////////////////
CUrlProcessor::CUrlProcessor()
{
	_pExecutor = new CUrlExecutor();
}

CUrlProcessor::~CUrlProcessor()
{
	delete _pExecutor;
}

IUrlRequestPtr CUrlProcessor::CreateRequest()
{
	return CreateRequest<IUrlRequest>();
}

bool CUrlProcessor::AddRequest(IUrlRequestPtr pRequest)
{
	return _pExecutor->AddRequest(pRequest);
}
bool CUrlProcessor::ProcessOnce()
{
	return _pExecutor->ProcessOnce();
}

NS_TOOL_FRAME_END

