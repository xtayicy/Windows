// MFCMultipleDemo.h : main header file for the MFCMULTIPLEDEMO application
//

#if !defined(AFX_MFCMULTIPLEDEMO_H__39D5DEF6_8645_4D33_84A1_315A8FCEBCC2__INCLUDED_)
#define AFX_MFCMULTIPLEDEMO_H__39D5DEF6_8645_4D33_84A1_315A8FCEBCC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCMultipleDemoApp:
// See MFCMultipleDemo.cpp for the implementation of this class
//

class CMFCMultipleDemoApp : public CWinApp
{
public:
	CMFCMultipleDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCMultipleDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMFCMultipleDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCMULTIPLEDEMO_H__39D5DEF6_8645_4D33_84A1_315A8FCEBCC2__INCLUDED_)
