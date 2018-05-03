#pragma once

#include "Macro.h"
#include "IUrlRequest.h"

//������������������

NS_TOOL_FRAME_BEGIN

class IUrlExecutor
{
public:
	virtual bool AddRequest(IUrlRequestPtr pRequest)=0;// ���һ����������
	virtual bool ProcessOnce()=0;// �ⲿѭ�����ô˺����������������
public:
	IUrlExecutor() {}
	virtual ~IUrlExecutor() {}
};

//////////////////////////////////////////////////////////////////////////
class CUrlProcessor
{
public:
	template<typename T>
	IUrlRequestPtr	CreateRequest();
	virtual IUrlRequestPtr	CreateRequest();
public:
	virtual bool AddRequest(IUrlRequestPtr pRequest);// ���һ����������
	virtual bool ProcessOnce();// �ⲿѭ�����ô˺����������������
public:
	CUrlProcessor();
	virtual ~CUrlProcessor();
private:
	IUrlExecutor* _pExecutor;
};

template<typename T>
IUrlRequestPtr CUrlProcessor::CreateRequest()
{
	return IUrlRequestPtr(new T());
}

NS_TOOL_FRAME_END