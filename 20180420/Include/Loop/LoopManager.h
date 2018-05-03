#pragma once

#include "Macro.h"
#include "ILoop.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL CLoopManager
{
	typedef std::vector<ILoop*>	VectorLoop;
public:
	bool AddLoop(ILoop* pLoop);
	bool RemoveLoop(ILoop* pLoop);
	bool Loop();
public:
	CLoopManager(void);
	virtual ~CLoopManager(void);
private:
	VectorLoop	_vLoop;
};

NS_TOOL_FRAME_END
