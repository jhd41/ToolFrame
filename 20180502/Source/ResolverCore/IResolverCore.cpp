#include "IResolverCore.h"
#include "ResolverCoreManager.h"

NS_TOOL_FRAME_BEGIN

IResolverCore::IResolverCore(void)
{
}


IResolverCore::~IResolverCore(void)
{
}

CResolverCoreManager* IResolverCore::GetResolverCore()
{
	return dynamic_cast<CResolverCoreManager*>(GetResolverMgr());
}

NS_TOOL_FRAME_END