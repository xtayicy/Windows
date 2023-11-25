// ScrollDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSingleDemo.h"
#include "ScrollDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScrollDlg dialog


CScrollDlg::CScrollDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScrollDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScrollDlg)
	m_nScroll = 0;
	//}}AFX_DATA_INIT
}


void CScrollDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScrollDlg)
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Slider(pDX, IDC_SLIDER1, m_nScroll);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScrollDlg, CDialog)
	//{{AFX_MSG_MAP(CScrollDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollDlg message handlers

BOOL CScrollDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_slider.SetRange(1,5);
	m_slider.SetPos(m_nScroll);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScrollDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_nScroll = m_slider.GetPos();
	CDialog::OnOK();
}
