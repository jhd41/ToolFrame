#pragma once
#include "IResolver.h"

NS_TOOL_FRAME_BEGIN

class CResolverCoreManager;
class IResolverCore
	:public IResolver
{
public:
	virtual CResolverCoreManager* GetResolverCore();
public:
	IResolverCore(void);
	virtual ~IResolverCore(void);
};

NS_TOOL_FRAME_END