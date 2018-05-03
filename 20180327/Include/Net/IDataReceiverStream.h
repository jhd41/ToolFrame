#pragma once
#include "Macro.h"
#include "IMsgStream.h"
#include "IMsgStreamSpliter.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IDataReceiverStream
	:public IDataReceiver
	,public IMsgStreamSpliter
{
	//内部
protected:
	virtual uint OnRecv(IDataSession* pSession)override;//返回处理了包的个数
public:
	IDataReceiverStream(void);
	virtual ~IDataReceiverStream(void);
};

NS_TOOL_FRAME_END
