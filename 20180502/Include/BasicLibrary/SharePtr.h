#pragma once
#include "Macro.h"

//Ŀǰû������������ָ��ά����,�˴����ڴ�й¶�������������ڶ��߳�������ε����⣬��ʱһ��ʹ��BOOST������
////����ָ��
//
//template<typename T>
//class CSharePtr{
//public:
//	UINT	GetRef()const;
//public:
//	T*		_GetPtr()const;
//	UINT*	_GetRef()const;
//public:
//	//���캯��
//	CSharePtr();
//	CSharePtr( T* tPtr);
//	//�������캯��
//	CSharePtr(const CSharePtr& ptr);
//	template<typename TSrc>
//	CSharePtr(const CSharePtr<TSrc>& ptr);
//
//	virtual ~CSharePtr();
//	T&			operator *	() const;
//	T*			operator ->	() const;
//	bool		operator !	() const;
//	bool		operator == (const CSharePtr& ptr)const;
//	bool		operator != (const CSharePtr& ptr)const;
//	bool		operator <	(const CSharePtr& ptr)const;
//	bool		operator >	(const CSharePtr& ptr)const;
//	bool		operator &&	(const CSharePtr& ptr)const;
//	bool		operator ||	(const CSharePtr& ptr)const;
//	operator bool(void)const;//��ʽ����
//
//	CSharePtr&	operator =	(const CSharePtr& ptr);
//
//	template<typename TSrc>
//	CSharePtr&	operator =	(const CSharePtr<TSrc>& ptr);
//private:
//	void AddRef();
//	void DropRef();
//private:
//	UINT*	_puRef;
//	T*		_pPtr;
//	boost::recursive_mutex _mutex;
//};
//
//template<typename T>
//UINT* CSharePtr<T>::_GetRef() const
//{
//	return _puRef;
//}
//
//template<typename T>
//T* CSharePtr<T>::_GetPtr() const
//{
//	return _pPtr;
//}
//
//template<typename T>
//bool CSharePtr<T>::operator||( const CSharePtr& ptr )const
//{
//	return _pPtr || ptr._pPtr;
//}
//
//template<typename T>
//bool CSharePtr<T>::operator&&( const CSharePtr<T>& ptr )const
//{
//	return _pPtr && ptr._pPtr;
//}
//
//template<typename T>
//bool CSharePtr<T>::operator>( const CSharePtr<T>& ptr )const
//{
//	return _pPtr > ptr._pPtr;
//}
//
//template<typename T>
//bool CSharePtr<T>::operator<( const CSharePtr<T>& ptr )const
//{
//	return _pPtr < ptr._pPtr;
//}
//
//template<typename T>
//bool CSharePtr<T>::operator!=( const CSharePtr<T>& ptr )const
//{
//	return _pPtr == ptr._pPtr;
//}
//
//template<typename T>
//CSharePtr<T>::operator bool(void)const
//{
//	return nullptr != _pPtr;
//}
//
//template<typename T>
//bool CSharePtr<T>::operator==( const CSharePtr<T>& ptr )const
//{
//	return _puRef == ptr._puRef;
//}
//
//template<typename T>
//CSharePtr<T>::CSharePtr( T* tPtr )
//{
//	_pPtr = tPtr;
//	_puRef = new UINT(1);
//}
//
//template<typename T>
//CSharePtr<T>::CSharePtr( const CSharePtr& ptr )
//{
//	_pPtr = ptr._pPtr;
//	_puRef= ptr._puRef;
//	AddRef();
//}
//
//template<typename T>
//template<typename TSrc>
//CSharePtr<T>::CSharePtr( const CSharePtr<TSrc>& ptr )
//{
//	T* pPtr = dynamic_cast<T*>(ptr._GetPtr());
//	if (pPtr)
//	{
//		_pPtr = pPtr;
//		_puRef= ptr._GetRef();
//		AddRef();
//	}else
//	{
//		_pPtr = pPtr;
//		_puRef = new UINT(1);
//	}
//}
//
//template<typename T>
//CSharePtr<T>::CSharePtr()
//{
//	_pPtr = nullptr;
//	_puRef = new UINT(1);
//}
//
//template<typename T>
//CSharePtr<T>::~CSharePtr()
//{
//	DropRef();
//}
//
//template<typename T>
//UINT CSharePtr<T>::GetRef()const
//{
//	return _puRef ? *_puRef:0;
//}
//
//template<typename T>
//void CSharePtr<T>::AddRef()
//{
//	boost::recursive_mutex::scoped_lock lLock(_mutex);
//	assert(_puRef && *_puRef > 0);
//	++(*_puRef);
//}
//
//template<typename T>
//void CSharePtr<T>::DropRef()
//{
//	assert(_puRef && (*_puRef > 0));
//
//	bool bDelete = false;
//	{
//		boost::recursive_mutex::scoped_lock lLock(_mutex);
//		--(*_puRef);
//		bDelete = 0 == GetRef();
//	}
//
//	if (bDelete)
//	{
//		assert(_puRef && (*_puRef == 0));
//		if (_pPtr)
//			delete _pPtr;
//		if (_puRef)
//			delete _puRef;
//
//		_pPtr = nullptr;
//		_puRef = nullptr;
//	}
//}
//
//template<typename T>
//CSharePtr<T>& CSharePtr<T>::operator=( const CSharePtr<T>& ptr )
//{
//	assert(_puRef && (*_puRef > 0));
//	if(ptr._pPtr == _pPtr){
//		//�����ͬһ��ָ��
//		//����Ҫ�������ü���ʲô��
//	}else{
//		//�������ͬһ��ָ��
//		//�ȶ�֮ǰ��ָ�����ü�������
//		DropRef();
//
//		//Ȼ�������µ����ü���
//		_pPtr = ptr._pPtr;
//		_puRef= ptr._puRef;
//		AddRef();
//	}
//	return *this;
//}
//
//template<typename T>
//template<typename TSrc>
//CSharePtr<T>& CSharePtr<T>::operator=( const CSharePtr<TSrc>& ptr )
//{
//	T* pPtr = dynamic_cast<T*>(ptr._GetPtr());
//	if (pPtr)
//	{
//		_pPtr = pPtr;
//		_puRef= ptr._GetRef();
//		AddRef();
//	}else
//	{
//		DropRef();
//		
//		_pPtr = pPtr;
//		_puRef = new UINT(1);
//	}
//
//	return *this;
//}
//
//template<typename T>
//bool CSharePtr<T>::operator!() const
//{
//	return _pPtr == 0;
//}
//
//template<typename T>
//T& CSharePtr<T>::operator*() const
//{
//	return *_pPtr;
//}
//
//template<typename T>
//T* CSharePtr<T>::operator->() const
//{
//	return _pPtr;
//}
