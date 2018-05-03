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

// �����������
bool CUrlExecutor::AddRequest(IUrlRequestPtr pRequest)
{
	if (!pRequest)return false;
	if (pRequest->GetUrl().empty())return false;

	// ����һ�������
	XRequestBundle* pBundle = new XRequestBundle;
	pBundle->pRequest = pRequest;
	pBundle->pMulitHandle = curl_multi_init();
	pBundle->nTime = pRequest->GetTimeOut();
	pBundle->bHaveTimeout = false;
	pBundle->sResponseData = "";
	if (pBundle->nTime > 0)
		pBundle->bHaveTimeout = true;

	//���������ļ�
	if (!pRequest->GetFileName().empty())
	{
		if (!ToolFrame::OpenFile(pBundle->fStream, pRequest->GetFileName(),std::ios::out | std::ios::binary | std::ios::app))
		{
			delete pBundle;
			return false;
		}
	}

	InitCUrl(pRequest, pBundle);// �� CUrl ���һ����������

	_vRequest.PushBack(pBundle);
	return true;
}

bool CUrlExecutor::ProcessOnce()
{
	DEBUG_FUN();

	CLockScoped lock(_xMutex,true);
	if (!lock.IsLocked())
		return false;

	//ƴ��
	{
		CLockWrite lockRequest(_vRequest.GetMutex());
		ToolFrame::Move(_vRequestRun, _vRequest.GetList());
	}

	// ��ѯÿ�������״̬
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

			// -1��ʾʱ���Ѻľ� // ��������˳�ʱ
			if (!pBundle->pRequest->IsFinished() && -1 == pBundle->nTime && pBundle->bHaveTimeout)
			{
				// ֪ͨ�����������ʱ
				pBundle->pRequest->CallBackTimeOut();
				curl_multi_cleanup(pMultiHandle);
			}

			if (!pBundle->pRequest->IsFinished() && 0 == nStillRunning)
			{
				// ֪ͨ��������������
				pBundle->pRequest->CallBackFinished(pBundle->sResponseData);
				curl_multi_cleanup(pMultiHandle);
			}
		}

		//ִ������
		if (pBundle->pRequest->IsFinished())
		{
			// ��������ɾ������
			itr = _vRequestRun.erase(itr);
			// ɾ��������
			delete pBundle;
			pBundle = nullptr;
		}
		else {
			++itr;
		}
	}

	// ���û�������ˣ�������ȫ�����
	return _vRequestRun.empty();
}

// easy_handle ���յ�����ʱ���ô˻ص�
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

// ����һ��easy_handle���������multi_handle
bool CUrlExecutor::InitCUrl(IUrlRequestPtr pRequest, XRequestBundle* pBundle)
{
	ASSERT_LOG_ERROR(pRequest);
	ASSERT_LOG_ERROR(pBundle);
	ASSERT_LOG_ERROR(!pRequest->GetUrl().empty());

	// ����easy_handle
	CURL * pCUrl = curl_easy_init();

	// ����easy_handleѡ��
	curl_easy_setopt(pCUrl, CURLOPT_URL, pRequest->GetUrl().c_str());

	curl_easy_setopt(pCUrl, CURLOPT_POST, pRequest->IsPost());
	if (!pRequest->GetPostFeilds().empty()) {
		curl_easy_setopt(pCUrl, CURLOPT_POSTFIELDS, pRequest->GetPostFeilds().c_str());
	}

	//���û�������
	curl_easy_setopt(pCUrl, CURLOPT_HEADER, 0L);
	curl_easy_setopt(pCUrl, CURLOPT_VERBOSE, 0L);
	curl_easy_setopt(pCUrl, CURLOPT_CONNECTTIMEOUT_MS,	10000);			// �������ӳ�ʱʱ��(��)
	curl_easy_setopt(pCUrl, CURLOPT_TIMEOUT_MS,			pRequest->GetTimeOut());
	curl_easy_setopt(pCUrl, CURLOPT_LOW_SPEED_LIMIT,	1);
	curl_easy_setopt(pCUrl, CURLOPT_LOW_SPEED_TIME,		30);
//	curl_easy_setopt(pCUrl, CURLOPT_VERBOSE, 1L);					// ���õ�����Ϣ

	if (pRequest->GetFileName().empty())
	{
		curl_easy_setopt(pCUrl, CURLOPT_WRITEFUNCTION, CUrlExecutor::CBWriteResponseMemory);
		curl_easy_setopt(pCUrl, CURLOPT_WRITEDATA, (void*)&pBundle->sResponseData);
	}
	else {
		// �����ļ�������λ�ø�libcurl
		curl_easy_setopt(pCUrl, CURLOPT_RESUME_FROM_LARGE,	(curl_off_t)ToolFrame::GetFileLength(pBundle->fStream));
		curl_easy_setopt(pCUrl, CURLOPT_WRITEFUNCTION,		CUrlExecutor::CBWriteResponseFile);
		curl_easy_setopt(pCUrl, CURLOPT_WRITEDATA,			(void*)&pBundle->fStream);
	}

	//���ؽ�����
	curl_easy_setopt(pCUrl, CURLOPT_NOPROGRESS, false);
	curl_easy_setopt(pCUrl, CURLOPT_PROGRESSFUNCTION, CUrlExecutor::CBProgress);
	curl_easy_setopt(pCUrl, CURLOPT_PROGRESSDATA, pRequest.get());
	curl_easy_setopt(pCUrl, CURLOPT_NOSIGNAL, 1L);

	//�ر�֤����֤������https�����ػ����60
	curl_easy_setopt(pCUrl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(pCUrl, CURLOPT_SSL_VERIFYPEER, 0L);

	// ����multi_handleѡ��
	// curl_multi_setopt(pMultiHandle, CURLMOPT_TIMERFUNCTION, TimerCallback);

	// �����ϴ�
	//curl_easy_setopt(curlhandle, CURLOPT_UPLOAD, 1L);

	// �����multi_handle
	int nCode = curl_multi_add_handle(pBundle->pMulitHandle, pCUrl);

	return (nCode == CURLMcode::CURLM_OK);
}

NS_TOOL_FRAME_END
