// DlgServerTotal.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgServerTotal.h"
#include "afxdialogex.h"
#include "DlgServers.h"
#include "..\..\ToolFrame\Include\MFC\ApiMFC.h"

// CDlgServerTotal 对话框

IMPLEMENT_DYNAMIC(CDlgServerTotal, CDialogEx)

CDlgServerTotal::CDlgServerTotal(CWnd* pParent /*=NULL*/)
	: CDialogEx(DLG_TOTAL_VIEW, pParent)
{

}

CDlgServerTotal::~CDlgServerTotal()
{
}

void CDlgServerTotal::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LC_LOGIC_SERVERS_TOTAL, _lcLogicServerTotal);
}

BEGIN_MESSAGE_MAP(CDlgServerTotal, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CDlgServerTotal 消息处理程序
void CDlgServerTotal::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();

	CDlgServers* pDlg = dynamic_cast<CDlgServers*>(GetParent());
	ASSERT_LOG_ERROR(pDlg);

	pDlg->OnTotalWndClosed();
}

BOOL CDlgServerTotal::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_TYPE,			"类型",		ToolFrame::CListCtrlEdit::SORT_STRING);
	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_CACHE_VAILD,	"负载",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_CACHE_CACHE,	"缓存",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_CACHE_TOTAL,	"总计",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_PRCOESSER_COUNT,"处理器数",ToolFrame::CListCtrlEdit::SORT_NUMBER);

	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_QUEUE_PROCESS, "队列",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_FREE_TIME,		"压力",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_CPU_USE_TIME,	"CPU时间",	ToolFrame::CListCtrlEdit::SORT_TIME);
	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_CPU_USAGE,		"CPU(%)",	ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_MEM_USED,		"内存占用(KB)", ToolFrame::CListCtrlEdit::SORT_NUMBER_READ_3);
	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_THREADS,		"线程数",	ToolFrame::CListCtrlEdit::SORT_NUMBER);

	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_SEND_BYTES,	"发送(KB/S)", ToolFrame::CListCtrlEdit::SORT_NUMBER_READ_3);
	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_RECV_BYTES,	"接收(KB/S)", ToolFrame::CListCtrlEdit::SORT_NUMBER_READ_3);

	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_LOGIC_PROCESS, "逻辑处理量", ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_NET_PROCESS,	"网络处理量", ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_LOGIC_CMD,		"逻辑队列", ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServerTotal.SetTitle(COL_LOGIC_TOTAL_NET_CMD,		"网络队列", ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServerTotal.Init();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDlgServerTotal::UpdateUI()
{
	CDlgServers* pDlg = dynamic_cast<CDlgServers*>(GetParent());
	ASSERT_LOG_ERROR(pDlg);

	MapTypeTotal vTotal;

	//统计出各项数据
	{
		const CDlgServers::MapLogicNode& vLogic = pDlg->GetLogicNode();

		CLockRead lock(vLogic.GetMutex());
		CDlgServers::MapLogicNode::StdMap::const_iterator itr;
		foreach(itr, vLogic.GetMap()) {
			const CDlgServers::XLogicNode* pNode = itr->second;
			ASSERT_LOG_ERROR(pNode);

			CLockScoped lockLogic(pNode->mutex);

			const ToolFrame::XServerLogic* pLogic = pDlg->GetTopologyControl().GetServersLogic().FindLogicByServerID(pNode->uServerID);
			ASSERT_LOG_ERROR(pLogic);

			const ToolFrame::XConfigLogic* pConfigSrvType = pDlg->GetTopologyControl().FindConfigSrvType(pLogic->eSrvType);
			ASSERT_LOG_ERROR(pConfigSrvType);

			XTotalNode& xNode = ToolFrame::GetValueByKeyForce(vTotal, pLogic->eSrvType);
			
			xNode.eType = pLogic->eSrvType;
			xNode.uCacheVaild += pLogic->xUpdate.uCacheVaild;
			xNode.uCacheTotal += pLogic->xUpdate.uCacheTotal;
			xNode.uProcesserCount += pLogic->xUpdate.uProcesserCount;
		
			xNode.uQueue += pLogic->xUpdate.uQueueProcess;
			xNode.uFreeTime += pLogic->xUpdate.uFreeTime;
			xNode.uTimeInterval += pConfigSrvType->uTimeInterval;

			xNode.uCpuUseTime += pLogic->xUpdate.uCpuUseTime;
			xNode.uCpuUsage += pLogic->xUpdate.uCpuUsage;
			xNode.uMemUsed += pLogic->xUpdate.uMemoryUsed;

			xNode.uThreads += pLogic->xUpdate.uThreads;

			xNode.uSendBytes += pLogic->xUpdate.uSendBytes;
			xNode.uRecvBytes += pLogic->xUpdate.uRecvBytes;
			xNode.uLogicCmd += pLogic->xUpdate.nLogicCmd;
			xNode.uNetCmd += pLogic->xUpdate.nNetCmd;
			xNode.uLogicProcess += pLogic->xUpdate.nLogicProcess;
			xNode.uNetProcess += pLogic->xUpdate.nNetProcess;
		}
	}

	//显示
	{
		MapTypeTotal::const_iterator itr;
		foreach(itr, vTotal) {
			const XTotalNode& xNode = itr->second;

			const ToolFrame::XConfigLogic* pConfigSrvType = pDlg->GetTopologyControl().FindConfigSrvType(xNode.eType);
			ASSERT_LOG_ERROR(pConfigSrvType);

			VectorString vString;
			vString.resize(COL_LOGIC_TOTAL_MAX);
			int nRow = ApiMFC::FindString(_lcLogicServerTotal, pConfigSrvType->sRemark, COL_LOGIC_TOTAL_TYPE);

			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_TYPE,			pConfigSrvType->sRemark);

			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_CACHE_VAILD,		ToolFrame::ValueToRead(xNode.uCacheVaild));
			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_CACHE_CACHE,		ToolFrame::ValueToRead(xNode.uCacheTotal - xNode.uCacheVaild));
			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_CACHE_TOTAL,		ToolFrame::ValueToRead(xNode.uCacheTotal));
			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_PRCOESSER_COUNT,	ToolFrame::ValueToRead(xNode.uProcesserCount));
			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_QUEUE_PROCESS,		ToolFrame::ValueToRead(xNode.uQueue));

			if (xNode.uTimeInterval > 0)
			{
				uint uFree = (uint)(1.f * xNode.uFreeTime / xNode.uTimeInterval*100);
				if (uFree>100)uFree = 100;
				ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_FREE_TIME, ToolFrame::ValueToRead(100 - uFree));
			}

			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_CPU_USE_TIME,	ToolFrame::TimeToRead(xNode.uCpuUseTime));
			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_CPU_USAGE,		ToolFrame::ValueToRead(xNode.uCpuUsage));
			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_MEM_USED,		ToolFrame::ValueToRead(xNode.uMemUsed));
			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_THREADS,		ToolFrame::ValueToRead(xNode.uThreads));

			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_SEND_BYTES,		ToolFrame::ValueToRead(xNode.uSendBytes));
			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_RECV_BYTES,		ToolFrame::ValueToRead(xNode.uRecvBytes));

			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_NET_CMD,		ToolFrame::ValueToRead(xNode.uNetCmd));
			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_LOGIC_CMD,		ToolFrame::ValueToRead(xNode.uLogicCmd));
			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_NET_PROCESS,	ToolFrame::ValueToRead(xNode.uNetProcess));
			ToolFrame::SetValueByIndex(vString, COL_LOGIC_TOTAL_LOGIC_PROCESS,	ToolFrame::ValueToRead(xNode.uLogicProcess));

			ApiMFC::SetRowString(_lcLogicServerTotal, nRow, vString);
		}
	}
}


