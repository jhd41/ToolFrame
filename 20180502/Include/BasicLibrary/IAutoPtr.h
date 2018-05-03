#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN

//引用计数器(默认为1 线程安全)
class IAutoPtr
{
public:	
	virtual int		Retain();				//增加引用计数
	virtual int		Release();				//减少引用计数
	virtual bool	IsZeroRef()const;		//是否0引用
	virtual int		GetRefCounter()const;	//获取引用数量
	virtual bool	AutoDelete(bool bAuto);	//自动释放(设置当引用计数为0时自动释放)
	virtual bool	IsAutoDelete()const;	//是否自动释放

	NO_COPY_VIRTUAL(IAutoPtr);			//不允许子类拷贝
public:
	IAutoPtr(void);
	virtual ~IAutoPtr(void);
private:
	int						_nRefCounter;
	bool					_bAutoDelete;
	mutable CMutexReadWrite _mutex;

};

//////////////////////////////////////////////////////////////////////////
//自动引用计数(模板)
template<typename T>
class TAutoPtr
{
public:
	virtual bool		Release();
	virtual bool		SetPtr(T* pRef);
	virtual T*			GetPtr();
	virtual const T*	GetPtr()const;
public:
	operator bool()const;
 	template<typename TArg>
 	TAutoPtr&	operator =(const TAutoPtr<TArg>& pAutoPtr);
	virtual TAutoPtr&	operator =(const TAutoPtr& ref);
	virtual TAutoPtr&	operator =(T* pRef);
	virtual T*			operator ->();
	virtual const T*	operator ->()const;
public:
	TAutoPtr();
	TAutoPtr(T* pRef);
	TAutoPtr(const TAutoPtr& ref);
 	template<typename TArg>
 	TAutoPtr(const TAutoPtr<TArg>& pAutoPtr);
	virtual ~TAutoPtr();
protected:
	T*	_pRef;
};

template<typename T>
TAutoPtr<T>::TAutoPtr()
{
	_pRef = nullptr;
}

template<typename T>
TAutoPtr<T>::TAutoPtr(T* pRef)
{
	_pRef = nullptr;
	SetPtr(pRef);
}

template<typename T>
TAutoPtr<T>::TAutoPtr(const TAutoPtr& ref)
{
	_pRef = nullptr;
	SetPtr(ref._pRef);
}

 template<typename T>
 template<typename TArg>
 TAutoPtr<T>::TAutoPtr(const TAutoPtr<TArg>& pAutoPtr)
 {
 	_pRef = nullptr;
 	SetPtr(pAutoPtr.GetPtr());
 }

template<typename T>
TAutoPtr<T>::~TAutoPtr()
{
	Release();
}

template<typename T>
T* TAutoPtr<T>::operator->()
{
	return _pRef;
}

template<typename T>
const T* TAutoPtr<T>::operator->() const
{
	return _pRef;
}

template<typename T>
bool TAutoPtr<T>::Release()
{
	if (_pRef) {
		_pRef->Release();
		_pRef = nullptr;
	}
	return true;
}

template<typename T>
bool TAutoPtr<T>::SetPtr(T* pRef)
{
	Release();

	if (pRef)
	{
		_pRef->Retain();
		_pRef = pRef;
	}

	return true;
}

template<typename T>
const T* TAutoPtr<T>::GetPtr() const
{
	return _pRef;
}

template<typename T>
T* TAutoPtr<T>::GetPtr()
{
	return _pRef;
}

template<typename T>
TAutoPtr<T>::operator bool()const {
	return !!_pRef;
}

template<typename T>
template<typename TArg>
TAutoPtr<T>& TAutoPtr<T>::operator=(const TAutoPtr<TArg>& pAutoPtr)
{
	SetPtr(pAutoPtr.GetPtr());
	return *this;
}

template<typename T>
TAutoPtr<T>& TAutoPtr<T>::operator=(const TAutoPtr<T>& ref)
{
	SetPtr(ref._pRef);
	return *this;
}

template<typename T>
TAutoPtr<T>& ToolFrame::TAutoPtr<T>::operator=(T* pRef)
{
	SetPtr(pRef);
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//定义基本类型
typedef TAutoPtr<IAutoPtr>					CAutoPtr;

NS_TOOL_FRAME_END
