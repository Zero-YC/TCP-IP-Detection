
// DetecForTCPDlg.h : ͷ�ļ�
//

#pragma once
#include"MyFunction.h"
#include "afxcmn.h"

// CDetecForTCPDlg �Ի���
class CDetecForTCPDlg : public CDialogEx
{
// ����
public:
	CDetecForTCPDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DETECFORTCP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CFont myfont;
public:
	afx_msg void OnBnClickedOk();
	CMyFunction Function;
	CIPAddressCtrl m_IPadress;
	int m_Port;
	void ResultStatue(bool result);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString IPinfor;
	int m_timer;
	afx_msg void OnBnClickedReset();
};
