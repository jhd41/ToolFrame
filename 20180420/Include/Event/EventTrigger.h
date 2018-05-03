#pragma once

#include "Macro.h"
#include "HEventTrigger.h"
#include "TThreadSaftyList.h"

//注记:事件触发器
//本类支持两种类型的注册,1.指定事件 2.所有事件
//在触发时 先触发指定事件的处理器，再触发所有事件处理器
NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CEventTrigger
{
	typedef TThreadSaftyList<XEvent>				QueueEvent;
public:
	typedef std::list<HEventTrigger*>				ListEventHandler;

	//Int类型事件
	typedef std::map<int,ListEventHandler*>			MapIntHandler;//事件->处理器
	typedef std::map<HEventTrigger*,SetInt*>		MapHanderInt;//处理器->事件

	//String类型事件
	typedef std::map<std::string,ListEventHandler*>	MapStringHandler;//事件->处理器
	typedef std::map<HEventTrigger*,SetString*>		MapHanderString;//处理器->事件

	//全局类
public:
	bool EnableTriggerEvent(bool bEnabled);	//设置能够触发事件默认 开启
	bool IsEnableTriggerEvent()const;		//是否能够触发事件默认 开启
	
	//所有事件类型处理器
	bool RegistAll(HEventTrigger* hEvent);
	bool UnregistAll(HEventTrigger* hEvent);

	//安全释放所有该处理器注册过的事件
	int	SafeUnregist(HEventTrigger* hEvent);

	//Int事件类
public:
	//指定事件类型处理器
	bool Regist(int nEventType,HEventTrigger* hEvent);
	bool Unregist(int nEventType,HEventTrigger* hEvent);

	//当前线程事件
	bool FireEvent(int nEventType);
	bool FireEvent(int nEventType,const std::string& sArg);
	bool FireEvent(int nEventType,int nArg1);
	bool FireEvent(int nEventType,int nArg1,int nArg2);
	bool FireEvent(int nEventType,int nArg1,int nArg2,int nArg3);
	bool FireEvent(int nEventType,const std::string& sArg,int nArg1,int nArg2);
	bool FireEvent(int nEventType,const std::string& sArg,int nArg1,int nArg2,int nArg3,void* pArg);
	bool FireEvent(int nEventType,void* pArg);
	
	//线程事件
	bool PostEvent(int nEventType);
	bool PostEvent(int nEventType,const std::string& sArg);
	bool PostEvent(int nEventType,int nArg1);
	bool PostEvent(int nEventType,int nArg1,int nArg2);
	bool PostEvent(int nEventType,int nArg1,int nArg2,int nArg3);
	bool PostEvent(int nEventType,const std::string& sArg,int nArg1,int nArg2);
	bool PostEvent(int nEventType,void* pArg);

	//String 事件类
public:
	//指定事件类型处理器
	bool Regist(const std::string& sEvent,HEventTrigger* hEvent);
	bool Unregist(const std::string& sEvent,HEventTrigger* hEvent);

	//当前线程事件
	bool FireEvent(const std::string& sEvent);
	bool FireEvent(const std::string& sEvent,const std::string& sArg);
	bool FireEvent(const std::string& sEvent,const std::string& sArg1,const std::string& sArg2);
	bool FireEvent(const std::string& sEvent,const std::string& sArg1,const std::string& sArg2,const std::string& sArg3);
	bool FireEvent(const std::string& sEvent,int nArg1);
	bool FireEvent(const std::string& sEvent,int nArg1,int nArg2);
	bool FireEvent(const std::string& sEvent,int nArg1,int nArg2,int nArg3);
	bool FireEvent(const std::string& sEvent,int nArg1, const std::string& sArg1);
	bool FireEvent(const std::string& sEvent,const std::string& sArg,int nArg1,int nArg2);
	bool FireEvent(const std::string& sEvent,const std::string& sArg,int nArg1,int nArg2,int nArg3,void* pArg);
	bool FireEvent(const std::string& sEvent,void* pArg);
	bool FireEvent(const XEvent& xEvent);

	//线程事件
	bool PostEvent(const std::string& sEvent);
	bool PostEvent(const std::string& sEvent,const std::string& sArg);
	bool PostEvent(const std::string& sEvent,const std::string& sArg1,const std::string& sArg2);
	bool PostEvent(const std::string& sEvent,const std::string& sArg1,const std::string& sArg2,const std::string& sArg3);
	bool PostEvent(const std::string& sEvent,int nArg1);
	bool PostEvent(const std::string& sEvent,int nArg1,int nArg2);
	bool PostEvent(const std::string& sEvent,int nArg1,int nArg2,int nArg3);
	bool PostEvent(const std::string& sEvent,int nArg1,const std::string& sArg1);
	bool PostEvent(const std::string& sEvent,const std::string& sArg,int nArg1,int nArg2);
	bool PostEvent(const std::string& sEvent,void* pArg);
	bool PostEvent(const XEvent& xEvent);
public:
	bool IsEventQueueEmpty()const;
	bool ProcessEvent(uint64 uTimeOut = 0);//外部线程调用 以便处理投递的事件 返回是否超时
private:
	bool FireEventVct(ListEventHandler& vHandlers, const XEvent& xEvent);
private:
	
	MapIntHandler	_vIntHandler;	//事件->处理器
	MapHanderInt	_vHandlerInt;	//处理器->事件

	MapStringHandler _vStringHandler;	//事件->处理器
	MapHanderString	_vHandlerString;	//处理器->事件

	ListEventHandler _vHandlerAll;	//所有事件都需要触发该容器

	QueueEvent		_vEvent;
	CMutexRecursive	_mutex;

	bool			_bEnable;
public:
	CEventTrigger(void);
	virtual ~CEventTrigger(void);
};

NS_TOOL_FRAME_END
