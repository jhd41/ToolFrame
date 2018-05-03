#include "IndexLocker.h"
#include "ToolFrame.h"
#include "IndexArchiveVer.h"

NS_TOOL_FRAME_BEGIN

CIndexLocker::CIndexLocker(void)
{

}

CIndexLocker::~CIndexLocker(void)
{
}

bool CIndexLocker::IsUnlocked( int nID ) const
{
	return ToolFrame::IsHasValue(GetUnlock(),nID);
}

bool CIndexLocker::Unlock( uint nID )
{
	if (IsUnlocked(nID))
		return false;
	
	return ToolFrame::Insert(GetUnlock(),nID);
}

bool CIndexLocker::LoadArchFile()
{
	CIndexArchiveVer1 arch;
	if (!_archAccess.Load(&arch))return false;
	_vUnlock = arch.vUnlocked;
	return true;
}

bool CIndexLocker::SaveArchFile()
{
	CIndexArchiveVer1 arch;
	arch.vUnlocked = _vUnlock;
	return _archAccess.Save(&arch);
}

NS_TOOL_FRAME_END

