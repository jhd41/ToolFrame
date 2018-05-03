#pragma once

#include "Macro.h"
#include "LuaEngine.h"
#include "IArchiveAccess.h"

NS_TOOL_FRAME_BEGIN

class IIndexLocker
{
public:
	virtual bool Init();
	virtual bool IsUnlocked(int nID)const=0;	//�Ƿ�����
	virtual bool Unlock(uint nID)=0;			//����
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
	virtual bool OnInitLua();//��Ҫ�Գ�ʼ��Lua���в��� ��̳�
public:
	bool		ApiTrace(std::string sMsg);	//������Ϣ
	bool		ApiUnlock_CPLUS(int nID);	//��������(����ID)
	bool		ApiIsUnLocked(int nID);		//�����Ƿ����
	bool		ApiSaveLockArchive();		//�����������浵
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
	CFIELD_REF(VectorString,LuaApi,v);	//LuaApi�ļ�
	CFIELD_REF(VectorString,LuaRule,v);	//Lua�����ļ�
};

NS_TOOL_FRAME_END