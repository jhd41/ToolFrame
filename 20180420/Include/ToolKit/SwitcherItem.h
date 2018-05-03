#pragma once

#include "Macro.h"

NS_TOOL_FRAME_BEGIN

//进度条小工具
//循环模式,当前值超过极限值 那么 重置
//非循环模式,当前值超过极限值，则为极限值
class TOOLFRAME_DLL CSwitcherItem
{
public:
	bool	SetLoop(bool bLoop);	//标记是否为循环模式
	int		AddItem(int nItemID);	//添加物品 返回该物品所在索引号
	bool	RemoveItem(int nItemID);//移除物品 返回该物品所在索引号
	bool	ClearItem();			//清空物品
	bool	AddItemRange(int nItemBegin,int nItemEnd);		//添加范围物品
	bool	AddItemRangeOpen(int nItemBegin,int nItemEnd);	//添加范围物品(开区间)
	
	int		GetSelIndex()const;		//获得当前选中的 索引
	int		GetSelItem()const;		//获得当前选中的 物品
	bool	IsItemEmpty()const;		//是否物品为空
	bool	IsItemVaild(int nItemID)const;//返回该物品是否有效
	uint	GetItemSize()const;		//获取物品数量
	bool	IsLoop()const;			//返回是否是循环模式

	int		SelIndex(int nIndex);	//选中指定索引号物品 返回实际指向有效物品索引
	int		SelItem(int nItemID);	//选中第一个物品 返回实际指向有效物品索引
	int		SelFirstItem();			//选中第一个物品 返回实际指向有效物品索引
	int		SelLastItem();			//选中最后一个物品 返回实际指向有效物品索引

	int		NextSel(int nStep=1);	//选中下一个 返回实际指向有效物品索引
	int		PrevSel(int nStep=1);	//选中上一个 返回实际指向有效物品索引
public:
	CSwitcherItem(void);
	virtual ~CSwitcherItem(void);
private:
	VectorInt	_vItem;
	int			_nIndexCur;
	bool		_bLoop;
};

NS_TOOL_FRAME_END
