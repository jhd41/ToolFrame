#include "MfcClass.h"

#ifdef MACRO_LIB_MFC

NS_TOOL_FRAME_BEGIN

//////////////////////////////////////////////////////////////////////////
void CPropertySheetNoBorder::PreSubclassWindow()
{
	//最小化按钮
	ModifyStyle(0, WS_MINIMIZEBOX);//WS_MAXIMIZEBOX
	ModifyStyleEx( 0, WS_EX_APPWINDOW ); 

	__super::PreSubclassWindow();
}

BOOL CPropertySheetNoBorder::OnInitDialog()
{
	CPropertySheet::OnInitDialog();

	//最小化按钮
	//ModifyStyle(0, WS_MINIMIZEBOX);//WS_MAXIMIZEBOX

	//隐藏4个按钮
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE); 
	GetDlgItem(IDHELP)->ShowWindow(SW_HIDE); 
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	GetDlgItem(ID_APPLY_NOW)->ShowWindow(SW_HIDE);

	//获取窗体尺寸
	CRect btnRect;
	GetDlgItem(IDCANCEL)->GetWindowRect(&btnRect);
	CRect wdnRect;
	GetWindowRect(&wdnRect); 
	//调整窗体大小
	::SetWindowPos(this->m_hWnd, HWND_TOP, 0,0,wdnRect.Width(),wdnRect.Height() - btnRect.Height(), SWP_NOMOVE | SWP_NOZORDER);
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////

NS_TOOL_FRAME_END

#endif // MACRO_LIB_MFC
