#pragma once
#include "Macro.h"

NS_TOOL_FRAME_BEGIN

//随机包:
//根据随机的概率(整数) 随机得到一个值

class CRandomPack
{
public:
	struct XRandomItem{
		uint	nProbability;	//几率
		uint	uItemID;		//物品ID
		void*	pItem;			//用户自定义物品
		uint	uRandKey;		//当前的随机标签
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
	size_t	GetItemCount()const;				//获得物品个数
	bool	Clear();
public:
	const MapRandomItem& GetRandItem()const;			//获取所有物品，没必要时 不要 获取
private:
	const XRandomItem* RandItemNode()const;
public:
	CRandomPack();
	CRandomPack(const CRandomPack& pack);//拷贝构造
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
