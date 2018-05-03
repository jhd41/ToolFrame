#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

//
// ժҪ��
//     ��ʾһ������������������ CRequestProcessor �Դ��������

NS_TOOL_FRAME_BEGIN
class IUrlRequest;
typedef CSharePtr<IUrlRequest>		IUrlRequestPtr;
typedef std::vector<IUrlRequestPtr>	VectorRequestPtr;

class HUrlRequest
{
public:
	virtual bool OnTimeOut(IUrlRequestPtr pRequest) { return false; }
	virtual bool OnFinished(IUrlRequestPtr pRequest) { return false; }
	virtual bool OnProcess(IUrlRequestPtr pRequest,double fTotalDownload, double fNowDownloaded, double fTotalToUpLoad, double fNowUpLoaded) { return false; }
public:
	HUrlRequest(){}
	virtual ~HUrlRequest(){}
};

class IUrlRequest
	:public CShareFromThis<IUrlRequest>
{
public:
	bool				SetHandler(HUrlRequest* hHandler);
	bool				SetUrl(const std::string& sUrl);// ������ַ
	bool				SetPost(bool bPostMethod);//ʹ��Post��ʽ���� Ĭ�ϲ����� HTTP POST method
	bool				SetPostFeilds(const std::string& sFeilds);//����Post������ֶ�
	bool				SetFileName(const std::string& sFileName);
	bool				SetTimeOut(const size_t uTimeOut);// ��ʱʱ��
	const std::string&	GetUrl() const;
	const std::string&	GetFileName()const;
	bool				IsPost()const;
	const std::string&	GetPostFeilds() const;
	size_t				GetTimeOut() const;
	const std::string&	GetResponseData() const;// ����������
	bool				IsFinished() const;// ��� - �Ƿ��ѹر�
	bool				MarkFinished();

	DEFINE_TO_PTR();
public:
	CFIELD_UINT(ID);
	CFIELD_INT(Type);
	CFIELD_INT(UserInt);
	CFIELD_UINT(UserUint);
	CFIELD_STRING(UserString);

	//����̳�
public:
	virtual bool OnProcess(double fTotalDownload, double fNowDownloaded, double fTotalToUpLoad, double fNowUpLoaded);
	virtual bool OnTimeOut();// ������ʱ
	virtual bool OnFinished();

	//�ײ�ص� ��Ҫ����
public:
	virtual bool CallBackTimeOut();
	virtual bool CallBackFinished(const std::string& sResponse);
public:
	IUrlRequest();
	virtual ~IUrlRequest();
private:
	std::string			_sUrl;					// ��ַ
	bool				_bPost;					// Post��ʽ
	std::string			_sPostFields;			// Post������ֶ�
	std::string			_sFileName;				// ���ص��ļ���
	std::string			_sResponseData;			// ������Ӧ����
	size_t				_uTimeout;				// ��ʱʱ�䣬��λ������

	bool				_bFinish;				// ��Ǵ������Ƿ��Ѵ������

	HUrlRequest*		_hHandler;
};

NS_TOOL_FRAME_END
