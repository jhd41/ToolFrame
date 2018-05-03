#pragma once
#include "Macro.h"

NS_TOOL_FRAME_BEGIN

//优先队列
//注意:Front() 之后Pop()不一定是同一个
template<typename TValue>
class TPriorityQueue
{
	typedef std::list<TValue>	Queue;
	typedef std::vector<Queue>	VectorQueue;
public:
	void	Push(const TValue& tValue,int nPriority);
	bool	Pop();
	TValue& Front();
	bool	Empty();
	size_t	Size();
public:
	TPriorityQueue(int nPriorityMax);
	virtual ~TPriorityQueue(void);
private:
	VectorQueue	_vPriority;
	size_t		_uSize;
	TValue*		_pFront;//最近一次Front()得到的值
};

template<typename TValue>
size_t TPriorityQueue<TValue>::Size()
{
	return _uSize;
}

template<typename TValue>
bool TPriorityQueue<TValue>::Empty()
{
	return _uSize == 0;
}

template<typename TValue>
TValue& TPriorityQueue<TValue>::Front()
{
	typename VectorQueue::reverse_iterator itr;
	foreachR(itr,_vPriority){
		Queue& vQueue = *itr;
		if (!vQueue.empty())
		{
			TValue& tValue = vQueue.front();
			_pFront = &tValue;
			return tValue;
		}
	}
	//不可以走到这里
	assert(false);
	return _vPriority[0].front();
}

template<typename TValue>
bool TPriorityQueue<TValue>::Pop()
{
	typename VectorQueue::reverse_iterator itr;
	foreachR(itr,_vPriority){
		Queue& vQueue = *itr;
		if (!vQueue.empty())
		{
			if (nullptr == _pFront )
			{
				--_uSize;
				vQueue.pop_front();
				return true;
			}else
			{
				if (_pFront == &vQueue.front())
				{
					--_uSize;
					vQueue.pop_front();
					_pFront = nullptr;
					return true;
				}
			}
		}
	}
	return false;
}

template<typename TValue>
void TPriorityQueue<TValue>::Push(const TValue& tValue,int nPriority )
{
	_vPriority[nPriority].push_back(tValue);
	++_uSize;
}

template<typename TValue>
TPriorityQueue<TValue>::~TPriorityQueue( void )
{

}

template<typename TValue>
TPriorityQueue<TValue>::TPriorityQueue( int nPriorityMax )
{
	_pFront = nullptr;
	_uSize	= 0;
	_vPriority.resize(nPriorityMax);
}

NS_TOOL_FRAME_END
