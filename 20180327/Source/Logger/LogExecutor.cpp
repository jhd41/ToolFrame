#include "LogExecutor.h"
#include "ToolPlat.h"
#include "ToolXml.h"
#include "ToolStd.h"

NS_TOOL_FRAME_BEGIN

bool InitLogExecutor(){return true;}//仅仅绕过编译器完全链接的执行代码

//////////////////////////////////////////////////////////////////////////
REGIST_LOG_EXECUTOR("Printer",CLogPrinterExecutor);
CLogPrinterExecutor::CLogPrinterExecutor(void)
{
}

CLogPrinterExecutor::~CLogPrinterExecutor(void)
{
}

bool CLogPrinterExecutor::ReadAttribute( const TiXmlElement* pxmlAttribute ,const MapStringString& vTemplateString)
{
	return true;
}

bool CLogPrinterExecutor::Init()
{
	return true;
}

bool CLogPrinterExecutor::LogMsg( const std::string& sMsg,const XLogLevel* pLogLevel )
{
	static boost::recursive_mutex g_mutex;
	boost::recursive_mutex::scoped_lock lock(g_mutex);
	ToolFrame::SetConsoleTextAttribute(pLogLevel->nColor);
	ToolFrame::OutPut(sMsg,pLogLevel->sLevel,pLogLevel->bTrace);
	return true;
}

bool CLogPrinterExecutor::Close()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
REGIST_LOG_EXECUTOR("Writer",CLogWriterExecutor);
CLogWriterExecutor::CLogWriterExecutor(void)
{
	_bFlush = false;

	SetBufferSize(1024);
	SetFilePath(ToolFrame::GetWriteableDir()+ToolFrame::GetProcessNameWithOutExt() + ".log");
}

CLogWriterExecutor::~CLogWriterExecutor(void)
{
}

bool CLogWriterExecutor::ReadAttribute( const TiXmlElement* pxmlAttribute ,const MapStringString& vTemplateString)
{
	int nBufferSize=0;std::string sFilePath;

	ToolFrame::SafeGetAttribute(pxmlAttribute,"IsFlush",	_bFlush,	false);
	ToolFrame::SafeGetAttribute(pxmlAttribute,"BufferSize",	nBufferSize,0);
	ToolFrame::SafeGetAttribute(pxmlAttribute,"FilePath",	sFilePath,	"");

	if (nBufferSize > 0)SetBufferSize(nBufferSize);

	//检查整理文件路径
	if (!sFilePath.empty())
	{
		ToolFrame::Replace(sFilePath,vTemplateString);
		if (!ToolFrame::IsAbsPath(sFilePath))
			sFilePath = ToolFrame::GetWriteableDir() + sFilePath;

		SetFilePath(sFilePath);
	}

	return true;
}

bool CLogWriterExecutor::Init()
{
	const std::string sDir = ToolFrame::PickDir(GetFilePath());
	if (!ToolFrame::MakeDir(sDir,DIR_TYPE_WRITEABLE))return false;
	return true;
}

bool CLogWriterExecutor::LogMsg( const std::string& sMsg,const XLogLevel* pLogLevel )
{
	boost::recursive_mutex::scoped_lock lock(_mutex);
	if (!ToolFrame::IsOpen(_fStream))
		if (!ToolFrame::OpenFile(_fStream,GetFilePath(),std::ios_base::out|std::ios_base::app))
			return false;

	_fStream<<sMsg<<std::endl;
	if (_bFlush)
		_fStream.flush();
	return true;
}

bool CLogWriterExecutor::Close()
{
	_fStream.close();
	return true;
}

NS_TOOL_FRAME_END
