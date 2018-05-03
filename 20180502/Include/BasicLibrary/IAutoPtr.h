#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN

//���ü�����(Ĭ��Ϊ1 �̰߳�ȫ)
class IAutoPtr
{
public:	
	virtual int		Retain();				//�������ü���
	virtual int		Release();				//�������ü���
	virtual bool	IsZeroRef()const;		//�Ƿ�0����
	virtual int		GetRefCounter()const;	//��ȡ��������
	virtual bool	AutoDelete(bool bAuto);	//�Զ��ͷ�(���õ����ü���Ϊ0ʱ�Զ��ͷ�)
	virtual bool	IsAutoDelete()const;	//�Ƿ��Զ��ͷ�

	NO_COPY_VIRTUAL(IAutoPtr);			//���������࿽��
public:
	IAutoPtr(void);
	virtual ~IAutoPtr(void);
private:
	int						_nRefCounter;
	bool					_bAutoDelete;
	mutable CMutexReadWrite _mutex;

};

//////////////////////////////////////////////////////////////////////////
//�Զ����ü���(ģ��)
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
//�����������
typedef TAutoPtr<IAutoPtr>					CAutoPtr;

NS_TOOL_FRAME_END
