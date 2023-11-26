// DatabaseDemoDoc.cpp : implementation of the CDatabaseDemoDoc class
//

#include "stdafx.h"
#include "DatabaseDemo.h"

#include "DatabaseDemoSet.h"
#include "DatabaseDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDemoDoc

IMPLEMENT_DYNCREATE(CDatabaseDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDatabaseDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CDatabaseDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDemoDoc construction/destruction

CDatabaseDemoDoc::CDatabaseDemoDoc()
{
	// TODO: add one-time construction code here

}

CDatabaseDemoDoc::~CDatabaseDemoDoc()
{
}

BOOL CDatabaseDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDatabaseDemoDoc serialization

void CDatabaseDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDemoDoc diagnostics

#ifdef _DEBUG
void CDatabaseDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDatabaseDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDemoDoc commands
