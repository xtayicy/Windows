// DatabaseDemoSet.h : interface of the CDatabaseDemoSet class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASEDEMOSET_H__0F1A0CC8_5CE9_4566_92A0_A338199E8BC7__INCLUDED_)
#define AFX_DATABASEDEMOSET_H__0F1A0CC8_5CE9_4566_92A0_A338199E8BC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDatabaseDemoSet : public CRecordset
{
public:
	CDatabaseDemoSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDatabaseDemoSet)

// Field/Param Data
	//{{AFX_FIELD(CDatabaseDemoSet, CRecordset)
	CString	m_username;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseDemoSet)
	public:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATABASEDEMOSET_H__0F1A0CC8_5CE9_4566_92A0_A338199E8BC7__INCLUDED_)

