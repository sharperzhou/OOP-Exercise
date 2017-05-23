#pragma once
#include "afxcmn.h"


// CDailyGSalesSheet 对话框

class CDailyGSalesSheet : public CDialog
{
	DECLARE_DYNAMIC(CDailyGSalesSheet)

public:
	CDailyGSalesSheet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDailyGSalesSheet();

// 对话框数据
	enum { IDD = IDD_DAILYGSALES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    void queryData(void);
    CListCtrl m_listView;
public:
    void Init(void);
};
