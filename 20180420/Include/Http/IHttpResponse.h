#pragma once
#include "Macro.h"

//HttpӦ��
NS_TOOL_FRAME_BEGIN

class IHttpResponse
{
public:
	enum EResponseCode
	{
		RESPONSE_OK					= 200,	//�ɹ�
		RESPONSE_MOVED_PERMANENTLY	= 301,	//�����ض���([Location]��ʾ�������Դ��������url���Ժ�Ӧʹ����url)
		RESPONSE_FOUND				= 302,	//��ʱ���ض���([Location] �ض����url���п��ܻ���ı�)
		RESPONSE_FILE_NOT_EXIST		= 404,	//�ļ�������
		RESPONSE_SERVER_ERR			= 500,	//�������ڲ�����
	};
public:
	virtual bool InitWithFormat(const std::string& sFormat);
	virtual const std::string& FindHead(const std::string& sHead)const;//����ͷ�ֶ�
public:
	virtual std::string ToFormat()const;//��ʽ�����
public:
	IHttpResponse();
	virtual ~IHttpResponse();
private:
	CFIELD_ENUM(EResponseCode,ResponseCode);		//״̬�� Ĭ�� RESPONSE_OK

	CFIELD_STRING(Content);		//����
	CFIELD_STRING(ContentType);	//�������� Ĭ��  text/html; charset=utf-8
	CFIELD_STRING(Server);		//��������Ϣ
	CFIELD_STRING(Date);		//��������
	CFIELD_BOOL(Connection);	//������Ƿ�֧�ֱ�������ģʽ(��������Ч�ʸ�) Ĭ��֧��
	CFIELD_STRING(Ver);			//�汾 1.1
	
	//ajax POST ����
	CFIELD_STRING(AccessControlAllowOrigin);	//ָ������������������   Ĭ�� *
	CFIELD_STRING(AccessControlAllowMethods);	//��Ӧ����   POST
	CFIELD_STRING(AccessControlAllowHeaders);	//��Ӧͷ����  x-requested-with,content-type

	CFIELD_REF(MapStringString,UserHead,v);		//δʶ��ͷ
};

NS_TOOL_FRAME_END
