// ChildProcessDlg.h : header file
//

#if !defined(AFX_CHILDPROCESSDLG_H__F0FFC56C_F574_41E5_B2A7_19BF27ED2FAD__INCLUDED_)
#define AFX_CHILDPROCESSDLG_H__F0FFC56C_F574_41E5_B2A7_19BF27ED2FAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChildProcessDlg dialog

class CChildProcessDlg : public CDialog
{
// Construction
public:
	HANDLE m_hInherited;
	HANDLE m_hThread;
	CChildProcessDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChildProcessDlg)
	enum { IDD = IDD_CHILDPROCESS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildProcessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChildProcessDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDPROCESSDLG_H__F0FFC56C_F574_41E5_B2A7_19BF27ED2FAD__INCLUDED_)
