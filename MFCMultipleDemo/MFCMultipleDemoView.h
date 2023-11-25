// MFCMultipleDemoView.h : interface of the CMFCMultipleDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCMULTIPLEDEMOVIEW_H__C843F048_8167_4551_807A_8E4527DDCD2A__INCLUDED_)
#define AFX_MFCMULTIPLEDEMOVIEW_H__C843F048_8167_4551_807A_8E4527DDCD2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCMultipleDemoView : public CView
{
protected: // create from serialization only
	CMFCMultipleDemoView();
	DECLARE_DYNCREATE(CMFCMultipleDemoView)

// Attributes
public:
	CMFCMultipleDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCMultipleDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMFCMultipleDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCMultipleDemoView)
	afx_msg void OnControlLastFile();
	afx_msg void OnControlNextFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCMultipleDemoView.cpp
inline CMFCMultipleDemoDoc* CMFCMultipleDemoView::GetDocument()
   { return (CMFCMultipleDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCMULTIPLEDEMOVIEW_H__C843F048_8167_4551_807A_8E4527DDCD2A__INCLUDED_)
