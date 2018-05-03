#include "ToolHttp.h"

#include "ToolStd.h"

#include "IHttpRequest.h"
#include "IHttpResponse.h"

bool ToolFrame::IsUrlNetAddress(const std::string& sUrl)
{
	if (ToolFrame::IsBeginWith(sUrl, "https://", 0, true))return true;
	if (ToolFrame::IsBeginWith(sUrl, "http://", 0, true))return true;
	if (ToolFrame::IsBeginWith(sUrl, "ftp://", 0, true))return true;
	if (ToolFrame::IsBeginWith(sUrl, "www.", 0, true))return true;
	return false;
}

bool ToolFrame::IsUrlFileAddress(const std::string& sUrl)
{
	return ToolFrame::IsBeginWith(sUrl, "file://", 0, true);
}

bool ToolFrame::IsFullUrl(const std::string& sUrl)
{
	return ToolFrame::IsHas(sUrl, "://", true);
}

std::string ToolFrame::GetFullUrl(const std::string& sUrl)
{
	if (sUrl.empty())return "";

	if (IsFullUrl(sUrl))return sUrl;

	//默认添加http开头
	return MAKE_STRING("http://" << sUrl);
}

std::string ToolFrame::TrimUrl(const std::string& sUrl)
{
	if (sUrl.empty())return "";
	std::string sFullUrl = GetFullUrl(sUrl);
	ToolFrame::ToLowerCase(sFullUrl);
	return sFullUrl;
}

std::string ToolFrame::HttpRequestGet(const std::string& sUrl) {
	if (sUrl.empty())return "";

	IHttpRequest request;
	if (!request.InitWithUrl(sUrl))return "";
	return request.ToFormat();
}

std::string ToolFrame::HttpRequestGet(const std::string& sUrl, const MapStringString& vArg)
{
	if (sUrl.empty())return "";

	IHttpRequest request;
	if (!request.InitWithUrl(sUrl))return "";
	request.SetArg(vArg);
	return request.ToFormat();
}

std::string ToolFrame::HttpRequestPost(const std::string& sUrl, const MapStringString& vArg)
{
	if (sUrl.empty())return "";

	IHttpRequest request;
	if (!request.InitWithUrl(sUrl))return "";
	request.SetRequestType(IHttpRequest::REQUEST_TYPE_POST);
	request.SetArg(vArg);
	return request.ToFormat();
}

std::string ToolFrame::HttpRequestPost(const std::string& sUrl)
{
	if (sUrl.empty())return "";

	IHttpRequest request;
	if (!request.InitWithUrl(sUrl))return "";
	request.SetRequestType(IHttpRequest::REQUEST_TYPE_POST);
	return request.ToFormat();
}

std::string ToolFrame::HttpResponce(const std::string& sContent) {
	IHttpResponse response;
	response.SetContent(sContent);
	return response.ToFormat();
}

std::string ToolFrame::GetHttpContent(const std::string& sSrc, bool bCheckLength) {
	if (!bCheckLength)
		return ToolFrame::GetMidString(sSrc, "\r\n\r\n", "");

	size_t uContentLength = 0;
	if (!ToolFrame::ToValue(ToolFrame::GetMidString(sSrc, "Content-Length:", "\r\n"), uContentLength))
		return "";

	if (uContentLength <= 0)return "";

	std::string sContent = ToolFrame::GetMidString(sSrc, "\r\n\r\n", "");
	if (sContent.length() != uContentLength)return "";

	return sContent;
}

bool ToolFrame::GetHttpArg(MapStringString& vArg, const std::string& sSrc)
{
	IHttpRequest request;
	if (!request.InitWithFormat(sSrc))return false;
	
	vArg = request.GetArg();
	return true;
}

std::string ToolFrame::HttpParamsToString(const MapStringString& vValue)
{
	if (vValue.empty())return "";

	std::stringstream sStream;
	bool bAttch = false;
	MapStringString::const_iterator itr;
	foreach(itr, vValue) {
		if (bAttch)sStream << "&";
		bAttch = true;

		sStream << UrlEncode(itr->first);
		sStream << "=";
		sStream << UrlEncode(itr->second);
	}
	return sStream.str();
}

bool ToolFrame::StringToHttpParams(MapStringString& vValue, const std::string& sSrc)
{
	if (sSrc.empty())return true;

	MapStringString vTemp;
	if (!ToValue(sSrc, vTemp, "=", "&"))return false;
	return UrlDecode(vValue, vTemp);
}

std::string ToolFrame::UrlEncode(const std::string& sUrl)
{
	std::stringstream sSream;
	size_t uLength = sUrl.length();
	for (size_t uIndex = 0; uIndex < uLength; ++uIndex)
	{
		if (isalnum((unsigned char)sUrl[uIndex]) ||
			(sUrl[uIndex] == '-') ||
			(sUrl[uIndex] == '_') ||
			(sUrl[uIndex] == '.') ||
			(sUrl[uIndex] == '*'))
			sSream << sUrl[uIndex];
		else if (sUrl[uIndex] == ' ')
			sSream << "+";
		else
		{
			sSream << '%';
			sSream << ToolFrame::ToHex((unsigned char)sUrl[uIndex] >> 4);
			sSream << ToolFrame::ToHex((unsigned char)sUrl[uIndex] % 16);
		}
	}
	return sSream.str();
}


std::string ToolFrame::UrlDecode(const std::string& str)
{
	std::stringstream sOutput;
	char cTmp[2] = { 0 };
	size_t uIndex = 0, uLen = str.length();
	while (uIndex < uLen) {
		if (str[uIndex] == '%') {
			if (uIndex + 2 >= uLen)
				return "";

			cTmp[0] = str[uIndex + 1];
			cTmp[1] = str[uIndex + 2];
			sOutput << UrlStr2Bin(cTmp);
			uIndex = uIndex + 3;
		}
		else if (str[uIndex] == '+') {
			sOutput << ' ';
			++uIndex;
		}
		else {
			sOutput << str[uIndex];
			++uIndex;
		}
	}
	return sOutput.str();
}

bool ToolFrame::UrlEncode(MapStringString& vValue, const MapStringString& vSrc)
{
	bool bErr = false;
	//将Arg中的urlencode格式转化为utf8格式
	MapStringString::const_iterator itr;
	foreach(itr, vSrc)
	{
		if (!ToolFrame::Insert(vValue, ToolFrame::UrlEncode(itr->first), ToolFrame::UrlEncode(itr->second)))
			bErr = true;
	}

	return bErr;
}

bool ToolFrame::UrlDecode(MapStringString& vValue, const MapStringString& vSrc)
{
	bool bErr = false;
	//将Arg中的urlencode格式转化为utf8格式
	MapStringString::const_iterator itr;
	foreach(itr, vSrc)
	{
		if (!ToolFrame::Insert(vValue, ToolFrame::UrlDecode(itr->first), ToolFrame::UrlDecode(itr->second)))
			bErr = true;
	}

	return bErr;
}

bool ToolFrame::UrlEncode(MapStringString& vValue)
{
	MapStringString vTemp;
	if (!UrlEncode(vTemp, vValue))return false;
	vValue = vTemp;
	return true;
}

bool ToolFrame::UrlDecode(MapStringString& vValue)
{
	MapStringString vTemp;
	if (!UrlDecode(vTemp, vValue))return false;
	vValue = vTemp;
	return true;
}

char ToolFrame::UrlChar2Int(char cChar)
{
	if (cChar >= '0' && cChar <= '9')return (char)(cChar - '0');
	if (cChar >= 'a' && cChar <= 'f')return (char)(cChar - 'a' + 10);
	if (cChar >= 'A' && cChar <= 'F')return (char)(cChar - 'A' + 10);
	return -1;
}

char ToolFrame::UrlStr2Bin(char *czStr)
{
	char cTempWord[2] = {0};
	char chn=0;
	cTempWord[0] = UrlChar2Int(czStr[0]);                  //make the B to 11 -- 00001011
	cTempWord[1] = UrlChar2Int(czStr[1]);                  //make the 0 to 0  -- 00000000
	chn = (cTempWord[0] << 4) | cTempWord[1];              //to change the BO to 10110000
	return chn;
}
