#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"

//�̰߳�ȫ�б�

NS_TOOL_FRAME_BEGIN

template<typename T>
class TOOLFRAME_DLL TThreadSaftyList
{
public:
	typedef std::list<T> StdList;
public:
	bool	Empty()const;
	bool	Clear();
	size_t	Size()const;
	bool	Push(const T& t);
	bool	Pop();
	bool	Pop(T& t);
	bool	PushFront(const T& t);
	bool	PushBack(const T& t);
	bool	PopFront();
	bool	PopFront(T& t);

	T&		Front();//���ܲ���ȫ
	T&		Back();//���ܲ���ȫ

	const T& Front()const;//���ܲ���ȫ
	const T& Back()const;//���ܲ���ȫ

	//���� ֵ
	uint EraseByValue(const T& t,bool bEreaseOne = false);//����ֵ �� bOne Ϊ true �� ����һ���ͷ���

	//ƴ��(���޸�ԭ ����)
	bool Splice(TThreadSaftyList<T>& vList, bool bBack = true);

	//û������ �ⲿʹ�����ע�ⰲȫ
	StdList& GetList();

	//û������ �ⲿʹ�����ע�ⰲȫ
	const StdList& GetList()const;

	//���ض�д������(ͬһ�߳�Ҳ��������,����)
	CMutexReadWrite& GetMutex()const;

	//��ֵ
	TThreadSaftyList& operator = (const TThreadSaftyList& other);
public:
	TThreadSaftyList();
	TThreadSaftyList(const TThreadSaftyList& other);
	virtual ~TThreadSaftyList();
protected:
	mutable CMutexReadWrite	_mutex;
	StdList					_vList;
};

//////////////////////////////////////////////////////////////////////////
template<typename T>
class TThreadSaftyListValue
	:public TThreadSaftyList<T>
{
	typedef TThreadSaftyList<T> Supper;
public:
	virtual T PopPtr();

	virtual T PopFrontPtr();
	virtual T PopBackPtr();
	virtual T FrontPtr()const;
	virtual T BackPtr()const;
public:
	TThreadSaftyListValue(void);
	virtual ~TThreadSaftyListValue(void);
};

//////////////////////////////////////////////////////////////////////////
template<typename T>
TThreadSaftyList<T>::TThreadSaftyList()
{

}

template<typename T>
TThreadSaftyList<T>::TThreadSaftyList(const TThreadSaftyList& other)
{
	*this = other;
}

template<typename T>
TThreadSaftyList<T>::~TThreadSaftyList()
{
	CLockWrite lock(_mutex);
	_vList.clear();
}

template<typename T>
bool TThreadSaftyList<T>::Empty() const
{
	CLockRead lock(_mutex);
	return _vList.empty();
}

template<typename T>
bool TThreadSaftyList<T>::Clear()
{
	CLockWrite lock(_mutex);
	_vList.clear();
	return true;
}

template<typename T>
size_t TThreadSaftyList<T>::Size() const
{
	CLockRead lock(_mutex);
	return _vList.size();
}

template<typename T>
bool TThreadSaftyList<T>::Push(const T& t)
{
	return PushBack(t);
}

template<typename T>
bool TThreadSaftyList<T>::Pop()
{
	return PopFront();
}

template<typename T>
bool TThreadSaftyList<T>::Pop(T& t)
{
	return PopFront(t);
}

template<typename T>
bool TThreadSaftyList<T>::PushFront(const T& t)
{
	CLockWrite lock(_mutex);
	_vList.push_front(t);
	return true;
}

template<typename T>
bool TThreadSaftyList<T>::PushBack(const T& t)
{
	CLockWrite lock(_mutex);
	_vList.push_back(t);
	return true;
}

template<typename T>
bool TThreadSaftyList<T>::PopFront()
{
	CLockWrite lock(_mutex);
	_vList.pop_front();
	return true;
}

template<typename T>
bool TThreadSaftyList<T>::PopFront(T& t)
{
	CLockWrite lock(_mutex);

	if (_vList.empty())
		return false;

	t = _vList.front();
	_vList.pop_front();

	return true;
}

template<typename T>
const T& TThreadSaftyList<T>::Front() const
{
	CLockRead lock(_mutex);
	return _vList.front();
}

template<typename T>
const T& TThreadSaftyList<T>::Back() const
{
	CLockRead lock(_mutex);
	return _vList.back();
}

template<typename T>
T& TThreadSaftyList<T>::Front() //���ܲ���ȫ
{
	CLockRead lock(_mutex);
	return _vList.front();
}

template<typename T>
T& TThreadSaftyList<T>::Back() //���ܲ���ȫ
{
	CLockRead lock(_mutex);
	return _vList.back();
}

template<typename T>
uint TThreadSaftyList<T>::EraseByValue(const T& t, bool bEreaseOne /*= false*/) //����ֵ �� bEreaseOne Ϊ true �� ����һ���ͷ���
{
	CLockWrite lock(_mutex);

	uint nCount = 0;

	typename StdList::iterator itr = _vList.begin();
	while (itr != _vList.end())
	{
		if (t == *itr)
		{
			itr = _vList.erase(itr);
			++nCount;

			if (bEreaseOne)
				break;
		}
		else
			++itr;
	}

	return nCount;
}

template<typename T>
bool TThreadSaftyList<T>::Splice(TThreadSaftyList<T>& vList, bool bBack /*= true*/)
{
	if (vList.Empty())return false;

	CLockWrite lockOther(vList._mutex);
	CLockWrite lockSelf(_mutex);

	_vList.splice(bBack ? _vList.end() : _vList.begin(), vList._vList);
	return true;
}

template<typename T>
typename TThreadSaftyList<T>::StdList& TThreadSaftyList<T>::GetList()
{
	return _vList;
}

template<typename T>
const typename TThreadSaftyList<T>::StdList& TThreadSaftyList<T>::GetList() const
{
	return _vList;
}

template<typename T>
CMutexReadWrite& TThreadSaftyList<T>::GetMutex() const
{
	return _mutex;
}

template<typename T>
TThreadSaftyList<T>& TThreadSaftyList<T>::operator=(const TThreadSaftyList<T>& other)
{
	CLockWrite	lockWrite(_mutex);
	CLockRead	lockRead(other._mutex);

	_vList = other._vList;
	return *this;
}


//////////////////////////////////////////////////////////////////////////

template<typename T>
T TThreadSaftyListValue<T>::PopPtr()
{
	return PopFrontPtr();
}

template<typename T>
T TThreadSaftyListValue<T>::BackPtr() const
{
	CLockRead lock(Supper::_mutex);

	if (Supper::_vList.empty())
		return T();

	return Supper::_vList.back();
}

template<typename T>
T TThreadSaftyListValue<T>::FrontPtr() const
{
	CLockRead lock(Supper::_mutex);

	if (Supper::_vList.empty())
		return T();

	return Supper::_vList.front();
}

template<typename T>
T TThreadSaftyListValue<T>::PopBackPtr()
{
	CLockWrite lock(Supper::_mutex);

	if (Supper::_vList.empty())
		return T();

	T t = Supper::_vList.back();
	Supper::_vList.pop_back();
	return t;
}

template<typename T>
T TThreadSaftyListValue<T>::PopFrontPtr()
{
	CLockWrite lock(Supper::_mutex);

	if (Supper::_vList.empty())
		return T();

	T t = Supper::_vList.front();
	Supper::_vList.pop_front();
	return t;
}

template<typename T>
TThreadSaftyListValue<T>::TThreadSaftyListValue(void)
{

}

template<typename T>
TThreadSaftyListValue<T>::~TThreadSaftyListValue(void)
{

}

NS_TOOL_FRAME_END
