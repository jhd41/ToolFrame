#include "IHttpResponse.h"

#include "ToolStd.h"
#include "ToolHttp.h"
#include "MLoger.h"

// 状态码详细见：RFC 7230 7231 7232 7234 7235
// 链接地址:
// RFC 7231 大部分的应答状态码定义:
// https://www.rfc-editor.org/rfc/pdfrfc/rfc7231.txt.pdf
// RFC 7232:
// https://www.rfc-editor.org/rfc/pdfrfc/rfc7232.txt.pdf
// RFC 7233:
// https://www.rfc-editor.org/rfc/pdfrfc/rfc7233.txt.pdf
// RFC 7234:
// https://www.rfc-editor.org/rfc/pdfrfc/rfc7234.txt.pdf
// RFC 7235:
// https://www.rfc-editor.org/rfc/pdfrfc/rfc7235.txt.pdf


// 消息：1xx
// 含义：通知的
// 
// 
// 
// 含义：继续传输（HTTP 1.1新）
// 简介：
// 是否接受请求中的大数据传输，接受则返回 状态100 ，拒绝则返回 状态417
// 
// 请求示例：
// 
// PUT / somewhere / fun HTTP / 1.1
// Host: origin.example.com
// 	Content - Type : video / h264
// 	Content - Length : 1234567890987
// 	Expect : 100 - continue
// 
// 	客户端请求上传一个大视频文件，在头文件中加了 Expect : 100 - continue 字段。
// 
// 	客户端行为：
// 	客户端在请求大文件传输之前加入Expect： 100 - continue 字段，首先访问服务器是否接受大文件传输，
// 	接收到
// 	状态100 或者 timeout（一些服务器不支持该状态所以，在超时后客户端默认接受） 之后 就会开始传输大文件数据。
// 	接收到
// 	状态417 则不上传大文件
// 
// 	服务器行为：
// 	接受   则返回 状态码100
// 	不接受 则返回 状态码417，通知客户端不接受
// 
// 	RESPONSE_CONTINUE = 100,
// 
// 
// 	含义：转换协议（HTTP 1.1新）
// 	简介：服务器将遵从客户端的请求转换到另外一种协议
// 
// 	RESPONSE_SWITCHING_PROTOCOLS,
// 
// 
// 	消息：2xx
// 	含义：成功的
// 
// 
// 
// 	含义：一切正常
// 
// 	RESPONSE_OK = 200,
// 
// 
// 	含义：已经创建
// 	简介：服务器已经创建了文档，Location头给出了它的URL
// 
// 	RESPONSE_CREATED,
// 
// 
// 	含义：接受
// 	简介：已经接受请求，但处理尚未完成。
// 
// 	RESPONSE_ACCEPTED,
// 
// 
// 	含义：不是自定义的信息
// 	简介：文档已经正常地返回，但一些应答头（response header）可能不正确，
// 	因为使用的是文档的拷贝。
// 
// 	RESPONSE_NON_AUTHORITATIVE_INFO,
// 
// 
// 	含义：没有新文档
// 	简介：没有新文档，浏览器应该继续显示原来的文档。如果用户定期地刷新页面，
// 	而Servlet可以确定用户文档足够新，这个状态代码是很有用的。
// 
// 	RESPONSE_NO_CONTENT,
// 
// 
// 	含义：没有新文档
// 	简介：没有新的内容，但浏览器应该重置它所显示的内容。
// 	用来强制浏览器清除表单输入内容。
// 
// 	RESPONSE_RESET_CONTENT,
// 
// 
// 	消息：3xx
// 	含义：重定向
// 
// 
// 	RESPONSE_MULTIPLE_CHOICES = 300,
// 	RESPONSE_MOVED_PERMANENTLY,
// 	RESPONSE_FOUND,
// 	RESPONSE_SEE_OTHER,
// 	RESPONSE_NOT_MODIFIED,
// 	RESPONSE_USE_PROXY,
// 
// 	含义：不使用的状态码（即无效）
// 
// 	RESPONSE_UNUSED,
// 	RESPONSE_TEMPORATY_REDIRECT,
// 
// 
// 	消息：4xx
// 	含义：错误的请求
// 
// 
// 	含义：错误请求（bad request）
// 	简介：服务器没有理解该请求，并且认为是客户端出错了
// 
// 	RESPONSE_BAD_REQUEST = 400,
// 
// 
// 	含义：证书未被授权
// 	简介：
// 
// 
// 	RESPONSE_UNAUTHORIZED,
// 
// 	含义：支付错误
// 	简介：为未来保留的状态码，还未有具体官方定义。
// 
// 	RESPONSE_PAYMENT_REQUIRED,
// 
// 	含义：禁止
// 	简介：服务器能理解该请求，但是禁止该请求
// 
// 	RESPONSE_FORBIDDEN,
// 
// 	含义：未找到
// 	简介：服务器未找到响应请求的代理
// 
// 	RESPONSE_NOT_FOUND,
// 
// 	含义：方法（request method）不允许
// 	简介：
// 	方法（request method）的请求信息（requst - line）被服务器理解，但是不支持对该资源进行操作。
// 	并且服务器必须返回对该资源接受的范围。
// 	示例：
// 
// 	RESPONSE_METHOD_NOT_ALLOWED,
// 
// 	含义：不接受的
// 	简介：
// 	接受信息（accept - line）被服务器理解，但是不被接受。
// 	并且服务器必须返回接受的内容。
// 	示例：
// 	Accept - Language = da, en - gb; q = 0.8, en; q = 0.7
// 	客户端表示，我接受丹麦（Danish）语言，英式语言，其他类型的语言。q的数值表示质量（quality）
// 	假如服务器不接受所有语言则返回 状态码406
// 
// 	RESPONSE_NOT_ACCEPTABLE,
// 
// 
// 	含义：
// 	简介：
// 
// 
// 	RESPONSE_PROXY_AUTHENTICATION_REQUIRED,
// 
// 
// 	含义：请求传输超时（注意：该请求并不是整个过程）
// 	简介：服务器没有在规定时间内接收到完整的请求时，
// 	应该发送 状态码408 给客户端，表明服务器打算关闭链接，而不是继续等待。
// 	客户端在接收到该 状态码408 后可能会创建新的链接，再次重复请求
// 
// 	RESPONSE_REQUEST_TIMEOUT,
// 
// 
// 	含义：资源冲突
// 	简介：这种情况更有可能发生在PUT请求中。
// 	当使用资源版本控制时，PUT请求发上来的资源与服务器上的资源版本不一致时则返回 状态码409，
// 	并且服务器需要返回 客户端能够理解的冲突信息，通知客户端资源版本冲突。
// 
// 	RESPONSE_CONFLICT,
// 
// 
// 	含义：过时的
// 	简介：该 状态码410 主要是协助维护服务器，通过通知接收者你请求的资源已经被服务器有意的变为不可用，
// 	希望客户端将废除该链接。
// 	假如该资源被永久废除时，就应该用 状态码404（未找到） 代替。
// 
// 	RESPONSE_GONE,
// 
// 
// 	含义：长度要求
// 	简介：服务器拒绝没有 内容长度（Content - Length）字段 的请求。
// 	说明服务器要求请求有该字段。
// 	客户端可能会添加一个有效的 内容长度（Content - Length），然后重新请求。
// 
// 	RESPONSE_LENGTH_REQUIRED,
// 
// 
// 	含义：有效数据过大
// 	简介：服务器拒绝数据过大的请求。
// 	如果该拒绝只是短暂的，那么服务器就应该在应答头（response header）添加(Retry - After)字段，
// 	表明客户端在多少时间后可能再次尝试请求
// 
// 	RESPONSE_PAYLOAD_TOO_LARGE,
// 
// 
// 	含义：统一资源标识符（URI）过长
// 	简介：服务器拒绝 请求资源（request - target） 长度过长的请求。
// 	这种拒绝请求可能发生在，客户端把POST请求写为GET导致 URI过长。
// 
// 	RESPONSE_URI_TOO_LONG,
// 
// 
// 	含义：传输（media）类型错误
// 	简介：服务器拒绝传输类型不符的请求。
// 	这种拒绝请求可能发生在，客户端指定的 内容类型（Content - Type）字段 和 内容编码（Content - Encoding）
// 	不被服务器接受。
// 
// 	RESPONSE_UNSUPPORTED_MEDIA_TYPE,
// 
// 
// 	含义：期望失败
// 	简介：见 状态码100
// 
// 	RESPONSE_EXPECTATION_FAILED,
// 
// 
// 	含义：升级协议
// 	简介：服务器拒绝当前协议版本，需要客户端使用高级指定协议。
// 	服务器需要在应答头（response header）中添加（Upgrade） 字段表明接受的协议版本
// 	示例：
// 
// 	HTTP / 1.1 426 Upgrade Required
// 	Upgrade : HTTP / 3.0
// 	Connection : Upgrade
// 	Content - Length : 53
// 	Content - Type : text / plain
// 
// 	服务器要求使用HTTP / 3.0的协议
// 
// 	RESPONSE_UPGRADE_REQUIRED = 426,
// 
// 
// 	消息：5xx
// 	含义：服务器内部错误
// 
// 
// 	含义：内部错误
// 	简介：服务器内部错误
// 
// 	RESPONSE_SERVER_ERROR = 500,
// 
// 
// 	含义：未实现
// 	简介：请求方法（request method） 不存在
// 
// 	RESPONSE_NOT_IMPLEMENTED,
// 
// 	含义：错误网关
// 	简介：
// 
// 	RESPONSE_BAD_GATEWAY,
// 
// 	含义：服务器难以获得
// 	简介：服务器过载或服务器正在周期性调度。
// 	服务器可以返回（Retry - After）字段 表示客户端可以在多少时间后重试
// 
// 	RESPONSE_SERVICE_UNAVAILABLE,
// 
// 	含义：网关超时
// 	简介：当网关服务器接收到请求，请求上级服务器时未在规定时间内收到上级服务器的应答。
// 
// 	RESPONSE_GATEWAY_TIMEOUT,
//
// 	含义：HTTP版本不支持
// 	简介：服务器不支持请求头中表明的HTTP版本。
// 	服务器应该（SHOULD）返回支持的HTTP版本号，并且说明为什么不支持。
// 
// 	RESPONSE_HTTP_VERSION_NOT_SUPPORTED

NS_TOOL_FRAME_BEGIN

IHttpResponse::IHttpResponse()
{
	SetResponseCode(RESPONSE_OK);
	SetConnection(true);
	SetDate("Wed, 24 May 2017 11:48:41 GMT");
	SetServer("Apache/2.2.15 (CentOS)");
	SetContentType("text/html; charset=utf-8");
	SetVer("1.1");
	SetAccessControlAllowOrigin("*");
	SetAccessControlAllowMethods("POST");
	SetAccessControlAllowHeaders("x-requested-with,content-type");
}

IHttpResponse::~IHttpResponse()
{

}
/*
HTTP / 1.1 200 OK
Date : Wed, 24 May 2017 11 : 48 : 41 GMT
	Server : Apache / 2.2.15 (CentOS)
	Connection : Keep - Alive
	Access - Control - Allow - Origin : *
	Access - Control - Allow - Methods : POST
	Access - Control - Allow - Headers : x - requested - with, content - type
	Content - Type : text / html; charset = utf - 8
	Content - Length: 29

	callback({
	"Stat" : 16
}
)
*/

bool IHttpResponse::InitWithFormat(const std::string& sFormat)
{
	if (sFormat.empty())return false;

	ToolFrame::Clear(_vUserHead);
	
	//分离 协议头 和 内容
	VectorString vFormat;
	bool bSplit = ToolFrame::SplitStringFirst(vFormat, sFormat, "\r\n\r\n");
	const std::string& sHead = bSplit ? vFormat[0] : sFormat;
	const std::string& sContent = bSplit ? vFormat[1] : ToolFrame::EmptyString();

	//解析头
	VectorString vHead;
	if (!ToolFrame::SplitString(vHead, sHead, "\r\n"))return false;
	if (vHead.empty())return false;

	//解析请求行(必须是第一行)
	VectorString vRequest;
	ToolFrame::GetStringByFormat(vRequest, vHead[0], "{ValueTag}", "{ValueTag}/{ValueTag} {ValueTag} {ValueTag}");
	if (vRequest.size() < 4)return false;

	const std::string& sResponseHttp = vRequest[0];
	const std::string& sResponseVer = vRequest[1];
	const std::string& sResponseCode = vRequest[2];
	int nResponseCode = 0;

	if (!ToolFrame::IsEqual(sResponseHttp, "Http", true))
		return false;

	if (!ToolFrame::ToValue(sResponseCode, nResponseCode))
		return false;

	SetVer(sResponseVer);
	SetResponseCode(nResponseCode);

	//解析其他头
	for (size_t uIndex = 1; uIndex < vHead.size(); ++uIndex)
	{
		VectorString vHeadArg;
		if (!ToolFrame::SplitStringFirst(vHeadArg, vHead[uIndex], ": "))return false;
		const std::string& sHeadField = vHeadArg[0];
		const std::string& sHeadArg = vHeadArg[1];

		if (ToolFrame::IsEqual(sHeadField, "Date", true)) {
			SetDate(sHeadArg);
			continue;
		}
		if (ToolFrame::IsEqual(sHeadField, "Server", true)) {
			SetServer(sHeadArg);
			continue;
		}
		if (ToolFrame::IsEqual(sHeadField, "Connection", true)) {
			SetConnection(ToolFrame::IsEqual(sHeadArg, "keep-alive", true));
			continue;
		}

		if (ToolFrame::IsEqual(sHeadField, "Access-Control-Allow-Origin", true)) {
			SetAccessControlAllowOrigin(sHeadArg);
			continue;
		}
		if (ToolFrame::IsEqual(sHeadField, "Access-Control-Allow-Methods", true)) {
			SetAccessControlAllowMethods(sHeadArg);
			continue;
		}
		if (ToolFrame::IsEqual(sHeadField, "Access-Control-Allow-Headers", true)) {
			SetAccessControlAllowHeaders(sHeadArg);
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
		ToolFrame::Insert(_vUserHead, sHeadField,sHeadArg);
	}

	//设置内容
	//转换内容格式
	std::string sDecodeContent = ToolFrame::UrlDecode(sContent);
	SetContent(sDecodeContent);
	return true;
}

const std::string& IHttpResponse::FindHead(const std::string& sHead) const
{
	return ToolFrame::GetValueByKey(_vUserHead, sHead,ToolFrame::EmptyString());
}

std::string IHttpResponse::ToFormat() const
{
	std::stringstream sStream;
	sStream << "HTTP/"		<<GetVer()<<" "<<GetResponseCode()<<" OK"<<"\r\n";
	sStream << "Date: "		<<GetDate()<<"\r\n";
	sStream << "Server: "	<<GetServer()<<"\r\n";
	sStream << "Connection: "<< (IsConnection() ? "Keep-Alive" : "close") <<"\r\n";
	sStream << "Access-Control-Allow-Origin: "	<< GetAccessControlAllowOrigin() << "\r\n";
	sStream << "Access-Control-Allow-Methods: " << GetAccessControlAllowMethods() << "\r\n";
	sStream << "Access-Control-Allow-Headers: " << GetAccessControlAllowHeaders() << "\r\n";

	//	sStream << "X-Powered-By: PHP/5.6.30\r\n";
	
	//编写内容
	const std::string& sContent = GetContent();
	sStream << "Content-Type: "<<GetContentType()<<"\r\n";
	sStream << "Content-Length: " << sContent.length() << "\r\n";
	sStream << "\r\n";
	sStream << sContent;

	return sStream.str();
}

NS_TOOL_FRAME_END
