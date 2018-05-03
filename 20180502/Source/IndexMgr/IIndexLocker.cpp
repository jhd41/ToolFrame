#include "IIndexLocker.h"
#include "ToolFrame.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

IIndexLocker::IIndexLocker(void)
{
}

IIndexLocker::~IIndexLocker(void)
{
}

bool IIndexLocker::Init()
{
	if (!InitLua())return false;
	if (!LoadLuaFile(GetLuaRule()))return false;
	if (!LoadArchFile())
	{
		ASSERT_LOG_ERROR(_luaEngine.CallFuction<bool>("OnInit"));
	}

	return true;
}

bool IIndexLocker::InitLua()
{
	if (!OnInitLua())return false;
		
	//¼ÓÔØlua_api
	return LoadLuaFile(GetLuaApi());
}

bool IIndexLocker::AddLuaApiFile( const std::string& sLuaFile )
{
	return ToolFrame::Insert(GetLuaApi(),sLuaFile);
}

bool IIndexLocker::AddLuaRuleFile( const std::string& sLuaFile )
{
	return ToolFrame::Insert(GetLuaRule(),sLuaFile); 
}

bool IIndexLocker::ApiTrace( std::string sMsg )
{
	LOG_LUA(sMsg);
	return true;
}

bool IIndexLocker::ApiUnlock_CPLUS( int nID )
{
	return Unlock(nID);
}

bool IIndexLocker::ApiIsUnLocked( int nID )
{
	return IsUnlocked(nID);
}

bool IIndexLocker::ApiSaveLockArchive()
{
	return Save();
}

CLuaEngine& IIndexLocker::GetLuaEngine()
{
	return _luaEngine;
}

bool IIndexLocker::LoadLuaFile( const VectorString& vFile )
{
	VectorString::const_iterator itr;
	foreach(itr,vFile){
		_luaEngine.DoString(ToolFrame::LoadFile(*itr));
	}

	return true;
}

bool IIndexLocker::OnInitLua()
{
	//×¢²álua
	_luaEngine.RegisterFunction("ApiTrace",				&IIndexLocker::ApiTrace,			this);
	_luaEngine.RegisterFunction("ApiUnlock_CPLUS",		&IIndexLocker::ApiUnlock_CPLUS,		this);
	_luaEngine.RegisterFunction("ApiIsUnLocked",		&IIndexLocker::ApiIsUnLocked,		this);
	_luaEngine.RegisterFunction("ApiSaveLockArchive",	&IIndexLocker::ApiSaveLockArchive,	this);

	return true;
}

bool IIndexLocker::SetArchiveFile( const std::string& sFile )
{
	return _archAccess.SetArchiveFile(sFile);
}

bool IIndexLocker::Save()
{
	return SaveArchFile();
}

NS_TOOL_FRAME_END
