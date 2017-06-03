// 实现文件
//

#include "stdafx.h"
//#include "..\Framework\ShoppingSystem.h"
//#include "Add_ModifyDlg.h"


// CAdd_ModifyDlg 对话框

IMPLEMENT_DYNAMIC(CAdd_ModifyDlg, CDialog)

CAdd_ModifyDlg::CAdd_ModifyDlg(int sheetStyle, BOOL bAdd, CWnd* pParent /*=NULL*/)
	: CDialog(CAdd_ModifyDlg::IDD, pParent), m_sheetStyle(sheetStyle), m_bAdd(bAdd)
{

}

CAdd_ModifyDlg::~CAdd_ModifyDlg()
{
}

void CAdd_ModifyDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, AM_GROUP, m_group);
    DDX_Control(pDX, AM_STATIC_1, m_static[0]);
    DDX_Control(pDX, AM_STATIC_2, m_static[1]);
    DDX_Control(pDX, AM_STATIC_3, m_static[2]);
    DDX_Control(pDX, AM_STATIC_4, m_static[3]);
    DDX_Control(pDX, AM_EDT_1, m_edit[0]);
    DDX_Control(pDX, AM_EDT_2, m_edit[1]);
    DDX_Control(pDX, AM_EDT_3, m_edit[2]);
    DDX_Control(pDX, AM_EDT_4, m_edit[3]);
}


BEGIN_MESSAGE_MAP(CAdd_ModifyDlg, CDialog)

    ON_BN_CLICKED(IDOK, &CAdd_ModifyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAdd_ModifyDlg 消息处理程序

void CAdd_ModifyDlg::Init(int sheetStyle, BOOL bAdd /* = TRUE*/)
{
    BOOL editVisible[4];

    if (0 == sheetStyle) {  //暂未解决头文件重复包含的问题，导致无法使用枚举querySheetStyle
        m_strLabel[0][0] = _T("ID");
        m_strLabel[1][0] = _T("名称");
        m_strLabel[2][0] = _T("单价");
        m_strLabel[3][0] = _T("库存");
        editVisible[0] = TRUE; editVisible[1] = TRUE;
        editVisible[2] = TRUE; editVisible[3] = TRUE;
        if (bAdd) {
            m_strLabel[0][1] = _T("(自动编号)");
            SetWindowText(_T("添加商品"));
        }
        else
            SetWindowText(_T("更新商品"));

        m_group.SetWindowText(_T("商品信息"));
    }
    else {
        m_strLabel[0][0] = _T("ID");
        m_strLabel[1][0] = _T("姓名");
        m_strLabel[2][0] = _T("密码");

        editVisible[0] = TRUE; editVisible[1] = TRUE;
        editVisible[2] = TRUE; editVisible[3] = FALSE;

        if (bAdd) {
            m_strLabel[0][1] = _T("(自动编号)");
            SetWindowText(_T("添加售货员"));
        }
        else
            SetWindowText(_T("修改售货员"));

        m_group.SetWindowText(_T("售货员信息"));
    }

    for (int i = 0; i < 4; ++i) {
        m_static[i].SetWindowText(m_strLabel[i][0]);
        m_edit[i].SetWindowText(m_strLabel[i][1]);
        m_edit[i].ShowWindow(editVisible[i]);
    }
}

BOOL CAdd_ModifyDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化

    Init(m_sheetStyle, m_bAdd);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}


void CAdd_ModifyDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    for (int i = 1; i < 4; ++i) {
       m_edit[i].GetWindowText( m_strLabel[i][1]);
    }
    OnOK();
}
