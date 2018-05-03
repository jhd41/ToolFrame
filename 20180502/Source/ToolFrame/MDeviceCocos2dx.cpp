#include "MDeviceCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "MSystem.h"

NS_TOOL_FRAME_BEGIN

MDeviceCocos2dx::MDeviceCocos2dx(void)
{
}

MDeviceCocos2dx::~MDeviceCocos2dx(void)
{
	Director::getInstance()->getScheduler()->unschedule((SEL_SCHEDULE)&MDeviceCocos2dx::update,this);
}

bool MDeviceCocos2dx::Init()
{
	Director::getInstance()->getScheduler()->schedule((SEL_SCHEDULE)&MDeviceCocos2dx::update,this,0,false);
	return true;
}

void MDeviceCocos2dx::update( float dt )
{
	MSystem::Singleton().RunOnce();
}

NS_TOOL_FRAME_END
#endif // MACRO_LIB_COCOS2D