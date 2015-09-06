// PageTwo.cpp : implementation file
//

#include "stdafx.h"
#include "LYPESoldering.h"
#include "PageTwo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageTwo dialog
int idHoDir[]={IDC_HOMEDIRECTIONX,IDC_HOMEDIRECTIONY,IDC_HOMEDIRECTIONZ};
int idHoZLogic[]={IDC_HOMEZLOGICX,IDC_HOMEZLOGICY,IDC_HOMEZLOGICZ};
int idHoOrgLogic[]={IDC_HOMEORGLOGICX,IDC_HOMEORGLOGICY,IDC_HOMEORGLOGICZ};
int idHoLimitLogic[]={IDC_HOMELIMITLOGICX,IDC_HOMELIMITLOGICY,IDC_HOMELIMITLOGICZ};

CPageTwo::CPageTwo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPageTwo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageTwo)
	m_HomeVelXAcc = 0;
	m_HomeVelXHigh = 0;
	m_HomeVelXLow = 0;
	m_HomeVelYAcc = 0;
	m_HomeVelYHigh = 0;
	m_HomeVelYLow = 0;
	m_HomeVelZAcc = 0;
	m_HomeVelZHigh = 0;
	m_HomeVelZLow = 0;
	m_ManualVelXAcc = 0;
	m_ManualVelXDec = 0;
	m_ManualVelXHigh = 0;
	m_ManualVelXLow = 0;
	m_ManualVelYAcc = 0;
	m_ManualVelYDec = 0;
	m_ManualVelYHigh = 0;
	m_ManualVelYLow = 0;
	m_ManualVelZAcc = 0;
	m_ManualVelZDec = 0;
	m_ManualVelZHigh = 0;
	m_ManualVelZLow = 0;
	m_AutoMaxVelX = 0;
	m_AutoMaxVelY = 0;
	m_AutoMaxVelZ = 0;
	//}}AFX_DATA_INIT
}


void CPageTwo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageTwo)
	DDX_Text(pDX, IDC_HOMEVELXACC, m_HomeVelXAcc);
	DDX_Text(pDX, IDC_HOMEVELXHIGH, m_HomeVelXHigh);
	DDX_Text(pDX, IDC_HOMEVELXLOW, m_HomeVelXLow);
	DDX_Text(pDX, IDC_HOMEVELYACC, m_HomeVelYAcc);
	DDX_Text(pDX, IDC_HOMEVELYHIGH, m_HomeVelYHigh);
	DDX_Text(pDX, IDC_HOMEVELYLOW, m_HomeVelYLow);
	DDX_Text(pDX, IDC_HOMEVELZACC, m_HomeVelZAcc);
	DDX_Text(pDX, IDC_HOMEVELZHIGH, m_HomeVelZHigh);
	DDX_Text(pDX, IDC_HOMEVELZLOW, m_HomeVelZLow);
	DDX_Text(pDX, IDC_MANUALVELXACC, m_ManualVelXAcc);
	DDX_Text(pDX, IDC_MANUALVELXDEC, m_ManualVelXDec);
	DDX_Text(pDX, IDC_MANUALVELXHIGH, m_ManualVelXHigh);
	DDX_Text(pDX, IDC_MANUALVELXLOW, m_ManualVelXLow);
	DDX_Text(pDX, IDC_MANUALVELYACC, m_ManualVelYAcc);
	DDX_Text(pDX, IDC_MANUALVELYDEC, m_ManualVelYDec);
	DDX_Text(pDX, IDC_MANUALVELYHIGH, m_ManualVelYHigh);
	DDX_Text(pDX, IDC_MANUALVELYLOW, m_ManualVelYLow);
	DDX_Text(pDX, IDC_MANUALVELZACC, m_ManualVelZAcc);
	DDX_Text(pDX, IDC_MANUALVELZDEC, m_ManualVelZDec);
	DDX_Text(pDX, IDC_MANUALVELZHIGH, m_ManualVelZHigh);
	DDX_Text(pDX, IDC_MANUALVELZLOW, m_ManualVelZLow);
	DDX_Text(pDX, IDC_AUTOMAXVELX, m_AutoMaxVelX);
	DDX_Text(pDX, IDC_AUTOMAXVELY, m_AutoMaxVelY);
	DDX_Text(pDX, IDC_AUTOMAXVELZ, m_AutoMaxVelZ);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageTwo, CDialogEx)
	//{{AFX_MSG_MAP(CPageTwo)
	ON_BN_CLICKED(IDC_HOMEDIRECTIONX, OnHomedirectionx)
	ON_BN_CLICKED(IDC_HOMEDIRECTIONY, OnHomedirectionx)
	ON_BN_CLICKED(IDC_HOMEDIRECTIONZ, OnHomedirectionx)

	ON_BN_CLICKED(IDC_HOMEZLOGICX, OnHomezlogicx)
	ON_BN_CLICKED(IDC_HOMEZLOGICY, OnHomezlogicx)
	ON_BN_CLICKED(IDC_HOMEZLOGICZ, OnHomezlogicx)

	ON_BN_CLICKED(IDC_HOMEORGLOGICX, OnHomeorglogicx)
	ON_BN_CLICKED(IDC_HOMEORGLOGICY, OnHomeorglogicx)
	ON_BN_CLICKED(IDC_HOMEORGLOGICZ, OnHomeorglogicx)

	ON_BN_CLICKED(IDC_HOMELIMITLOGICX, OnHomelimitlogicx)
	ON_BN_CLICKED(IDC_HOMELIMITLOGICY, OnHomelimitlogicx)
	ON_BN_CLICKED(IDC_HOMELIMITLOGICZ, OnHomelimitlogicx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageTwo message handlers

BOOL CPageTwo::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialogEx::OnCommand(wParam, lParam);
}

BOOL CPageTwo::OnInitDialog() 
{
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageTwo::OnHomedirectionx() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	int nID=GetFocus()->GetDlgCtrlID();
	int pos;
	for(pos=0;pos<MAXAXISCOUNT;pos++)
		if(nID!=idHoDir[pos])	continue;
		else	break;
	if(m_HomeDirection[pos])
	{
		m_HomeDirection[pos]=FALSE;
		SetDlgItemText(nID,_T("正相"));
	}
	else
	{
		m_HomeDirection[pos]=TRUE;
		SetDlgItemText(nID,_T("反相"));
	}
}

void CPageTwo::OnHomezlogicx() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	int nID=GetFocus()->GetDlgCtrlID();
	int pos;
	for(pos=0;pos<MAXAXISCOUNT;pos++)
		if(nID!=idHoZLogic[pos])	continue;
		else	break;
	if(m_HomeZLogic[pos])
	{
		m_HomeZLogic[pos]=FALSE;
		SetDlgItemText(nID,_T("正相"));
	}
	else
	{
		m_HomeZLogic[pos]=TRUE;
		SetDlgItemText(nID,_T("反相"));
	}
}

void CPageTwo::OnHomeorglogicx() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	int nID=GetFocus()->GetDlgCtrlID();
	int pos;
	for(pos=0;pos<MAXAXISCOUNT;pos++)
		if(nID!=idHoOrgLogic[pos])	continue;
		else	break;
	if(m_HomeOrgLogic[pos])
	{
		m_HomeOrgLogic[pos]=FALSE;
		SetDlgItemText(nID,_T("正相"));
	}
	else
	{
		m_HomeOrgLogic[pos]=TRUE;
		SetDlgItemText(nID,_T("反相"));
	}
}

void CPageTwo::OnHomelimitlogicx() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	int nID=GetFocus()->GetDlgCtrlID();
	int pos;
	for(pos=0;pos<MAXAXISCOUNT;pos++)
		if(nID!=idHoLimitLogic[pos])	continue;
		else	break;
	if(m_HomeLimitLogic[pos])
	{
		m_HomeLimitLogic[pos]=FALSE;
		SetDlgItemText(nID,_T("正相"));
	}
	else
	{
		m_HomeLimitLogic[pos]=TRUE;
		SetDlgItemText(nID,_T("反相"));
	}
}
