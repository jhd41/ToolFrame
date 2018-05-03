#pragma once
#include "Macro.h"
#include "TThreadSaftyMap.h"
#include "CalCounter.h"
#include "TimeAvg.h"
#include "TimeElapse.h"

NS_TOOL_FRAME_BEGIN

//调试类 (多线程安全)
class MDebug
{
	struct XElapsedInfo
	{
		mutable CMutexReadWrite	_mutex;
		CTimeAvg				_tTimeAvg;		//平均流逝时间
		uint64					_uTimeLast;		//最近一次运行使用时间
		uint64					_uTimeMin;		//最短用时
		uint64					_uTimeMax;		//最长用时
		uint					_uCount;		//次数
		int						_uUsing;		//正在使用
		uint64					_uTotal;		//总计用时
		XElapsedInfo() {
			_uTimeLast = 0;
			_uTimeMin = 0;
			_uTimeMax = 0;
			_uCount = 0;
			_uUsing = 0;
			_uTotal = 0;
		}
		XElapsedInfo& operator = (const XElapsedInfo& info) {
			CLockWrite lockInfo(info._mutex);
			CLockWrite lock(_mutex);

			_uTimeLast = info._uTimeLast;
			_uTimeMin = info._uTimeMin;
			_uTimeMax = info._uTimeMax;
			_uCount = info._uCount;
			_uUsing = info._uUsing;
			_uTotal = info._uTotal;
			return *this;
		}

	};

	typedef TThreadSaftyMapValue<std::string, CCalCounterInt>	MapTagCount;
	typedef TThreadSaftyMapValue<std::string, XElapsedInfo>		MapTagElapsed;

	typedef std::vector<PairStringUint64>		VectorTagTime;
	struct XTimeChain
	{
		mutable CMutexReadWrite	_mutex;
		std::string				_sType;		//链条类型
		std::string				_sID;		//ID
		VectorTagTime			_vTagTime;	//标记时间
		XTimeChain() {
		}
		XTimeChain& operator = (const XTimeChain& info) {
			CLockWrite lockInfo(info._mutex);
			CLockWrite lock(_mutex);

			_sType		= info._sType;
			_sID		= info._sID;
			_vTagTime	= info._vTagTime;
			return *this;
		}
	};

	typedef TThreadSaftyMapValue<PairStringString, XTimeChain>	MapTimeChain;
public:
	ST_INTANCE(MDebug);
public:
	//用于统计某个点触发的次数
	virtual bool Point(const std::string& sTag);	

	//用于统计某个点是否成对抵消
	virtual bool PointRetain(const std::string& sTag);
	virtual bool PointReduce(const std::string& sTag);

	//用于统计时间损耗
	virtual bool ElapsedRetain(const std::string& sTag);
	virtual bool ElapsedReduce(const std::string& sTag, uint64 uTimeElapsed);

	//用于统计某些点间的时间损耗(时间链)
	virtual bool TimeChain(const std::string& sType, const std::string& sID,const std::string& sTag);
public:
	virtual std::string DebugString(const VectorString& vDebug)const;//获取调试信息
public:
	const MapTagCount& GetTagCount()const;
public:
	MDebug();
	virtual ~MDebug();
private:
	MapTagCount		_vTagCount;
	MapTagElapsed	_vTagElapsed;
	MapTimeChain	_vTimeChain;
};

//////////////////////////////////////////////////////////////////////////
class CDebugElapsed
{
public:
	 bool SetTag(const std::string& sTag);
public:
	CDebugElapsed();
	CDebugElapsed(const std::string& sTag);
	~CDebugElapsed();//为提升性能 故意不写虚析构
private:
	std::string _sTag;
	CTimeElapse	_tTimeElapse;	//时间流逝
};

NS_TOOL_FRAME_END

//DEBUG模式下启用避免性能消耗
#if MACRO_TARGET_VER == MACRO_VER_DEBUG
	#define DEBUG_POINT_TAG(tag)			ToolFrame::MDebug::Singleton().Point(tag);
	#define DEBUG_POINT()					{std::stringstream sStreamToolFrameDebug;sStreamToolFrameDebug<<FUN_FILE_LINE; ToolFrame::MDebug::Singleton().Point(sStreamToolFrameDebug.str());}
	#define DEBUG_POINT_IF(exp)				if(exp){DEBUG_POINT;}
	#define DEBUG_POINT_IF_TAG(exp,tag)		if(exp,tag){DEBUG_POINT_TAG(tag;}

	#define DEBUG_RETAIN_REF(tag)			ToolFrame::MDebug::Singleton().PointRetain(tag);
	#define DEBUG_REDUCE_REF(tag)			ToolFrame::MDebug::Singleton().PointReduce(tag);
	#define DEBUG_RETAIN_REF_IF(exp,tag)	if(exp){DEBUG_RETAIN_REF(tag);}
	#define DEBUG_REDUCE_REF_IF(exp,tag)	if(exp){DEBUG_REDUCE_REF(tag);}

	//该函数放置在刚刚进入函数时 可以统计函数调用时间
	#define DEBUG_FUN()						ToolFrame::CDebugElapsed xToolFrameDebugElapsed(FUN_FILE_LINE);

	//统计类的构造析构时间
	#define DEBUG_CLASS						ToolFrame::CDebugElapsed _xToolFrameDebugClass;
	//初始化调试类的代码，只要不放置在构造、析构函数中即可检测
	#define DEBUG_CLASS_INIT()				_xToolFrameDebugClass.SetTag(ToolFrame::GetTypeName(this));

	//时间链
	#define DEBUG_TIME_CHAIN_TAG(type,id,tag)	{std::stringstream sStreamType,sStreamID,sStreamTag;sStreamType<<type;sStreamID<<id;sStreamTag<<tag;ToolFrame::MDebug::Singleton().TimeChain(sStreamType.str(),sStreamID.str(),sStreamTag.str());}
	#define DEBUG_TIME_CHAIN(type,id)			DEBUG_TIME_CHAIN_TAG(type,id,FUN_FILE_LINE);
	#define DEBUG_TIME_CHAIN_DEFAULT(id,tag)	DEBUG_TIME_CHAIN_TAG("Default",id,FUN_FILE_LINE);
#else

	#define DEBUG_POINT_TAG(tag)
	#define DEBUG_POINT()		
	#define DEBUG_POINT_IF(exp)
	#define DEBUG_POINT_IF_TAG(exp,tag)

	#define DEBUG_RETAIN_REF(tag)	
	#define DEBUG_REDUCE_REF(tag)
	#define DEBUG_RETAIN_REF_IF(exp,tag)
	#define DEBUG_REDUCE_REF_IF(exp,tag)
	
	#define DEBUG_FUN()
	#define DEBUG_CLASS	
	#define DEBUG_CLASS_INIT()

	#define DEBUG_TIME_CHAIN_TAG(type,id,tag)
	#define DEBUG_TIME_CHAIN(type,id)			
	#define DEBUG_TIME_CHAIN_DEFAULT(id,tag)	

#endif // MACRO_TARGET_VER == MACRO_VER_DEBUG

