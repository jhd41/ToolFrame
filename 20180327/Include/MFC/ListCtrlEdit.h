#pragma once

#include "Macro.h"

#ifdef MACRO_LIB_MFC


#include <afxcontrolbars.h> 
#include <afxcmn.h>
#include <afxwin.h>

//思路:
//响应双击事件,生成一个输入文本框,当离开这个输入文本框焦点时,销毁文本框，并把值保存到双击时的位置

NS_TOOL_FRAME_BEGIN

class CListCtrlEdit;
class IEditing{
private:
	CListCtrlEdit* _pcLcEdt;
public:
	void SetParentListCtrl(CListCtrlEdit* pLc);
	CListCtrlEdit* GetParentListCtrl();
public:
	virtual void OnPrepair();
	virtual void OnSetFocus(int nRow,int nCol,const CString& csString);
	virtual void OnKillFocus(CString& csString);
public:
	int GetEditRow()const;
	int GetEditCol()const;
public:
	IEditing();
	virtual ~IEditing();
private:
	int _nRow;
	int _nCol;
};
class CListEdit
	:public CEdit
	,public IEditing
{
public:
	virtual void OnPrepair();
	virtual void OnSetFocus(int nRow,int nCol,const CString& csString);
	virtual void OnKillFocus(CString& csString);

	afx_msg virtual void OnKeyDown(UINT   nChar,   UINT   nRepCnt,   UINT   nFlags);

	DECLARE_MESSAGE_MAP()
private:
	void SuitStringShow(const std::string& sText );
	void SetUnitRect();
public:
	CListEdit(){}
	virtual ~CListEdit(){}
private:
	CRect rUnit;//单位窗口
};

class CListCmb
	:public CComboBox
	,public IEditing
{
public:
	virtual void OnSetFocus(int nRow,int nCol,const CString& csString);
	virtual void OnKillFocus(CString& csString);
public:
	CListCmb(){}
	virtual ~CListCmb(){}
};

class TOOLFRAME_DLL CListCtrlEdit
	:public CListCtrl
{
public:
	enum ESortRule{
		SORT_NULL,				//不可排序
		SORT_BOOL,				//布尔
		SORT_NUMBER,			//带符号整数
		SORT_NUMBER_N,			//无符号整数
		SORT_NUMBER_READ_3,		//无符号 以3位 为分割单位 数字排序 1,000 4,256 55,323,665
		SORT_NUMBER_READ_4,		//无符号 以4位 为分割单位 数字排序 1,1000 1,4256 1,5532,3665
		SORT_STRING,			//字符串
		SORT_DATETIME,			//日期时间
		SORT_DATE,				//日期
		SORT_TIME,				//时间
		SORT_TYPE_MAX
	};

	struct XEditingInfo 
	{
		std::string sTitle;		//标题栏
		IEditing*	iEditing;	//编辑时显示的窗口指针
		int			nSortType;	//排序时的类型
		BOOL		bOriginal;	//是否保持原窗口大小
		XEditingInfo(){
			iEditing = nullptr;
			nSortType = SORT_NULL;
			bOriginal = FALSE;
		}
	};
	typedef std::vector<XEditingInfo> VectorEditingInfo;//<列,信息>
public:
	typedef bool (*FnCompare)(const std::string& sSrc, const std::string& sDes);
	typedef std::map<int,std::vector<CString> > MapCopy;//<nRow,内容>
	typedef std::map<int,FnCompare>				MapComparePtr;
	typedef std::map<int,COLORREF>				MapRowColor;

	//对外公开函数
public:
	void SetTitle(int nCol, const std::string& sTitle,int nSortType = SORT_NULL,IEditing* iEditing = nullptr,BOOL bOriginal = FALSE,BOOL bParent = TRUE);
	void Init();
public:
	CListEdit*	CreateCtlEdit(uint uControlID = 0);
	CListCmb*	CreateCtlComboBox(uint uControlID = 0);
	bool		DestoryCtl(IEditing* pControl);
public:
	BOOL IsEditing(){return nullptr == _iEditing;}	//是否编辑中
	void SetEditing(IEditing* iEditing){_iEditing = iEditing;}
	IEditing* GetEditing(){return _iEditing;}

	void SetSuitWidth(BOOL bSuit=TRUE){_bSuitWidth = bSuit;}
	BOOL IsSuitWidth(){return _bSuitWidth;}

	BOOL SetExtraLine(BOOL bExtra = TRUE);
	BOOL ExtraLineAdd();	//添加额外的空白行(用于做添加操作)
	BOOL ExtraLineRemove();	//移除额外的空白行

	void SetCompareFun(int nType,FnCompare pfn);//设置排序函数指针

	int	 GetEditRow()const;
	int	 GetEditCol()const;

	bool SetRowTextColor(int nRow,COLORREF clr);
	bool SetRowTextBgColor(int nRow,COLORREF clr);
	
public:
	BOOL DeleteItem(int nItem);
	BOOL DeleteAllItems();

	//重载函数
private:
	DECLARE_MESSAGE_MAP()

private:
	afx_msg virtual void PreSubclassWindow();

	//编辑相关
	afx_msg virtual void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg virtual void OnSetFocus(CWnd* pOldWnd);
	virtual void DisposeEdit(IEditing* iEditing);

	//删除相关
	void CopyToMem();
	afx_msg virtual void OnKeyDown(UINT   nChar,   UINT   nRepCnt,   UINT   nFlags);

	//拖动相关
	afx_msg virtual void OnLvnBeginrdrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg virtual void OnLButtonUp(UINT nFlags, CPoint point);
	
	//排序相关
	afx_msg void OnLvnColumnclickList(NMHDR *pNMHDR, LRESULT *pResult);
	static int CALLBACK ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	static	bool CompareBool(const std::string& sSrc, const std::string& sDes);
	static  bool CompareNumber(const std::string& sSrc, const std::string& sDes);
	static  bool CompareNumberN(const std::string& sSrc, const std::string& sDes);
	static  bool CompareString(const std::string& sSrc, const std::string& sDes); 
	static  bool CompareDateTime(const std::string& sSrc, const std::string& sDes);
	static  bool CompareDate(const std::string& sSrc, const std::string& sDes);
	static  bool CompareTime(const std::string& sSrc, const std::string& sDes);

	static  bool CompareNumberRead3(const std::string& sSrc, const std::string& sDes);
	static  bool CompareNumberRead4(const std::string& sSrc, const std::string& sDes);

	//自定义绘制
	virtual void OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnPaint();
	virtual BOOL OnEraseBkgnd(CDC* pDC);
public:
	CListCtrlEdit(void);
	virtual ~CListCtrlEdit(void);
private:
	VectorEditingInfo	_vInfo;
	MapRowColor			_vColorRowText;		//行 文本 颜色
	MapRowColor			_vColorRowTextBg;	//行 文本 背景 颜色
	BOOL				_bExtraLine;

	CPoint _ptItem;			//编辑中的物品行列

	BOOL _bSuitWidth;
	IEditing* _iEditing;	//正在编辑中的控件
	BOOL _bDragging;		//是否拖动中
	BOOL _bAsc;             //用来设置是升序排列还是降序排列
	int _nSortedCol;        //用来记录被点击的是哪一列
	FnCompare _fnCompare; //排序函数

	MapCopy _vCopy;			//复制粘贴时的临时容器(以后复制到剪切板)
	MapComparePtr _vComparePtr;//<排序类型,排序函数>
};

NS_TOOL_FRAME_END

#endif // MACRO_LIB_MFC
