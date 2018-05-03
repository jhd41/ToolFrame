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
//Э������://������ַ /Option ? ����

bool IHttpRequest::InitWithUrl(const std::string& sUrl)
{
	if (sUrl.empty())return false;

	//URL���ǿɼ���
	if (!ToolFrame::IsVisibleString(sUrl))return false;

	ToolFrame::Clear(_vUserHead);

	std::string sUrlFull = ToolFrame::GetFullUrl(sUrl);

	//�������
	VectorString vReturn;
	if (!ToolFrame::GetStringByFormat(vReturn, sUrlFull, "{ValueTag}", "{ValueTag}://{ValueTag}?{ValueTag}", "{ValueTag}://{ValueTag}"))return false;
	if (vReturn.size() < 2)return false;

	const std::string& sFormat		= vReturn[0];
	const std::string& sHostOption  = vReturn[1];
	const std::string& sArg			= vReturn.size() > 2 ? vReturn[2] : ToolFrame::EmptyString();
	std::string sHost;
	std::string sOption;

	//��һ������Host�Լ�Option
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

	//У�����
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

	//���� Э��ͷ �� ����
	VectorString vFormat;
	bool bSplit = ToolFrame::SplitStringFirst(vFormat, sFormat, "\r\n\r\n");
	const std::string& sHead	= bSplit ? vFormat[0] : sFormat;
	const std::string& sContent = bSplit ? vFormat[1] : ToolFrame::EmptyString();

	//����ͷ
	VectorString vHead;
	if (!ToolFrame::SplitString(vHead, sHead, "\r\n"))return false;
	if (vHead.empty())return false;

	//����������(�����ǵ�һ��)
	VectorString vRequest;
	ToolFrame::GetStringByFormat(vRequest, vHead[0], "{ValueTag}", "{ValueTag} {ValueTag} {ValueTag}/{ValueTag}");
	if (vRequest.size() < 4)return false;

	const std::string&  sRequestType = vRequest[0];
	const std::string&  sRequestOption = vRequest[1];
	const std::string&  sResponseHttp = vRequest[2];
	const std::string&  sRequestVer = vRequest[3];

	if (!SetRequestType(sRequestType))return false;
	SetVer(sRequestVer);

	//����Option
	if (!sRequestOption.empty())
	{
		//ͨ����˵Get��ͨ��ͷ���ݲ�����Post��ͨ��ͷ������ʹ��Postman���߾�Ȼ postҲͨ��ͷ���ͣ�������Ϊ���棬���ǵ����߲�����ͻ ��˵���Ϊ��ǰ���ݵ�д��
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

	//��������ͷ
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

		//У�����ݳ���
		if (ToolFrame::IsEqual(sHeadField, "Content-Length", true)) {
			size_t uLength = 0;
			ASSERT_LOG_ERROR(ToolFrame::ToValue(sHeadArg, uLength));
			if (sContent.length() < uLength)
				return false;
			continue;
		}

		//��ӵ�δʶ��ͷ
		ToolFrame::Insert(_vUserHead, sHeadField, sHeadArg);
	}

	//��������
	if (REQUEST_TYPE_POST == GetRequestType())
		ToolFrame::StringToHttpParams(_vArg, sContent);

	return true;
}

std::string IHttpRequest::ToFormat() const
{
	std::stringstream sStream;

	//дHttpͷ
	switch (GetRequestType())
	{
		case REQUEST_TYPE_GET:
		{
			sStream << "GET " << GetOption();
			if (!GetArg().empty()) {
				//�����GET����ͽ�Arg�е�urlencode��ʽת��Ϊutf8��ʽ
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

	//����
	sStream <<"Host: "<< GetHost() << "\r\n";
	//����
	sStream << "Connection: " << (IsConnection() ? "Keep-Alive" : "close") << "\r\n";

	//����
	if (!GetAcceptLanguage().empty())
		sStream << "Accept-Language: " << GetAcceptLanguage() << "\r\n";

	if (!GetUserAgent().empty())
		sStream << "User-Agent: " << GetUserAgent() << "\r\n";

	//�������� ���������ֵ д���� û���� д �����ı�
	std::string sArgString;

	//�����Post��ʽ��Ҫ��������
	if (REQUEST_TYPE_POST == GetRequestType())
	{
		if (!_vArg.empty())
			sArgString = ToolFrame::HttpParamsToString(_vArg);
	}

	const std::string& sContent = sArgString.empty() ? GetContent() : sArgString;

	//���ݱ������ĩβ
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
//Э������://������ַ /Option ? ����
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
