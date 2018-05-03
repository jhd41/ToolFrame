#pragma once

#include "Macro.h"

#include "LockMutex.h"
#include "TThreadSaftyList.h"
#include "UrlProcessor.h"

#include "curl/multi.h"

//
// 摘要：
//     非阻塞网络请求处理器，需要外部驱动

NS_TOOL_FRAME_BEGIN

class CUrlExecutor
	:public IUrlExecutor
{
	//
	// 摘要：
	//     表示一个请求捆绑包。将 IUrlRequest，CURLM，ResponseData 绑定
	struct XRequestBundle
	{
		IUrlRequestPtr				pRequest;
		CURLM*						pMulitHandle;

		long						nTime;
		bool						bHaveTimeout;

		//响应字段
		std::string					sResponseData;
		std::fstream				fStream;
	};

	typedef std::list<XRequestBundle*> VectorBundle;
	typedef TThreadSaftyListValue<XRequestBundle*> TsVectorBundle;

public:
	bool			AddRequest(IUrlRequestPtr pRequest)override;// 添加一个网络请求
	bool			ProcessOnce()override;// 外部循环调用此函数，才能完成请求
private:
	static size_t	CBWriteResponseMemory(char* pData, size_t uSize, size_t nNmemb, void *pContent);// easy_handle 接收到数据时调用此回调
	static size_t	CBWriteResponseFile(char* pData, size_t uSize, size_t nNmemb, void *pContent);// easy_handle 接收到数据时调用此回调
	static int		CBProgress(void *ptr, double fTotalDownload, double fNowDownloaded, double fTotalToUpLoad, double fNowUpLoaded);
	static int		TimerCallback(CURLM *multi, long timeout_ms, void *userp);
	static bool		InitCUrl(IUrlRequestPtr pRequest, XRequestBundle* pBundle);// 创建一个easy_handle，并添加至multi_handle
public:
	CUrlExecutor();
	virtual ~CUrlExecutor();
private:
	VectorBundle	_vRequestRun;
	TsVectorBundle	_vRequest;		//临时的队列
	

	CMutexRecursive	_xMutex;
};

NS_TOOL_FRAME_END
