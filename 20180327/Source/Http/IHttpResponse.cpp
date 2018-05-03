#include "IHttpResponse.h"

#include "ToolStd.h"
#include "ToolHttp.h"
#include "MLoger.h"

// ״̬����ϸ����RFC 7230 7231 7232 7234 7235
// ���ӵ�ַ:
// RFC 7231 �󲿷ֵ�Ӧ��״̬�붨��:
// https://www.rfc-editor.org/rfc/pdfrfc/rfc7231.txt.pdf
// RFC 7232:
// https://www.rfc-editor.org/rfc/pdfrfc/rfc7232.txt.pdf
// RFC 7233:
// https://www.rfc-editor.org/rfc/pdfrfc/rfc7233.txt.pdf
// RFC 7234:
// https://www.rfc-editor.org/rfc/pdfrfc/rfc7234.txt.pdf
// RFC 7235:
// https://www.rfc-editor.org/rfc/pdfrfc/rfc7235.txt.pdf


// ��Ϣ��1xx
// ���壺֪ͨ��
// 
// 
// 
// ���壺�������䣨HTTP 1.1�£�
// ��飺
// �Ƿ���������еĴ����ݴ��䣬�����򷵻� ״̬100 ���ܾ��򷵻� ״̬417
// 
// ����ʾ����
// 
// PUT / somewhere / fun HTTP / 1.1
// Host: origin.example.com
// 	Content - Type : video / h264
// 	Content - Length : 1234567890987
// 	Expect : 100 - continue
// 
// 	�ͻ��������ϴ�һ������Ƶ�ļ�����ͷ�ļ��м��� Expect : 100 - continue �ֶΡ�
// 
// 	�ͻ�����Ϊ��
// 	�ͻ�����������ļ�����֮ǰ����Expect�� 100 - continue �ֶΣ����ȷ��ʷ������Ƿ���ܴ��ļ����䣬
// 	���յ�
// 	״̬100 ���� timeout��һЩ��������֧�ָ�״̬���ԣ��ڳ�ʱ��ͻ���Ĭ�Ͻ��ܣ� ֮�� �ͻῪʼ������ļ����ݡ�
// 	���յ�
// 	״̬417 ���ϴ����ļ�
// 
// 	��������Ϊ��
// 	����   �򷵻� ״̬��100
// 	������ �򷵻� ״̬��417��֪ͨ�ͻ��˲�����
// 
// 	RESPONSE_CONTINUE = 100,
// 
// 
// 	���壺ת��Э�飨HTTP 1.1�£�
// 	��飺����������ӿͻ��˵�����ת��������һ��Э��
// 
// 	RESPONSE_SWITCHING_PROTOCOLS,
// 
// 
// 	��Ϣ��2xx
// 	���壺�ɹ���
// 
// 
// 
// 	���壺һ������
// 
// 	RESPONSE_OK = 200,
// 
// 
// 	���壺�Ѿ�����
// 	��飺�������Ѿ��������ĵ���Locationͷ����������URL
// 
// 	RESPONSE_CREATED,
// 
// 
// 	���壺����
// 	��飺�Ѿ��������󣬵�������δ��ɡ�
// 
// 	RESPONSE_ACCEPTED,
// 
// 
// 	���壺�����Զ������Ϣ
// 	��飺�ĵ��Ѿ������ط��أ���һЩӦ��ͷ��response header�����ܲ���ȷ��
// 	��Ϊʹ�õ����ĵ��Ŀ�����
// 
// 	RESPONSE_NON_AUTHORITATIVE_INFO,
// 
// 
// 	���壺û�����ĵ�
// 	��飺û�����ĵ��������Ӧ�ü�����ʾԭ�����ĵ�������û����ڵ�ˢ��ҳ�棬
// 	��Servlet����ȷ���û��ĵ��㹻�£����״̬�����Ǻ����õġ�
// 
// 	RESPONSE_NO_CONTENT,
// 
// 
// 	���壺û�����ĵ�
// 	��飺û���µ����ݣ��������Ӧ������������ʾ�����ݡ�
// 	����ǿ�������������������ݡ�
// 
// 	RESPONSE_RESET_CONTENT,
// 
// 
// 	��Ϣ��3xx
// 	���壺�ض���
// 
// 
// 	RESPONSE_MULTIPLE_CHOICES = 300,
// 	RESPONSE_MOVED_PERMANENTLY,
// 	RESPONSE_FOUND,
// 	RESPONSE_SEE_OTHER,
// 	RESPONSE_NOT_MODIFIED,
// 	RESPONSE_USE_PROXY,
// 
// 	���壺��ʹ�õ�״̬�루����Ч��
// 
// 	RESPONSE_UNUSED,
// 	RESPONSE_TEMPORATY_REDIRECT,
// 
// 
// 	��Ϣ��4xx
// 	���壺���������
// 
// 
// 	���壺��������bad request��
// 	��飺������û���������󣬲�����Ϊ�ǿͻ��˳�����
// 
// 	RESPONSE_BAD_REQUEST = 400,
// 
// 
// 	���壺֤��δ����Ȩ
// 	��飺
// 
// 
// 	RESPONSE_UNAUTHORIZED,
// 
// 	���壺֧������
// 	��飺Ϊδ��������״̬�룬��δ�о���ٷ����塣
// 
// 	RESPONSE_PAYMENT_REQUIRED,
// 
// 	���壺��ֹ
// 	��飺���������������󣬵��ǽ�ֹ������
// 
// 	RESPONSE_FORBIDDEN,
// 
// 	���壺δ�ҵ�
// 	��飺������δ�ҵ���Ӧ����Ĵ���
// 
// 	RESPONSE_NOT_FOUND,
// 
// 	���壺������request method��������
// 	��飺
// 	������request method����������Ϣ��requst - line������������⣬���ǲ�֧�ֶԸ���Դ���в�����
// 	���ҷ��������뷵�ضԸ���Դ���ܵķ�Χ��
// 	ʾ����
// 
// 	RESPONSE_METHOD_NOT_ALLOWED,
// 
// 	���壺�����ܵ�
// 	��飺
// 	������Ϣ��accept - line������������⣬���ǲ������ܡ�
// 	���ҷ��������뷵�ؽ��ܵ����ݡ�
// 	ʾ����
// 	Accept - Language = da, en - gb; q = 0.8, en; q = 0.7
// 	�ͻ��˱�ʾ���ҽ��ܵ���Danish�����ԣ�Ӣʽ���ԣ��������͵����ԡ�q����ֵ��ʾ������quality��
// 	������������������������򷵻� ״̬��406
// 
// 	RESPONSE_NOT_ACCEPTABLE,
// 
// 
// 	���壺
// 	��飺
// 
// 
// 	RESPONSE_PROXY_AUTHENTICATION_REQUIRED,
// 
// 
// 	���壺�����䳬ʱ��ע�⣺�����󲢲����������̣�
// 	��飺������û���ڹ涨ʱ���ڽ��յ�����������ʱ��
// 	Ӧ�÷��� ״̬��408 ���ͻ��ˣ���������������ر����ӣ������Ǽ����ȴ���
// 	�ͻ����ڽ��յ��� ״̬��408 ����ܻᴴ���µ����ӣ��ٴ��ظ�����
// 
// 	RESPONSE_REQUEST_TIMEOUT,
// 
// 
// 	���壺��Դ��ͻ
// 	��飺����������п��ܷ�����PUT�����С�
// 	��ʹ����Դ�汾����ʱ��PUT������������Դ��������ϵ���Դ�汾��һ��ʱ�򷵻� ״̬��409��
// 	���ҷ�������Ҫ���� �ͻ����ܹ����ĳ�ͻ��Ϣ��֪ͨ�ͻ�����Դ�汾��ͻ��
// 
// 	RESPONSE_CONFLICT,
// 
// 
// 	���壺��ʱ��
// 	��飺�� ״̬��410 ��Ҫ��Э��ά����������ͨ��֪ͨ���������������Դ�Ѿ�������������ı�Ϊ�����ã�
// 	ϣ���ͻ��˽��ϳ������ӡ�
// 	�������Դ�����÷ϳ�ʱ����Ӧ���� ״̬��404��δ�ҵ��� ���档
// 
// 	RESPONSE_GONE,
// 
// 
// 	���壺����Ҫ��
// 	��飺�������ܾ�û�� ���ݳ��ȣ�Content - Length���ֶ� ������
// 	˵��������Ҫ�������и��ֶΡ�
// 	�ͻ��˿��ܻ����һ����Ч�� ���ݳ��ȣ�Content - Length����Ȼ����������
// 
// 	RESPONSE_LENGTH_REQUIRED,
// 
// 
// 	���壺��Ч���ݹ���
// 	��飺�������ܾ����ݹ��������
// 	����þܾ�ֻ�Ƕ��ݵģ���ô��������Ӧ����Ӧ��ͷ��response header�����(Retry - After)�ֶΣ�
// 	�����ͻ����ڶ���ʱ�������ٴγ�������
// 
// 	RESPONSE_PAYLOAD_TOO_LARGE,
// 
// 
// 	���壺ͳһ��Դ��ʶ����URI������
// 	��飺�������ܾ� ������Դ��request - target�� ���ȹ���������
// 	���־ܾ�������ܷ����ڣ��ͻ��˰�POST����дΪGET���� URI������
// 
// 	RESPONSE_URI_TOO_LONG,
// 
// 
// 	���壺���䣨media�����ʹ���
// 	��飺�������ܾ��������Ͳ���������
// 	���־ܾ�������ܷ����ڣ��ͻ���ָ���� �������ͣ�Content - Type���ֶ� �� ���ݱ��루Content - Encoding��
// 	�������������ܡ�
// 
// 	RESPONSE_UNSUPPORTED_MEDIA_TYPE,
// 
// 
// 	���壺����ʧ��
// 	��飺�� ״̬��100
// 
// 	RESPONSE_EXPECTATION_FAILED,
// 
// 
// 	���壺����Э��
// 	��飺�������ܾ���ǰЭ��汾����Ҫ�ͻ���ʹ�ø߼�ָ��Э�顣
// 	��������Ҫ��Ӧ��ͷ��response header������ӣ�Upgrade�� �ֶα������ܵ�Э��汾
// 	ʾ����
// 
// 	HTTP / 1.1 426 Upgrade Required
// 	Upgrade : HTTP / 3.0
// 	Connection : Upgrade
// 	Content - Length : 53
// 	Content - Type : text / plain
// 
// 	������Ҫ��ʹ��HTTP / 3.0��Э��
// 
// 	RESPONSE_UPGRADE_REQUIRED = 426,
// 
// 
// 	��Ϣ��5xx
// 	���壺�������ڲ�����
// 
// 
// 	���壺�ڲ�����
// 	��飺�������ڲ�����
// 
// 	RESPONSE_SERVER_ERROR = 500,
// 
// 
// 	���壺δʵ��
// 	��飺���󷽷���request method�� ������
// 
// 	RESPONSE_NOT_IMPLEMENTED,
// 
// 	���壺��������
// 	��飺
// 
// 	RESPONSE_BAD_GATEWAY,
// 
// 	���壺���������Ի��
// 	��飺���������ػ���������������Ե��ȡ�
// 	���������Է��أ�Retry - After���ֶ� ��ʾ�ͻ��˿����ڶ���ʱ�������
// 
// 	RESPONSE_SERVICE_UNAVAILABLE,
// 
// 	���壺���س�ʱ
// 	��飺�����ط��������յ����������ϼ�������ʱδ�ڹ涨ʱ�����յ��ϼ���������Ӧ��
// 
// 	RESPONSE_GATEWAY_TIMEOUT,
//
// 	���壺HTTP�汾��֧��
// 	��飺��������֧������ͷ�б�����HTTP�汾��
// 	������Ӧ�ã�SHOULD������֧�ֵ�HTTP�汾�ţ�����˵��Ϊʲô��֧�֡�
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
	
	//���� Э��ͷ �� ����
	VectorString vFormat;
	bool bSplit = ToolFrame::SplitStringFirst(vFormat, sFormat, "\r\n\r\n");
	const std::string& sHead = bSplit ? vFormat[0] : sFormat;
	const std::string& sContent = bSplit ? vFormat[1] : ToolFrame::EmptyString();

	//����ͷ
	VectorString vHead;
	if (!ToolFrame::SplitString(vHead, sHead, "\r\n"))return false;
	if (vHead.empty())return false;

	//����������(�����ǵ�һ��)
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

	//��������ͷ
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
		//У�����ݳ���
		if (ToolFrame::IsEqual(sHeadField, "Content-Length", true)) {
			size_t uLength = 0;
			ASSERT_LOG_ERROR(ToolFrame::ToValue(sHeadArg, uLength));
			if (sContent.length() < uLength)
				return false;
			continue;
		}

		//��ӵ�δʶ��ͷ
		ToolFrame::Insert(_vUserHead, sHeadField,sHeadArg);
	}

	//��������
	//ת�����ݸ�ʽ
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
	
	//��д����
	const std::string& sContent = GetContent();
	sStream << "Content-Type: "<<GetContentType()<<"\r\n";
	sStream << "Content-Length: " << sContent.length() << "\r\n";
	sStream << "\r\n";
	sStream << sContent;

	return sStream.str();
}

NS_TOOL_FRAME_END
