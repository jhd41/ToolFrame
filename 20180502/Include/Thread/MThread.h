#pragma once
#include "ElasticThreadManager.h"
#include "TaskThreadManager.h"

//线程管理器:
//管理两种线程
//1.IThread:	线程		会真实启动一根全新的线程
//2.IThreadTask:线程任务	会添加到任务队列 使得本类设置的线程会来执行 以达到减少总体线程数量的目的

//备注:设计思路 本类为了减少整个系统线程个数而存在，希望将每个需要线程执行的任务 能够 不用再单独起线程，将其封装成任务的方式 在任务线程中运行。
//例如 原先会起4个网络线程，4个逻辑线程，这样就是8线程。而如今，只需要起4线程，同时执行网络任务和逻辑任务即可。
//这里的线程任务理论应该就是任务调度器的写法，短作业优先，4线程中有2条长作业线程，2条短作业线程。
//但是到目前为止，暂时没有这样的需求。未来再来优化吧。


NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL MThread
{
	ST_INTANCE(MThread);
public:
	bool AddThread(IThread* pThread);			//添加一个线程
	bool RemoveThread(IThread* pThread);		//移除一个线程
	bool Stop();
public:
	CElasticThreadManager&	GetElasticMgr();	//伸缩线程
	CTaskThreadManager&		GetTaskMgr();		//任务线程
public:
	MThread(void);
	virtual ~MThread(void);
private:
	CElasticThreadManager	_mgrElastic;	//伸缩线程
	CTaskThreadManager		_mgrTask;		//任务线程
	CThreadGroup			_vThread;		//所有的线程
};

NS_TOOL_FRAME_END
