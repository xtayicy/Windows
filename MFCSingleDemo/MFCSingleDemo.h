// MFCSingleDemo.h : main header file for the MFCSINGLEDEMO application
//

#if !defined(AFX_MFCSINGLEDEMO_H__F5F75D01_53FE_4E5F_95EB_EA04749A5E82__INCLUDED_)
#define AFX_MFCSINGLEDEMO_H__F5F75D01_53FE_4E5F_95EB_EA04749A5E82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCSingleDemoApp:
// See MFCSingleDemo.cpp for the implementation of this class
//

class CMFCSingleDemoApp : public CWinApp
{
public:
	CMFCSingleDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCSingleDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMFCSingleDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCSINGLEDEMO_H__F5F75D01_53FE_4E5F_95EB_EA04749A5E82__INCLUDED_)
