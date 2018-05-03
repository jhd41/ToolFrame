#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"

//缓冲池 Vector实现
template<typename T>
class CCachePool
{
	typedef std::vector<T> VectorT;
public:
	bool SetSizeMax(uint uSizeMax);//设置最大尺寸
	bool Init();
	
	//线程安全
public:
	bool IsEmpty()const;			//是否为空
	bool Push(const T& t);			//压入新缓存
	T	 Random()const;				//随机返回缓存内容
public:
	uint GetSizeMax()const;			//获取缓冲容量上限
	uint GetSize()const;			//获取当前缓冲大小
	T	 GetValue(uint uIndex)const;//获取缓存(位置) 返回 不能为引用，因为线程安全
	uint GetCur()const;				//获取下一指针位置
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

	//调整缓冲指针索引
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
