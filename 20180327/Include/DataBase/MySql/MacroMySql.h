#pragma once

#include "Macro.h"

#ifdef MACRO_LIB_MY_SQL

#include "MacroDefineEx.h"

NS_TOOL_FRAME_BEGIN

DECLARE_SHARE_PTR(IMySqlQuery);
DECLARE_SHARE_PTR(CMySqlWorkThread);

NS_TOOL_FRAME_END

#endif
	