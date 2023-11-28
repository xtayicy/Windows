// InputDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "DatabaseDemo.h"
#include "InputDlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputDlg dialog


CInputDlg::CInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputDlg)
	m_sql = _T("");
	//}}AFX_DATA_INIT
}


void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputDlg)
	DDX_Control(pDX, IDC_LIST2, m_table);
	DDX_Control(pDX, IDC_LIST1, m_show_content);
	DDX_Text(pDX, IDC_EDIT1, m_sql);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialog)
	//{{AFX_MSG_MAP(CInputDlg)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputDlg message handlers

BOOL CInputDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CListBox *plistbox=(CListBox *)GetDlgItem(IDC_LIST1);
	HENV henv;
	HDBC hdbc;
	RETCODE rc;
	HSTMT hstmt;


	UCHAR szTableName[128],szTableType[128];
	SDWORD cbTableName,cbTableType;
	LPCTSTR tmptable;
	tmptable=(char *)malloc(100);
	char username[10];
	char password[10];
	char sourcename[30];
	strcpy(sourcename,"DbDemo");
	strcpy(username,"root");
	strcpy(password,"root");
	SWORD FAR *pcol;
	pcol=(SWORD FAR *)malloc(sizeof(SWORD FAR));
	rc=SQLAllocEnv(&henv);
	if(rc == SQL_SUCCESS){
		//MessageBox("success");
		rc=SQLAllocConnect(henv,&hdbc);
		if(rc == SQL_SUCCESS){
			//MessageBox("success");
			rc=SQLConnect(hdbc,(UCHAR *)sourcename,SQL_NTS,(UCHAR *)username,SQL_NTS,(UCHAR *)password,SQL_NTS);
			if(rc == SQL_SUCCESS){
				//MessageBox("success");
				SQLAllocStmt(hdbc,(HSTMT FAR *)&hstmt);
				rc=SQLTables(hstmt,NULL,0,NULL,0,NULL,0,NULL,0);
				if(rc == SQL_SUCCESS){
					//MessageBox("success");
					SQLNumResultCols(hstmt,pcol);
					SQLBindCol(hstmt,3,SQL_C_CHAR,szTableName,sizeof(szTableName),&cbTableName);
					SQLBindCol(hstmt,4,SQL_C_CHAR,szTableType,sizeof(szTableType),&cbTableType);
					while(TRUE){
						rc=SQLFetch(hstmt);
						if(rc==SQL_SUCCESS||rc==SQL_SUCCESS_WITH_INFO){
							tmptable=(LPCTSTR)szTableName;
							plistbox->InsertString(-1,tmptable);
						}else{
							break;
						}
					}
				}
			}
		}
	}
	
	SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
	SQLDisconnect(hdbc);
	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInputDlg::OnKillfocusEdit1() 
{
	// TODO: Add your control notification handler code here
}

void CInputDlg::OnDblclkList1() 
{
	// TODO: Add your control notification handler code here
	
}

void CInputDlg::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
