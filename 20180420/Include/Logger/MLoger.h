#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

#include <boost/thread.hpp>
#include <boost/thread/recursive_mutex.hpp>

//��־��¼��
//���������� �� ��ʼ�� Ҳ����ֱ�ӳ�ʼ��
//˼·:��ӡ/д��־/����/�ȵȡ����Ǵ�����־��Ϣ�ķ�ʽ δ����취��չ
#include "tinyxml.h"
#include "MCreator.h"
#include "HLog.h"
#include "TThreadSaftyList.h"

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL ILogExecutor;
struct TOOLFRAME_DLL XLogLevel
{
	std::string		sLevel;
	ILogExecutor*	pLogExecutor;
	int				nColor;
	bool			bTrace;
};
class TOOLFRAME_DLL ILogExecutor
{
public:
	virtual bool SetThread(bool bThread){_bThread = bThread;return _bThread;}
	virtual bool IsThread()const{return _bThread;}
public:
	virtual bool ReadAttribute(const TiXmlElement* pxmlAttribute,const MapStringString& vTemplateString)=0;

	virtual bool Init()=0;
	virtual bool LogMsg(const std::string& sMsg,const XLogLevel* pLogLevel)=0;
	virtual bool Close()=0;
public:
	ILogExecutor(){_bThread = false;}
	virtual ~ILogExecutor(){}
private:
	bool _bThread;
};

typedef std::vector<XLogLevel>					VectorXLogLevel;
typedef std::map<std::string,VectorXLogLevel>	MapLogLevel;

typedef std::map<std::string,ILogExecutor*>		MapExecutor;

typedef ILogExecutor*	ILogExecutorPtr;
typedef ILogExecutorPtr (*FnCreateLogExecutor)();
typedef MMultiMap<std::string,FnCreateLogExecutor,ILogExecutor> MLogExecutorCreater;

#define CREATE_FUN_LOG_EXECUTOR(className)		FUN_CREATE(className,ILogExecutorPtr)
#define REGIST_LOG_EXECUTOR(key,className)		MMULTIMAP_REGIST_CREATE_FUN(MLogExecutorCreater,key,className,className) 
#define CREATE_LOG_EXECUTOR(key)				MMULTIMAP_CREATE(key,ILogExecutorPtr,std::string,FnCreateLogExecutor,MLogExecutorCreater)

class TOOLFRAME_DLL MLoger
{
	ST_INTANCE(MLoger);
private:
	struct SQueueNode{
		std::string			sMsg;
		const XLogLevel*	pLogLevel;
		
		SQueueNode(const std::string& msg,const XLogLevel*	p){
			sMsg		= msg;
			pLogLevel	= p;
		}
	};
	typedef boost::shared_ptr<SQueueNode>			SQueueNodePtr;
	typedef TThreadSaftyListValue<SQueueNodePtr> 	QueueThread;	
public:
	bool SetHandler(HLog* pHandler);
	bool SetTag(const std::string& sTag);
	bool Init(const std::string& sConfigPath = "LogCfg.xml");
	bool IsInitded()const;
	const std::string& GetTag()const;
	void ShutDown();
public:
	const VectorXLogLevel* PreLogMsg(const std::string& sLogLevel);
	bool LogMsg( const std::string& sLogLevel,const std::stringstream& sStreamLog,const VectorXLogLevel* pvLogExecutor );
private:
	bool ReadConfig(const std::string& sPath);	//��ȡ�����ļ�

	void RunThread();
private:
	MLoger(void);
	virtual ~MLoger(void);
private:
	HLog*			_pHandler;
	std::string		_sTag;
	bool			_bInit;
	volatile bool	_bStop;

	bool			_bStartThread;		//�����߳�
	volatile bool	_bThreadStoped;		//�߳��Ƿ�ر�
	boost::recursive_mutex _mutexInit;
	boost::recursive_mutex _mutexClose;

	MapExecutor		_vExecutor;			//ִ����<name,Executor>
	MapLogLevel		_vLogLevel;			//��־�ȼ�<loglevel,XLogLevel>
	QueueThread		_vQueueThread;		//�߳���Ϣ����
};

#define LOG_MSG(logGrade,msg)			{																											\
											const ToolFrame::VectorXLogLevel* pvLogExecutor = ToolFrame::MLoger::Singleton().PreLogMsg(logGrade);	\
											if (pvLogExecutor)																						\
											{																										\
												std::stringstream sStreamToolFrameLog;																\
												sStreamToolFrameLog<<msg;																			\
												ToolFrame::MLoger::Singleton().LogMsg(logGrade,sStreamToolFrameLog,pvLogExecutor);					\
											}																										\
										}

//ע��:��־�ȼ���
//Debug�ȼ�(DEBUGģʽ�����ñ�����������)
#if MACRO_TARGET_VER == MACRO_VER_DEBUG
	//Debug(����)
	#define LOG_DEBUG(msg)							LOG_MSG("Debug",msg<<FUN_FILE_LINE)
	#define LOG_DEBUG_EXP(exp)						exp
	#define IF_DEBUG(exp)							if (exp){LOG_DEBUG(#exp)}
	#define IF_DEBUG_MSG(exp,msg)					if (exp){LOG_DEBUG(#exp<<";"<<msg)}

	//DebugErr(���Դ���)
	#define LOG_DEBUG_ERR(msg)						LOG_MSG("DebugErr",msg<<FUN_FILE_LINE)
	#define ASSERT_LOG_DEBUG_ERR(exp)				if (!(exp)){LOG_DEBUG_ERR(#exp)}
	#define ASSERT_LOG_DEBUG_ERR_MSG(exp,msg)		if (!(exp)){LOG_DEBUG_ERR(#exp<<";"<<msg)}
	#define ASSERT_LOG_DEBUG_ERR_INT(nErrCode,exp)	{int nErr = (exp); if ((nErrCode != nErr)){LOG_DEBUG_ERR(#exp<<";"<<nErr)}}
	#define IF_LOG_DEBUG_ERR(exp)					if (exp){LOG_DEBUG_ERR(#exp)}
	#define IF_LOG_DEBUG_ERR_MSG(exp,msg)			if (exp){LOG_DEBUG_ERR(#exp<<";"<<msg)}

	//NetDebug(�������)
	#define LOG_NET_DEBUG(msg)						LOG_MSG("NetDebug",msg<<FUN_FILE_LINE)
#else
	//Debug
	#define LOG_DEBUG(msg)
	#define LOG_DEBUG_EXP(exp)						

	//DebugErr
	#define LOG_DEBUG_ERR(msg)						
	#define ASSERT_LOG_DEBUG_ERR(exp)				
	#define ASSERT_LOG_DEBUG_ERR_MSG(exp,msg)
	#define ASSERT_LOG_DEBUG_ERR_INT(nErrCode,exp)

	//NetDebug(�������)
	#define LOG_NET_DEBUG(msg)					
#endif // MACRO_TARGET_VER == MACRO_VER_DEBUG

//System(ϵͳ)
#define LOG_SYSTEM(msg)							LOG_MSG("System",msg)

//Warning(����)
#define LOG_WARNING(msg)						LOG_MSG("Warning",msg)

//Fatal(����)
#define LOG_FATAL(msg)							LOG_MSG("Fatal",msg)
#define ASSERT_LOG_FATAL(exp)					if (!(exp)){LOG_FATAL(#exp)}
#define ASSERT_LOG_FATAL_MSG(exp)				if (!(exp)){LOG_FATAL(#exp<<";"<<msg)}

//NetErr(�������)
#define LOG_NET_ERR(msg)						LOG_MSG("NetErr",msg<<FUN_FILE_LINE)
#define ASSERT_LOG_NET_ERR(exp)					if (!(exp)){LOG_NET_ERR(#exp)}

//ClientErr(�ͻ��˴���)
#define LOG_CLIENT_ERR()							LOG_MSG("ClientErr",FUN_FILE_LINE)
#define LOG_CLIENT_ERR_MSG(msg)						LOG_MSG("ClientErr",msg<<FUN_FILE_LINE)
#define ASSERT_LOG_CLIENT_ERR(exp)					if (!(exp)){LOG_CLIENT_ERR_MSG(#exp)}
#define ASSERT_LOG_CLIENT_ERR_MSG(exp,msg)			if (!(exp)){LOG_CLIENT_ERR_MSG(#exp<<";"<<msg)}
#define ASSERT_LOG_CLIENT_ERR_RETURN(exp)			if (!(exp)){LOG_CLIENT_ERR_MSG(#exp);return;}
#define ASSERT_LOG_CLIENT_ERR_MSG_RETURN(exp,msg)	if (!(exp)){LOG_CLIENT_ERR_MSG(#exp<<";"<<msg);return;}

#define ASSERT_LOG_CLIENT_ERR_RETURN_VAL(exp,val)	if (!(exp)){LOG_CLIENT_ERR_MSG(#exp);return val;}
#define ASSERT_LOG_CLIENT_ERR_RETURN_FALSE(exp)		ASSERT_LOG_CLIENT_ERR_RETURN_VAL(exp,false);

//Error(����)
#define LOG_ERROR()								LOG_MSG("Error",FUN_FILE_LINE)
#define LOG_ERROR_MSG(msg)						LOG_MSG("Error",msg<<FUN_FILE_LINE)
#define ASSERT_LOG_ERROR(exp)					if (!(exp)){LOG_ERROR_MSG(#exp)}
#define ASSERT_LOG_ERROR_MSG(exp,msg)			if (!(exp)){LOG_ERROR_MSG(#exp<<";"<<msg)}
#define ASSERT_LOG_ERROR_RETURN(exp)			if (!(exp)){LOG_ERROR_MSG(#exp);return;}
#define ASSERT_LOG_ERROR_RETURN_MSG(exp,msg)	if (!(exp)){LOG_ERROR_MSG(#exp<<";"<<msg);return;}
#define ASSERT_LOG_ERROR_CONTINUE(exp)			if (!(exp)){LOG_ERROR_MSG(#exp);continue;}
#define ASSERT_LOG_ERROR_CONTINUE_MSG(exp,msg)	if (!(exp)){LOG_ERROR_MSG(#exp<<";"<<msg);continue;}

#define ASSERT_LOG_ERROR_INT(nErrCode,exp)		{int nErr = (exp); if ((nErrCode != nErr)){LOG_ERROR_MSG(#exp<<";"<<nErr)}}
#define ASSERT_LOG_ERROR_INT_RETURN(nErrCode,exp,nReturn)		{int nErr = (exp); if ((nErrCode != nErr)){LOG_ERROR_MSG(#exp<<";"<<nErr);return nReturn;}}

#define IF_LOG_ERROR(exp)						if (exp){LOG_ERROR_MSG(#exp)}
#define IF_LOG_ERROR_MSG(exp,msg)				if (exp){LOG_ERROR_MSG(#exp<<";"<<msg)}

#define LOG_ERROR_CLASS()						LOG_MSG("Error",FUN_FILE_LINE_CLASS)
#define LOG_ERROR_MSG_CLASS(msg)				LOG_MSG("Error",msg<<FUN_FILE_LINE_CLASS)
#define ASSERT_LOG_ERROR_CLASS(exp)				if (!(exp)){LOG_ERROR_MSG_CLASS(#exp)}
#define ASSERT_LOG_ERROR_MSG_CLASS(exp,msg)		if (!(exp)){LOG_ERROR_MSG_CLASS(#exp<<";"<<msg)}

//Lua(Lua�ű�)
#define LOG_LUA(msg)							LOG_MSG("Lua",msg)
#define LOG_LUA_DEBUG(msg)						LOG_MSG("LuaDebug",msg)
#define LOG_LUA_ERR(msg)						LOG_MSG("LuaErr",msg)

NS_TOOL_FRAME_END
