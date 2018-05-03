#pragma once

#include "Macro.h"
#include "IUrlRequest.h"

//非阻塞网络请求处理器

NS_TOOL_FRAME_BEGIN

class IUrlExecutor
{
public:
	virtual bool AddRequest(IUrlRequestPtr pRequest)=0;// 添加一个网络请求
	virtual bool ProcessOnce()=0;// 外部循环调用此函数，才能完成请求
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
	virtual bool AddRequest(IUrlRequestPtr pRequest);// 添加一个网络请求
	virtual bool ProcessOnce();// 外部循环调用此函数，才能完成请求
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