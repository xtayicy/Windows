// ADODlg.cpp : implementation file
//

#include "stdafx.h"
#include "DatabaseDemo.h"
#include "ADODlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ADODlg dialog


ADODlg::ADODlg(CWnd* pParent /*=NULL*/)
	: CDialog(ADODlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ADODlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ADODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ADODlg)
	DDX_Control(pDX, IDC_LIST1, m_Grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ADODlg, CDialog)
	//{{AFX_MSG_MAP(ADODlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ADODlg message handlers

void ADODlg::OnInitADOConn()
{
	try{
		m_pConnection.CreateInstance("ADODB.Connection");
		CString strConnect = "DRIVER={Microsoft Access Driver (*.mdb)};uid=root;pwd=root;DBQ=A.mdb;";
		m_pConnection->Open((_bstr_t)strConnect,"","",adModeUnknown);
	}catch(_com_error e){
		AfxMessageBox(e.Description());
	}
}

void ADODlg::ExitConnect()
{
	if(m_pRecordset != NULL){
		m_pRecordset->Close();
	}
	
	m_pConnection->Close();
}

BOOL ADODlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Grid.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);
	m_Grid.InsertColumn(1,"ÐÕÃû",LVCFMT_LEFT,60,0);
	AddToGrid();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ADODlg::AddToGrid()
{
	OnInitADOConn();
	_bstr_t bstrSQL = "select * from Person";
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordset->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	while(!m_pRecordset->adoEOF){
		m_Grid.InsertItem(0,"");
		m_Grid.SetItemText(0,0,(char*)(_bstr_t)m_pRecordset->GetCollect("username"));
		m_pRecordset->MoveNext();
	}

	ExitConnect();
}
