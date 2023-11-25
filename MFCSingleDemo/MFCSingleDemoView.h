// MFCSingleDemoView.h : interface of the CMFCSingleDemoView class
//
/////////////////////////////////////////////////////////////////////////////
#include "ScrollDlg.h"

#if !defined(AFX_MFCSINGLEDEMOVIEW_H__C732FE8B_4D98_4556_B5F0_426BD3139C5F__INCLUDED_)
#define AFX_MFCSINGLEDEMOVIEW_H__C732FE8B_4D98_4556_B5F0_426BD3139C5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCSingleDemoView : public CView
{
protected: // create from serialization only
	CMFCSingleDemoView();
	DECLARE_DYNCREATE(CMFCSingleDemoView)

// Attributes
public:
	CMFCSingleDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCSingleDemoView)
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
	virtual ~CMFCSingleDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CPoint m_ptStart;
	CPoint m_ptEnd;
	bool m_isDragging;
	COLORREF m_currentColor;
	int m_currentId;

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCSingleDemoView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnColorBlack();
	afx_msg void OnColorBlue();
	afx_msg void OnUpdateColorBlack(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColorBlue(CCmdUI* pCmdUI);
	afx_msg void OnColorRed();
	afx_msg void OnUpdateColorRed(CCmdUI* pCmdUI);
	afx_msg void OnColorYellow();
	afx_msg void OnUpdateColorYellow(CCmdUI* pCmdUI);
	afx_msg void OnColorCustom();
	afx_msg void OnUpdateColorCustom(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCancelMode();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nScroll;
	UINT_PTR m_nTimer;
};

#ifndef _DEBUG  // debug version in MFCSingleDemoView.cpp
inline CMFCSingleDemoDoc* CMFCSingleDemoView::GetDocument()
   { return (CMFCSingleDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCSINGLEDEMOVIEW_H__C732FE8B_4D98_4556_B5F0_426BD3139C5F__INCLUDED_)
