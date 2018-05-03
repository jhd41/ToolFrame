#pragma once

#include "Macro.h"
#include "IIndexLocker.h"

NS_TOOL_FRAME_BEGIN

class CIndexLocker
	:public IIndexLocker
{
public:
	virtual bool IsUnlocked(int nID)const;		//是否上锁
	virtual bool Unlock(uint nID);				//解锁
	virtual bool LoadArchFile();
	virtual bool SaveArchFile();
public:
	CIndexLocker(void);
	virtual ~CIndexLocker(void);
protected:
	CFIELD_REF(SetInt,Unlock,v);		//已经解锁的索引
};

NS_TOOL_FRAME_END
