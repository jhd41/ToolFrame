#include "IArchive.h"

NS_TOOL_FRAME_BEGIN

IArchive::IArchive(void)
{
}

IArchive::~IArchive(void)
{
}

uint IArchive::GetVersion() const
{
	return _uVer;
}

bool IArchive::SetVersion( uint uVer )
{
	_uVer = uVer;
	return true;
}

NS_TOOL_FRAME_END
