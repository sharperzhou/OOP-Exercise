#pragma once
//#include "afxcmn.h"
//#include "afxwin.h"
//#include "..\Entity\GSales.h"

// CCashierSheet 对话框

class CCashierSheet : public CDialog
{
	DECLARE_DYNAMIC(CCashierSheet)

public:
	CCashierSheet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCashierSheet();

// 对话框数据
	enum { IDD = IDD_CASHIER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
    virtual BOOL OnInitDialog();
    CListCtrl m_LV_Goods;
    CListCtrl m_LV_Cart;
    CString m_strName;
    int m_nQuantity;
    CString m_strAmount;  //字符串方式显示应收金额
    double m_fAmount;  //浮点数方式存储应收金额
    double m_fPaid;  //实收金额
    CString m_strCharge;
    CArray<GSales> *m_pArrayOrder;

    void moveCtrl(void);
    afx_msg void OnDeltaposSpinQuantity(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedBtnQuery();
    afx_msg void OnBnClickedBtnPurchase();
    afx_msg void OnBnClickedBtnCancel();
    afx_msg void OnBnClickedBtnCash();

public:
    void Init(void);
public:
    afx_msg void OnLvnItemchangedLvGoods(NMHDR *pNMHDR, LRESULT *pResult);
};
