#define _CRT_SECURE_NO_WARNINGS 1

#include "ApiCUrl.h"

#define CURL_STATICLIB

#pragma comment(lib, "Wldap32.lib")

#include "curl/curl.h"
#include "curl/easy.h"

#define UPDATE_LOW_SPEED_LIMIT 1L
#define UPDATE_LOW_SPEED_TIME 5L

bool ApiCUrl::DownLoadFile( const std::string& sUrl,const std::string& sFileName,HCUrl* hHandler /*= nullptr*/ )
{
	if (sUrl.empty())return false;
	if (sFileName.empty())return false;

	//AssetsManager  
	FILE *fp = fopen(sFileName.c_str(), "wb");
	if (!fp)return false;

	CURL* pCUrl = curl_easy_init();
	if (!pCUrl)return false;

	// Download pacakge
	CURLcode res;
	curl_easy_setopt(pCUrl, CURLOPT_URL, sUrl.c_str());
	curl_easy_setopt(pCUrl, CURLOPT_WRITEFUNCTION, ApiCUrl::ApiFileWriter);
	curl_easy_setopt(pCUrl, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(pCUrl, CURLOPT_NOPROGRESS, false);
	curl_easy_setopt(pCUrl, CURLOPT_PROGRESSFUNCTION, ApiCUrl::ApiDownLoadProgress);
	curl_easy_setopt(pCUrl, CURLOPT_PROGRESSDATA, hHandler);
	curl_easy_setopt(pCUrl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(pCUrl, CURLOPT_LOW_SPEED_LIMIT, UPDATE_LOW_SPEED_LIMIT);
	curl_easy_setopt(pCUrl, CURLOPT_LOW_SPEED_TIME, UPDATE_LOW_SPEED_TIME);
	curl_easy_setopt(pCUrl, CURLOPT_CONNECTTIMEOUT, 10);			// 设置连接超时时间(秒)

	//关闭证书认证，否则https的下载会错误60
	curl_easy_setopt(pCUrl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(pCUrl, CURLOPT_SSL_VERIFYPEER, 0L);

	res = curl_easy_perform(pCUrl);
	curl_easy_cleanup(pCUrl);

	fclose(fp);
	return CURLE_OK == res;
}

size_t ApiCUrl::ApiFileWriter( void *ptr, size_t size, size_t nmemb, void *userdata )
{
	FILE *fp = (FILE*)userdata;
	size_t written = fwrite(ptr, size, nmemb, fp);
	return written;
}

int ApiCUrl::ApiDownLoadProgress( void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded )
{
	HCUrl* hHandler = (HCUrl*)ptr;
	if (ptr)
		hHandler->OnDownLoadProgress(totalToDownload,nowDownloaded);
	return 0;
}

bool ApiCUrl::PostUrl( const std::string& sUrl,const std::string& sContent/*=""*/ )
{
	std::string sResponce;

	CURL* pCurl = curl_easy_init();
	if (!pCurl)return false;

	CURLcode code;
	curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, false);			// 设置https跳过证书验证
	curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, true);
	curl_easy_setopt(pCurl, CURLOPT_URL, sUrl.c_str());				// 设置Url
	curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, sContent.c_str());	// 设置post的json数据
	curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 10);					// 设置超时时间(秒)
	curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, ApiStringWriter);// 设置回调函数
	curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, (void*)&sResponce);	// 设置写数据
	curl_easy_setopt(pCurl, CURLOPT_FOLLOWLOCATION, true);			// 是否抓取跳转后的页面
																 
	code = curl_easy_perform(pCurl);	 // 执行请求
	if (CURLcode::CURLE_OK != code) {
		curl_easy_cleanup(pCurl);
		return false;
	}

	long responseCode = 0;
	curl_easy_getinfo(pCurl, CURLINFO_RESPONSE_CODE, &responseCode);
	if (responseCode < 200 || responseCode >= 300 || sResponce.empty())
	{
		curl_easy_cleanup(pCurl);
		return false;
	}
	
	// 清除curl对象
	curl_easy_cleanup(pCurl);
	return true;
}


size_t ApiCUrl::ApiStringWriter(void* data, size_t size, size_t nmemb, void* content)
{
	size_t totalSize = size*nmemb;
	std::string* symbolBuffer = (std::string*)content;
	if(symbolBuffer)
		symbolBuffer->append((char *)data, ((char*)data)+totalSize);

	return totalSize;
}

std::string ApiCUrl::PostUrlResponce( const std::string& sUrl,const std::string& sContent )
{
	std::string sResponce;

	CURL* pCurl=curl_easy_init();
	if (!pCurl)return "";

	CURLcode code;
	curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, false);			// 设置https跳过证书验证
	curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, true);
	curl_easy_setopt(pCurl, CURLOPT_URL, sUrl.c_str());				// 设置Url
	curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, sContent.c_str());	// 设置post的json数据
	curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 10);					// 设置超时时间(秒)
	curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, ApiStringWriter);// 设置回调函数
	curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, (void*)&sResponce);	// 设置写数据
	curl_easy_setopt(pCurl, CURLOPT_FOLLOWLOCATION, true);			// 是否抓取跳转后的页面
	
	// 执行请求
	code = curl_easy_perform(pCurl);
	if (CURLcode::CURLE_OK != code) {
		curl_easy_cleanup(pCurl);
		return "";
	}

	long responseCode = 0;
	curl_easy_getinfo(pCurl, CURLINFO_RESPONSE_CODE, &responseCode);
	if (responseCode < 200 || responseCode >= 300 || sResponce.empty())
	{
		curl_easy_cleanup(pCurl);
		return "";
	}

	// 清除curl对象
	curl_easy_cleanup(pCurl);
	return sResponce;
}
