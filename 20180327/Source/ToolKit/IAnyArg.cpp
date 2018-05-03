#include "IAnyArg.h"

NS_TOOL_FRAME_BEGIN

bool DestoryAnyArg(IAnyArg* pAnyArg)
{
	delete pAnyArg;
	return true;
}

NS_TOOL_FRAME_END
