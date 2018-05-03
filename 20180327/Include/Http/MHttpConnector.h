#pragma once
#include "Macro.h"
#include "HttpConnector.h"

//Http���ӷ��ʹ�����
//���ڴ�����Http���� Ĭ�����������1

NS_TOOL_FRAME_BEGIN

class MHttpConnector
{
public:
	ST_INTANCE(MHttpConnector);
public:
	typedef std::vector<CHttpConnector*> VectorConnector;
public:
	virtual bool SetHandler(HHttpConnector* hHandler);
	virtual bool SetConnectorCount(uint uCount);		//��������������(Ĭ��1)
	virtual bool Init();

	//Get��ʽ�ύURL																									 //Post��ʽ�ύURL
	virtual bool UrlGet(const std::string& sUrl);
	virtual bool UrlGet(const std::string& sUrl, const FnHttpCallBack& fn);
	virtual bool UrlGet(const std::string& sUrl, const MapStringString& vArg);
	virtual bool UrlGet(const std::string& sUrl, const MapStringString& vArg, const FnHttpCallBack& fn);

	//Post��ʽ�ύURL
	virtual bool UrlPost(const std::string& sUrl);
	virtual bool UrlPost(const std::string& sUrl, const FnHttpCallBack& fn);

	virtual bool UrlPost(const std::string& sUrl, const MapStringString& vArg);
	virtual bool UrlPost(const std::string& sUrl, const MapStringString& vArg,const FnHttpCallBack& fn);

	virtual bool UrlPost(const std::string& sUrl, const std::string& sContent);					//����Url
	virtual bool UrlPost(const std::string& sUrl, const std::string& sContent, const FnHttpCallBack& fn);//����Url

	virtual bool Request(const IHttpRequest& request);	//���һ������

	virtual size_t DebugRequestCount()const;//������ ͳ���ڲ�������
	virtual bool IsOver()const;				//�Ƿ�������
public:
	MHttpConnector();
	virtual ~MHttpConnector();
private:
	VectorConnector _vConnector;
	uint			_uConnectorCount;
	HHttpConnector*	_hHandler;
};

NS_TOOL_FRAME_END
