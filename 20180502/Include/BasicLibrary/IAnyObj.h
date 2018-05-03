#pragma once
#include "Macro.h"

NS_TOOL_FRAME_BEGIN

//任意类对象的指针 用于提供虚析构
class IAnyObj
{
public:
	IAnyObj(){}
	virtual ~IAnyObj(){}
};

NS_TOOL_FRAME_END
