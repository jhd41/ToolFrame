#include "ResolverLua.h"
#include "ResolverCoreManager.h"

NS_TOOL_FRAME_BEGIN

CResolverLua::CResolverLua(void)
{
	_uIndex =0;

	SetResolveRange(RESOLVE_INIT,RESOLVE_OVER);
}

CResolverLua::~CResolverLua(void)
{
}

bool CResolverLua::Init(uint uIndex )
{
	_uIndex = uIndex;
	return true;
}

bool CResolverLua::OnResolve()
{
	switch(GetResolve())
	{
	case RESOLVE_INIT:
		{
			SetResolve(RESOLVE_RESOLVE);
		}
		break;
	case RESOLVE_RESOLVE:
		{
			if (GetResolverCore()->GetLuaEngine().CallFuction<bool,uint>("ResolveAction",_uIndex)){
				SetResolve(RESOLVE_END);
				break;
			}
				
			SetResolve(RESOLVE_NEXT);
		}
		break;
	case RESOLVE_NEXT:
		SetResolve(RESOLVE_RESOLVE);
		break;
	case RESOLVE_END:
		{
			SetResolve(RESOLVE_OVER);
		}
		break;
	}

	return true;
}

NS_TOOL_FRAME_END
