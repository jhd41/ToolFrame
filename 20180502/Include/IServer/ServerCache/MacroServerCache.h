#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"
#include "MacroTopology.h"
#include "IMsgStream.h"

NS_TOOL_FRAME_BEGIN
class IServerCache;
class CServerCacheManager;

typedef CSharePtr<IServerCache>	IServerCachePtr;
NS_TOOL_FRAME_END