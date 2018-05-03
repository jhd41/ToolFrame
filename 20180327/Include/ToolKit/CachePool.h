#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"

//����� Vectorʵ��
template<typename T>
class CCachePool
{
	typedef std::vector<T> VectorT;
public:
	bool SetSizeMax(uint uSizeMax);//�������ߴ�
	bool Init();
	
	//�̰߳�ȫ
public:
	bool IsEmpty()const;			//�Ƿ�Ϊ��
	bool Push(const T& t);			//ѹ���»���
	T	 Random()const;				//������ػ�������
public:
	uint GetSizeMax()const;			//��ȡ������������
	uint GetSize()const;			//��ȡ��ǰ�����С
	T	 GetValue(uint uIndex)const;//��ȡ����(λ��) ���� ����Ϊ���ã���Ϊ�̰߳�ȫ
	uint GetCur()const;				//��ȡ��һָ��λ��
public:
	CCachePool(void);
	virtual ~CCachePool(void);
private:
	uint	_uSizeMax;
	VectorT	_vT;
	mutable CMutexReadWrite _mutex;
	uint	_uCur;
};

template<typename T>
bool CCachePool<T>::IsEmpty() const
{
	CLockRead lock(_mutex);

	return _vT.empty();
}

template<typename T>
uint CCachePool<T>::GetCur() const
{
	CLockRead lock(_mutex);
	return _uCur;
}

template<typename T>
uint CCachePool<T>::GetSize() const
{
	CLockRead lock(_mutex);

	return _vT.size();
}

template<typename T>
uint CCachePool<T>::GetSizeMax() const
{
	CLockRead lock(_mutex);

	return _uSizeMax;
}

template<typename T>
T CCachePool<T>::Random() const
{
	CLockRead lock(_mutex);

	uint uIndex = rand()%_vT.size();
	return _vT[uIndex];
}

template<typename T>
T CCachePool<T>::GetValue( uint uIndex ) const
{
	CLockRead lock(_mutex);
	return _vT[uIndex];
}

template<typename T>
bool CCachePool<T>::Push( const T& t )
{
	CLockWrite lock(_mutex);
	if (_vT.size()<_uSizeMax)
	{
		_vT.push_back(t);
		return true;
	}

	if (_uCur>=_uSizeMax)
		_uCur = 0;
	
	_vT[_uCur] = t;

	//��������ָ������
	++_uCur;
	return true;
}

template<typename T>
bool CCachePool<T>::Init()
{
	return true;
}

template<typename T>
bool CCachePool<T>::SetSizeMax( uint uSizeMax )
{
	CLockWrite lock(_mutex);
	_uSizeMax = uSizeMax;
	return true;
}

template<typename T>
CCachePool<T>::~CCachePool( void )
{
	_uSizeMax = 1000;
	_uCur = 0;
}

template<typename T>
CCachePool<T>::CCachePool( void )
{

}
