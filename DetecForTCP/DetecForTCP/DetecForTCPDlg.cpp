
// DetecForTCPDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DetecForTCP.h"
#include "DetecForTCPDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

BEGIN_MESSAGE_MAP(CDetecForTCPDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDCANCEL, &CDetecForTCPDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDetecForTCPDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_STOP, &CDetecForTCPDlg::OnBnClickedStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RESET, &CDetecForTCPDlg::OnBnClickedReset)
END_MESSAGE_MAP()


// CDetecForTCPDlg 对话框



CDetecForTCPDlg::CDetecForTCPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DETECFORTCP_DIALOG, pParent)
	, m_Port(0)
	, m_timer(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDetecForTCPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IPadress);
	DDX_Text(pDX, IDC_EDIT2, m_Port);
	DDX_Text(pDX, IDC_EDIT3, m_timer);
}

// CDetecForTCPDlg 消息处理程序

BOOL CDetecForTCPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect rect;
	GetDlgItem(IDC_BREAK)->GetWindowRect(&rect);
	LOGFONT font;
	memset(&font, 0, sizeof(LOGFONT));
	font.lfHeight = rect.Height();
	font.lfWidth = rect.Width() / 2;
	wcscpy_s(font.lfFaceName, TEXT("黑体"));
	myfont.CreateFontIndirectW(&font);
	//	myfont.CreateFontIndirectW()
	GetDlgItem(IDC_CONNECT)->SetFont(&myfont);
	GetDlgItem(IDC_BREAK)->SetFont(&myfont);
	GetDlgItem(IDC_CONNECT)->SetWindowTextW(TEXT(""));
	GetDlgItem(IDC_BREAK)->SetWindowTextW(TEXT(""));
	GetDlgItem(IDC_STOP)->EnableWindow(0);
	GetDlgItem(IDOK)->EnableWindow(1);
	
	
	//delete myfont;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDetecForTCPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDetecForTCPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CDetecForTCPDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (IDC_CONNECT == pWnd->GetDlgCtrlID())
	{
		/*pDC->SetTextColor(RGB(0, 255, 0));
		pDC->SetBkColor(RGB(0, 0, 0));*/
		pDC->SetBkColor(RGB(0, 255, 0));

	}
	if (IDC_BREAK == pWnd->GetDlgCtrlID())
	{
		/*pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkColor(RGB(0, 0, 0));*/
		pDC->SetBkColor(RGB(255, 0, 0));

	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CDetecForTCPDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	UpdateData(1);
	if (!m_IPadress.IsBlank() && m_Port > 1024&& m_timer>0)
	{
		BYTE nf1, nf2, nf3, nf4;
		m_IPadress.GetAddress(nf1, nf2, nf3, nf4);
		IPinfor.Format(TEXT("%d.%d.%d.%d:%d"), nf1, nf2, nf3, nf4, m_Port);
		SetTimer(1, m_timer,NULL);
		GetDlgItem(IDC_STOP)->EnableWindow(1);
		GetDlgItem(IDOK)->EnableWindow(0); 
		GetDlgItem(IDC_IPADDRESS1)->EnableWindow(0); 
		GetDlgItem(IDC_EDIT2)->EnableWindow(0);
		GetDlgItem(IDC_EDIT3)->EnableWindow(0);
		CTime time = CTime::GetCurrentTime();
		CString str;
		str.Format(TEXT("%d/%d_%d:%d:%d"),time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
		GetDlgItem(IDC_EDIT4)->SetWindowTextW(str);
		
	}
	else
	{
		MessageBox(TEXT("IP或端口号配置错误"));
	}
	
}
void CDetecForTCPDlg::ResultStatue(bool result)
{
	// TODO:  在此添加控件通知处理程序代码
		if (result)
		{
			GetDlgItem(IDC_BREAK)->ShowWindow(0);
			GetDlgItem(IDC_CONNECT)->ShowWindow(1);
			GetDlgItem(IDC_CONNECT)->SetWindowTextW(TEXT("  "));
		}
		else
		{
			GetDlgItem(IDC_BREAK)->ShowWindow(1);
			GetDlgItem(IDC_CONNECT)->ShowWindow(0);
			GetDlgItem(IDC_BREAK)->SetWindowTextW(TEXT("  "));
			CTime time = CTime::GetCurrentTime();
			CString str;
			str.Format(TEXT("%d/%d_%d:%d:%d"), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
			GetDlgItem(IDC_EDIT6)->SetWindowTextW(str);
		}
}




void CDetecForTCPDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedStop();
	CDialogEx::OnCancel();
	
}


void CDetecForTCPDlg::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_STOP)->EnableWindow(0);
	GetDlgItem(IDOK)->EnableWindow(1);
	GetDlgItem(IDC_IPADDRESS1)->EnableWindow(1);
	GetDlgItem(IDC_EDIT2)->EnableWindow(1);
	GetDlgItem(IDC_EDIT3)->EnableWindow(1);
	KillTimer(1);
}


void CDetecForTCPDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		USES_CONVERSION;
		//result = Function.TcpPortState(T2A(IPinfor));
		ResultStatue(Function.TcpPortState(T2A(IPinfor)));
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CDetecForTCPDlg::OnBnClickedReset()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedStop();
	m_IPadress.SetAddress(NULL);
	m_Port = 0;
	m_timer = 0;
	UpdateData(0);
}
