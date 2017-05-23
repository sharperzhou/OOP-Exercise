// DailyGSalesSheet.cpp : 实现文件
//

#include "..\Framework\stdafx.h"
#include "..\Framework\ShoppingSystem.h"
#include "DailyGSalesSheet.h"
#include "..\BLL\GSalesManager.h"
#include "..\Entity\GSales.h"
#include "..\Tools\Tools.h"


// CDailyGSalesSheet 对话框

IMPLEMENT_DYNAMIC(CDailyGSalesSheet, CDialog)

CDailyGSalesSheet::CDailyGSalesSheet(CWnd* pParent /*=NULL*/)
	: CDialog(CDailyGSalesSheet::IDD, pParent)
{

}

CDailyGSalesSheet::~CDailyGSalesSheet()
{
}

void CDailyGSalesSheet::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, DGS_LISTVIEW, m_listView);
}


BEGIN_MESSAGE_MAP(CDailyGSalesSheet, CDialog)
END_MESSAGE_MAP()


// CDailyGSalesSheet 消息处理程序

BOOL CDailyGSalesSheet::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化

    //ListView额外样式
    m_listView.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CDailyGSalesSheet::queryData(void)
{
    m_listView.DeleteAllItems();
    GSalesManager gSalesMgr;
    CArray<GSales> *pArrayGSales = gSalesMgr.dailyGSales();
    for (int i = pArrayGSales->GetCount() - 1; i >= 0; --i) {
        GSales gsales(pArrayGSales->GetAt(i));
        m_listView.InsertItem(0, gsales.getGName());
        m_listView.SetItemText(0, 1, toCString(gsales.getGPrice()));
        m_listView.SetItemText(0, 2, toCString(gsales.getGNum()));
        m_listView.SetItemText(0, 3, toCString(gsales.getAllSNum()));
    }
    delete pArrayGSales;
}

void CDailyGSalesSheet::Init(void)
{
    //ListView在窗体中的位置
    CRect rcClient;
    GetClientRect(&rcClient);
    int topLeftRightMargin = 5;
    int bottomMargin = 5;
    rcClient.left += topLeftRightMargin;
    rcClient.right -= topLeftRightMargin;
    rcClient.top += topLeftRightMargin;
    rcClient.bottom -= bottomMargin;
    m_listView.MoveWindow(&rcClient);


    //设置ListView的列
    while (m_listView.DeleteColumn(0));
    m_listView.InsertColumn(0, _T("销量"), LVCFMT_LEFT, 80);
    m_listView.InsertColumn(0, _T("库存"), LVCFMT_LEFT, 80);
    m_listView.InsertColumn(0, _T("单价"), LVCFMT_LEFT, 80);
    m_listView.InsertColumn(0, _T("名称"), LVCFMT_LEFT, 80);

    //查询数据
    queryData();
}
