#include "LockMutex.h"

//////////////////////////////////////////////////////////////////////////
//递归互斥体
CMutexRecursive::CMutexRecursive()
{
}

CMutexRecursive::~CMutexRecursive()
{
}

bool CMutexRecursive::Lock()
{
	_mutex.lock();
	return true;
}

bool CMutexRecursive::TryLock()
{
	return _mutex.try_lock();
}

bool CMutexRecursive::UnLock()
{
	_mutex.unlock();
	return true;
}

//////////////////////////////////////////////////////////////////////////
//递归锁
CLockScoped::CLockScoped(CMutexRecursive& mutex, bool bTry /*= false*/)
	:_mutex(mutex)
{
	_bLocked = false;
	bTry ? TryLock() : Lock();
}

CLockScoped::~CLockScoped()
{
	UnLock();
}

bool CLockScoped::UnLock()
{
	if (_bLocked)
	{
		_mutex.UnLock();
		_bLocked = false;
	}
	return true;
}

bool CLockScoped::Lock()
{
	if (_bLocked)return true;//如果已经上锁 直接返回成功

	_bLocked = _mutex.Lock();
	return _bLocked;
}

bool CLockScoped::TryLock()
{
	if (_bLocked)return true;//如果已经上锁 直接返回成功

	_bLocked = _mutex.TryLock();
	return _bLocked;
}

bool CLockScoped::IsLocked() const
{
	return _bLocked;
}

//////////////////////////////////////////////////////////////////////////
//读写互斥体
CMutexReadWrite::CMutexReadWrite()
{

}

CMutexReadWrite::~CMutexReadWrite()
{

}

bool CMutexReadWrite::Lock()
{
	_mutex.lock();
	return true;
}

bool CMutexReadWrite::TryLock()
{
	return _mutex.try_lock();
}

bool CMutexReadWrite::UnLock()
{
	_mutex.unlock(); 
	return true;
}

bool CMutexReadWrite::LockShared()
{
	_mutex.lock_shared();
	return true;
}

bool CMutexReadWrite::TryLockShared()
{
	return _mutex.try_lock_shared();
}

bool CMutexReadWrite::UnLockShared()
{
	_mutex.unlock_shared();
	return true;
}
//////////////////////////////////////////////////////////////////////////
//读写互斥锁 - 读锁
CLockRead::CLockRead(CMutexReadWrite& mutex, bool bTry /*= false*/)
	:_mutex(mutex)
{
	_bLocked = false;
	bTry ? TryLock() : Lock();
}

CLockRead::~CLockRead()
{
	UnLock();
}

bool CLockRead::UnLock()
{
	if (_bLocked)
	{
		_mutex.UnLockShared();
		_bLocked = false;
	}
	return true;
}

bool CLockRead::Lock()
{
	if (_bLocked)return true;//如果已经上锁 直接返回成功

	_bLocked = _mutex.LockShared();
	return _bLocked;
}

bool CLockRead::TryLock()
{
	if (_bLocked)return true;//如果已经上锁 直接返回成功

	_bLocked = _mutex.TryLockShared();
	return _bLocked;
}

bool CLockRead::IsLocked() const
{
	return _bLocked;
}

//////////////////////////////////////////////////////////////////////////
//读写互斥锁 - 写锁
CLockWrite::CLockWrite(CMutexReadWrite& mutex, bool bTry /*= false*/)
	:_mutex(mutex)
{
	_bLocked = false;
	bTry ? TryLock() : Lock();
}

CLockWrite::~CLockWrite()
{
	UnLock();
}

bool CLockWrite::UnLock()
{
	if (_bLocked)
	{
		_mutex.UnLock();
		_bLocked = false;
	}
	return true;
}

bool CLockWrite::Lock()
{
	if (_bLocked)return true;//如果已经上锁 直接返回成功

	_bLocked = _mutex.Lock();
	return _bLocked;
}

bool CLockWrite::TryLock()
{
	if (_bLocked)return true;//如果已经上锁 直接返回成功

	_bLocked = _mutex.TryLock();
	return _bLocked;
}

bool CLockWrite::IsLocked() const
{
	return _bLocked;
}
