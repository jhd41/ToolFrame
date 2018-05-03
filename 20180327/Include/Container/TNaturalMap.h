#pragma once
#include "Macro.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

//��Ȼ��ӳ���
//�����ṩ����(ԼΪFastMax)���ڵ���0�����Ȼ����ӳ��
//ֵֻ�ṩָ������(�����Ч���Լ���д����)  ����GetValueЧ�ʼ��罵�ͣ�
//˼·:
//��std::vectorΪӳ������ӳ��
//ֻ�Ӳ�ɾ
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
	typedef std::list<TValue>		LstValue;//���ڱ���
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

	VectorValue*	_pvFast;	//(������)������ֵû��Խ��ʱ�����
	VectorNode*		_pvNormal;	//(������)��Խ��������ʱ�����
	MapValue*		_pmapNormal;//(������)��Խ�������ܶ�ʱ�����

	LstValue		_vTotal;	//������е�Ԫ�� ���� �ⲿ����
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
	//����ȫ��
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
		//������������������ֵ
		ASSERT_LOG_ERROR(!(_pvNormal && _pmapNormal));

		//�����ûֵ
		if (!_pvNormal && !_pmapNormal)
		{
			_pvNormal = new VectorNode();
			ASSERT_LOG_ERROR(_pvNormal);
		}

		//�����ͨӳ���Ƿ����㹻�ռ�
		if (_pvNormal)
		{
			if (!_pvNormal->empty() && _pvNormal->size() + 1 >= _uNormalMax)
			{
				//���������ôȫ���Ƶ�mapӳ���
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

			//����ֵ
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
	//�ͷű���new�Ľڵ�
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

	//�ͷŸ�������
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
