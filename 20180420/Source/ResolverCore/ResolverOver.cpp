#include "ResolverOver.h"
#include "ResolverStop.h"
#include "ResolverCoreManager.h"

NS_TOOL_FRAME_BEGIN

CResolverOver::CResolverOver(void)
{
	SetResolveRange(RESOLVE_INIT,RESOLVE_OVER);
}

CResolverOver::~CResolverOver(void)
{
}

bool CResolverOver::OnResolve()
{
	switch (GetResolve())
	{
	case RESOLVE_INIT:
		SetResolve(RESOLVE_TRIGGLE_GAME_OVER);
		break;
	case RESOLVE_TRIGGLE_GAME_OVER:
		GetResolverCore()->TriggleEvent("OnGameOver");
		SetResolve(RESOLVE_GAME_OVER);
		break;
	case RESOLVE_GAME_OVER:
		SetResolve(RESOLVE_STOP_GAME);
		break;
	case RESOLVE_STOP_GAME:
		GetResolverCore()->CreateTopResolver<CResolverStop>(nullptr);
		SetResolve(RESOLVE_OVER);
		break;
	}

	return true;
}

NS_TOOL_FRAME_END
