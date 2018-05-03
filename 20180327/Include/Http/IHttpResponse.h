#pragma once
#include "Macro.h"

//Http应答
NS_TOOL_FRAME_BEGIN

class IHttpResponse
{
public:
	enum EResponseCode
	{
		RESPONSE_OK					= 200,	//成功
		RESPONSE_MOVED_PERMANENTLY	= 301,	//永久重定向([Location]表示请求的资源分配了新url，以后应使用新url)
		RESPONSE_FOUND				= 302,	//临时性重定向([Location] 重定向的url还有可能还会改变)
		RESPONSE_FILE_NOT_EXIST		= 404,	//文件不存在
		RESPONSE_SERVER_ERR			= 500,	//服务器内部错误
	};
public:
	virtual bool InitWithFormat(const std::string& sFormat);
	virtual const std::string& FindHead(const std::string& sHead)const;//查找头字段
public:
	virtual std::string ToFormat()const;//格式化输出
public:
	IHttpResponse();
	virtual ~IHttpResponse();
private:
	CFIELD_ENUM(EResponseCode,ResponseCode);		//状态码 默认 RESPONSE_OK

	CFIELD_STRING(Content);		//内容
	CFIELD_STRING(ContentType);	//内容类型 默认  text/html; charset=utf-8
	CFIELD_STRING(Server);		//服务器信息
	CFIELD_STRING(Date);		//返回日期
	CFIELD_BOOL(Connection);	//浏览器是否支持保持连接模式(保持连接效率高) 默认支持
	CFIELD_STRING(Ver);			//版本 1.1
	
	//ajax POST 跨域
	CFIELD_STRING(AccessControlAllowOrigin);	//指定允许其他域名访问   默认 *
	CFIELD_STRING(AccessControlAllowMethods);	//响应类型   POST
	CFIELD_STRING(AccessControlAllowHeaders);	//响应头设置  x-requested-with,content-type

	CFIELD_REF(MapStringString,UserHead,v);		//未识别头
};

NS_TOOL_FRAME_END
