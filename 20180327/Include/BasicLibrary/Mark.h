#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"

//备注:
//本类是唯一执行类，用于只在第一次运行时做点什么的标记。

NS_TOOL_FRAME_BEGIN
class CMark
{
public:
	bool IsMarked(int nMark = INVALID_ID)const;
	bool TryMark(int nMark = INVALID_ID);//尝试标记第一次执行，返回flase代表已经执行过
	bool Clear(int nMark = INVALID_ID);
	bool ClearAll();
public:
	CMark(void);
	virtual ~CMark(void);
private:
	SetInt _vMark;
	mutable CMutexReadWrite _mutex;
};

NS_TOOL_FRAME_END
