// DlgDebug.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgDebug.h"
#include "afxdialogex.h"
#include "Resource.h"

#include "ApiMFC.h"
#include "DlgServers.h"


// CDlgDebug 对话框

IMPLEMENT_DYNAMIC(CDlgDebug, CDialogEx)

CDlgDebug::CDlgDebug(CWnd* pParent /*=NULL*/)
	: CDialogEx(DLG_DEBUG, pParent)
{

}

CDlgDebug::~CDlgDebug()
{
}

void CDlgDebug::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, EDT_DEBUG_INFO, _cEdtInfo);
	DDX_Control(pDX, CHK_DEBUG_MEMORY, _cChxMemory);
	DDX_Control(pDX, CHK_DEBUG_CALLSTACK, _cChxCallStack);
	DDX_Control(pDX, CHK_DEBUG_DEBUGPOINT, _cChxDebugPoint);
	DDX_Control(pDX, CHK_DEBUG_DEBUGELAPSED, _cChxElapsed);
	DDX_Control(pDX, CHK_DEBUG_DEBUGTIME_CHAIN, _cChkTimeChain);
}


BEGIN_MESSAGE_MAP(CDlgDebug, CDialogEx)
	ON_BN_CLICKED(BTN_DEBUG_GATHER, &CDlgDebug::OnBnClickedDebugGather)
	ON_BN_CLICKED(BTN_DEBUG_REFLASH, &CDlgDebug::OnBnClickedDebugReflash)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgDebug 消息处理程序
BOOL CDlgDebug::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ApiMFC::SetChecked(_cChxMemory,		TRUE);
	ApiMFC::SetChecked(_cChxCallStack,	TRUE);
	ApiMFC::SetChecked(_cChxDebugPoint,	TRUE);
	ApiMFC::SetChecked(_cChxElapsed,	TRUE);
	ApiMFC::SetChecked(_cChkTimeChain,	TRUE);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDlgDebug::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();

	CDlgServers* pDlg = dynamic_cast<CDlgServers*>(GetParent());
	ASSERT_LOG_ERROR(pDlg);

	pDlg->OnDebugWndClosed();
}

void CDlgDebug::OnBnClickedDebugGather()
{
	CDlgServers* pDlg = dynamic_cast<CDlgServers*>(GetParent());
	ASSERT_LOG_ERROR(pDlg);

	VectorString vDebug;
	if (ApiMFC::IsChecked(_cChxMemory))
	{
		vDebug.push_back("Memory");
	}
	if (ApiMFC::IsChecked(_cChxCallStack))
	{
		vDebug.push_back("CallStack");
	}
	if (ApiMFC::IsChecked(_cChxDebugPoint))
	{
		vDebug.push_back("DebugPoint");
	}
	if (ApiMFC::IsChecked(_cChxElapsed))
	{
		vDebug.push_back("DebugElapsed");
	}
	if (ApiMFC::IsChecked(_cChkTimeChain))
	{
		vDebug.push_back("DebugTimeChain");
	}

	VectorUint vServerID;
	pDlg->GetTopologyControl().FindOnlineServerList(vServerID);
	VectorUint::const_iterator itr;
	foreach(itr, vServerID) {
		pDlg->GetTopologyControl().SendLogicDebug(*itr, vDebug);
	}
}

void CDlgDebug::OnBnClickedDebugReflash()
{
	CDlgServers* pDlg = dynamic_cast<CDlgServers*>(GetParent());
	ASSERT_LOG_ERROR(pDlg);

	ApiMFC::SetWindowText(_cEdtInfo, pDlg->GetTopologyControl().GetDebugString());
}

