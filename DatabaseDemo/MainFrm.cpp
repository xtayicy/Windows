// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DatabaseDemo.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_DATABASE_TEST, OnDatabaseTest)
	ON_COMMAND(ID_DATABASE_MYSQL, OnDatabaseMysql)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnDatabaseTest() 
{
	// TODO: Add your command handler code here
	char *sql = "Insert into Person values('Marry')";
	HENV henv;
	HDBC hdbc;
	RETCODE rc;
	char username[10];
	char password[10];
	char sourcename[30];
// SWORD LenSourceName;
 //SWORD LenSourceDescription;
 HSTMT FAR *phstmt;
 phstmt=(HSTMT FAR *)malloc(sizeof(HSTMT FAR));
// char * token;
 strcpy(sourcename,"DbDemo");
 strcpy(username,"root");
 strcpy(password,"root");
 rc=SQLAllocEnv(&henv);
 if(rc==SQL_SUCCESS)
 {
	rc=SQLAllocConnect(henv,&hdbc);
	if(rc==SQL_SUCCESS)
	{
	 rc=SQLConnect(hdbc,(UCHAR *)sourcename,SQL_NTS,(UCHAR *)username,SQL_NTS,(UCHAR *)password,SQL_NTS);
	 if(rc==SQL_SUCCESS||rc==SQL_SUCCESS_WITH_INFO)
		 rc=SQLAllocStmt(hdbc,phstmt);
	     rc=SQLExecDirect(*phstmt,(UCHAR FAR *)sql,SQL_NTS);
		 SQLDisconnect(hdbc);
	}
    SQLFreeConnect(hdbc);
 }

 SQLFreeEnv(henv);
}

void CMainFrame::OnDatabaseMysql() 
{
	// TODO: Add your command handler code here
	
}
