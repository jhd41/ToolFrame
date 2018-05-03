#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN

//使用计数器(默认为1 线程安全)
class IUseRef
{
public:	
	virtual int		RetainUse();			//增加使用计数
	virtual int		ReleaseUse();			//减少使用计数
	virtual bool	IsZeroUse()const;		//是否0使用
	virtual int		GetUseCounter()const;	//获取使用数量
	virtual bool	TryRetainUse();			//当没有在使用中 则返回 成功 增加一个使用计数

	NO_COPY_VIRTUAL(IUseRef);			//不允许子类拷贝
public:
	IUseRef(void);
	virtual ~IUseRef(void);
private:
	int						_nUseCounter;
	mutable CMutexReadWrite _mutex;

};

//////////////////////////////////////////////////////////////////////////
//自动引用计数(模板)
template<typename T>
class TLockUse
{
public:
	virtual bool UnLock();				//释放此锁
	virtual bool Lock(T* pAutoUse);		//强行上锁(一定能成功)
	virtual bool TryLock(T* pAutoUse);	//尝试上锁(返回是否锁成功)
	virtual bool IsLocked()const;		//是否此锁锁成功	
public:
	operator T*()const;
	virtual TLockUse& operator =(const TLockUse& ref);
	virtual TLockUse& operator =(T* pAutoUse);
public:
	TLockUse();
	TLockUse(T* pAutoUse,bool bTry = false);//上锁(尝试上锁标记)
	TLockUse(const TLockUse& ref);
	virtual ~TLockUse();
private:
	T*	_pAutoUse;
};

template<typename T>
TLockUse<T>::TLockUse()
{
	_pAutoUse = nullptr;
}

template<typename T>
ToolFrame::TLockUse<T>::TLockUse(T* pAutoUse, bool bTry /*= false*/)
{
	_pAutoUse = nullptr;
	bTry ? TryLock(pAutoUse): Lock(pAutoUse);
}

template<typename T>
TLockUse<T>::TLockUse(const TLockUse& ref)
{
	_pAutoUse = nullptr;
	Lock(ref._pAutoUse);
}

template<typename T>
TLockUse<T>::~TLockUse()
{
	UnLock();
}

template<typename T>
bool TLockUse<T>::UnLock()
{
	if (_pAutoUse) {
		_pAutoUse->ReleaseUse();
		_pAutoUse = nullptr;
	}
	return true;
}

template<typename T>
bool TLockUse<T>::Lock(T* pAutoUse)
{
	UnLock();

	if (pAutoUse)
	{
		_pAutoUse = pAutoUse;
		_pAutoUse->RetainUse();
	}

	return true;
}

template<typename T>
bool TLockUse<T>::TryLock(T* pAutoUse)
{
	if (!pAutoUse)return false;

	if (_pAutoUse)//如果已经上锁
		return _pAutoUse == pAutoUse;

	if (pAutoUse->TryRetainUse())
		_pAutoUse = pAutoUse;

	return !!_pAutoUse;
}

template<typename T>
bool TLockUse<T>::IsLocked() const
{
	return !!_pAutoUse;
}

template<typename T>
TLockUse<T>::operator T*()const {
	return _pAutoUse;
}

template<typename T>
TLockUse<T>& TLockUse<T>::operator=(const TLockUse<T>& ref)
{
	Lock(ref._pAutoUse);
	return *this;
}

template<typename T>
TLockUse<T>& TLockUse<T>::operator=(T* pAutoUse)
{
	Lock(pAutoUse);
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//定义基本类型
typedef TLockUse<IUseRef>		CLockUse;
NS_TOOL_FRAME_END
