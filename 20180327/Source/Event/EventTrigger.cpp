#include "EventTrigger.h"
#include "MLoger.h"
#include "TimeOut.h"

NS_TOOL_FRAME_BEGIN
CEventTrigger::CEventTrigger(void)
{
	_bEnable = true;
}

CEventTrigger::~CEventTrigger(void)
{
	CLockScoped lock(_mutex);
	ToolFrame::Delete(_vIntHandler);
	ToolFrame::Delete(_vHandlerInt);
	ToolFrame::Delete(_vStringHandler);
	ToolFrame::Delete(_vHandlerString);
}

bool CEventTrigger::Regist( int nEventType,HEventTrigger* hEvent )
{
	CLockScoped lock(_mutex);

	//注册到事件->处理器
	ListEventHandler* pvHandler = ToolFrame::GetPtrValueByKey(_vIntHandler,nEventType,true);
	ASSERT_LOG_ERROR(pvHandler);

	if (!ToolFrame::Insert(*pvHandler,hEvent))return false;

	//注册到处理器->事件
	SetInt* pvEvent = ToolFrame::GetPtrValueByKey(_vHandlerInt,hEvent,true);
	ASSERT_LOG_ERROR(pvEvent);

	if (!ToolFrame::Insert(*pvEvent,nEventType))return false;
	
	return true;
}

bool CEventTrigger::Unregist( int nEventType,HEventTrigger* hEvent )
{
	CLockScoped lock(_mutex);

	//注销到事件->处理器
	ListEventHandler* pvHandler = ToolFrame::GetPtrValueByKey(_vIntHandler,nEventType);
	if (!pvHandler)return false;

	//返回是否成功
	bool bSucceed = true;

	bSucceed &= ToolFrame::EraseByValue(*pvHandler,hEvent);

	//注销到处理器->事件
	SetInt* pvEvent = ToolFrame::GetPtrValueByKey(_vHandlerInt,hEvent);
	ASSERT_LOG_ERROR(pvEvent);

	bSucceed &= ToolFrame::EraseByValue(*pvEvent,nEventType);

	return bSucceed;
}

int CEventTrigger::SafeUnregist( HEventTrigger* hEvent )
{
	CLockScoped lock(_mutex);

	//统计删除多少个事件点
	int nCount = 0;

	//注销所有事件触发
	nCount += ToolFrame::EraseByValueAll(_vHandlerAll,hEvent);

	//注销指定事件触发
	{
		SetInt* pvEvent = ToolFrame::GetPtrValueByKey(_vHandlerInt,hEvent);
		if (pvEvent)
		{
			SetInt vEvent = *pvEvent;
			SetInt::iterator itr;
			foreach(itr,vEvent)
			{
				ASSERT_LOG_ERROR(Unregist(*itr,hEvent));
			}
			nCount += (int)vEvent.size();

			ToolFrame::DeleteByKey(_vHandlerInt,hEvent);
		}
	}
	{
		SetString* pvEvent = ToolFrame::GetPtrValueByKey(_vHandlerString,hEvent);
		if (pvEvent)
		{
			SetString vEvent = *pvEvent;
			SetString::iterator itr;
			foreach(itr,vEvent)
			{
				ASSERT_LOG_ERROR(Unregist(*itr,hEvent));
			}
			nCount += (int)vEvent.size();

			ToolFrame::DeleteByKey(_vHandlerString,hEvent);
		}
	}
	return nCount;
}

bool CEventTrigger::FireEvent( int nEventType )
{
	XEvent xEvent;
	xEvent.eEventType = nEventType;
	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( int nEventType,const std::string& sArg )
{
	XEvent xEvent;
	xEvent.eEventType = nEventType;
	xEvent.sArg1 = sArg;
	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( int nEventType,int nArg1 )
{
	XEvent xEvent;
	xEvent.eEventType = nEventType;
	xEvent.nArg1 = nArg1;
	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( int nEventType,int nArg1,int nArg2 )
{
	XEvent xEvent;
	xEvent.eEventType = nEventType;
	xEvent.nArg1 = nArg1;
	xEvent.nArg2 = nArg2;
	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( int nEventType,int nArg1,int nArg2,int nArg3 )
{
	XEvent xEvent;
	xEvent.eEventType = nEventType;
	xEvent.nArg1 = nArg1;
	xEvent.nArg2 = nArg2;
	xEvent.nArg3 = nArg3;
	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( int nEventType,const std::string& sArg,int nArg1,int nArg2 )
{
	XEvent xEvent;
	xEvent.eEventType = nEventType;
	xEvent.sArg1 = sArg;
	xEvent.nArg1 = nArg1;
	xEvent.nArg2 = nArg2;

	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( int nEventType,const std::string& sArg,int nArg1,int nArg2,int nArg3,void* pArg )
{
	XEvent xEvent;
	xEvent.eEventType = nEventType;
	xEvent.sArg1 = sArg;
	xEvent.nArg1 = nArg1;
	xEvent.nArg2 = nArg2;
	xEvent.nArg3 = nArg3;
	xEvent.pArg = pArg;
	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( int nEventType,void* pArg )
{
	XEvent xEvent;
	xEvent.eEventType = nEventType;
	xEvent.pArg = pArg;
	return FireEvent(xEvent);
}

bool CEventTrigger::RegistAll(HEventTrigger* hEvent)
{
	CLockScoped lock(_mutex);
	return	ToolFrame::Insert(_vHandlerAll,hEvent);
}

bool CEventTrigger::UnregistAll( HEventTrigger* hEvent )
{
	CLockScoped lock(_mutex);
	return ToolFrame::EraseByValue(_vHandlerAll,hEvent);
}

bool CEventTrigger::FireEventVct( ListEventHandler& vHandlers, const XEvent& xEvent )
{
	if (!vHandlers.empty())
	{
		ListEventHandler vHandler = vHandlers;//必须复制一份放置在触发时卸载自己之类的事情发生
		ListEventHandler::iterator itr;
		foreach(itr,vHandler){
			HEventTrigger* hEvent = *itr;
			if (!hEvent)return false;

			if (INVALID_ID != xEvent.eEventType)
				hEvent->OnEvent(xEvent.eEventType,xEvent);
			else
				hEvent->OnEvent(xEvent.sEventType,xEvent);
		}
	}
	return true;
}

bool CEventTrigger::PostEvent( int nEventType )
{
	return PostEvent(nEventType,ToolFrame::EmptyString(),0,0);
}

bool CEventTrigger::PostEvent( int nEventType,const std::string& sArg )
{
	return PostEvent(nEventType,sArg,0,0);
}

bool CEventTrigger::PostEvent( int nEventType,int nArg1 )
{
	return PostEvent(nEventType,ToolFrame::EmptyString(),nArg1,0);
}

bool CEventTrigger::PostEvent( int nEventType,int nArg1,int nArg2 )
{
	return PostEvent(nEventType,ToolFrame::EmptyString(),nArg1,nArg2);
}

bool CEventTrigger::PostEvent( int nEventType,const std::string& sArg,int nArg1,int nArg2 )
{
	XEvent xEvent;
	xEvent.eEventType = nEventType;
	xEvent.sArg1 = sArg;
	xEvent.nArg1 = nArg1;
	xEvent.nArg2 = nArg2;
	return _vEvent.Push(xEvent);
}

bool CEventTrigger::PostEvent( int nEventType,int nArg1,int nArg2,int nArg3 )
{
	XEvent xEvent;
	xEvent.eEventType = nEventType;
	xEvent.nArg1 = nArg1;
	xEvent.nArg2 = nArg2;
	xEvent.nArg3 = nArg3;
	return _vEvent.Push(xEvent);
}

bool CEventTrigger::PostEvent( int nEventType,void* pArg )
{
	XEvent xEvent;
	xEvent.eEventType = nEventType;
	xEvent.pArg = pArg;
	return _vEvent.Push(xEvent);
}

bool CEventTrigger::ProcessEvent(uint64 uTimeOut)
{
	if (_vEvent.Empty())return false;

	CTimeOut timeout(uTimeOut);
	while (!timeout.IsTimeOut())
	{
		XEvent xEvent;
		if (!_vEvent.PopFront(xEvent))return false;

		FireEvent(xEvent);
	}
	return true;
}

bool CEventTrigger::EnableTriggerEvent( bool bEnabled )
{
	_bEnable = bEnabled;
	return true;
}

bool CEventTrigger::IsEnableTriggerEvent() const
{
	return _bEnable;
}

bool CEventTrigger::Regist( const std::string& sEvent,HEventTrigger* hEvent )
{
	CLockScoped lock(_mutex);

	//注册到事件->处理器
	ListEventHandler* pvHandler = ToolFrame::GetPtrValueByKey(_vStringHandler,sEvent,true);
	ASSERT_LOG_ERROR(pvHandler);

	if (!ToolFrame::Insert(*pvHandler,hEvent))return false;

	//注册到处理器->事件
	SetString* pvEvent = ToolFrame::GetPtrValueByKey(_vHandlerString,hEvent,true);
	ASSERT_LOG_ERROR(pvEvent);

	if (!ToolFrame::Insert(*pvEvent,sEvent))return false;
	return true;
}

bool CEventTrigger::Unregist( const std::string& sEvent,HEventTrigger* hEvent )
{
	CLockScoped lock(_mutex);

	//注销到事件->处理器
	ListEventHandler* pvHandler = ToolFrame::GetPtrValueByKey(_vStringHandler,sEvent);
	if (!pvHandler)return false;

	//返回是否成功
	bool bSucceed = true;

	bSucceed &= ToolFrame::EraseByValue(*pvHandler,hEvent);

	//注销到处理器->事件
	SetString* pvEvent = ToolFrame::GetPtrValueByKey(_vHandlerString,hEvent);
	ASSERT_LOG_ERROR(pvEvent);

	bSucceed &= ToolFrame::EraseByValue(*pvEvent,sEvent);

	return bSucceed;
}

bool CEventTrigger::FireEvent( const std::string& sEvent )
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( const std::string& sEvent,const std::string& sArg )
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.sArg1 = sArg;
	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( const std::string& sEvent,int nArg1 )
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.nArg1 = nArg1;
	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( const std::string& sEvent,int nArg1,int nArg2 )
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.nArg1 = nArg1;
	xEvent.nArg2 = nArg2;
	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( const std::string& sEvent,int nArg1,int nArg2,int nArg3 )
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.nArg1 = nArg1;
	xEvent.nArg2 = nArg2;
	xEvent.nArg3 = nArg3;
	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent(const std::string& sEvent, int nArg1, const std::string& sArg1)
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.nArg1 = nArg1;
	xEvent.sArg1 = sArg1;
	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( const std::string& sEvent,const std::string& sArg,int nArg1,int nArg2 )
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.sArg1 = sArg;
	xEvent.nArg1 = nArg1;
	xEvent.nArg2 = nArg2;

	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( const std::string& sEvent,const std::string& sArg,int nArg1,int nArg2,int nArg3,void* pArg )
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.sArg1 = sArg;
	xEvent.nArg1 = nArg1;
	xEvent.nArg2 = nArg2;
	xEvent.nArg3 = nArg3;
	xEvent.pArg = pArg;
	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( const std::string& sEvent,void* pArg )
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.pArg = pArg;
	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( const std::string& sEvent,const std::string& sArg1,const std::string& sArg2 )
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.sArg1 = sArg1;
	xEvent.sArg2 = sArg2;
	return FireEvent(xEvent);
}

bool CEventTrigger::FireEvent( const std::string& sEvent,const std::string& sArg1,const std::string& sArg2,const std::string& sArg3 )
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.sArg1 = sArg1;
	xEvent.sArg2 = sArg2;
	xEvent.sArg3 = sArg3;
	return FireEvent(xEvent);
}

bool CEventTrigger::PostEvent( const std::string& sEvent )
{
	return PostEvent(sEvent,ToolFrame::EmptyString(),0,0);
}

bool CEventTrigger::PostEvent( const std::string& sEvent,const std::string& sArg )
{
	return PostEvent(sEvent,sArg,0,0);
}

bool CEventTrigger::PostEvent( const std::string& sEvent,int nArg1 )
{
	return PostEvent(sEvent,ToolFrame::EmptyString(),nArg1,0);
}

bool CEventTrigger::PostEvent( const std::string& sEvent,int nArg1,int nArg2 )
{
	return PostEvent(sEvent,ToolFrame::EmptyString(),nArg1,nArg2);
}

bool CEventTrigger::PostEvent( const std::string& sEvent,const std::string& sArg1,const std::string& sArg2 )
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.sArg1 = sArg1;
	xEvent.sArg2 = sArg2;

	return PostEvent(xEvent);
}

bool CEventTrigger::PostEvent( const std::string& sEvent,const std::string& sArg1,const std::string& sArg2,const std::string& sArg3 )
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.sArg1 = sArg1;
	xEvent.sArg2 = sArg2;
	xEvent.sArg3 = sArg3;

	return PostEvent(xEvent);
}

bool CEventTrigger::PostEvent( const std::string& sEvent,const std::string& sArg,int nArg1,int nArg2 )
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.sArg1 = sArg;
	xEvent.nArg1 = nArg1;
	xEvent.nArg2 = nArg2;

	return PostEvent(xEvent);
}

bool CEventTrigger::PostEvent( const std::string& sEvent,int nArg1,int nArg2,int nArg3 )
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.nArg1 = nArg1;
	xEvent.nArg2 = nArg2;
	xEvent.nArg3 = nArg3;
	return PostEvent(xEvent);
}

bool CEventTrigger::PostEvent( const std::string& sEvent,void* pArg )
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.pArg = pArg;
	return PostEvent(xEvent);
}

bool ToolFrame::CEventTrigger::PostEvent(const std::string& sEvent, int nArg1, const std::string& sArg1)
{
	XEvent xEvent;
	xEvent.sEventType = sEvent;
	xEvent.nArg1 = nArg1;
	xEvent.sArg1 = sArg1;
	return PostEvent(xEvent);
}

bool CEventTrigger::PostEvent( const XEvent& xEvent )
{
	if (!_bEnable)return false;

	return _vEvent.Push(xEvent);
}

bool CEventTrigger::FireEvent( const XEvent& xEvent )
{
	if (!_bEnable)return false;

	if (INVALID_ID == xEvent.eEventType && xEvent.sEventType.empty())
		return false;
	
	CLockScoped lock(_mutex);

	//先触发指定事件处理器
	ListEventHandler* pvHandler = nullptr;
	if (INVALID_ID != xEvent.eEventType)
		pvHandler = ToolFrame::GetPtrValueByKey(_vIntHandler,xEvent.eEventType);
	else
		pvHandler = ToolFrame::GetPtrValueByKey(_vStringHandler,xEvent.sEventType);

	if (pvHandler)
		FireEventVct(*pvHandler,xEvent);

	//后触发所有事件处理器
	FireEventVct(_vHandlerAll,xEvent);
	return true;
}

bool CEventTrigger::IsEventQueueEmpty() const
{
	return _vEvent.Empty();
}

NS_TOOL_FRAME_END
