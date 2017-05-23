#pragma once
#include "afxwin.h"
#include "Add_ModifyDlg.h"

// CQuerySheet 对话框

class CQuerySheet : public CDialog
{
	DECLARE_DYNAMIC(CQuerySheet)

public:
	CQuerySheet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQuerySheet();

// 对话框数据
	enum { IDD = IDD_QUERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    enum querySheetStyle {sheetGoods, sheetSalesman};  //CQuerySheet对话框用途/风格
    // 按类型进行初始化
    void Init(querySheetStyle sheetStyle);
private:
    CListCtrl m_listView;
    CString m_static_queryName;
    CString m_edit_queryName;
    CButton m_query;
    CButton m_add;
    CButton m_update;
    CButton m_delete;
    querySheetStyle m_sheetStyle;
    void moveCtrl(void);
    afx_msg void OnBnClickedBtnQuery();
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedBtnAdd();
    afx_msg void OnBnClickedBtnUpdate();
    afx_msg void OnLvnItemchangedLvView(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedBtnDelete();
};
