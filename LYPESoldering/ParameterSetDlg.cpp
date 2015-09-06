// ParameterSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LYPESoldering.h"
#include "ParameterSetDlg.h"
#include "Externs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL bFirstPoint=TRUE;
BOOL bFirstNum=TRUE;
/////////////////////////////////////////////////////////////////////////////
// CParameterSetDlg dialog


CParameterSetDlg::CParameterSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParameterSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParameterSetDlg)
	m_currentlimit = 0.0;
	m_rmanspeed = 0;
	m_rdotdistance = 0;
	m_rrrturnspeed = 0;
	m_rspeedlimit = 0;
	m_santodistance = 0;
	m_sbackdistance = 0.0;
	m_sbackspeed = 0;
	m_sdotdistance = 0.0;
	m_smandistance = 0;
	m_templimit = 0;
	m_xdotdistance = 0.0;
	m_xmanspeed = 0;
	m_xreturnspeed = 0;
	m_xspeedlimit = 0;
	//}}AFX_DATA_INIT
}


void CParameterSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameterSetDlg)
	DDX_Text(pDX, IDC_CurrentLimit, m_currentlimit);
	DDV_MinMaxInt(pDX, m_currentlimit, 0, 40);
	DDX_Text(pDX, IDC_RManSpeed, m_rmanspeed);
	DDX_Text(pDX, IDC_RDotDistance, m_rdotdistance);
	DDV_MinMaxInt(pDX, m_rdotdistance, 1, 20);
	DDX_Text(pDX, IDC_RReturnSpeed, m_rrrturnspeed);
	DDV_MinMaxInt(pDX, m_rrrturnspeed, 1, 180);
	DDX_Text(pDX, IDC_RSpeedLimit, m_rspeedlimit);
	DDV_MinMaxInt(pDX, m_rspeedlimit, 1, 180);
	DDX_Text(pDX, IDC_SAutoDistance, m_santodistance);
	DDV_MinMaxInt(pDX, m_santodistance, 1, 40);
	DDX_Text(pDX, IDC_SBackDistance, m_sbackdistance);
	DDV_MinMaxDouble(pDX, m_sbackdistance, 0.1, 10.);
	DDX_Text(pDX, IDC_SBackSpeed, m_sbackspeed);
	DDV_MinMaxInt(pDX, m_sbackspeed, 1, 40);
	DDX_Text(pDX, IDC_SDotDistance, m_sdotdistance);
	DDV_MinMaxDouble(pDX, m_sdotdistance, 0.1, 10.);
	DDX_Text(pDX, IDC_SManDistance, m_smandistance);
	DDV_MinMaxInt(pDX, m_smandistance, 1, 40);
	DDX_Text(pDX, IDC_TempLimit, m_templimit);
	DDV_MinMaxInt(pDX, m_templimit, 0, 600);
	DDX_Text(pDX, IDC_XDotDistance, m_xdotdistance);
	DDV_MinMaxDouble(pDX, m_xdotdistance, 0.1, 10.);
	DDX_Text(pDX, IDC_XManSpeed, m_xmanspeed);
	DDV_MinMaxInt(pDX, m_xmanspeed, 1, 200);
	DDX_Text(pDX, IDC_XReturnSpeed, m_xreturnspeed);
	DDV_MinMaxInt(pDX, m_xreturnspeed, 1, 200);
	DDX_Text(pDX, IDC_XSpeedLimit, m_xspeedlimit);
	DDV_MinMaxInt(pDX, m_xspeedlimit, 1, 200);

	DDX_Text(pDX, IDC_YDotDistance, m_ydotdistance);
	DDV_MinMaxDouble(pDX, m_ydotdistance, 0.1, 10.);
	DDX_Text(pDX, IDC_YManSpeed, m_ymanspeed);
	DDV_MinMaxInt(pDX, m_ymanspeed, 1, 200);
	DDX_Text(pDX, IDC_YReturnSpeed, m_yreturnspeed);
	DDV_MinMaxInt(pDX, m_yreturnspeed, 1, 200);
	DDX_Text(pDX, IDC_YSpeedLimit, m_yspeedlimit);
	DDV_MinMaxInt(pDX, m_yspeedlimit, 1, 200);

	DDX_Text(pDX, IDC_ZDotDistance, m_zdotdistance);
	DDV_MinMaxDouble(pDX, m_zdotdistance, 0.1, 10.);
	DDX_Text(pDX, IDC_ZManSpeed, m_zmanspeed);
	DDV_MinMaxInt(pDX, m_zmanspeed, 1, 200);
	DDX_Text(pDX, IDC_ZReturnSpeed, m_zreturnspeed);
	DDV_MinMaxInt(pDX, m_zreturnspeed, 1, 200);
	DDX_Text(pDX, IDC_ZSpeedLimit, m_zspeedlimit);
	DDV_MinMaxInt(pDX, m_zspeedlimit, 1, 200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParameterSetDlg, CDialog)
	//{{AFX_MSG_MAP(CParameterSetDlg)
	ON_BN_CLICKED(IDC_Default, OnDefault)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParameterSetDlg message handlers

void CParameterSetDlg::OnDefault() 
{
	// TODO: Add your control notification handler code here
	//运行参数
	EnterCriticalSection(&cs);
	ObjectInfo.xspeedlimit=100;
	ObjectInfo.yspeedlimit=100;
	ObjectInfo.zspeedlimit=30;
	ObjectInfo.rspeedlimit=100;
	ObjectInfo.xacclimit=10;
	ObjectInfo.yacclimit=10;
	ObjectInfo.zacclimit=10;
	ObjectInfo.racclimit=10;
	ObjectInfo.xdotdistance=0.1;
	ObjectInfo.ydotdistance=0.1;
	ObjectInfo.zdotdistance=0.1;
	ObjectInfo.rdotdistance=1;
	ObjectInfo.xmanualspeed=50;
	ObjectInfo.ymanualspeed=50;
	ObjectInfo.zmanualspeed=15;
	ObjectInfo.rmanualspeed=100;
	ObjectInfo.currentlimit=10.0;
	ObjectInfo.tempsetted=25;
	ObjectInfo.tempgain=10;
	ObjectInfo.itime=1;
	ObjectInfo.dtime=10;
//	ObjectInfo.realtimetemp;
//	ObjectInfo.silktemp;

	ObjectInfo.xreturnspeed=30;
	ObjectInfo.yreturnspeed=30;
	ObjectInfo.zreturnspeed=10;
	ObjectInfo.rreturnspeed=45;
	ObjectInfo.zupdistance=0;

	ObjectInfo.sdotdistance=0.5;
	ObjectInfo.smandistance=3;
	ObjectInfo.sautodistance=4;
	ObjectInfo.sbackdistance=1;
	ObjectInfo.sbackspeed=2;
	ObjectInfo.laserptime=20;
	ObjectInfo.laseritime=1;
	ObjectInfo.laserdtime=10;
	ObjectInfo.templimit=300;
	LeaveCriticalSection(&cs);
	RefreshControls();
}

void CParameterSetDlg::RefreshControls(void)
{
	CString str;
	EnterCriticalSection(&cs);
	str.Format("%d",ObjectInfo.xspeedlimit);
	GetDlgItem(IDC_XSpeedLimit)->SetWindowText(str);
	str.Format("%d",ObjectInfo.yspeedlimit);
	GetDlgItem(IDC_YSpeedLimit)->SetWindowText(str);
	str.Format("%d",ObjectInfo.zspeedlimit);
	GetDlgItem(IDC_ZSpeedLimit)->SetWindowText(str);
	str.Format("%d",ObjectInfo.rspeedlimit);
	GetDlgItem(IDC_RSpeedLimit)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.xacclimit);
	GetDlgItem(IDC_XAccLimit)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.yacclimit);
	GetDlgItem(IDC_YAccLimit)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.zacclimit);
	GetDlgItem(IDC_ZAccLimit)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.racclimit);
	GetDlgItem(IDC_RAccLimit)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.xdotdistance);
	GetDlgItem(IDC_XDotDistance)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.ydotdistance);
	GetDlgItem(IDC_YDotDistance)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.zdotdistance);
	GetDlgItem(IDC_ZDotDistance)->SetWindowText(str);
	str.Format("%d",ObjectInfo.rdotdistance);
	GetDlgItem(IDC_RDotDistance)->SetWindowText(str);
	str.Format("%d",ObjectInfo.xmanualspeed);
	GetDlgItem(IDC_XManSpeed)->SetWindowText(str);
	str.Format("%d",ObjectInfo.ymanualspeed);
	GetDlgItem(IDC_YManSpeed)->SetWindowText(str);
	str.Format("%d",ObjectInfo.zmanualspeed);
	GetDlgItem(IDC_ZManSpeed)->SetWindowText(str);
	str.Format("%d",ObjectInfo.rmanualspeed);
	GetDlgItem(IDC_RManSpeed)->SetWindowText(str);
	str.Format("%.1f",ObjectInfo.currentlimit);
	GetDlgItem(IDC_CurrentLimit)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.tempsetted);
	GetDlgItem(IDC_TempSetted)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.tempgain);
	GetDlgItem(IDC_TempGain)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.itime);
	GetDlgItem(IDC_ITime)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.dtime);
	GetDlgItem(IDC_DTime)->SetWindowText(str);
//	ObjectInfo.realtimetemp;
//	ObjectInfo.silktemp;
	str.Format("%.2f",ObjectInfo.realtimetemp);
	GetDlgItem(IDC_RealTimeTemp)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.silktemp);
	GetDlgItem(IDC_SilkTemp)->SetWindowText(str);

	str.Format("%d",ObjectInfo.xreturnspeed);
	GetDlgItem(IDC_XReturnSpeed)->SetWindowText(str);
	str.Format("%d",ObjectInfo.yreturnspeed);
	GetDlgItem(IDC_YReturnSpeed)->SetWindowText(str);
	str.Format("%d",ObjectInfo.zreturnspeed);
	GetDlgItem(IDC_ZReturnSpeed)->SetWindowText(str);
	str.Format("%d",ObjectInfo.rreturnspeed);
	GetDlgItem(IDC_RReturnSpeed)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.zupdistance);
	GetDlgItem(IDC_ZUpDistance)->SetWindowText(str);

	str.Format("%.2f",ObjectInfo.sdotdistance);
	GetDlgItem(IDC_SDotDistance)->SetWindowText(str);
	str.Format("%d",ObjectInfo.smandistance);
	GetDlgItem(IDC_SManDistance)->SetWindowText(str);
	str.Format("%d",ObjectInfo.sautodistance);
	GetDlgItem(IDC_SAutoDistance)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.sbackdistance);
	GetDlgItem(IDC_SBackDistance)->SetWindowText(str);
	str.Format("%d",ObjectInfo.sbackspeed);
	GetDlgItem(IDC_SBackSpeed)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.laserptime);
	GetDlgItem(IDC_LaserPTime)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.laseritime);
	GetDlgItem(IDC_LaserITime)->SetWindowText(str);
	str.Format("%.2f",ObjectInfo.laserdtime);
	GetDlgItem(IDC_LaserDTime)->SetWindowText(str);
	str.Format("%d",ObjectInfo.templimit);
	GetDlgItem(IDC_TempLimit)->SetWindowText(str);
	LeaveCriticalSection(&cs);
}

BOOL CParameterSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	RefreshControls();
	SetTimer(0,100,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CParameterSetDlg::OnOK() 
{
	// TODO: Add extra validation here
	BOOL bUpData;
	bUpData=UpdateData();

	if(!bUpData)
		return;

	CString str;
	EnterCriticalSection(&cs);
	GetDlgItemText(IDC_XSpeedLimit,str);
	ObjectInfo.xspeedlimit=atoi(str);
	GetDlgItemText(IDC_YSpeedLimit,str);
	ObjectInfo.yspeedlimit=atoi(str);
	GetDlgItemText(IDC_ZSpeedLimit,str);
	ObjectInfo.zspeedlimit=atoi(str);
	GetDlgItemText(IDC_RSpeedLimit,str);
	ObjectInfo.rspeedlimit=atoi(str);
	GetDlgItemText(IDC_XAccLimit,str);
	ObjectInfo.xacclimit=atof(str);
	GetDlgItemText(IDC_YAccLimit,str);
	ObjectInfo.yacclimit=atof(str);
	GetDlgItemText(IDC_ZAccLimit,str);
	ObjectInfo.zacclimit=atof(str);
	GetDlgItemText(IDC_RAccLimit,str);
	ObjectInfo.racclimit=atof(str);
	GetDlgItemText(IDC_XDotDistance,str);
	ObjectInfo.xdotdistance=atof(str);
	GetDlgItemText(IDC_YDotDistance,str);
	ObjectInfo.ydotdistance=atof(str);
	GetDlgItemText(IDC_ZDotDistance,str);
	ObjectInfo.zdotdistance=atof(str);
	GetDlgItemText(IDC_RDotDistance,str);
	ObjectInfo.rdotdistance=atoi(str);
	GetDlgItemText(IDC_XManSpeed,str);
	ObjectInfo.xmanualspeed=atoi(str);
	GetDlgItemText(IDC_YManSpeed,str);
	ObjectInfo.ymanualspeed=atoi(str);
	GetDlgItemText(IDC_ZManSpeed,str);
	ObjectInfo.zmanualspeed=atoi(str);
	GetDlgItemText(IDC_RManSpeed,str);
	ObjectInfo.rmanualspeed=atoi(str);
	GetDlgItemText(IDC_CurrentLimit,str);
	ObjectInfo.currentlimit=atof(str);
	GetDlgItemText(IDC_TempSetted,str);
	ObjectInfo.tempsetted=atof(str);
	GetDlgItemText(IDC_TempGain,str);
	ObjectInfo.tempgain=atof(str);
	GetDlgItemText(IDC_ITime,str);
	ObjectInfo.itime=atof(str);
	GetDlgItemText(IDC_DTime,str);
	ObjectInfo.dtime=atof(str);
//	ObjectInfo.realtimetemp;
//	ObjectInfo.silktemp;

	GetDlgItemText(IDC_XReturnSpeed,str);
	ObjectInfo.xreturnspeed=atoi(str);
	GetDlgItemText(IDC_YReturnSpeed,str);
	ObjectInfo.yreturnspeed=atoi(str);
	GetDlgItemText(IDC_ZReturnSpeed,str);
	ObjectInfo.zreturnspeed=atoi(str);
	GetDlgItemText(IDC_RReturnSpeed,str);
	ObjectInfo.rreturnspeed=atoi(str);
	GetDlgItemText(IDC_ZUpDistance,str);
	ObjectInfo.zupdistance=atof(str);

	GetDlgItemText(IDC_SDotDistance,str);
	ObjectInfo.sdotdistance=atof(str);
	GetDlgItemText(IDC_SManDistance,str);
	ObjectInfo.smandistance=atoi(str);
	GetDlgItemText(IDC_SAutoDistance,str);
	ObjectInfo.sautodistance=atoi(str);
	GetDlgItemText(IDC_SBackDistance,str);
	ObjectInfo.sbackdistance=atof(str);
	GetDlgItemText(IDC_SBackSpeed,str);
	ObjectInfo.sbackspeed=atoi(str);
	GetDlgItemText(IDC_LaserPTime,str);
	ObjectInfo.laserptime=atof(str);
	GetDlgItemText(IDC_LaserITime,str);
	ObjectInfo.laseritime=atof(str);
	GetDlgItemText(IDC_LaserDTime,str);
	ObjectInfo.laserdtime=atof(str);
	GetDlgItemText(IDC_TempLimit,str);
	ObjectInfo.templimit=atoi(str);

		
	if(queuer_num==198)
	{
		LeaveCriticalSection(&cs);
		return;
	}
	queuer[queuer_num][0]=10;
	queuer[queuer_num++][1]=1;
	queuer[queuer_num][0]=11;
	queuer[queuer_num++][1]=1;
	LeaveCriticalSection(&cs);
	CDialog::OnOK();
	DestroyWindow();
}


void CParameterSetDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialog::PostNcDestroy();
}

void CParameterSetDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
	DestroyWindow();
}

void CParameterSetDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
	DestroyWindow();
}

BOOL CParameterSetDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL   bReturn   =   FALSE; 
    if(pMsg->message == WM_KEYDOWN   && 
		  (	pMsg-> wParam   != 0x30  &&
			pMsg-> wParam   != 0x31  &&
			pMsg-> wParam   != 0x32  &&
			pMsg-> wParam   != 0x33  &&
			pMsg-> wParam   != 0x34  &&
			pMsg-> wParam   != 0x35  &&
			pMsg-> wParam   != 0x36  &&
			pMsg-> wParam   != 0x37  &&
			pMsg-> wParam   != 0x38  &&
			pMsg-> wParam   != 0x39  &&
			pMsg-> wParam   != 0xBE  &&
			pMsg-> wParam   != 0xBD  &&
			pMsg-> wParam   != VK_TAB    &&
			pMsg-> wParam   != VK_BACK   &&
			pMsg-> wParam   != VK_DELETE &&
			pMsg-> wParam   != VK_DECIMAL
			))
	{
		bReturn = TRUE; 
	} 
	else
		bReturn = CDialog::PreTranslateMessage(pMsg);
	return 
		bReturn;
}

void CParameterSetDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString str;
	str.Format("%.1f",ObjectInfo.realtimetemp);
	GetDlgItem(IDC_RealTimeTemp)->SetWindowText(str);
	str.Format("%.1f",ObjectInfo.silktemp);
	GetDlgItem(IDC_SilkTemp)->SetWindowText(str);

	CDialog::OnTimer(nIDEvent);
}
