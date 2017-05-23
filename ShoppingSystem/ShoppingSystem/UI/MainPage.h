// ShoppingSystemDlg.h : 头文件
//
#pragma once
#include "SidebarSheet.h"
#include "QuerySheet.h"
#include "DailyGSalesSheet.h"
#include "CashierSheet.h"

// MainPage 对话框
class MainPage : public CDialog
{
// 构造
public:
	MainPage(CWnd* pParent = NULL);	// 标准构造函数
    ~MainPage();

// 对话框数据
	enum { IDD = IDD_MAIN };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg LRESULT OnSidebarMenuItem(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
    CSidebarSheet m_sidebar;
    CStatusBar m_statusBar;
    CQuerySheet *m_pQuerySheet;
    CDailyGSalesSheet *m_pDailyGSSheet;
    CCashierSheet *m_pCashierSheet;
    int m_userId;

public:
    int getUserId() {return m_userId;} //用户Id，专指售货员Id
};
