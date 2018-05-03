#pragma once

#include "Macro.h"

#include "LockMutex.h"
#include "TThreadSaftyList.h"
#include "UrlProcessor.h"

#include "curl/multi.h"

//
// ժҪ��
//     ����������������������Ҫ�ⲿ����

NS_TOOL_FRAME_BEGIN

class CUrlExecutor
	:public IUrlExecutor
{
	//
	// ժҪ��
	//     ��ʾһ��������������� IUrlRequest��CURLM��ResponseData ��
	struct XRequestBundle
	{
		IUrlRequestPtr				pRequest;
		CURLM*						pMulitHandle;

		long						nTime;
		bool						bHaveTimeout;

		//��Ӧ�ֶ�
		std::string					sResponseData;
		std::fstream				fStream;
	};

	typedef std::list<XRequestBundle*> VectorBundle;
	typedef TThreadSaftyListValue<XRequestBundle*> TsVectorBundle;

public:
	bool			AddRequest(IUrlRequestPtr pRequest)override;// ���һ����������
	bool			ProcessOnce()override;// �ⲿѭ�����ô˺����������������
private:
	static size_t	CBWriteResponseMemory(char* pData, size_t uSize, size_t nNmemb, void *pContent);// easy_handle ���յ�����ʱ���ô˻ص�
	static size_t	CBWriteResponseFile(char* pData, size_t uSize, size_t nNmemb, void *pContent);// easy_handle ���յ�����ʱ���ô˻ص�
	static int		CBProgress(void *ptr, double fTotalDownload, double fNowDownloaded, double fTotalToUpLoad, double fNowUpLoaded);
	static int		TimerCallback(CURLM *multi, long timeout_ms, void *userp);
	static bool		InitCUrl(IUrlRequestPtr pRequest, XRequestBundle* pBundle);// ����һ��easy_handle���������multi_handle
public:
	CUrlExecutor();
	virtual ~CUrlExecutor();
private:
	VectorBundle	_vRequestRun;
	TsVectorBundle	_vRequest;		//��ʱ�Ķ���
	

	CMutexRecursive	_xMutex;
};

NS_TOOL_FRAME_END
