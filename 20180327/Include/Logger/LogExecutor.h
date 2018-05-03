#pragma once

#include "Macro.h"
#include "MLoger.h"
#include <iostream>

NS_TOOL_FRAME_BEGIN

//日志打印器
//////////////////////////////////////////////////////////////////////////
class CLogPrinterExecutor :
	public ILogExecutor
{
	CREATE_FUN_LOG_EXECUTOR(CLogPrinterExecutor);

	struct SLevelInfo{
		std::string sLevel;
		bool		bPrint;
		int			nColor;
		bool		bTrace;
	};
	typedef std::map<std::string,SLevelInfo*> MapLevelInfo;
public:
	virtual bool ReadAttribute(const TiXmlElement* pxmlAttribute,const MapStringString& vTemplateString)override;

	virtual bool Init()override;
	virtual bool LogMsg(const std::string& sMsg,const XLogLevel* pLogLevel)override;
	virtual bool Close()override;
public:
	CLogPrinterExecutor(void);
	virtual ~CLogPrinterExecutor(void);
};

//日志写入器
//////////////////////////////////////////////////////////////////////////
class CLogWriterExecutor :
	public ILogExecutor
{
	CREATE_FUN_LOG_EXECUTOR(CLogWriterExecutor);
public:
	virtual bool ReadAttribute(const TiXmlElement* pxmlAttribute,const MapStringString& vTemplateString)override;

	virtual bool Init()override;
	virtual bool LogMsg(const std::string& sMsg,const XLogLevel* pLogLevel)override;
	virtual bool Close()override;
public:
	CLogWriterExecutor(void);
	virtual ~CLogWriterExecutor(void);
private:
	CFIELD_INT(BufferSize);
	CFIELD_STRING(FilePath);

	std::fstream _fStream;
	bool		_bFlush;

	boost::recursive_mutex _mutex;
};

NS_TOOL_FRAME_END
