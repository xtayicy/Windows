#if !defined(AFX_ADODLG_H__2024F5AD_1348_4284_8B9A_7257DA433DF3__INCLUDED_)
#define AFX_ADODLG_H__2024F5AD_1348_4284_8B9A_7257DA433DF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ADODlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ADODlg dialog

class ADODlg : public CDialog
{
// Construction
public:
	void AddToGrid();
	void ExitConnect();
	void OnInitADOConn();
	_RecordsetPtr m_pRecordset;
	_ConnectionPtr m_pConnection;
	ADODlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ADODlg)
	enum { IDD = IDD_DIALOG1 };
	CListCtrl	m_Grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ADODlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ADODlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADODLG_H__2024F5AD_1348_4284_8B9A_7257DA433DF3__INCLUDED_)
