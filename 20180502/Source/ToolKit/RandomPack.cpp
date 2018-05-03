#include "RandomPack.h"
#include "ToolStd.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

CRandomPack::CRandomPack()
{
	_nRandomMax = 0;
}

CRandomPack::CRandomPack( const CRandomPack& pack )
{
	_vRandom	= pack._vRandom;
	_nRandomMax = pack._nRandomMax;
}

CRandomPack::~CRandomPack(void)
{
}

bool CRandomPack::AddItem( uint uItemID,uint nProbability /*= 1*/ )
{
	if (nProbability <= 0)return false;

	_nRandomMax += nProbability;

	XRandomItem xItem;
	xItem.nProbability	= nProbability;
	xItem.uItemID		= uItemID;
	xItem.uRandKey		= _nRandomMax;
	return ToolFrame::Insert(_vRandom,xItem.uRandKey,xItem);
}

const CRandomPack::XRandomItem* CRandomPack::RandItemNode() const
{
	if (!IsValid())return nullptr;
	return ToolFrame::GetValuePtrUpperMap(_vRandom,ToolFrame::Rand(0,_nRandomMax-1));
}

uint CRandomPack::RandomItem()const
{
	const XRandomItem* pItem = RandItemNode();
	return pItem ? pItem->uItemID : INVALID_ID;
}

uint CRandomPack::RandomItem( bool bRemove )
{
	const XRandomItem* pItem = RandItemNode();
	if (!pItem)return INVALID_ID;

	if (!bRemove)
		return pItem->uItemID;

	uint uItemID = pItem->uItemID;

	_nRandomMax -= pItem->nProbability;
	_vRandom.erase(pItem->uRandKey);

	return uItemID;
}

bool CRandomPack::AddItemPtr( void* pItem,uint nProbability /*= 1*/ )
{
	if (nProbability <= 0)return false;

	_nRandomMax += nProbability;

	XRandomItem xItem;
	xItem.nProbability	= nProbability;
	xItem.pItem			= pItem;
	xItem.uRandKey		= _nRandomMax;
	return ToolFrame::Insert(_vRandom,xItem.uRandKey,xItem);
}

void* CRandomPack::RandomItemPtr() const
{
	const XRandomItem* pItem = RandItemNode();
	return pItem ? pItem->pItem : nullptr;
}

void* CRandomPack::RandomItemPtr( bool bRemove )
{
	const XRandomItem* pItem = RandItemNode();
	if (!pItem)return nullptr;

	if (!bRemove)
		return pItem->pItem;

	void* pItemUser = pItem->pItem;

	_nRandomMax -= pItem->nProbability;
	_vRandom.erase(pItem->uRandKey);

	return pItemUser;
}

bool CRandomPack::IsValid()const
{
	return _nRandomMax >= 1 && !_vRandom.empty();
}

size_t CRandomPack::GetItemCount()const
{
	return _vRandom.size();
}

bool CRandomPack::Clear()
{
	ToolFrame::Clear(_vRandom);
	_nRandomMax = 0;
	return true;
}

const CRandomPack::MapRandomItem& CRandomPack::GetRandItem() const
{
	return _vRandom;
}

NS_TOOL_FRAME_END
