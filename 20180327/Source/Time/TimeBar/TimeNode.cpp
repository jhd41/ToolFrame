#include "TimeNode.h"

NS_TOOL_FRAME_BEGIN

CTimeNode::CTimeNode()
{
	_bEnable = false;
	_uTimeOut = 0;
	_bLoop = false;
	_uTimeDelay = 0;
	_hHandler= nullptr;

	_pObj = nullptr;
	_nArg = 0;
}

CTimeNode::~CTimeNode()
{

}

bool CTimeNode::SetInvaild()
{
	CLockScoped lock(_mutex);

	if (!_bEnable)return true;
	_bEnable = false;
	_hHandler = nullptr;
	return true;
}

bool CTimeNode::Init( bool bLoop,uint64 uTimeDelay,HTimeOut* hHandler )
{
	CLockScoped lock(_mutex);

	_bEnable = true;
	_bLoop = bLoop;
	_uTimeDelay = uTimeDelay;
	_hHandler = hHandler;
	return true;
}

bool CTimeNode::IsEnable() const
{
	CLockScoped lock(_mutex);
	return _bEnable;
}

HTimeOut* CTimeNode::GetHandler()const{
	CLockScoped lock(_mutex);
	return _hHandler;
}

uint64 CTimeNode::GetTimeOut() const
{
	CLockScoped lock(_mutex);
	return _uTimeOut;
}

void CTimeNode::SetObj(void* pObj)
{
	CLockScoped lock(_mutex);
	_pObj = pObj;
}

void* CTimeNode::GetObj()const
{
	CLockScoped lock(_mutex);

	return _pObj;
}

void CTimeNode::SetTimeOut( uint64 uTimeOut )
{
	CLockScoped lock(_mutex);
	_uTimeOut = uTimeOut;
}

CMutexRecursive& CTimeNode::GetMutex()const
{
	return _mutex;
}

bool CTimeNode::IsLoop() const
{
	CLockScoped lock(_mutex);
	return _bLoop;
}

uint64 CTimeNode::GetTimeDelay() const
{
	CLockScoped lock(_mutex);
	return _uTimeDelay;
}

void CTimeNode::SetUserDataInt( int nArg )
{
	_nArg = nArg;
}

int CTimeNode::GetUserDataInt() const
{
	return _nArg;
}

void CTimeNode::SetUserDataString( const std::string& sArg )
{
	_sArg = sArg;
}

const std::string& CTimeNode::GetUserDataString() const
{
	return _sArg;
}

NS_TOOL_FRAME_END
