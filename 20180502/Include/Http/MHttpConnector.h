#pragma once
#include "Macro.h"
#include "HttpConnector.h"

//Http连接访问管理器
//用于大批量Http访问 默认最大连接数1

NS_TOOL_FRAME_BEGIN

class MHttpConnector
{
public:
	ST_INTANCE(MHttpConnector);
public:
	typedef std::vector<CHttpConnector*> VectorConnector;
public:
	virtual bool SetHandler(HHttpConnector* hHandler);
	virtual bool SetConnectorCount(uint uCount);		//设置连接数数量(默认1)
	virtual bool Init();

	//Get方式提交URL																									 //Post方式提交URL
	virtual bool UrlGet(const std::string& sUrl);
	virtual bool UrlGet(const std::string& sUrl, const FnHttpCallBack& fn);
	virtual bool UrlGet(const std::string& sUrl, const MapStringString& vArg);
	virtual bool UrlGet(const std::string& sUrl, const MapStringString& vArg, const FnHttpCallBack& fn);

	//Post方式提交URL
	virtual bool UrlPost(const std::string& sUrl);
	virtual bool UrlPost(const std::string& sUrl, const FnHttpCallBack& fn);

	virtual bool UrlPost(const std::string& sUrl, const MapStringString& vArg);
	virtual bool UrlPost(const std::string& sUrl, const MapStringString& vArg,const FnHttpCallBack& fn);

	virtual bool UrlPost(const std::string& sUrl, const std::string& sContent);					//请求Url
	virtual bool UrlPost(const std::string& sUrl, const std::string& sContent, const FnHttpCallBack& fn);//请求Url

	virtual bool Request(const IHttpRequest& request);	//添加一个请求

	virtual size_t DebugRequestCount()const;//调试用 统计内部请求数
	virtual bool IsOver()const;				//是否均已完成
public:
	MHttpConnector();
	virtual ~MHttpConnector();
private:
	VectorConnector _vConnector;
	uint			_uConnectorCount;
	HHttpConnector*	_hHandler;
};

NS_TOOL_FRAME_END
