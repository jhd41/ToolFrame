#pragma once
#include "IPage.h"

#ifdef MACRO_LIB_COCOS2D

#include "ToolFrame.h"

class TOOLFRAME_DLL IPageSingle
{
public:
	template<typename T>
	T*			RelacePage(int nUserData=0);
	template<typename T>
	bool		SafeRelacePage(int nUserData=0);
	bool		Init(IPage* pPage);
	template<typename T>
	bool		IsCurPage()const;
	bool		IsEmpty()const;
	IPage*		GetCurPage()const;
	bool		Clear();
private:
	template<typename T>
	T*			CreatePage();
	bool		DestoryPage(IPage*& pPage);
	bool		SetPage(IPage* pPage);
public:
	IPageSingle(void);
	virtual ~IPageSingle(void);
private:
	IPage*				_pPageCur;
	IPage*				_pPageParent;
};

template<typename T>
T* IPageSingle::CreatePage()
{
	T* pPage = new T();
	if (!pPage) return nullptr;

	if (_pPageParent)
		_pPageParent->AddChild(pPage);

	pPage->release();
	return pPage;
}

template<typename T>
bool IPageSingle::IsCurPage() const
{
	return _pPageCur && ToolFrame::IsTargetClass<T>(_pPageCur);
}

template<typename T>
T* IPageSingle::RelacePage(int nUserData)
{
	if (_pPageCur && ToolFrame::IsTargetClass<T>(_pPageCur))
		return nullptr;

	Clear();
	
	T* pPage = CreatePage<T>();
	if (!pPage)return nullptr;
	pPage->SetUserDataInt(nUserData);
	SetPage(pPage);
	return pPage;
}

template<typename T>
bool IPageSingle::SafeRelacePage( int nUserData/*=0*/ )
{
	if (IsCurPage<T>())return true;
	return !!RelacePage<T>(nUserData);
}

#endif //MACRO_LIB_COCOS2D
