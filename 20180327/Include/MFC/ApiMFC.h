#pragma once
#include "Macro.h"

#ifdef MACRO_LIB_MFC

#include <afxwin.h>
#include <afxcmn.h>
#include <afxdtctl.h>
#include <atlimage.h>
#include <afxdlgs.h>
#include <afxdd_.h>

#include "ToolStd.h"
#include "Date.h"
#include "DateTime.h"

#define MMessageBox(text,caption,mb) {std::stringstream sStream;sStream<<text;MessageBox(sStream.str().c_str(),caption,mb);}

//概念定义:
//Update:	从视图更新到内部变量
//Show:		从内部变量更新到视图

class TOOLFRAME_DLL ApiMFC
{
public:
	//界面操作函数

	//对话框 - 标题
	static bool SetTitle(CWnd& cDlg, const std::string& sNickName);
	static bool SetTitle(CWnd* pWnd, const std::string& sNickName);
	static bool SetTitle(CPropertySheet& cDlg, const std::string& sNickName, uint uStyle = 0);

	//通用设置 - 设置窗口是否有效
	static bool EnableWindow(CWnd& wnd, BOOL bEnable);

	//通用设置 - 判断窗口是否有效
	static bool IsWindowEnabled(const CWnd& wnd);

	//通用设置 - 设置为焦点
	static bool SetFocus(CWnd& wnd);

	//通用设置 - 设置窗口文本
	template<typename TValue>
	static bool SetWindowText(CWnd& wnd, const TValue& tValue);
	static bool SetWindowText(CWnd& wnd, const std::string& tValue);
	//通用设置 - 设置选中状态
	static int SetSelected(CListBox& cBox, int nIndex = 0);
	static int SetSelected(CComboBox& cBox, int nIndex = 0);
	static int SetSelected(CComboBox& cBox, const std::string& sValue, bool bSet = false);//设置控件为选中状态 如果 没有在列表中找到 则自动设置显示该文本
	static int SetSelected(CComboBox& cBox, const CString& sValue, bool bSet = false);//设置控件为选中状态 如果 没有在列表中找到 则自动设置显示该文本
																					  //通用设置 - 设置选中状态
	static bool SetSelected(CListCtrl& cBox);
	static bool SetSelected(CListCtrl& cBox, int nRow);
	//通用设置 - 取消选中状态
	static bool SetNotSel(CListCtrl& cBox);
	static bool SetNotSel(CListCtrl& cBox, int nRow);
	static bool SetNotSel(CListBox& cBox);
	static bool SetNotSel(CListBox& cBox, int nRow);
	//通用设置 - 设置/取消选中状态
	static bool SetSel(CListCtrl& cBox, int nRow, bool bTrue);
	//通用设置 - 获取选中行
	static bool GetSelRows(const CListCtrl& cBox, VectorInt& vVct);
	static bool GetSelRows(const CListCtrl& cBox, SetInt& vVct);
	static bool GetSelRows(const CListBox& cBox, VectorInt& vVct);
	static bool GetSelRows(const CListBox& cBox, SetInt& vVct);
	//通用设置 - 增加一条字符串
	static bool AddString(CComboBox& cWnd, const std::string& sString);
	static bool AddString(CListBox& cWnd, const std::string& sString);
	template<typename T>
	static bool AddString(CComboBox& cWnd, const T& t);
	//列表控件 - 删除全部内容
	static void DeleteItem(CListBox& cBox);
	static void DeleteItem(CComboBox& cBox);
	static uint DeleteItem(CComboBox& cBox, const std::string& sValue, int nCount = -1);
	template<typename T>
	static uint DeleteItem(CComboBox& cBox, const T& t, int nCount = -1);

	//特殊设置
	//时间拾取器 - 设置格式
	static void		SetFormatDataTime(CDateTimeCtrl& cCtl);
	//时间拾取器 - 设置/获得时间
	static void		SetTime(CDateTimeCtrl& cCtl, time_t nTime);
	static time_t	GetTime(const CDateTimeCtrl& cCtl);

	//编辑框 - 设置字符串长度
	static void SetLimitText(CEdit& cWnd, UINT uMax);
	//编辑框 - 在光标处添加字符串(如果有选中字符，则会被替换掉。)
	static void InsertString(CEdit& cWnd, const std::string& sString);
	//编辑框 - 获得添加之后的字符串(如果有选中字符，则会被替换掉。)
	static std::string GetInsertString(CEdit& cWnd, const std::string& sString);

	//复选框 - 复选状态
	static bool IsChecked(CButton& cBox);
	static bool SetChecked(CButton& cBox, BOOL bCheck = TRUE);
	static bool SetChecked(CWnd* pWnd,int nID, BOOL bCheck = TRUE);

	//组合框 - 是否已经存在
	static bool IsExists(const CComboBox& cBox, const std::string& sValue);
	//组合框 - 找出字符串所在位置
	static int FindString(const CComboBox& cBox, const std::string& sValue);
	static int FindString(const CComboBox& cBox, const CString& sValue);
	static void Init(CComboBox&cBox, int nCols, ...);
	//组合框 - 插入字符串
	static void InsertString(CComboBox& cWnd, int nIndex, const std::string& sString);

	//列表控件 - 初始化
	static void SetReport(CListCtrl& vShow);
	static void Init(CListCtrl& vShow, int nCols, ...);//(... 名字1,宽度1,名字2,宽度2...名字nCols,宽度nCols)
	static void	InitName(CListCtrl& vShow, int nCols, ...);//(名字1，名字2..名字n)
	static void InitColumn(CListCtrl& vShow, int nCol, CString sName, int nWidth);

	static void Init(CListCtrl& vShow, const std::string& s1);
	static void Init(CListCtrl& vShow, const std::string& s1, const std::string& s2);
	static void Init(CListCtrl& vShow, const std::string& s1, const std::string& s2, const std::string& s3);
	static void Init(CListCtrl& vShow, const std::string& s1, const std::string& s2, const std::string& s3, const std::string& s4);
	static void Init(CListCtrl& vShow, const std::string& s1, const std::string& s2, const std::string& s3, const std::string& s4, const std::string& s5);
	static void Init(CListCtrl& vShow, const std::string& s1, const std::string& s2, const std::string& s3, const std::string& s4, const std::string& s5, const std::string& s6);
	static void Init(CListCtrl& vShow, const std::string& s1, const std::string& s2, const std::string& s3, const std::string& s4, const std::string& s5, const std::string& s6, const std::string& s7);
	static void Init(CListCtrl& vShow, const std::string& s1, const std::string& s2, const std::string& s3, const std::string& s4, const std::string& s5, const std::string& s6, const std::string& s7, const std::string& s8);
	static void Init(CListCtrl& vShow, const std::string& s1, const std::string& s2, const std::string& s3, const std::string& s4, const std::string& s5, const std::string& s6, const std::string& s7, const std::string& s8, const std::string& s9);
	static void	Init(CListCtrl& vShow, const VectorString& vString);
	static void Init(CListCtrl& vShow, const MapIntString& vString);

	//列表控件 - 查找所在行
	template<typename T>
	static int FindString(const CListCtrl& vShow, const T& sValue, int nCol);
	static int FindString(const CListCtrl& vShow, const std::string& sValue, int nCol);

	//列表控件 - 获取列数
	static int GetColumnCount(CListCtrl& cBox);
	//列表控件 - 获取行数
	static int GetRowCount(CListCtrl& cBox);
	//列表控件 - 获取某列的title
	static CString GetColumnText(const CListCtrl& cBox, int nCol);
	//列表控件 - 删除所有的title
	static void DeleteAllColumns(CListCtrl& vShow);
	//列表控件 - 是否是空行
	static bool IsEmptyLine(CListCtrl& cBox, int nRow);
	//列表控件 - 移除所有的空行
	static void RemoveEmptyLine(CListCtrl& cBox);
	//列表控件 - 设置/获取 某行的所有字符串
	static void SetRowString(CListCtrl& cBox, int nRow, const std::vector<CString>& vValue);
	static void SetRowString(CListCtrl& cBox, int nRow, const VectorString& vValue);
	static void SetRowString(CListCtrl& cBox, int nRow, const MapIntString& vString);
	static void GetRowString(CListCtrl& cBox, int nRow, std::vector<CString>& vStrings);
	static void GetRowString(CListCtrl& cBox, int nRow, VectorString& vStrings);
	//列表控件 - 获取 某列的所有字符串
	static void GetColString(const CListCtrl& cBox, int nCol, std::vector<CString>& vStrings);
	static void GetColString(const CListCtrl& cBox, int nCol, VectorString& vStrings);
	//列表控件 - 让列表框的每一列自动调整宽度 以适应新的字符串长度
	static void SuitStringWidth(CListCtrl& cBox);
	static void SuitStringWidth(CListCtrl& cBox, int nCol, int nExtra = 15);
	//列表控件 - 删除全部内容
	static void DeleteItem(CListCtrl& cBox);
	//列表控件 - 删除单行内容
	static void DeleteItem(CListCtrl& cBox, int nRow);
	//列表控件 - 删除多行内容
	static void DeleteItem(CListCtrl& cBox, const std::set<int>& vRow);
	//列表控件 - 删除指定列 与 指定内容 相同的行
	template<typename T>
	static uint DeleteItem(CListCtrl& cBox, int nCol, const T& t, int nCounter = -1);
	static uint DeleteItem(CListCtrl& cBox, int nCol, const std::string& sString, int nCounter = -1);
	//列表控件 - 删除选中行内容
	static void DeleteSelRows(CListCtrl& cBox);
	//列表控件 - 设置/获取某项文本
	static void SetItemText(CListCtrl& vWnd, int nItem, int nSubItem, const std::string& tVaue);
	template<typename T>
	static void SetItemText(CListCtrl& vWnd, int nItem, int nSubItem, const T& tVaue);
	template<typename T>
	static bool			GetItemText(const CListCtrl& vWnd, int nItem, int nSubItem, T& tVaue);
	static std::string	GetItemText(const CListCtrl& vWnd, int nItem, int nSubItem);
	//列表控件 - 插入某行
	static int InsertItem(CListCtrl& vWnd, int nRow);
	template<typename T1>
	static int InsertItem(CListCtrl& vWnd, int nRow, const T1& t1);
	template<typename T1, typename T2>
	static int InsertItem(CListCtrl& vWnd, int nRow, const T1& t1, const T2& t2);
	template<typename T1, typename T2, typename T3>
	static int InsertItem(CListCtrl& vWnd, int nRow, const T1& t1, const T2& t2, const T3& t3);
	template<typename T1, typename T2, typename T3, typename T4>
	static int InsertItem(CListCtrl& vWnd, int nRow, const T1& t1, const T2& t2, const T3& t3, const T4& t4);
	static int InsertItem(CListCtrl& vWnd, int nRow, const std::vector<CString>& vStrings);
	static int InsertItem(CListCtrl& vWnd, int nRow, const VectorString& vStrings);
	//列表控件 - 选中以目标字符串开头的行
	template<typename T>
	static uint SelectedBeginWith(CListCtrl& vWnd, const T& tValue);
	template<typename T>
	static uint SelectedHas(CListCtrl& vWnd, const T& tValue);
	//列表控件 - 复制选中行 到 另一个列表
	static void CopySels(CListCtrl& wSrc, CListCtrl& wDes, int nRow = -1);

	//组合框
	static bool			SetDefault(const CComboBox& cBox, std::string& sValue);
	static std::string	GetSelectd(const CComboBox& cBox);
	static bool			SetSelectd(CComboBox& cBox, int nRow = -1);

	//树 - 复制
	static void CopyTree(const CTreeCtrl& cTreeSrc, CTreeCtrl& cTreeDes);
	//树 - 拷贝某结点以及以下所有节点
	static void CopyChild(const CTreeCtrl& cTreeSrc, CTreeCtrl& cTreeDes, const HTREEITEM& itemSrcParent, const HTREEITEM& itemDesParent);
	//树 - 展开所有
	static void ExpandTree(CTreeCtrl& cTree);
	//树 - 展开某节点以及以下所有节点
	static void ExpandChild(CTreeCtrl& cTree, const HTREEITEM& itemParent);
	//树 - 将整棵树全部复选
	static void CheckedTree(CTreeCtrl& cTreeSrc, bool bChecked = true);
	//树 - 将某子节点以下(包括子节点)全部复选
	static void CheckedChild(CTreeCtrl& cTreeSrc, const HTREEITEM& itemParent, bool bChecked = true);
	//树 - 获取整棵树中所有被复选的叶子
	static void GetCheckedItems(std::set<HTREEITEM>& vDes, const CTreeCtrl& cTreeSrc);
	//树 - 获取某子节点以下(包括子节点)所有被复选的叶子
	static void GetCheckedItems(std::set<HTREEITEM>& vDes, const CTreeCtrl& cTreeSrc, const HTREEITEM& itemParent);

	//ATL
	static bool SetOleDateTime(COleDateTime& oleDateTime, const time_t tTime);
	static double SetOleDateTime(const time_t tTime);
	static double SetOleDateTime(const ToolFrame::CDateTime& date);
	static double SetOleDateTime(const ToolFrame::CDate& date);

	//内部数据 更新到 界面 函数
	static void Show(CListBox& cLstBox, const VectorString& vValue);
	static void Show(CListBox& cLstBox, const MapStringString& vMap, bool bFirst = false);
	static void Show(CListBox& cLstBox, const MapStringString* vMap, bool bFirst = false);

	static void Show(CComboBox& cComBox, const VectorString& vSrc);
	static void Show(CComboBox& cComBox, const MapStringString& vMap, bool bFirst = false);
	static void Show(CComboBox& cComBox, const MapStringString* pvMap, bool bFirst = false);
	static void Show(CListCtrl& cEdit, int nRow, int nArgs, ...);
	static void Show(CListCtrl& cEdit, int nRow, const VectorString& vStrings);

	template<typename TKey, typename TValue>
	static void ShowKey(CComboBox& cBox, const std::map<TKey, TValue>& vMap);
	template<typename TKey, typename TValue>
	static void ShowValue(CComboBox& cBox, const std::map<TKey, TValue>& vMap);

	//万能混合显示
	static void MergeShow(CListBox& cLstBox, const MapStringString& vMap, bool bFirst = false);
	static void MergeShow(CComboBox& cComBox, const MapStringString& vMap, bool bFirst = false);
	static void MergeShow(CComboBox& cComBox, const MapStringString* pvMap, bool bFirst = false);

	template<typename TKey, typename TValue>
	static void MergeShowKey(CComboBox& cComBox, const std::map<TKey, TValue>& vMap);
	template<typename TKey, typename TValue>
	static void MergeShowValue(CComboBox& cComBox, const std::map<TKey, TValue>& vMap);

	//将显示更新到内部
	static std::string	GetWindowText(const CWnd& wnd);
	template<typename TValue>
	static bool			GetWindowText(const CWnd& wnd, TValue& tValue);

	//万能更新(将界面数据更新到内部数据)
	static void Update(const CComboBox& cComBoxS, VectorString& vDes);
	static void Update(const CListBox& cBox, VectorString& vDes);

	//帮助工具
	static std::string GetHtmlSource(const CString& sAddress);
	static std::string GetHtmlSource(const std::string& sAddress);

	//std MFC 互转工具
	static CString		ToCString(const std::string& sSrc);
	static std::string	ToString(const CString& sSrc);

	//图形
	static HBITMAP LoadPngPicture(const std::string& sPath);
	static void MakeBackAlpha(CImage& img);

	//获取图形矩形
	static CRect GetRect(const CImage& img);
	static CRect GetRect(const CImage& img, const CPoint& ptPos);
	static CRect GetRect(const CImage& img, const CPoint& ptPos, double fRate, const CPoint& ptBegin);
	//矩形缩放
	template<typename TRate>
	static CRect Mult(CRect& rect, TRate tRate);

	//创建非模态窗口
	template<typename T>
	static BOOL CreateDlg(T& tDlg, CWnd* pParent = nullptr);
	template<typename T>
	static T* CreateDlg(CWnd* pParent = nullptr);

	//销毁非模态窗口(返回空指针)
	template<typename T>
	static T*		DestoryDlg(T* pWnd);
	template<typename TReturn,typename TArg>
	static TReturn* DestoryDlg(TArg* pWnd);
	
	//剪切板
	static std::string	GetClipboardText(const CWnd* pWnd);							//获取剪切板文本
	static bool			SetClipboardText(const CWnd* pWnd, const std::string& sText);//设置剪切板文字

																					 //按键 - 组合键
	static bool IsKeyComb(UINT nArg, UINT nChar, int nVKCtl1 = 0, int nVKCtl2 = 0, int nVKCtl3 = 0);

	//文件对话框
	static void			GetFilePath(const CFileDialog& dlg, VectorString& vPath);
	static std::string	GetFilePath(const CFileDialog& dlg);
	static std::string	GetDlgFileSel(bool bOpen);

	//文件夹对话框
	static std::string	GetDlgFolderSel(const std::string& sTitle, int nSpecDir = CSIDL_DESKTOP);//CSIDL_DESKTOP

																								 //消息框
	static int			ApiMessageBox(const std::string& sMsg, const std::string& sTitle, uint uType = MB_OK);
	static int			ApiWarningBox(const std::string& sMsg, const std::string& sTitle, uint uType = MB_ICONWARNING | MB_OK);

	static int			ApiMessageBox(CWnd* wnd, const std::string& sMsg, const std::string& sTitle, uint uType = MB_OK);
	static int			ApiWarningBox(CWnd* wnd, const std::string& sMsg, const std::string& sTitle, uint uType = MB_ICONWARNING | MB_OK);

	//ToString
	static std::string	ToString(const VectorString& vString, const std::string& sp = "\\\r\n");
};

template<typename T>
int ApiMFC::FindString(const CListCtrl& vShow, const T& sValue, int nCol)
{
	return FindString(vShow, ToolFrame::ToString(sValue), nCol);
}

template<typename T>
uint ApiMFC::DeleteItem(CComboBox& cBox, const T& t, int nCount)
{
	return DeleteItem(cBox, ToolFrame::ToString(t), nCount);
}

template<typename T>
bool ApiMFC::AddString(CComboBox& cWnd, const T& t)
{
	return AddString(cWnd, ToolFrame::ToString(t));
}

template<typename T>
uint ApiMFC::DeleteItem(CListCtrl& cBox, int nCol, const T& t, int nCounter /*= -1*/)
{
	return DeleteItem(cBox, nCol, ToolFrame::ToString(t), nCounter);
}

template<typename T>
BOOL ApiMFC::CreateDlg(T& tDlg, CWnd* pParent)
{
	return tDlg.Create(T::IDD, pParent);
}

template<typename T>
T* ApiMFC::CreateDlg(CWnd* pParent /*= nullptr*/)
{
	T* p = new T();
	if (!p)return nullptr;
	
	if (!p->Create(T::IDD, pParent))
	{
		delete p;
		return nullptr;
	}

	p->CenterWindow();
	p->ShowWindow(SW_SHOW);
	return p;
}

template<typename TReturn, typename TArg>
TReturn* ApiMFC::DestoryDlg(TArg* pWnd)
{
	if (!pWnd)return nullptr;
	delete pWnd;
	return nullptr;
}

template<typename T>
T* ApiMFC::DestoryDlg(T* pWnd)
{
	if (!pWnd)return nullptr;
	delete pWnd;
	return nullptr;
}

template<typename T>
uint ApiMFC::SelectedHas(CListCtrl& vWnd, const T& tValue)
{
	uint uCount = 0;
	const std::string sDes = ToolFrame::ToString(tValue);
	std::string sTemp;
	int nRowMax = vWnd.GetItemCount();
	int nColMax = ApiMFC::GetColumnCount(vWnd);
	for (int nRow = 0; nRow < nRowMax; ++nRow) {
		ApiMFC::SetNotSel(vWnd, nRow);
		for (int nCol = 0; nCol < nColMax; ++nCol)
		{
			ApiMFC::GetItemText(vWnd, nRow, nCol, sTemp);
			if (ToolFrame::IsHas(sTemp, sDes))
			{
				ApiMFC::SetSelected(vWnd, nRow);
				++uCount;
				break;
			}
		}
	}

	return uCount;
}

template<typename T>
uint ApiMFC::SelectedBeginWith(CListCtrl& vWnd, const T& tValue)
{
	uint uCount = 0;
	const std::string sDes = ToolFrame::ToString(tValue);
	std::string sTemp;
	int nRowMax = vWnd.GetItemCount();
	int nColMax = ApiMFC::GetColumnCount(vWnd);
	for (int nRow = 0; nRow < nRowMax; ++nRow) {
		ApiMFC::SetNotSel(vWnd, nRow);
		for (int nCol = 0; nCol < nColMax; ++nCol)
		{
			ApiMFC::GetItemText(vWnd, nRow, nCol, sTemp);
			if (ToolFrame::IsBeginWith(sTemp, sDes))
			{
				ApiMFC::SetSelected(vWnd, nRow);
				++uCount;
				break;
			}
		}
	}

	return uCount;
}
template<typename T>
bool ApiMFC::GetItemText(const CListCtrl& vWnd, int nItem, int nSubItem, T& tVaue)
{
	return ToolFrame::ToValue(ApiMFC::ToString(vWnd.GetItemText(nItem, nSubItem)), tVaue);
}

template<typename T1>
int ApiMFC::InsertItem(CListCtrl& vWnd, int nRow, const T1& t1)
{
	nRow = InsertItem(vWnd, nRow);
	SetItemText(vWnd, nRow, 0, t1);
	return nRow;
}

template<typename T1, typename T2>
int ApiMFC::InsertItem(CListCtrl& vWnd, int nRow, const T1& t1, const T2& t2)
{
	nRow = InsertItem(vWnd, nRow);
	SetItemText(vWnd, nRow, 0, t1);
	SetItemText(vWnd, nRow, 1, t2);
	return nRow;
}

template<typename T1, typename T2, typename T3>
int ApiMFC::InsertItem(CListCtrl& vWnd, int nRow, const T1& t1, const T2& t2, const T3& t3)
{
	nRow = InsertItem(vWnd, nRow);
	SetItemText(vWnd, nRow, 0, t1);
	SetItemText(vWnd, nRow, 1, t2);
	SetItemText(vWnd, nRow, 2, t3);
	return nRow;
}

template<typename T1, typename T2, typename T3, typename T4>
int ApiMFC::InsertItem(CListCtrl& vWnd, int nRow, const T1& t1, const T2& t2, const T3& t3, const T4& t4)
{
	nRow = InsertItem(vWnd, nRow);
	SetItemText(vWnd, nRow, 0, t1);
	SetItemText(vWnd, nRow, 1, t2);
	SetItemText(vWnd, nRow, 2, t3);
	SetItemText(vWnd, nRow, 3, t4);
	return nRow;
}

template<typename T>
void ApiMFC::SetItemText(CListCtrl& vWnd, int nItem, int nSubItem, const T& tVaue)
{
	ApiMFC::SetItemText(vWnd, nItem, nSubItem, ToolFrame::ToString(tVaue));
}

template<typename TRate>
CRect ApiMFC::Mult(CRect& rect, TRate tRate)
{
	rect.top = (LONG)(rect.top * tRate);
	rect.left = (LONG)(rect.left * tRate);
	rect.right = (LONG)(rect.right * tRate);
	rect.bottom = (LONG)(rect.bottom * tRate);

	return rect;
}
template<typename TValue>
bool ApiMFC::GetWindowText(const CWnd& wnd, TValue& tValue)
{
	return ToolFrame::ToValue(ApiMFC::GetWindowText(wnd), tValue);
}

template<typename TValue>
bool ApiMFC::SetWindowText(CWnd& wnd, const TValue& tValue) {
	return SetWindowText(wnd, ToolFrame::ToString(tValue));
}

template<typename TKey, typename TValue>
void ApiMFC::MergeShowValue(CComboBox& cComBox, const std::map<TKey, TValue>& vMap)
{
	std::map<TKey, TValue>::const_iterator itrOptions;
	foreach(itrOptions, vMap) {
		AddString(cComBox, ToolFrame::ToString(itrOptions->second));
	}
}
template<typename TKey, typename TValue>
void ApiMFC::ShowValue(CComboBox& cBox, const std::map<TKey, TValue>& vMap)
{
	cBox.ResetContent();
	MergeShowValue(cBox, vMap);

	SetSelected(cBox, 0);
}
template<typename TKey, typename TValue>
void ApiMFC::MergeShowKey(CComboBox& cComBox, const std::map<TKey, TValue>& vMap)
{
	std::map<TKey, TValue>::const_iterator itrOptions;
	foreach(itrOptions, vMap) {
		AddString(cComBox, ToolFrame::ToString(itrOptions->first));
	}
}
template<typename TKey, typename TValue>
void ApiMFC::ShowKey(CComboBox& cBox, const std::map<TKey, TValue>& vMap)
{
	cBox.ResetContent();
	MergeShowKey(cBox, vMap);

	SetSelected(cBox, 0);
}

#endif //MACRO_LIB_MFC
