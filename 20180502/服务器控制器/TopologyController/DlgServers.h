
// ServersControllerDlg.h : 头文件
//

#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "TopologyControl.h"
#include "ListCtrlEdit.h"
#include "TThreadSaftyList.h"
#include "IThreadTask.h"
#include "HSystem.h"
#include "HLog.h"
#include "TimeOut.h"
#include "TThreadSaftyMap.h"
#include "DlgServerTotal.h"
#include "DlgDebug.h"

//对应字符串
const std::string SERVER_STATE_UNKNOW	="未知";
const std::string SERVER_STATE_INIT		="初始";
const std::string SERVER_STATE_NORMAL	="正常";
const std::string SERVER_STATE_STOP		="停止";
const std::string SERVER_STATE_OFFLINE	="离线";

// CDlgServers 对话框
class CDlgServers 
	: public CDialogEx
	,public ToolFrame::HTopologyControl
	,public ToolFrame::HSystem
	,public ToolFrame::HLog
{
// 构造
public:
	CDlgServers(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CDlgServers();
// 对话框数据
	enum { IDD = DLG_SERVERS };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedStartServer();
	afx_msg void OnBnClickedSaveServer();
	afx_msg void OnBnClickedCleanUpServer();
	afx_msg void OnBnClickedStopService();
	afx_msg void OnBnClickedShutDown();
	afx_msg void OnBnClickedUploadConfig();
	afx_msg void OnBnClickedUploadAndStart();
	afx_msg void OnCbnSelchangeOperator();
public:
	afx_msg void OnBnClickedPhysicalMemoryClear();
	afx_msg void OnBnClickedPhysicalReboot();
	afx_msg void OnCbnSelchangeSolution();
	afx_msg void OnBnClickedTotalServer();
private:
	enum ELogicCol
	{
		COL_LOGIC_INVAILD = -1,

		COL_LOGIC_ID,
		COL_LOGIC_TYPE,
		COL_LOGIC_RUN_TYPE,
		COL_LOGIC_HASH,
		COL_LOGIC_PORT,
		COL_LOGIC_PUBLIC_PORT,

		COL_LOGIC_STATE,

		COL_LOGIC_TIME_RUNONCE_AVG,
		COL_LOGIC_TIME_RUNONCE_MAX,

		COL_LOGIC_TIME_PROCESS_AVG,
		COL_LOGIC_TIME_PROCESS_MAX,

		COL_LOGIC_TIME_SEND_AVG,
		COL_LOGIC_TIME_SEND_MAX,

		COL_LOGIC_TIME_SENDING_AVG,
		COL_LOGIC_TIME_SENDING_MAX,
		
		COL_LOGIC_CACHE_VAILD,
		COL_LOGIC_CACHE_TOTAL,
		COL_LOGIC_PROCESSER_COUNT,
		COL_LOGIC_QUEUE_PROCESS,
		COL_LOGIC_FREE_TIME,
		COL_LOGIC_CPU_TIME,
		COL_LOGIC_CPU_USAGE,
		COL_LOGIC_MEM_USED,
		COL_LOGIC_THREADS,

		COL_LOGIC_PHYSICAL_ID,

		COL_LOGIC_TIME_STARTUP,
		COL_LOGIC_TIME_REPROT,
		COL_LOGIC_TIME_SAVE,
		COL_LOGIC_TIME_CLEAN_UP,
		COL_LOGIC_SYSTEM_CLEANUP,
		COL_LOGIC_RECONNECT,

		COL_LOGIC_SEND_BYTES,
		COL_LOGIC_RECV_BYTES,
		COL_LOGIC_SEND_BYTES_TOTAL,
		COL_LOGIC_RECV_BYTES_TOTAL,

		COL_LOGIC_NET_CMD,
		COL_LOGIC_LOGIC_CMD,
		COL_LOGIC_NET_PROCESS,
		COL_LOGIC_LOGIC_PROCESS,
		
		COL_LOGIC_PUBLIC_RECV,
		COL_LOGIC_PUBLIC_SEND,

		COL_LOGIC_SESSION,
		COL_LOGIC_PACK_PROCESS,
		COL_LOGIC_LOGIC_PROCESS_TOTAL,
		COL_LOGIC_NET_PROCESS_TOTAL,
		COL_LOGIC_PACK_PROCESS_TOTAL,

		COL_LOGIC_MAX,
	};
	enum EPhysicalCol
	{
		COL_PHYSICAL_ID,
		COL_PHYSICAL_STATE,
		COL_PHYSICAL_CPU_USAGE,
		COL_PHYSICAL_MEM_USED,
		COL_PHYSICAL_MEM_FREE,
		COL_PHYSICAL_MEM_USAGE,
		COL_PHYSICAL_IP,
		COL_PHYSICAL_MAC,
		COL_PHYSICAL_CLEANUP,
		COL_PHYSICAL_RECONNECT,

		COL_PHYSICAL_SEND_BYTES,
		COL_PHYSICAL_RECV_BYTES,
		COL_PHYSICAL_TOTAL_BYTES,

		COL_PHYSICAL_REMARK,

		COL_PHYSICAL_MAX,
	};

public:
	struct XLogicNode
	{
		mutable CMutexRecursive	mutex;
		bool					bUpdated;
		uint					uServerID;

		uint					uSendBytesTotal;
		uint					uRecvBytesTotal;

		uint					uLogicProcessTotal;
		uint					uNetProcessTotal;
		uint					uPackProcessTotal;
	};

	typedef ToolFrame::TThreadSaftyMapValue<int,XLogicNode*>	MapLogicNode;
	typedef ToolFrame::TThreadSaftyListValue<XLogicNode*>		QueueLogicNode;

	//警告色
	struct XWarningColor
	{
		std::string sWarningLevel;//警告等级
		COLORREF	clrText;
		COLORREF	clrTextBg;
	};
	typedef std::map<std::string,XWarningColor> MapWarningColor;
private:
	bool ReadConfig();
	bool ReadConfigSolution(const std::string& sName);
	bool InitReportData();
	bool AddLogic(const ToolFrame::VectorLogic& vLogic);
	bool AddPhysical(const ToolFrame::VectorPhysical& vPhysical);
private:
	virtual bool OnAuthorizationRep(bool bAuthorized,time_t uTimeStart);
	virtual bool OnAllServer(const ToolFrame::VectorPhysical& vPhysical,const ToolFrame::VectorLogic& vLogic);
	virtual bool OnAddPhysical(const ToolFrame::VectorPhysical& vPhysical);
	virtual bool OnAddLogic(const ToolFrame::VectorLogic& vLogic);
	virtual bool OnRemovePhysical(int nID);
	virtual bool OnRemoveLogic(int nID);
	virtual bool OnLogicStateChanged(const ToolFrame::MapLogicUpdate& vUpdate,uint uClientID);
	virtual bool OnPhysicalStateChanged(const ToolFrame::MapPhysicalUpdate& vUpdate,uint uClientID);
	virtual bool OnConnectStateChanged(int eState);//CConnectMonitor::EState
public:
	virtual const MapLogicNode& GetLogicNode()const;
	virtual const ToolFrame::CTopologyControl& GetTopologyControl()const;
public:
	virtual bool OnTotalWndClosed();
	virtual bool OnDebugWndClosed();
public:
	virtual bool UpdateUI();//绘制UI界面 返回 是否还需要继续绘制
	virtual bool DrawColorLogic(int nRow);
	virtual bool DrawColorPhysical(int nRow);
	virtual bool LogicGetSelectedServerID(VectorUint32& vServerID)const;
	virtual bool LogicAllServerID(VectorUint32& vServerID)const;

	virtual bool PhysicalGetSelectedServerID(VectorUint32& vPhysicalID)const;
	virtual bool PhysicalGetAllServerID(VectorUint32& vPhysicalID)const;
public:
	std::string TranState(int eState)const;
	std::string TranMonitorState(int eState)const;
	std::string TranRunType(int eRunType)const;
private:
	bool GetInfo(VectorString& vString,XLogicNode* pNode);
	bool GetInfo(VectorString& vString,const ToolFrame::XServerLogic* pServer)const;
	bool GetInfo(VectorString& vString,const ToolFrame::XServerPhysical* pServer)const;
private:
	virtual	bool OnSystemProcess(uint64 uTime);	//主循环回调(处理时间)
	virtual bool OnLogMsg(const std::string& sLogLevel,const std::stringstream& sStreamLog);//产生日志时(返回false阻止写日志)
private:
	ToolFrame::CListCmb		_cCmbOperator;
	ToolFrame::CListCtrlEdit _lcLogicServers;
	ToolFrame::CListCtrlEdit _lcPhysicalServers;

	CComboBox				_cCmbSolution;
	CStatic					_cStcStartTime;

	std::string				_sTitle;
	MapLogicNode			_vLogicNode;
	QueueLogicNode			_vLogicQueue;

	ToolFrame::CTopologyControl	_xTopologyControl;

	VectorString			_vSolution;		
	MapWarningColor			_vWarningColor;
	MapStringString			_vWarningLogicState;
	MapIntString			_vWarningLogicPressure;
	MapIntString			_vWarningPhysical;

	ToolFrame::CTimeOut		_xTimeOutUI;

	CDlgServerTotal*		_pDlgTotalServer;
	CDlgDebug*				_pDlgDebug;
public:
	afx_msg void OnBnClickedServersDebug();
};
