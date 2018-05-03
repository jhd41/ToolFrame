#include "IFunctionArg.h"

NS_TOOL_FRAME_BEGIN

bool DestoryFunctionArg(IFunctionArg* pFunctionArg)
{
	delete pFunctionArg;
	return true;
}

NS_TOOL_FRAME_END
