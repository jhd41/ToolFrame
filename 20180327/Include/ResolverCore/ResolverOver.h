#pragma once
#include "IResolverCore.h"

NS_TOOL_FRAME_BEGIN

class CResolverOver
	:public IResolverCore
{
	enum {
		RESOLVE_INVAILD=0,
		RESOLVE_INIT,
		RESOLVE_TRIGGLE_GAME_OVER,
		RESOLVE_GAME_OVER,
		RESOLVE_STOP_GAME,
		RESOLVE_OVER,
	};
private:
	virtual bool OnResolve();
public:
	CResolverOver(void);
	virtual ~CResolverOver(void);
};

NS_TOOL_FRAME_END