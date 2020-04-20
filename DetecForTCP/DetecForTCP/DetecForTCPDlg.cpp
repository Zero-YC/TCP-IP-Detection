
// DetecForTCPDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DetecForTCP.h"
#include "DetecForTCPDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

BEGIN_MESSAGE_MAP(CDetecForTCPDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDCANCEL, &CDetecForTCPDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDetecForTCPDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_STOP, &CDetecForTCPDlg::OnBnClickedStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RESET, &CDetecForTCPDlg::OnBnClickedReset)
END_MESSAGE_MAP()


// CDetecForTCPDlg �Ի���



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

// CDetecForTCPDlg ��Ϣ�������

BOOL CDetecForTCPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CRect rect;
	GetDlgItem(IDC_BREAK)->GetWindowRect(&rect);
	LOGFONT font;
	memset(&font, 0, sizeof(LOGFONT));
	font.lfHeight = rect.Height();
	font.lfWidth = rect.Width() / 2;
	wcscpy_s(font.lfFaceName, TEXT("����"));
	myfont.CreateFontIndirectW(&font);
	//	myfont.CreateFontIndirectW()
	GetDlgItem(IDC_CONNECT)->SetFont(&myfont);
	GetDlgItem(IDC_BREAK)->SetFont(&myfont);
	GetDlgItem(IDC_CONNECT)->SetWindowTextW(TEXT(""));
	GetDlgItem(IDC_BREAK)->SetWindowTextW(TEXT(""));
	GetDlgItem(IDC_STOP)->EnableWindow(0);
	GetDlgItem(IDOK)->EnableWindow(1);
	
	
	//delete myfont;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDetecForTCPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDetecForTCPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CDetecForTCPDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
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
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CDetecForTCPDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(TEXT("IP��˿ں����ô���"));
	}
	
}
void CDetecForTCPDlg::ResultStatue(bool result)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedStop();
	CDialogEx::OnCancel();
	
}


void CDetecForTCPDlg::OnBnClickedStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_STOP)->EnableWindow(0);
	GetDlgItem(IDOK)->EnableWindow(1);
	GetDlgItem(IDC_IPADDRESS1)->EnableWindow(1);
	GetDlgItem(IDC_EDIT2)->EnableWindow(1);
	GetDlgItem(IDC_EDIT3)->EnableWindow(1);
	KillTimer(1);
}


void CDetecForTCPDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedStop();
	m_IPadress.SetAddress(NULL);
	m_Port = 0;
	m_timer = 0;
	UpdateData(0);
}
