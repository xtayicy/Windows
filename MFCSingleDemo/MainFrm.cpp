// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MFCSingleDemo.h"

#include "MainFrm.h"
#include "DialogModalAndModeless.h"

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
	ON_COMMAND(ID_DIALOG_MODAL, OnDialogModal)
	ON_COMMAND(ID_DIALOG_MODELESS, OnDialogModeless)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
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


void CMainFrame::OnDialogModal() 
{
	// TODO: Add your command handler code here
	CDialogModalAndModeless modalDialog;
	modalDialog.m_pText = "当前是模态对话框";
	modalDialog.DoModal();
}

void CMainFrame::OnDialogModeless() 
{
	// TODO: Add your command handler code here
	CDialogModalAndModeless *modelessDialog;
	modelessDialog = new CDialogModalAndModeless(this);
	modelessDialog->m_pText = "当前是非模态对话框";
	modelessDialog->Create(IDD_DIALOG);
	modelessDialog->ShowWindow(SW_RESTORE);
}

void CMainFrame::OnFileOpen() 
{
	// TODO: Add your command handler code here hide readonly
	CFileDialog fileDialog(TRUE,NULL,NULL,OFN_HIDEREADONLY,"All File(*.*)|*.*||",NULL);
	CFile file;
	CFileStatus fileStatus;
	CString information,filename,fileSize,createTime;

	fileDialog.DoModal();
	CString fileName = fileDialog.GetFileName();
	file.GetStatus(fileName,fileStatus);
	filename.Format("文件名：%s",fileName);
	fileSize.Format("\n文件大小：%d字节",fileStatus.m_size);
	createTime = fileStatus.m_ctime.Format("\n创建时间：%Y年%m月%d日");
	information = filename + fileSize + createTime;
	MessageBox(information);
}
