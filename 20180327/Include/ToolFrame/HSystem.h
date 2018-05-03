#pragma once
#include "Macro.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL HSystem
{
public:
	virtual bool		OnSystemInit();					//系统初始化时
	virtual	bool		OnSystemProcess(uint64 uTime);	//主循环回调(处理时间)
	virtual bool		OnSystemCleanUp();				//系统清理(返回false阻止清理)
	virtual	bool		OnSystemMemoryLow();			//内存不足(返回false阻止清理)
public:
	HSystem(void);
	virtual ~HSystem(void);
};

NS_TOOL_FRAME_END
