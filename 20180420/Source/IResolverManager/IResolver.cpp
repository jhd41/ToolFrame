#include "IResolver.h"
#include "IResolverManager.h"

NS_TOOL_FRAME_BEGIN

IResolver::IResolver(void)
{
	_hHandler = nullptr;

	SetResolverMgrNull();
	SetParentNull();
	SetManagerCreate(false);
	SetRemoved(true);
	SetResolving(false);
	SetResolveRange(RESOLVER_BASE_INIT,RESOLVER_BASE_MAX);

	if (_hHandler)
		_hHandler->OnResolverCreate(this);
}

IResolver::~IResolver(void)
{
	if (_hHandler)
		_hHandler->OnResolverDestory(this);
}
bool IResolver::IsResolveOver() const
{
	return GetResolve() == GetResolveEnd();
}

bool IResolver::SetResolveRange( int nBegin,int nEnd )
{
	SetResolveBegin(nBegin);
	SetResolveEnd(nEnd);

	SetResolve(nBegin);
	return true; 
}

bool IResolver::WaitSeconds( int nSeconds )
{
	return GetResolverMgr()->WaitSeconds(nSeconds);
}

bool IResolver::WaitSeconds( float fSeconds )
{
	return GetResolverMgr()->WaitSeconds(fSeconds);
}

bool IResolver::WaitMillSec( uint64 uMillSec )
{
	return GetResolverMgr()->WaitMillSec(uMillSec);
}

bool IResolver::WaitForever()
{
	return GetResolverMgr()->WaitForever();
}

bool IResolver::ClearWait()
{
	return GetResolverMgr()->ClearWait();
}

bool IResolver::MarkResolveOver()
{
	GetResolverMgr()->MarkResolveOver();
	return true;
}
bool IResolver::OnResolve()
{
	OnResolveOnce();
	SetResolveOver();
	return true;
}

bool IResolver::OnResolveOnce()
{
	return false;
}

bool IResolver::OnTimeOut()
{
	return false;
}

bool IResolver::PushAction( IResolver* pAc )
{
	if (!pAc)return false;
	if (!GetResolverMgr())return false;

	return GetResolverMgr()->PushResolver(pAc,this);
}

bool IResolver::PushActionSelf()
{
	if (!GetResolverMgr())return false;
	return GetResolverMgr()->PushResolver(this,GetParent());
}

bool IResolver::ResetResolve()
{
	SetResolving(false);
	SetResolve(GetResolveBegin());
	if (_hHandler)
		_hHandler->OnResolverResetResolve(this);
	return true;
}

bool IResolver::SetResolveOver()
{
	SetResolve(GetResolveEnd());
	return true;
}

bool IResolver::OnResolveOver()
{
	return true;
}

bool IResolver::OnResolveBegin()
{
	return true;
}

bool IResolver::IgnoreCheckResolve()
{
	if (!GetResolverMgr())return false;
	return GetResolverMgr()->IgnoreCheckResolve();
}

bool IResolver::SetHandler( HResolver* hHandler )
{
	_hHandler = hHandler;
	return true;
}

HResolver* IResolver::GetHandler() const
{
	return _hHandler;
}

NS_TOOL_FRAME_END
