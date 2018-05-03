#pragma once
#include "Macro.h"

//����ͳ����
NS_TOOL_FRAME_BEGIN
template<typename T>
class TTriggerCounter
{
public:
	typename typedef std::map<T,uint> MapCounter;
public:
	uint Trigger(const T& t);				//���ش�������
	uint GetTriggerCount(const T& t)const;	//��ȡ��������
	const MapCounter& GetMapCounter()const;	//��ȡ�ڲ�����(�ⲿ����)
public:
	TTriggerCounter(void){}
	virtual ~TTriggerCounter(void){}
private:
	MapCounter	_vCounter;
};
template<typename T>
typename const TTriggerCounter<T>::MapCounter& TTriggerCounter<T>::GetMapCounter() const
{
	return _vCounter;
}

template<typename T>
uint TTriggerCounter<T>::GetTriggerCount( const T& t ) const
{
	MapCounter::const_iterator itr = _vCounter.find(t);
	return itr == _vCounter.end() ? 0 :itr->second;
}

template<typename T>
uint TTriggerCounter<T>::Trigger( const T& t )
{
	MapCounter::iterator itr = _vCounter.find(t);
	if (itr == _vCounter.end())
	{
		_vCounter.insert(std::make_pair(t,1));
		return 1;
	}

	return ++(itr->second);
}

NS_TOOL_FRAME_END