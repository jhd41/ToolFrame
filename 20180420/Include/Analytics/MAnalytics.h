#pragma once
#include "MacroAnalytics.h"

#include "ToolFrame.h"
#include "IAnalytics.h"

//分析插件管理器
//备注:游戏启动后 OnStartUp 必须尽快 设置需要分析的账号，若不设置 则 分析的账号为空 会造成没有数据
//如果游戏需要登录 则 登录后 调用 OnLogin ，否则 启动后直接调用 SetAnonymous即可
//IAnalytics对象被创建出来之时 已经进入了 MAnalytics 的管理范畴
//Channel 渠道指的是用户属性渠道(第一次登录时的推广渠道即被计算为用户行为属性 用户的所有行为计算为用户属性渠道的数据)

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL MAnalytics
{
public:
	typedef std::vector<IAnalytics*> VectorAnalytics;
public:
	ST_INTANCE(MAnalytics);
public:
	bool					Regist(IAnalytics* pAnalytics);	//注册
	bool					UnRegist(IAnalytics* pAnalytics);
	VectorAnalytics&		GetAnalytics();					//获取所有的分析器
	const VectorAnalytics&	GetAnalytics()const;
public:
	//账户管理
	bool SetAnonymous();//设置匿名账号(无需调用 OnLogin)

	bool SetLevel(int nLevel);													//设置级别
	bool SetGender(EGender eGender);											//设置性别
	bool SetAge(int nAge);														//设置年龄
	bool SetGameServer(const std::string& sServerName);							//设置区服
	bool SetChannelID(const std::string& sChannel);								//设置渠道
	bool OnLogin(const std::string& sUserID, const std::string& sAccount,const std::string& sChannelID);	//登陆
	bool OnLogout();															//登出

	bool OnStartUp();	//启动
	bool OnPause();		//暂停
	bool OnResume();	//回到游戏
	bool OnExit();		//退出

	//支付
	bool OnPayReq(const std::string& sOrderID,const std::string& sItemID,uint uItemCount,uint uMoney,const std::string& sPayCurrency,const std::string& sPayType,uint uVirtualCurrency=0);//支付(支付方式EPayType 币种ECurrency 金额 单位分) sProductID(用户自定义)
	bool OnPayed(const std::string& sOrderID,const std::string& sPaySource="",const std::string& sArg="");
	bool OnPayFaild(const std::string& sOrderID,const std::string& sReason="",const std::string& sArg="");

	//虚拟币分析 获得 与 消耗
	bool OnVirtualCurrencyGain(const std::string& sCurrencyType,uint uCount,const std::string& sSource="");															//虚拟币 币种,数量，来源
	bool OnVirtualCurrencyUsed(const std::string& sCurrencyType,uint uCount,const std::string& sWay="",const std::string& sArg1="",const std::string& sArg2="");	//虚拟币 币种,数量，途径(例如使用 钻石 3个 购买物品 买了3个5号道具)

	//物品分析 获得 与 消耗
	bool OnItemRecv(const std::string& sItemID,uint uCount,const std::string& sSource="");														//物品
	bool OnItemUsed(const std::string& sItemID,uint uCount,const std::string& sWay="",const std::string& sArg1="",const std::string& sArg2="");

	//扩展接口
	bool OnEvent(const std::string& sEvent);
	bool OnEvent(const std::string& sEvent, const std::string& sKey, const std::string& sValue);
	bool OnEvent(const std::string& sEvent, const MapStringString& vKeyValue);					//实际执行

	template<typename TValue>
	bool OnEvent(const std::string& sEvent, const std::string& sKey, const TValue& tValue);

	bool OnEventBegin(const std::string& sEvent);
	bool OnEventBegin(const std::string& sEvent, const std::string& sKey, const std::string& sValue);
	bool OnEventBegin(const std::string& sEvent, const MapStringString& vKeyValue);
	bool OnEventEnd(const std::string& sEvent);
	bool OnEventEnd(const std::string& sEvent, const std::string& sKey, const std::string& sValue);
	bool OnEventEnd(const std::string& sEvent, const MapStringString& vKeyValue);

	//任务
	bool OnTaskBegin(const std::string& sTaskName);		//任务开始
	bool OnTaskCompleted(const std::string& sTaskName);	//任务完成
	bool OnTaskFailed(const std::string& sTaskName,const std::string& sReason);//任务失败 失败原因

	//玩家等级
	bool OnLevelUp(int nLevel);

	//用户留言
	bool OnAdvice(int eAdviceType, const std::string& sName, const std::string& sTel, const std::string& sContent, const std::string& sQQ);

	//系统
	bool SetLogEnabled(bool bEnable);//打开日志功能
public:
	MAnalytics(void);
	virtual ~MAnalytics(void);
private:
	VectorAnalytics _vAnalytics;
};

template<typename TValue>
bool MAnalytics::OnEvent( const std::string& sEvent,const std::string& sKey,const TValue& tValue )
{
	return OnEvent(sEvent,sKey,ToolFrame::ToString(tValue));
}


NS_TOOL_FRAME_END