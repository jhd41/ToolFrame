#include "MDestoryMonitor.h"

#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

MDestoryMonitor::MDestoryMonitor(void)
{
}

MDestoryMonitor::~MDestoryMonitor(void)
{
	CallFunction();
	Clear();
}

bool MDestoryMonitor::AddFunction( void(*fn)() )
{
	return DoAddFunction<void()>(fn);
}

bool MDestoryMonitor::AddFunction( bool(*fn)() )
{
	return DoAddFunction<bool()>(fn);
}

bool MDestoryMonitor::CallFunction()const
{
	VectorFunction::const_iterator itr;
	foreach(itr,_vFunction){
		IFunctionPtr ptr = *itr;
		ASSERT_LOG_ERROR(ptr);

		ptr->CallFunction();
	}

	return true;
}

bool MDestoryMonitor::Clear()
{
	_vFunction.clear();
	return true;
}

NS_TOOL_FRAME_END
