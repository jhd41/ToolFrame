#pragma once

#include "Macro.h"
#include "IIndexLocker.h"

NS_TOOL_FRAME_BEGIN

class CIndexLocker
	:public IIndexLocker
{
public:
	virtual bool IsUnlocked(int nID)const;		//�Ƿ�����
	virtual bool Unlock(uint nID);				//����
	virtual bool LoadArchFile();
	virtual bool SaveArchFile();
public:
	CIndexLocker(void);
	virtual ~CIndexLocker(void);
protected:
	CFIELD_REF(SetInt,Unlock,v);		//�Ѿ�����������
};

NS_TOOL_FRAME_END
