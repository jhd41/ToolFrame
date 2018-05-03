#pragma once

#include "Macro.h"

#ifdef MACRO_LIB_COCOS2D

#include "MacroCocos2dx.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL MDeviceCocos2dx
	:public Ref
{
	ST_INTANCE(MDeviceCocos2dx);
public:
	bool Init();
private:
	void update(float dt);
public:
	MDeviceCocos2dx(void);
	virtual ~MDeviceCocos2dx(void);
};

NS_TOOL_FRAME_END
#endif // MACRO_LIB_COCOS2D
