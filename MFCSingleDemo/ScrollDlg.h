#if !defined(AFX_SCROLLDLG_H__8BAD9BE4_4F77_4D31_82FB_2FC2781BAAF9__INCLUDED_)
#define AFX_SCROLLDLG_H__8BAD9BE4_4F77_4D31_82FB_2FC2781BAAF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScrollDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScrollDlg dialog

class CScrollDlg : public CDialog
{
// Construction
public:
	CScrollDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScrollDlg)
	enum { IDD = IDD_DIALOG_SCROLL };
	CSliderCtrl	m_slider;
	int		m_nScroll;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScrollDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCROLLDLG_H__8BAD9BE4_4F77_4D31_82FB_2FC2781BAAF9__INCLUDED_)
