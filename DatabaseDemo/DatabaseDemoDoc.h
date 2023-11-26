// DatabaseDemoDoc.h : interface of the CDatabaseDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASEDEMODOC_H__0D1FA812_60DD_4D7B_92CF_871EF0DD8024__INCLUDED_)
#define AFX_DATABASEDEMODOC_H__0D1FA812_60DD_4D7B_92CF_871EF0DD8024__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DatabaseDemoSet.h"


class CDatabaseDemoDoc : public CDocument
{
protected: // create from serialization only
	CDatabaseDemoDoc();
	DECLARE_DYNCREATE(CDatabaseDemoDoc)

// Attributes
public:
	CDatabaseDemoSet m_databaseDemoSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDatabaseDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDatabaseDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATABASEDEMODOC_H__0D1FA812_60DD_4D7B_92CF_871EF0DD8024__INCLUDED_)
