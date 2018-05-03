#pragma once
#include "Macro.h"
#include "ListCtrlEdit.h"
#include "resource.h"		// 主符号

// CDlgServerTotal 对话框

class CDlgServerTotal : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgServerTotal)

public:
	CDlgServerTotal(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgServerTotal();

// 对话框数据
//#ifdef AFX_DESIGN_TIME
	enum { IDD = DLG_TOTAL_VIEW };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	enum ELogicTotalCol
	{
		COL_LOGIC_TOTAL_INVAILD = -1,

		COL_LOGIC_TOTAL_TYPE,

		COL_LOGIC_TOTAL_CACHE_VAILD,
		COL_LOGIC_TOTAL_CACHE_CACHE,
		COL_LOGIC_TOTAL_CACHE_TOTAL,
		COL_LOGIC_TOTAL_PRCOESSER_COUNT,
		COL_LOGIC_TOTAL_QUEUE_PROCESS,
		COL_LOGIC_TOTAL_FREE_TIME,
		COL_LOGIC_TOTAL_CPU_USE_TIME,
		COL_LOGIC_TOTAL_CPU_USAGE,
		COL_LOGIC_TOTAL_MEM_USED,
		COL_LOGIC_TOTAL_THREADS,

		COL_LOGIC_TOTAL_SEND_BYTES,
		COL_LOGIC_TOTAL_RECV_BYTES,

		COL_LOGIC_TOTAL_NET_CMD,
		COL_LOGIC_TOTAL_LOGIC_CMD,
		COL_LOGIC_TOTAL_NET_PROCESS,
		COL_LOGIC_TOTAL_LOGIC_PROCESS,

		COL_LOGIC_TOTAL_MAX,
	};
public:
	struct XTotalNode
	{
		int		eType;
		uint	uCacheVaild;
		uint	uCacheTotal;
		uint	uProcesserCount;
		uint	uQueue;
		uint	uFreeTime;
		uint	uTimeInterval;

		uint64	uCpuUseTime;
		uint	uCpuUsage;
		uint64	uMemUsed;
		uint	uThreads;

		uint64	uSendBytes;
		uint64	uRecvBytes;

		uint	uLogicCmd;
		uint	uNetCmd;

		uint	uLogicProcess;
		uint	uNetProcess;

		XTotalNode() {
			eType = 0;
			uCacheVaild = 0;
			uCacheTotal = 0;
			uProcesserCount = 0;
			uQueue = 0;
			uFreeTime = 0;
			uTimeInterval = 0;

			uCpuUseTime = 0;
			uCpuUsage = 0;
			uMemUsed = 0;
			uThreads = 0;

			uSendBytes = 0;
			uRecvBytes = 0;

			uLogicCmd = 0;
			uNetCmd = 0;
			uLogicProcess = 0;
			uNetProcess = 0;
		}
	};
	typedef std::map<int, XTotalNode> MapTypeTotal;
public:
	void UpdateUI();
private:
	ToolFrame::CListCtrlEdit _lcLogicServerTotal;// 逻辑服务器总览
public:
	afx_msg void OnClose();
};
