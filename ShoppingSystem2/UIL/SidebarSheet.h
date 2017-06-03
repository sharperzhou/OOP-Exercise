#pragma once
//#include "afxwin.h"
//#include "afxcmn.h"

//SidebarShee向MainPage发送消息
#define WM_SBMENUITEM  (WM_USER+10)

//消息内容，WPARAM参数
#define SB_XPWH        1  //当前选择商品维护菜单
#define SB_GWJS        2  //当前选择购物结算菜单
#define SB_DRMCSP      3  //当前选择当日卖出商品菜单
#define SB_SHYGL       4  //当前选择售货员管理菜单

// CSidebarSheet 对话框

class CSidebarSheet : public CDialog
{
	DECLARE_DYNAMIC(CSidebarSheet)

public:
	CSidebarSheet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSidebarSheet();

// 对话框数据
	enum { IDD = IDD_SIDEBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
    CButton m_btn_spwh;
    CButton m_btn_qtsy;
    CButton m_btn_spgl;
    CTreeCtrl m_tree_menu;
    void moveCtrl(int nIDClickedBtn);
    // 根据单击的按钮设置侧边栏菜单项
    void setMenu(int nIDClickedBtn);

public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnBnClickedBtnSpwh();

private:
    // 根据所单击的按钮移动控件
    afx_msg void OnBnClickedBtnQtsy();
    afx_msg void OnBnClickedBtnSpgl();
    virtual BOOL OnInitDialog();
    afx_msg void OnNMClickTreeMenu(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnTvnSelchangedTreeMenu(NMHDR *pNMHDR, LRESULT *pResult);
};
