#pragma once

//本工具函数主要围绕Http协议产生
#include "Macro.h"

namespace ToolFrame
{
	//HTTP
	std::string HttpRequestGet(const std::string& sUrl);								//网页请求(Get)
	std::string HttpRequestGet(const std::string& sUrl, const MapStringString& vArg);	//网页请求(Get)						//网页请求(Get)
	std::string HttpRequestPost(const std::string& sUrl);								//网页请求(Post)
	std::string HttpRequestPost(const std::string& sUrl, const MapStringString& vArg);	//网页请求(Post)
	std::string HttpResponce(const std::string& sContent);								//网页应答
	std::string GetHttpContent(const std::string& sSrc, bool bCheckLength = false);		//获取Http内容
	bool		GetHttpArg(MapStringString& vArg, const std::string& sSrc);				//获取Http参数
	std::string HttpParamsToString(const MapStringString& vValue);						//拼接Get方式下Http参数
	bool		StringToHttpParams(MapStringString& vValue,const std::string& sSrc);	//字符串到参数的转换
	bool		IsUrlNetAddress(const std::string& sUrl);								//网址是否是网络地址
	bool		IsUrlFileAddress(const std::string& sUrl);								//网址是否是网络地址
	bool		IsFullUrl(const std::string& sUrl);										//判断是否为完整URL
	std::string GetFullUrl(const std::string& sUrl);									//获取完整URL
	std::string TrimUrl(const std::string& sUrl);										//规整化URL
	
	std::string UrlEncode(const std::string& str);										//字符串到URL格式转换
	std::string UrlDecode(const std::string& str);										//URL到字符串格式转换

	bool		UrlEncode(MapStringString& vValue);										//字符串到URL格式转换
	bool		UrlDecode(MapStringString& vValue);										//URL到字符串格式转换

	bool		UrlEncode(MapStringString& vValue,const MapStringString& vSrc);			//字符串到URL格式转换
	bool		UrlDecode(MapStringString& vValue, const MapStringString& vSrc);		//URL到字符串格式转换

	char		UrlChar2Int(char cChar);//内部函数 不要调用
	char		UrlStr2Bin(char *czStr);//内部函数 不要调用
};

