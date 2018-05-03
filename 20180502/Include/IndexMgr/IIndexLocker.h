#pragma once

#include "Macro.h"
#include "LuaEngine.h"
#include "IArchiveAccess.h"

NS_TOOL_FRAME_BEGIN

class IIndexLocker
{
public:
	virtual bool Init();
	virtual bool IsUnlocked(int nID)const=0;	//是否上锁
	virtual bool Unlock(uint nID)=0;			//解锁
protected:
	virtual bool LoadArchFile()=0;
	virtual bool SaveArchFile()=0;
public:
	virtual bool SetArchiveFile(const std::string& sFile);
	virtual bool AddLuaApiFile(const std::string& sLuaFile);
	virtual bool AddLuaRuleFile(const std::string& sLuaFile);
	virtual bool Save();
protected:
	virtual bool InitLua();
	virtual bool OnInitLua();//若要对初始化Lua进行补充 请继承
public:
	bool		ApiTrace(std::string sMsg);	//调试信息
	bool		ApiUnlock_CPLUS(int nID);	//解锁索引(索引ID)
	bool		ApiIsUnLocked(int nID);		//索引是否解锁
	bool		ApiSaveLockArchive();		//索引解锁器存档
public:
	CLuaEngine&	GetLuaEngine();
protected:
	bool		LoadLuaFile(const VectorString& vFile);
public:
	IIndexLocker(void);
	virtual ~IIndexLocker(void);
protected:
	CLuaEngine		_luaEngine;
	IArchiveAccess	_archAccess;
private:
	CFIELD_REF(VectorString,LuaApi,v);	//LuaApi文件
	CFIELD_REF(VectorString,LuaRule,v);	//Lua规则文件
};

NS_TOOL_FRAME_END