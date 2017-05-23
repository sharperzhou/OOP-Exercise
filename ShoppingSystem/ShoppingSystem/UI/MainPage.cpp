// ShoppingSystemDlg.cpp : 实现文件
//

#include "..\framework\stdafx.h"
#include "..\framework\ShoppingSystem.h"
#include "MainPage.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// MainPage 对话框




MainPage::MainPage(CWnd* pParent /*=NULL*/)
	: CDialog(MainPage::IDD, pParent),
    m_pQuerySheet(NULL), m_pDailyGSSheet(NULL),
    m_pCashierSheet(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

MainPage::~MainPage() {
    if (m_pQuerySheet) delete m_pQuerySheet;
    if (m_pDailyGSSheet) delete m_pDailyGSSheet;
    if (m_pCashierSheet) delete m_pCashierSheet;
}

void MainPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(MainPage, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_MESSAGE(WM_SBMENUITEM, &MainPage::OnSidebarMenuItem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// MainPage 消息处理程序

BOOL MainPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

    CRect rcClient;

    //控制登录界面是否成功登录
    CLoginDlg loginDlg;
    if (IDOK != loginDlg.DoModal()) {
        PostQuitMessage(0);
        return TRUE;
    }

    //保存用户Id（专指售货员）
    m_userId = loginDlg.m_userId;

    //创建状态栏
    m_statusBar.CreateEx(this);
    GetClientRect(&rcClient);
    UINT indicator[2] = {2000, 2001};
    m_statusBar.SetIndicators(indicator, sizeof(indicator)/sizeof(UINT));
    m_statusBar.SetPaneInfo(0, indicator[0], SBPS_STRETCH, 200);
    m_statusBar.SetPaneInfo(1, indicator[1], SBPS_STRETCH, 0);

    CString paneText = _T("当前用户：") + loginDlg.m_userName + _T("（") + loginDlg.m_roleName + _T("）");
    m_statusBar.SetPaneText(0, _T("就绪"));
    m_statusBar.SetPaneText(1, paneText);

    m_statusBar.MoveWindow(rcClient.left, rcClient.bottom-20, rcClient.Width(), 20, FALSE);
    
    //创建侧边栏
    m_sidebar.Create(IDD_SIDEBAR, this);
    GetClientRect(&rcClient);
    rcClient.right = 170;
    rcClient.bottom -= 20;
    m_sidebar.MoveWindow(&rcClient, FALSE);
    m_sidebar.ShowWindow(SW_NORMAL);

    //初始化侧边栏
    int clickedBtnId;
    if (loginDlg.m_roleName == _T("管理员")) {
        clickedBtnId = m_sidebar.m_btn_spwh.GetDlgCtrlID();
        m_sidebar.setMenu(clickedBtnId);
        m_sidebar.moveCtrl(clickedBtnId);
        m_sidebar.m_btn_qtsy.EnableWindow(FALSE);
    }
    else if (loginDlg.m_roleName == _T("售货员")) {
        clickedBtnId = m_sidebar.m_btn_qtsy.GetDlgCtrlID();
        m_sidebar.setMenu(clickedBtnId);
        m_sidebar.moveCtrl(clickedBtnId);
        m_sidebar.m_btn_spwh.EnableWindow(FALSE);
        m_sidebar.m_btn_spgl.EnableWindow(FALSE);
    }


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void MainPage::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR MainPage::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT MainPage::OnSidebarMenuItem(WPARAM wParam, LPARAM lParam)
{
    CRect rcClient;
    int cy;
    m_sidebar.GetClientRect(&rcClient);
    cy = rcClient.right;
    this->GetClientRect(&rcClient);
    rcClient.left = cy;
    rcClient.bottom -= 20;

    switch (wParam) {
        case SB_XPWH:
        case SB_SHYGL:
            if (m_pDailyGSSheet) {
                delete m_pDailyGSSheet;
                m_pDailyGSSheet = NULL;
            }
            if (m_pCashierSheet) {
                delete m_pCashierSheet;
                m_pCashierSheet = NULL;
            }
            if (!m_pQuerySheet) {
                m_pQuerySheet = new CQuerySheet;
                m_pQuerySheet->Create(IDD_QUERY, this);
                m_pQuerySheet->MoveWindow(&rcClient);
                m_pQuerySheet->ShowWindow(SW_NORMAL);
            }
            
            CQuerySheet::querySheetStyle sheetStyle;
            if (SB_XPWH == wParam) sheetStyle = CQuerySheet::sheetGoods;
            else if (SB_SHYGL == wParam) sheetStyle = CQuerySheet::sheetSalesman;
            
            m_pQuerySheet->Init(sheetStyle);

            break;

        case SB_GWJS:
            if (m_pQuerySheet) {
                delete m_pQuerySheet;
                m_pQuerySheet = NULL;
            }
            if (m_pDailyGSSheet) {
                delete m_pDailyGSSheet;
                m_pDailyGSSheet = NULL;
            }
            if (!m_pCashierSheet) {
                m_pCashierSheet = new CCashierSheet;
                m_pCashierSheet->Create(IDD_CASHIER, this);
                m_pCashierSheet->MoveWindow(&rcClient);
                m_pCashierSheet->ShowWindow(SW_NORMAL);
            }
            m_pCashierSheet->Init();
            break;

        case SB_DRMCSP:
            if (m_pQuerySheet) {
                delete m_pQuerySheet;
                m_pQuerySheet = NULL;
            }
            if (m_pCashierSheet) {
                delete m_pCashierSheet;
                m_pCashierSheet = NULL;
            }
            if (!m_pDailyGSSheet) {
                m_pDailyGSSheet = new CDailyGSalesSheet;
                m_pDailyGSSheet->Create(IDD_DAILYGSALES, this);
                m_pDailyGSSheet->MoveWindow(&rcClient);
                m_pDailyGSSheet->ShowWindow(SW_NORMAL);
            }
            m_pDailyGSSheet->Init();
            break;

        default: break;
    }

    return 0;
}

