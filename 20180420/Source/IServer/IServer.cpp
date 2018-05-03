#include "IServer.h"

#include "MLoger.h"

#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN
IServer::IServer(void)
{
	_uRunOnceSleep= 10;

	_mgrElasticThread.SetHandler(this);
	_mgrElasticThread.SetTimeRecycle(30);
}

IServer::~IServer(void)
{
	_mgrElasticThread.Stop();
}

bool IServer::Run()
{
	Init() ? OnInitSucceed() : OnInitFaild();

	while(!MSystem::Singleton().IsReqStop() && RunOnce())
		ToolFrame::Sleep(_uRunOnceSleep);

	return true;
}

bool IServer::ShutDown()
{
	_mgrElasticThread.Stop();
	return MSystem::Singleton().ReqStop();
}

bool IServer::Init()
{
	return MSystem::Singleton().Init();
}

bool IServer::RunOnce()
{
	_mgrElasticThread.RunElasticThread();
	return true;
}

bool IServer::OnInitSucceed()
{
	return false;
}

bool IServer::OnInitFaild()
{
	return false;
}

bool IServer::OnRunElasticThread()
{
	return MSystem::Singleton().RunOnce();
}

bool IServer::SetRunOnceSleep( uint uRunOnceSleep )
{
	_uRunOnceSleep = uRunOnceSleep;
	return true;
}

NS_TOOL_FRAME_END
