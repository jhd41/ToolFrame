#include "ResolverStop.h"
#include "ResolverCoreManager.h"

NS_TOOL_FRAME_BEGIN
	
CResolverStop::CResolverStop(void)
{
	SetResolveRange(RESOLVE_INIT,RESOLVE_OVER);
}

CResolverStop::~CResolverStop(void)
{
}

bool CResolverStop::OnResolve()
{
	switch (GetResolve())
	{
	case RESOLVE_INIT:
		SetResolve(RESOLVE_TRIGGLE_STOP);
		break;
	case RESOLVE_TRIGGLE_STOP:
		GetResolverCore()->TriggleEvent("OnStop");
		SetResolve(RESOLVE_STOP);
		break;
	case RESOLVE_STOP:
		GetResolverCore()->MarkResolveOver();
		SetResolve(RESOLVE_OVER);
		break;
	}

	return true;
}

NS_TOOL_FRAME_END