#include "DownLoadFile.h"

NS_TOOL_FRAME_BEGIN

CDownLoadFile::CDownLoadFile(void)
{
	_hHandler = nullptr;
}

CDownLoadFile::~CDownLoadFile(void)
{
}

const std::string& CDownLoadFile::GetUrl() const
{
	return _sUrl;
}

const std::string& CDownLoadFile::GetFileName() const
{
	return _sFileName;
}

bool CDownLoadFile::SetHandler( HDownLoad* hHandler )
{
	_hHandler = hHandler;
	return true;
}

HDownLoad* CDownLoadFile::GetHandler() const
{
	return _hHandler;
}

bool CDownLoadFile::SetUrl( const std::string& sUrl )
{
	_sUrl = sUrl;
	return true;
}

bool CDownLoadFile::SetFileName( const std::string& sFileName )
{
	_sFileName = sFileName;
	return true;
}

bool CDownLoadFile::DownLoadFile()
{
	return ApiCUrl::DownLoadFile(_sUrl,_sFileName,this);
}

bool CDownLoadFile::OnDownLoadProgress( double fTotalDownload, double fNowDownload )
{
	if (!_hHandler)return true;
	if (fTotalDownload<=0)return true;
	return _hHandler->OnDownLoadProgress(this,fTotalDownload,fNowDownload);
}

NS_TOOL_FRAME_END
