// DialogModalAndModeless.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleDemo.h"
#include "DialogModalAndModeless.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogModalAndModeless dialog


CDialogModalAndModeless::CDialogModalAndModeless(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogModalAndModeless::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogModalAndModeless)
	m_pText = _T("");
	//}}AFX_DATA_INIT
}


void CDialogModalAndModeless::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogModalAndModeless)
	DDX_Text(pDX, IDC_TEXT, m_pText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogModalAndModeless, CDialog)
	//{{AFX_MSG_MAP(CDialogModalAndModeless)
	ON_COMMAND(ID_DIALOG_MODAL, OnDialogModal)
	ON_COMMAND(ID_DIALOG_MODELESS, OnDialogModeless)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogModalAndModeless message handlers

void CDialogModalAndModeless::OnDialogModal() 
{
	// TODO: Add your command handler code here
}

void CDialogModalAndModeless::OnDialogModeless() 
{
	// TODO: Add your command handler code here
	
}
