#include "MAnalytics.h"
#include "ReturnAllTrue.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN
	
MAnalytics::MAnalytics(void)
{
}

MAnalytics::~MAnalytics(void)
{
}

bool MAnalytics::OnStartUp()
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnStartUp();
	}

	return r;
}

bool MAnalytics::OnPause()
{
	CReturnAllTrue r;
	
	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnPause();
	}

	return r;
}


bool MAnalytics::OnResume()
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnResume();
	}

	return r;
}

bool MAnalytics::OnExit()
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnExit();
	}

	return r;
}

bool MAnalytics::SetAnonymous()
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->SetAnonymous();
	}

	return r;
}

bool MAnalytics::OnEvent( const std::string& sEvent )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnEvent(sEvent);
	}

	return r;
}

bool MAnalytics::OnEvent( const std::string& sEvent,const std::string& sKey,const std::string& sValue )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnEvent(sEvent,sKey,sValue);
	}

	return r;
}

bool MAnalytics::OnEvent( const std::string& sEvent,const MapStringString& vKeyValue )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnEvent(sEvent,vKeyValue);
	}

	return r;
}

bool MAnalytics::OnEventEnd(const std::string& sEvent)
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr, _vAnalytics) {
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnEventEnd(sEvent);
	}

	return r;
}

bool MAnalytics::OnEventEnd(const std::string& sEvent, const std::string& sKey, const std::string& sValue)
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr, _vAnalytics) {
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnEventEnd(sEvent, sKey, sValue);
	}

	return r;
}

bool MAnalytics::OnEventEnd(const std::string& sEvent, const MapStringString& vKeyValue)
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr, _vAnalytics) {
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnEventEnd(sEvent, vKeyValue);
	}

	return r;
}

bool MAnalytics::OnTaskBegin( const std::string& sTaskName )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnTaskBegin(sTaskName);
	}

	return r;
}

bool MAnalytics::OnTaskCompleted( const std::string& sTaskName )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnTaskCompleted(sTaskName);
	}

	return r;
}

bool MAnalytics::OnTaskFailed( const std::string& sTaskName,const std::string& sReason )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnTaskFailed(sTaskName,sReason);
	}

	return r;
}

bool MAnalytics::SetLogEnabled( bool bEnable )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->SetLogEnabled(bEnable);
	}

	return r;
}

MAnalytics::VectorAnalytics& MAnalytics::GetAnalytics()
{
	return _vAnalytics;
}

const MAnalytics::VectorAnalytics& MAnalytics::GetAnalytics() const
{
	return _vAnalytics;
}

bool MAnalytics::Regist(IAnalytics* pAnalytics)
{
	if (!pAnalytics)return false;
	return ToolFrame::Insert(_vAnalytics, pAnalytics);
}

bool MAnalytics::UnRegist(IAnalytics* pAnalytics)
{
	if (!pAnalytics)return false;
	return ToolFrame::EraseByValue(_vAnalytics, pAnalytics);
}

bool MAnalytics::OnLogin(const std::string& sUserID, const std::string& sAccount, const std::string& sChannelID)
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr, _vAnalytics) {
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init()) {
			pAnalytics->SetUserID(sUserID);
			pAnalytics->SetAccount(sAccount);
			pAnalytics->SetAccountChannelID(sChannelID);

			r += pAnalytics->OnLogin();
		}
	}

	return r;
}

bool MAnalytics::OnLogout()
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init()){
			r += pAnalytics->OnLogout();
		}
	}

	return r;
}

bool MAnalytics::OnVirtualCurrencyGain( const std::string& sCurrencyType,uint uCount,const std::string& sSource/*=""*/ )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnVirtualCurrencyGain(sCurrencyType,uCount,sSource);
	}

	return r;
}

bool MAnalytics::OnVirtualCurrencyUsed( const std::string& sCurrencyType,uint uCount,const std::string& sWay/*=""*/,const std::string& sArg1/*=""*/,const std::string& sArg2/*=""*/ )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnVirtualCurrencyUsed(sCurrencyType,uCount,sWay,sArg1,sArg2);
	}

	return r;
}

bool MAnalytics::OnItemRecv( const std::string& sItemID,uint uCount,const std::string& sSource/*=""*/ )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnItemRecv(sItemID,uCount,sSource);
	}

	return r;
}

bool MAnalytics::OnItemUsed( const std::string& sItemID,uint uCount,const std::string& sWay/*=""*/,const std::string& sArg1/*=""*/,const std::string& sArg2/*=""*/ )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnItemUsed(sItemID,uCount,sWay,sArg1,sArg2);
	}

	return r;
}

bool MAnalytics::OnEventBegin(const std::string& sEvent)
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr, _vAnalytics) {
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnEventBegin(sEvent);
	}

	return r;
}

bool MAnalytics::OnEventBegin(const std::string& sEvent, const std::string& sKey, const std::string& sValue)
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr, _vAnalytics) {
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnEventBegin(sEvent, sKey, sValue);
	}

	return r;
}

bool MAnalytics::OnEventBegin(const std::string& sEvent, const MapStringString& vKeyValue)
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr, _vAnalytics) {
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnEventBegin(sEvent, vKeyValue);
	}

	return r;
}

bool MAnalytics::OnPayReq( const std::string& sOrderID,const std::string& sItemID,uint uItemCount,uint uMoney,const std::string& sPayCurrency,const std::string& sPayType,uint uVirtualCurrency/*=0*/ )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnPayReq(sOrderID,sItemID,uItemCount,uMoney,sPayCurrency,sPayType,uVirtualCurrency);
	}

	return r;
}

bool MAnalytics::OnPayed( const std::string& sOrderID,const std::string& sPaySource/*=""*/,const std::string& sArg/*=""*/ )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnPayed(sOrderID,sPaySource,sArg);
	}

	return r;
}

bool MAnalytics::OnPayFaild( const std::string& sOrderID,const std::string& sReason/*=""*/,const std::string& sArg/*=""*/ )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnPayFaild(sOrderID,sReason,sArg);
	}

	return r;
}

bool MAnalytics::OnLevelUp( int nLevel )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnLevelUp(nLevel);
	}

	return r;
}

bool MAnalytics::SetLevel( int nLevel )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);
		r += pAnalytics->SetLevel(nLevel);
	}
	return r;
}

bool MAnalytics::SetGender( EGender eGender )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);
		r += pAnalytics->SetGender(eGender);
	}
	return r;
}

bool MAnalytics::SetAge( int nAge )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);
		r += pAnalytics->SetAge(nAge);
	}
	return r;
}

bool MAnalytics::SetGameServer( const std::string& sServerName )
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr,_vAnalytics){
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);
		r += pAnalytics->SetGameServer(sServerName);
	}
	return r;
}

bool MAnalytics::SetChannelID(const std::string& sChannel)
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr, _vAnalytics) {
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);
		r += pAnalytics->SetChannelID(sChannel);
	}
	return r;
}

bool MAnalytics::OnAdvice(int eAdviceType, const std::string& sName, const std::string& sTel, const std::string& sContent, const std::string& sQQ)
{
	CReturnAllTrue r;

	VectorAnalytics::const_iterator itr;
	foreach(itr, _vAnalytics) {
		IAnalytics* pAnalytics = *itr;
		ASSERT_LOG_ERROR(pAnalytics);

		if (pAnalytics->Init())
			r += pAnalytics->OnAdvice(eAdviceType,sName, sTel, sContent, sQQ);
	}

	return r;
}

NS_TOOL_FRAME_END
