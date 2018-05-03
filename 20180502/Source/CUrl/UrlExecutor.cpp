#include "UrlExecutor.h"
#include "MLoger.h"
#include "ToolStd.h"
#include "ApiCUrl.h"

#include "MDebug.h"

NS_TOOL_FRAME_BEGIN

CUrlExecutor::CUrlExecutor()
{
	ApiCUrl::InitGlobal();
}

CUrlExecutor::~CUrlExecutor()
{
}

// 添加网络请求
bool CUrlExecutor::AddRequest(IUrlRequestPtr pRequest)
{
	if (!pRequest)return false;
	if (pRequest->GetUrl().empty())return false;

	// 创建一个请求包
	XRequestBundle* pBundle = new XRequestBundle;
	pBundle->pRequest = pRequest;
	pBundle->pMulitHandle = curl_multi_init();
	pBundle->nTime = pRequest->GetTimeOut();
	pBundle->bHaveTimeout = false;
	pBundle->sResponseData = "";
	if (pBundle->nTime > 0)
		pBundle->bHaveTimeout = true;

	//创建下载文件
	if (!pRequest->GetFileName().empty())
	{
		if (!ToolFrame::OpenFile(pBundle->fStream, pRequest->GetFileName(),std::ios::out | std::ios::binary | std::ios::app))
		{
			delete pBundle;
			return false;
		}
	}

	InitCUrl(pRequest, pBundle);// 向 CUrl 添加一个网络请求

	_vRequest.PushBack(pBundle);
	return true;
}

bool CUrlExecutor::ProcessOnce()
{
	DEBUG_FUN();

	CLockScoped lock(_xMutex,true);
	if (!lock.IsLocked())
		return false;

	//拼接
	{
		CLockWrite lockRequest(_vRequest.GetMutex());
		ToolFrame::Move(_vRequestRun, _vRequest.GetList());
	}

	// 轮询每个请求的状态
	VectorBundle::iterator itr = _vRequestRun.begin();
	while (itr != _vRequestRun.end())
	{
		XRequestBundle* pBundle = *itr;
		ASSERT_LOG_ERROR(pBundle);

		CURLM* pMultiHandle = pBundle->pMulitHandle;
		ASSERT_LOG_ERROR(pMultiHandle);

		if (pBundle->pRequest->IsFinished())
		{
			curl_multi_cleanup(pMultiHandle);
		}
		else {
			int nStillRunning = 1;

			curl_multi_perform(pMultiHandle, &nStillRunning);
			curl_multi_timeout(pMultiHandle, &(pBundle->nTime));

			// -1表示时间已耗尽 // 如果设置了超时
			if (!pBundle->pRequest->IsFinished() && -1 == pBundle->nTime && pBundle->bHaveTimeout)
			{
				// 通知请求对象：请求超时
				pBundle->pRequest->CallBackTimeOut();
				curl_multi_cleanup(pMultiHandle);
			}

			if (!pBundle->pRequest->IsFinished() && 0 == nStillRunning)
			{
				// 通知请求对象：请求完成
				pBundle->pRequest->CallBackFinished(pBundle->sResponseData);
				curl_multi_cleanup(pMultiHandle);
			}
		}

		//执行清理
		if (pBundle->pRequest->IsFinished())
		{
			// 从容器中删除引用
			itr = _vRequestRun.erase(itr);
			// 删除该引用
			delete pBundle;
			pBundle = nullptr;
		}
		else {
			++itr;
		}
	}

	// 如果没有请求了，则设置全部完成
	return _vRequestRun.empty();
}

// easy_handle 接收到数据时调用此回调
size_t CUrlExecutor::CBWriteResponseMemory(char* pData, size_t uSize, size_t uNmemb, void* pContent)
{
	size_t uTotalSize = uSize * uNmemb;

	std::string* symbolBuffer = (std::string*)pContent;
	if (symbolBuffer)
	{
		symbolBuffer->append((char*)pData, (char*)pData + uTotalSize);
	}

	return uTotalSize;
}

 size_t CUrlExecutor::CBWriteResponseFile(char* pData, size_t uSize, size_t uNmemb, void *pContent)
 {
	 size_t uTotalSize = uSize * uNmemb;

	 std::fstream* pfStream = (std::fstream*)pContent;
	 pfStream->write(pData, uTotalSize);

 	return uTotalSize;
 }

int CUrlExecutor::CBProgress(void *ptr, double fTotalDownload, double fNowDownloaded, double fTotalToUpLoad, double fNowUpLoaded)
{
	IUrlRequest* pReqeust = (IUrlRequest*)ptr;
	if (ptr)
		pReqeust->OnProcess(fTotalDownload, fNowDownloaded, fTotalToUpLoad, fNowUpLoaded);
	return 0;
}


int CUrlExecutor::TimerCallback(CURLM *multi, long timeout_ms, void *userp)
{
	// std::cout << "time out!!!" << std::endl;
	std::cout << timeout_ms << std::endl;

	return 0;
}

// 创建一个easy_handle，并添加至multi_handle
bool CUrlExecutor::InitCUrl(IUrlRequestPtr pRequest, XRequestBundle* pBundle)
{
	ASSERT_LOG_ERROR(pRequest);
	ASSERT_LOG_ERROR(pBundle);
	ASSERT_LOG_ERROR(!pRequest->GetUrl().empty());

	// 创建easy_handle
	CURL * pCUrl = curl_easy_init();

	// 设置easy_handle选项
	curl_easy_setopt(pCUrl, CURLOPT_URL, pRequest->GetUrl().c_str());

	curl_easy_setopt(pCUrl, CURLOPT_POST, pRequest->IsPost());
	if (!pRequest->GetPostFeilds().empty()) {
		curl_easy_setopt(pCUrl, CURLOPT_POSTFIELDS, pRequest->GetPostFeilds().c_str());
	}

	//设置基本属性
	curl_easy_setopt(pCUrl, CURLOPT_HEADER, 0L);
	curl_easy_setopt(pCUrl, CURLOPT_VERBOSE, 0L);
	curl_easy_setopt(pCUrl, CURLOPT_CONNECTTIMEOUT_MS,	10000);			// 设置连接超时时间(秒)
	curl_easy_setopt(pCUrl, CURLOPT_TIMEOUT_MS,			pRequest->GetTimeOut());
	curl_easy_setopt(pCUrl, CURLOPT_LOW_SPEED_LIMIT,	1);
	curl_easy_setopt(pCUrl, CURLOPT_LOW_SPEED_TIME,		30);
//	curl_easy_setopt(pCUrl, CURLOPT_VERBOSE, 1L);					// 设置调试信息

	if (pRequest->GetFileName().empty())
	{
		curl_easy_setopt(pCUrl, CURLOPT_WRITEFUNCTION, CUrlExecutor::CBWriteResponseMemory);
		curl_easy_setopt(pCUrl, CURLOPT_WRITEDATA, (void*)&pBundle->sResponseData);
	}
	else {
		// 设置文件续传的位置给libcurl
		curl_easy_setopt(pCUrl, CURLOPT_RESUME_FROM_LARGE,	(curl_off_t)ToolFrame::GetFileLength(pBundle->fStream));
		curl_easy_setopt(pCUrl, CURLOPT_WRITEFUNCTION,		CUrlExecutor::CBWriteResponseFile);
		curl_easy_setopt(pCUrl, CURLOPT_WRITEDATA,			(void*)&pBundle->fStream);
	}

	//下载进度条
	curl_easy_setopt(pCUrl, CURLOPT_NOPROGRESS, false);
	curl_easy_setopt(pCUrl, CURLOPT_PROGRESSFUNCTION, CUrlExecutor::CBProgress);
	curl_easy_setopt(pCUrl, CURLOPT_PROGRESSDATA, pRequest.get());
	curl_easy_setopt(pCUrl, CURLOPT_NOSIGNAL, 1L);

	//关闭证书认证，否则https的下载会错误60
	curl_easy_setopt(pCUrl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(pCUrl, CURLOPT_SSL_VERIFYPEER, 0L);

	// 设置multi_handle选项
	// curl_multi_setopt(pMultiHandle, CURLMOPT_TIMERFUNCTION, TimerCallback);

	// 设置上传
	//curl_easy_setopt(curlhandle, CURLOPT_UPLOAD, 1L);

	// 添加至multi_handle
	int nCode = curl_multi_add_handle(pBundle->pMulitHandle, pCUrl);

	return (nCode == CURLMcode::CURLM_OK);
}

NS_TOOL_FRAME_END
