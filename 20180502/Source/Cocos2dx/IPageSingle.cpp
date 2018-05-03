#include "IPageSingle.h"

#ifdef MACRO_LIB_COCOS2D

#include "ToolFrame.h"

IPageSingle::IPageSingle(void)
{
	_pPageCur		= nullptr;
	_pPageParent	= nullptr;
}

IPageSingle::~IPageSingle(void)
{
	Clear();
}

bool IPageSingle::DestoryPage( IPage*& pPage )
{
	if (!pPage)return true;

	pPage->MarkRemoveFromeParent();
	pPage =nullptr;
	return true;
}

bool IPageSingle::Init( IPage* pPage)
{
	_pPageParent = pPage;
	return true;
}

bool IPageSingle::IsEmpty() const
{
	return !_pPageCur;
}

IPage* IPageSingle::GetCurPage() const
{
	return _pPageCur;
}

bool IPageSingle::Clear()
{
	if (!_pPageCur)return true;
	
	_pPageCur->MarkRemoveFromeParent();
	_pPageCur->release();
	_pPageCur =nullptr;
	return true;
}

bool IPageSingle::SetPage( IPage* pPage )
{
	if (!pPage)return false;

	Clear();

	_pPageCur = pPage;
	_pPageCur->retain();
	return true;
}

#endif //MACRO_LIB_COCOS2D

