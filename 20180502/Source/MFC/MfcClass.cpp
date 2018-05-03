#include "MfcClass.h"

#ifdef MACRO_LIB_MFC

NS_TOOL_FRAME_BEGIN

//////////////////////////////////////////////////////////////////////////
void CPropertySheetNoBorder::PreSubclassWindow()
{
	//��С����ť
	ModifyStyle(0, WS_MINIMIZEBOX);//WS_MAXIMIZEBOX
	ModifyStyleEx( 0, WS_EX_APPWINDOW ); 

	__super::PreSubclassWindow();
}

BOOL CPropertySheetNoBorder::OnInitDialog()
{
	CPropertySheet::OnInitDialog();

	//��С����ť
	//ModifyStyle(0, WS_MINIMIZEBOX);//WS_MAXIMIZEBOX

	//����4����ť
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE); 
	GetDlgItem(IDHELP)->ShowWindow(SW_HIDE); 
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	GetDlgItem(ID_APPLY_NOW)->ShowWindow(SW_HIDE);

	//��ȡ����ߴ�
	CRect btnRect;
	GetDlgItem(IDCANCEL)->GetWindowRect(&btnRect);
	CRect wdnRect;
	GetWindowRect(&wdnRect); 
	//���������С
	::SetWindowPos(this->m_hWnd, HWND_TOP, 0,0,wdnRect.Width(),wdnRect.Height() - btnRect.Height(), SWP_NOMOVE | SWP_NOZORDER);
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////

NS_TOOL_FRAME_END

#endif // MACRO_LIB_MFC
