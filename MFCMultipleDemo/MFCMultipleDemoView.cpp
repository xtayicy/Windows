// MFCMultipleDemoView.cpp : implementation of the CMFCMultipleDemoView class
//

#include "stdafx.h"
#include "MFCMultipleDemo.h"

#include "MFCMultipleDemoDoc.h"
#include "MFCMultipleDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCMultipleDemoView

IMPLEMENT_DYNCREATE(CMFCMultipleDemoView, CView)

BEGIN_MESSAGE_MAP(CMFCMultipleDemoView, CView)
	//{{AFX_MSG_MAP(CMFCMultipleDemoView)
	ON_COMMAND(ID_CONTROL_LAST_FILE, OnControlLastFile)
	ON_COMMAND(ID_CONTROL_NEXT_FILE, OnControlNextFile)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCMultipleDemoView construction/destruction

CMFCMultipleDemoView::CMFCMultipleDemoView()
{
	// TODO: add construction code here

}

CMFCMultipleDemoView::~CMFCMultipleDemoView()
{
}

BOOL CMFCMultipleDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMFCMultipleDemoView drawing

void CMFCMultipleDemoView::OnDraw(CDC* pDC)
{
	CMFCMultipleDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMFCMultipleDemoView printing

BOOL CMFCMultipleDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCMultipleDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCMultipleDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMFCMultipleDemoView diagnostics

#ifdef _DEBUG
void CMFCMultipleDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCMultipleDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCMultipleDemoDoc* CMFCMultipleDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCMultipleDemoDoc)));
	return (CMFCMultipleDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCMultipleDemoView message handlers

void CMFCMultipleDemoView::OnControlLastFile() 
{
	// TODO: Add your command handler code here
	
}

void CMFCMultipleDemoView::OnControlNextFile() 
{
	// TODO: Add your command handler code here
	
}
