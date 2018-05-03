#pragma once
#include "MacroAnalytics.h"
#include "IAnyObj.h"

NS_TOOL_FRAME_BEGIN

//统计接口
class TOOLFRAME_DLL IAnalytics
	:public IAnyObj
{
	//外部接口调用
public:
	virtual bool Init();			//请求初始化
	virtual bool IsInited()const;	//是否已经初始化

	//子类继承
public://账户管理
	virtual bool SetAnonymous();//设置匿名账号
	virtual bool OnLogin();		//登陆
	virtual bool OnLogout();	//登出
public:
	virtual bool OnInit();		//初始化

	virtual bool OnStartUp();	//启动	
	virtual bool OnPause();		//暂停
	virtual bool OnResume();	//回到游戏
	virtual bool OnExit();		//离开

	//支付
	virtual bool OnPayReq(const std::string& sOrderID,const std::string& sItemID,uint uItemCount,uint uMoney,const std::string& sPayCurrency,const std::string& sPayType,uint uVirtualCurrency=0);//支付(支付方式EPayType 币种ECurrency 金额 单位分) sProductID(用户自定义)
	virtual bool OnPayed(const std::string& sOrderID,const std::string& sPaySource="",const std::string& sArg="");
	virtual bool OnPayFaild(const std::string& sOrderID,const std::string& sReason="",const std::string& sArg="");
	
	//虚拟币分析 获得 与 消耗
	virtual bool OnVirtualCurrencyGain(const std::string& sCurrencyType,uint uCount,const std::string& sSource="");															//虚拟币 币种,数量，来源
	virtual bool OnVirtualCurrencyUsed(const std::string& sCurrencyType,uint uCount,const std::string& sWay="",const std::string& sArg1="",const std::string& sArg2="");	//虚拟币 币种,数量，途径(例如使用 钻石 3个 购买物品 买了3个5号道具)

	//物品分析 获得 与 消耗
	virtual bool OnItemRecv(const std::string& sItemID,uint uCount,const std::string& sSource="");														//物品
	virtual bool OnItemUsed(const std::string& sItemID,uint uCount,const std::string& sWay="",const std::string& sArg1="",const std::string& sArg2="");

	//扩展接口
	virtual bool OnEvent(const std::string& sEvent);
	virtual bool OnEvent(const std::string& sEvent,const std::string& sKey,const std::string& sValue);
	virtual bool OnEvent(const std::string& sEvent,const MapStringString& vKeyValue);					//实际执行

	virtual bool OnEventBegin(const std::string& sEvent);
	virtual bool OnEventBegin(const std::string& sEvent, const std::string& sKey, const std::string& sValue);
	virtual bool OnEventBegin(const std::string& sEvent, const MapStringString& vKeyValue);
	virtual bool OnEventEnd(const std::string& sEvent);
	virtual bool OnEventEnd(const std::string& sEvent, const std::string& sKey, const std::string& sValue);
	virtual bool OnEventEnd(const std::string& sEvent, const MapStringString& vKeyValue);

	//任务
	virtual bool OnTaskBegin(const std::string& sTaskName);		//任务开始
	virtual bool OnTaskCompleted(const std::string& sTaskName);	//任务完成
	virtual bool OnTaskFailed(const std::string& sTaskName,const std::string& sReason);//任务失败 失败原因

	//玩家等级
	virtual bool OnLevelUp(int nLevel);

	//用户建议
	virtual bool OnAdvice(int eAdviceType, const std::string& sName, const std::string& sTel, const std::string& sContent, const std::string& sQQ);
	
	//用户日志
	virtual bool OnLog(int eLogType, const std::string& sContent, const std::string& sArg1 = "", const std::string& sArg2 = "", const std::string& sArg3 = "", const std::string& sArg4 = "", const std::string& sArg5 = "", int32 nArgValue = 0);

	//系统
	virtual bool SetLogEnabled(bool bEnable);//打开日志功能

	//设置App信息
	virtual bool SetAppID(const std::string& sAppID);
	virtual bool SetAppVer(const std::string& sAppVer);

	//设置账号信息
	virtual bool SetUserID(const std::string& sUserID);
	virtual bool SetAccount(const std::string& sAccount);
	virtual bool SetAccountChannelID(const std::string& sAccountChannelID);
	virtual bool SetLevel(int nLevel);
	virtual bool SetGender(EGender eGender);											//设置性别
	virtual bool SetAge(int nAge);														//设置年龄
	virtual bool SetGameServer(const std::string& sGameServer);							//设置区服
	virtual bool SetChannelID(const std::string& sChannelID);							//设置渠道
public:
	IAnalytics(void);
	virtual ~IAnalytics(void);
protected:
	//App信息
	std::string _sAppID;		//应用ID
	std::string _sChannelID;	//渠道
	std::string	_sAppVer;		//版本

	//账号信息
	std::string _sUserID;				//用户ID
	std::string _sAccount;				//账号ID
	std::string _sAccountChannelID;		//账号渠道ID
	int			_nLevel;				//等级
	EGender		_eGender;				//性别
	int			_nAge;					//年纪
	std::string _sGameServer;			//区服

	bool		_bInited;		//初始化 完成
};

NS_TOOL_FRAME_END
