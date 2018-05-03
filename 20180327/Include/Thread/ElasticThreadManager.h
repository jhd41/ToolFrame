#pragma once
#include "Macro.h"

#include "IThreadNew.h"
#include "ThreadGroup.h"
#include "TimeOut.h"
#include "AvgCounter.h"

//弹性线程
//备注:设计一个自动调节当前线程数 以适应当前系统的类。
//主要目的为 减少总线程数，能够自由的分配线程多寡 来达到优化系统的目的。
//设计思路：当弹性线程任务执行超时时，新分配新的线程。当长期处在未超时状态时，则回收线程

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL HElasticThread
{
public:
	virtual bool OnElasticThreadStarted(){return false;}			//弹性线程启动时
	virtual bool OnElasticThreadStoped(){return false;}				//弹性线程停止时
	
	virtual bool OnElasticRuned(uint64 uTimeUsed,bool bTimeOut){return false;}	//单次运行时间
	virtual bool OnElasticTimeOut(uint64 uTimeElapsed){return false;}	//运行超时(会在调用OnElasticRuned后调用本函数)
	virtual bool OnRunElasticThread(){return false;}					//执行弹性线程，返回是否超时
public:
	HElasticThread(){}
	virtual ~HElasticThread(){}
};

class TOOLFRAME_DLL CElasticThreadProcesser;
class TOOLFRAME_DLL CElasticThreadManager
{
public:
	virtual bool SetHandler(HElasticThread* hHandler);
	virtual bool SetTimeRecycle(uint uTimeOut);			//设置空闲时回收线程时间(秒) 默认300
	virtual bool SetTimeCheck(uint uTimeSpace);			//设置检查时间间隔。(避免突然 起很多，突然释放很多) 默认3000毫秒
	virtual bool SetThreadTimeInterval(uint uTimeInterval);//线程单次运行时间间隔
public:
	virtual bool AddElasticThread(uint uTimeInterval=50);//新增一个伸缩线程
	virtual bool RecycleElasticThread();
	virtual bool RunElasticThread();
	virtual bool Stop();
	virtual size_t Count()const;
	virtual uint64 GetRunTimeAvg()const;
	virtual uint64 GetRunTimeMax()const;
	virtual bool CheckElastic();
	
	//内部调用
public:
	virtual bool OnThreadStarted(CElasticThreadProcesser* pThread);
	virtual bool OnThreadStoped(CElasticThreadProcesser* pThread);
public:
	CFIELD_UINT(ThreadMax);			//线程上限
public:
	CElasticThreadManager(void);
	virtual ~CElasticThreadManager(void);
public:
	HElasticThread* _hHandler;
	CThreadGroup	_vThread;
	bool			_bStarting;			//正在启动新线程
	CTimeOut		_xTimeRecycle;		//超时回收
	CTimeOut		_xTimeCheck;		//检查时间间隔
	uint			_uThreadTimeInterval;//线程单次运行时间间隔
	uint64			_uRunTimeAvg;		//平均单次运行时间
	uint64			_uRunTimeMax;		//单词运行最长时间
	CMutexReadWrite	_mutex;

	CAvgCounter		_xRunTime;			//运行统计
};

//////////////////////////////////////////////////////////////////////////
class CElasticThreadProcesser
	:public IThreadNew
{
public:
	virtual bool SetManager(CElasticThreadManager* pMgr);
public:
	virtual	bool InitThread();
	virtual bool RunOnceThread();
	virtual bool OnThreadStoped();
public:
	CElasticThreadProcesser();
	virtual ~CElasticThreadProcesser();
private:
	CElasticThreadManager* _pMgr;
};

NS_TOOL_FRAME_END