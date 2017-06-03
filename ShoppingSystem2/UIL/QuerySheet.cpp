// QuerySheet.cpp : 实现文件
//

#include "stdafx.h"
//#include "..\Framework\ShoppingSystem.h"
//#include "QuerySheet.h"
//#include "..\BLL\GoodsManager.h"
//#include "..\BLL\SalesmanManager.h"
//#include "..\Tools\Tools.h"


// CQuerySheet 对话框

IMPLEMENT_DYNAMIC(CQuerySheet, CDialog)

CQuerySheet::CQuerySheet(CWnd* pParent /*=NULL*/)
	: CDialog(CQuerySheet::IDD, pParent)
    , m_static_queryName(_T(""))
    , m_edit_queryName(_T(""))
{

}

CQuerySheet::~CQuerySheet()
{
}

void CQuerySheet::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, QUERY_LV_VIEW, m_listView);
    DDX_Text(pDX, QUERY_STATIC_QUERYNAME, m_static_queryName);
    DDX_Text(pDX, QUERY_EDT_QUERY, m_edit_queryName);
    DDX_Control(pDX, QUERY_BTN_QUERY, m_query);
    DDX_Control(pDX, QUERY_BTN_ADD, m_add);
    DDX_Control(pDX, QUERY_BTN_UPDATE, m_update);
    DDX_Control(pDX, QUERY_BTN_DELETE, m_delete);
}


BEGIN_MESSAGE_MAP(CQuerySheet, CDialog)
    ON_BN_CLICKED(QUERY_BTN_QUERY, &CQuerySheet::OnBnClickedBtnQuery)
    ON_BN_CLICKED(QUERY_BTN_ADD, &CQuerySheet::OnBnClickedBtnAdd)
    ON_BN_CLICKED(QUERY_BTN_UPDATE, &CQuerySheet::OnBnClickedBtnUpdate)
    ON_NOTIFY(LVN_ITEMCHANGED, QUERY_LV_VIEW, &CQuerySheet::OnLvnItemchangedLvView)
    ON_BN_CLICKED(QUERY_BTN_DELETE, &CQuerySheet::OnBnClickedBtnDelete)
END_MESSAGE_MAP()

BOOL CQuerySheet::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_listView.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CQuerySheet::OnLvnItemchangedLvView(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    if (pNMLV->uNewState & LVIS_SELECTED) {
        m_update.EnableWindow(TRUE);
        m_delete.EnableWindow(TRUE);
    }
    else {
        m_update.EnableWindow(FALSE);
        m_delete.EnableWindow(FALSE);
    }

    *pResult = 0;
}

// 按类型进行初始化

void CQuerySheet::Init(querySheetStyle sheetStyle)
{
    m_listView.DeleteAllItems();
    while (m_listView.DeleteColumn(0)); //删除所有列

    //修改和删除按钮置灰
    m_update.EnableWindow(FALSE);
    m_delete.EnableWindow(FALSE);

    m_sheetStyle = sheetStyle;
    switch (sheetStyle) {
        case sheetGoods:
            m_static_queryName = _T("商品名称：");

            m_listView.InsertColumn(0, _T("备注"), LVCFMT_LEFT, 150);
            m_listView.InsertColumn(0, _T("库存"), LVCFMT_LEFT, 60);
            m_listView.InsertColumn(0, _T("单价"), LVCFMT_LEFT, 60);
            m_listView.InsertColumn(0, _T("名称"), LVCFMT_LEFT, 100);
            m_listView.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 60);
            break;

        case sheetSalesman:
            m_static_queryName = _T("售货员姓名：");

            m_listView.InsertColumn(0, _T("密码"), LVCFMT_LEFT, 100);
            m_listView.InsertColumn(0, _T("用户名"), LVCFMT_LEFT, 100);
            m_listView.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 60);
            break;

        default:
            break;
    }
    UpdateData(FALSE);
    moveCtrl();
}

void CQuerySheet::moveCtrl(void)
{
    CRect rcClient;
    GetClientRect(&rcClient);

    int xOrg = 5, yOrg = 5;  //ListView左上角点
    int yBtm = rcClient.bottom-30;  //横排控件上沿距窗口底部的距离
    int cyGap = 10;  //ListView和横排控件的间距
    int cyCtrl = 20; //横排控件的高度
    int cxStatic = 80, cxEdit = 100, cxBtn = 60; //横排控件Static、编辑框和按钮的长度
    
    //设置控件的位置
    m_listView.MoveWindow(xOrg, yOrg, rcClient.right-2*xOrg, yBtm-cyGap-yOrg, FALSE);  //ListView
    GetDlgItem(QUERY_STATIC_QUERYNAME)->MoveWindow(xOrg, yBtm+2, cxStatic, cyCtrl, FALSE); //Static
    GetDlgItem(QUERY_EDT_QUERY)->MoveWindow(xOrg+cxStatic, yBtm, cxEdit, cyCtrl, FALSE);  //Edit
    m_query.MoveWindow(xOrg+cxStatic+cxEdit+3, yBtm, cxBtn, cyCtrl, FALSE);  //Button
    m_add.MoveWindow(xOrg+cxStatic+cxEdit+3+cxBtn+15, yBtm, cxBtn, cyCtrl, FALSE);  //Button
    m_update.MoveWindow(xOrg+cxStatic+cxEdit+3+2*cxBtn+2*15, yBtm, cxBtn, cyCtrl, FALSE);  //Button
    m_delete.MoveWindow(xOrg+cxStatic+cxEdit+3+3*cxBtn+3*15, yBtm, cxBtn, cyCtrl, FALSE);  //Button
}

void CQuerySheet::OnBnClickedBtnQuery()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_listView.DeleteAllItems();

        if (sheetGoods == m_sheetStyle) {
            GoodsManager goodsMgr;
            CArray<Goods> *pArrayGoods = goodsMgr.queryGoods(m_edit_queryName);
            for (int i = pArrayGoods->GetCount() - 1; i >= 0 ; --i) {
                Goods goods = pArrayGoods->GetAt(i);
                m_listView.InsertItem(0, toCString(goods.getGId()));
                m_listView.SetItemText(0, 1, goods.getGName());
                m_listView.SetItemText(0, 2, toCString(goods.getGPrice()));
                m_listView.SetItemText(0, 3, toCString(goods.getGNum()));
            }
            delete pArrayGoods;
        }
        else if (sheetSalesman == m_sheetStyle) {
            SalesmanManager salesmanMgr;
            CArray<Salesman> *pArraySalesman = salesmanMgr.querySalesman(m_edit_queryName);
            for (int i = pArraySalesman->GetCount() - 1; i >= 0; --i) {
                Salesman salesman = pArraySalesman->GetAt(i);
                m_listView.InsertItem(0, toCString(salesman.getSId()));
                m_listView.SetItemText(0, 1, salesman.getSName());
                m_listView.SetItemText(0, 2, salesman.getSPassword());
            }
            delete pArraySalesman;
        }
}

void CQuerySheet::OnBnClickedBtnAdd()
{
    // TODO: 在此添加控件通知处理程序代码
    CAdd_ModifyDlg add_modify(m_sheetStyle, TRUE);
    BOOL fRet = FALSE;

    if (IDOK == add_modify.DoModal()) {
        if (sheetGoods == m_sheetStyle) {
            Goods goods(add_modify.m_strLabel[1][1],
                _tstof((LPCTSTR) add_modify.m_strLabel[2][1]),
                _ttoi((LPCTSTR) add_modify.m_strLabel[3][1]));
            GoodsManager goodsMgr;
            fRet = goodsMgr.addGoods(&goods);
        }
        else {
            Salesman salesman(add_modify.m_strLabel[2][1],
                add_modify.m_strLabel[1][1]);
            SalesmanManager salesmanMgr;
            fRet = salesmanMgr.addSalesman(&salesman);
        }
        CString msg = fRet ? _T("添加成功！") : _T("添加失败！");
        AfxMessageBox(msg);
    }
}

void CQuerySheet::OnBnClickedBtnUpdate()
{
    // TODO: 在此添加控件通知处理程序代码
    CAdd_ModifyDlg add_modify(m_sheetStyle, FALSE);
    BOOL fRet = FALSE;

    //根据Id查出结果
    int selectId = _ttoi((LPCTSTR) m_listView.GetItemText(m_listView.GetSelectionMark(), 0));
    if (sheetGoods == m_sheetStyle) {

        GoodsManager goodsMgr;
        Goods goods = goodsMgr.queryGoods(selectId);
        add_modify.m_strLabel[0][1] = toCString(goods.getGId());
        add_modify.m_strLabel[1][1] = goods.getGName();
        add_modify.m_strLabel[2][1] = toCString(goods.getGPrice());
        add_modify.m_strLabel[3][1] = toCString(goods.getGNum());
    }
    else {
        SalesmanManager salsemanMgr;
        Salesman salesman = salsemanMgr.querySalesman(selectId);
        add_modify.m_strLabel[0][1] = toCString(salesman.getSId());
        add_modify.m_strLabel[1][1] = salesman.getSName();
        add_modify.m_strLabel[2][1] = salesman.getSPassword();
    }

    //将修改后的结果更新到数据库
    if (IDOK == add_modify.DoModal()) {
        if (sheetGoods == m_sheetStyle) {
            Goods goods(_ttoi((LPCTSTR) add_modify.m_strLabel[0][1]),
                add_modify.m_strLabel[1][1],
                _tstof((LPCTSTR) add_modify.m_strLabel[2][1]),
                _ttoi((LPCTSTR) add_modify.m_strLabel[3][1]));
            GoodsManager goodsMgr;
            fRet = goodsMgr.updateGoods(&goods);
        }
        else {
            Salesman salesman(_ttoi((LPCTSTR) add_modify.m_strLabel[0][1]),
                add_modify.m_strLabel[2][1],
                add_modify.m_strLabel[1][1]);
            SalesmanManager salesmanMgr;
            fRet = salesmanMgr.updateSalesman(&salesman);
        }
        CString msg = fRet ? _T("更新成功！") : _T("更新失败！");
        AfxMessageBox(msg);
    }
}

void CQuerySheet::OnBnClickedBtnDelete()
{
    // TODO: 在此添加控件通知处理程序代码

    int rowId = m_listView.GetSelectionMark();
    CString subItem0 = m_listView.GetItemText(rowId, 0);
    CString subItem1 = m_listView.GetItemText(rowId, 1);
    BOOL fRet = FALSE;

    CString msg = _T("确实要删除ID为") + subItem0;
    msg += sheetGoods == m_sheetStyle ? _T("，名称为") : _T("，姓名为");
    msg += subItem1;

    int selectId = _ttoi((LPCTSTR) subItem0);
    if (IDYES == AfxMessageBox(msg, MB_YESNO | MB_ICONWARNING)) {
        if (sheetGoods == m_sheetStyle) {
            GoodsManager goodsMgr;
            fRet = goodsMgr.deleteGoods(selectId);
        }
        else {
            SalesmanManager salesmanMgr;
            fRet = salesmanMgr.deleteSalesman(selectId);
        }
        msg = fRet ? _T("删除成功！") : _T("删除失败！");
        AfxMessageBox(msg);
    }
}


