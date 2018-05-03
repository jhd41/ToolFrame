#pragma once
#include "afxwin.h"
#include "Resource.h"


// CDlgDebug �Ի���

class CDlgDebug : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDebug)

public:
	CDlgDebug(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDebug();

// �Ի�������
//#ifdef AFX_DESIGN_TIME
	enum { IDD = DLG_DEBUG };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
private:
	CEdit _cEdtInfo;
public:
	afx_msg void OnBnClickedDebugGather();
	afx_msg void OnBnClickedDebugReflash();
	CButton _cChxMemory;
	CButton _cChxCallStack;
	CButton _cChxDebugPoint;
	CButton _cChxElapsed;
	CButton _cChkTimeChain;
};
