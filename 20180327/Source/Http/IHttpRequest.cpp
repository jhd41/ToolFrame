#include "IHttpRequest.h"

#include "ToolStd.h"
#include "ToolHttp.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

IHttpRequest::IHttpRequest()
{
	SetFormat("http");
	SetRequestType(REQUEST_TYPE_GET);
	SetAcceptLanguage("zh - CN");
	SetHost("127.0.0.1");
	SetUserAgent("Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 10.0; WOW64; Trident/7.0; .NET4.0C; .NET4.0E; Tablet PC 2.0)");
	SetConnection(true);
	SetOption("/");
	SetVer("1.1");
}

IHttpRequest::~IHttpRequest()
{
}

//http://hypay.hao-games.com/Alipay/creatorder.php?aaa=1&bb=2
//协议类型://主机地址 /Option ? 参数

bool IHttpRequest::InitWithUrl(const std::string& sUrl)
{
	if (sUrl.empty())return false;

	//URL均是可见的
	if (!ToolFrame::IsVisibleString(sUrl))return false;

	ToolFrame::Clear(_vUserHead);

	std::string sUrlFull = ToolFrame::GetFullUrl(sUrl);

	//分离参数
	VectorString vReturn;
	if (!ToolFrame::GetStringByFormat(vReturn, sUrlFull, "{ValueTag}", "{ValueTag}://{ValueTag}?{ValueTag}", "{ValueTag}://{ValueTag}"))return false;
	if (vReturn.size() < 2)return false;

	const std::string& sFormat		= vReturn[0];
	const std::string& sHostOption  = vReturn[1];
	const std::string& sArg			= vReturn.size() > 2 ? vReturn[2] : ToolFrame::EmptyString();
	std::string sHost;
	std::string sOption;

	//进一步分离Host以及Option
	if (!sHostOption.empty())
	{
		VectorString vOption;
		if (!ToolFrame::SplitStringFirst(vOption, sHostOption, "/"))
		{
			sHost = sHostOption;
			sOption = "/";
		}
		else
		{
			ASSERT_LOG_ERROR(vOption.size() == 2);

			sHost = vOption[0];
			sOption = MAKE_STRING("/" << vOption[1]);
		}
	}

	//校验参数
	if (sHost.empty())return false;

	SetInitUrl(sUrl);
	SetFormat(sFormat);
	SetRequestType(REQUEST_TYPE_GET);
	SetHost(sHost);
	SetOption(sOption);
	ToolFrame::StringToHttpParams(_vArg, sArg);
	return true;
}

bool IHttpRequest::IsUrl(const std::string& sUrl)
{
	IHttpRequest request;
	return request.InitWithUrl(sUrl);
}

bool IHttpRequest::SetCallBack(FnHttpCallBack fn)
{
	_fnCallBack = fn;
	return true;
}

bool IHttpRequest::CallBack(const IHttpResponse& response) const
{
	if (_fnCallBack)
		return _fnCallBack(response);

	return true;
}

bool IHttpRequest::SetRequestType(const std::string& sRequestType)
{
	if (ToolFrame::IsEqual(sRequestType, "GET", true))
	{
		SetRequestType(REQUEST_TYPE_GET);
		return true;
	}
	else if (ToolFrame::IsEqual(sRequestType, "POST", true))
	{
		SetRequestType(REQUEST_TYPE_POST);
		return true;
	}
	return false;
}
/*
GET / sample.Jsp HTTP / 1.1
 Accept-Language:zh-cn
 Connection:Keep-Alive
 Host:localhost
 User-Agent:Mozila/4.0(compatible;MSIE5.01;Window NT5.0)

 Accept-Encoding:gzip,deflate

 username=jinqiao&password=1234
*/

bool IHttpRequest::InitWithFormat(const std::string& sFormat)
{
	if (sFormat.empty())return false;

	//分离 协议头 和 内容
	VectorString vFormat;
	bool bSplit = ToolFrame::SplitStringFirst(vFormat, sFormat, "\r\n\r\n");
	const std::string& sHead	= bSplit ? vFormat[0] : sFormat;
	const std::string& sContent = bSplit ? vFormat[1] : ToolFrame::EmptyString();

	//解析头
	VectorString vHead;
	if (!ToolFrame::SplitString(vHead, sHead, "\r\n"))return false;
	if (vHead.empty())return false;

	//解析请求行(必须是第一行)
	VectorString vRequest;
	ToolFrame::GetStringByFormat(vRequest, vHead[0], "{ValueTag}", "{ValueTag} {ValueTag} {ValueTag}/{ValueTag}");
	if (vRequest.size() < 4)return false;

	const std::string&  sRequestType = vRequest[0];
	const std::string&  sRequestOption = vRequest[1];
	const std::string&  sResponseHttp = vRequest[2];
	const std::string&  sRequestVer = vRequest[3];

	if (!SetRequestType(sRequestType))return false;
	SetVer(sRequestVer);

	//解析Option
	if (!sRequestOption.empty())
	{
		//通常来说Get才通过头传递参数，Post不通过头，但是使用Postman工具竟然 post也通过头发送，觉得甚为惊奇，考虑到两者并不冲突 因此调整为当前兼容的写法
		VectorString vOption;
		if (!ToolFrame::SplitStringFirst(vOption, sRequestOption, "?"))
		{
			SetOption(sRequestOption);
		}
		else
		{
			ASSERT_LOG_ERROR(vOption.size() == 2);
			SetOption(vOption[0]);
			ToolFrame::StringToHttpParams(_vArg, vOption[1]);
		}
	}

	//解析其他头
	for (size_t uIndex = 1; uIndex < vHead.size(); ++uIndex)
	{
		VectorString vHeadArg;
		if (!ToolFrame::SplitStringFirst(vHeadArg, vHead[uIndex], ": "))return false;
		const std::string& sHeadField = vHeadArg[0];
		const std::string& sHeadArg = vHeadArg[1];

		if (ToolFrame::IsEqual(sHeadField, "Host",true)) {
			SetHost(sHeadArg);
			continue;
		}

		if (ToolFrame::IsEqual(sHeadField, "Connection", true)) {
			SetConnection(ToolFrame::IsEqual(sHeadArg, "Keep-Alive", true));
			continue;
		}

		if (ToolFrame::IsEqual(sHeadField, "Accept-Language", true)) {
			SetAcceptLanguage(sHeadArg);
			continue;
		}

		if (ToolFrame::IsEqual(sHeadField, "User-Agent", true)) {
			SetUserAgent(sHeadArg);
			continue;
		}

		//校验内容长度
		if (ToolFrame::IsEqual(sHeadField, "Content-Length", true)) {
			size_t uLength = 0;
			ASSERT_LOG_ERROR(ToolFrame::ToValue(sHeadArg, uLength));
			if (sContent.length() < uLength)
				return false;
			continue;
		}

		//添加到未识别头
		ToolFrame::Insert(_vUserHead, sHeadField, sHeadArg);
	}

	//解析内容
	if (REQUEST_TYPE_POST == GetRequestType())
		ToolFrame::StringToHttpParams(_vArg, sContent);

	return true;
}

std::string IHttpRequest::ToFormat() const
{
	std::stringstream sStream;

	//写Http头
	switch (GetRequestType())
	{
		case REQUEST_TYPE_GET:
		{
			sStream << "GET " << GetOption();
			if (!GetArg().empty()) {
				//如果是GET请求就将Arg中的urlencode格式转化为utf8格式
				MapStringString vArg = GetArg();

				MapStringString::iterator itr;
				foreach(itr, vArg)
				{
					itr->second = ToolFrame::UrlEncode(itr->second);
				}

				sStream << "?" << ToolFrame::HttpParamsToString(vArg);
			}
				
			sStream << " HTTP/" << GetVer() << "\r\n";
		}
		break;
		case REQUEST_TYPE_POST:
		{
			sStream << "POST " << GetOption() << " HTTP / " << GetVer() << "\r\n";
		}	
		break;
	}

	//主机
	sStream <<"Host: "<< GetHost() << "\r\n";
	//连接
	sStream << "Connection: " << (IsConnection() ? "Keep-Alive" : "close") << "\r\n";

	//语言
	if (!GetAcceptLanguage().empty())
		sStream << "Accept-Language: " << GetAcceptLanguage() << "\r\n";

	if (!GetUserAgent().empty())
		sStream << "User-Agent: " << GetUserAgent() << "\r\n";

	//设置内容 如果参数有值 写参数 没参数 写 内容文本
	std::string sArgString;

	//如果是Post方式需要放在内容
	if (REQUEST_TYPE_POST == GetRequestType())
	{
		if (!_vArg.empty())
			sArgString = ToolFrame::HttpParamsToString(_vArg);
	}

	const std::string& sContent = sArgString.empty() ? GetContent() : sArgString;

	//内容必须放在末尾
	if (!sContent.empty())
	{
		sStream << "Content-Length: " << sContent.length() << "\r\n";
		sStream << "\r\n";
		sStream << sContent;
	}
	else {
		sStream << "\r\n";
	}

	return sStream.str();
}

//http://hypay.hao-games.com/Alipay/creatorder.php?aaa=1&bb=2
//协议类型://主机地址 /Option ? 参数
std::string IHttpRequest::ToUrl() const
{
	std::stringstream sStream;
	sStream << GetFormat() << "://"<<GetHost()<<GetOption();

	if (!GetArg().empty())
	{
		MapStringString vArg = GetArg();

		MapStringString::iterator itr;
		foreach(itr, vArg)
		{
			itr->second = ToolFrame::UrlEncode(itr->second);
		}

		sStream << "?" << ToolFrame::HttpParamsToString(vArg);
	}


	return sStream.str();
}

NS_TOOL_FRAME_END
