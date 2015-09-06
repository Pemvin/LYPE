// PageThree.cpp : implementation file
//

#include "stdafx.h"
#include "LYPESoldering.h"
#include "PageThree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageThree dialog


CPageThree::CPageThree(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPageThree::IDD, pParent)
	, m_CircleDelay(0)
{
	//{{AFX_DATA_INIT(CPageThree)
	m_ZUpDistance = 0.0;
	m_SilkBackDelay = 0.0;
	m_SilkManualSpd = 0;
	m_SilkBackSpd = 0;
	m_TempRatio = 0.0;
	m_SilkDetect = FALSE;
	//}}AFX_DATA_INIT
}


void CPageThree::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageThree)
	DDX_Text(pDX, IDC_ZUP, m_ZUpDistance);
	DDV_MinMaxDouble(pDX, m_ZUpDistance, 0., 20.);
	DDX_Text(pDX, IDC_SILKBACKDELAY, m_SilkBackDelay);
	DDX_Text(pDX, IDC_SILKMANUALSPD, m_SilkManualSpd);
	DDV_MinMaxInt(pDX, m_SilkManualSpd, 0, 100);
	DDX_Text(pDX, IDC_SILKBACKSPD, m_SilkBackSpd);
	DDX_Text(pDX, IDC_TEMPORATURERATIO, m_TempRatio);
	DDV_MinMaxDouble(pDX, m_TempRatio, 0.1, 1.5);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_SILKDETECT, m_SilkDetect);
	DDX_Text(pDX, IDC_CIRCLEDELAY, m_CircleDelay);
	DDV_MinMaxDouble(pDX, m_CircleDelay, 0, 100);
}


BEGIN_MESSAGE_MAP(CPageThree, CDialogEx)
	//{{AFX_MSG_MAP(CPageThree)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageThree message handlers
