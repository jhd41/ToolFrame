#pragma once
#include "IArchive.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

struct CIndexArchiveVer1
	:public IArchive
{
	ARCHIVE_SERIALIZE(CIndexArchiveVer1,1,vUnlocked);
public:
	SetInt vUnlocked;
};

NS_TOOL_FRAME_END
