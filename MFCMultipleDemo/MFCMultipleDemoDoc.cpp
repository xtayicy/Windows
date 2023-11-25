// MFCMultipleDemoDoc.cpp : implementation of the CMFCMultipleDemoDoc class
//

#include "stdafx.h"
#include "MFCMultipleDemo.h"

#include "MFCMultipleDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCMultipleDemoDoc

IMPLEMENT_DYNCREATE(CMFCMultipleDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCMultipleDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CMFCMultipleDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCMultipleDemoDoc construction/destruction

CMFCMultipleDemoDoc::CMFCMultipleDemoDoc()
{
	// TODO: add one-time construction code here

}

CMFCMultipleDemoDoc::~CMFCMultipleDemoDoc()
{
}

BOOL CMFCMultipleDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMFCMultipleDemoDoc serialization

void CMFCMultipleDemoDoc::Serialize(CArchive& ar)
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
// CMFCMultipleDemoDoc diagnostics

#ifdef _DEBUG
void CMFCMultipleDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCMultipleDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCMultipleDemoDoc commands
