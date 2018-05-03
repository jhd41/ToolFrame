#pragma once

#include "Macro.h"

//返回值助手:
//所有返回值中有一个 返回true 则 返回 true，否则 返回flase
NS_TOOL_FRAME_BEGIN
class CReturnOneTrue
{
public:
	bool	AddReturn(bool b);
	bool	GetReturn()const;
public:
	bool	operator += (bool b);
	operator bool(void)const;
public:
	CReturnOneTrue(void);
	virtual ~CReturnOneTrue(void);
private:
	bool	_bResult;
};

NS_TOOL_FRAME_END
