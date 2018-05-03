#include "ResolverCoreManager.h"
#include "ToolFrame.h"
#include "ResolverLua.h"
#include "ResolverOver.h"
#include "TimeOut.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

CResolverCoreManager::CResolverCoreManager(void)
{
	_bPost = false;
	_mgrEvent.RegistAll(this);

	_pLuaEngine = new CLuaEngine();
}

CResolverCoreManager::~CResolverCoreManager(void)
{
	ToolFrame::Delete(_pLuaEngine);
}

bool CResolverCoreManager::Init()
{
	if (!InitLua())return false;
	
	return true;
}

CLuaEngine& CResolverCoreManager::GetLuaEngine()
{
	return *_pLuaEngine;
}

const CLuaEngine& CResolverCoreManager::GetLuaEngine() const
{
	return *_pLuaEngine;
}

bool CResolverCoreManager::InitLua()
{
	_pLuaEngine->RegisterFunction("ApiTrace",				&CResolverCoreManager::ApiTrace,		this);
	_pLuaEngine->RegisterFunction("ApiLogLuaDebug",			&CResolverCoreManager::ApiLogLuaDebug,	this);
	_pLuaEngine->RegisterFunction("ApiLogLuaError",			&CResolverCoreManager::ApiLogLuaError,	this);
	_pLuaEngine->RegisterFunction("ApiLogSystem",			&CResolverCoreManager::ApiLogSystem,	this);

	_pLuaEngine->RegisterFunction("ApiTriggerEvent",		&CResolverCoreManager::ApiTriggerEvent,	this);
	_pLuaEngine->RegisterFunction("ApiTriggerEventWithInt",	&CResolverCoreManager::ApiTriggerEventWithInt,	this);
	_pLuaEngine->RegisterFunction("ApiTriggerEventWithString",&CResolverCoreManager::ApiTriggerEventWithString,	this);

	_pLuaEngine->RegisterFunction("ApiClearEventArg",		&CResolverCoreManager::ApiClearEventArg,	this);

	_pLuaEngine->RegisterFunction("ApiGetEventName",		&CResolverCoreManager::ApiGetEventName,	this);

	_pLuaEngine->RegisterFunction("ApiGetEventInt",			&CResolverCoreManager::ApiGetEventInt,	this);
	_pLuaEngine->RegisterFunction("ApiGetEventInt1",		&CResolverCoreManager::ApiGetEventInt1,	this);
	_pLuaEngine->RegisterFunction("ApiGetEventInt2",		&CResolverCoreManager::ApiGetEventInt2,	this);
	_pLuaEngine->RegisterFunction("ApiGetEventInt3",		&CResolverCoreManager::ApiGetEventInt3,	this);

	_pLuaEngine->RegisterFunction("ApiGetEventString",		&CResolverCoreManager::ApiGetEventString,this);
	_pLuaEngine->RegisterFunction("ApiGetEventString1",		&CResolverCoreManager::ApiGetEventString1,this);
	_pLuaEngine->RegisterFunction("ApiGetEventString2",		&CResolverCoreManager::ApiGetEventString2,this);
	_pLuaEngine->RegisterFunction("ApiGetEventString3",		&CResolverCoreManager::ApiGetEventString3,this);

	_pLuaEngine->RegisterFunction("ApiActionLua",			&CResolverCoreManager::ApiActionLua,	this);
	_pLuaEngine->RegisterFunction("ApiActionGameOver",		&CResolverCoreManager::ApiActionGameOver,this);
	return true;
}

bool CResolverCoreManager::LoadLuaFile( const std::string& sFile )
{
	return _pLuaEngine->DoString(ToolFrame::LoadFile(sFile));
}

bool CResolverCoreManager::LoadLua( const std::string& sLua )
{
	return _pLuaEngine->DoString(sLua);
}

bool CResolverCoreManager::ApiTrace( std::string sMsg )
{
	LOG_LUA(sMsg);
	return true;
}

bool CResolverCoreManager::ApiLogLuaDebug( std::string sMsg )
{
	LOG_LUA_DEBUG(sMsg);
	return true;
}

bool CResolverCoreManager::ApiLogLuaError( std::string sMsg )
{
	LOG_LUA_ERR(sMsg);
	return true;
}

bool CResolverCoreManager::ApiLogSystem( std::string sMsg )
{
	LOG_SYSTEM(sMsg);
	return true;
}

bool CResolverCoreManager::ApiTriggerEvent( std::string sEvent )
{
	return TriggleEvent(sEvent);
}

bool CResolverCoreManager::ApiTriggerEventWithInt( std::string sEvent,int nInt )
{
	return TriggleEvent(sEvent,nInt);
}

bool CResolverCoreManager::ApiTriggerEventWithString( std::string sEvent,std::string sArg )
{
	return TriggleEvent(sEvent,sArg);
}

std::string CResolverCoreManager::ApiGetEventName()
{
	return _xEvent.sEventType;
}

int CResolverCoreManager::ApiGetEventInt()
{
	return _xEvent.nArg1;
}

int CResolverCoreManager::ApiGetEventInt1()
{
	return _xEvent.nArg1;
}

int CResolverCoreManager::ApiGetEventInt2()
{
	return _xEvent.nArg2;
}

int CResolverCoreManager::ApiGetEventInt3()
{
	return _xEvent.nArg3;
}

std::string CResolverCoreManager::ApiGetEventString()
{
	return _xEvent.sArg1;
}

std::string CResolverCoreManager::ApiGetEventString1()
{
	return _xEvent.sArg1;
}

std::string CResolverCoreManager::ApiGetEventString2()
{
	return _xEvent.sArg2;
}

std::string CResolverCoreManager::ApiGetEventString3()
{
	return _xEvent.sArg3;
}

bool CResolverCoreManager::ApiActionLua( uint uIndex )
{
	CResolverLua* pResolver = CreateTopResolver<CResolverLua>(nullptr);
	if (!pResolver)return false;
	
	return pResolver->Init(uIndex);
}

bool CResolverCoreManager::ApiActionGameOver()
{
	CResolverOver* pResolver = CreateTopResolver<CResolverOver>(nullptr);
	if (!pResolver)return false;

	return true;
}

bool CResolverCoreManager::TriggleEvent( const std::string& sEventName )
{
	if (_bPost)
		return _mgrEvent.PostEvent(sEventName);

	return _mgrEvent.FireEvent(sEventName);
}

bool CResolverCoreManager::TriggleEvent( const std::string& sEventName,int nEventInt )
{
	if (_bPost)
		return _mgrEvent.PostEvent(sEventName,nEventInt);

	return _mgrEvent.FireEvent(sEventName,nEventInt);
}

bool CResolverCoreManager::TriggleEvent( const std::string& sEventName,int nEventInt1,int nEventInt2 )
{
	if (_bPost)
		return _mgrEvent.PostEvent(sEventName,nEventInt1,nEventInt2);

	return _mgrEvent.FireEvent(sEventName,nEventInt1,nEventInt2);
}

bool CResolverCoreManager::TriggleEvent( const std::string& sEventName,int nEventInt1,int nEventInt2,int nEventInt3 )
{
	if (_bPost)
		return _mgrEvent.PostEvent(sEventName,nEventInt1,nEventInt2,nEventInt3);

	return _mgrEvent.FireEvent(sEventName,nEventInt1,nEventInt2,nEventInt3);
}

bool CResolverCoreManager::TriggleEvent( const std::string& sEventName,const std::string& sEventString )
{
	if (_bPost)
		return _mgrEvent.PostEvent(sEventName,sEventString);

	return _mgrEvent.FireEvent(sEventName,sEventString);
}

bool CResolverCoreManager::TriggleEvent( const std::string& sEventName,const std::string& sEventString1,const std::string& sEventString2 )
{
	if (_bPost)
		return _mgrEvent.PostEvent(sEventName,sEventString1,sEventString2);

	return _mgrEvent.FireEvent(sEventName,sEventString1,sEventString2);
}

bool CResolverCoreManager::TriggleEvent( const std::string& sEventName,const std::string& sEventString1,const std::string& sEventString2,const std::string& sEventString3 )
{
	if (_bPost)
		return _mgrEvent.PostEvent(sEventName,sEventString1,sEventString2,sEventString3);

	return _mgrEvent.FireEvent(sEventName,sEventString1,sEventString2,sEventString3);
}

bool CResolverCoreManager::TriggleEvent( const std::string& sEventName,void* pAc )
{
	if (_bPost)
		return _mgrEvent.PostEvent(sEventName,pAc);

	return _mgrEvent.FireEvent(sEventName,pAc);
}

bool CResolverCoreManager::TriggleEvent( const XEvent& xEvent )
{
	if (_bPost)
		return _mgrEvent.PostEvent(xEvent);

	return _mgrEvent.FireEvent(xEvent);
}

bool CResolverCoreManager::ClearEventArg()
{
	_xEvent = XEvent();
	_xEvent.pArg = nullptr;
	return true;
}

bool CResolverCoreManager::OnEvent( const std::string& sEvent,const XEvent& xEvent )
{
	_xEvent = xEvent;
	TriggleLuaEvent(sEvent);
	return true;
}

bool CResolverCoreManager::TriggleLuaEvent( const std::string& sEventName )
{
	if (sEventName.empty())return false;

	//触发Lua事件
	try{
		_pLuaEngine->CallFuction<void>("CPlus_OnEvent",sEventName);
	}catch(std::exception& e){
		LOG_ERROR_MSG(e.what());
		return false;
	}
	return true;
}

bool CResolverCoreManager::ApiClearEventArg()
{
	return ClearEventArg();
}

bool CResolverCoreManager::RegistEvent( const std::string& sEvent,HEventTrigger* hEvent )
{
	return _mgrEvent.Regist(sEvent,hEvent);
}

bool CResolverCoreManager::UnregistEvent( const std::string& sEvent,HEventTrigger* hEvent )
{
	return _mgrEvent.Unregist(sEvent,hEvent);
}

bool CResolverCoreManager::RegistAllEvent( HEventTrigger* hEvent )
{
	return _mgrEvent.RegistAll(hEvent);
}

bool CResolverCoreManager::UnregistAllEvent( HEventTrigger* hEvent )
{
	return _mgrEvent.UnregistAll(hEvent);
}

int CResolverCoreManager::SafeUnregistEvent( HEventTrigger* hEvent )
{
	return _mgrEvent.SafeUnregist(hEvent);
}

bool CResolverCoreManager::EnableTriggerEvent( bool bEnabled )
{
	return _mgrEvent.EnableTriggerEvent(bEnabled);
}

bool CResolverCoreManager::IsEnableTriggerEvent() const
{
	return _mgrEvent.IsEnableTriggerEvent();
}

bool CResolverCoreManager::ProcessOne( uint64 uMillSeconds /*= 0*/ )
{
	CTimeOut timeout(uMillSeconds);

	if (IsProcessed())return true;

	//先处理事件 再处理阶段
	_mgrEvent.ProcessEvent(timeout.TimeRemaining());
	if (timeout.IsTimeOut())return false;
	
	return IResolverManager::ProcessOne(timeout.TimeRemaining());
}

bool CResolverCoreManager::IsProcessed() const
{
	return _mgrEvent.IsEventQueueEmpty() && IResolverManager::IsProcessed();
}

bool CResolverCoreManager::SetEventPost( bool bPost )
{
	_bPost = bPost;
	return true;
}

bool CResolverCoreManager::IsEventPost() const
{
	return _bPost;
}

bool CResolverCoreManager::ResetLuaEngine()
{
	ToolFrame::Delete(_pLuaEngine);
	_pLuaEngine = new CLuaEngine();
	return true;
}

NS_TOOL_FRAME_END