// SidebarSheet.cpp : 实现文件
//

#include "..\Framework\stdafx.h"
#include "..\Framework\ShoppingSystem.h"
#include "SidebarSheet.h"


// CSidebarSheet 对话框

IMPLEMENT_DYNAMIC(CSidebarSheet, CDialog)

CSidebarSheet::CSidebarSheet(CWnd* pParent /*=NULL*/)
	: CDialog(CSidebarSheet::IDD, pParent)
{
}

CSidebarSheet::~CSidebarSheet()
{
}

void CSidebarSheet::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, SB_BTN_SPWH, m_btn_spwh);
    DDX_Control(pDX, SB_BTN_QTSY, m_btn_qtsy);
    DDX_Control(pDX, SB_BTN_SPGL, m_btn_spgl);
    DDX_Control(pDX, SB_TREE_MENU, m_tree_menu);
}

BEGIN_MESSAGE_MAP(CSidebarSheet, CDialog)
ON_WM_SIZE()
ON_BN_CLICKED(SB_BTN_SPWH, &CSidebarSheet::OnBnClickedBtnSpwh)
ON_BN_CLICKED(SB_BTN_QTSY, &CSidebarSheet::OnBnClickedBtnQtsy)
ON_BN_CLICKED(SB_BTN_SPGL, &CSidebarSheet::OnBnClickedBtnSpgl)
ON_NOTIFY(NM_CLICK, SB_TREE_MENU, &CSidebarSheet::OnNMClickTreeMenu)
ON_NOTIFY(TVN_SELCHANGED, SB_TREE_MENU, &CSidebarSheet::OnTvnSelchangedTreeMenu)
END_MESSAGE_MAP()


void CSidebarSheet::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    //if (!m_btn_spwh || !m_btn_spgl || !m_btn_qtsy || !m_tree_menu) return;

    //moveCtrl(SB_BTN_SPWH);
    //setMenu(SB_BTN_SPWH);
}

void CSidebarSheet::OnBnClickedBtnSpwh()
{
    // TODO: 在此添加控件通知处理程序代码
    moveCtrl(SB_BTN_SPWH);
    setMenu(SB_BTN_SPWH);
    InvalidateRect(NULL);

}

void CSidebarSheet::OnBnClickedBtnQtsy()
{
    // TODO: 在此添加控件通知处理程序代码
    moveCtrl(SB_BTN_QTSY);
    setMenu(SB_BTN_QTSY);
    InvalidateRect(NULL);
}

void CSidebarSheet::OnBnClickedBtnSpgl()
{
    // TODO: 在此添加控件通知处理程序代码
    moveCtrl(SB_BTN_SPGL);
    setMenu(SB_BTN_SPGL);
    InvalidateRect(NULL);
}

void CSidebarSheet::moveCtrl(int nIDClickedBtn) {
    CRect rcClient;
    GetClientRect(&rcClient);

    int xOrg = 5, yOrg = 10, yBtm = rcClient.bottom-5;  //设置左上角坐标和底部预留空白
    int cx = rcClient.right-2*xOrg, cyBtn = 22,
        cyGapTree = 5, cyGapBtn = 2,
        cyTree = yBtm-3*cyBtn-yOrg-cyGapTree-3*cyGapBtn;  //设置长宽和控件底部间隙
    int yOrg_btn_qtsy, yOrg_btn_spgl, yOrg_tree_menu;  //控件坐标的角点纵坐标


    switch (nIDClickedBtn) {
        case SB_BTN_SPWH:
            yOrg_tree_menu = yOrg+cyBtn+cyGapBtn;
            yOrg_btn_qtsy = yOrg_tree_menu+cyTree+cyGapTree;
            yOrg_btn_spgl = yOrg_btn_qtsy+cyBtn+cyGapBtn;
            break;

        case SB_BTN_QTSY:
            yOrg_btn_qtsy = yOrg+cyBtn+cyGapBtn;
            yOrg_tree_menu = yOrg_btn_qtsy+cyBtn+cyGapBtn;
            yOrg_btn_spgl = yOrg_tree_menu+cyTree+cyGapTree;
            break;

        case SB_BTN_SPGL:
            yOrg_btn_qtsy = yOrg+cyBtn+cyGapBtn;
            yOrg_btn_spgl = yOrg_btn_qtsy+cyBtn+cyGapBtn;
            yOrg_tree_menu = yOrg_btn_spgl+cyBtn+cyGapBtn;
            break;

        default:
            break;
    }

    m_btn_spwh.MoveWindow(xOrg, yOrg, cx, cyBtn);
    m_btn_qtsy.MoveWindow(xOrg, yOrg_btn_qtsy, cx, cyBtn);
    m_btn_spgl.MoveWindow(xOrg, yOrg_btn_spgl, cx, cyBtn);
    m_tree_menu.MoveWindow(xOrg, yOrg_tree_menu, cx, cyTree);
}

void CSidebarSheet::setMenu(int nIDClickedBtn) {
    m_tree_menu.DeleteAllItems();
    switch (nIDClickedBtn) {
        case SB_BTN_SPWH:
            m_tree_menu.InsertItem(_T("商品维护"));
            break;

        case SB_BTN_QTSY:
            m_tree_menu.InsertItem(_T("购物结算"));
            break;

        case SB_BTN_SPGL:
           m_tree_menu.InsertItem(_T("当日卖出商品"));
           m_tree_menu.InsertItem(_T("售货员管理"));
            break;

        default:
            break;
    }
}

BOOL CSidebarSheet::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    //修改树形控件样式
    m_tree_menu.SetItemHeight(25);
    m_tree_menu.ModifyStyle(0, TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CSidebarSheet::OnNMClickTreeMenu(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: 在此添加控件通知处理程序代码
    CPoint pt;
    UINT uFlag = 0;
    GetCursorPos(&pt);
    m_tree_menu.ScreenToClient(&pt);
    HTREEITEM hItemSel = m_tree_menu.GetSelectedItem();
    HTREEITEM hItemHistTest = m_tree_menu.HitTest(pt, &uFlag);

    if (hItemHistTest) {
        if (hItemHistTest == hItemSel) return;

        WPARAM wParam = 0;
        if (TVHT_ONITEM & uFlag) {
            CString strItemName = m_tree_menu.GetItemText(hItemHistTest);
            if (_T("商品维护") == strItemName)
                wParam = SB_XPWH;
            else if (_T("购物结算") == strItemName)
                wParam = SB_GWJS;
            else if (_T("当日卖出商品") == strItemName)
                wParam = SB_DRMCSP;
            else if (_T("售货员管理") == strItemName)
                wParam = SB_SHYGL;
        }
            
        ::SendMessage(GetParent()->GetSafeHwnd(), WM_SBMENUITEM, wParam, 0);
    }
    
    *pResult = 0;
}

void CSidebarSheet::OnTvnSelchangedTreeMenu(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    //AfxMessageBox(m_tree_menu.GetItemText(pNMTreeView->itemNew.hItem));

    *pResult = 0;
}
