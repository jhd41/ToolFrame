#pragma once

#include "Macro.h"
//����ֵ����:
//���з���ֵ��Ϊtrueʱ ���� true������ ����flase

NS_TOOL_FRAME_BEGIN

class CReturnAllTrue
{
public:
	bool	AddReturn(bool b);
	bool	GetReturn()const;
public:
	bool	operator += (bool b);
	operator bool(void)const;
public:
	CReturnAllTrue(void);
	virtual ~CReturnAllTrue(void);
private:
	bool	_bResult;
};

NS_TOOL_FRAME_END
