#include "TaskThreadManager.h"

#include "ToolFrame.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN
CTaskThreadManager::CTaskThreadManager(void)
{
}

CTaskThreadManager::~CTaskThreadManager(void)
{
	Stop();
}

bool CTaskThreadManager::AddTaskThread( uint uThreads,uint uTimeInterval )
{
	if (!_vThread.StopThread())return false;

	for(uint uIndex =0;uIndex < uThreads ;++uIndex){
		CThreadTaskProcesser* pThread = _vThread.CreateThread<CThreadTaskProcesser>();
		ASSERT_LOG_ERROR(pThread);

		pThread->SetManager(this);
		pThread->StartThread(uTimeInterval);
	}

	return true;
}

bool CTaskThreadManager::AddTask( IThreadTask* pTask,int nLoop /*= -1*/,uint uCount/*=1*/,uint uTimeInterval/*=0*/ )
{
	if (!pTask)return false;
	if (uCount <= 0)return false;

	for(uint uIndex=0;uIndex<uCount;++uIndex){
		TaskNodePtr ptr(new XTaskNode());
		ASSERT_LOG_ERROR(ptr);

		ptr->pTask			= pTask;
		ptr->uTimeInterval	= uTimeInterval;
		ptr->nLoopCount		= nLoop;
		ptr->bDeleted		= false;
		ptr->uTimeLast		= 0;
		ptr->bInited		= false;
		ptr->uTimeLastWork	= 0;

		_vTask.Push(ptr);
		_vRuning.Push(ptr);
	}

	return true;
}

bool CTaskThreadManager::RemoveTask(const IThreadTask* pTask )
{
	if (!pTask)return false;

	CLockWrite lock(_vTask.GetMutex());
	QueueTask::StdList::iterator itr = _vTask.GetList().begin();
	while(itr != _vTask.GetList().end()){
		TaskNodePtr ptr = *itr;
		ASSERT_LOG_ERROR(ptr);

		if (pTask == ptr->pTask)
		{
			CLockScoped lockNode(ptr->mutex);
			ptr->bDeleted = true;

			itr = ToolFrame::EraseByItr(_vTask.GetList(),itr);
		}else{
			++itr;
		}
	}

	return true;
}

CTaskThreadManager::TaskNodePtr CTaskThreadManager::PopRunOneTask()
{
	TaskNodePtr ptr = _vRuning.PopFrontPtr();
	if (!ptr)return ptr;

	CLockScoped lockNode(ptr->mutex);

	//保证任务在规定时间间隔中执行
	if (!ptr->bDeleted)
	{
		uint64 uTimeNow = ToolFrame::GetNowTimeMill();
		if (ptr->uTimeLast + ptr->uTimeInterval  <= uTimeNow)
		{
			if (!ptr->bInited)
			{
				if (ptr->pTask->InitThread())
					ptr->bInited = true;
				else
					ptr->bDeleted = true;
			}else{
				//遵循线程执行规则，单次线程循环执行 返回 false 不再继续下次循环 线程结束
				if (ptr->pTask->RunOnceThread()) {
					if (ptr->nLoopCount > 0)
						--ptr->nLoopCount;
				}
				else {
					ptr->nLoopCount = 0;
				}
			}

			//引用为0则删除
			if (0 == ptr->nLoopCount) {
				ptr->bDeleted = true;
			}

			ptr->uTimeLast		= uTimeNow;
			ptr->uTimeLastWork	= ToolFrame::GetNowTimeMill()-uTimeNow;
		}
	}
	return ptr;
}

bool CTaskThreadManager::Stop()
{
	//将所有任务节点标记为删除
	{
		CLockWrite lock(_vTask.GetMutex());
		QueueTask::StdList::iterator itr = _vTask.GetList().begin();
		while(itr != _vTask.GetList().end()){
			TaskNodePtr ptr = *itr;
			ASSERT_LOG_ERROR(ptr);

			CLockScoped lockNode(ptr->mutex);
			ptr->bDeleted = true;

			itr = ToolFrame::EraseByItr(_vTask.GetList(),itr);
		}
	}

	//等待直到全部被清除
	_vThread.StopThread();
	return true;
}

bool CTaskThreadManager::RunOneTask()
{
	TaskNodePtr ptr = PopRunOneTask();
	if (!ptr)return false;

	//减少任务的运行次数
	CLockScoped lock(ptr->mutex);
	if (ptr->bDeleted) {
		_vTask.EraseByValue(ptr);
		return true;
	}

	_vRuning.Push(ptr);
	return true;
}

bool CTaskThreadManager::RunTask( uint64 uTime )
{
	bool bRuned = false;
	uint64 uTimeBegin = ToolFrame::GetNowTimeMill();
	while (ToolFrame::GetNowTimeMill() < (uTimeBegin + uTime) )
	{
		if (RunOneTask())
			bRuned = true;
	}

	return bRuned;
}

CTaskThreadManager::QueueTask& CTaskThreadManager::GetRunningTaskQueue()
{
	return _vRuning;
}

//线程任务处理器
//////////////////////////////////////////////////////////////////////////
CThreadTaskProcesser::CThreadTaskProcesser()
{
	_pMgr = nullptr;
}

CThreadTaskProcesser::~CThreadTaskProcesser()
{

}

bool CThreadTaskProcesser::SetManager(CTaskThreadManager* pMgr)
{
	_pMgr = pMgr;
	return true;
}

bool CThreadTaskProcesser::InitThread()
{
	return true;
}

bool CThreadTaskProcesser::RunOnceThread()
{
	//优化(当线程任务很少时,让线程多睡一会)
	uint	uSleepTime = 100;
	CTaskThreadManager::TaskNodePtr ptr = _pMgr->PopRunOneTask();
	if (ptr)
	{
		CLockScoped lockNode(ptr->mutex);
		uint64 uNextRunTime = ptr->uTimeLast + ptr->uTimeInterval;//下次执行时间
		uint64 uTimeNow = ToolFrame::GetNowTimeMill();

		uSleepTime = 0;
		if (uNextRunTime > uTimeNow)
			uSleepTime = (uint)(uNextRunTime - uTimeNow);

		if (uSleepTime<50)
			uSleepTime = 50;
		if (uSleepTime>1000)//保护
			uSleepTime = 1000;

		CTaskThreadManager::QueueTask& vTask = _pMgr->GetRunningTaskQueue();
		vTask.Push(ptr);
	}

	SetTimeInterval(uSleepTime);
	return true;
}

NS_TOOL_FRAME_END
