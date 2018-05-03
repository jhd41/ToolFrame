#pragma once
#include "LuaEngine.h"
#include "IResolverManager.h"
#include "EventTrigger.h"

NS_TOOL_FRAME_BEGIN

class CResolverCoreManager
	:public IResolverManager
	,public HEventTrigger
{
public:
	virtual bool Init();
	virtual bool ProcessOne(uint64 uMillSeconds = 0);			//处理一个阶段 返回是否处理(返回Flase代表 不需要处理)
	virtual bool IsProcessed()const;		//是否已经处理完成

	//Lua
public:
	virtual bool				InitLua();
	virtual bool				LoadLua(const std::string& sLua);
	virtual bool				LoadLuaFile(const std::string& sFile);
	virtual CLuaEngine&			GetLuaEngine();
	virtual const CLuaEngine&	GetLuaEngine()const;
	virtual bool				SetEventPost(bool bPost);//使用Post方式抛送事件(默认flase)
	virtual bool				IsEventPost()const;		//是否使用Post方式抛送事件
	virtual bool				ResetLuaEngine();		//重置Lua引擎

	//LuaApi
public:
	bool			ApiTrace(std::string sMsg);			//打印调试信息
	bool			ApiLogLuaDebug(std::string sMsg);	//记录调试日志
	bool			ApiLogLuaError(std::string sMsg);	//记录错误日志
	bool			ApiLogSystem(std::string sMsg);		//记录系统日志

	bool			ApiTriggerEvent(std::string sEvent);				//触发事件
	bool			ApiTriggerEventWithInt(std::string sEvent,int nInt);//触发事件(带参)
	bool			ApiTriggerEventWithString(std::string sEvent,std::string sArg);//触发事件(带参)

	bool			ApiClearEventArg();					//清除事件参数

	std::string		ApiGetEventName();					//获取事件名称
	int				ApiGetEventInt();					//获得事件参数:Int 等同 ApiGetEventInt1
	int				ApiGetEventInt1();					//获得事件参数1:Int
	int				ApiGetEventInt2();					//获得事件参数2:Int
	int				ApiGetEventInt3();					//获得事件参数3:Int
	std::string		ApiGetEventString();				//获得事件参数:String 等同 ApiGetEventString1
	std::string		ApiGetEventString1();				//获得事件参数1:String
	std::string		ApiGetEventString2();				//获得事件参数2:String
	std::string		ApiGetEventString3();				//获得事件参数3:String

	bool			ApiActionLua(uint uIndex);			//创建Lua结算动作
	bool			ApiActionGameOver();				//创建游戏结束动作

//Event
public:
	virtual	bool TriggleEvent(const std::string& sEventName);
	virtual bool TriggleEvent(const std::string& sEventName,int nEventInt);
	virtual bool TriggleEvent(const std::string& sEventName,int nEventInt1,int nEventInt2);
	virtual bool TriggleEvent(const std::string& sEventName,int nEventInt1,int nEventInt2,int nEventInt3);
	virtual bool TriggleEvent(const std::string& sEventName,const std::string& sEventString);
	virtual bool TriggleEvent(const std::string& sEventName,const std::string& sEventString1,const std::string& sEventString2);
	virtual bool TriggleEvent(const std::string& sEventName,const std::string& sEventString1,const std::string& sEventString2,const std::string& sEventString3);
	virtual	bool TriggleEvent(const std::string& sEventName,void* pAc);
	virtual	bool TriggleEvent(const XEvent& xEvent);

	virtual bool ClearEventArg();
	
	//注册事件
public:
	virtual bool EnableTriggerEvent(bool bEnabled);	//设置能够触发事件默认 开启
	virtual bool IsEnableTriggerEvent()const;		//是否能够触发事件默认 开启

	//指定事件类型处理器
	virtual bool RegistEvent(const std::string& sEvent,HEventTrigger* hEvent);
	virtual bool UnregistEvent(const std::string& sEvent,HEventTrigger* hEvent);

	//所有事件类型处理器
	virtual bool RegistAllEvent(HEventTrigger* hEvent);
	virtual bool UnregistAllEvent(HEventTrigger* hEvent);

	//安全释放所有该处理器注册过的事件
	virtual int	SafeUnregistEvent(HEventTrigger* hEvent);
protected:
	virtual bool OnEvent(const std::string& sEvent,const XEvent& xEvent);
private:
	bool TriggleLuaEvent( const std::string& sEventName );
private:
	XEvent _xEvent;
public:
	CResolverCoreManager(void);
	virtual ~CResolverCoreManager(void);
protected:
	CLuaEngine*		_pLuaEngine;		//Lua引擎
	CEventTrigger	_mgrEvent;		//事件管理器
	bool			_bPost;
};

NS_TOOL_FRAME_END
