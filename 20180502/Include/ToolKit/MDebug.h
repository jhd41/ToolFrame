#pragma once
#include "Macro.h"
#include "TThreadSaftyMap.h"
#include "CalCounter.h"
#include "TimeAvg.h"
#include "TimeElapse.h"

NS_TOOL_FRAME_BEGIN

//������ (���̰߳�ȫ)
class MDebug
{
	struct XElapsedInfo
	{
		mutable CMutexReadWrite	_mutex;
		int						_uUsing;		//����ʹ��

		bool					_bFirst;		//�״α�ʶ
		uint64					_uElapsedFirst;	//��һ������ʹ��ʱ��

		CTimeAvg				_tTimeAvg;		//ƽ������ʱ��
		uint64					_uElapsedLast;	//���һ������ʹ��ʱ��
		uint64					_uTimeMin;		//�����ʱ
		uint64					_uTimeMax;		//���ʱ
		uint					_uCount;		//����
		
		uint64					_uTotal;		//�ܼ���ʱ

		uint64					_uInvaild;		//��Ч�Ĵ���
		uint64					_uInvaildTotal;	//�ܼ���Ч��ʱ
		XElapsedInfo() {
			_uUsing = 0;

			_bFirst = true;
			_uElapsedFirst = 0;
			_uElapsedLast = 0;
			_uTimeMin = 0;
			_uTimeMax = 0;
			_uCount = 0;
			
			_uTotal = 0;

			_uInvaild = 0;
			_uInvaildTotal = 0;
		}
		XElapsedInfo& operator = (const XElapsedInfo& info) {
			CLockWrite lockInfo(info._mutex);
			CLockWrite lock(_mutex);

			_uUsing = info._uUsing;

			_bFirst = info._bFirst;
			_uElapsedFirst = info._uElapsedFirst;
			_uElapsedLast = info._uElapsedLast;
			_uTimeMin = info._uTimeMin;
			_uTimeMax = info._uTimeMax;
			_uCount = info._uCount;
			
			_uTotal = info._uTotal;

			_uInvaild = info._uInvaild;
			_uInvaildTotal = info._uInvaildTotal;
			return *this;
		}

	};

	typedef TThreadSaftyMapValue<std::string, CCalCounterInt>	MapTagCount;
	typedef TThreadSaftyMapValue<std::string, XElapsedInfo>		MapTagElapsed;

	typedef std::vector<PairStringUint64>		VectorTagTime;
	struct XTimeChain
	{
		mutable CMutexReadWrite	_mutex;
		std::string				_sType;		//��������
		std::string				_sID;		//ID
		VectorTagTime			_vTagTime;	//���ʱ��
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
	//����ͳ��ĳ���㴥���Ĵ���
	virtual bool Point(const std::string& sTag);	

	//����ͳ��ĳ�����Ƿ�ɶԵ���
	virtual bool PointRetain(const std::string& sTag);
	virtual bool PointReduce(const std::string& sTag);

	//����ͳ��ʱ�����
	virtual bool ElapsedRetain(const std::string& sTag);
	virtual bool ElapsedReduce(const std::string& sTag, uint64 uTimeElapsed,bool bInvaild = false);

	//����ͳ��ĳЩ����ʱ�����(ʱ����)
	virtual bool TimeChain(const std::string& sType, const std::string& sID,const std::string& sTag);
public:
	virtual std::string DebugString(const VectorString& vDebug)const;//��ȡ������Ϣ
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
	 bool ReStart();	//���¼�ʱ
	 bool SetInvaild(bool bInvaild = true);	//��Ч��
public:
	CDebugElapsed();
	CDebugElapsed(const std::string& sTag);
	~CDebugElapsed();//Ϊ�������� ���ⲻд������
private:
	std::string _sTag;
	CTimeElapse	_tTimeElapse;	//ʱ������
	bool		_bInvaild;
};

NS_TOOL_FRAME_END

//DEBUGģʽ�����ñ�����������
#if MACRO_TARGET_VER == MACRO_VER_DEBUG
	#define DEBUG_FUNC(func)				func

	#define DEBUG_POINT_TAG(tag)			{std::stringstream sStreamToolFrameDebug;sStreamToolFrameDebug<<tag; ToolFrame::MDebug::Singleton().Point(sStreamToolFrameDebug.str());}
	#define DEBUG_POINT()					{std::stringstream sStreamToolFrameDebug;sStreamToolFrameDebug<<FUN_FILE_LINE; ToolFrame::MDebug::Singleton().Point(sStreamToolFrameDebug.str());}
	#define DEBUG_POINT_FUN()				{std::stringstream sStreamToolFrameDebug;sStreamToolFrameDebug<<__FUNCTION__; ToolFrame::MDebug::Singleton().Point(sStreamToolFrameDebug.str());}			
	#define DEBUG_POINT_IF(exp)				if(exp){DEBUG_POINT;}
	#define DEBUG_POINT_IF_TAG(exp,tag)		if(exp,tag){DEBUG_POINT_TAG(tag;}

	#define DEBUG_RETAIN_REF(tag)			ToolFrame::MDebug::Singleton().PointRetain(tag);
	#define DEBUG_REDUCE_REF(tag)			ToolFrame::MDebug::Singleton().PointReduce(tag);
	#define DEBUG_RETAIN_REF_IF(exp,tag)	if(exp){DEBUG_RETAIN_REF(tag);}
	#define DEBUG_REDUCE_REF_IF(exp,tag)	if(exp){DEBUG_REDUCE_REF(tag);}

	//�ú��������ڸոս��뺯��ʱ ����ͳ�ƺ�������ʱ��
	#define DEBUG_FUN_TAG(tag)				ToolFrame::CDebugElapsed xToolFrameDebugElapsed;{std::stringstream sStream;sStream<<tag;xToolFrameDebugElapsed.SetTag(sStream.str());}
	#define DEBUG_FUN()						DEBUG_FUN_TAG(FUN_FILE_LINE);
	#define DEBUG_FUN_INVAILD()				xToolFrameDebugElapsed.SetInvaild();

	//ͳ����Ĺ�������ʱ��
	#define DEBUG_CLASS						ToolFrame::CDebugElapsed _xToolFrameDebugClass;
	//��ʼ��������Ĵ��룬ֻҪ�������ڹ��졢���������м��ɼ��
	#define DEBUG_CLASS_INIT()				_xToolFrameDebugClass.SetTag(ToolFrame::GetTypeName(this));
	#define DEBUG_CLASS_INIT_TAG(tag)		_xToolFrameDebugClass.SetTag(tag);
	#define DEBUG_CLASS_RESTART()			_xToolFrameDebugClass.ReStart();

	//ʱ����
	#define DEBUG_TIME_CHAIN_TAG(type,id,tag)	{std::stringstream sStreamType,sStreamID,sStreamTag;sStreamType<<type;sStreamID<<id;sStreamTag<<tag;ToolFrame::MDebug::Singleton().TimeChain(sStreamType.str(),sStreamID.str(),sStreamTag.str());}
	#define DEBUG_TIME_CHAIN(type,id)			DEBUG_TIME_CHAIN_TAG(type,id,FUN_FILE_LINE);
	#define DEBUG_TIME_CHAIN_DEFAULT(id,tag)	DEBUG_TIME_CHAIN_TAG("Default",id,FUN_FILE_LINE);
#else
	#define DEBUG_FUNC(func)

	#define DEBUG_POINT_TAG(tag)
	#define DEBUG_POINT()		
	#define DEBUG_POINT_FUN()	
	#define DEBUG_POINT_IF(exp)
	#define DEBUG_POINT_IF_TAG(exp,tag)

	#define DEBUG_RETAIN_REF(tag)	
	#define DEBUG_REDUCE_REF(tag)
	#define DEBUG_RETAIN_REF_IF(exp,tag)
	#define DEBUG_REDUCE_REF_IF(exp,tag)
	
	#define DEBUG_FUN_TAG(tag)
	#define DEBUG_FUN()
	#define DEBUG_FUN_INVAILD()

	#define DEBUG_CLASS	
	#define DEBUG_CLASS_INIT()
	#define DEBUG_CLASS_INIT_TAG(tag)
	#define DEBUG_CLASS_RESTART()
	#define DEBUG_FUN_INVAILD()

	#define DEBUG_TIME_CHAIN_TAG(type,id,tag)
	#define DEBUG_TIME_CHAIN(type,id)			
	#define DEBUG_TIME_CHAIN_DEFAULT(id,tag)	

#endif // MACRO_TARGET_VER == MACRO_VER_DEBUG

