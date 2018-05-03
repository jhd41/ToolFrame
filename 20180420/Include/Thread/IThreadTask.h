#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"
#include "IThread.h"

//�߳�:
//�̳б���֮�� ��Ҫ��������ʵ������������.
//ʹ��StartThread֮��������N���߳�����MThread���������̻߳���ִ�е�ǰ������
//�÷����������̻߳����MTheard��ȥ����MThreadͳһ����

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CTaskThreadManager;
class TOOLFRAME_DLL IThreadTask
		:public IThread
{
public:
	virtual bool StartThread(int nLoop = -1,uint uCount = 1,uint uTimeInterval=50);
	virtual bool ReqStopThread();
public:
	IThreadTask(void);
	virtual ~IThreadTask(void);
private:
	CMutexRecursive		_mutex;
	CTaskThreadManager*	_pMgrTaskThread;
};

NS_TOOL_FRAME_END
