#pragma once
#include "Macro.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

//自然数映射表
//本类提供少量(约为FastMax)大于等于0起的自然数的映射
//值只提供指针类型(方便高效率以及书写方便)  否则GetValue效率急剧降低！
//思路:
//以std::vector为映射表进行映射
//只加不删
template<typename TValue>
class TNaturalMap
{
	struct SNode 
	{
		UINT	uKey;
		TValue	tValue;
	};
private:
	typedef std::vector<TValue>		VectorValue;
	typedef std::vector<SNode*>		VectorNode;
	typedef std::map<UINT,TValue>	MapValue;
public:
	typedef std::list<TValue>		LstValue;//用于遍历
public:
	UINT	GetFastMax();
	UINT	GetNormalMax();

	void	Insert(UINT uKey,TValue tValue);
	TValue	GetValue(UINT uKey);

	std::list<TValue>& GetTotal();

	void	Clear();

	size_t	GetSize();
	bool	IsEmpty();
	bool	Erase(UINT uKey);
public:
	TNaturalMap(UINT uFastMax=1024,UINT uNormalMax=16);
	virtual ~TNaturalMap(void);
private:
	UINT _uFastMax;
	UINT _uNormalMax;

	VectorValue*	_pvFast;	//(高性能)当传入值没有越界时用这个
	VectorNode*		_pvNormal;	//(中性能)当越界数量少时用这个
	MapValue*		_pmapNormal;//(低性能)当越界数量很多时用这个

	LstValue		_vTotal;	//存放所有的元素 用于 外部遍历
};

template<typename TValue>
bool TNaturalMap<TValue>::IsEmpty()
{
	return _vTotal.empty();
}

template<typename TValue>
size_t TNaturalMap<TValue>::GetSize()
{
	return _vTotal.size();
}

template<typename TValue>
TValue TNaturalMap<TValue>::GetValue(UINT uKey )
{
	if (uKey < _uFastMax)
	{
		if (nullptr == _pvFast)return nullptr;
		
		ASSERT_LOG_ERROR(_pvFast);
		return (*_pvFast)[uKey];
	}else
	{
		if (_pvNormal)
		{
			typename VectorNode::iterator itr;
			foreach(itr,*_pvNormal){
				SNode* pNode = *itr;
				ASSERT_LOG_ERROR(pNode);
				if (uKey == pNode->uKey)
				{
					return pNode->tValue;
				}
			}
		}
		if (_pmapNormal)
		{
			typename MapValue::iterator itr = _pmapNormal->find(uKey);
			if (itr == _pmapNormal->end())
			{
				return nullptr;
			}
			return itr->second;
		}
	}

	return nullptr;
}

template<typename TValue>
void TNaturalMap<TValue>::Insert( UINT uKey,TValue tValue)
{
	//加入全局
	_vTotal.push_back(tValue);
	
	if (uKey < _uFastMax)
	{
		if (nullptr == _pvFast)
		{
			ASSERT_LOG_ERROR(_uFastMax>0);
			_pvFast = new VectorValue();
			_pvFast->resize(_uFastMax+1,nullptr);
		}

		ASSERT_LOG_ERROR(_pvFast);
		(*_pvFast)[uKey] = tValue;
		return;
	}else
	{
		//不可能两个容器都有值
		ASSERT_LOG_ERROR(!(_pvNormal && _pmapNormal));

		//如果都没值
		if (!_pvNormal && !_pmapNormal)
		{
			_pvNormal = new VectorNode();
			ASSERT_LOG_ERROR(_pvNormal);
		}

		//检查普通映射是否还有足够空间
		if (_pvNormal)
		{
			if (!_pvNormal->empty() && _pvNormal->size() + 1 >= _uNormalMax)
			{
				//如果不够那么全部移到map映射表
				_pmapNormal = new MapValue();
				ASSERT_LOG_ERROR(_pmapNormal);

				typename VectorNode::iterator itr;
				foreach(itr,*_pvNormal){
					SNode* pNode = *itr;
					ASSERT_LOG_ERROR(pNode);
					_pmapNormal->insert(std::make_pair(pNode->uKey,pNode->tValue));

					delete pNode;
				}
				_pvNormal->clear();
				delete _pvNormal;
				_pvNormal = nullptr;
			}

			//插入值
			if (_pvNormal)
			{
				SNode* pNode = new SNode();
				ASSERT_LOG_ERROR(pNode);
				pNode->uKey		= uKey;
				pNode->tValue	= tValue;

				_pvNormal->push_back(pNode);
				return;
			}
		}

		if (_pmapNormal)
		{
			(*_pmapNormal)[uKey]= tValue;
			return ;
		}
	}
}

template<typename TValue>
std::list<TValue>& TNaturalMap<TValue>::GetTotal()
{
	return _vTotal;
}

template<typename TValue>
TNaturalMap<TValue>::TNaturalMap(UINT uFastMax/*=1024*/,UINT uNormalMax/*=16*/ )
{
	_uFastMax	= uFastMax;
	_uNormalMax	= uNormalMax;

	_pvFast		= nullptr;
	_pvNormal	= nullptr;
	_pmapNormal = nullptr;
}

template<typename TValue>
TNaturalMap<TValue>::~TNaturalMap( void )
{
	Clear();
}

template<typename TValue>
void TNaturalMap<TValue>::Clear()
{
	//释放本类new的节点
	if (_pvNormal)
	{
		typename VectorNode::iterator itr;
		foreach(itr,*_pvNormal){
			SNode* pNode = *itr;
			ASSERT_LOG_ERROR(pNode);
			delete pNode;
		}
		_pvNormal->clear();
	}

	//释放各个容器
	if (_pvFast)
	{
		delete _pvFast;
		_pvFast =nullptr;
	}

	if (_pvNormal)
	{
		delete _pvNormal;
		_pvNormal = nullptr;
	}

	if (_pmapNormal)
	{
		delete _pmapNormal;
		_pmapNormal = nullptr;
	}

	_vTotal.clear();
}


template<typename TValue>
UINT TNaturalMap<TValue>::GetNormalMax()
{
	return _uNormalMax;
}

template<typename TValue>
UINT TNaturalMap<TValue>::GetFastMax()
{
	return _uFastMax;
}

NS_TOOL_FRAME_END
