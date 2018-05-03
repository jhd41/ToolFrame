#pragma once
#include "Macro.h"

NS_TOOL_FRAME_BEGIN

class CIndexMgr
{
public:
	bool				Init();
	const std::string&	GetFile(int nID)const;
	const MapIntString& GetIndex()const;
	size_t				GetIndexSize()const;
public:
	CIndexMgr(void);
	virtual ~CIndexMgr(void);
private:
	MapIntString	_vIndex;
private:
	CFIELD_STRING(IndexFile);
};

NS_TOOL_FRAME_END
