#pragma once
#include "IThreadNew.h"

//安全线程
//启动的线程会加入MTheard中去会由MThread统一管理(系统Stop时会等待本类的子类完成)

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IThreadSafty
	:public IThreadNew
{
public:
	virtual bool StartThread(uint uTimeInterval=50);
protected:
	virtual	bool SetThreadStoped();
public:
	IThreadSafty(void);
	virtual ~IThreadSafty(void);
};

NS_TOOL_FRAME_END
