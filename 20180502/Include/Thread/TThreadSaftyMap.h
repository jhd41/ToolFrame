#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

//�̰߳�ȫӳ���

NS_TOOL_FRAME_BEGIN

template<typename T, typename K>
class TOOLFRAME_DLL TThreadSaftyMap
{
public:
	typedef std::map<T, K> StdMap;
public:
	bool Empty()const;
	void Clear();
	size_t Size()const;
	bool Insert(const T& t, const K& k);//����(���Ѵ��������ʧ��)
	K	GetValueByKey(const T& t)const;//��ȡֵ(���Ҳ�������� ���̰߳�ȫ�����Ҫ��������ֵ)
	
	template<typename TDefault>
	K	GetValueByKey(const T& t,const TDefault& tDefault)const;//��ȡֵ(���Ҳ�������� ���̰߳�ȫ�����Ҫ��������ֵ)

	bool EraseByKey(const T& t);
	bool IsHasKey(const T& t)const;

	//���ز�����������
	StdMap&			GetMap();
	const StdMap&	GetMap()const;
	bool			SetMap(const StdMap& vMap);

	//���ض�д������(ͬһ�߳�Ҳ��������,����)
	CMutexReadWrite& GetMutex()const;

	//��ֵ
	TThreadSaftyMap& operator = (const TThreadSaftyMap& other);
public:
	TThreadSaftyMap(void);
	TThreadSaftyMap(const TThreadSaftyMap& other);
	virtual ~TThreadSaftyMap(void);
protected:
	mutable CMutexReadWrite	_mutex;
	StdMap					 _vMap;
};

template<typename T, typename K>
class TThreadSaftyMapValue
	:public TThreadSaftyMap<T, K>
{
	typedef TThreadSaftyMap<T, K> Supper;
public:
	//ͨ��Key����ֵ ����ֵ�Ŀ��� ����ȡ�����򴴽� ���̰߳�ȫ�����Ҫ��������ֵ
	K	GetValueByKeyForce(const T& t,bool bTryRead = true);

	//ͨ��Key����ֵ ����ֵ������ ����ȡ�����򴴽�(ע����߳�)
	K&	GetValueRefByKeyForce(const T& t, bool bTryRead = true);

	//���̰߳�ȫ�����Ҫ��������ֵ
	K	GetPtrValueByKey(const T& t)const;

	//����� �����Ƿ���룬���֮ǰ�Ѿ����� ����false
	bool InsertKey(const T& t);

public:
	TThreadSaftyMapValue(void);
	virtual ~TThreadSaftyMapValue(void);
};

//////////////////////////////////////////////////////////////////////////
template<typename T, typename K>
TThreadSaftyMap<T, K>::TThreadSaftyMap(void)
{

}

template<typename T, typename K>
TThreadSaftyMap<T, K>::TThreadSaftyMap(const TThreadSaftyMap& other)
{
	*this = other;
}

template<typename T, typename K>
TThreadSaftyMap<T, K>::~TThreadSaftyMap(void)
{

}

template<typename T, typename K>
bool TThreadSaftyMap<T, K>::Empty() const
{
	CLockRead lock(_mutex);
	return _vMap.empty();
}

template<typename T, typename K>
void TThreadSaftyMap<T, K>::Clear()
{
	CLockWrite lock(_mutex);
	return _vMap.clear();
}

template<typename T, typename K>
size_t TThreadSaftyMap<T, K>::Size() const
{
	CLockRead lock(_mutex);
	return _vMap.size();
}

template<typename T, typename K>
bool TThreadSaftyMap<T, K>::Insert(const T& t, const K& k)
{
	CLockWrite lock(_mutex);

	if (_vMap.find(t) != _vMap.end())return false;//Ϊ�˰�ȫ��� ����ʱ�ٲ���һ��

	_vMap.insert(std::make_pair(t, k));//vMap[tKey]=kValue; ������д�������𡣴�д��������
	return true;
}

template<typename T, typename K>
K TThreadSaftyMap<T, K>::GetValueByKey(const T& t) const
{
	CLockRead lock(_mutex);

	typename StdMap::const_iterator itr = _vMap.find(t);
	assert(itr != _vMap.end());
	return itr->second;
}

template<typename T, typename K>
bool TThreadSaftyMap<T, K>::EraseByKey(const T& t)
{
	CLockWrite lock(_mutex);

	size_t uSize = _vMap.size();
	_vMap.erase(t);
	return 1 == (uSize - _vMap.size());
}

template<typename T, typename K>
bool TThreadSaftyMap<T, K>::IsHasKey(const T& t) const
{
	CLockRead lock(_mutex);
	return _vMap.find(t) != _vMap.end();
}

template<typename T, typename K>
typename TThreadSaftyMap<T, K>::StdMap& TThreadSaftyMap<T, K>::GetMap()
{
	return _vMap;
}

template<typename T, typename K>
const typename TThreadSaftyMap<T, K>::StdMap& TThreadSaftyMap<T, K>::GetMap() const
{
	return _vMap;
}

template<typename T, typename K>
bool TThreadSaftyMap<T, K>::SetMap(const StdMap& vMap)
{
	_vMap = vMap; return true;
}

template<typename T, typename K>
CMutexReadWrite& TThreadSaftyMap<T, K>::GetMutex() const
{
	return _mutex;
}

template<typename T, typename K>
TThreadSaftyMap<T, K>& TThreadSaftyMap<T, K>::operator=(const TThreadSaftyMap<T, K>& other)
{
	CLockWrite	lockWrite(_mutex);
	CLockRead	lockRead(other._mutex);

	_vMap = other._vMap;
	return *this;
}

template<typename T, typename K>
template<typename TDefault>
K TThreadSaftyMap<T, K>::GetValueByKey(const T& t, const TDefault& tDefault) const
{
	CLockRead lock(_mutex);

	typename StdMap::const_iterator itr = _vMap.find(t);
	return itr != _vMap.end() ? itr->second : tDefault;
}

//////////////////////////////////////////////////////////////////////////
template<typename T, typename K>
TThreadSaftyMapValue<T, K>::TThreadSaftyMapValue(void)
{

}

template<typename T, typename K>
TThreadSaftyMapValue<T, K>::~TThreadSaftyMapValue(void)
{

}

template<typename T, typename K>
K TThreadSaftyMapValue<T, K>::GetValueByKeyForce(const T& t, bool bTryRead)
{
	//������һ�飬�������������
	if (bTryRead)
	{
		CLockRead lock(Supper::_mutex);

		typename Supper::StdMap::iterator itr = Supper::_vMap.find(t);
		if (itr != Supper::_vMap.end())
			return itr->second;
	}
	//���߳���Ҫ��������
	{
		CLockWrite lock(Supper::_mutex);

		typename Supper::StdMap::iterator itr = Supper::_vMap.find(t);
		if (itr == Supper::_vMap.end())
		{
			Supper::_vMap[t] = K();
			return Supper::_vMap[t];
		}
		return itr->second;
	}
}


template<typename T, typename K>
K& TThreadSaftyMapValue<T, K>::GetValueRefByKeyForce(const T& t, bool bTryRead)
{
	//������һ�飬�������������
	if (bTryRead)
	{
		CLockRead lock(Supper::_mutex);

		typename Supper::StdMap::iterator itr = Supper::_vMap.find(t);
		if (itr != Supper::_vMap.end())
			return itr->second;
	}
	//���߳���Ҫ��������
	{
		CLockWrite lock(Supper::_mutex);

		typename Supper::StdMap::iterator itr = Supper::_vMap.find(t);
		if (itr == Supper::_vMap.end())
		{
			Supper::_vMap[t] = K();
			return Supper::_vMap[t];
		}
		return itr->second;
	}
}


template<typename T, typename K>
K TThreadSaftyMapValue<T, K>::GetPtrValueByKey(const T& t) const
{
	CLockRead lock(Supper::_mutex);

	typename Supper::StdMap::const_iterator itr = Supper::_vMap.find(t);
	return itr == Supper::_vMap.end() ? K() : itr->second;
}


template<typename T, typename K>
bool TThreadSaftyMapValue<T, K>::InsertKey(const T& t)
{
	CLockWrite lock(Supper::_mutex);
	typename Supper::StdMap::iterator itr = Supper::_vMap.find(t);
	if (itr != Supper::_vMap.end())return false;

	Supper::_vMap.insert(std::make_pair(t, K()));
	return true;
}

NS_TOOL_FRAME_END