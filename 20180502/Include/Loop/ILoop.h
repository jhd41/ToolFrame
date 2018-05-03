#pragma once

#include "Macro.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL ILoop
{
public:
	virtual	bool InitLoop()=0;
	virtual bool RunOnceLoop()=0;
public:
	virtual bool SetInitedLoop();
	virtual bool IsInitedLoop()const;
public:
	ILoop(void);
	virtual ~ILoop(void);
private:
	bool _bInitLoop;
};

NS_TOOL_FRAME_END
