#include "IClientCore.h"

#ifdef MACRO_LIB_COCOS2D

#include "MProtocol.h"
#include "MSystem.h"
#include "MAnalytics.h"

#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

IClientCore::IClientCore(void)
{
	MAnalytics::Singleton();
	
	_eState = INVALID_ID;
	_eStateArg1 = 0;
	_eStateArg2 = 0;
	_eStateArg3 = 0;

	_eGoToPage = INVALID_ID;
	_nGoToArg1 = 0;
	_nGoToArg2 = 0;

	_nIntervalTime =0;

	_bAllowMulit = false;

	_xConnector.SetHandler(this);
	_vSceneMgr.SetHandler(this);

	SetCacheMsg(false);

	SetDeviceChannel(ToolFrame::GetPlatformString());
	SetDeviceAccount(ToolFrame::GetDeviceID());
	SetDevicePassword("Anonymous");

	SetZoneID(INVALID_ID);
	SetServerID(INVALID_ID);
	SetChannel(GetDeviceChannel());
	SetAccount(GetDeviceAccount());
	SetPassword(GetDevicePassword());

	SetAppVer(1);
	SetAppVerString("1.0.0.0");
	SetResVer(1);

	SetGameID(INVALID_ID);

	SetSleepFreeTime(false);

	//设置检查文件路径
	ToolFrame::SetCheckFileCaseSensitive(MACRO_OS_WINDOWS == ToolFrame::GetPlatform() && ToolFrame::IsDebugVer());

	MSystem::Singleton().GetEventTrigger().RegistAll(this);
}

IClientCore::~IClientCore(void)
{
	OnSaveArchive();

	MAnalytics::Singleton().OnExit();

	MSystem::Singleton().GetEventTrigger().UnregistAll(this);
}

bool IClientCore::Init()
{
	if (!IsAllowMulit() && ToolFrame::IsExecutedMulit())return false;

	MSystem::Singleton().SetHandler(this);
	MLoger::Singleton().SetHandler(this);

	MSystem::Singleton().GetThread().GetTaskMgr().AddTaskThread(1, 10);

	MProtocol::Singleton().AddNetTaskThread(3);

	MSystem::Singleton().Init();

	MAnalytics::Singleton().OnStartUp();
	
	_xConnector.StartHeartCheck();	
	return true;
}

CEventTrigger& IClientCore::GetEventTrigger()
{
	return MSystem::Singleton().GetEventTrigger();
}

CSceneFrameMgr& IClientCore::GetSceneMgr()
{
	return _vSceneMgr;
}

CUserConnector& IClientCore::GetConnector()
{
	return _xConnector;
}

ISceneFrame* IClientCore::FindRunningScene() const
{
	return _vSceneMgr.GetScene();
}

bool IClientCore::IsConnected() const
{
	return _xConnector.IsConnected();
}

bool IClientCore::Connect()
{
	return _xConnector.Connect();
}

bool IClientCore::Disconnect( int nNetErrCode /*= NET_ERRCODE_ACTIVE*/,bool bClear /*= true*/ )
{
	LOG_DEBUG("Disconnect NetErrCode:"<< nNetErrCode);
	return _xConnector.Disconnect(nNetErrCode, bClear);
}

int IClientCore::GetState() const
{
	return _eState;
}

int IClientCore::GetStateArg1() const
{
	return _eStateArg1;
}

int IClientCore::GetStateArg2() const
{
	return _eStateArg2;
}

int IClientCore::GetStateArg3() const
{
	return _eStateArg3;
}

bool IClientCore::SetState( int eState,int nArg1/*=0*/,int nArg2/*=0*/,int nArg3/*=0*/ )
{
	_eState		= eState;
	_eStateArg1 = nArg1;
	_eStateArg2 = nArg2;
	_eStateArg3 = nArg3;
	return true;
}

bool IClientCore::PushMsg( IMsgStream& msg,bool bSecret /*= true*/ )
{
	return PushMsg(msg.GetSendStream(),bSecret);
}

bool IClientCore::PushMsg(StreamBinaryPtr ptr,bool bSecret /*= true*/ )
{
	if (!ptr)return false;

	return _xConnector.Push(ptr,bSecret);
}

bool IClientCore::SendMsg( IMsgStream& msg,bool bSecret)
{
	return SendMsg(msg.GetSendStream(),bSecret);
}

bool IClientCore::SendMsg(StreamBinaryPtr ptr,bool bSecret )
{
	if (!ptr)return false;

	return _xConnector.Send(ptr,bSecret);
}

bool IClientCore::OnConnected( uint uClientID )
{
	ISceneFrame* pScene = FindRunningScene();
	if (pScene)
		pScene->OnConnected(uClientID);

	return true;
}

bool IClientCore::OnConnected(CUserConnector* pConnector )
{
	return OnConnected(pConnector->GetClientID());
}

bool IClientCore::OnDisconnected( uint uClientID )
{
	//界面显示
	ISceneFrame* pScene = FindRunningScene();
	if (pScene)
		pScene->OnDisconnected(uClientID);

	return true;
}

bool IClientCore::OnRefused(uint uClientID)
{
	return true;
}

bool IClientCore::OnDisconnected(CUserConnector* pConnector )
{
	ASSERT_LOG_ERROR(pConnector);
	return OnDisconnected(pConnector->GetClientID());
}

bool IClientCore::OnRecvDecrypted(CUserConnector* pConnector,IMsgStream& msgStream )
{
	if (!pConnector)return false;

	OnRecved(pConnector->GetClientID(),msgStream,IsCacheMsg());
	return true;
}

bool IClientCore::OnRecved( uint uClientID,IMsgStream& msgStream,bool bCacheMsg )
{
	if (bCacheMsg || _vSceneMgr.IsHasNewPage())
	{
		_vMsgCache.push_back(msgStream.GetSendStream());
		return true;
	}

	return OnRecved(uClientID,msgStream);	
}

bool IClientCore::OnRecved( uint uClientID,IMsgStream& msgStream )
{
	//界面显示
	ISceneFrame* pScene = FindRunningScene();
	if (pScene)
		pScene->OnRecv(uClientID,msgStream);

	//尝试初始化
	_vSceneMgr.TryInitPage();
	return false;
}

bool IClientCore::OnHeartTimeOut(CUserConnector* pConnector)
{
	Disconnect(NET_ERRCODE_HEART_TIMEOUT);
	return true;
}

bool IClientCore::OnKeepHeartTimeOut(CUserConnector* pConnector)
{
	return true;
}

bool IClientCore::SetServerAddress( const VectorString& vAddress )
{
	return _xConnector.SetServerAddress(vAddress);
}

IClientCore::AnyObjCreator& IClientCore::GetAnyObjCreator()
{
	return _vAnyObjCreator;
}

const IClientCore::AnyObjCreator& IClientCore::GetAnyObjCreator() const
{
	return _vAnyObjCreator;
}

bool IClientCore::OnPause()
{
	//暂停声音
	ApiCocos2dx::SetAudioPauseAll(true);

	MAnalytics::Singleton().OnPause();

	ISceneFrame* pScene = GetSceneMgr().GetScene();
	if (pScene)
		pScene->OnPause();
	
	OnSaveArchive();
	return true;
}

bool IClientCore::OnResume()
{
	ApiCocos2dx::SetAudioPauseAll(false);

	MAnalytics::Singleton().OnResume();

	ISceneFrame* pScene = GetSceneMgr().GetScene();
	if (pScene)
		pScene->OnResume();

	return true;
}

bool IClientCore::OnSaveArchive()
{
	return false;
}

bool IClientCore::SetAllowMulit( bool bAllowMulit /*= false*/ )
{
	_bAllowMulit = bAllowMulit;
	return true;
}

bool IClientCore::IsAllowMulit() const
{
	return _bAllowMulit;
}

bool IClientCore::OnSystemInit()
{
	return true;
}

bool IClientCore::OnSystemProcess(uint64 uTime)
{
	MProtocol::Singleton().ProcessLogic(uTime);//处理协议
	_mgrResolver.Process();//处理结算器
	_vSceneMgr.TryInitPage();//展现页面
	if (IsSleepFreeTime())
		ApiCocos2dx::SleepFreeTime();//优化性能
	return true;
}

bool IClientCore::OnSystemCleanUp()
{
	LOG_SYSTEM("IClientCore::OnSystemCleanUp");
	
	ApiCocos2dx::PurgeTextureCache(true);				//清理图片
	ToolFrame::PurgeMemory(ToolFrame::GetProcessId());	//清理当前进程内存
	return true;
}

bool IClientCore::OnSystemMemoryLow()
{
	LOG_SYSTEM("IClientCore::OnSystemMemoryLow");
	return true;
}

bool IClientCore::OnLogMsg( const std::string& sLogLevel,const std::stringstream& sStreamLog )
{
	return true;
}

bool IClientCore::OnEvent(const std::string& sEvent, const XEvent& xEvent)
{
	if (EVENT_TF_SYSTEM_NET_CHANGE == sEvent)
	{
		Disconnect(NET_ERRCODE_RECV);
		return true;
	}
	
	return false;
}

bool IClientCore::IsHasCachedMsg() const
{
	return !ToolFrame::IsEmpty(_vMsgCache);
}

StreamBinaryPtr IClientCore::PopCacheMsg()
{
	return ToolFrame::PopPtr(_vMsgCache);
}

bool IClientCore::ProcessCachedMsg()
{
	if (_vSceneMgr.IsHasNewPage())return false;	//如果页面没有初始化好

	StreamBinaryPtr pMsg = PopCacheMsg();
	if (!pMsg)return false;

	IMsgStream msgStream(pMsg);
	ASSERT_LOG_ERROR(msgStream.LoadBegin());

	OnRecved(INVALID_ID,msgStream);
	return true;
}

bool IClientCore::ProcessCachedMsgAll()
{
	while (ProcessCachedMsg());
	return true;
}

const std::string& IClientCore::GetSoundFile(const std::string& sSoundKey) const
{
	return ToolFrame::GetValueByKey(_vSound,sSoundKey,ToolFrame::EmptyString());
}

int IClientCore::PlaySound( const std::string& sSoundKey,bool bLoop)const
{
	if (ApiCocos2dx::IsSoundMute())return experimental::AudioEngine::INVALID_AUDIO_ID;
	return ApiCocos2dx::PlaySound(GetSoundFile(sSoundKey),bLoop);
}

int IClientCore::PlayMusic( const std::string& sMusicKey,bool bLoop )const
{
	if (ApiCocos2dx::IsMusicMute())return experimental::AudioEngine::INVALID_AUDIO_ID;
	return  ApiCocos2dx::PlayMusic(GetSoundFile(sMusicKey),bLoop);
}

const std::string& IClientCore::GetString( const std::string& sID ) const
{
	return ToolFrame::GetValueByKey(_vString,sID,ToolFrame::EmptyString());
}

const std::string IClientCore::GetString( const std::string& sID,const MapStringString& vString ) const
{
	std::string sTemplate = GetString(sID);
	if (sTemplate.empty())return ToolFrame::EmptyString();

	ToolFrame::Replace(sTemplate,vString);
	return sTemplate;
}

int IClientCore::GetIntervalTime() const
{
	return _nIntervalTime;
}

time_t IClientCore::GetServerTime() const
{
	return _nIntervalTime + ToolFrame::GetNowTime();
}

int IClientCore::CalIntervalTime( time_t uTime ) const
{
	return ToolFrame::Difference(uTime,ToolFrame::GetNowTime());
}

time_t IClientCore::SetServerTime( time_t uTime )
{
	_nIntervalTime = CalIntervalTime(uTime);
	return uTime;
}

bool IClientCore::OnScreenSizeChanged( int newWidth, int newHeight )
{
	ApiCocos2dx::SwitchScreen(newWidth >= newHeight);

	ISceneFrame* pScene = FindRunningScene();
	if (pScene)
		pScene->OnScreenSizeChanged(newWidth,newHeight);
	
	return true;
}

bool IClientCore::SetAccountAnonymous()
{
	SetChannel(GetDeviceChannel());
	SetAccount(GetDeviceAccount());
	SetPassword(GetDevicePassword());
	return true;
}

int IClientCore::GetNetErrCode() const
{
	return _xConnector.GetNetErrCode();
}

bool IClientCore::SetReconnect(int nReconnect /*= -1*/)
{
	return _xConnector.SetReconnectMax(nReconnect);
}

bool IClientCore::ClearChachedMsg( bool bCacheMsg /*= false*/ )
{
	SetCacheMsg(bCacheMsg);
	ToolFrame::Clear(_vMsgCache);
	return true;
}

CResolverCoreManager& IClientCore::GetResolverCoreMgr()
{
	return _mgrResolver;
}

const CResolverCoreManager& IClientCore::GetResolverCoreMgr() const
{
	return _mgrResolver;
}

bool IClientCore::OnSceneChanged()
{
	return false;
}

bool IClientCore::OnRootPageChanged()
{
	return false;
}

bool IClientCore::OnSend(StreamBinaryPtr ptr,bool bSecret)
{
	return true;
}

bool IClientCore::OnSend( CUserConnector* pConnector, StreamBinaryPtr ptr,bool bSecret )
{
	//回调
	return OnSend(ptr,bSecret);
}

bool IClientCore::OnRefused(CUserConnector* pConnector)
{
	return OnRefused(pConnector->GetClientID());
}

bool IClientCore::OnConnectFaild(uint uClientID)
{
	ISceneFrame* pScene = FindRunningScene();
	if (pScene)
		pScene->OnConnectFailed(uClientID);

	return true;
}

bool IClientCore::OnConnectFaild( CUserConnector* pConnector )
{
	ASSERT_LOG_ERROR(pConnector);
	return OnConnectFaild(pConnector->GetClientID());
}

bool IClientCore::OnNewPageAdd( IPage* pPage )
{
	return true;
}

bool IClientCore::OnNewPageInited( IPage* pPage )
{
	return true;
}

bool ToolFrame::IClientCore::OnNewPageAllInited()
{
	//接着处理未处理协议
	if (!IsCacheMsg())
		ProcessCachedMsgAll();

	return true;
}

bool IClientCore::Send(IMsgStream& msg, bool bSecret /*= true*/)
{
	return PushMsg(msg,bSecret);
}

bool IClientCore::Send(StreamBinaryPtr ptr,bool bSecret /*= true*/ )
{
	return PushMsg(ptr,bSecret);
}

bool IClientCore::SetAutoPurgeCache( bool bAuto )
{
	return ApiCocos2dx::SetAutoPurgeCache(bAuto);
}

bool IClientCore::SetNetErrCode(int nNetErrCode)
{
	return _xConnector.SetNetErrCode(nNetErrCode);
}

bool IClientCore::IsAutoPurgeCache()const
{
	return ApiCocos2dx::IsAutoPurgeCache();
}

int IClientCore::GetGoToPage() const
{
	return _eGoToPage;
}

int IClientCore::GetGoToArg1() const
{
	return _nGoToArg1;
}

int IClientCore::GetGoToArg2() const
{
	return _nGoToArg2;
}

bool IClientCore::SetGoToPage( int eGoToPage,int nArg1/*=0*/,int nArg2/*=0*/ )
{
	_eGoToPage = eGoToPage;
	_nGoToArg1 = nArg1;
	_nGoToArg2 = nArg2;
	return true;
}

bool IClientCore::ClearGoToPage()
{
	_eGoToPage = INVALID_ID;
	_nGoToArg1 = 0;
	_nGoToArg2 = 0;

	return true;
}

bool IClientCore::IsGoToPageVaild() const
{
	return INVALID_ID != _eGoToPage;
}

NS_TOOL_FRAME_END

#endif //MACRO_LIB_COCOS2D
