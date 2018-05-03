#include "MLoger.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

MLoger::MLoger(void)
{
	_bInit = false;
	_bStop = false;
	_bStartThread=false;
	_bThreadStoped = true;
	_pHandler = nullptr;
}

MLoger::~MLoger(void)
{
	ShutDown();

	ToolFrame::Delete(_vExecutor);		//非线程执行器
}

bool MLoger::Init( const std::string& sConfigPath /*= "LogCfg.xml"*/ )
{
	if (IsInitded())return false;
	if (!ReadConfig(sConfigPath))return false;

	//初始化执行器
	if (!_vExecutor.empty())
	{
		MapExecutor::iterator itr;
		foreach(itr,_vExecutor){
            if(!itr->second->Init())return false;
		}
	}

	//启动线程
	if (_bStartThread){
		_bThreadStoped = false;
		boost::thread thrd(boost::bind(&MLoger::RunThread, this));
	}

	_bInit = true;

	if (_pHandler && !_pHandler->OnLogInited())return false;
	return true;
}

bool MLoger::ReadConfig( const std::string& sPath /*= "LogCfg.xml"*/ )
{
	TiXmlDocument xml;
    
    std::string sFile = ToolFrame::LoadFile(sPath);
	if(!ToolFrame::Parse(xml,sFile))return false;
	TiXmlElement* pRoot = ToolFrame::GetElement(&xml,"LogCfg");
	if (!pRoot)return false;

	//创建通配符
	std::string sDateTime = ToolFrame::GetNowTimeString();
	ToolFrame::Replace(sDateTime,":","-");//路径不能出现冒号

	MapStringString vTemplateString;
	if (!ToolFrame::Insert(vTemplateString,"{ProcessName}",	ToolFrame::GetProcessNameWithOutExt()))return false;
	if (!ToolFrame::Insert(vTemplateString,"{WriteableDir}",ToolFrame::GetWriteableDir()))return false;
	if (!ToolFrame::Insert(vTemplateString,"{WorkDir}",		ToolFrame::GetWorkingDir()))return false;
	if (!ToolFrame::Insert(vTemplateString,"{CacheDir}",	ToolFrame::GetCacheDir()))return false;
	if (!ToolFrame::Insert(vTemplateString,"{DateTime}",	sDateTime))return false;
	if (!ToolFrame::Insert(vTemplateString,"{Tag}",			_sTag))return false;

	//读取LogExecutor
	{
		VectorElement vXmlNode;
		if (!ToolFrame::GetElement(vXmlNode,pRoot,"LogExecutor"))return false;
		VectorElement::const_iterator itr;
		foreach(itr,vXmlNode){
			const TiXmlElement* pXmlExecutor = *itr;
			if (!pXmlExecutor)return false;

			bool bEnable = false;std::string sName;std::string sType;bool bThread = false;
			ToolFrame::SafeGetAttribute(pXmlExecutor,"Enable",		bEnable,true);
			ToolFrame::SafeGetAttribute(pXmlExecutor,"Name",		sName,	"");
			ToolFrame::SafeGetAttribute(pXmlExecutor,"Type",		sType,	"");
			ToolFrame::SafeGetAttribute(pXmlExecutor,"IsThread",	bThread,false);
			if (bEnable)
			{
				ILogExecutor* pLogExecutor = CREATE_LOG_EXECUTOR(sType);
				if (pLogExecutor)
				{
					pLogExecutor->SetThread(bThread);
					pLogExecutor->ReadAttribute(pXmlExecutor,vTemplateString);
					if (!ToolFrame::Insert(_vExecutor,sName,pLogExecutor))return false;
				}
			}
		}
	}
	//读取日志项
	{
		VectorElement vXmlNode;
		if (!ToolFrame::GetElement(vXmlNode,pRoot,"LogLevel"))return false;
		VectorElement::const_iterator itr;
		foreach(itr,vXmlNode){
			const TiXmlElement* pXmlLogLevel = *itr;
			if (!pXmlLogLevel)return false;

			bool bEnable = false;XLogLevel xLevel;std::string sExecutorName;
			ToolFrame::SafeGetAttribute(pXmlLogLevel,"Enable",		bEnable,				true);

			ToolFrame::SafeGetAttribute(pXmlLogLevel,"LogExecutor",	sExecutorName,			"");
			ToolFrame::SafeGetAttribute(pXmlLogLevel,"Level",		xLevel.sLevel,			"");
			ToolFrame::SafeGetAttribute(pXmlLogLevel,"Color",		xLevel.nColor,			0);
			ToolFrame::SafeGetAttribute(pXmlLogLevel,"Trace",		xLevel.bTrace,			true);

			if (bEnable)
			{
				ILogExecutor* pLogExecutor = ToolFrame::GetPtrValueByKey(_vExecutor,sExecutorName);
				if (pLogExecutor){
					if (pLogExecutor->IsThread())
						_bStartThread = true; 
					xLevel.pLogExecutor = pLogExecutor;
					if (!ToolFrame::InsertVector(_vLogLevel,xLevel.sLevel,xLevel))return false;
				}
			}
		}
	}
	return true;
}

const VectorXLogLevel* MLoger::PreLogMsg( const std::string& sLogLevel ) 
{
	if (!IsInitded())
	{
		boost::recursive_mutex::scoped_lock lLock(_mutexInit);
		if (!IsInitded() && !Init())return nullptr;
	}

	//日志执行器
	const VectorXLogLevel* pvLogExecutor = ToolFrame::GetValuePtrByKey(_vLogLevel,sLogLevel);
	if (!pvLogExecutor || pvLogExecutor->empty())return nullptr;
	return pvLogExecutor;
}

bool MLoger::LogMsg( const std::string& sLogLevel,const std::stringstream& sStreamLog,const VectorXLogLevel* pvLogExecutor )
{
	if (!pvLogExecutor || pvLogExecutor->empty())return false;

	//回调
	if (_pHandler && !_pHandler->OnLogMsg(sLogLevel,sStreamLog))return false;

	//准备要写的信息
	std::stringstream sStream ;
	sStream<<"["<<ToolFrame::GetNowTimeString()<<"]["<<sLogLevel<<"]"<<ToolFrame::RemoveReturn(sStreamLog.str());

	std::string sMsgFull = sStream.str();

	VectorXLogLevel::const_iterator itr;
	foreach(itr,*pvLogExecutor){
		const XLogLevel& xLogLevel = *itr;
		ILogExecutor* pLogExecutor = xLogLevel.pLogExecutor;
		if (pLogExecutor){
			if (!pLogExecutor->IsThread())
				pLogExecutor->LogMsg(sMsgFull,&xLogLevel);
			else
				_vQueueThread.Push(SQueueNodePtr(new SQueueNode(sMsgFull,&xLogLevel)));
		}
	}

	return true;
}

void MLoger::ShutDown()
{
	//关闭的 时候需要阻塞一下
	boost::recursive_mutex::scoped_lock lLock(_mutexClose);
	
	if(_bStop)return;

	_bStop = true;
	while (!_bThreadStoped)
		ToolFrame::Sleep(100);

	if (!_vExecutor.empty())
	{
		MapExecutor::iterator itr;
		foreach(itr,_vExecutor){
			itr->second->Close();
		}
	}

	_pHandler = nullptr;
}

bool MLoger::IsInitded()const
{
	return _bInit;
}

void MLoger::RunThread()
{
	while (!_bStop)
	{
		//这个花括号很关键(当进行写入的时候线程上锁,其他线程无法shutdown,执行完之后进行睡觉，其他线程才执行shutdown,下次循环就主动退出了)
		{
			boost::recursive_mutex::scoped_lock lLock(_mutexClose);

			SQueueNodePtr ptr;
			while(ptr = _vQueueThread.PopFrontPtr() ){
				const SQueueNode& node = *ptr;
				node.pLogLevel->pLogExecutor->LogMsg(node.sMsg,node.pLogLevel);
			}
		}

		ToolFrame::Sleep(100);
	}

	_bThreadStoped = true;
}

bool MLoger::SetHandler( HLog* pHandler )
{
	_pHandler = pHandler;
	return true;
}

bool MLoger::SetTag( const std::string& sTag )
{
	_sTag = sTag;
	return true;
}

const std::string& MLoger::GetTag() const
{
	return _sTag;
}

NS_TOOL_FRAME_END
