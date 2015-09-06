// PageOne.cpp : implementation file
//

#include "stdafx.h"
#include "LYPESoldering.h"
#include "PageOne.h"
#include "SystemSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageOne dialog


CPageOne::CPageOne(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPageOne::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageOne)
	m_PulsePerMmX = 0;
	m_PulsePerMmY = 0;
	m_PulsePerMmZ = 0;
	m_MessageEnable = FALSE;
	m_ZUpDistance = 0.0;
	//}}AFX_DATA_INIT
	m_OriginX = 0.0;
	m_OriginY = 0.0;
	m_OriginZ = 0.0;
	m_BackToOrigin=FALSE;
	m_TempRatio = 0.0;
	m_ZMaxCoor = 0.0;
	m_XMaxCoor = 0.0;
	m_XMinCoor = 0.0;
	m_YMaxCoor = 0.0;
	m_YMinCoor = 0.0;
	m_ZMinCoor = 0.0;
}


void CPageOne::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageOne)
	DDX_Text(pDX, IDC_PULSEPERMMX, m_PulsePerMmX);
	DDX_Text(pDX, IDC_PULSEPERMMY, m_PulsePerMmY);
	DDX_Text(pDX, IDC_PULSEPERMMZ, m_PulsePerMmZ);
	DDX_Check(pDX, IDC_MESSAGEENABLE, m_MessageEnable);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_ZUP, m_ZUpDistance);
	DDV_MinMaxDouble(pDX, m_ZUpDistance, 0., 20.);
	DDX_Text(pDX, IDC_CIRCLEDELAY, m_CircleDelay);
	DDV_MinMaxDouble(pDX, m_CircleDelay, 0, 100);
	DDX_Check(pDX, IDC_BackToOrigin, m_BackToOrigin);
	DDX_Text(pDX, IDC_OriginX, m_OriginX);
	DDX_Text(pDX, IDC_OriginY, m_OriginY);
	DDX_Text(pDX, IDC_OriginZ, m_OriginZ);
	DDX_Text(pDX, IDC_TEMPORATURERATIO, m_TempRatio);
	DDV_MinMaxDouble(pDX, m_TempRatio, 0.1, 1.5);
	DDX_Text(pDX, IDC_ZMAXCOOR, m_ZMaxCoor);
	DDX_Text(pDX, IDC_XMAXCOOR, m_XMaxCoor);
	DDX_Text(pDX, IDC_XMINCOOR, m_XMinCoor);
	DDX_Text(pDX, IDC_YMAXCOOR, m_YMaxCoor);
	DDX_Text(pDX, IDC_YMINCOOR, m_YMinCoor);
	DDX_Text(pDX, IDC_ZMINCOOR, m_ZMinCoor);
}


BEGIN_MESSAGE_MAP(CPageOne, CDialogEx)
	//{{AFX_MSG_MAP(CPageOne)
	ON_BN_CLICKED(IDC_DIRECTIONLOGICX, OnDirectionlogicx)
	ON_BN_CLICKED(IDC_DIRECTIONLOGICY, OnDirectionlogicy)
	ON_BN_CLICKED(IDC_DIRECTIONLOGICZ, OnDirectionlogicz)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageOne message handlers

/*BOOL CPageOne::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	CLYPESolderingApp *p1 = (CLYPESoldering *)AfxGetApp();
	::SendMessage(GetParent()->m_hWnd,WM_COMMAND,wParam,lParam);
	return CDialogEx::OnCommand(wParam, lParam);
}*/

void CPageOne::OnDirectionlogicx() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	if(m_DirLogic[0])
	{
		m_DirLogic[0]=FALSE;
		SetDlgItemText(IDC_DIRECTIONLOGICX,_T("同相"));
	}
	else
	{
		m_DirLogic[0]=TRUE;
		SetDlgItemText(IDC_DIRECTIONLOGICX,_T("反相"));
	}
}

void CPageOne::OnDirectionlogicy() 
{
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	if(m_DirLogic[1])
	{
		m_DirLogic[1]=FALSE;
		SetDlgItemText(IDC_DIRECTIONLOGICY,_T("同相"));
	}
	else
	{
		m_DirLogic[1]=TRUE;
		SetDlgItemText(IDC_DIRECTIONLOGICY,_T("反相"));
	}
	
}

void CPageOne::OnDirectionlogicz() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	if(m_DirLogic[2])
	{
		m_DirLogic[2]=FALSE;
		SetDlgItemText(IDC_DIRECTIONLOGICZ,_T("同相"));
	}
	else
	{
		m_DirLogic[2]=TRUE;
		SetDlgItemText(IDC_DIRECTIONLOGICZ,_T("反相"));
	}
}
