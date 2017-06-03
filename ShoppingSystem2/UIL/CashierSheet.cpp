// CashierSheet.cpp : 实现文件
//

#include "stdafx.h"
//#include "..\Framework\ShoppingSystem.h"
//#include "CashierSheet.h"
//#include "..\BLL\GSalesManager.h"
//#include "..\BLL\GoodsManager.h"
//#include "..\Entity\Goods.h"
//#include "..\Tools\Tools.h"
//#include "MainPage.h"

//class MainPage;

// CCashierSheet 对话框

IMPLEMENT_DYNAMIC(CCashierSheet, CDialog)

CCashierSheet::CCashierSheet(CWnd* pParent /*=NULL*/)
	: CDialog(CCashierSheet::IDD, pParent)
    , m_strName(_T(""))
    , m_nQuantity(1)
    , m_strAmount(_T("应收：0.00"))
    , m_fAmount(0)
    , m_fPaid(0)
    , m_strCharge(_T("找零：0.00"))
{
    m_pArrayOrder = new CArray<GSales>;
}

CCashierSheet::~CCashierSheet()
{
    GSalesManager gsalesMgr;
    gsalesMgr.uncashierAll(m_pArrayOrder);
    delete m_pArrayOrder;
}

void CCashierSheet::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, CASHIER_LV_GOODS, m_LV_Goods);
    DDX_Control(pDX, CASHIER_LV_CART, m_LV_Cart);
    DDX_Text(pDX, CASHIER_EDT_NAME, m_strName);
    DDX_Text(pDX, CASHIER_EDT_QUANTITY, m_nQuantity);
    DDV_MinMaxInt(pDX, m_nQuantity, 1, 100);
    DDX_Text(pDX, CASHIER_STATIC_AMOUNT, m_strAmount);
    DDX_Text(pDX, CASHIER_EDT_PAID, m_fPaid);
    DDX_Text(pDX, CASHIER_STATIC_CHARGE, m_strCharge);
}


BEGIN_MESSAGE_MAP(CCashierSheet, CDialog)
    ON_NOTIFY(UDN_DELTAPOS, CASHIER_SPIN_QUANTITY, &CCashierSheet::OnDeltaposSpinQuantity)
    ON_BN_CLICKED(CASHIER_BTN_QUERY, &CCashierSheet::OnBnClickedBtnQuery)
    ON_BN_CLICKED(CASHIER_BTN_PURCHASE, &CCashierSheet::OnBnClickedBtnPurchase)
    ON_BN_CLICKED(CASHIER_BTN_CANCEL, &CCashierSheet::OnBnClickedBtnCancel)
    ON_BN_CLICKED(CASHIER_BTN_CASH, &CCashierSheet::OnBnClickedBtnCash)
    ON_NOTIFY(LVN_ITEMCHANGED, CASHIER_LV_GOODS, &CCashierSheet::OnLvnItemchangedLvGoods)
END_MESSAGE_MAP()


// CCashierSheet 消息处理程序

BOOL CCashierSheet::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化

    //设置ListView扩展样式
    DWORD style = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_LV_Cart.SetExtendedStyle(style);
    m_LV_Goods.SetExtendedStyle(style);
    
    //设置Spin关联文本框
    CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*) GetDlgItem(CASHIER_SPIN_QUANTITY);
    pSpin->SetBuddy(GetDlgItem(CASHIER_EDT_QUANTITY));
    pSpin->SetRange(1, 100);

    //按钮置灰
    GetDlgItem(CASHIER_BTN_PURCHASE)->EnableWindow(FALSE);
    GetDlgItem(CASHIER_BTN_CASH)->EnableWindow(FALSE);
    GetDlgItem(CASHIER_BTN_CANCEL)->EnableWindow(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CCashierSheet::OnDeltaposSpinQuantity(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    
    if (pNMUpDown->iDelta == -1) {
        m_nQuantity -= 1;
    }
    if (pNMUpDown->iDelta == 1) {
        m_nQuantity += 1;
    }
    CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*) GetDlgItem(CASHIER_SPIN_QUANTITY);
    int nLow, nUpper;
    pSpin->GetRange32(nLow, nUpper);
    m_nQuantity = max(nLow, min(nUpper, m_nQuantity));
    UpdateData(FALSE);
    *pResult = 0;
}

void CCashierSheet::OnLvnItemchangedLvGoods(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    CWnd *pBtnPurchase = GetDlgItem(CASHIER_BTN_PURCHASE);
    if (pNMLV->uNewState & LVIS_SELECTED)
        pBtnPurchase->EnableWindow(TRUE);
    else
        pBtnPurchase->EnableWindow(FALSE);
    *pResult = 0;
}

void CCashierSheet::moveCtrl(void)
{
    CRect rcClient;
    
    int xEdgeMargin = 5, yEdgeMargin = 5; //上下左右边缘边距
    int cyCtrl = 20, cxBtn = 60;  //横排控件高度，按钮宽度
    int cyGap = 3; //ListView与横排控件的间距

    //商品列表GroupBox
    GetClientRect(&rcClient);
    rcClient.left += xEdgeMargin;
    rcClient.right -= xEdgeMargin;
    rcClient.top += yEdgeMargin;
    rcClient.bottom = rcClient.bottom/2 - yEdgeMargin/2;
    GetDlgItem(CASHIER_GRP_GOODS)->MoveWindow(&rcClient, FALSE);

    rcClient.InflateRect(-xEdgeMargin, -yEdgeMargin);
    rcClient.top += 2*yEdgeMargin; //防止遮盖GroupBox顶部的文字部分
    int xOrgCtrl = rcClient.left, yOrgCtrl = rcClient.bottom-cyCtrl;
    //ListView_Goods
    m_LV_Goods.MoveWindow(xOrgCtrl, rcClient.top, rcClient.Width(), rcClient.Height()-cyGap-cyCtrl, FALSE);
    //从左往右
    GetDlgItem(CASHIER_STATIC_NAME)->MoveWindow(xOrgCtrl, yOrgCtrl+3, 60, cyCtrl, FALSE);
    GetDlgItem(CASHIER_EDT_NAME)->MoveWindow(xOrgCtrl+63, yOrgCtrl, 80, cyCtrl, FALSE);
    GetDlgItem(CASHIER_BTN_QUERY)->MoveWindow(xOrgCtrl+150, yOrgCtrl, cxBtn, cyCtrl, FALSE);
    //从右往左
    GetDlgItem(CASHIER_BTN_PURCHASE)->MoveWindow(rcClient.right-cxBtn, yOrgCtrl, cxBtn, cyCtrl, FALSE);
    GetDlgItem(CASHIER_SPIN_QUANTITY)->MoveWindow(rcClient.right-cxBtn-25, yOrgCtrl, 15, cyCtrl, FALSE);
    GetDlgItem(CASHIER_EDT_QUANTITY)->MoveWindow(rcClient.right-cxBtn-60, yOrgCtrl, 35, cyCtrl, FALSE);
    GetDlgItem(CASHIER_STATIC_QUANTITY)->MoveWindow(rcClient.right-cxBtn-100, yOrgCtrl+3, 40, cyCtrl, FALSE);

    //购物车GroupBox
    GetClientRect(&rcClient);
    rcClient.left += xEdgeMargin;
    rcClient.right -= xEdgeMargin;
    rcClient.top = rcClient.Height()/2 + yEdgeMargin/2;
    rcClient.bottom -= yEdgeMargin;
    GetDlgItem(CASHIER_GRP_CART)->MoveWindow(&rcClient, FALSE);

    rcClient.InflateRect(-xEdgeMargin, -yEdgeMargin);
    rcClient.top += 2*yEdgeMargin; //防止遮盖GroupBox顶部的文字部分
    xOrgCtrl = rcClient.left, yOrgCtrl = rcClient.bottom-cyCtrl;
    //ListView_Cart
    m_LV_Cart.MoveWindow(xOrgCtrl, rcClient.top, rcClient.Width(), rcClient.Height()-cyGap-cyCtrl, FALSE);
    //从左往右
    GetDlgItem(CASHIER_STATIC_AMOUNT)->MoveWindow(xOrgCtrl, yOrgCtrl+3, 100, cyCtrl, FALSE);
    GetDlgItem(CASHIER_STATIC_PAID)->MoveWindow(xOrgCtrl+125, yOrgCtrl+3, 40, cyCtrl, FALSE);
    GetDlgItem(CASHIER_EDT_PAID)->MoveWindow(xOrgCtrl+165, yOrgCtrl, 50, cyCtrl, FALSE);
    GetDlgItem(CASHIER_STATIC_CHARGE)->MoveWindow(xOrgCtrl+255, yOrgCtrl+3, 100, cyCtrl, FALSE);
    //从右向左
    GetDlgItem(CASHIER_BTN_CASH)->MoveWindow(rcClient.right-cxBtn, yOrgCtrl, cxBtn, cyCtrl, FALSE);
    GetDlgItem(CASHIER_BTN_CANCEL)->MoveWindow(rcClient.right-2*cxBtn-5, yOrgCtrl, cxBtn, cyCtrl, FALSE);
}

void CCashierSheet::Init(void)
{
    while (m_LV_Goods.DeleteColumn(0));
    m_LV_Goods.DeleteAllItems();

    m_LV_Goods.InsertColumn(0, _T("备注"), LVCFMT_LEFT, 150);
    m_LV_Goods.InsertColumn(0, _T("库存"), LVCFMT_LEFT, 60);
    m_LV_Goods.InsertColumn(0, _T("单价"), LVCFMT_LEFT, 60);
    m_LV_Goods.InsertColumn(0, _T("商品名称"), LVCFMT_LEFT, 100);
    m_LV_Goods.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 60);

    while (m_LV_Cart.DeleteColumn(0));
    m_LV_Cart.DeleteAllItems();

    m_LV_Cart.InsertColumn(0, _T("金额"), LVCFMT_LEFT, 60);
    m_LV_Cart.InsertColumn(0, _T("数量"), LVCFMT_LEFT, 60);
    m_LV_Cart.InsertColumn(0, _T("商品名称"), LVCFMT_LEFT, 100);
    m_LV_Cart.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 60);

    moveCtrl();
}

void CCashierSheet::OnBnClickedBtnQuery()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_LV_Goods.DeleteAllItems();
    
    GoodsManager goodsMgr;
    CArray<Goods> *pArrayGoods = goodsMgr.queryGoods(m_strName);
    for (int i = pArrayGoods->GetCount()-1; i >= 0; --i) {
        Goods goods = pArrayGoods->GetAt(i);
        m_LV_Goods.InsertItem(0, toCString(goods.getGId()));
        m_LV_Goods.SetItemText(0, 1, goods.getGName());
        m_LV_Goods.SetItemText(0, 2, toCString(goods.getGPrice()));
        m_LV_Goods.SetItemText(0, 3, toCString(goods.getGNum()));
    }
    delete pArrayGoods;
}
void CCashierSheet::OnBnClickedBtnPurchase()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_LV_Cart.DeleteAllItems();

    GSalesManager gsalesMgr;
    BOOL fRet = FALSE;
    int selectId = _ttoi((LPCTSTR) m_LV_Goods.GetItemText(m_LV_Goods.GetSelectionMark(), 0));
    fRet = gsalesMgr.cashierByOnce(m_pArrayOrder, selectId, m_nQuantity);
    if (!fRet) {
        AfxMessageBox(_T("当前商品库存不足！"));
        return;
    }

    for (int i = m_pArrayOrder->GetCount()-1; i >= 0; --i) {
        GSales gsales = m_pArrayOrder->GetAt(i);
        m_LV_Cart.InsertItem(0, toCString(i+1));
        m_LV_Cart.SetItemText(0, 1, gsales.getGName());
        int gNum = gsales.getSNum();
        double gPrice = gsales.getGPrice();
        m_LV_Cart.SetItemText(0, 2, toCString(gNum));
        m_LV_Cart.SetItemText(0, 3, toCString(gPrice*gNum));
        m_fAmount += gPrice*gNum;
    }

    GetDlgItem(CASHIER_BTN_CANCEL)->EnableWindow(TRUE);
    GetDlgItem(CASHIER_BTN_CASH)->EnableWindow(TRUE);

    m_strAmount.Format(_T("应收：%0.2f"), m_fAmount);
    m_strCharge = _T("找零：0.00");
    UpdateData(FALSE);
}

void CCashierSheet::OnBnClickedBtnCancel()
{
    // TODO: 在此添加控件通知处理程序代码
    GSalesManager gsalesMgr;
    gsalesMgr.uncashierAll(m_pArrayOrder);
    m_LV_Cart.DeleteAllItems();

    GetDlgItem(CASHIER_BTN_CANCEL)->EnableWindow(FALSE);
    GetDlgItem(CASHIER_BTN_CASH)->EnableWindow(FALSE);

    m_strAmount = _T("应收：0.00");
    m_fAmount = 0;
    m_fPaid = 0;
    UpdateData(FALSE);
}



void CCashierSheet::OnBnClickedBtnCash()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    double charge = m_fPaid - m_fAmount;

    if (charge < 0) {
        AfxMessageBox(_T("结算失败，当前付款金额不足！"));
        GetDlgItem(CASHIER_EDT_PAID)->SetFocus();
        return;
    }

    GSalesManager gsalesMgr;
    gsalesMgr.settleAccount(m_pArrayOrder, ((MainPage*) AfxGetApp()->GetMainWnd())->getUserId());
    
    GetDlgItem(CASHIER_BTN_CANCEL)->EnableWindow(FALSE);
    GetDlgItem(CASHIER_BTN_CASH)->EnableWindow(FALSE);

    m_LV_Cart.DeleteAllItems();
    m_strAmount = _T("应收：0.00");
    m_fAmount = 0;
    m_fPaid = 0;
    m_strCharge.Format(_T("找零：%0.2f"), charge);
    UpdateData(FALSE);
}

