#pragma once

#include "Macro.h"

NS_TOOL_FRAME_BEGIN

//进度条小工具
//循环模式,当前值超过极限值 那么 重置
//非循环模式,当前值超过极限值，则为极限值
class TOOLFRAME_DLL CSwitcherNumber 
{
public:
	bool	Init(int nCur,int nRangeBegin,int nRangeEnd,bool bLoop = true);
	bool	IsInitVaild()const;
	int		Add(int nValue = 1);
	int		Reduce(int nValue = -1);
	int		GetCur()const;
	bool	IsLoop()const;
public:
	bool	SetRangeInClosed(int nRangeBegin,int nRangeEnd);
	bool	SetRangeInOpen(int nRangeBegin,int nRangeEnd);
	bool	SetLoop(bool bLoop);
	int		SetCur(int nCur);
public:
	CSwitcherNumber ();
	CSwitcherNumber (int nCur,int nRangeBegin,int nRangeEnd);
	virtual ~CSwitcherNumber (void);
private:
	int		_nCur;
	int		_nRangeBegin;
	int		_nRangeEnd;
	bool	_bLoop;
};

NS_TOOL_FRAME_END
