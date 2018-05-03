#pragma once

#include "Macro.h"

//设置 事件参数
#define SET_EVENT_ARG(tName)					(void*)&tName

//获取 并且声明事件参数
#define GET_EVENT_ARG(tT,tArg)				*((tT*)tArg)
#define DECLARE_EVENT_ARG(tT,tName,tArg)	tT& tName = *((tT*)tArg)

NS_TOOL_FRAME_BEGIN

struct TOOLFRAME_DLL XEvent
{
	std::string	sEventType;
	int			eEventType;
	std::string sArg1;
	std::string sArg2;
	std::string sArg3;
	int			nArg1;
	int			nArg2;
	int			nArg3;
	void*		pArg;
	
	XEvent(){
		eEventType = INVALID_ID;
		nArg1 = 0;
		nArg2 = 0;
		nArg3 = 0;
		pArg = nullptr;
	}
};

class TOOLFRAME_DLL HEventTrigger
{
public:
	virtual bool OnEvent(int nEvent,				const XEvent& xEvent);
	virtual bool OnEvent(const std::string& sEvent,	const XEvent& xEvent);
public:
	HEventTrigger(void);
	virtual ~HEventTrigger(void);
};

NS_TOOL_FRAME_END
