#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN

//ʹ�ü�����(Ĭ��Ϊ1 �̰߳�ȫ)
class IUseRef
{
public:	
	virtual int		RetainUse();			//����ʹ�ü���
	virtual int		ReleaseUse();			//����ʹ�ü���
	virtual bool	IsZeroUse()const;		//�Ƿ�0ʹ��
	virtual int		GetUseCounter()const;	//��ȡʹ������
	virtual bool	TryRetainUse();			//��û����ʹ���� �򷵻� �ɹ� ����һ��ʹ�ü���

	NO_COPY_VIRTUAL(IUseRef);			//���������࿽��
public:
	IUseRef(void);
	virtual ~IUseRef(void);
private:
	int						_nUseCounter;
	mutable CMutexReadWrite _mutex;

};

//////////////////////////////////////////////////////////////////////////
//�Զ����ü���(ģ��)
template<typename T>
class TLockUse
{
public:
	virtual bool UnLock();				//�ͷŴ���
	virtual bool Lock(T* pAutoUse);		//ǿ������(һ���ܳɹ�)
	virtual bool TryLock(T* pAutoUse);	//��������(�����Ƿ����ɹ�)
	virtual bool IsLocked()const;		//�Ƿ�������ɹ�	
public:
	operator T*()const;
	virtual TLockUse& operator =(const TLockUse& ref);
	virtual TLockUse& operator =(T* pAutoUse);
public:
	TLockUse();
	TLockUse(T* pAutoUse,bool bTry = false);//����(�����������)
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

	if (_pAutoUse)//����Ѿ�����
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
//�����������
typedef TLockUse<IUseRef>		CLockUse;
NS_TOOL_FRAME_END
