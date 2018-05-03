#include "ListCtrlEdit.h"

#ifdef MACRO_LIB_MFC

#include "ToolStd.h"
#include "MLoger.h"
#include "ApiMFC.h"
#include "ApiWin.h"
#include "DateTime.h"
#include "Date.h"

NS_TOOL_FRAME_BEGIN

//////////////////////////////////////////////////////////////////////////
IEditing::IEditing()
{
	_pcLcEdt = nullptr;
}

IEditing::~IEditing()
{

}

void IEditing::SetParentListCtrl( CListCtrlEdit* pLc )
{
	_pcLcEdt=pLc;
}

CListCtrlEdit* IEditing::GetParentListCtrl()
{
	return _pcLcEdt;
}

void IEditing::OnPrepair()
{

}

void IEditing::OnSetFocus( int nRow,int nCol,const CString& csString )
{
	_nRow = nRow;
	_nCol = nCol;
}

void IEditing::OnKillFocus( CString& csString )
{

}

int IEditing::GetEditRow() const
{
	return _nRow;
}

int IEditing::GetEditCol() const
{
	return _nCol;
}

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CListEdit, CEdit)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

void CListEdit::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{	
	if (ApiMFC::IsKeyComb(nChar,VK_RETURN))
	{
		std::string sText = ApiMFC::GetInsertString(*this,"\r\n");
		SuitStringShow(sText);
		ApiMFC::SetWindowText(*this,sText);
	}
	if (ApiMFC::IsKeyComb(nChar,'V',VK_CONTROL))
	{
		std::string sMem = ApiMFC::GetClipboardText(this);
		sMem = ApiMFC::GetInsertString(*this,sMem);
		SuitStringShow(sMem);
	}
	__super::OnKeyDown(nChar,nRepCnt,nFlags);
}
void CListEdit::SetUnitRect(){
	GetWindowRect(&rUnit);   
	GetParentListCtrl()->ScreenToClient(&rUnit);
}
void CListEdit::SuitStringShow(const std::string& sText ){
	//计算行数的个数
	int nRow = ToolFrame::GetSubNum(sText,"\r\n") + 1;

	//修正屏幕长度
	CRect rWindow = rUnit;
	rWindow.bottom = rUnit.top+ rUnit.Height()*nRow;

	MoveWindow(&rWindow);

	//ApiMFC::SetWindowText(*this,sText);
}
void CListEdit::OnPrepair(){
	ModifyStyle(0,ES_MULTILINE|ES_WANTRETURN);
}

void CListEdit::OnSetFocus( int nRow,int nCol,const CString& csString )
{
	IEditing::OnSetFocus(nRow,nCol,csString);

	SetUnitRect();

	//整理每个回车
	std::string sText = ApiMFC::ToString(csString);
	ToolFrame::Replace(sText,"\r\n",	"\n");
	ToolFrame::Replace(sText,"\n",		"\r\n");

	SuitStringShow(sText);
	ApiMFC::SetWindowText(*this,sText);
}

void CListEdit::OnKillFocus( CString& csString )
{
	GetWindowText(csString);
}

void CListCmb::OnSetFocus( int nRow,int nCol,const CString& csString )
{
	IEditing::OnSetFocus(nRow,nCol,csString);

	ApiMFC::SetSelected(*this,csString,true);
}

void CListCmb::OnKillFocus( CString& csString )
{
	GetWindowText(csString);
}
CListCtrlEdit::CListCtrlEdit(void)
{
	_iEditing = nullptr;
	_bDragging = FALSE;
	_bSuitWidth = FALSE;
	_bExtraLine	= FALSE;

	_bAsc = TRUE;
	_nSortedCol = -1;
	_fnCompare = nullptr;

	SetCompareFun(SORT_BOOL,			CompareBool);
	SetCompareFun(SORT_NUMBER,			CompareNumber);
	SetCompareFun(SORT_NUMBER_N,		CompareNumberN);
	SetCompareFun(SORT_STRING,			CompareString);
	SetCompareFun(SORT_DATETIME,		CompareDateTime);
	SetCompareFun(SORT_DATE,			CompareDate);
	SetCompareFun(SORT_TIME,			CompareTime);

	SetCompareFun(SORT_NUMBER_READ_3,	CompareNumberRead3);
	SetCompareFun(SORT_NUMBER_READ_4,	CompareNumberRead4);
}

CListCtrlEdit::~CListCtrlEdit(void)
{
}
BEGIN_MESSAGE_MAP(CListCtrlEdit, CListCtrl)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SETFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG,OnLvnBeginrdrag)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnLvnColumnclickList)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomdraw)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CListCtrlEdit::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(LVS_EDITLABELS,0);
	ModifyStyle(0,LVS_REPORT);
	ModifyStyle(0,LVS_SHOWSELALWAYS);
	SetExtendedStyle(LVS_EX_FLATSB  |  LVS_EX_FULLROWSELECT   |  LVS_EX_GRIDLINES);

	ExtraLineAdd();

	__super::PreSubclassWindow();
}

void CListCtrlEdit::OnLButtonDblClk( UINT nFlags, CPoint point )
{

	// TODO: Add your message handler code here and/or call default
	__super::OnLButtonDblClk(nFlags, point);
	LVHITTESTINFO info;
	info.pt=point;
	info.flags=LVHT_ONITEMLABEL;
	if(SubItemHitTest(&info)>=0)     //SubItemHitTest进行点击测试，目的是确定双击的单元格是第几行第几列。
	{
		_ptItem.y = info.iItem;		//行索引
		_ptItem.x = info.iSubItem;	//列索引

		CRect rect;
		GetSubItemRect(_ptItem.y,_ptItem.x,LVIR_LABEL,rect);    //得到该单元格矩形的位置大小信息。

		if (ToolFrame::IsVaildIndex(_vInfo,_ptItem.x))
		{
			XEditingInfo& info = _vInfo[_ptItem.x];
			SetEditing(info.iEditing);

			//设置窗口
			CWnd* pWnd = dynamic_cast<CWnd*>(info.iEditing);
			if (pWnd)
			{
				//调整窗口
				if (info.bOriginal){
					CRect rctEditing;
					pWnd->GetWindowRect(rctEditing);

					CPoint ptButton = rect.TopLeft();
					ptButton.Offset(rctEditing.Size());

					rect.SetRect(rect.TopLeft(),ptButton);
				}
				pWnd->MoveWindow(rect);

				//设置数据
				info.iEditing->OnSetFocus(_ptItem.y,_ptItem.x,GetItemText(_ptItem.y,_ptItem.x));

				pWnd->SetFont(this->GetFont());
				pWnd->SetFocus();
				pWnd->ShowWindow(SW_SHOW);
			}
		}

		UpdateWindow();
	}
}
void CListCtrlEdit::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if (ApiMFC::IsKeyComb(nChar,'A',VK_CONTROL)){
		ApiMFC::SetSelected(*this);
	}
	if (ApiMFC::IsKeyComb(nChar,VK_DELETE))
	{
		std::set<int> vDelete;
		ApiMFC::GetSelRows(*this,vDelete);
		ApiMFC::DeleteItem(*this,vDelete);

		//检查添加额外行
		ExtraLineAdd();
	}
	if (ApiMFC::IsKeyComb(nChar,'C',VK_CONTROL))
	{
		CopyToMem();
	}
	if (ApiMFC::IsKeyComb(nChar,'V',VK_CONTROL))
	{
		int nRowInsert=0;
		//先记录起点 并删除 已选中的行，然后插入
		std::set<int> vSelect;
		ApiMFC::GetSelRows(*this,vSelect);
		if (!vSelect.empty())nRowInsert = *(vSelect.begin());
		ApiMFC::DeleteItem(*this,vSelect);

		//填入
		MapCopy::reverse_iterator itrCopyR;
		foreachR(itrCopyR,_vCopy){
			int nRowNew = this->InsertItem(nRowInsert,_T(""));
			ApiMFC::SetRowString(*this,nRowNew,itrCopyR->second);

			ApiMFC::SetSelected(*this,nRowNew);
		}

		//检查添加额外行
		ExtraLineAdd();
	}

	__super::OnKeyDown(nChar,nRepCnt,nFlags);
}
void CListCtrlEdit::DisposeEdit(IEditing* iEditing)
{
	//更新并隐藏界面
	CWnd* pWnd = dynamic_cast<CWnd*>(iEditing);
	if (pWnd)
	{
		CString csText;
		iEditing->OnKillFocus(csText);
		this->SetItemText(_ptItem.y,_ptItem.x,csText);
		pWnd->ShowWindow(SW_HIDE);
		if(GetItemCount() == _ptItem.y+1)     //如果编辑的这行是最后一行的话，就添加一行，在这里可以设置更多的判断。
			InsertItem(_ptItem.y+1,0);

		if (IsSuitWidth())ApiMFC::SuitStringWidth(*this,_ptItem.x);
	}
	SetEditing(nullptr);
	return ;
}

void CListCtrlEdit::SetCompareFun( int nType,FnCompare pfn )
{
	_vComparePtr[nType] = pfn ;
}

BOOL CListCtrlEdit::DeleteItem(int nItem){
	BOOL bResault = CListCtrl::DeleteItem(nItem);
	ExtraLineAdd();
	return bResault;
}
BOOL CListCtrlEdit::DeleteAllItems(){
	BOOL bResault = CListCtrl::DeleteAllItems();
	ExtraLineAdd();
	return bResault;
}

BOOL CListCtrlEdit::SetExtraLine( BOOL bExtra /*= true*/ )
{
	_bExtraLine = bExtra;
	return TRUE;
}

BOOL CListCtrlEdit::ExtraLineAdd()
{
	if (!_bExtraLine)return FALSE;

	if (this->GetItemCount() <= 0 )
	{
		this->InsertItem(0,_T(""));
		return TRUE;
	}

	if (ApiMFC::IsEmptyLine(*this,this->GetItemCount()-1))return FALSE;

	this->InsertItem(this->GetItemCount(),_T(""));
	return TRUE;
}
BOOL CListCtrlEdit::ExtraLineRemove(){
	if (this->GetItemCount() <= 0)return FALSE;
	if (!ApiMFC::IsEmptyLine(*this,this->GetItemCount()-1))return FALSE;
	
	CListCtrl::DeleteItem(this->GetItemCount()-1);
	return TRUE;
}
void CListCtrlEdit::OnLvnBeginrdrag(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

	*pResult = 0;

	_bDragging = TRUE;
}

void CListCtrlEdit::OnLButtonUp(UINT nFlags, CPoint point){
	if (_bDragging)
	{
		ExtraLineRemove();

		LVHITTESTINFO info;
		info.pt=point;
		info.flags=LVHT_ONITEMLABEL;
		if(SubItemHitTest(&info)>=0)     //SubItemHitTest进行点击测试，目的是确定双击的单元格是第几行第几列。
		{
			std::set<int> vSelect;
			ApiMFC::GetSelRows(*this,vSelect);
			if(!vSelect.empty()){
				const int nRowDes = info.iItem;
				const int nRowSrc = *vSelect.begin();

				CopyToMem();
				ApiMFC::DeleteItem(*this,vSelect);

				int nCount = ToolFrame::GetLessCount(vSelect,nRowDes);
				int nInsertPos = nRowDes >= nRowSrc ? nRowDes - nCount + 1 : nRowDes - nCount ;
				for(MapCopy::reverse_iterator itrCopyR = _vCopy.rbegin();itrCopyR != _vCopy.rend();++itrCopyR){
					int nRowNew = this->InsertItem(nInsertPos,_T(""));
					ApiMFC::SetRowString(*this,nRowNew,itrCopyR->second);
					ApiMFC::SetSelected(*this,nRowNew);
				}
			}
		}
		_bDragging = FALSE;
		ExtraLineAdd();
	}
	__super::OnLButtonUp(nFlags, point);
}

void CListCtrlEdit::OnLvnColumnclickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if( pNMListView->iSubItem == _nSortedCol )     //如果被点击的列和上一次点击的列是同一列的话
		_bAsc = !_bAsc;                             //排序方式取反，即上次是升序这次就为降序，上次降序这次就为升序
	else                                                   //如果被点击的列和上一次点击的列不是同一列的话
	{
		_bAsc = TRUE;                               //排序方式为升序
		_nSortedCol = pNMListView->iSubItem;        //把这次点击的列序号保存到m_nSortedCol 变量中
	}

	if (ToolFrame::IsVaildIndex(_vInfo,_nSortedCol))
	{
		int nSortType = _vInfo[_nSortedCol].nSortType;
		MapComparePtr::iterator itrCompare = _vComparePtr.find(nSortType);
		if (itrCompare != _vComparePtr.end())
		{
			_fnCompare = itrCompare->second;

			for (int index=0;index<GetItemCount();index++)
				SetItemData(index,index); //SetItemData函数的作用是为一行设置一个标签，以后通过该标签就能找回这一行，标签是一个数值。SetItemData(index,index)意思就是这一行是第几列就把标签设为几。为什么要设置标签呢？以后的排序必须用到标签。

			ExtraLineRemove();
			SortItems( CListCtrlEdit::ListCompare, (DWORD)this );    
			//SortItems函数进行排序操作，ListCompare是回调函数，SortItems函数会调用此回调函数进行排序判断
			ExtraLineAdd();
		}
	}

	*pResult = 0;
}

int CALLBACK CListCtrlEdit::ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrlEdit* pV=(CListCtrlEdit*)lParamSort;
	if (pV && pV->_fnCompare)
	{
		std::string sSrc = ApiMFC::ToString(pV->GetItemText(lParam1,pV->_nSortedCol));
		std::string sDes = ApiMFC::ToString(pV->GetItemText(lParam2,pV->_nSortedCol));
		int nResault = (pV->_fnCompare)(sSrc,sDes) ? 1:-1 ;
		return pV->_bAsc ? nResault : nResault * -1;
	}

	return 0;
}

void CListCtrlEdit::CopyToMem()
{
	_vCopy.clear();
	POSITION   pos=this->GetFirstSelectedItemPosition();
	while(pos){
		int nRow=this->GetNextSelectedItem(pos);
		std::vector<CString> vString;
		for(int nCol = 0 ;nCol < GetHeaderCtrl()-> GetItemCount();++nCol){
			vString.push_back(GetItemText(nRow,nCol));
		}
		_vCopy.insert(std::make_pair(nRow,vString));
	}
}

bool ToolFrame::CListCtrlEdit::CompareBool(const std::string& sSrc, const std::string& sDes)
{
	bool bSrc = false, bDes = false;
	ASSERT_LOG_ERROR(ToolFrame::ToValue(sSrc, bSrc));
	ASSERT_LOG_ERROR(ToolFrame::ToValue(sDes, bDes));

	return bSrc < bDes;
}

bool CListCtrlEdit::CompareNumber( const std::string& sSrc, const std::string& sDes )
{
	INT64 nSrc = 0, nDes = 0;
	ASSERT_LOG_ERROR(ToolFrame::ToValue(sSrc,nSrc));
	ASSERT_LOG_ERROR(ToolFrame::ToValue(sDes,nDes));

	return nSrc < nDes;
}

bool CListCtrlEdit::CompareNumberN( const std::string& sSrc, const std::string& sDes )
{
	UINT64 nSrc = 0, nDes = 0;
	ASSERT_LOG_ERROR(ToolFrame::ToValue(sSrc,nSrc));
	ASSERT_LOG_ERROR(ToolFrame::ToValue(sDes,nDes));

	return nSrc < nDes;
}

bool CListCtrlEdit::CompareNumberRead3( const std::string& sSrc, const std::string& sDes )
{
	return ToolFrame::ReadToValue(sSrc,3) < ToolFrame::ReadToValue(sDes,3);
}

bool CListCtrlEdit::CompareNumberRead4( const std::string& sSrc, const std::string& sDes )
{
	return ToolFrame::ReadToValue(sSrc,4) < ToolFrame::ReadToValue(sDes,4);
}

bool CListCtrlEdit::CompareDateTime( const std::string& sSrc, const std::string& sDes )
{
	CDateTime d1(sSrc);
	CDateTime d2(sDes);
	return d1 < d2;
}

bool CListCtrlEdit::CompareDate( const std::string& sSrc, const std::string& sDes )
{
	CDate d1(sSrc);
	CDate d2(sDes);
	return d1 < d2;
}

bool CListCtrlEdit::CompareTime(const std::string& sSrc, const std::string& sDes)
{
	return ToolFrame::ReadToTime(sSrc) < ToolFrame::ReadToTime(sDes);
}

bool CListCtrlEdit::CompareString( const std::string& sSrc, const std::string& sDes )
{
	return sSrc < sDes;
}

void CListCtrlEdit::OnSetFocus( CWnd* pOldWnd )
{
	CListCtrl::OnSetFocus(pOldWnd);
	IEditing* iEditing = GetEditing();
	if (iEditing)DisposeEdit(iEditing);
}

void CListCtrlEdit::Init()
{
	ApiMFC::DeleteAllColumns(*this);
	for(size_t uIndex = 0;uIndex<_vInfo.size();++uIndex){
		XEditingInfo& info = _vInfo[uIndex];
		InsertColumn(uIndex,ApiWin::ToStringT(info.sTitle).c_str());

		if (info.iEditing)info.iEditing->OnPrepair();
	}
	ApiMFC::SuitStringWidth(*this);
}

CListCmb* CListCtrlEdit::CreateCtlComboBox(uint uControlID)
{
	CListCmb* p = new  CListCmb();
	if (!p)return nullptr;

	RECT r;
	p->Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST, r, this, uControlID);
	return p;
}

CListEdit* CListCtrlEdit::CreateCtlEdit(uint uControlID)
{
	CListEdit* p = new  CListEdit();
	if (!p)return nullptr;

	RECT r;
	Create(WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_CENTER, r, this, uControlID);
	return p;
}

bool CListCtrlEdit::DestoryCtl(IEditing* pControl)
{
	if (!pControl)return true;
	delete pControl;
	return true;
}

void CListCtrlEdit::SetTitle(int nCol, const std::string& sTitle, int nSortType, IEditing* iEditing, BOOL bOriginal /*= FALSE*/, BOOL bParent /*= TRUE*/)
{
	ToolFrame::PushSameValue(_vInfo,XEditingInfo(),nCol + 1 - _vInfo.size());

	XEditingInfo& info	= _vInfo[nCol];
	info.sTitle			= sTitle;
	info.nSortType		= nSortType;
	info.iEditing		= iEditing;
	info.bOriginal		= bOriginal;

	//设置窗口
	CWnd* pWnd = dynamic_cast<CWnd*>(iEditing);
	if (pWnd)
	{
		pWnd->ShowWindow(SW_HIDE);
		if (bParent)pWnd->SetParent(this);
	}

	if (iEditing)
	{
		iEditing->SetParentListCtrl(this);
	}
}

int CListCtrlEdit::GetEditRow() const
{
	return _ptItem.y;
}

int CListCtrlEdit::GetEditCol() const
{
	return _ptItem.x;
}

void CListCtrlEdit::OnCustomdraw( NMHDR* pNMHDR, LRESULT* pResult )
{
 	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );     // Take the default processing unless we set this to something else below.
 	*pResult = 0;     // First thing - check the draw stage. If it's the control's prepaint
 	// stage, then tell Windows we want messages for every item.
 	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
 	{
 		*pResult = CDRF_NOTIFYITEMDRAW;
 	}
 	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
 	{
		COLORREF* clrText = ToolFrame::GetValuePtrByKey(_vColorRowText,pLVCD->nmcd.dwItemSpec);
		if (clrText)
			pLVCD->clrText = *clrText;

		COLORREF* clrTextBk = ToolFrame::GetValuePtrByKey(_vColorRowTextBg,pLVCD->nmcd.dwItemSpec);
		if (clrText)
			pLVCD->clrTextBk = *clrTextBk;

 		*pResult = CDRF_DODEFAULT;
 	}
}

bool CListCtrlEdit::SetRowTextColor( int nRow,COLORREF clr )
{
	_vColorRowText[nRow] = clr;
	return true;
}

bool CListCtrlEdit::SetRowTextBgColor( int nRow,COLORREF clr )
{
	_vColorRowTextBg[nRow] = clr;
	return true;
}

void CListCtrlEdit::OnPaint()
{
	//使用双缓冲的方法绘制背景
	CPaintDC dc(this); // device context for painting
	CRect rect;
	CRect headerRect;
	CDC MenDC;		//内存DC   
	CBitmap MemMap;

	GetClientRect(&rect);    
	GetDlgItem(0)->GetWindowRect(&headerRect);   
	MenDC.CreateCompatibleDC(&dc);   
	MemMap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height()); 
	MenDC.SelectObject(&MemMap);
	MenDC.FillSolidRect(&rect,RGB(255,255,255));   

	//调用默认的OnPaint(),把图形画在内存DC表上   
	DefWindowProc(WM_PAINT,(WPARAM)MenDC.m_hDC,(LPARAM)0);   

	//输出到显示设备
	dc.BitBlt(0,
		headerRect.Height(),   
		rect.Width(),   
		rect.Height(),   
		&MenDC,   
		0,     
		headerRect.Height(),   
		SRCCOPY);   
	MenDC.DeleteDC();
	MemMap.DeleteObject();
}

BOOL CListCtrlEdit::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CListCtrl::OnEraseBkgnd(pDC);
	return FALSE;
}

NS_TOOL_FRAME_END

#endif // MACRO_LIB_MFC
