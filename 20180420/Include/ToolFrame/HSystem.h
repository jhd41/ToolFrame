#pragma once
#include "Macro.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL HSystem
{
public:
	virtual bool		OnSystemInit();					//ϵͳ��ʼ��ʱ
	virtual	bool		OnSystemProcess(uint64 uTime);	//��ѭ���ص�(����ʱ��)
	virtual bool		OnSystemCleanUp();				//ϵͳ����(����false��ֹ����)
	virtual	bool		OnSystemMemoryLow();			//�ڴ治��(����false��ֹ����)
public:
	HSystem(void);
	virtual ~HSystem(void);
};

NS_TOOL_FRAME_END
