#include "IQuery.h"
#include "MSystem.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

IQuery::IQuery()
{
	SetID(INVALID_ID);
	SetType(0);
	SetTypeSub(0);
	SetTimeOut(0);
	SetQueryElapse(0);

	SetArgInt(0);
	SetArgUint(0);
}

IQuery::~IQuery()
{
	MSystem::Singleton().GetTimeOutQueque().RemoveTimer(_pTimer);
}

bool IQuery::Init()
{
	DEBUG_CLASS_INIT();

	QueryBegin();

	DEBUG_FUNC(if (GetTag().empty())SetTag(ToolFrame::GetTypeName(this)));
	
	return true;
}

bool IQuery::QueryBegin()
{
	_xElapse.ReStart();
	if (GetTimeOut()>0)
	{
		ASSERT_LOG_ERROR(_pTimer);
		_pTimer = MSystem::Singleton().GetTimeOutQueque().CreateTimerByAfterMil(this,GetTimeOut());
	}
	
	return true;
}

bool IQuery::QueryEnd()
{
	SetQueryElapse(_xElapse.TimeElapsed());
	return true;
}

bool IQuery::OnTimeOut(const CTimeNodePtr& pTimeNode)
{
	if (_pTimer == pTimeNode)
	{
		OnQueryTimeOut();
		return true;
	}
	return false;
}

bool IQuery::OnQueryTimeOut()
{
	return false;
}

NS_TOOL_FRAME_END
