#pragma once

#include "Macro.h"

#ifdef MACRO_LIB_MFC


#include <afxcontrolbars.h> 
#include <afxcmn.h>
#include <afxwin.h>

//˼·:
//��Ӧ˫���¼�,����һ�������ı���,���뿪��������ı��򽹵�ʱ,�����ı��򣬲���ֵ���浽˫��ʱ��λ��

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
	CRect rUnit;//��λ����
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
		SORT_NULL,				//��������
		SORT_BOOL,				//����
		SORT_NUMBER,			//����������
		SORT_NUMBER_N,			//�޷�������
		SORT_NUMBER_READ_3,		//�޷��� ��3λ Ϊ�ָλ �������� 1,000 4,256 55,323,665
		SORT_NUMBER_READ_4,		//�޷��� ��4λ Ϊ�ָλ �������� 1,1000 1,4256 1,5532,3665
		SORT_STRING,			//�ַ���
		SORT_DATETIME,			//����ʱ��
		SORT_DATE,				//����
		SORT_TIME,				//ʱ��
		SORT_TYPE_MAX
	};

	struct XEditingInfo 
	{
		std::string sTitle;		//������
		IEditing*	iEditing;	//�༭ʱ��ʾ�Ĵ���ָ��
		int			nSortType;	//����ʱ������
		BOOL		bOriginal;	//�Ƿ񱣳�ԭ���ڴ�С
		XEditingInfo(){
			iEditing = nullptr;
			nSortType = SORT_NULL;
			bOriginal = FALSE;
		}
	};
	typedef std::vector<XEditingInfo> VectorEditingInfo;//<��,��Ϣ>
public:
	typedef bool (*FnCompare)(const std::string& sSrc, const std::string& sDes);
	typedef std::map<int,std::vector<CString> > MapCopy;//<nRow,����>
	typedef std::map<int,FnCompare>				MapComparePtr;
	typedef std::map<int,COLORREF>				MapRowColor;

	//���⹫������
public:
	void SetTitle(int nCol, const std::string& sTitle,int nSortType = SORT_NULL,IEditing* iEditing = nullptr,BOOL bOriginal = FALSE,BOOL bParent = TRUE);
	void Init();
public:
	CListEdit*	CreateCtlEdit(uint uControlID = 0);
	CListCmb*	CreateCtlComboBox(uint uControlID = 0);
	bool		DestoryCtl(IEditing* pControl);
public:
	BOOL IsEditing(){return nullptr == _iEditing;}	//�Ƿ�༭��
	void SetEditing(IEditing* iEditing){_iEditing = iEditing;}
	IEditing* GetEditing(){return _iEditing;}

	void SetSuitWidth(BOOL bSuit=TRUE){_bSuitWidth = bSuit;}
	BOOL IsSuitWidth(){return _bSuitWidth;}

	BOOL SetExtraLine(BOOL bExtra = TRUE);
	BOOL ExtraLineAdd();	//��Ӷ���Ŀհ���(��������Ӳ���)
	BOOL ExtraLineRemove();	//�Ƴ�����Ŀհ���

	void SetCompareFun(int nType,FnCompare pfn);//����������ָ��

	int	 GetEditRow()const;
	int	 GetEditCol()const;

	bool SetRowTextColor(int nRow,COLORREF clr);
	bool SetRowTextBgColor(int nRow,COLORREF clr);
	
public:
	BOOL DeleteItem(int nItem);
	BOOL DeleteAllItems();

	//���غ���
private:
	DECLARE_MESSAGE_MAP()

private:
	afx_msg virtual void PreSubclassWindow();

	//�༭���
	afx_msg virtual void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg virtual void OnSetFocus(CWnd* pOldWnd);
	virtual void DisposeEdit(IEditing* iEditing);

	//ɾ�����
	void CopyToMem();
	afx_msg virtual void OnKeyDown(UINT   nChar,   UINT   nRepCnt,   UINT   nFlags);

	//�϶����
	afx_msg virtual void OnLvnBeginrdrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg virtual void OnLButtonUp(UINT nFlags, CPoint point);
	
	//�������
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

	//�Զ������
	virtual void OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnPaint();
	virtual BOOL OnEraseBkgnd(CDC* pDC);
public:
	CListCtrlEdit(void);
	virtual ~CListCtrlEdit(void);
private:
	VectorEditingInfo	_vInfo;
	MapRowColor			_vColorRowText;		//�� �ı� ��ɫ
	MapRowColor			_vColorRowTextBg;	//�� �ı� ���� ��ɫ
	BOOL				_bExtraLine;

	CPoint _ptItem;			//�༭�е���Ʒ����

	BOOL _bSuitWidth;
	IEditing* _iEditing;	//���ڱ༭�еĿؼ�
	BOOL _bDragging;		//�Ƿ��϶���
	BOOL _bAsc;             //�����������������л��ǽ�������
	int _nSortedCol;        //������¼�����������һ��
	FnCompare _fnCompare; //������

	MapCopy _vCopy;			//����ճ��ʱ����ʱ����(�Ժ��Ƶ����а�)
	MapComparePtr _vComparePtr;//<��������,������>
};

NS_TOOL_FRAME_END

#endif // MACRO_LIB_MFC
