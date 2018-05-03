#pragma once
#include "Macro.h"
#include "IHttpResponse.h"
#include <functional>

//Http请求 暂时支持 GET POST 两种方式
NS_TOOL_FRAME_BEGIN

typedef std::function<bool(const IHttpResponse&)> FnHttpCallBack;

class IHttpRequest
{
public:
	//请求类型 默认 Get方式
	enum ERequestType
	{
		REQUEST_TYPE_GET,
		REQUEST_TYPE_POST,
		REQUEST_TYPE_HEAD,
		REQUEST_TYPE_OPTIONS,
		REQUEST_TYPE_TRACE,
		REQUEST_TYPE_PUT,
	};
public:
	virtual bool InitWithFormat(const std::string& sFormat);
	virtual bool InitWithUrl(const std::string& sUrl);
public:
	static bool IsUrl(const std::string& sUrl);
public:
	virtual bool SetCallBack(FnHttpCallBack fn);
	virtual bool SetRequestType(const std::string& sRequestType);
	virtual std::string ToFormat()const;//格式化输出
	virtual std::string ToUrl()const;//转换回Url
public:
	virtual bool CallBack(const IHttpResponse& response)const;
public:
	IHttpRequest();
	virtual ~IHttpRequest();
private:
	CFIELD_STRING(InitUrl);					//初始化时候的Url

	CFIELD_STRING(Format);					//协议格式(只能为http)
	CFIELD_ENUM(ERequestType, RequestType);	//请求类型 默认GET
	CFIELD_STRING(AcceptLanguage);			//浏览器接受的语言 默认为 zh-CN
	CFIELD_STRING(Host);					//主机地址 默认本机
	CFIELD_STRING(UserAgent);				//浏览器信息 默认 Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 10.0; WOW64; Trident/7.0; .NET4.0C; .NET4.0E; Tablet PC 2.0)
	CFIELD_BOOL(Connection);				//浏览器是否支持保持连接模式(保持连接效率高) 默认支持
	CFIELD_STRING(Option);					//访问页面路径 必须 / 开头
	CFIELD_REF(MapStringString,Arg,v);		//附带参数
	CFIELD_STRING(Ver);						//Http格式 默认 1.1
	CFIELD_STRING(Content);					//内容

	CFIELD_REF(MapStringString, UserHead, v);//未识别头
private:
	FnHttpCallBack	_fnCallBack;
};

NS_TOOL_FRAME_END
