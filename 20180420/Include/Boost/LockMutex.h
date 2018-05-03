#pragma once

#include <boost/thread.hpp>
#include <boost/thread/recursive_mutex.hpp>

#include <boost/smart_ptr/detail/spinlock.hpp>

//线程相关
//旋转锁:使用死循环来实现堵塞的锁,非常消耗CPU,并且不释放占用,特点是响应速度快拥有最高的优先级
//互斥体:是使用信号量来实现的锁,非常常用,当访问的临界区被其他线程占用会将自己所在线程堵塞 并 等待释放的信号量到来

//旋转锁
typedef boost::detail::spinlock					CSpinLock;//旋转锁

//基于Boost互斥锁 编写的 更方便的 锁
//////////////////////////////////////////////////////////////////////////
//递归互斥体
//在当前花括号调用结束后自动解锁,同一个线程可以多次上锁
class CMutexRecursive
{
public:
	virtual bool Lock();				//强行上锁(若已上锁会等待)
	virtual bool TryLock();				//尝试上锁(返回是否锁成功)
	virtual bool UnLock();				//释放此锁
public:
	CMutexRecursive();
	virtual ~CMutexRecursive();
private:
	boost::recursive_mutex _mutex;
};

//////////////////////////////////////////////////////////////////////////
//递归锁
class CLockScoped
{
public:
	virtual bool UnLock();		//释放此锁
	virtual bool Lock();		//强行上锁(若已上锁会等待)
	virtual bool TryLock();		//尝试上锁(返回是否锁成功)
	virtual bool IsLocked()const;//是否上锁成功
public:
	CLockScoped(CMutexRecursive& mutex,bool bTry = false);//上锁(若bTry为false 则 上锁不成功 时会等待，若为 true 则需要逻辑层判断 IsLocked() 是否上锁成功 不会阻塞 )
	virtual ~CLockScoped();
private:
	bool _bLocked;
	CMutexRecursive& _mutex;
};

//////////////////////////////////////////////////////////////////////////
//读写互斥体
//在当前花括号调用结束后自动解锁,读读 不互斥,读写互斥,写写互斥。同一线程不能多次上锁
class CMutexReadWrite
{
public:
	virtual bool Lock();				//强行上写锁(若已上锁会等待)
	virtual bool TryLock();				//尝试上写锁(返回是否锁成功)
	virtual bool UnLock();				//释放此写锁

	virtual bool LockShared();			//强行上读锁(若已上锁会等待)
	virtual bool TryLockShared();		//尝试上读锁(返回是否锁成功)
	virtual bool UnLockShared();		//释放此读锁
public:
	CMutexReadWrite();
	virtual ~CMutexReadWrite();
private:
	boost::shared_mutex _mutex;
};

//////////////////////////////////////////////////////////////////////////
//读写互斥锁 - 读锁
class CLockRead
{
public:
	virtual bool UnLock();		//释放此锁
	virtual bool Lock();		//强行上锁(若已上锁会等待)
	virtual bool TryLock();		//尝试上锁(返回是否锁成功)
	virtual bool IsLocked()const;//是否上锁成功
public:
	CLockRead(CMutexReadWrite& mutex, bool bTry = false);//上锁(若bTry为false 则 上锁不成功 时会等待，若为 true 则需要逻辑层判断 IsLocked() 是否上锁成功 不会阻塞 )
	virtual ~CLockRead();
private:
	bool _bLocked;
	CMutexReadWrite& _mutex;
};

//////////////////////////////////////////////////////////////////////////
//读写互斥锁 - 写锁
class CLockWrite
{
public:
	virtual bool UnLock();		//释放此锁
	virtual bool Lock();		//强行上锁(若已上锁会等待)
	virtual bool TryLock();		//尝试上锁(返回是否锁成功)
	virtual bool IsLocked()const;//是否上锁成功
public:
	CLockWrite(CMutexReadWrite& mutex, bool bTry = false);//上锁(若bTry为false 则 上锁不成功 时会等待，若为 true 则需要逻辑层判断 IsLocked() 是否上锁成功 不会阻塞 )
	virtual ~CLockWrite();
private:
	bool _bLocked;
	CMutexReadWrite& _mutex;
};
