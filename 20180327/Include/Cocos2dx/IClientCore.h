#pragma once

#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "TransitoryLinker.h"
#include "SceneFrameMgr.h"
#include "EventTrigger.h"
#include "HTimeOut.h"
#include "TimeOut.h"
#include "HLog.h"
#include "HSystem.h"
#include "ResolverCoreManager.h"
#include "UserConnector.h"
#include "IAnyObj.h"
#include "TObjCreator.h"

#include "MSystem.h"
//备注:
//渠道 三个渠道
//1.账号渠道:登陆的渠道。是 360登陆 还是QQ登陆 还是 短信注册 账号 还是 邮箱 还是 自己注册的官方。
//2.发布渠道:上架的渠道。 仅仅是提供我们上架的渠道，例如 是ios上架 还是移动MM上架 还是 和游戏上架 还是 游侠上架。
//3.推广渠道:销售的渠道。这表达的是 以何种方式 让玩家 安装上游戏的渠道。例如 是电脑城装机的方式。

//备注:
//使用的SDK未必是发布渠道的SDK，通常两者是相同的，但也有不同，例如使用 AnySDK 打包的 小米渠道包

//例子：一个玩家 去电脑城装机 电脑城 在装机的时候 给他安装上了 我们的 通过 和游戏上架的游戏。他的支付理所应当 也应该是使用的 和游戏支付方式进行支付。但是 他 在进入游戏时 却是 使用QQ的账号进行登录的，更坑的是 它可能是使用AnySDK打包的

//备注:windows 平台下 Debug模式 默认 会 检查 文件大小写,Release模式不检查
NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IClientCore
	:public ISystemInit
	,public HUserConnector
	,public HLog
	,public HSystem
	,public HSceneFrameMgr
	,public HEventTrigger
{
public:
	typedef TObjCreator<IAnyObj> AnyObjCreator;
public:
	virtual bool				SetServerAddress(const VectorString& vAddress);//设置服务器地址
	virtual bool				SetReconnect(int nReconnect = -1);		//设置重连次数默认为-1
	virtual bool				SetAllowMulit(bool bAllowMulit = false);//设置是否允许多开
	virtual bool				SetAutoPurgeCache(bool bAuto);			//设置自动回收缓存
	virtual bool				SetNetErrCode(int nNetErrCode);			//设置网络错误代号
	virtual bool				IsAutoPurgeCache()const;				//是否自动回收缓存
	virtual bool				Init();
	virtual bool				IsConnected()const;						//是否连接中
	virtual bool				Connect();								//开始连接服务器
	virtual bool				Disconnect(int nNetErrCode = NET_ERRCODE_ACTIVE,bool bClear = true);	//断开连接(主动,放弃未发送消息)
	virtual bool				SetAccountAnonymous();					//设置为默认账号 密码 渠道号
	virtual int					GetNetErrCode()const;					//获取网络错误代号
	virtual AnyObjCreator&		GetAnyObjCreator();
	virtual const AnyObjCreator& GetAnyObjCreator()const;

	//外部接口
public:
	virtual bool				OnPause();	//暂停
	virtual bool				OnResume();	//回到游戏
	virtual bool				OnScreenSizeChanged(int newWidth, int newHeight);
public:
	virtual bool				IsHasCachedMsg()const;	//是否还有缓存的协议
	virtual StreamBinaryPtr		PopCacheMsg();			//弹出缓存协议
	virtual bool				ProcessCachedMsg();		//处理缓存协议(一条)
	virtual bool				ProcessCachedMsgAll();	//处理缓存协议(所有)
	virtual bool				ClearChachedMsg(bool bCacheMsg = false);	//清理缓存协议 并 充值 缓存标记SetCacheMsg
	virtual int					PlaySound(const std::string& sSoundKey,bool bLoop = false)const;		//播放音效
	virtual int					PlayMusic(const std::string& sMusicKey,bool bLoop = true)const;			//播放音乐
	virtual const std::string&	GetSoundFile(const std::string& sSoundKey)const;
	virtual const std::string&	GetString(const std::string& sID)const;									//获取游戏提示文字
	virtual const std::string	GetString(const std::string& sID,const MapStringString& vString)const;	//获取游戏提示文字	
	
	virtual time_t				SetServerTime(time_t uTime);		//设置服务器时间
	virtual int					GetIntervalTime() const;			//获取获取客户端与服务器的时间差
	virtual time_t				GetServerTime()const;				//获取服务器时间
	virtual int					CalIntervalTime(time_t uTime)const;	//计算时间差

	//页面跳转
	virtual bool				SetGoToPage(int eGoToPage,int nArg1=0,int nArg2=0);
	virtual int					GetGoToPage()const;		//获取跳转页面 枚举值
	virtual int					GetGoToArg1()const;
	virtual int					GetGoToArg2()const;
	virtual bool				IsGoToPageVaild()const;	//是否需要跳转页面
	virtual bool				ClearGoToPage();		//清除跳转页面
public:
	virtual bool				SetState(int eState,int nArg1=0,int nArg2=0,int nArg3=0);
	virtual int					GetState()const;
	virtual int					GetStateArg1()const;
	virtual int					GetStateArg2()const;
	virtual int					GetStateArg3() const;
	virtual ISceneFrame*		FindRunningScene()const;
	virtual CEventTrigger&		GetEventTrigger();			//事件触发器
	virtual CSceneFrameMgr&		GetSceneMgr();				//场景管理器
	virtual CUserConnector&		GetConnector();				//连接器
	virtual bool				IsAllowMulit()const;		//是否允许多开
public:
	virtual bool				PushMsg(IMsgStream& msg,bool bSecret = true);		//压入队列发送
	virtual bool				PushMsg(StreamBinaryPtr ptr,bool bSecret = true);
	virtual bool				SendMsg(IMsgStream& msg,bool bSecret = true);		//直接发送
	virtual bool				SendMsg(StreamBinaryPtr ptr,bool bSecret = true);
	virtual bool				Send(IMsgStream& msg,bool bSecret = true);			//等同于PushMsg
	virtual bool				Send(StreamBinaryPtr ptr,bool bSecret = true);

	//结算
public:
	CResolverCoreManager&		GetResolverCoreMgr();
	const CResolverCoreManager&	GetResolverCoreMgr()const;

	//需要子类实现
public:
	virtual bool OnSaveArchive();		//保存存档
protected:
	virtual bool OnSceneChanged();		//当场景切换
	virtual bool OnRootPageChanged();	//当根页面切换
	virtual bool OnNewPageAdd(IPage* pPage);		//当新页面增加
	virtual bool OnNewPageInited(IPage* pPage);		//当新页面初始化完成
	virtual bool OnNewPageAllInited();			//当所有新页面初始化完成
protected:
	virtual bool OnConnected(uint uClientID);
	virtual bool OnConnectFaild(uint uClientID);
	virtual bool OnDisconnected(uint uClientID);
	virtual bool OnRefused(uint uClientID);
	virtual bool OnRecved(uint uClientID,IMsgStream& msgStream);
	virtual bool OnSend(StreamBinaryPtr ptr,bool bSecret);//当发送数据时

	//本类已处理
protected:
	virtual bool OnConnected		(CUserConnector* pConnector)override;
	virtual bool OnConnectFaild		(CUserConnector* pConnector)override;
	virtual bool OnDisconnected		(CUserConnector* pConnector)override;
	virtual bool OnRecvEncrypted	(CUserConnector* pConnector,IMsgStream& msgStream)override {return false;}				//处理明文
	virtual bool OnRecvDecrypted	(CUserConnector* pConnector,IMsgStream& msgStream)override;								//处理密文
	virtual bool OnEncrypt			(CUserConnector* pConnector,void* pBuffer, size_t uLength)override {return false;}
	virtual bool OnEncryptFailed	(CUserConnector* pConnector,void* pBuffer, size_t uLength)override {return false;}
	virtual bool OnDecrypt			(CUserConnector* pConnector,void* pBuffer, size_t uLength)override {return false;}
	virtual bool OnDecryptFailed	(CUserConnector* pConnector,void* pBuffer, size_t uLength)override {return false;}
	virtual bool OnStateChanged		(CUserConnector* pConnector,int eState)override {return false;}
	virtual bool OnRecved			(CUserConnector* pConnector,IMsgStream& msgStream)override {return false;}
	virtual bool OnSend				(CUserConnector* pConnector,StreamBinaryPtr ptr,bool bSecret)override;
	virtual bool OnRefused			(CUserConnector* pConnector)override;
	virtual bool OnHeartTimeOut		(CUserConnector* pConnector)override;													//心跳超时
	virtual bool OnKeepHeartTimeOut	(CUserConnector* pConnector)override;													//需要发心跳包时
protected:
	virtual bool OnRecved(uint uClientID,IMsgStream& msgStream,bool bCacheMsg );
protected:
	virtual bool OnSystemInit()override;					//系统初始化时
	virtual	bool OnSystemProcess(uint64 uTime)override;		//主循环回调
	virtual bool OnSystemCleanUp()override;					//系统清理(返回false阻止清理)
	virtual	bool OnSystemMemoryLow()override;				//内存不足(返回false阻止清理)
protected:
	virtual bool OnLogMsg(const std::string& sLogLevel,const std::stringstream& sStreamLog)override;//产生日志时(返回false阻止写日志)
protected:
	virtual bool OnEvent(const std::string& sEvent, const XEvent& xEvent)override;
public:
	CFIELD_INT(AppVer);					//游戏版本号
	CFIELD_STRING(AppVerString);		//游戏版本字符串
	CFIELD_INT(ResVer);					//资源版本号

	CFIELD_VECTOR_STRING(UpdateServerIP);		//更新服务器地址

	CFIELD_STRING(DeviceChannel);		//匿名注册渠道
	CFIELD_STRING(DeviceAccount);		//匿名账户
	CFIELD_STRING(DevicePassword);		//匿名密码

	CFIELD_INT(ZoneID);					//大区
	CFIELD_INT(ServerID);				//服务器

	CFIELD_STRING(Channel);				//账户渠道
	CFIELD_STRING(Account);				//账户账号
	CFIELD_STRING(Password);			//账户密码

	CFIELD_STRING(ReleaseChannelID);	//发布渠道
	CFIELD_STRING(PromotionChannelID);	//推广渠道

	CFIELD_STRING(SdkID);				//SDK ID

	CFIELD_BOOL(CacheMsg);				//缓存协议

	CFIELD_STRING(Title);				//窗口标题栏(windows)
	CFIELD_REF(CPoint2d,Resolution,pt);	//窗口分辨率(windows)

	CFIELD_BOOL(SleepFreeTime);			//是否需要在空闲时睡觉(性能优化 默认关闭 因为修改源码的方式更加高效)
public:
	IClientCore(void);
	virtual ~IClientCore(void);
protected:
	int					_nIntervalTime;	//客户端与服务器的时间差

	int					_eState;		//游戏状态
	int					_eStateArg1;	//游戏状态参数1
	int					_eStateArg2;	//游戏状态参数2
	int					_eStateArg3;	//游戏状态参数3

	CUserConnector		_xConnector;	//短连接连接器
	
	CSceneFrameMgr		_vSceneMgr;		//场景管理器

	bool				_bAllowMulit;	//允许多开

	ListStreamBinary	_vMsgCache;		//消息缓存

	MapStringString		_vString;		//游戏提示文字
	MapStringString		_vSound;		//游戏音效

	CResolverCoreManager _mgrResolver;	//结算核心

	//跳转页面
	int			_eGoToPage;
	int			_nGoToArg1;
	int			_nGoToArg2;

	AnyObjCreator	_vAnyObjCreator;
};

NS_TOOL_FRAME_END

#endif //MACRO_LIB_COCOS2D
