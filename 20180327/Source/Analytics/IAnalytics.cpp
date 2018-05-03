#include "IAnalytics.h"

#include "MAnalytics.h"

#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN
IAnalytics::IAnalytics(void)
{
	_nLevel		= 0;
	_eGender	= GENDER_INVAILD;
	_nAge		= 0;

	_bInited = false;

	MAnalytics::Singleton().Regist(this);
}

IAnalytics::~IAnalytics(void)
{
	MAnalytics::Singleton().UnRegist(this);
}

bool IAnalytics::OnStartUp()
{
	return true;
}

bool IAnalytics::OnPause()
{
	return true;
}

bool IAnalytics::OnResume()
{
	return true;
}

bool IAnalytics::OnExit()
{
	return true;
}

bool IAnalytics::SetAnonymous()
{
	return true;
}

bool IAnalytics::OnLevelUp( int nLevel )
{
	return true;
}

bool IAnalytics::OnAdvice(int eAdviceType, const std::string& sName, const std::string& sTel, const std::string& sContent, const std::string& sQQ)
{
	return true;
}

bool IAnalytics::OnLog(int eLogType, const std::string& sContent, const std::string& sArg1 /*= ""*/, const std::string& sArg2 /*= ""*/, const std::string& sArg3 /*= ""*/, const std::string& sArg4 /*= ""*/, const std::string& sArg5 /*= ""*/, int32 nArgValue /*= 0*/)
{
	return true;
}

bool IAnalytics::OnEvent( const std::string& sEvent )
{
	MapStringString vKeyValue;
	return OnEvent(sEvent, vKeyValue);
}

bool IAnalytics::OnEvent( const std::string& sEvent,const std::string& sKey,const std::string& sValue )
{
	MapStringString vKeyValue;
	ToolFrame::Insert(vKeyValue, sKey,sValue);
	return OnEvent(sEvent, vKeyValue);
}

bool IAnalytics::OnEvent( const std::string& sEvent,const MapStringString& vKeyValue )
{
	return true;
}

bool IAnalytics::OnEventEnd(const std::string& sEvent)
{
	MapStringString vKeyValue;
	return OnEventEnd(sEvent, vKeyValue);
}

bool IAnalytics::OnEventEnd(const std::string& sEvent, const std::string& sKey, const std::string& sValue)
{
	MapStringString vKeyValue;
	ToolFrame::Insert(vKeyValue, sKey, sValue);
	return OnEventEnd(sEvent, vKeyValue);
}

bool IAnalytics::OnEventEnd(const std::string& sEvent, const MapStringString& vKeyValue)
{
	return true;
}

bool IAnalytics::OnTaskBegin( const std::string& sTaskName )
{
	return true;
}

bool IAnalytics::OnTaskCompleted( const std::string& sTaskName )
{
	return true;
}

bool IAnalytics::OnTaskFailed( const std::string& sTaskName,const std::string& sReason )
{
	return true;
}

bool IAnalytics::SetLogEnabled( bool bEnable )
{
	return true;
}

bool IAnalytics::SetAppID( const std::string& sAppID )
{
	_sAppID = sAppID;
	return true;
}

bool IAnalytics::SetChannelID( const std::string& sChannelID )
{
	_sChannelID = sChannelID;
	return true;
}

bool IAnalytics::SetAppVer( const std::string& sAppVer )
{
	_sAppVer = sAppVer;
	return true;
}

bool IAnalytics::OnLogin()
{
	return true;
}

bool IAnalytics::OnLogout()
{
	return true;
}

bool IAnalytics::OnVirtualCurrencyGain( const std::string& sCurrencyType,uint uCount,const std::string& sSource/*=""*/ )
{
	return true;
}

bool IAnalytics::OnVirtualCurrencyUsed( const std::string& sCurrencyType,uint uCount,const std::string& sWay/*=""*/,const std::string& sArg1/*=""*/,const std::string& sArg2/*=""*/ )
{
	return true;
}

bool IAnalytics::OnItemRecv( const std::string& sItemID,uint uCount,const std::string& sSource/*=""*/ )
{
	return true;
}

bool IAnalytics::OnItemUsed( const std::string& sItemID,uint uCount,const std::string& sWay/*=""*/,const std::string& sArg1/*=""*/,const std::string& sArg2/*=""*/ )
{
	return true;
}

bool IAnalytics::OnEventBegin(const std::string& sEvent)
{
	MapStringString vKeyValue;
	return OnEventBegin(sEvent, vKeyValue);
}

bool IAnalytics::OnEventBegin(const std::string& sEvent, const std::string& sKey, const std::string& sValue)
{
	MapStringString vKeyValue;
	ToolFrame::Insert(vKeyValue, sKey, sValue);
	return OnEventBegin(sEvent, vKeyValue);
}

bool IAnalytics::OnEventBegin(const std::string& sEvent, const MapStringString& vKeyValue)
{
	return true;
}

bool IAnalytics::OnPayReq( const std::string& sOrderID,const std::string& sItemID,uint uItemCount,uint uMoney,const std::string& sPayCurrency,const std::string& sPayType,uint uVirtualCurrency/*=0*/ )
{
	return true;
}

bool IAnalytics::OnPayed( const std::string& sOrderID,const std::string& sPaySource/*=""*/,const std::string& sArg/*=""*/ )
{
	return true;
}

bool IAnalytics::OnPayFaild( const std::string& sOrderID,const std::string& sReason/*=""*/,const std::string& sArg/*=""*/ )
{
	return true;
}

bool IAnalytics::OnInit()
{
	return true;
}

bool IAnalytics::Init()
{
	if (_bInited)return true;

	_bInited = OnInit();
	return _bInited;
}

bool IAnalytics::IsInited() const
{
	return _bInited;
}

bool IAnalytics::SetUserID( const std::string& sUserID)
{
	_sUserID = sUserID;
	return true;
}

bool IAnalytics::SetAccount(const std::string& sAccount)
{
	_sAccount = sAccount;
	return true;
}

bool IAnalytics::SetAccountChannelID( const std::string& sAccountChannelID )
{
	_sAccountChannelID = sAccountChannelID;
	return true;
}

bool IAnalytics::SetLevel( int nLevel )
{
	_nLevel = nLevel;
	return true;
}

bool IAnalytics::SetGender( EGender eGender )
{
	_eGender = eGender;
	return true;
}

bool IAnalytics::SetAge( int nAge )
{
	_nAge = nAge;
	return true;
}

bool IAnalytics::SetGameServer( const std::string& sGameServer )
{
	_sGameServer = sGameServer;
	return true;
}

NS_TOOL_FRAME_END
