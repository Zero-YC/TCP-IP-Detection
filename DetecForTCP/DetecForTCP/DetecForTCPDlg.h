
// DetecForTCPDlg.h : 头文件
//

#pragma once
#include"MyFunction.h"
#include "afxcmn.h"

// CDetecForTCPDlg 对话框
class CDetecForTCPDlg : public CDialogEx
{
// 构造
public:
	CDetecForTCPDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DETECFORTCP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
