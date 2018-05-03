
// ServersControllerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ServersController.h"
#include "DlgServers.h"
#include "afxdialogex.h"

#include "ToolFrame.h"

#include "ApiMFC.h"
#include "ApiWin.h"
#include "IApiTool.h"
#include "MProtocol.h"
#include "TimeOut.h"
#include "MSystem.h"
#include "MLoger.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	CStatic _cStcCompileTime;
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, STC_ABOUT_TIME, _cStcCompileTime);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ApiMFC::SetWindowText(_cStcCompileTime,MAKE_STRING(MACRO_DATE<<" "<<MACRO_TIME));
	return TRUE;
}


// CServersControllerDlg 对话框
CDlgServers::CDlgServers(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgServers::IDD, pParent)
{
	_pDlgTotalServer = nullptr;
	_pDlgDebug = nullptr;
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	_xTimeOutUI.SetIntervalMill(1000);
	_xTopologyControl.SetHandler(this);
}

CDlgServers::~CDlgServers()
{
}

void CDlgServers::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LC_LOGIC_SERVERS, _lcLogicServers);
	DDX_Control(pDX, LC_PHYSICAL_SERVERS, _lcPhysicalServers);
	DDX_Control(pDX, STC_START_TIME, _cStcStartTime);
	DDX_Control(pDX, CMB_OPERATOR, _cCmbOperator);
	DDX_Control(pDX, CMB_SOLUTION, _cCmbSolution);
}

BEGIN_MESSAGE_MAP(CDlgServers, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BTN_SHUT_DOWN, &CDlgServers::OnBnClickedShutDown)
	ON_BN_CLICKED(BTN_START_SERVER, &CDlgServers::OnBnClickedStartServer)
	ON_BN_CLICKED(BTN_SAVE_SERVER, &CDlgServers::OnBnClickedSaveServer)
	ON_BN_CLICKED(BTN_STOP_SERVICE, &CDlgServers::OnBnClickedStopService)
	ON_CBN_SELCHANGE(CMB_OPERATOR, &CDlgServers::OnCbnSelchangeOperator)
	ON_BN_CLICKED(BTN_CLEAN_UP_SERVER, &CDlgServers::OnBnClickedCleanUpServer)
	ON_BN_CLICKED(BTN_UPLOAD_CONFIG, &CDlgServers::OnBnClickedUploadConfig)
	ON_BN_CLICKED(BTN_UPLOAD_AND_START, &CDlgServers::OnBnClickedUploadAndStart)
	ON_BN_CLICKED(BTN_PHYSICAL_MEMORY_CLEAR, &CDlgServers::OnBnClickedPhysicalMemoryClear)
	ON_BN_CLICKED(BTN_PHYSICAL_REBOOT, &CDlgServers::OnBnClickedPhysicalReboot)
	ON_CBN_SELCHANGE(CMB_SOLUTION, &CDlgServers::OnCbnSelchangeSolution)
	ON_BN_CLICKED(BTN_TOTAL_SERVER, &CDlgServers::OnBnClickedTotalServer)
	ON_BN_CLICKED(BTN_SERVERS_DEBUG, &CDlgServers::OnBnClickedServersDebug)
END_MESSAGE_MAP()


// CServersControllerDlg 消息处理程序

BOOL CDlgServers::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	ToolFrame::MSystem::Singleton();
	ToolFrame::MSystem::Singleton().SetHandler(this);
	ToolFrame::MLoger::Singleton().SetHandler(this);
	ToolFrame::MSystem::Singleton().Init();

	ApiMFC::AddString(_cCmbOperator,"维持原状");
	ApiMFC::AddString(_cCmbOperator,"启动服务");
	ApiMFC::AddString(_cCmbOperator,"保存数据");
	ApiMFC::AddString(_cCmbOperator,"清理缓存");
	ApiMFC::AddString(_cCmbOperator,"停止服务");
	ApiMFC::AddString(_cCmbOperator,"关闭服务");

	_lcLogicServers.SetTitle(COL_LOGIC_ID,					"ID",			ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_TYPE,				"类型",			ToolFrame::CListCtrlEdit::SORT_STRING);
	_lcLogicServers.SetTitle(COL_LOGIC_HASH,				"哈希",			ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_RUN_TYPE,			"架构",			ToolFrame::CListCtrlEdit::SORT_STRING);
	_lcLogicServers.SetTitle(COL_LOGIC_PORT,				"端口",			ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_PUBLIC_PORT,			"开放端口",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_PUBLIC_RECV,			"开放接收",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_PUBLIC_SEND,			"开放发送",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_STATE,				"服务状态",		ToolFrame::CListCtrlEdit::SORT_STRING,&_cCmbOperator);
	_lcLogicServers.SetTitle(COL_LOGIC_TIME_RUNONCE_AVG,	"跑均(MS)",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_TIME_RUNONCE_MAX,	"跑峰(MS)",		ToolFrame::CListCtrlEdit::SORT_NUMBER);

	_lcLogicServers.SetTitle(COL_LOGIC_TIME_PROCESS_AVG,	"包均(MS)",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_TIME_PROCESS_MAX,	"包峰(MS)",		ToolFrame::CListCtrlEdit::SORT_NUMBER);

	_lcLogicServers.SetTitle(COL_LOGIC_TIME_SEND_AVG,		"发均(MS)",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_TIME_SEND_MAX,		"发峰(MS)",		ToolFrame::CListCtrlEdit::SORT_NUMBER);

	_lcLogicServers.SetTitle(COL_LOGIC_TIME_SENDING_AVG,	"发中均(MS)",	ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_TIME_SENDING_MAX,	"发中峰(MS)",	ToolFrame::CListCtrlEdit::SORT_NUMBER);

	_lcLogicServers.SetTitle(COL_LOGIC_CACHE_VAILD,			"负载",			ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_CACHE_TOTAL,			"缓存",			ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_PROCESSER_COUNT,		"处理器数",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_QUEUE_PROCESS,		"队列",			ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_FREE_TIME,			"压力",			ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_CPU_TIME,			"CPU时间",		ToolFrame::CListCtrlEdit::SORT_TIME);
	_lcLogicServers.SetTitle(COL_LOGIC_CPU_USAGE,			"CPU(%)",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_MEM_USED,			"内存占用(KB)",	ToolFrame::CListCtrlEdit::SORT_NUMBER_READ_3);
	_lcLogicServers.SetTitle(COL_LOGIC_THREADS,				"线程数",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	
	_lcLogicServers.SetTitle(COL_LOGIC_PHYSICAL_ID,			"物理ID",		ToolFrame::CListCtrlEdit::SORT_NUMBER);

	_lcLogicServers.SetTitle(COL_LOGIC_TIME_STARTUP,		"启动时间",		ToolFrame::CListCtrlEdit::SORT_STRING);
	_lcLogicServers.SetTitle(COL_LOGIC_TIME_REPROT,			"最近汇报",		ToolFrame::CListCtrlEdit::SORT_STRING);
	_lcLogicServers.SetTitle(COL_LOGIC_TIME_SAVE,			"最近保存",		ToolFrame::CListCtrlEdit::SORT_STRING);
	_lcLogicServers.SetTitle(COL_LOGIC_TIME_CLEAN_UP,		"最近清理",		ToolFrame::CListCtrlEdit::SORT_STRING);
	_lcLogicServers.SetTitle(COL_LOGIC_SYSTEM_CLEANUP,		"系统清理",		ToolFrame::CListCtrlEdit::SORT_STRING);
	_lcLogicServers.SetTitle(COL_LOGIC_RECONNECT,			"重启",			ToolFrame::CListCtrlEdit::SORT_NUMBER);

	_lcLogicServers.SetTitle(COL_LOGIC_SEND_BYTES,			"发送(KB/S)",	ToolFrame::CListCtrlEdit::SORT_NUMBER_READ_3);
	_lcLogicServers.SetTitle(COL_LOGIC_RECV_BYTES,			"接收(KB/S)",	ToolFrame::CListCtrlEdit::SORT_NUMBER_READ_3);
	_lcLogicServers.SetTitle(COL_LOGIC_SEND_BYTES_TOTAL,	"总发送(KB)",	ToolFrame::CListCtrlEdit::SORT_NUMBER_READ_3);
	_lcLogicServers.SetTitle(COL_LOGIC_RECV_BYTES_TOTAL,	"总接收(KB)",	ToolFrame::CListCtrlEdit::SORT_NUMBER_READ_3);

	_lcLogicServers.SetTitle(COL_LOGIC_SESSION,				"会话数",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_PACK_PROCESS_TOTAL,	"协议包总处理",	ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_LOGIC_PROCESS_TOTAL,	"逻辑总处理",	ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_NET_PROCESS_TOTAL,	"网络总处理",	ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_PACK_PROCESS,		"协议包处理量",	ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_LOGIC_PROCESS,		"逻辑处理量",	ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_NET_PROCESS,			"网络处理量",	ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_LOGIC_CMD,			"逻辑队列",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.SetTitle(COL_LOGIC_NET_CMD,				"网络队列",		ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcLogicServers.Init();

	_lcPhysicalServers.SetTitle(COL_PHYSICAL_ID,		"ID",			ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcPhysicalServers.SetTitle(COL_PHYSICAL_STATE,		"状态",			ToolFrame::CListCtrlEdit::SORT_STRING);
	_lcPhysicalServers.SetTitle(COL_PHYSICAL_CPU_USAGE,	"CPU占用率(%)",	ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcPhysicalServers.SetTitle(COL_PHYSICAL_MEM_USED,	"内存使用(KB)",	ToolFrame::CListCtrlEdit::SORT_NUMBER_READ_3);
	_lcPhysicalServers.SetTitle(COL_PHYSICAL_MEM_FREE,	"内存剩余(KB)",	ToolFrame::CListCtrlEdit::SORT_NUMBER_READ_3);
	_lcPhysicalServers.SetTitle(COL_PHYSICAL_MEM_USAGE,	"内存占用率(%)",ToolFrame::CListCtrlEdit::SORT_NUMBER);
	_lcPhysicalServers.SetTitle(COL_PHYSICAL_IP,		"IP地址",		ToolFrame::CListCtrlEdit::SORT_STRING);
	_lcPhysicalServers.SetTitle(COL_PHYSICAL_MAC,		"Mac地址",		ToolFrame::CListCtrlEdit::SORT_STRING);
	_lcPhysicalServers.SetTitle(COL_PHYSICAL_CLEANUP,	"系统清理",		ToolFrame::CListCtrlEdit::SORT_STRING);
	_lcPhysicalServers.SetTitle(COL_PHYSICAL_RECONNECT,	"重启",			ToolFrame::CListCtrlEdit::SORT_NUMBER);
	
	_lcPhysicalServers.SetTitle(COL_PHYSICAL_SEND_BYTES,"发送(KB/S)",	ToolFrame::CListCtrlEdit::SORT_NUMBER_READ_3);
	_lcPhysicalServers.SetTitle(COL_PHYSICAL_RECV_BYTES,"接收(KB/S)",	ToolFrame::CListCtrlEdit::SORT_NUMBER_READ_3);
	_lcPhysicalServers.SetTitle(COL_PHYSICAL_TOTAL_BYTES,"流量(KB/S)",	ToolFrame::CListCtrlEdit::SORT_NUMBER_READ_3);

	_lcPhysicalServers.SetTitle(COL_PHYSICAL_REMARK,	"备注",			ToolFrame::CListCtrlEdit::SORT_STRING);
	_lcPhysicalServers.Init();

	ApiMFC::DeleteItem(_lcLogicServers);
	ApiMFC::DeleteItem(_lcPhysicalServers);

	if (!ReadConfig())//读取配置表
		ApiMFC::ApiMessageBox("配置表错误", "错误");
	
	ApiMFC::Show(_cCmbSolution,_vSolution);
	ApiMFC::SetSelectd(_cCmbSolution,0);
	OnCbnSelchangeSolution();

	//初始化拓扑控制器
	_xTopologyControl.Init();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDlgServers::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDlgServers::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDlgServers::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CDlgServers::ReadConfig()
{
	//清除内存
	ToolFrame::Clear(_vWarningColor);
	ToolFrame::Clear(_vWarningLogicState);
	ToolFrame::Clear(_vWarningLogicPressure);
	ToolFrame::Clear(_vWarningPhysical);

	std::string sFile = ToolFrame::LoadFile("Config.xml");
	if (ApiWin::IsUtf8(sFile))
		sFile = ApiWin::Utf8ToGbk(sFile);

	TiXmlDocument xDoc;
	if (!ToolFrame::Parse(xDoc,sFile))return false;

	//读取标题
	ToolFrame::SafeGetAttribute(&xDoc,"Config[Name]",_sTitle,"");
	//_sTitle = ApiWin::Utf8ToGbk(_sTitle);

	//读取控制器所需信息
	std::string sAddress;std::string sPassword;
	if (!ToolFrame::GetAttribute(&xDoc,"Config/Center[Address Password]",sAddress,sPassword))return false;

	//读取所属服务器组,大区 服务器名称 开服日期
	std::string sServerGroupID;std::string sServerZoneID;std::string sServerName;ToolFrame::CDate xServerOpen;
	ToolFrame::SafeGetAttribute(&xDoc,"Config/Center[ServerGroupID]",	sServerGroupID,	"");
	ToolFrame::SafeGetAttribute(&xDoc,"Config/Center[ServerZoneID]",	sServerZoneID,	"");
	ToolFrame::SafeGetAttribute(&xDoc,"Config/Center[ServerName]",		sServerName,	"");
	ToolFrame::SafeGetAttribute(&xDoc,"Config/Center[ServerOpen]",		xServerOpen,	ToolFrame::CDate());

	//读取警告色配置
	VectorElement vXmlWarningColor;
	if (ToolFrame::GetElement(vXmlWarningColor,&xDoc,"Config/WarningConfig/WarningColor/Warning"))
	{
		VectorElement::const_iterator itr;
		foreach(itr,vXmlWarningColor){
			const TiXmlElement* pXmlWarningColor = *itr;
			ASSERT_LOG_ERROR(pXmlWarningColor);

			VectorInt vTextColor;
			VectorInt vTextBgColor;

			XWarningColor xColor;
			if (!ToolFrame::GetAttribute(pXmlWarningColor,"[Level TextColor TextBgColor]",xColor.sWarningLevel,vTextColor,vTextBgColor))return false;

			if (vTextColor.size() != 3)return false;
			if (vTextBgColor.size() != 3)return false;

			xColor.clrText		= RGB(vTextColor[0],vTextColor[1],vTextColor[2]);
			xColor.clrTextBg	= RGB(vTextBgColor[0],vTextBgColor[1],vTextBgColor[2]);

			ToolFrame::Insert(_vWarningColor,xColor.sWarningLevel,xColor);
		}
	}
	//读取警告列表
	VectorElement vXmlLogicWarningState;
	if (ToolFrame::GetElement(vXmlLogicWarningState,&xDoc,"Config/WarningConfig/LogicServer/ServerState"))
	{
		VectorElement::const_iterator itr;
		foreach(itr,vXmlLogicWarningState){
			const TiXmlElement* pXmlWarning = *itr;
			ASSERT_LOG_ERROR(pXmlWarning);

			std::string sState; std::string sWarningLevel;
			if (!ToolFrame::GetAttribute(pXmlWarning,"[State WarningLevel]",sState,sWarningLevel))return false;

			ToolFrame::Insert(_vWarningLogicState,sState,sWarningLevel);
		}
	}
	//读取警告列表
	VectorElement vXmlLogicWarningPressure;
	if (ToolFrame::GetElement(vXmlLogicWarningPressure,&xDoc,"Config/WarningConfig/LogicServer/ServerPressure"))
	{
		VectorElement::const_iterator itr;
		foreach(itr,vXmlLogicWarningPressure){
			const TiXmlElement* pXmlWarning = *itr;
			ASSERT_LOG_ERROR(pXmlWarning);

			int nValue = 0; std::string sWarningLevel;
			if (!ToolFrame::GetAttribute(pXmlWarning,"[Pressure WarningLevel]",nValue,sWarningLevel))return false;

			ToolFrame::Insert(_vWarningLogicPressure,nValue,sWarningLevel);
		}
	}

	//读取警告列表
	VectorElement vXmlPhysicalWarning;
	if (ToolFrame::GetElement(vXmlPhysicalWarning,&xDoc,"Config/WarningConfig/PhysicalServer/Warning"))
	{
		VectorElement::const_iterator itr;
		foreach(itr,vXmlPhysicalWarning){
			const TiXmlElement* pXmlWarning = *itr;
			ASSERT_LOG_ERROR(pXmlWarning);

			int nValue = 0; std::string sWarningLevel;
			if (!ToolFrame::GetAttribute(pXmlWarning,"[MemoryUsage WarningLevel]",nValue,sWarningLevel))return false;

			ToolFrame::Insert(_vWarningPhysical,nValue,sWarningLevel);
		}
	}

	//读取解决方案标题
	VectorElement vXmlSolution;
	if (!ToolFrame::GetElement(vXmlSolution,&xDoc,"Config/Solution/"))return false;

	VectorElement::const_iterator itr;
	foreach(itr,vXmlSolution){
		const TiXmlElement* pXmlSolution = *itr;
		ASSERT_LOG_ERROR(pXmlSolution);

		std::string sName;
		if (!ToolFrame::GetAttribute(pXmlSolution,"[Name]",sName))return false;
		if (sName.empty())return false;

		ToolFrame::Insert(_vSolution,sName);
	}

	uint uSendSize = 0; uint uRecvSize = 0;  uint uBlockSize = 0;
	ToolFrame::SafeGetAttribute(&xDoc, "Config/Center[SendSize]", uSendSize, 0);
	ToolFrame::SafeGetAttribute(&xDoc, "Config/Center[RecvSize]", uRecvSize, 0);
	ToolFrame::SafeGetAttribute(&xDoc, "Config/Center[BlockSize]", uBlockSize, ToolFrame::MProtocol::Singleton().GetBlockSize());

	//设置拓扑控制器
	_xTopologyControl.SetCenterIP(sAddress);
	_xTopologyControl.SetPassword(sPassword);
	_xTopologyControl.SetServerGroupID(sServerGroupID);
	_xTopologyControl.SetServerZoneID(sServerZoneID);
	_xTopologyControl.SetServerName(sServerName);
	_xTopologyControl.SetServerOpen(xServerOpen);
	_xTopologyControl.SetPassword(sPassword);
	_xTopologyControl.SetSendSize(uSendSize);
	_xTopologyControl.SetRecvSize(uRecvSize);
	_xTopologyControl.SetBlockSize(uBlockSize);
	return true;
}

bool CDlgServers::ReadConfigSolution( const std::string& sName )
{
	ToolFrame::MapConfigLogic		vConfigLogic;
	ToolFrame::MapConfigLink		vConfigLink;
	ToolFrame::MapConfigServer		vConfigServer;

	std::string sFile = ToolFrame::LoadFile("Config.xml");
	if (ApiWin::IsUtf8(sFile))
		sFile = ApiWin::Utf8ToGbk(sFile);

	TiXmlDocument xDoc;
	if (!ToolFrame::Parse(xDoc,sFile))return false;

	//读取逻辑连接
	{
		VectorElement vXmlTopologyLink;
		if (!ToolFrame::GetElement(vXmlTopologyLink,&xDoc,"Config/LogicLinks/Link"))return false;

		VectorElement::const_iterator itr;
		foreach(itr,vXmlTopologyLink){
			const TiXmlElement* pXmlConfigLink = *itr;
			ASSERT_LOG_ERROR(pXmlConfigLink);

			ToolFrame::XConfigLink xConfigLink;
			if (!ToolFrame::GetAttribute(pXmlConfigLink,"[SrcSrv DesSrv Count]",xConfigLink.eSrcSrv,xConfigLink.eDesSrv,xConfigLink.uCount))return false;

			if (!ToolFrame::Insert(vConfigLink,xConfigLink))
				return false;
		}
	}
	
	const TiXmlElement* pXmlSolution = ToolFrame::GetElement(&xDoc,MAKE_STRING("Config/Solution[Name=\""<<sName<<"\"]"));
	if (!pXmlSolution)return false;

	std::string sSrvTag;
	//读取方案基本属性
	{
		ToolFrame::SafeGetAttribute(pXmlSolution, "[SrvTag]", sSrvTag,"");
	}
	
	//读取逻辑服务器类型列表
	{
		VectorElement vXmlServerType;
		if (!ToolFrame::GetElement(vXmlServerType,pXmlSolution,"LogicServers/SeverType"))return false;

		VectorElement::const_iterator itr;
		foreach(itr,vXmlServerType){
			const TiXmlElement* pXmlServerType = *itr;
			ASSERT_LOG_ERROR(pXmlServerType);

			int eSrvType = INVALID_ID;
			if (!ToolFrame::GetAttribute(pXmlServerType,"[Type]",eSrvType))return false;

			ToolFrame::XConfigLogic xConfigLogic;
			xConfigLogic.eSrvType = eSrvType;

			if (!ToolFrame::GetAttribute(xConfigLogic.eRunType,		pXmlSolution,MAKE_STRING("../LogicServers/SeverType[RunType Type=\""<<eSrvType<<"\"]")))return false;

			if (!ToolFrame::GetAttribute(xConfigLogic.uThread,		pXmlSolution,MAKE_STRING("LogicServers/SeverType[Thread Type=\""<<eSrvType<<"\"]"),			MAKE_STRING("../LogicServers/SeverType[Thread Type=\""<<eSrvType<<"\"]")))
				xConfigLogic.uThread = 0;

			if (!ToolFrame::GetAttribute(xConfigLogic.uRunOnce,		pXmlSolution,MAKE_STRING("LogicServers/SeverType[RunOnce Type=\""<<eSrvType<<"\"]"),		MAKE_STRING("../LogicServers/SeverType[RunOnce Type=\""<<eSrvType<<"\"]")))
				xConfigLogic.uRunOnce = 300;

			if (!ToolFrame::GetAttribute(xConfigLogic.uTimeInterval,pXmlSolution,MAKE_STRING("LogicServers/SeverType[TimeInterval Type=\""<<eSrvType<<"\"]"),	MAKE_STRING("../LogicServers/SeverType[TimeInterval Type=\""<<eSrvType<<"\"]")))
				xConfigLogic.uTimeInterval = 5000;

			if (!ToolFrame::GetAttribute(xConfigLogic.sRemark,		pXmlSolution,MAKE_STRING("LogicServers/SeverType[Remark Type=\""<<eSrvType<<"\"]"),			MAKE_STRING("../LogicServers/SeverType[Remark Type=\""<<eSrvType<<"\"]")))return false;

			if (!ToolFrame::GetAttribute(xConfigLogic.sExePath,		pXmlSolution,MAKE_STRING("LogicServers/SeverType[ExePath Type=\""<<eSrvType<<"\"]"),		MAKE_STRING("../LogicServers/SeverType[ExePath Type=\""<<eSrvType<<"\"]")))return false;
			if (!ToolFrame::GetAttribute(xConfigLogic.sWorkingDir,	pXmlSolution,MAKE_STRING("LogicServers/SeverType[WorkingDir Type=\""<<eSrvType<<"\"]"),		MAKE_STRING("../LogicServers/SeverType[WorkingDir Type=\""<<eSrvType<<"\"]")))return false;
			
			if (!ToolFrame::GetAttribute(xConfigLogic.uRecvSize, pXmlSolution, MAKE_STRING("LogicServers/SeverType[RecvSize Type=\"" << eSrvType << "\"]"), MAKE_STRING("../LogicServers/SeverType[RecvSize Type=\"" << eSrvType << "\"]")))
				xConfigLogic.uRecvSize = 0;
			if (!ToolFrame::GetAttribute(xConfigLogic.uSendSize, pXmlSolution, MAKE_STRING("LogicServers/SeverType[SendSize Type=\"" << eSrvType << "\"]"), MAKE_STRING("../LogicServers/SeverType[SendSize Type=\"" << eSrvType << "\"]")))
				xConfigLogic.uSendSize = 0;
			if (!ToolFrame::GetAttribute(xConfigLogic.uBlockSize, pXmlSolution, MAKE_STRING("LogicServers/SeverType[BlockSize Type=\"" << eSrvType << "\"]"), MAKE_STRING("../LogicServers/SeverType[BlockSize Type=\"" << eSrvType << "\"]")))
				xConfigLogic.uBlockSize = 4096;

			if (!ToolFrame::GetAttribute(xConfigLogic.uPublicRecv,	pXmlSolution,MAKE_STRING("LogicServers/SeverType[PublicRecv Type=\""<<eSrvType<<"\"]"),		MAKE_STRING("../LogicServers/SeverType[PublicRecv Type=\""<<eSrvType<<"\"]")))
				xConfigLogic.uPublicRecv = 8192;
			if (!ToolFrame::GetAttribute(xConfigLogic.uPublicSend,	pXmlSolution,MAKE_STRING("LogicServers/SeverType[PublicSend Type=\""<<eSrvType<<"\"]"),		MAKE_STRING("../LogicServers/SeverType[PublicSend Type=\""<<eSrvType<<"\"]")))
				xConfigLogic.uPublicSend = 0;
			if (!ToolFrame::GetAttribute(xConfigLogic.uPublicBlock, pXmlSolution, MAKE_STRING("LogicServers/SeverType[PublicBlock Type=\"" << eSrvType << "\"]"), MAKE_STRING("../LogicServers/SeverType[PublicBlock Type=\"" << eSrvType << "\"]")))
				xConfigLogic.uPublicBlock = 8192;

			if (!ToolFrame::GetAttribute(xConfigLogic.uSaveTime,	pXmlSolution,MAKE_STRING("LogicServers/SeverType[SaveTime Type=\""<<eSrvType<<"\"]"),		MAKE_STRING("../LogicServers/SeverType[SaveTime Type=\""<<eSrvType<<"\"]")))
				xConfigLogic.uSaveTime = 0;

			//xConfigLogic.sRemark = ApiWin::Utf8ToGbk(xConfigLogic.sRemark);
			if (!ToolFrame::Insert(vConfigLogic,xConfigLogic.eSrvType,xConfigLogic))
				return false;
		}
	}

	//读取服务器列表
	uint uBeginServerID = 0;uint uBeginPort = 0;//推导时的服务器 以及 端口起点
	{
		ToolFrame::SafeGetAttribute(pXmlSolution,"ServerList[BeginServerID]",	uBeginServerID,	1);
		ToolFrame::SafeGetAttribute(pXmlSolution,"ServerList[BeginPort]",		uBeginPort,		10000);

		VectorElement vXmlTopologyServer;
		if (!ToolFrame::GetElement(vXmlTopologyServer,pXmlSolution,"ServerList/Sever"))return false;

		VectorElement::const_iterator itr;
		foreach(itr,vXmlTopologyServer){
			const TiXmlElement* pXmlConfigServer = *itr;
			ASSERT_LOG_ERROR(pXmlConfigServer);

			ToolFrame::XConfigServer xConfigServer;
			if (!ToolFrame::GetAttribute(pXmlConfigServer,"[PhysicalID ServerType]",xConfigServer.uPhysicalID,xConfigServer.eSrvType))return false;

			ToolFrame::SafeGetAttribute(pXmlConfigServer,"[ServerID]",		xConfigServer.uServerID	,	INVALID_ID);
			ToolFrame::SafeGetAttribute(pXmlConfigServer,"[Port]",			xConfigServer.uPort		,	INVALID_ID);
			ToolFrame::SafeGetAttribute(pXmlConfigServer,"[PublicPort]",	xConfigServer.vPublicPort,	VectorUint16());
			ToolFrame::SafeGetAttribute(pXmlConfigServer,"[PublicConnect]",	xConfigServer.uPublicConnect, 6000);
			ToolFrame::SafeGetAttribute(pXmlConfigServer,"[Command]",		xConfigServer.sCommand,		"");

			//推导ServerID号 以及 端口号
			if (INVALID_ID == xConfigServer.uServerID)
				xConfigServer.uServerID = uBeginServerID++;
			if (INVALID_ID == xConfigServer.uPort)
				xConfigServer.uPort		= uBeginPort++;

			if (!ToolFrame::Insert(vConfigServer,xConfigServer.uServerID,xConfigServer))
				return false;
		}
	}

	//推导
	{
		//推导哈希值
		{
			ToolFrame::MapConfigLogic::iterator itrConfig;
			foreach(itrConfig,vConfigLogic){
				ToolFrame::XConfigLogic& xConfigLogic = itrConfig->second;
				if (ToolFrame::RUN_TYPE_HASH == xConfigLogic.eRunType)
				{
					uint uHashCount=0;
					ToolFrame::MapConfigServer::iterator itrServer;
					foreach(itrServer,vConfigServer){
						ToolFrame::XConfigServer& xServer = itrServer->second;
						if (xServer.eSrvType == xConfigLogic.eSrvType)
							xServer.uHash = uHashCount++;
					}
					xConfigLogic.uHashCount = uHashCount;
				}
			}
		}
	}
	
	//设置拓扑控制器
	_xTopologyControl.SetServerTag(sSrvTag);
	_xTopologyControl.SetConfigLogic(vConfigLogic);
	_xTopologyControl.SetConfigLink(vConfigLink);
	_xTopologyControl.SetConfigServer(vConfigServer);
	return true;
}

bool CDlgServers::OnAllServer( const ToolFrame::VectorPhysical& vPhysical,const ToolFrame::VectorLogic& vLogic )
{
	AddLogic(vLogic);
	AddPhysical(vPhysical);
	return true;
}

bool CDlgServers::OnAddPhysical( const ToolFrame::VectorPhysical& vPhysical )
{
	AddPhysical(vPhysical);
	return true;
}

bool CDlgServers::OnAddLogic( const ToolFrame::VectorLogic& vLogic )
{
	AddLogic(vLogic);
	return true;
}

bool CDlgServers::OnRemovePhysical( int nID )
{
	//ApiMFC::DeleteItem(_lcPhysicalServers,COL_LOGIC_ID,nID);
	return true;
}

bool CDlgServers::OnRemoveLogic( int nID )
{
// 	CLockWrite lock(_vLogicNode.GetMutex());
// 
// 	XLogicNode* pLogic =ToolFrame::GetPtrValueByKey(_vLogicNode.GetMap(),nID,true);
// 	ASSERT_LOG_ERROR(pLogic);
// 
// 	CLockScoped lockLogic(pLogic->mutex);
// 	pLogic->bUpdated = true;
// 
// 
// 	_vLogicQueue.Push(pLogic);

	return true;
}

bool CDlgServers::AddLogic( const ToolFrame::VectorLogic& vLogic )
{
	ToolFrame::VectorLogic::const_iterator itr;
	foreach(itr,vLogic){
		const ToolFrame::XServerLogic& xLogic = *itr;

		CLockWrite lock(_vLogicNode.GetMutex());

		XLogicNode* pLogic =ToolFrame::GetPtrValueByKey(_vLogicNode.GetMap(),xLogic.uServerID,true);
		ASSERT_LOG_ERROR(pLogic);

		CLockScoped lockLogic(pLogic->mutex);
		pLogic->bUpdated = true;

		pLogic->uServerID			= xLogic.uServerID;

		pLogic->uSendBytesTotal		= xLogic.xUpdate.uSendBytes;
		pLogic->uRecvBytesTotal		= xLogic.xUpdate.uRecvBytes;

		pLogic->uLogicProcessTotal	= xLogic.xUpdate.nLogicProcess;
		pLogic->uNetProcessTotal	= xLogic.xUpdate.nNetProcess;
		pLogic->uPackProcessTotal	= xLogic.xUpdate.nPacketProcess;

		_vLogicQueue.Push(pLogic);
	}

	return true;
}

bool CDlgServers::AddPhysical( const ToolFrame::VectorPhysical& vPhysical )
{
	ToolFrame::VectorPhysical::const_iterator itr;
	foreach(itr,vPhysical){
		const ToolFrame::XServerPhysical& xPhysical = *itr;

		VectorString vString;
		vString.resize(COL_PHYSICAL_MAX);
		GetInfo(vString,&xPhysical);

		int nRow = ApiMFC::FindString(_lcPhysicalServers,xPhysical.uPhysicalID,COL_PHYSICAL_ID);
		ApiMFC::SetRowString(_lcPhysicalServers,nRow,vString);
	}

	ApiMFC::SuitStringWidth(_lcPhysicalServers);
	return true;
}

std::string CDlgServers::TranState( int eState )const
{
	switch (eState)
	{
	case ToolFrame::CONNECT_STATE_INIT:
		return SERVER_STATE_INIT;
		break;
	case ToolFrame::CONNECT_STATE_NORMAL:
		return SERVER_STATE_NORMAL;
		break;
	case ToolFrame::CONNECT_STATE_STOP_SERVICE:
		return SERVER_STATE_STOP;
		break;
	case ToolFrame::CONNECT_STATE_OFFLINE:
		return SERVER_STATE_OFFLINE;
		break;
	}

	return SERVER_STATE_UNKNOW;
}

bool CDlgServers::OnLogicStateChanged( const ToolFrame::MapLogicUpdate& vUpdate,uint uClientID )
{
	ToolFrame::MapLogicUpdate::const_iterator itr;
	foreach(itr,vUpdate){
		uint uServerID = itr->first;
		const ToolFrame::XLogicUpdate& xUpdate = itr->second;

		CLockRead lock(_vLogicNode.GetMutex());

		XLogicNode* pLogic = ToolFrame::GetPtrValueByKey(_vLogicNode.GetMap(),uServerID);
		ASSERT_LOG_ERROR(pLogic);

		CLockScoped lockLogic(pLogic->mutex);

		pLogic->uSendBytesTotal	+= xUpdate.uSendBytes;
		pLogic->uRecvBytesTotal	+= xUpdate.uRecvBytes;

		pLogic->uPackProcessTotal	+= xUpdate.nPacketProcess;
		pLogic->uLogicProcessTotal	+= xUpdate.nLogicProcess;
		pLogic->uNetProcessTotal	+= xUpdate.nNetProcess;

		if (!pLogic->bUpdated)
		{
			pLogic->bUpdated = true;
			_vLogicQueue.Push(pLogic);
		}
	}


	return true;
}

bool CDlgServers::OnPhysicalStateChanged( const ToolFrame::MapPhysicalUpdate& vUpdate,uint uClientID )
{
	ToolFrame::MapPhysicalUpdate::const_iterator itr;
	foreach(itr,vUpdate){
		uint uServerID = itr->first;
		const ToolFrame::XPhysicalUpdate& xUpdate = itr->second;

		const ToolFrame::XServerPhysical* pServer = _xTopologyControl.GetServersPhysical().FindPhysicalByPhysicalID(uServerID);

		ASSERT_LOG_ERROR(pServer);

		VectorString vString;
		vString.resize(COL_PHYSICAL_MAX);
		GetInfo(vString,pServer);
		int nRow = ApiMFC::FindString(_lcPhysicalServers,pServer->uPhysicalID,COL_PHYSICAL_ID);
		ApiMFC::SetRowString(_lcPhysicalServers,nRow,vString);
		//ApiMFC::SuitStringWidth(_lcPhysicalServers);

		DrawColorPhysical(nRow);
	}

	return true;
}

bool CDlgServers::GetInfo( VectorString& vString,const ToolFrame::XServerLogic* pServer ) const
{
	ASSERT_LOG_ERROR(pServer);

	const ToolFrame::XConfigServer* pConfigServer = _xTopologyControl.FindConfigServer(pServer->uServerID);
	ASSERT_LOG_ERROR(pConfigServer);

	const ToolFrame::XConfigLogic* pConfigSrvType = _xTopologyControl.FindConfigSrvType(pConfigServer->eSrvType);
	ASSERT_LOG_ERROR(pConfigSrvType);

	ToolFrame::SetValueByIndex(vString,COL_LOGIC_ID,			pServer->uServerID);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_TYPE,			_xTopologyControl.TranSrvType(pServer->eSrvType));
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_RUN_TYPE,		TranRunType(pConfigSrvType->eRunType));

	if (ToolFrame::RUN_TYPE_HASH == pConfigSrvType->eRunType)
		ToolFrame::SetValueByIndex(vString,COL_LOGIC_HASH,		(int)pConfigServer->uHash);

	ToolFrame::SetValueByIndex(vString,COL_LOGIC_PORT,			pConfigServer->uPort);

	ToolFrame::SetValueByIndex(vString,COL_LOGIC_PUBLIC_PORT,	pConfigServer->vPublicPort);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_PUBLIC_RECV,	pConfigSrvType->uPublicRecv);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_PUBLIC_SEND,	pConfigSrvType->uPublicSend);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_STATE,			TranState(pServer->xUpdate.eState));

	ToolFrame::SetValueByIndex(vString,COL_LOGIC_TIME_RUNONCE_AVG,	pServer->xUpdate.uTimeRunOnce);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_TIME_RUNONCE_MAX,	pServer->xUpdate.uTimeRunOnceMax);

	ToolFrame::SetValueByIndex(vString,COL_LOGIC_TIME_PROCESS_AVG,	pServer->xUpdate.uProcessAvg);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_TIME_PROCESS_MAX,	pServer->xUpdate.uProcessMax);

	ToolFrame::SetValueByIndex(vString,COL_LOGIC_TIME_SEND_AVG,		pServer->xUpdate.uTimeSendAvg);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_TIME_SEND_MAX,		pServer->xUpdate.uTimeSendMax);

	ToolFrame::SetValueByIndex(vString,COL_LOGIC_TIME_SENDING_AVG,	pServer->xUpdate.uTimeSendingAvg);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_TIME_SENDING_MAX,	pServer->xUpdate.uTimeSendingMax);

	ToolFrame::SetValueByIndex(vString,COL_LOGIC_CACHE_VAILD,		pServer->xUpdate.uCacheVaild);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_CACHE_TOTAL,		pServer->xUpdate.uCacheTotal > pServer->xUpdate.uCacheVaild ?  pServer->xUpdate.uCacheTotal - pServer->xUpdate.uCacheVaild : 0);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_PROCESSER_COUNT,	pServer->xUpdate.uProcesserCount);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_QUEUE_PROCESS,		pServer->xUpdate.uQueueProcess);
	
	if (pConfigSrvType->uTimeInterval > 0)
	{
		uint uFree = (uint)(1.f*pServer->xUpdate.uFreeTime/pConfigSrvType->uTimeInterval*100);
		if (uFree>100)uFree=100;
		ToolFrame::SetValueByIndex(vString,COL_LOGIC_FREE_TIME,		100 - uFree);
	}

	ToolFrame::SetValueByIndex(vString,COL_LOGIC_CPU_TIME,		ToolFrame::TimeToRead(pServer->xUpdate.uCpuUseTime));
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_CPU_USAGE,		(uint)pServer->xUpdate.uCpuUsage);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_MEM_USED,		ToolFrame::ValueToRead(pServer->xUpdate.uMemoryUsed/1024));
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_THREADS,		(uint)pServer->xUpdate.uThreads);

	ToolFrame::SetValueByIndex(vString,COL_LOGIC_PHYSICAL_ID,	pConfigServer->uPhysicalID);

	ToolFrame::SetValueByIndex(vString,COL_LOGIC_TIME_STARTUP,	ToolFrame::TimeToString(pServer->uTimeStartUp,			"hh:mm:ss"));
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_TIME_REPROT,	ToolFrame::TimeToString(pServer->xUpdate.uTimeReport,	"hh:mm:ss"));
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_TIME_SAVE,		ToolFrame::TimeToString(pServer->xUpdate.uTimeSave,		"hh:mm:ss"));
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_TIME_CLEAN_UP,	ToolFrame::TimeToString(pServer->xUpdate.uTimeCleanUp,	"hh:mm:ss"));
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_SYSTEM_CLEANUP,ToolFrame::TimeToString(pServer->xUpdate.uSystemCleanUp,"hh:mm:ss"));
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_RECONNECT,		pServer->uReconnect);

	if (pConfigSrvType->uTimeInterval >0)
	{
		ToolFrame::SetValueByIndex(vString,COL_LOGIC_SEND_BYTES,ToolFrame::ValueToRead(pServer->xUpdate.uSendBytes/ (pConfigSrvType->uTimeInterval/1000)));
		ToolFrame::SetValueByIndex(vString,COL_LOGIC_RECV_BYTES,ToolFrame::ValueToRead(pServer->xUpdate.uRecvBytes/ (pConfigSrvType->uTimeInterval/1000)));
	}

	ToolFrame::SetValueByIndex(vString,COL_LOGIC_SESSION,		pServer->xUpdate.nSessionNum);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_PACK_PROCESS,	pServer->xUpdate.nPacketProcess);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_LOGIC_PROCESS,	pServer->xUpdate.nLogicProcess);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_NET_PROCESS,	pServer->xUpdate.nNetProcess);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_LOGIC_CMD,		pServer->xUpdate.nLogicCmd);
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_NET_CMD,		pServer->xUpdate.nNetCmd);

	//补充所有其他没有更新的项为 空
	for (int nCol = COL_LOGIC_ID;nCol<COL_LOGIC_MAX;++nCol)
	{
		if (!ToolFrame::IsVaildIndex(vString,nCol))
			ToolFrame::SetValueByIndex(vString,nCol,"");
	}

	return true;
}

bool CDlgServers::GetInfo( VectorString& vString,XLogicNode* pNode )
{
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_SEND_BYTES_TOTAL,		ToolFrame::ValueToRead(pNode->uSendBytesTotal));
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_RECV_BYTES_TOTAL,		ToolFrame::ValueToRead(pNode->uRecvBytesTotal));

	ToolFrame::SetValueByIndex(vString,COL_LOGIC_PACK_PROCESS_TOTAL,	ToolFrame::ValueToRead(pNode->uPackProcessTotal));
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_LOGIC_PROCESS_TOTAL,	ToolFrame::ValueToRead(pNode->uLogicProcessTotal));
	ToolFrame::SetValueByIndex(vString,COL_LOGIC_NET_PROCESS_TOTAL,		ToolFrame::ValueToRead(pNode->uNetProcessTotal));

	const ToolFrame::XServerLogic* pLogic = _xTopologyControl.GetServersLogic().FindLogicByServerID(pNode->uServerID);
	ASSERT_LOG_ERROR(pLogic);
	return GetInfo(vString,pLogic);
}

bool CDlgServers::GetInfo( VectorString& vString,const ToolFrame::XServerPhysical* pServer ) const
{
	ToolFrame::SetValueByIndex(vString,COL_PHYSICAL_ID,			pServer->uPhysicalID);
	ToolFrame::SetValueByIndex(vString,COL_PHYSICAL_STATE,		TranState(pServer->xUpdate.eState));
	ToolFrame::SetValueByIndex(vString,COL_PHYSICAL_CPU_USAGE,	(int)pServer->xUpdate.uCpuUsage);
	ToolFrame::SetValueByIndex(vString,COL_PHYSICAL_MEM_USED,	ToolFrame::ValueToRead(pServer->xUpdate.uMemoryUsed/1024));
	ToolFrame::SetValueByIndex(vString,COL_PHYSICAL_MEM_FREE,	ToolFrame::ValueToRead(pServer->xUpdate.uMemoryFree/1024));
	ToolFrame::SetValueByIndex(vString,COL_PHYSICAL_MEM_USAGE,	(int)pServer->xUpdate.uMemoryUsage);
	ToolFrame::SetValueByIndex(vString,COL_PHYSICAL_IP,			pServer->sIP);
	ToolFrame::SetValueByIndex(vString,COL_PHYSICAL_MAC,		pServer->sMac);
	ToolFrame::SetValueByIndex(vString,COL_PHYSICAL_CLEANUP,	ToolFrame::TimeToString(pServer->xUpdate.uSystemCleanUp,	"hh:mm:ss"));
	ToolFrame::SetValueByIndex(vString,COL_PHYSICAL_RECONNECT,	pServer->uReconnect);

	ToolFrame::SetValueByIndex(vString,COL_PHYSICAL_SEND_BYTES,	ToolFrame::ValueToRead(pServer->xUpdate.uSendBytes/ 1024));
	ToolFrame::SetValueByIndex(vString,COL_PHYSICAL_RECV_BYTES,	ToolFrame::ValueToRead(pServer->xUpdate.uRecvBytes/ 1024));
	ToolFrame::SetValueByIndex(vString,COL_PHYSICAL_TOTAL_BYTES,ToolFrame::ValueToRead((pServer->xUpdate.uSendBytes + pServer->xUpdate.uRecvBytes)/ 1024));

	//ToolFrame::SetValueByIndex(vString,COL_PHYSICAL_REMARK,		pServer->);

	//补充所有其他没有更新的项为 空
	for (int nCol = COL_PHYSICAL_ID;nCol<COL_PHYSICAL_MAX;++nCol)
	{
		if (!ToolFrame::IsVaildIndex(vString,nCol))
			ToolFrame::SetValueByIndex(vString,nCol,"");
	}

	return true;
}

bool CDlgServers::UpdateUI()
{
	XLogicNode* pLogic = _vLogicQueue.PopBackPtr();
	if (!pLogic)return false;

	CLockScoped lockLogic(pLogic->mutex);
	
	ASSERT_LOG_ERROR(pLogic->bUpdated);
	pLogic->bUpdated = false;
	
	VectorString vString;
	vString.resize(COL_LOGIC_MAX);
	GetInfo(vString,pLogic);
	int nRow = ApiMFC::FindString(_lcLogicServers,pLogic->uServerID,COL_LOGIC_ID);
	ApiMFC::SetRowString(_lcLogicServers,nRow,vString);
	//ApiMFC::SuitStringWidth(_lcLogicServers);

	DrawColorLogic(nRow);
	return true;
}

bool CDlgServers::OnSystemProcess(uint64 uTime)
{
	ToolFrame::CTimeOut timeSystemProcess(uTime);

	//处理协议
	ToolFrame::MProtocol::Singleton().ProcessNet(100);
	ToolFrame::MProtocol::Singleton().ProcessLogic(100);

	if (_xTimeOutUI.TryTimeOutRestart())
	{
		//处理UI
		ToolFrame::CTimeOut timeOut(50);
		while (!timeOut.IsTimeOut() && UpdateUI());

		//更新子窗口的UI
		if (_pDlgTotalServer)
			_pDlgTotalServer->UpdateUI();
	}
	return timeSystemProcess.IsTimeOut();
}

bool CDlgServers::OnLogMsg( const std::string& sLogLevel,const std::stringstream& sStreamLog )
{
	return true;
}

void CDlgServers::OnBnClickedUploadAndStart()
{
	if (!_xTopologyControl.IsAuthorized())
	{
		ApiMFC::ApiMessageBox("初始化未完成,请稍后","确定",MB_ICONASTERISK|MB_OK);
		return;
	}

	if (IDOK == ApiMFC::ApiMessageBox("您即将【初始化启动服务器组】","确定",MB_ICONQUESTION|MB_OKCANCEL))
	{
		//设置并发送服务器配置
		_xTopologyControl.SendServerConfig();
	
		//启动服务器实例
		ToolFrame::MapConfigServer::const_iterator itr;
		foreach(itr,_xTopologyControl.GetConfigServer()){
			const ToolFrame::XConfigServer& xServer = itr->second;

			if (!_xTopologyControl.IsLogicOnline(xServer.uServerID))
				_xTopologyControl.SendPhysicalStartServer(xServer.uServerID);
		}
	}
}

void CDlgServers::OnBnClickedUploadConfig()
{
	if (IDOK == ApiMFC::ApiMessageBox("您即将【上传】服务器配置","确定",MB_ICONQUESTION|MB_OKCANCEL))
	{
		//设置并发送服务器配置
		_xTopologyControl.SendServerConfig();
	}
}

void CDlgServers::OnBnClickedStartServer()
{
	VectorUint32 vServerID;
	if (LogicGetSelectedServerID(vServerID))
	{
		if (IDOK != ApiMFC::ApiMessageBox("您即将启动【选择】的服务器","确定",MB_ICONQUESTION|MB_OKCANCEL))
			return ;
	}else{
		LogicAllServerID(vServerID);
		if (IDOK != ApiMFC::ApiMessageBox("您即将启动【所有离线】的服务器","确定",MB_ICONQUESTION|MB_OKCANCEL))
			return ;
	}
	
	VectorUint32::const_iterator itr;
	foreach(itr,vServerID){
		uint32 uServerID = *itr;
		if (!_xTopologyControl.IsLogicOnline(uServerID))
			_xTopologyControl.SendPhysicalStartServer(uServerID);
	}
}

void CDlgServers::OnBnClickedSaveServer()
{
	VectorUint32 vServerID;
	if (LogicGetSelectedServerID(vServerID))
	{
		if (IDOK != ApiMFC::ApiMessageBox("您即将 保存【选择】的服务器数据","确定",MB_ICONQUESTION|MB_OKCANCEL))
			return ;
	}else{
		LogicAllServerID(vServerID);
		if (IDOK != ApiMFC::ApiMessageBox("您即将 保存【所有正常】的服务器数据","确定",MB_ICONQUESTION|MB_OKCANCEL))
			return ;
	}

	VectorUint32::const_iterator itr;
	foreach(itr,vServerID){
		uint32 uServerID = *itr;
		if (_xTopologyControl.IsLogicOnline(uServerID))
			_xTopologyControl.SendLogicSaveServer(uServerID);
	}
}

void CDlgServers::OnBnClickedCleanUpServer()
{
	VectorUint32 vServerID;
	if (LogicGetSelectedServerID(vServerID))
	{
		if (IDOK != ApiMFC::ApiMessageBox("您即将 清理【选择】的服务器缓存","确定",MB_ICONQUESTION|MB_OKCANCEL))
			return ;
	}else{
		LogicAllServerID(vServerID);
		if (IDOK != ApiMFC::ApiMessageBox("您即将 清理【所有正常】的服务器缓存","确定",MB_ICONQUESTION|MB_OKCANCEL))
			return ;
	}

	VectorUint32::const_iterator itr;
	foreach(itr,vServerID){
		uint32 uServerID = *itr;
		if (_xTopologyControl.IsLogicOnline(uServerID))
			_xTopologyControl.SendLogicCleanUpServer(uServerID);
	}
}

void CDlgServers::OnBnClickedStopService()
{
	VectorUint32 vServerID;
	if (LogicGetSelectedServerID(vServerID))
	{
		if (IDOK != ApiMFC::ApiMessageBox("您即将 停止【选择】的服务器服务","确定",MB_ICONQUESTION|MB_OKCANCEL))
			return ;
	}else{
		LogicAllServerID(vServerID);
		if (IDOK != ApiMFC::ApiMessageBox("您即将 停止【所有正常】的服务器服务","确定",MB_ICONQUESTION|MB_OKCANCEL))
			return ;
	}

	VectorUint32::const_iterator itr;
	foreach(itr,vServerID){
		uint32 uServerID = *itr;
		if (_xTopologyControl.IsLogicOnline(uServerID))
			_xTopologyControl.SendLogicStopService(uServerID);
	}
}

void CDlgServers::OnBnClickedShutDown()
{
	VectorUint32 vServerID;
	if (LogicGetSelectedServerID(vServerID))
	{
		if (IDOK != ApiMFC::ApiMessageBox("您即将 关闭【选择】的服务器","确定",MB_ICONQUESTION|MB_OKCANCEL))
			return ;
	}else{
		LogicAllServerID(vServerID);
		if (IDOK != ApiMFC::ApiMessageBox("您即将 关闭【所有正常】的服务器","确定",MB_ICONQUESTION|MB_OKCANCEL))
			return ;
	}

	VectorUint32::const_iterator itr;
	foreach(itr,vServerID){
		uint32 uServerID = *itr;
		if (_xTopologyControl.IsLogicOnline(uServerID))
			_xTopologyControl.SendLogicShutDown(uServerID);
	}
}

bool CDlgServers::OnAuthorizationRep( bool bAuthorized,time_t uTimeStart )
{
	if (bAuthorized)
	{
		ApiMFC::SetWindowText(_cStcStartTime,ToolFrame::TimeToString(uTimeStart));
	}
	
	return true;
}


void CDlgServers::OnCbnSelchangeOperator()
{
	uint nServerID = INVALID_ID;
	ApiMFC::GetItemText(_lcLogicServers,_lcLogicServers.GetEditRow(),COL_LOGIC_ID,nServerID);

	switch(_cCmbOperator.GetCurSel())
	{
	case 0:
		break;
	case 1:
		_xTopologyControl.SendPhysicalStartServer(nServerID);
		break;
	case 2:
		_xTopologyControl.SendLogicSaveServer(nServerID);
		break;
	case 3:
		_xTopologyControl.SendLogicCleanUpServer(nServerID);
		break;
	case 4:
		_xTopologyControl.SendLogicStopService(nServerID);
		break;
	case 5:
		_xTopologyControl.SendLogicShutDown(nServerID);
		break;
	}
}

bool CDlgServers::OnConnectStateChanged( int eState )
{
	std::stringstream sStream;
	sStream<<_sTitle;

	if (!_xTopologyControl.GetServerGroupID().empty())
		sStream <<" ServerTag:" << _xTopologyControl.GetServerTag();
	
	if (!_xTopologyControl.GetServerZoneID().empty())
		sStream	<<" ServerZoneID:"<<_xTopologyControl.GetServerZoneID();

	if (!_xTopologyControl.GetServerGroupID().empty())
		sStream	<<" ServerGroupID:"<<_xTopologyControl.GetServerGroupID();

	sStream<<" "<<_xTopologyControl.GetConnectedCenterAddress()<<"("<<TranMonitorState(eState)<<")";

	ApiMFC::SetTitle(*this,sStream.str());
	return true;
}

std::string CDlgServers::TranMonitorState( int eState ) const
{
	switch (eState)
	{
	case ToolFrame::CConnectMonitor::STATE_CONNECT:
		return "连接中";
		break;
	case ToolFrame::CConnectMonitor::STATE_NORMAL:
		return "已连接";
		break;
	case ToolFrame::CConnectMonitor::STATE_STOPING:
		return "停止中";
		break;
	case ToolFrame::CConnectMonitor::STATE_STOP:
		return "已停止";
		break;
	case ToolFrame::CConnectMonitor::STATE_RECONNECT:
		return "重连中";
		break;
	}

	return "未知";
}

std::string CDlgServers::TranRunType( int eRunType ) const
{
	switch (eRunType)
	{
	case ToolFrame::RUN_TYPE_RANDOM:
		return "随机";
		break;
	case ToolFrame::RUN_TYPE_HASH:
		return "哈希";
		break;
	case ToolFrame::RUN_TYPE_UNIQUE:
		return "唯一";
		break;
	case ToolFrame::RUN_TYPE_BALANCE:
		return "平衡";
		break;
	case ToolFrame::RUN_TYPE_SEQUENCE:
		return "顺序";
		break;
	}

	return "未知";
}

bool CDlgServers::InitReportData()
{
	ApiMFC::DeleteItem(_lcLogicServers);

	//展示 逻辑 服务器 初始数据
	{
		const ToolFrame::MapConfigServer& vConfigServer = _xTopologyControl.GetConfigServer();
		ToolFrame::MapConfigServer::const_iterator itr;
		foreach(itr,vConfigServer){
			const ToolFrame::XConfigServer& xConfigServer = itr->second;

			const ToolFrame::XConfigLogic* pConfigLogic = _xTopologyControl.FindConfigSrvType(xConfigServer.eSrvType);
			ASSERT_LOG_ERROR(pConfigLogic);

			MapIntString vString;

			ToolFrame::InsertString(vString,COL_LOGIC_ID,			xConfigServer.uServerID);
			ToolFrame::InsertString(vString,COL_LOGIC_TYPE,			_xTopologyControl.TranSrvType(xConfigServer.eSrvType));
			ToolFrame::InsertString(vString,COL_LOGIC_RUN_TYPE,		TranRunType(pConfigLogic->eRunType));

			if (ToolFrame::RUN_TYPE_HASH == pConfigLogic->eRunType)
				ToolFrame::InsertString(vString,COL_LOGIC_HASH,		(int)xConfigServer.uHash);

			ToolFrame::InsertString(vString,COL_LOGIC_PORT,			xConfigServer.uPort);

			ToolFrame::InsertString(vString,COL_LOGIC_PUBLIC_PORT,	xConfigServer.vPublicPort);
			ToolFrame::InsertString(vString,COL_LOGIC_PUBLIC_RECV,	pConfigLogic->uPublicRecv);
			ToolFrame::InsertString(vString,COL_LOGIC_PUBLIC_SEND,	pConfigLogic->uPublicSend);

			ToolFrame::InsertString(vString,COL_LOGIC_STATE,		TranState(ToolFrame::CONNECT_STATE_OFFLINE));
			ToolFrame::InsertString(vString,COL_LOGIC_PHYSICAL_ID,	xConfigServer.uPhysicalID);

			ApiMFC::SetRowString(_lcLogicServers,-1,vString);
		}

		ApiMFC::SuitStringWidth(_lcLogicServers);
	}

	return true;
}

bool CDlgServers::LogicGetSelectedServerID( VectorUint32& vServerID ) const
{
	VectorInt vRows;
	ApiMFC::GetSelRows(_lcLogicServers,vRows);
	VectorInt::const_iterator itr;
	foreach(itr,vRows){
		uint32 uServerID = INVALID_ID;
		ApiMFC::GetItemText(_lcLogicServers,*itr,COL_LOGIC_ID,uServerID);

		vServerID.push_back(uServerID);
	}
	return !vServerID.empty();
}

bool CDlgServers::LogicAllServerID( VectorUint32& vServerID ) const
{
	int nRows = _lcLogicServers.GetItemCount();
	for (int nRow = 0;nRow < nRows;++nRow)
	{
		uint32 uServerID = INVALID_ID;
		ApiMFC::GetItemText(_lcLogicServers,nRow,COL_LOGIC_ID,uServerID);

		vServerID.push_back(uServerID);
	}

	return !vServerID.empty();
}

bool CDlgServers::PhysicalGetSelectedServerID( VectorUint32& vPhysicalID ) const
{
	VectorInt vRows;
	ApiMFC::GetSelRows(_lcPhysicalServers,vRows);
	VectorInt::const_iterator itr;
	foreach(itr,vRows){
		uint32 uServerID = INVALID_ID;
		ApiMFC::GetItemText(_lcPhysicalServers,*itr,COL_PHYSICAL_ID,uServerID);

		vPhysicalID.push_back(uServerID);
	}
	return !vPhysicalID.empty();
}

bool CDlgServers::PhysicalGetAllServerID( VectorUint32& vPhysicalID ) const
{
	int nRows = _lcPhysicalServers.GetItemCount();
	for (int nRow = 0;nRow < nRows;++nRow)
	{
		uint32 uServerID = INVALID_ID;
		ApiMFC::GetItemText(_lcPhysicalServers,nRow,COL_PHYSICAL_ID,uServerID);

		vPhysicalID.push_back(uServerID);
	}

	return !vPhysicalID.empty();
}

bool CDlgServers::DrawColorLogic(int nRow)
{
	if (_vWarningColor.empty())return false;

	//先根据服务器状态 然后 再根据 其他属性 上色
	std::string sWarningLevel;

	std::string sState;
	ApiMFC::GetItemText(_lcLogicServers,nRow,COL_LOGIC_STATE,sState);

	sWarningLevel = ToolFrame::GetValueByKey(_vWarningLogicState,sState,ToolFrame::EmptyString());

	if (SERVER_STATE_NORMAL == sState)
	{
		//根据压力 大小 进行上色
		int uValue = 0;
		ApiMFC::GetItemText(_lcLogicServers,nRow,COL_LOGIC_FREE_TIME,uValue);
		const std::string* pWarning = ToolFrame::GetLowerPtrMap(_vWarningLogicPressure,uValue);
		if (pWarning)
			sWarningLevel = *pWarning;
	}

	const XWarningColor* pWarningColor = ToolFrame::GetValuePtrByKey(_vWarningColor,sWarningLevel);
	if (pWarningColor)
	{
		_lcLogicServers.SetRowTextColor(nRow,pWarningColor->clrText);
		_lcLogicServers.SetRowTextBgColor(nRow,pWarningColor->clrTextBg);
	}

	return true;
}

bool CDlgServers::DrawColorPhysical(int nRow)
{
	if (_vWarningColor.empty())return false;

	if (_vWarningPhysical.empty())return false;

	//根据内存使用率 进行上色
	int uValue = 0;
	ApiMFC::GetItemText(_lcPhysicalServers,nRow,COL_PHYSICAL_MEM_USAGE,uValue);

	const std::string* pWarning = ToolFrame::GetLowerPtrMap(_vWarningPhysical,uValue);
	if (!pWarning)return false;

	const XWarningColor* pWarningColor = ToolFrame::GetValuePtrByKey(_vWarningColor,*pWarning);
	if (pWarningColor)
	{
		_lcPhysicalServers.SetRowTextColor(nRow,pWarningColor->clrText);
		_lcPhysicalServers.SetRowTextBgColor(nRow,pWarningColor->clrTextBg);
	}
	return true;
}


void CDlgServers::OnBnClickedPhysicalMemoryClear()
{
	VectorUint32 vPhysicalID;
	
	if (PhysicalGetSelectedServerID(vPhysicalID))
	{
		if (IDOK == ApiMFC::ApiMessageBox("您即将 清理内存【选择】的物理服务器","确定",MB_ICONQUESTION|MB_OKCANCEL))
			return ;
	}else{
		PhysicalGetAllServerID(vPhysicalID);
		if (IDOK != ApiMFC::ApiMessageBox("您即将 清理内存【所有】的物理服务器","确定",MB_ICONQUESTION|MB_OKCANCEL))
			return ;
	}

	VectorUint32::const_iterator itr;
	foreach(itr,vPhysicalID){
		_xTopologyControl.SendPhysicalMemoryClear(*itr);
	}
}


void CDlgServers::OnBnClickedPhysicalReboot()
{
	VectorUint32 vPhysicalID;

	if (PhysicalGetSelectedServerID(vPhysicalID))
	{
		if (IDOK == ApiMFC::ApiMessageBox("您即将 重启【选择】的物理服务器","确定",MB_ICONQUESTION|MB_OKCANCEL))
			return ;
	}else{
		PhysicalGetAllServerID(vPhysicalID);
		if (IDOK != ApiMFC::ApiMessageBox("您即将 重启【所有】的物理服务器","确定",MB_ICONQUESTION|MB_OKCANCEL))
			return ;
	}

	VectorUint32::const_iterator itr;
	foreach(itr,vPhysicalID){
		_xTopologyControl.SendPhysicalReboot(*itr);
	}
}


void CDlgServers::OnCbnSelchangeSolution()
{
	if (!ReadConfigSolution(ApiMFC::GetWindowText(_cCmbSolution)))
		ApiMFC::ApiMessageBox("配置表错误", "错误");

	InitReportData();	//初始化报表的数据
}

void CDlgServers::OnBnClickedTotalServer()
{
	if (_pDlgTotalServer)
	{
		_pDlgTotalServer = ApiMFC::DestoryDlg(_pDlgTotalServer);
	}
	else {
		_pDlgTotalServer = ApiMFC::CreateDlg<CDlgServerTotal>(this);
	}
}

bool CDlgServers::OnTotalWndClosed()
{
	_pDlgTotalServer = nullptr;
	return true;
}

bool CDlgServers::OnDebugWndClosed()
{
	_pDlgDebug = nullptr;
	return true;
}

const CDlgServers::MapLogicNode& CDlgServers::GetLogicNode() const
{
	return _vLogicNode;
}

const ToolFrame::CTopologyControl& CDlgServers::GetTopologyControl() const
{
	return _xTopologyControl;
}

void CDlgServers::OnBnClickedServersDebug()
{
	if (_pDlgDebug)
	{
		_pDlgDebug = ApiMFC::DestoryDlg(_pDlgDebug);
	}
	else {
		_pDlgDebug = ApiMFC::CreateDlg<CDlgDebug>(this);
	}
}
