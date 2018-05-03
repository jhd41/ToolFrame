#pragma once
#include "IResolverCore.h"

NS_TOOL_FRAME_BEGIN

class CResolverStop
	:public IResolverCore
{
	enum {
		RESOLVE_INVAILD=0,
		RESOLVE_INIT,
		RESOLVE_TRIGGLE_STOP,
		RESOLVE_STOP,
		RESOLVE_OVER,
	};
private:
	virtual bool OnResolve();
public:
	CResolverStop(void);
	virtual ~CResolverStop(void);
};

NS_TOOL_FRAME_END
