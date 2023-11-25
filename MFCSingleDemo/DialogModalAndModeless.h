#if !defined(AFX_DIALOGMODALANDMODELESS_H__8F1A0FCF_6F24_4132_9231_400C04669F2B__INCLUDED_)
#define AFX_DIALOGMODALANDMODELESS_H__8F1A0FCF_6F24_4132_9231_400C04669F2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogModalAndModeless.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogModalAndModeless dialog

class CDialogModalAndModeless : public CDialog
{
// Construction
public:
	CDialogModalAndModeless(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogModalAndModeless)
	enum { IDD = IDD_DIALOG };
	CString	m_pText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogModalAndModeless)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogModalAndModeless)
	afx_msg void OnDialogModal();
	afx_msg void OnDialogModeless();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGMODALANDMODELESS_H__8F1A0FCF_6F24_4132_9231_400C04669F2B__INCLUDED_)
