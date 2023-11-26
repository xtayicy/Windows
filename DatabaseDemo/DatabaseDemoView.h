// DatabaseDemoView.h : interface of the CDatabaseDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASEDEMOVIEW_H__C0713E53_AE27_4668_886A_C19CCB8380E6__INCLUDED_)
#define AFX_DATABASEDEMOVIEW_H__C0713E53_AE27_4668_886A_C19CCB8380E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDatabaseDemoSet;

class CDatabaseDemoView : public CRecordView
{
protected: // create from serialization only
	CDatabaseDemoView();
	DECLARE_DYNCREATE(CDatabaseDemoView)

public:
	//{{AFX_DATA(CDatabaseDemoView)
	enum { IDD = IDD_DATABASEDEMO_FORM };
	CDatabaseDemoSet* m_pSet;
	CString	m_username;
	//}}AFX_DATA

// Attributes
public:
	CDatabaseDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseDemoView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDatabaseDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDatabaseDemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DatabaseDemoView.cpp
inline CDatabaseDemoDoc* CDatabaseDemoView::GetDocument()
   { return (CDatabaseDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATABASEDEMOVIEW_H__C0713E53_AE27_4668_886A_C19CCB8380E6__INCLUDED_)
