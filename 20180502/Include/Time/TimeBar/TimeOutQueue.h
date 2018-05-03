#pragma once

#include "Macro.h"
#include "HTimeOut.h"
#include "TimeBar.h"
#include "TimeOut.h"
#include "TThreadSaftyMap.h"
#include "TimeElapse.h"
#include "TThreadSaftyList.h"

//超时队列
//作用:
//适应频繁添加删除操作下,高效的超时回调。
//时间条分为两种
//1.x秒之后超时 只要是相同秒数的超时，比如都是5秒，则消耗的时间片为1，否则 按照 不同的秒数个数 增加时间。
//2.x的时候超时 只要是相同的时间点的超时，比如都是9点，则消耗的时间片为1.否则 按照 不同的时间点个数 增加插入时间,单次循环时间消耗时间片仍然为1.
//以下为x秒之后超时的实现：
//注意:本类的效率和超时的时间条种类有关,和个数无关。
//所谓时间条种类 就是 超时的时间,比如都是5秒超时，那么哪怕有成千上万个 效率依然可以保证。
//而5秒和10秒超时的时间条算是两个不同的种类的时间条。
//思路:
//参考三国杀timebar诡异的写法之后得到以下思路和结论
//超时队列分两层，第一层 以map作为timebar容器。事先以1秒为时间间隔建立100秒也就是100个timebar。
//每个timebar里面都是一个list。
//当逻辑层添加一个时间节点时,比如5秒，服务器找到5秒的timebar,然后获取当前时间,放在timebar里面的list的末尾。
//删除的时候 按照懒惰删除的原则，仅仅是对node进行一个删除标记。
//系统调用process的时候,遍历当前所有的timebar,timebar则会判断list内部节点的超时时间从头开始判断是否超时,
//若超时，则处理回调。若没超时，则返回,不再进行对当前list进行超时判断。接下来外部对下一个timebar做同样的操作。
//分析:
//Map容器具备查找快的,扩展性强的优点,但是插入 删除非常慢。所以事先就建立了100个timebar,以后都只有查找操作，没有插入和删除。
//timebar内部list可以认为是一段一段的,比如5秒超时,这里的都是5秒之后要超时的节点，但是插入的时间却是不一样的。因此 可以保证 前面插入的 必然比后面插入的先超时。
//我们假设我们自己的想法是利用mulitmap对时间进行排序，然后从前到后超时运算。
//整体来看，其实把频繁的每次对map的插入删除调整平衡二叉树的过程替换为稳定的每次100个timebar的遍历。
//是一个利用map的find和list的push,pop操作的性能消耗来抗衡频繁的二叉树。

NS_TOOL_FRAME_BEGIN

typedef CSharePtr<CTimeBar>		CTimeBarPtr;
class CTimeOutQueue;

enum ETimeMode
{
	TIME_MODE_INVAILD,
	TIME_MODE_REAL,		//真实时间
	TIME_MODE_SEQ,		//顺序时间
	TIME_MODE_MAX,
};

class ITimeOutQueue
{
public:
	virtual uint64	GetTimeNow()const;
	virtual uint64	SetTimeNow(uint64 uTimeNow);
	virtual int		GetTimeMode()const;
	virtual bool	Pause();	//暂停
	virtual bool	Resume();	//回复
public:
	virtual CTimeOutQueue* GetTimeOutQueue()const;
	virtual bool	SetTimeOutQueue(CTimeOutQueue* pTimeOutQueue);
public:
	ITimeOutQueue();
	virtual ~ITimeOutQueue();
protected:
	int				_eTimeMode;			//时间模式
	CTimeOutQueue*	_pTimeOutQueue;
};

//////////////////////////////////////////////////////////////////////////
class CTimeOutQueueReal
	:public ITimeOutQueue
{
public:
	virtual uint64	GetTimeNow()const;
	virtual bool	Pause();	//暂停
	virtual bool	Resume();	//回复
public:
	CTimeOutQueueReal();
	virtual ~CTimeOutQueueReal();
private:
	CTimeElapse		_tTimeElapse;		//暂停时间
};
//////////////////////////////////////////////////////////////////////////
class CTimeOutQueueSeq
	:public ITimeOutQueue
{
public:
	virtual uint64	GetTimeNow()const;
	virtual uint64	SetTimeNow(uint64 uTimeNow);
	virtual bool	Pause();	//暂停
	virtual bool	Resume();	//回复
public:
	CTimeOutQueueSeq();
	virtual ~CTimeOutQueueSeq();
private:
	uint64			_uSeqTimeNow;		//顺序时间 当前时间
};

//////////////////////////////////////////////////////////////////////////
class TOOLFRAME_DLL CTimeOutQueue
{
public:
	typedef TThreadSaftyMapValue<uint64,CTimeBarPtr>	MapTimeBar;
	typedef TThreadSaftyListValue<CTimeNodePtr>		QueueTimeOut;
	//逻辑调用
public:
	CTimeNodePtr	CreateTimerByAfterSec(HTimeOut* pCallBack,time_t uTimeAfter,bool bLoop = false,time_t uTimeDelay=0);			//(创建 多少秒之后超时)精确到秒
	CTimeNodePtr	CreateTimerByAfterMil(HTimeOut* pCallBack,UINT64 uTimeAfter,bool bLoop = false,UINT64 uTimeDelay=0);			//精确到毫秒
	CTimeNodePtr	CreateTimerByPointSec(HTimeOut* pCallBack,time_t uTimePoint,bool bLoop = false,UINT64 uTimeDelay=0);//(创建 什么时间点 超时)精确到秒
	CTimeNodePtr	CreateTimerByPointMil(HTimeOut* pCallBack,UINT64 uTimePoint,bool bLoop = false,UINT64 uTimeDelay=0);//精确到毫秒
	bool			RemoveTimer(CTimeNodePtr& pTimeNode);
	
	bool			Pause();	//暂停
	bool			Resume();	//回复
	bool			IsPausing()const;//是否在暂停中
	bool			ClearEmptyTimebar();	//清除无用的时间条提升性能

	uint64			SetModeTimeNow(uint64 uTimeNow);
	uint64			GetModeTimeNow()const;	//获取模式下当前时间			

	bool			SetInterface(ETimeMode eTimeMode);	//设置时间模式(默认:真实时间)
	bool			SetInterface(ITimeOutQueue* pTimeOutQueue);

	ITimeOutQueue*	GetInterface()const;
	int				GetTimeMode()const;
	
	//系统调用
public:
	bool		ProcessTestTimeOut(uint64 uTimeProcess);						//处理测试是否超时以当前时间作为参考时间(返回是否超时)
	bool		ProcessTestTimeOut(uint64 uTimeNow,uint64 uTimeProcess);		//处理测试是否超时(返回是否超时)
	bool		ProcessTimeOut(uint64 uTimeProcess);							//处理已经超时的对象(返回是否均被正确处理)

	//外部不要调用
	friend class CTimeBar;
private:
	bool		AddTimerAfter(CTimeNodePtr& pTimeNode,UINT64 uTimeAfter);
	bool		AddTimerPoint(CTimeNodePtr& pTimeNode,UINT64 uTimePoint);
	
	bool		ClearEmptyTimebarAfter();
	bool		ClearEmptyTimebarPoint();
	
	bool		ProcessTestTimeOutAfter( uint64 uTimeNow,const CTimeOut& tTimeOut );
	bool		ProcessTestTimeOutPoint( uint64 uTimeNow,const CTimeOut& tTimeOut );
	bool		ClearTimeOutTimeBarPoint(uint64 uTimeNow);//清除已经超时的时间队列

	bool		AddTimeOut(CTimeNodePtr ptr);

	bool		DeleteInterface();
public:
	bool		ResumeAfter(uint64 uTimePaused);
	bool		ResumePoint(uint64 uTimePaused);
public:
	CTimeOutQueue(void);
	virtual ~CTimeOutQueue(void);
private:
	MapTimeBar		_vTimeBarAfter;		//正在结算中的节点队列
	MapTimeBar		_vTimeBarPoint;		//正在结算中的节点队列
	QueueTimeOut	_vTimeOut;			//已经超时的节点

	ITimeOutQueue*	_pTimeOutQueue;		//接口
	bool			_bPaused;			//暂停标记
};

NS_TOOL_FRAME_END
