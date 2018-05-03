#include "LoopManager.h"

#include "ToolFrame.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

CLoopManager::CLoopManager(void)
{
}

CLoopManager::~CLoopManager(void)
{
}

bool CLoopManager::AddLoop( ILoop* pLoop )
{
	if (!pLoop)return false;

	ToolFrame::PushBack(_vLoop,pLoop);
	return true;
}

bool CLoopManager::RemoveLoop( ILoop* pLoop )
{
	if (!pLoop)return false;

	return ToolFrame::EraseByValue(_vLoop,pLoop);
}

bool CLoopManager::Loop()
{
	if (_vLoop.empty())return true;
	
	VectorLoop::const_iterator itr;
	foreach(itr,_vLoop){
		ILoop* pLoop = *itr;
		ASSERT_LOG_ERROR(pLoop);

		if (!pLoop->IsInitedLoop())
		{
			if (pLoop->InitLoop())
				pLoop->SetInitedLoop();
		}else{
			pLoop->RunOnceLoop();
		}
	}
	return true;
}

NS_TOOL_FRAME_END
