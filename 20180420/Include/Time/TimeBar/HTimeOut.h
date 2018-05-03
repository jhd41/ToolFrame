#pragma once

#include "Macro.h"
#include "MacroDefineEx.h"

#include "TimeNode.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL HTimeOut
{
public:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode)=0;
public:
	HTimeOut();
	virtual ~HTimeOut();
};

NS_TOOL_FRAME_END
