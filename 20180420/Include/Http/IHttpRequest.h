#pragma once
#include "Macro.h"
#include "IHttpResponse.h"
#include <functional>

//Http���� ��ʱ֧�� GET POST ���ַ�ʽ
NS_TOOL_FRAME_BEGIN

typedef std::function<bool(const IHttpResponse&)> FnHttpCallBack;

class IHttpRequest
{
public:
	//�������� Ĭ�� Get��ʽ
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
	virtual std::string ToFormat()const;//��ʽ�����
	virtual std::string ToUrl()const;//ת����Url
public:
	virtual bool CallBack(const IHttpResponse& response)const;
public:
	IHttpRequest();
	virtual ~IHttpRequest();
private:
	CFIELD_STRING(InitUrl);					//��ʼ��ʱ���Url

	CFIELD_STRING(Format);					//Э���ʽ(ֻ��Ϊhttp)
	CFIELD_ENUM(ERequestType, RequestType);	//�������� Ĭ��GET
	CFIELD_STRING(AcceptLanguage);			//��������ܵ����� Ĭ��Ϊ zh-CN
	CFIELD_STRING(Host);					//������ַ Ĭ�ϱ���
	CFIELD_STRING(UserAgent);				//�������Ϣ Ĭ�� Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 10.0; WOW64; Trident/7.0; .NET4.0C; .NET4.0E; Tablet PC 2.0)
	CFIELD_BOOL(Connection);				//������Ƿ�֧�ֱ�������ģʽ(��������Ч�ʸ�) Ĭ��֧��
	CFIELD_STRING(Option);					//����ҳ��·�� ���� / ��ͷ
	CFIELD_REF(MapStringString,Arg,v);		//��������
	CFIELD_STRING(Ver);						//Http��ʽ Ĭ�� 1.1
	CFIELD_STRING(Content);					//����

	CFIELD_REF(MapStringString, UserHead, v);//δʶ��ͷ
private:
	FnHttpCallBack	_fnCallBack;
};

NS_TOOL_FRAME_END
