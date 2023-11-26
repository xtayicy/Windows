// DatabaseDemoSet.cpp : implementation of the CDatabaseDemoSet class
//

#include "stdafx.h"
#include "DatabaseDemo.h"
#include "DatabaseDemoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDemoSet implementation

IMPLEMENT_DYNAMIC(CDatabaseDemoSet, CRecordset)

CDatabaseDemoSet::CDatabaseDemoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDatabaseDemoSet)
	m_username = _T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CDatabaseDemoSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=DbDemo");
}

CString CDatabaseDemoSet::GetDefaultSQL()
{
	return _T("[Person]");
}

void CDatabaseDemoSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDatabaseDemoSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[username]"), m_username);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDemoSet diagnostics

#ifdef _DEBUG
void CDatabaseDemoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDatabaseDemoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
