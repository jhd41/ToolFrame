#pragma once
#include "Macro.h"
#include "IMsgStream.h"
#include "IMsgStreamSpliter.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IDataReceiverStream
	:public IDataReceiver
	,public IMsgStreamSpliter
{
	//�ڲ�
protected:
	virtual uint OnRecv(IDataSession* pSession)override;//���ش����˰��ĸ���
public:
	IDataReceiverStream(void);
	virtual ~IDataReceiverStream(void);
};

NS_TOOL_FRAME_END
