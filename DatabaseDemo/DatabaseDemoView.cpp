// DatabaseDemoView.cpp : implementation of the CDatabaseDemoView class
//

#include "stdafx.h"
#include "DatabaseDemo.h"

#include "DatabaseDemoSet.h"
#include "DatabaseDemoDoc.h"
#include "DatabaseDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDemoView

IMPLEMENT_DYNCREATE(CDatabaseDemoView, CRecordView)

BEGIN_MESSAGE_MAP(CDatabaseDemoView, CRecordView)
	//{{AFX_MSG_MAP(CDatabaseDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDemoView construction/destruction

CDatabaseDemoView::CDatabaseDemoView()
	: CRecordView(CDatabaseDemoView::IDD)
{
	//{{AFX_DATA_INIT(CDatabaseDemoView)
	m_pSet = NULL;
	m_username = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CDatabaseDemoView::~CDatabaseDemoView()
{
}

void CDatabaseDemoView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseDemoView)
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_username);
	//}}AFX_DATA_MAP
}

BOOL CDatabaseDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CDatabaseDemoView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_databaseDemoSet;
	CRecordView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDemoView printing

BOOL CDatabaseDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDatabaseDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDatabaseDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDemoView diagnostics

#ifdef _DEBUG
void CDatabaseDemoView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CDatabaseDemoView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CDatabaseDemoDoc* CDatabaseDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDatabaseDemoDoc)));
	return (CDatabaseDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDemoView database support
CRecordset* CDatabaseDemoView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseDemoView message handlers
