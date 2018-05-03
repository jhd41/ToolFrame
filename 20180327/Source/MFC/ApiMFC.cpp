#include "ApiMFC.h"

#ifdef MACRO_LIB_MFC

#include <afxinet.h>
#include <windows.h>
#include <stdarg.h>
#include <atltime.h>
#include <atlimage.h>

#include "ToolFrame.h"
#include "ApiWin.h"

void ApiMFC::Show(CComboBox& cComBox,const MapStringString* pvMap,bool bFirst){
	cComBox.ResetContent();
	if(pvMap){
		MergeShow(cComBox,*pvMap,bFirst);

		SetSelected(cComBox,0);
	}
}

void ApiMFC::Show(CComboBox& cComBox,const MapStringString& vMap,bool bFirst){
	cComBox.ResetContent();

	MergeShow(cComBox,vMap,bFirst);
	
	SetSelected(cComBox,0);
}
void ApiMFC::MergeShow(CListBox& cLstBox,const MapStringString& vMap,bool bFirst){
	CString csBuff;
	MapStringString::const_iterator itrOptions;
	foreach(itrOptions,vMap){
		if (bFirst)
			csBuff=(itrOptions->first).c_str();
		else
			csBuff=(itrOptions->second).c_str();

		cLstBox.InsertString(cLstBox.GetCount(),csBuff);
	}
}
void ApiMFC::MergeShow(CComboBox& cComBox,const MapStringString* pvMap,bool bFirst){
	if(pvMap)
		MergeShow(cComBox,*pvMap,bFirst);
}

void ApiMFC::MergeShow(CComboBox& cComBox,const MapStringString& vMap,bool bFirst){
	CString csBuff;
	MapStringString::const_iterator itrOptions;
	foreach(itrOptions,vMap){
		if (bFirst)
			csBuff=(itrOptions->first).c_str();
		else
			csBuff=(itrOptions->second).c_str();

		cComBox.InsertString(cComBox.GetCount(),csBuff);
	}
}
void ApiMFC::Show( CListBox& cLstBox,const VectorString& vValue )
{
	cLstBox.ResetContent();

	CString csBuff;
	int nIndex =0;
	VectorString::const_iterator itr;
	foreach(itr,vValue){
		csBuff = (*itr).c_str();
		cLstBox.InsertString(nIndex++,csBuff);
	}
}
void ApiMFC::Show(CListBox& cLstBox,const MapStringString* vMap,bool bFirst){
	cLstBox.ResetContent();

	if (vMap)
	{
		MergeShow(cLstBox,*vMap,bFirst);

		SetSelected(cLstBox,0);
	}
}
void ApiMFC::Show(CListBox& cLstBox,const MapStringString& vMap,bool bFirst){
	cLstBox.ResetContent();
	MergeShow(cLstBox,vMap,bFirst);

	SetSelected(cLstBox,0);
}

void ApiMFC::Show( CComboBox& cComBox,const VectorString& vSrc )
{
	cComBox.ResetContent();

	CString csBuff;
	int nIndex =0;
	VectorString::const_iterator itr;
	foreach(itr,vSrc){
		csBuff = (*itr).c_str();
		cComBox.InsertString(nIndex++,csBuff);
	}
}

void ApiMFC::Show( CListCtrl& cEdit,int nRow,int nArgs,... )
{
	cEdit.InsertItem(nRow,_T(""));

	va_list vaList;
	va_start(vaList, nArgs);
	
	for (int nIndex = 0;nIndex < nArgs;++nIndex)
	{
		CString csBUff = ToCString(*va_arg(vaList, std::string*));
		cEdit.SetItemText(nRow,nIndex,csBUff);
	}

	va_end(vaList);

}
int ApiMFC::FindString(const CComboBox& cBox,const std::string& sValue){
	return FindString(cBox,ApiMFC::ToCString(sValue));
}
int ApiMFC::FindString(const CComboBox& cBox,const CString& sValue){
	int nReturn = -1;
	do 
	{
		nReturn = cBox.FindStringExact(nReturn,sValue);
		if (nReturn >= 0)
		{
			CString csDes;
			cBox.GetLBText(nReturn,csDes);
			if (csDes == sValue)
				break;
		}
	} while (nReturn>=0);

	return nReturn;
}

int ApiMFC::FindString( const CListCtrl& vShow,const std::string& sValue,int nCol )
{
	for (int nIndex = 0; nIndex < vShow.GetItemCount(); ++nIndex)
	{
		if (ToString(vShow.GetItemText(nIndex,nCol)) == sValue)
			return nIndex;
	}

	return -1;
}

int ApiMFC::SetSelected( CComboBox& cBox,const std::string& sValue ,bool bSet)
{
	return SetSelected(cBox,ApiMFC::ToCString(sValue),bSet);
}
int ApiMFC::SetSelected( CComboBox& cBox,const CString& sValue ,bool bSet)
{
	int nReturn = FindString(cBox,sValue);
	if (nReturn >= 0)
	{
		cBox.SetCurSel(nReturn);
	}

	if (bSet && nReturn < 0)
		cBox.SetWindowText(sValue);

	return nReturn;	
}

int ApiMFC::SetSelected( CComboBox& cBox,int nIndex )
{
	//如果nIndex是合法的
	int nReturn = -1;
	if( nIndex >= -1 && nIndex < cBox.GetCount())
		nReturn = nIndex;

	cBox.SetCurSel(nReturn);
	return nReturn;
}

int ApiMFC::SetSelected( CListBox& cBox,int nIndex /*= 0*/ )
{
	//如果nIndex是合法的
	int nReturn = -1;
	if( nIndex >= -1 && nIndex < cBox.GetCount())
		nReturn = nIndex;

	cBox.SetCurSel(nReturn);
	return nReturn;
}
bool ApiMFC::SetNotSel(CListCtrl& cBox){
	for (int nRow=0;nRow<cBox.GetItemCount();++nRow)
		SetNotSel(cBox,nRow);
	return true;
}
bool ApiMFC::SetNotSel(CListCtrl& cBox, int nRow ){
	cBox.SetItemState(nRow,0,LVIS_SELECTED);
	return true;
}

bool ApiMFC::SetNotSel(CListBox& cBox){
	//cBox.SetCurSel(-1);
	for(int nIndex =0;nIndex<cBox.GetCount();++nIndex)
		SetNotSel(cBox,nIndex);
	return true;
}

bool ApiMFC::SetNotSel(CListBox& cBox, int nRow ){
	cBox.SetSel(nRow,FALSE);
	return true;
}

bool ApiMFC::SetSelected( CListCtrl& cBox, int nRow )
{
	cBox.SetSelectionMark(nRow);
	cBox.SetItemState(nRow,LVIS_SELECTED|LVIS_FOCUSED|LVIS_CUT,LVIS_SELECTED|LVIS_FOCUSED|LVIS_CUT|LVIS_DROPHILITED);//选择
	cBox.EnsureVisible(nRow,TRUE);
	return true;
}
bool ApiMFC::SetSelected(CListCtrl& cBox){
	for (int nRow=0;nRow<cBox.GetItemCount();++nRow)
		SetSelected(cBox,nRow);

	return true;
}
void ApiMFC::Update(const CComboBox& cComBoxS,VectorString& vDes )
{
	vDes.clear();

	CString csBuff;

	for (int nIndex = 0; nIndex < cComBoxS.GetCount(); ++nIndex)
	{
		cComBoxS.GetLBText(nIndex,csBuff);
		vDes.push_back(ToString(csBuff));
	}
}
void ApiMFC::Update(const CListBox& cBox,VectorString& vDes){
	vDes.clear();

	CString csBuff;

	for (int nIndex = 0; nIndex < cBox.GetCount(); ++nIndex)
	{
		cBox.GetText(nIndex,csBuff);
		vDes.push_back(ToString(csBuff));
	}
}
bool ApiMFC::IsExists( const CComboBox& cBox,const std::string& sValue )
{
	CString csBuff = sValue.c_str();
	int nIndex = cBox.FindString(0,csBuff);

	if( nIndex >= 0 && nIndex < cBox.GetCount())
		return true;
	return false;
}

bool ApiMFC::SetDefault( const CComboBox& cBox,std::string& sValue )
{
	CString csBuff;
	int nIndex = cBox.GetCurSel();
	if (nIndex >= 0 && nIndex < cBox.GetCount())	cBox.GetLBText(nIndex,csBuff);
	if (csBuff.IsEmpty() && cBox.GetCount() > 0)	cBox.GetLBText(0,csBuff);
	if (csBuff.IsEmpty())							cBox.GetWindowText(csBuff);

	sValue = ToString(csBuff);

	return cBox.GetCount() > 0;
}

std::string ApiMFC::GetHtmlSource( const std::string& sAddress )
{
	CString csAddress = sAddress.c_str();

	CInternetSession mySession(nullptr,0);
	CHttpFile* myHttpFile = (CHttpFile*)mySession.OpenURL(csAddress);

	CString csSource,csLine;
	while(myHttpFile->ReadString(csLine)){
		csSource += csLine;
		csSource += "\n";
	}
	myHttpFile->Close();
	mySession.Close();

	return ToString(csSource);
}

std::string ApiMFC::GetHtmlSource( const CString& sAddress )
{
	return GetHtmlSource(ToString(sAddress));
}
CString ApiMFC::ToCString( const std::string& sSrc)
{
	return CString(sSrc.c_str());
}

std::string ApiMFC::ToString( const CString& sSrc )
{
	std::string_t sReturn;
	sReturn.assign(sSrc);
	return ApiWin::ToMulti(sReturn);
}

std::string ApiMFC::ToString( const VectorString& vString,const std::string& sp/*="\\\r\n"*/ )
{
	std::stringstream sStream;
	VectorString::const_iterator itr;
	foreach(itr,vString){
		const std::string& sString = *itr;
		sStream<<sString<<sp;
	}

	return sStream.str();
}

void ApiMFC::InitColumn( CListCtrl& vShow,int nCol,CString sName,int nWidth )
{
	vShow.InsertColumn(nCol,sName);
	vShow.SetColumnWidth(nCol,nWidth);
}
void ApiMFC::InitName(CListCtrl& vShow,int nCols,...){
	SetReport(vShow);
	DeleteAllColumns(vShow);

	va_list vaList;
	va_start(vaList, nCols);

	for (int nCol = 0;nCol < nCols;++nCol)
	{
		vShow.InsertColumn(nCol,va_arg(vaList, char_t*));
	}

	va_end(vaList);

	SuitStringWidth(vShow);
}
void ApiMFC::Init(CListCtrl& vShow,int nCols,...){
	va_list vaList;
	va_start(vaList, nCols);

	DeleteAllColumns(vShow);

	for (int nCol = 0;nCol < nCols;++nCol)
	{
		vShow.InsertColumn(nCol,	va_arg(vaList, char_t*));
		vShow.SetColumnWidth(nCol,	va_arg(vaList, int));
	}

	va_end(vaList);
}

void ApiMFC::Init( CListCtrl& vShow,const MapIntString& vString )
{
	SetReport(vShow);
	DeleteAllColumns(vShow);

	MapIntString::const_iterator itr;
	foreach(itr,vString){
		vShow.InsertColumn(itr->first,ApiWin::ToWide(itr->second).c_str());
	}

	SuitStringWidth(vShow);
}

void ApiMFC::Init( CListCtrl& vShow,const VectorString& vString )
{
	SetReport(vShow);
	DeleteAllColumns(vShow);

	int nCol = 0;
	VectorString::const_iterator itr;
	foreach(itr,vString){
		const std::string& sString = *itr; 
		vShow.InsertColumn(nCol,ApiWin::ToWide(sString).c_str());

		++nCol;
	}

	SuitStringWidth(vShow);
}

void ApiMFC::Init( CComboBox&cBox,int nCols,... )
{
	cBox.Clear();

	va_list vaList;
	va_start(vaList, nCols);
	for (int nCol = 0;nCol < nCols;++nCol)
	{
		cBox.AddString(va_arg(vaList, char_t*));
	}
	cBox.SetCurSel(0);
	va_end(vaList);
}

void ApiMFC::Init( CListCtrl& vShow,const std::string& s1 )
{
	VectorString vString;
	vString.push_back(s1);
	return Init(vShow,vString);
}

void ApiMFC::Init( CListCtrl& vShow,const std::string& s1,const std::string& s2 )
{
	VectorString vString;
	vString.push_back(s1);
	vString.push_back(s2);
	return Init(vShow,vString);
}

void ApiMFC::Init( CListCtrl& vShow,const std::string& s1,const std::string& s2,const std::string& s3 )
{
	VectorString vString;
	vString.push_back(s1);
	vString.push_back(s2);
	vString.push_back(s3);
	return Init(vShow,vString);
}

void ApiMFC::Init( CListCtrl& vShow,const std::string& s1,const std::string& s2,const std::string& s3,const std::string& s4 )
{
	VectorString vString;
	vString.push_back(s1);
	vString.push_back(s2);
	vString.push_back(s3);
	vString.push_back(s4);
	return Init(vShow,vString);
}

void ApiMFC::Init( CListCtrl& vShow,const std::string& s1,const std::string& s2,const std::string& s3,const std::string& s4,const std::string& s5 )
{
	VectorString vString;
	vString.push_back(s1);
	vString.push_back(s2);
	vString.push_back(s3);
	vString.push_back(s4);
	vString.push_back(s5);
	return Init(vShow,vString);
}

void ApiMFC::Init( CListCtrl& vShow,const std::string& s1,const std::string& s2,const std::string& s3,const std::string& s4,const std::string& s5,const std::string& s6 )
{
	VectorString vString;
	vString.push_back(s1);
	vString.push_back(s2);
	vString.push_back(s3);
	vString.push_back(s4);
	vString.push_back(s5);
	vString.push_back(s6);
	return Init(vShow,vString);
}

void ApiMFC::Init( CListCtrl& vShow,const std::string& s1,const std::string& s2,const std::string& s3,const std::string& s4,const std::string& s5,const std::string& s6,const std::string& s7 )
{
	VectorString vString;
	vString.push_back(s1);
	vString.push_back(s2);
	vString.push_back(s3);
	vString.push_back(s4);
	vString.push_back(s5);
	vString.push_back(s6);
	vString.push_back(s7);
	return Init(vShow,vString);
}

void ApiMFC::Init( CListCtrl& vShow,const std::string& s1,const std::string& s2,const std::string& s3,const std::string& s4,const std::string& s5,const std::string& s6,const std::string& s7,const std::string& s8 )
{
	VectorString vString;
	vString.push_back(s1);
	vString.push_back(s2);
	vString.push_back(s3);
	vString.push_back(s4);
	vString.push_back(s5);
	vString.push_back(s6);
	vString.push_back(s7);
	vString.push_back(s8);
	return Init(vShow,vString);
}

void ApiMFC::Init( CListCtrl& vShow,const std::string& s1,const std::string& s2,const std::string& s3,const std::string& s4,const std::string& s5,const std::string& s6,const std::string& s7,const std::string& s8,const std::string& s9 )
{
	VectorString vString;
	vString.push_back(s1);
	vString.push_back(s2);
	vString.push_back(s3);
	vString.push_back(s4);
	vString.push_back(s5);
	vString.push_back(s6);
	vString.push_back(s7);
	vString.push_back(s8);
	vString.push_back(s9);
	return Init(vShow,vString);
}

void ApiMFC::DeleteAllColumns(CListCtrl& vShow){
	while(vShow.DeleteColumn(0));
}

std::string ApiMFC::GetSelectd( const CComboBox& cBox )
{
	CString csBuff;
	int nIndex = cBox.GetCurSel();
	nIndex >= 0 ? cBox.GetLBText(nIndex,csBuff) : cBox.GetWindowText(csBuff);

	return ToString(csBuff);
}

bool ApiMFC::SetSelectd(CComboBox& cBox, int nRow /*= -1*/ )
{
	if (nRow < 0 && cBox.GetCount()>0)
	{
		nRow = cBox.GetCount() - 1;
	}
	
	cBox.SetCurSel(nRow);
	return true;
}

void ApiMFC::SetTime( CDateTimeCtrl& cCtl,time_t nTime )
{
	CTime mTime = nTime;
	cCtl.SetTime(&mTime);
}

time_t ApiMFC::GetTime(const CDateTimeCtrl& cCtl )
{
	CTime tMFCTime;
	cCtl.GetTime(tMFCTime);
	return tMFCTime.GetTime();
}
void ApiMFC::SetFormatDataTime(CDateTimeCtrl& cCtl){
	cCtl.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
}
void ApiMFC::ExpandTree(CTreeCtrl& cTree ){
	cTree.Expand(TVI_ROOT,TVE_EXPAND);
	HTREEITEM item = cTree.GetChildItem(TVI_ROOT);
	while(item != nullptr){
		ExpandChild(cTree,item);
		item = cTree.GetNextSiblingItem(item);
	}
}
void ApiMFC::ExpandChild( CTreeCtrl& cTree,const HTREEITEM& itemParent){
	cTree.Expand(itemParent,TVE_EXPAND);
	if (cTree.ItemHasChildren(itemParent)){
		HTREEITEM item = cTree.GetChildItem(itemParent);
		while(item != nullptr){
			ExpandChild(cTree,item);
			item = cTree.GetNextSiblingItem(item);
		}
	}
}

void ApiMFC::CopyTree( const CTreeCtrl& cTreeSrc,CTreeCtrl& cTreeDes ){
	cTreeDes.DeleteAllItems();
	CopyChild(cTreeSrc,cTreeDes,TVI_ROOT,TVI_ROOT);
}
void ApiMFC::CopyChild(const CTreeCtrl& cTreeSrc,CTreeCtrl& cTreeDes,const HTREEITEM& itemSrcParent,const HTREEITEM& itemDesParent){
	HTREEITEM itemSrc = cTreeSrc.GetChildItem(itemSrcParent);
	while(itemSrc != nullptr){
		HTREEITEM itemDes = cTreeDes.InsertItem(cTreeSrc.GetItemText(itemSrc),itemDesParent);
		if (cTreeSrc.ItemHasChildren(itemSrc))
			CopyChild(cTreeSrc,cTreeDes,itemSrc,itemDes);

		itemSrc = cTreeSrc.GetNextSiblingItem(itemSrc);
	}
}

void ApiMFC::CheckedTree( CTreeCtrl& cTreeSrc,bool bChecked /*= true*/ )
{
	CheckedChild(cTreeSrc,TVI_ROOT,bChecked);
}

void ApiMFC::CheckedChild( CTreeCtrl& cTreeSrc,const HTREEITEM& itemParent,bool bChecked /*= true*/ )
{
	HTREEITEM item = cTreeSrc.GetChildItem(itemParent);
	while(item != nullptr){
		cTreeSrc.SetCheck(item,bChecked);
		if (cTreeSrc.ItemHasChildren(item))
			CheckedChild(cTreeSrc,item,bChecked);

		item = cTreeSrc.GetNextSiblingItem(item);
	}
}

void ApiMFC::GetCheckedItems(std::set<HTREEITEM>& vDes,const CTreeCtrl& cTreeSrc)
{
	GetCheckedItems(vDes,cTreeSrc,TVI_ROOT);
}

void ApiMFC::GetCheckedItems( std::set<HTREEITEM>& vDes,const CTreeCtrl& cTreeSrc,const HTREEITEM& itemParent )
{
	HTREEITEM item = cTreeSrc.GetChildItem(itemParent);
	while(item != nullptr){
		if (cTreeSrc.GetCheck(item))
			vDes.insert(item);
		if (cTreeSrc.ItemHasChildren(item))
			GetCheckedItems(vDes,cTreeSrc,item);

		item = cTreeSrc.GetNextSiblingItem(item);
	}
}

HBITMAP ApiMFC::LoadPngPicture(const std::string& sPath) 
{
	CImage MyMouseImage;
	MyMouseImage.Load(ApiWin::ToStringT(sPath).c_str()); 
	if(MyMouseImage.IsNull()) return nullptr; 
	
	return MyMouseImage.Detach();
}

void ApiMFC::MakeBackAlpha(CImage& img){
	for(int i = 0; i < img.GetWidth(); i++)
	{
		for(int j = 0; j < img.GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char *>(img.GetPixelAddress(i , j));
			pucColor[0] = pucColor[0] * pucColor[3] / 255;
			pucColor[1] = pucColor[1] * pucColor[3] / 255;
			pucColor[2] = pucColor[2] * pucColor[3] / 255;
		}
	}
}

CRect ApiMFC::GetRect( const CImage& img,const CPoint& ptPos,double fRate,const CPoint& ptBegin )
{
	CRect rect = GetRect(img,ptPos);

	Mult(rect,fRate);

	rect.OffsetRect(ptBegin);

	return rect;
}

CRect ApiMFC::GetRect( const CImage& img,const CPoint& ptPos )
{
	CRect rect = GetRect(img);
	rect.OffsetRect(ptPos);
	return rect;
}

CRect ApiMFC::GetRect( const CImage& img )
{
	return CRect(0,0,img.GetWidth(),img.GetHeight());
}

bool ApiMFC::IsEmptyLine( CListCtrl& cBox,int nRow )
{
	for(int nCol = 0 ;nCol < cBox.GetHeaderCtrl()-> GetItemCount();++nCol){
		if (!cBox.GetItemText(nRow,nCol).IsEmpty())
			return false;
	}

	return true;
}
void ApiMFC::GetColString(const CListCtrl& cBox,int nCol,std::vector<CString>& vStrings )
{
	for(int nRow  =0;nRow<cBox.GetItemCount();++nRow){
		vStrings.push_back(cBox.GetItemText(nRow,nCol));
	}
}

void ApiMFC::GetColString( const CListCtrl& cBox,int nCol,VectorString& vStrings )
{
	for(int nRow  =0;nRow<cBox.GetItemCount();++nRow){
		vStrings.push_back(ToString(cBox.GetItemText(nRow,nCol)));
	}
}
void ApiMFC::GetRowString( CListCtrl& cBox,int nRow,std::vector<CString>& vStrings )
{
	for(int nCol = 0 ;nCol < cBox.GetHeaderCtrl()-> GetItemCount();++nCol){
		vStrings.push_back(cBox.GetItemText(nRow,nCol));
	}
}

void ApiMFC::GetRowString( CListCtrl& cBox,int nRow,VectorString& vStrings )
{
	for(int nCol = 0 ;nCol < cBox.GetHeaderCtrl()-> GetItemCount();++nCol){
		vStrings.push_back(ApiMFC::ToString(cBox.GetItemText(nRow,nCol)));
	}
}
void ApiMFC::SetRowString( CListCtrl& cBox,int nRow,const std::vector<CString>& vValue )
{
	if (nRow<0)
		nRow = cBox.InsertItem(cBox.GetItemCount(),_T(""));
	
	for(int nCol = 0 ;nCol < cBox.GetHeaderCtrl()-> GetItemCount();++nCol){
		if (nCol >= (int)vValue.size())return;

		cBox.SetItemText(nRow,nCol,vValue[nCol]);
	}
}

void ApiMFC::SetRowString( CListCtrl& cBox,int nRow,const VectorString& vValue )
{
	if (nRow<0)
		nRow = cBox.InsertItem(cBox.GetItemCount(),_T(""));

	//赋值
	for(int nCol = 0 ;nCol < cBox.GetHeaderCtrl()-> GetItemCount();++nCol){
		if (nCol >= (int)vValue.size())return;
		cBox.SetItemText(nRow,nCol,ApiWin::ToStringT(vValue[nCol]).c_str());
	}
}

void ApiMFC::SetRowString( CListCtrl& cBox,int nRow,const MapIntString& vString )
{
	if (nRow<0)
		nRow = cBox.InsertItem(cBox.GetItemCount(),_T(""));

	MapIntString::const_iterator itr;
	foreach(itr,vString){
		cBox.SetItemText(nRow,itr->first,ApiWin::ToStringT(itr->second).c_str());
	}
}

bool ApiMFC::GetSelRows( const CListCtrl& cBox,VectorInt& vVct )
{
	POSITION   pos=cBox.GetFirstSelectedItemPosition();
	while(pos){
		int nRow=cBox.GetNextSelectedItem(pos);
		vVct.push_back(nRow);
	}
	return true;
}

bool ApiMFC::GetSelRows( const CListCtrl& cBox,SetInt& vVct )
{
	POSITION   pos=cBox.GetFirstSelectedItemPosition();
	while(pos){
		int nRow=cBox.GetNextSelectedItem(pos);
		vVct.insert(nRow);
	}

	return true;
}

bool ApiMFC::GetSelRows( const CListBox& cBox,VectorInt& vVct )
{
	//得到选中列表
	int nCount= cBox.GetSelCount(); 
	if(nCount > 0){
		CArray<int,int> aryListSel; 
		aryListSel.SetSize(nCount); 
		cBox. GetSelItems(nCount,   aryListSel.GetData()); 

		for (int nIndex =0;nIndex<aryListSel.GetSize();++nIndex)
		{
			vVct.push_back(aryListSel.GetAt(nIndex));
		}
	}

	return true;
}

bool ApiMFC::GetSelRows( const CListBox& cBox,SetInt& vVct )
{
	//得到选中列表
	int nCount= cBox.GetSelCount(); 
	if(nCount > 0){
		CArray<int,int> aryListSel; 
		aryListSel.SetSize(nCount); 
		cBox. GetSelItems(nCount,   aryListSel.GetData()); 

		for (int nIndex =0;nIndex<aryListSel.GetSize();++nIndex)
		{
			vVct.insert(aryListSel.GetAt(nIndex));
		}
	}

	return true;
}
void ApiMFC::RemoveEmptyLine( CListCtrl& cBox )
{
	for(int nRow = 0 ; nRow < cBox.GetItemCount();++nRow){
		if (ApiMFC::IsEmptyLine(cBox,nRow))
		{
			cBox.DeleteItem(nRow);
			--nRow;
		}
	}
}

void ApiMFC::DeleteItem(CListCtrl& cBox,const std::set<int>& vRow )
{
	for(std::set<int>::const_reverse_iterator itr = vRow.rbegin();itr != vRow.rend();++itr){
		cBox.DeleteItem(*itr);
	}
}

void ApiMFC::DeleteItem( CListCtrl& cBox )
{
	cBox.DeleteAllItems();
}

void ApiMFC::DeleteItem( CListCtrl& cBox,int nRow )
{
	cBox.DeleteItem(nRow);
}

void ApiMFC::DeleteItem( CListBox& cBox )
{
	cBox.ResetContent();
}

void ApiMFC::DeleteItem( CComboBox& cBox )
{
	cBox.ResetContent();
}

uint ApiMFC::DeleteItem( CListCtrl& cBox,int nCol,const std::string& sString,int nCounter /*= -1*/ )
{
	uint nReal = 0;
	for(int nRow = cBox.GetItemCount();nRow >= 0;--nRow){
		if (GetItemText(cBox,nRow,nCol) == sString){
			cBox.DeleteItem(nRow);
			++nReal;
			if (-1 != nCounter && (int)nReal > nCounter)return nReal;
		}
	}

	return nReal;
}

uint ApiMFC::DeleteItem( CComboBox& cBox,const std::string& sValue,int nCount /*= -1*/ )
{
	uint nReal = 0;	int nStartPos = 0 ;
	while( -1 == nCount || (int)nReal < nCount){
		nStartPos = cBox.FindString(nStartPos,ApiWin::ToWide(sValue).c_str());
		if (-1 == nStartPos)return nReal;

		cBox.DeleteString(nStartPos);
		++nReal;
	}

	return nReal;
}

CString ApiMFC::GetColumnText(const CListCtrl& cBox ,int nCol )
{
	char_t name[255]={0};

	LVCOLUMN item;
	item.pszText = name;
	item.cchTextMax=sizeof(name);
	item.mask = LVCF_TEXT;
	cBox.GetColumn(nCol,&item);
	return item.pszText;
}

void ApiMFC::SuitStringWidth( CListCtrl& cBox,int nCol,int nExtra /*= 15*/ )
{
	int nLength = cBox.GetStringWidth(ApiMFC::GetColumnText(cBox,nCol));
	for(int nRow = 0;nRow< cBox.GetItemCount();++nRow){
		int nCur = cBox.GetStringWidth(cBox.GetItemText(nRow,nCol));
		if (nLength < nCur)
		{
			nLength = nCur;
		}
	}
	cBox.SetColumnWidth(nCol,nLength + nExtra);
}

void ApiMFC::SuitStringWidth( CListCtrl& cBox )
{
	for(int nCol = 0;nCol<cBox.GetHeaderCtrl()->GetItemCount();++nCol){
		SuitStringWidth(cBox,nCol);
	}
}

void ApiMFC::Show( CListCtrl& cEdit,int nRow,const VectorString& vStrings )
{
	int nMin = ToolFrame::Min((int)vStrings.size(),ApiMFC::GetColumnCount(cEdit));
	for (int nIndex = 0;nIndex < nMin;++nIndex)
	{
		cEdit.SetItemText(nRow,nIndex,ApiWin::ToStringT(vStrings[nIndex]).c_str());
	}
}

int ApiMFC::GetColumnCount( CListCtrl& cBox )
{
	return cBox.GetHeaderCtrl()-> GetItemCount();
}

bool ApiMFC::SetTitle( CWnd& cDlg,const std::string& sNickName )
{
	cDlg.SetWindowText(ApiWin::ToStringT(sNickName).c_str());
	return true;
}

bool ApiMFC::SetTitle( CPropertySheet& cDlg,const std::string& sNickName,uint uStyle /*= 0*/ )
{
	cDlg.SetTitle(ApiWin::ToStringT(sNickName).c_str(),uStyle);
	return true;
}

bool ApiMFC::SetTitle(CWnd* pWnd, const std::string& sNickName)
{
	if (!pWnd)return false;
	pWnd->SetWindowText(ApiWin::ToStringT(sNickName).c_str());
	return true;
}

bool ApiMFC::EnableWindow(CWnd& wnd, BOOL bEnable)
{
	wnd.EnableWindow(bEnable);
	return true;
}

bool ApiMFC::SetFocus( CWnd& wnd )
{
	wnd.SetFocus();
	return true;
}

void ApiMFC::SetLimitText( CEdit& cWnd,UINT uMax )
{
	cWnd.SetLimitText(uMax);
}

bool ApiMFC::AddString( CComboBox& cWnd,const std::string& sString )
{
	cWnd.AddString(ApiWin::ToStringT(sString).c_str());
	return true;
}

bool ApiMFC::AddString( CListBox& cWnd,const std::string& sString )
{
	cWnd.AddString(ApiWin::ToStringT(sString).c_str());
	return true;
}

bool ApiMFC::SetChecked( CButton& cBox,BOOL bCheck)
{
	cBox.SetCheck(bCheck ? BST_CHECKED:BST_UNCHECKED);
	return true;
}

bool ApiMFC::SetChecked(CWnd* pWnd, int nID, BOOL bCheck)
{
	if (!pWnd)return false;

	pWnd = pWnd->GetDlgItem(nID);
	if (!pWnd)return false;

	((CButton*)pWnd)->SetCheck(bCheck);
	return true;
}

bool ApiMFC::IsChecked(CButton& cBox)
{
	return BST_CHECKED == cBox.GetCheck();
}

void ApiMFC::SetReport( CListCtrl& vShow )
{
	vShow.ModifyStyle(LVS_EDITLABELS,0);
	vShow.ModifyStyle(0,LVS_REPORT);
	vShow.ModifyStyle(0,LVS_SHOWSELALWAYS);
	vShow.SetExtendedStyle(LVS_EX_FLATSB  |  LVS_EX_FULLROWSELECT   |  LVS_EX_GRIDLINES);
}

bool ApiMFC::SetSel( CListCtrl& cBox,int nRow,bool bTrue )
{
	return bTrue ? SetSelected(cBox,nRow):SetNotSel(cBox,nRow);
}

int ApiMFC::InsertItem( CListCtrl& vWnd, int nRow,const std::vector<CString>& vStrings )
{
	nRow = InsertItem(vWnd,nRow);
	SetRowString(vWnd,nRow,vStrings);
	return nRow;
}

int ApiMFC::InsertItem( CListCtrl& vWnd, int nRow,const VectorString& vStrings )
{
	nRow = InsertItem(vWnd,nRow);
	SetRowString(vWnd,nRow,vStrings);
	return nRow;
}

int ApiMFC::InsertItem( CListCtrl& vWnd, int nRow )
{
	nRow = nRow >0 ? nRow:vWnd.GetItemCount();

	vWnd.InsertItem(nRow,_T(""));
	return nRow;
}

void ApiMFC::CopySels(CListCtrl& wSrc,CListCtrl& wDes,int nRow /*= -1*/ )
{
	std::set<int> vSel;
	ApiMFC::GetSelRows(wSrc,vSel);

	std::set<int>::const_iterator itr;
	foreach(itr,vSel){
		std::vector<CString> vStrings;
		ApiMFC::GetRowString(wSrc,*itr,vStrings);
		ApiMFC::InsertItem(wDes,nRow,vStrings);
	}
}

void ApiMFC::DeleteSelRows( CListCtrl& cBox )
{
	std::set<int> vSel;
	ApiMFC::GetSelRows(cBox,vSel);
	ApiMFC::DeleteItem(cBox,vSel);
}

std::string ApiMFC::GetItemText(const CListCtrl& vWnd,int nItem,int nSubItem )
{
	return ApiMFC::ToString(vWnd.GetItemText(nItem,nSubItem));
}

std::string ApiMFC::GetClipboardText( const CWnd* pWnd )
{
	if (!::OpenClipboard(pWnd->GetSafeHwnd()))return "";

	HANDLE hClipMemory=::GetClipboardData(CF_TEXT);
	std::string sText = (char*)::GlobalLock(hClipMemory);
	::GlobalUnlock(hClipMemory);
	::CloseClipboard();

	return sText;
}

bool ApiMFC::SetClipboardText(const CWnd* pWnd,const std::string& sText )
{
	if (sText.empty())return false;
	if(!::OpenClipboard(pWnd->GetSafeHwnd()))return false;

	CString sSource(sText.c_str());
	::EmptyClipboard(); 
	HGLOBAL clipbuffer = ::GlobalAlloc(GMEM_DDESHARE, sSource.GetLength()+1); 
	char_t * buffer       = (char_t*)::GlobalLock(clipbuffer);
	lstrcpy(buffer, sSource.GetString());
	::GlobalUnlock(clipbuffer); 
	::SetClipboardData(CF_TEXT,clipbuffer); 
	::CloseClipboard(); 

	return true;
}

bool ApiMFC::IsKeyComb( UINT nArg,UINT nChar,int nVKCtl1/*=0*/,int nVKCtl2/*=0*/,int nVKCtl3/*=0*/ )
{
	bool bTrue = nChar == nArg;
	if (bTrue && nVKCtl1) bTrue &= GetKeyState(nVKCtl1) < 0;
	if (bTrue && nVKCtl2) bTrue &= GetKeyState(nVKCtl2) < 0;
	if (bTrue && nVKCtl3) bTrue &= GetKeyState(nVKCtl3) < 0;

	return bTrue;
}

void ApiMFC::InsertString( CEdit& cWnd,const std::string& sString )
{
	int nStartChar=0,nEndChar=0;
	cWnd.GetSel(nStartChar,nEndChar);

	ApiMFC::SetWindowText(cWnd,GetInsertString(cWnd,sString));

	cWnd.SetSel(nStartChar,nEndChar);
}

void ApiMFC::InsertString( CComboBox& cWnd,int nIndex,const std::string& sString )
{
	cWnd.InsertString(nIndex,ApiMFC::ToCString(sString));
}

std::string ApiMFC::GetInsertString( CEdit& cWnd,const std::string& sString )
{
	int nStartChar=0,nEndChar=0;
	cWnd.GetSel(nStartChar,nEndChar);

	const std::string sBuff = ApiMFC::GetWindowText(cWnd);

	std::stringstream sStream;
	sStream<<sBuff.substr(0,nStartChar);
	sStream<<sString;
	sStream<<sBuff.substr(nEndChar);

	return sStream.str();
}

int ApiMFC::GetRowCount( CListCtrl& cBox )
{
	return cBox.GetItemCount();
}

void ApiMFC::GetFilePath( const CFileDialog& dlg,VectorString& vPath )
{
	POSITION   pos   =  dlg.GetStartPosition();
	while (pos)
		vPath.push_back( ApiMFC::ToString(dlg.GetNextPathName(pos)));
}

std::string ApiMFC::GetFilePath( const CFileDialog& dlg )
{
	return ApiMFC::ToString(dlg.GetPathName());
}

void ApiMFC::SetItemText( CListCtrl& vWnd,int nItem,int nSubItem,const std::string& tVaue )
{
	vWnd.SetItemText(nItem,nSubItem,ApiWin::ToStringT(tVaue).c_str());
}

bool ApiMFC::SetWindowText( CWnd& wnd,const std::string& tValue )
{
	//整理所有的\n 变成 \r\n
	std::string s = tValue;
	ToolFrame::Replace(s,"\r\n","\n");
	ToolFrame::Replace(s, "\n", "\r\n");
	wnd.SetWindowText(ApiWin::ToStringT(s).c_str());
	return true;
}

std::string ApiMFC::GetDlgFolderSel( const std::string& sTitle,int nSpecDir /*= CSIDL_DESKTOP*/ )
{
	// 获取特定文件夹的LPITEMIDLIST，可以将之理解为HANDLE
	// 所谓的特定文件夹,你可以用CSIDL_XXX来检索之。
	LPITEMIDLIST rootLoation;
	SHGetSpecialFolderLocation( nullptr, nSpecDir, &rootLoation );
	if ( rootLoation == nullptr ) {
		return "";
	}
	// 配置对话框
	BROWSEINFO bi;
	ZeroMemory( &bi, sizeof( bi ) );
	bi.pidlRoot = rootLoation; // 文件夹对话框之根目录，不指定的话则为我的电脑
	bi.lpszTitle = ApiWin::ToStringT(sTitle).c_str(); // 可以不指定
	// bi.ulFlags = BIF_EDITBOX | BIF_RETURNONLYFSDIRS;

	// 打开对话框, 有点像DoModal
	LPITEMIDLIST targetLocation = SHBrowseForFolder( &bi );
	if ( targetLocation == nullptr )return "";
	
	
	TCHAR targetPath[ MAX_PATH ]={0};
	SHGetPathFromIDList( targetLocation, targetPath );
	return ApiWin::ToMulti(targetPath);
}

std::string ApiMFC::GetDlgFileSel( bool bOpen )
{
	CFileDialog dlg(TRUE,nullptr,nullptr,0,nullptr);
	if(IDOK == dlg.DoModal()){
		return ApiMFC::ToString( dlg.GetPathName());
	}

	return "";
}

int ApiMFC::ApiMessageBox( const std::string& sMsg,const std::string& sTitle,uint uType )
{
	return ApiMessageBox(nullptr,sMsg,sTitle,uType);
}

int ApiMFC::ApiMessageBox(CWnd* wnd,const std::string& sMsg,const std::string& sTitle,uint uType )
{
	HWND hWnd = NULL;
	if (wnd)
		hWnd = wnd->m_hWnd;

	return MessageBox(hWnd,ApiWin::ToStringT(sMsg).c_str(),ApiWin::ToStringT(sTitle).c_str(),uType);
}

int ApiMFC::ApiWarningBox( CWnd* wnd,const std::string& sMsg,const std::string& sTitle,uint uType /*= MB_ICONWARNING|MB_OK*/ )
{
	return ApiMessageBox(wnd,sMsg,sTitle,uType);
}

int ApiMFC::ApiWarningBox( const std::string& sMsg,const std::string& sTitle,uint uType /*= MB_ICONWARNING|MB_OK*/ )
{
	return ApiMessageBox(nullptr,sMsg,sTitle,uType);
}

std::string ApiMFC::GetWindowText( const CWnd& wnd )
{
	CString csBuff;
	wnd.GetWindowText(csBuff);
	return ToString(csBuff);
}

bool ApiMFC::SetOleDateTime( COleDateTime& oleDateTime,const time_t tTime )
{
	tm t;
	localtime_s(&t,&tTime);
	return !!oleDateTime.SetDateTime(1900 + t.tm_year,1+t.tm_mon,t.tm_mday,t.tm_hour,t.tm_min,t.tm_sec);
}

double ApiMFC::SetOleDateTime( const time_t tTime )
{
	COleDateTime oleDateTime;
	SetOleDateTime(oleDateTime,tTime);
	return oleDateTime;
}

double ApiMFC::SetOleDateTime( const ToolFrame::CDateTime& date )
{
	return SetOleDateTime(date.GetTime());
}

double ApiMFC::SetOleDateTime( const ToolFrame::CDate& date )
{
	return SetOleDateTime(date.GetTime());
}

bool ApiMFC::IsWindowEnabled( const CWnd& wnd )
{
	return TRUE == wnd.IsWindowEnabled();
}

#endif //MACRO_LIB_MFC
