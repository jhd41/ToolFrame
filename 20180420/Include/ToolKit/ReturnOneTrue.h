#pragma once

#include "Macro.h"

//����ֵ����:
//���з���ֵ����һ�� ����true �� ���� true������ ����flase
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
