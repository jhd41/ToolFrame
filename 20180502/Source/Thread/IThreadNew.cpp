#include "IThreadNew.h"

#include "MacroDefineBoost.h"
#include "MLoger.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

IThreadNew::IThreadNew(void)
{
	_bReqStop = false;
	_uTimeInterval = 0;
	_pThread= nullptr;
	_bReqInterrupt = false;
	_bInterrupted = false;
}

IThreadNew::~IThreadNew(void)
{
	StopThread();

	//结束线程
	delete _pThread;
}

bool IThreadNew::StartThread( uint uTimeInterval/*=50*/ )
{
	if (_bReqStop)return false;
	if (_pThread)return false;

	if (!IThread::StartThread())return false;

	_uTimeInterval = uTimeInterval;

	_pThread = new boost::thread(boost::bind(&IThreadNew::RunThread, this));
	return true;
}

void IThreadNew::RunThread()
{
	SetThreadStarted();

	try
	{
		//初始化线程
		ToolFrame::Srand();//新版本需要重新补充 为每个线程初始化 随机种子

		do 
		{
			if (_bReqStop || !InitThread())break;
			while (!_bReqStop && RunOnceThread())
				ToolFrame::Sleep(_uTimeInterval);
		} while (false);
	}
	catch (CExceptionThreadInterrupt&)
	{
		_bInterrupted = true;
		OnInterrupted();
	}

	SetThreadStoped();

	//删除自己
	if (IsAutoRelease())
		delete this;
}

bool IThreadNew::ReqStopThread()
{
	_bReqStop = true;
	return true;
}

bool IThreadNew::Interrupt()
{
	if (_pThread)
		_pThread->interrupt();

	SetThreadStoped();
	return true;
}

bool IThreadNew::IsReqStopThread()const
{
	return _bReqStop;
}

bool IThreadNew::IsReqInterrupt() const
{
	return _bReqInterrupt;
}

bool IThreadNew::ReqInterrupt()
{
	_bReqInterrupt = true;
	return true;
}

bool IThreadNew::InterruptPoint()
{
	if (!_bReqInterrupt)return false;

	//抛 线程打断
	throw CExceptionThreadInterrupt();
	return true;
}

bool IThreadNew::OnInterrupted()
{
	return true;
}

bool IThreadNew::SetTimeInterval( uint uTimeInterval )
{
	_uTimeInterval = uTimeInterval;
	return true;
}

uint IThreadNew::GetTimeInterval() const
{
	return _uTimeInterval;
}

bool IThreadNew::IsInterrupted() const
{
	return _bInterrupted;
}

NS_TOOL_FRAME_END
