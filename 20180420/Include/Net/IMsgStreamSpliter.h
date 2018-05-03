#pragma once

#include "Macro.h"
#include "IMsgStream.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IMsgStreamSpliter
{
public:
	virtual uint SpliteMsgStream(IDataSession* pSession);

	//二选一 随意 选择一个 函数 进行继承
public:
	virtual bool OnRecv( IDataSession* pSession, IMsgStream& msgStream);
	virtual bool OnRecv( uint uClientID,IMsgStream& msgStream);
public:
	IMsgStreamSpliter(void);
	virtual ~IMsgStreamSpliter(void);
};

NS_TOOL_FRAME_END
