#pragma once
#include "Macro.h"
class HCUrl{
public:
	virtual bool OnDownLoadProgress(double fTotalDownload, double fNowDownload){return false;}		//下载进度
public:
	HCUrl(){}
	virtual ~HCUrl(){}
};
class ApiCUrl
{
public:
	static bool			DownLoadFile(const std::string& sUrl,const std::string& sFileName,HCUrl* hHandler = nullptr);//下载文件
	static bool			PostUrl(const std::string& sUrl,const std::string& sContent="");
	static std::string	PostUrlResponce( const std::string& sUrl,const std::string& sContent="");

	static bool			InitGlobal();
private:
	static int			ApiDownLoadProgress( void *ptr, double fTotalDownload, double fNowDownloaded, double fTotalToUpLoad, double fNowUpLoaded );

	static size_t		ApiFileWriter( void *ptr, size_t size, size_t nmemb, void *userdata );
	static size_t		ApiStringWriter(void* data, size_t size, size_t nmemb, void* content);
};

