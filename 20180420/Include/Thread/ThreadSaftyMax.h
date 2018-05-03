#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL CThreadSaftyMax
{
public:
	int SetMax(int nMax);
	int AddMax(int nMax);
	int GetMax()const;
public:
	CThreadSaftyMax(void);
	virtual ~CThreadSaftyMax(void);
private:
	mutable CMutexReadWrite _xMutex;
	int _nMax;
};

NS_TOOL_FRAME_END
