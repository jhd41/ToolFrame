#pragma once
#include "IThreadNew.h"

//��ȫ�߳�
//�������̻߳����MTheard��ȥ����MThreadͳһ����(ϵͳStopʱ��ȴ�������������)

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IThreadSafty
	:public IThreadNew
{
public:
	virtual bool StartThread(uint uTimeInterval=50);
protected:
	virtual	bool SetThreadStoped();
public:
	IThreadSafty(void);
	virtual ~IThreadSafty(void);
};

NS_TOOL_FRAME_END
