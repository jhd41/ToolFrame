#pragma once
#include "IResolverCore.h"
#include "LuaEngine.h"

NS_TOOL_FRAME_BEGIN

class CResolverLua
	:public IResolverCore
{
	enum{
		RESOLVE_INVAILD=0,
		RESOLVE_INIT,
		RESOLVE_RESOLVE,
		RESOLVE_NEXT,
		RESOLVE_END,
		RESOLVE_OVER,
	};
public:
	bool Init(uint uIndex);
private:
	virtual bool OnResolve();
public:
	CResolverLua(void);
	virtual ~CResolverLua(void);
private:
	uint		_uIndex;
};

NS_TOOL_FRAME_END