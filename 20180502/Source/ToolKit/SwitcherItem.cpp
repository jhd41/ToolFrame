#include "SwitcherItem.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

CSwitcherItem::CSwitcherItem(void)
{
	_nIndexCur = 0;
	_bLoop = true;
}

CSwitcherItem::~CSwitcherItem(void)
{
}

bool CSwitcherItem::SetLoop( bool bLoop )
{
	_bLoop = bLoop;
	return true;
}

int CSwitcherItem::AddItem( int nItemID )
{
	ToolFrame::PushBack(_vItem,nItemID);
	return (int)_vItem.size()-1;
}

bool CSwitcherItem::RemoveItem( int nItemID )
{
	return ToolFrame::EraseByValue(_vItem,nItemID);
}

bool CSwitcherItem::ClearItem()
{
	ToolFrame::Clear(_vItem);
	_nIndexCur = 0;
	return true;
}

int CSwitcherItem::GetSelIndex() const
{
	return _nIndexCur;
}

int CSwitcherItem::GetSelItem() const
{
	if (!ToolFrame::IsVaildIndex(_vItem,_nIndexCur))return -1;
	return ToolFrame::GetValueByIndex(_vItem,_nIndexCur);
}

bool CSwitcherItem::IsLoop() const
{
	return _bLoop;
}

int CSwitcherItem::SelIndex( int nIndex )
{
	_nIndexCur = nIndex;

	if (_vItem.empty())
		return -1;

	int nItemSize = (int)_vItem.size();

	//不是循环模式
	if (!_bLoop)
	{
		if (0<_nIndexCur)
			_nIndexCur = 0;
		if (_nIndexCur>nItemSize -1)
			_nIndexCur = nItemSize -1;
		return _nIndexCur;
	}

	if (_nIndexCur < 0)
		_nIndexCur += nItemSize;
	_nIndexCur %= nItemSize;

	return _nIndexCur;
}

int CSwitcherItem::SelItem( int nItemID )
{
	int nIndex = ToolFrame::GetIndexByValue(_vItem,nItemID);
	if (nIndex<0)return -1;
	return SelIndex(nIndex);
}

int CSwitcherItem::NextSel( int nStep/*=1*/ )
{
	return SelIndex(_nIndexCur + nStep);
}

int CSwitcherItem::PrevSel( int nStep/*=1*/ )
{
	return SelIndex(_nIndexCur - nStep);
}

uint CSwitcherItem::GetItemSize() const
{
	return (uint)_vItem.size();
}

int CSwitcherItem::SelFirstItem()
{
	return SelIndex(0);
}

int CSwitcherItem::SelLastItem()
{
	if (_vItem.empty())return -1;
	return SelIndex((int)_vItem.size()-1);
}

bool CSwitcherItem::AddItemRange( int nItemBegin,int nItemEnd )
{
	if (nItemEnd<nItemBegin)return false;
	int nRange = nItemEnd - nItemBegin;
	for(int nIndex =0;nIndex < nRange;++nIndex){
		ToolFrame::PushBack(_vItem,nItemBegin + nIndex);
	}
	
	return true;
}

bool CSwitcherItem::AddItemRangeOpen( int nItemBegin,int nItemEnd )
{
	if (nItemEnd<nItemBegin)return false;
	return AddItemRange(nItemBegin+1,nItemEnd-1);
}

bool CSwitcherItem::IsItemEmpty() const
{
	return _vItem.empty();
}

bool ToolFrame::CSwitcherItem::IsItemVaild(int nItemID) const
{
	return ToolFrame::GetIndexByValue(_vItem, nItemID) >= 0;
}

NS_TOOL_FRAME_END
