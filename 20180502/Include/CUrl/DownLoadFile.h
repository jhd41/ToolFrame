#pragma once
#include "Macro.h"
#include "ApiCUrl.h"

NS_TOOL_FRAME_BEGIN

class CDownLoadFile;
class HDownLoad{
public:
	virtual bool OnDownLoadProgress(const CDownLoadFile* pFile, double fTotalDownload, double fNowDownload){return false;}		//下载进度
public:
	HDownLoad(){};
	virtual ~HDownLoad(){}
};
class CDownLoadFile
	:public HCUrl
{
public:
	bool SetHandler(HDownLoad* hHandler);
	bool SetUrl(const std::string& sUrl);
	bool SetFileName(const std::string& sFileName);
	bool DownLoadFile();
public:
	const std::string&	GetUrl()const;
	const std::string&	GetFileName()const;
	HDownLoad*			GetHandler()const;
private:
public:
	virtual bool OnDownLoadProgress(double fTotalDownload, double fNowDownload);		//下载进度
public:
	CDownLoadFile(void);
	virtual ~CDownLoadFile(void);
private:
	std::string _sUrl;
	std::string _sFileName;
	HDownLoad*	_hHandler;
};

NS_TOOL_FRAME_END
