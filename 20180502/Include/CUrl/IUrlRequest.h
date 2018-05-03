#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

//
// 摘要：
//     表示一个网络请求对象，添加至 CRequestProcessor 以处理该请求

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
	bool				SetUrl(const std::string& sUrl);// 请求网址
	bool				SetPost(bool bPostMethod);//使用Post方式请求 默认不开启 HTTP POST method
	bool				SetPostFeilds(const std::string& sFeilds);//设置Post所需的字段
	bool				SetFileName(const std::string& sFileName);
	bool				SetTimeOut(const size_t uTimeOut);// 超时时间
	const std::string&	GetUrl() const;
	const std::string&	GetFileName()const;
	bool				IsPost()const;
	const std::string&	GetPostFeilds() const;
	size_t				GetTimeOut() const;
	const std::string&	GetResponseData() const;// 请求结果数据
	bool				IsFinished() const;// 标记 - 是否已关闭
	bool				MarkFinished();

	DEFINE_TO_PTR();
public:
	CFIELD_UINT(ID);
	CFIELD_INT(Type);
	CFIELD_INT(UserInt);
	CFIELD_UINT(UserUint);
	CFIELD_STRING(UserString);

	//子类继承
public:
	virtual bool OnProcess(double fTotalDownload, double fNowDownloaded, double fTotalToUpLoad, double fNowUpLoaded);
	virtual bool OnTimeOut();// 当请求超时
	virtual bool OnFinished();

	//底层回调 不要调用
public:
	virtual bool CallBackTimeOut();
	virtual bool CallBackFinished(const std::string& sResponse);
public:
	IUrlRequest();
	virtual ~IUrlRequest();
private:
	std::string			_sUrl;					// 网址
	bool				_bPost;					// Post方式
	std::string			_sPostFields;			// Post所需的字段
	std::string			_sFileName;				// 下载的文件名
	std::string			_sResponseData;			// 请求响应数据
	size_t				_uTimeout;				// 超时时间，单位：毫秒

	bool				_bFinish;				// 标记此请求是否已处理完成

	HUrlRequest*		_hHandler;
};

NS_TOOL_FRAME_END
