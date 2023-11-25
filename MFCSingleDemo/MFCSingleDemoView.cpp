// MFCSingleDemoView.cpp : implementation of the CMFCSingleDemoView class
//

#include "stdafx.h"
#include "MFCSingleDemo.h"

#include "MFCSingleDemoDoc.h"
#include "MFCSingleDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCSingleDemoView

IMPLEMENT_DYNCREATE(CMFCSingleDemoView, CView)

BEGIN_MESSAGE_MAP(CMFCSingleDemoView, CView)
	//{{AFX_MSG_MAP(CMFCSingleDemoView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_COLOR_BLACK, OnColorBlack)
	ON_COMMAND(ID_COLOR_BLUE, OnColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, OnUpdateColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, OnUpdateColorBlue)
	ON_COMMAND(ID_COLOR_RED, OnColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, OnUpdateColorRed)
	ON_COMMAND(ID_COLOR_YELLOW, OnColorYellow)
	ON_UPDATE_COMMAND_UI(ID_COLOR_YELLOW, OnUpdateColorYellow)
	ON_COMMAND(ID_COLOR_CUSTOM, OnColorCustom)
	ON_UPDATE_COMMAND_UI(ID_COLOR_CUSTOM, OnUpdateColorCustom)
	ON_WM_CREATE()
	ON_WM_CANCELMODE()
	ON_WM_CAPTURECHANGED()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCSingleDemoView construction/destruction

CMFCSingleDemoView::CMFCSingleDemoView()
{
	// TODO: add construction code here
	m_nScroll = 1;
}

CMFCSingleDemoView::~CMFCSingleDemoView()
{
}

BOOL CMFCSingleDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMFCSingleDemoView drawing

void CMFCSingleDemoView::OnDraw(CDC* pDC)
{
	CMFCSingleDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMFCSingleDemoView printing

BOOL CMFCSingleDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCSingleDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCSingleDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMFCSingleDemoView diagnostics

#ifdef _DEBUG
void CMFCSingleDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCSingleDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCSingleDemoDoc* CMFCSingleDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCSingleDemoDoc)));
	return (CMFCSingleDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCSingleDemoView message handlers

void CMFCSingleDemoView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_ptStart = point;
	m_ptEnd = point;
	SetCapture();
	m_isDragging = true;
	CView::OnLButtonDown(nFlags, point);
}

void CMFCSingleDemoView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
	if(m_isDragging){
		CClientDC cDC(this);
		cDC.SetROP2(R2_NOT);
		cDC.MoveTo(m_ptStart);
		cDC.LineTo(m_ptEnd);
		cDC.MoveTo(m_ptStart);
		cDC.LineTo(point);
		m_ptEnd = point;
	}

	CView::OnMouseMove(nFlags, point);
}

void CMFCSingleDemoView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_isDragging){
		m_isDragging = false;
		ReleaseCapture();
		CClientDC cDC(this);
		CPen pen, *pOldPen;
		pen.CreatePen(PS_SOLID,1,m_currentColor);
		pOldPen=cDC.SelectObject(&pen);
		cDC.MoveTo(m_ptStart);
		cDC.LineTo(point);
		cDC.SelectObject(pOldPen);
		m_ptEnd = point;
	}

	CView::OnLButtonUp(nFlags, point);
}

void CMFCSingleDemoView::OnColorBlack() 
{
	// TODO: Add your command handler code here
	m_currentColor = RGB(0,0,0);
	m_currentId = ID_COLOR_BLACK;
}

void CMFCSingleDemoView::OnUpdateColorBlack(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_currentId ==ID_COLOR_BLACK ? 1 : 0);
}

void CMFCSingleDemoView::OnColorBlue() 
{
	// TODO: Add your command handler code here
	m_currentColor = RGB(0,0,255);
	m_currentId = ID_COLOR_BLUE;
}

void CMFCSingleDemoView::OnUpdateColorBlue(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_currentId ==ID_COLOR_BLUE ? 1 : 0);
}

void CMFCSingleDemoView::OnColorRed() 
{
	// TODO: Add your command handler code here
	m_currentColor = RGB(255,0,0);
	m_currentId = ID_COLOR_RED;
}

void CMFCSingleDemoView::OnUpdateColorRed(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_currentId ==ID_COLOR_RED ? 1 : 0);
}

void CMFCSingleDemoView::OnColorYellow() 
{
	// TODO: Add your command handler code here
	m_currentColor = RGB(255,255,0);
	m_currentId = ID_COLOR_YELLOW;
}

void CMFCSingleDemoView::OnUpdateColorYellow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_currentId ==ID_COLOR_YELLOW ? 1 : 0);
}

void CMFCSingleDemoView::OnColorCustom() 
{
	// TODO: Add your command handler code here
	CColorDialog colorDialog;
	if(colorDialog.DoModal() == IDOK){
		m_currentColor = colorDialog.GetColor();
		m_currentId = ID_COLOR_CUSTOM;
	}
}

void CMFCSingleDemoView::OnUpdateColorCustom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_currentId ==ID_COLOR_CUSTOM ? 1 : 0);
}

int CMFCSingleDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation  code here
	

	return 0;
}

void CMFCSingleDemoView::OnCancelMode() 
{
	CView::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CMFCSingleDemoView::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
	
	CView::OnCaptureChanged(pWnd);
}

void CMFCSingleDemoView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CMFCSingleDemoView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnTimer(nIDEvent);
}

void CMFCSingleDemoView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CView::OnPaint() for painting messages
}
