#pragma once
#include "Macro.h"

NS_TOOL_FRAME_BEGIN

//�����:
//��������ĸ���(����) ����õ�һ��ֵ

class CRandomPack
{
public:
	struct XRandomItem{
		uint	nProbability;	//����
		uint	uItemID;		//��ƷID
		void*	pItem;			//�û��Զ�����Ʒ
		uint	uRandKey;		//��ǰ�������ǩ
		XRandomItem(){
			nProbability = 1;
			uItemID = INVALID_ID;
			pItem = 0;
			uRandKey = 0;
		}
	};

	typedef std::map<uint,XRandomItem> MapRandomItem;
public:
	bool	AddItem(uint uItemID,uint nProbability = 1);
	uint	RandomItem()const;
	uint	RandomItem(bool bRemove);

	bool	AddItemPtr(void* pItem,uint nProbability = 1);
	void*	RandomItemPtr()const;
	void*	RandomItemPtr(bool bRemove);

	template<typename T>
	T*		RandomItemPtr()const;

	template<typename T>
	T*		RandomItemPtr(bool bRemove);

	bool	IsValid()const;
	size_t	GetItemCount()const;				//�����Ʒ����
	bool	Clear();
public:
	const MapRandomItem& GetRandItem()const;			//��ȡ������Ʒ��û��Ҫʱ ��Ҫ ��ȡ
private:
	const XRandomItem* RandItemNode()const;
public:
	CRandomPack();
	CRandomPack(const CRandomPack& pack);//��������
	virtual ~CRandomPack(void);
private:
	MapRandomItem	_vRandom;//<range,Item>
	uint			_nRandomMax;
};

template<typename T>
T*	CRandomPack::RandomItemPtr()const
{
	return (T*)RandomItemPtr();
}
template<typename T>
T*	CRandomPack::RandomItemPtr(bool bRemove)
{
	return (T*)RandomItemPtr(bRemove);
}
NS_TOOL_FRAME_END
