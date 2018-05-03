#include "LockMutex.h"

//////////////////////////////////////////////////////////////////////////
//�ݹ黥����
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
//�ݹ���
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
	if (_bLocked)return true;//����Ѿ����� ֱ�ӷ��سɹ�

	_bLocked = _mutex.Lock();
	return _bLocked;
}

bool CLockScoped::TryLock()
{
	if (_bLocked)return true;//����Ѿ����� ֱ�ӷ��سɹ�

	_bLocked = _mutex.TryLock();
	return _bLocked;
}

bool CLockScoped::IsLocked() const
{
	return _bLocked;
}

//////////////////////////////////////////////////////////////////////////
//��д������
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
//��д������ - ����
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
	if (_bLocked)return true;//����Ѿ����� ֱ�ӷ��سɹ�

	_bLocked = _mutex.LockShared();
	return _bLocked;
}

bool CLockRead::TryLock()
{
	if (_bLocked)return true;//����Ѿ����� ֱ�ӷ��سɹ�

	_bLocked = _mutex.TryLockShared();
	return _bLocked;
}

bool CLockRead::IsLocked() const
{
	return _bLocked;
}

//////////////////////////////////////////////////////////////////////////
//��д������ - д��
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
	if (_bLocked)return true;//����Ѿ����� ֱ�ӷ��سɹ�

	_bLocked = _mutex.Lock();
	return _bLocked;
}

bool CLockWrite::TryLock()
{
	if (_bLocked)return true;//����Ѿ����� ֱ�ӷ��سɹ�

	_bLocked = _mutex.TryLock();
	return _bLocked;
}

bool CLockWrite::IsLocked() const
{
	return _bLocked;
}
