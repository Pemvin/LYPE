// SystemSet.cpp : implementation file
//

#include "stdafx.h"
#include "LYPESoldering.h"
#include "SystemSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSystemSet dialog
//int idPulsePerMm[]={IDC_PULSEPERMMX,IDC_PULSEPERMMY,IDC_PULSEPERMMZ};
//int idOrigin[]={IDC_OriginX,IDC_OriginY,IDC_OriginZ};
int idDirLogic[]={IDC_DIRECTIONLOGICX,IDC_DIRECTIONLOGICY,IDC_DIRECTIONLOGICZ};
int idHomeDir[]={IDC_HOMEDIRECTIONX,IDC_HOMEDIRECTIONY,IDC_HOMEDIRECTIONZ};
int idHomeZLogic[]={IDC_HOMEZLOGICX,IDC_HOMEZLOGICY,IDC_HOMEZLOGICZ};
int idHomeOrgLogic[]={IDC_HOMEORGLOGICX,IDC_HOMEORGLOGICY,IDC_HOMEORGLOGICZ};
int idHomeLimitLogic[]={IDC_HOMELIMITLOGICX,IDC_HOMELIMITLOGICY,IDC_HOMELIMITLOGICZ};

CSystemSet::CSystemSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSystemSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSystemSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSystemSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystemSet)
	DDX_Control(pDX, IDC_TAB_SYSTEMSET, m_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSystemSet, CDialogEx)
	//{{AFX_MSG_MAP(CSystemSet)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SYSTEMSET, OnSelchangeTabSystemset)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_SYSTEMSET, OnSelchangingTabSystemset)
	//}}AFX_MSG_MAP
//	ON_COMMAND(IDC_DIRECTIONLOGICX,OnDirectionLogicXChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemSet message handlers

BOOL CSystemSet::OnInitDialog() 
{
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	m_tab.InsertItem(0,_T("工程参数"));
	m_tab.InsertItem(1,_T("速度控制"));
	m_tab.InsertItem(2,_T("输入输出"));

	m_pageone.Create(IDD_PAGEONE,&m_tab);
	m_pagetwo.Create(IDD_PAGETWO,&m_tab);
	m_pagefour.Create(IDD_PAGEFOUR,&m_tab);

	CRect rt;
	m_tab.GetClientRect(rt);
	rt.top +=25;
	rt.bottom -=2;
	rt.left +=2;
	rt.right -=2;
	m_pageone.MoveWindow(&rt);
	m_pagetwo.MoveWindow(&rt);
	m_pagefour.MoveWindow(&rt);
	m_CurSelTab=0;
	
	for(int i=0;i<MAXAXISCOUNT;i++)
	{	//page one
		m_pageone.m_DirLogic[i]=pApp->mVar.AXISDIRECTION[i];
		//page two
		m_pagetwo.m_HomeDirection[i]=pApp->mVar.HOMEDIRECTION[i];
		m_pagetwo.m_HomeZLogic[i]=pApp->mVar.HOMEZLOGIC[i];
		m_pagetwo.m_HomeOrgLogic[i]=pApp->mVar.HOMEORGLOGIC[i];
		m_pagetwo.m_HomeLimitLogic[i]=pApp->mVar.HOMELIMITLOGIC[i];
	}
	//page one
	m_pageone.m_PulsePerMmX=pApp->mVar.PULSEPERMM[0];
	m_pageone.m_PulsePerMmY=pApp->mVar.PULSEPERMM[1];
	m_pageone.m_PulsePerMmZ=pApp->mVar.PULSEPERMM[2];
	m_pageone.m_OriginX=pApp->mVar.ORIGIN[0];
	m_pageone.m_OriginY=pApp->mVar.ORIGIN[1];
	m_pageone.m_OriginZ=pApp->mVar.ORIGIN[2];
	m_pageone.m_MessageEnable=pApp->mVar.MESSAGEENABLE;
	m_pageone.m_BackToOrigin=pApp->mVar.BACKTOORIGIN;
	m_pageone.m_TempRatio=pApp->mVar.TEMPORATURERATIO;

	m_pageone.m_ZUpDistance=pApp->mVar.ZUPDISTANCE;
	m_pageone.m_XMaxCoor=pApp->mVar.MAXCOOR[0];
	m_pageone.m_XMinCoor=pApp->mVar.MINCOOR[0];
	m_pageone.m_YMaxCoor=pApp->mVar.MAXCOOR[1];
	m_pageone.m_YMinCoor=pApp->mVar.MINCOOR[1];
	m_pageone.m_ZMaxCoor=pApp->mVar.MAXCOOR[2];
	m_pageone.m_ZMinCoor=pApp->mVar.MINCOOR[2];
//	m_pageone.m_SilkBackDelay=pApp->mVar.SILKBACKDELAY;
//	m_pageone.m_SilkManualSpd=pApp->mVar.SILKMANUALSPEED;
//	m_pageone.m_SilkBackSpd=pApp->mVar.SILKBACKSPEED;
//	m_pageone.m_SilkDetect=pApp->mVar.SILKDETECT;
	m_pageone.m_CircleDelay=pApp->mVar.CIRCLEDELAY;

	//page two
	m_pagetwo.m_HomeVelXLow=pApp->mVar.HOMEVELLOW[0];
	m_pagetwo.m_HomeVelXHigh=pApp->mVar.HOMEVELHIGH[0];
	m_pagetwo.m_HomeVelXAcc=pApp->mVar.HOMEVELACC[0];

	m_pagetwo.m_HomeVelYLow=pApp->mVar.HOMEVELLOW[1];
	m_pagetwo.m_HomeVelYHigh=pApp->mVar.HOMEVELHIGH[1];
	m_pagetwo.m_HomeVelYAcc=pApp->mVar.HOMEVELACC[1];

	m_pagetwo.m_HomeVelZLow=pApp->mVar.HOMEVELLOW[2];
	m_pagetwo.m_HomeVelZHigh=pApp->mVar.HOMEVELHIGH[2];
	m_pagetwo.m_HomeVelZAcc=pApp->mVar.HOMEVELACC[2];

	//manual
	m_pagetwo.m_ManualVelXLow=pApp->mVar.MANUALVELLOW[0];
	m_pagetwo.m_ManualVelXHigh=pApp->mVar.MANUALVELHIGH[0];
	m_pagetwo.m_ManualVelXAcc=pApp->mVar.MANUALVELACC[0];
	m_pagetwo.m_ManualVelXDec=pApp->mVar.MANUALVELDEC[0];

	m_pagetwo.m_ManualVelYLow=pApp->mVar.MANUALVELLOW[1];
	m_pagetwo.m_ManualVelYHigh=pApp->mVar.MANUALVELHIGH[1];
	m_pagetwo.m_ManualVelYAcc=pApp->mVar.MANUALVELACC[1];
	m_pagetwo.m_ManualVelYDec=pApp->mVar.MANUALVELDEC[1];

	m_pagetwo.m_ManualVelZLow=pApp->mVar.MANUALVELLOW[2];
	m_pagetwo.m_ManualVelZHigh=pApp->mVar.MANUALVELHIGH[2];
	m_pagetwo.m_ManualVelZAcc=pApp->mVar.MANUALVELACC[2];
	m_pagetwo.m_ManualVelZDec=pApp->mVar.MANUALVELDEC[2];

	m_pagetwo.m_AutoMaxVelX=pApp->mVar.AUTOMAXVEL[0];
	m_pagetwo.m_AutoMaxVelY=pApp->mVar.AUTOMAXVEL[1];
	m_pagetwo.m_AutoMaxVelZ=pApp->mVar.AUTOMAXVEL[2];
	RenewTabControl();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSystemSet::OnSelchangeTabSystemset(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_CurSelTab = m_tab.GetCurSel();
	RenewTabControl();
	*pResult = 0;
}

void CSystemSet::OnOK() 
{
	// TODO: Add extra validation here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	int i;
	m_pageone.UpdateData(TRUE);
	m_pagetwo.UpdateData(TRUE);
	//page one
	pApp->mVar.PULSEPERMM[0]=m_pageone.m_PulsePerMmX;
	pApp->mVar.PULSEPERMM[1]=m_pageone.m_PulsePerMmY;
	pApp->mVar.PULSEPERMM[2]=m_pageone.m_PulsePerMmZ;
	pApp->mVar.ORIGIN[0]=m_pageone.m_OriginX;
	pApp->mVar.ORIGIN[1]=m_pageone.m_OriginY;
	pApp->mVar.ORIGIN[2]=m_pageone.m_OriginZ;
	pApp->mVar.MESSAGEENABLE=m_pageone.m_MessageEnable;
	pApp->mVar.BACKTOORIGIN=m_pageone.m_BackToOrigin;
	pApp->mVar.TEMPORATURERATIO=m_pageone.m_TempRatio;
	pApp->mVar.ZUPDISTANCE=m_pageone.m_ZUpDistance;
	pApp->mVar.CIRCLEDELAY=m_pageone.m_CircleDelay;
	pApp->mVar.MAXCOOR[0]=m_pageone.m_XMaxCoor;
	pApp->mVar.MINCOOR[0]=m_pageone.m_XMinCoor;
	pApp->mVar.MAXCOOR[1]=m_pageone.m_YMaxCoor;
	pApp->mVar.MINCOOR[1]=m_pageone.m_YMinCoor;
	pApp->mVar.MAXCOOR[2]=m_pageone.m_ZMaxCoor;
	pApp->mVar.MINCOOR[2]=m_pageone.m_ZMinCoor;
	for(i=0;i<MAXAXISCOUNT;i++)
	{
//		pApp->mVar.PULSEPERMM[i]=m_pageone.GetDlgItemInt(idPulsePerMm[i]);
		pApp->mVar.AXISDIRECTION[i]=m_pageone.m_DirLogic[i];
		//0x00000001:OUT/DIR,0x00000004:OUT/DIR DIR NEG
		pApp->mVar.axisoperate.SetAxisDirection(i,pApp->mVar.AXISDIRECTION[i]?0x00000001:0x00000004);
		pApp->mVar.axisoperate.SetAxisPulsePerMM(i,pApp->mVar.PULSEPERMM[i]);

		pApp->mVar.HOMEDIRECTION[i]=m_pagetwo.m_HomeDirection[i];
		pApp->mVar.HOMEZLOGIC[i]=m_pagetwo.m_HomeZLogic[i];
		pApp->mVar.HOMEORGLOGIC[i]=m_pagetwo.m_HomeOrgLogic[i];
		pApp->mVar.HOMELIMITLOGIC[i]=m_pagetwo.m_HomeLimitLogic[i];
		pApp->mVar.axisoperate.AxisHomeOptionSet(i);
		pApp->mVar.axisoperate.AxisSetLimit(i,TRUE,pApp->mVar.MINCOOR[i],pApp->mVar.MAXCOOR[i]);
	}
	//page two
	pApp->mVar.HOMEVELLOW[0]=m_pagetwo.m_HomeVelXLow;
	pApp->mVar.HOMEVELHIGH[0]=m_pagetwo.m_HomeVelXHigh;
	pApp->mVar.HOMEVELACC[0]=m_pagetwo.m_HomeVelXAcc;

	pApp->mVar.HOMEVELLOW[1]=m_pagetwo.m_HomeVelYLow;
	pApp->mVar.HOMEVELHIGH[1]=m_pagetwo.m_HomeVelYHigh;
	pApp->mVar.HOMEVELACC[1]=m_pagetwo.m_HomeVelYAcc;

	pApp->mVar.HOMEVELLOW[2]=m_pagetwo.m_HomeVelZLow;
	pApp->mVar.HOMEVELHIGH[2]=m_pagetwo.m_HomeVelZHigh;
	pApp->mVar.HOMEVELACC[2]=m_pagetwo.m_HomeVelZAcc;

	//manual
	pApp->mVar.MANUALVELLOW[0]=m_pagetwo.m_ManualVelXLow;
	pApp->mVar.MANUALVELHIGH[0]=m_pagetwo.m_ManualVelXHigh;
	pApp->mVar.MANUALVELACC[0]=m_pagetwo.m_ManualVelXAcc;
	pApp->mVar.MANUALVELDEC[0]=m_pagetwo.m_ManualVelXDec;

	pApp->mVar.MANUALVELLOW[1]=m_pagetwo.m_ManualVelYLow;
	pApp->mVar.MANUALVELHIGH[1]=m_pagetwo.m_ManualVelYHigh;
	pApp->mVar.MANUALVELACC[1]=m_pagetwo.m_ManualVelYAcc;
	pApp->mVar.MANUALVELDEC[1]=m_pagetwo.m_ManualVelYDec;

	pApp->mVar.MANUALVELLOW[2]=m_pagetwo.m_ManualVelZLow;
	pApp->mVar.MANUALVELHIGH[2]=m_pagetwo.m_ManualVelZHigh;
	pApp->mVar.MANUALVELACC[2]=m_pagetwo.m_ManualVelZAcc;
	pApp->mVar.MANUALVELDEC[2]=m_pagetwo.m_ManualVelZDec;

	pApp->mVar.AUTOMAXVEL[0]=m_pagetwo.m_AutoMaxVelX;
	pApp->mVar.AUTOMAXVEL[1]=m_pagetwo.m_AutoMaxVelY;
	pApp->mVar.AUTOMAXVEL[2]=m_pagetwo.m_AutoMaxVelZ;

	for(i=0;i<MAXAXISCOUNT;i++)
	{
		if(pApp->mVar.HOMEVELHIGH[i]>pApp->mVar.AUTOMAXVEL[i])
			pApp->mVar.HOMEVELHIGH[i]=pApp->mVar.AUTOMAXVEL[i];
		if(pApp->mVar.MANUALVELHIGH[i]>pApp->mVar.AUTOMAXVEL[i])
			pApp->mVar.MANUALVELHIGH[i]=pApp->mVar.AUTOMAXVEL[i];
	}

	CDialogEx::OnOK();
}

void CSystemSet::RenewTabControl() 
{
	// TODO: Add extra validation here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	int i;

//	m_pageone.SetDlgItemInt(idPulsePerMm[0],m_pageone.m_PulsePerMmX);
//	m_pageone.SetDlgItemInt(idPulsePerMm[1],m_pageone.m_PulsePerMmY);
//	m_pageone.SetDlgItemInt(idPulsePerMm[2],m_pageone.m_PulsePerMmZ);
//	m_pageone.SetDlgItemInt(idPulsePerMm[3],m_pageone.m_PulsePerMmA);
	for(i=0;i<MAXAXISCOUNT;i++)
	{
		if(!m_pageone.m_DirLogic[i])
			m_pageone.SetDlgItemText(idDirLogic[i],_T("同相"));
		else
			m_pageone.SetDlgItemText(idDirLogic[i],_T("反相"));
	}

	for(i=0;i<MAXAXISCOUNT;i++)
	{
		if(!m_pagetwo.m_HomeDirection[i])
			m_pagetwo.SetDlgItemText(idHomeDir[i],_T("正相"));
		else
			m_pagetwo.SetDlgItemText(idHomeDir[i],_T("反相"));

		if(!m_pagetwo.m_HomeZLogic[i])
			m_pagetwo.SetDlgItemText(idHomeZLogic[i],_T("正相"));
		else
			m_pagetwo.SetDlgItemText(idHomeZLogic[i],_T("反相"));

		if(!m_pagetwo.m_HomeOrgLogic[i])
			m_pagetwo.SetDlgItemText(idHomeOrgLogic[i],_T("正相"));
		else
			m_pagetwo.SetDlgItemText(idHomeOrgLogic[i],_T("反相"));

		if(!m_pagetwo.m_HomeLimitLogic[i])
			m_pagetwo.SetDlgItemText(idHomeLimitLogic[i],_T("正相"));
		else
			m_pagetwo.SetDlgItemText(idHomeLimitLogic[i],_T("反相"));
	}
	m_pageone.UpdateData(FALSE);
	m_pagetwo.UpdateData(FALSE);

	switch(m_CurSelTab)
	{
	case 0:
		m_pageone.ShowWindow(SW_SHOW);
		m_pagetwo.ShowWindow(SW_HIDE);
		m_pagefour.ShowWindow(SW_HIDE);

/*		m_pageone.SetDlgItemInt(idPulsePerMm[0],m_pageone.m_PulsePerMmX);
		m_pageone.SetDlgItemInt(idPulsePerMm[1],m_pageone.m_PulsePerMmY);
		m_pageone.SetDlgItemInt(idPulsePerMm[2],m_pageone.m_PulsePerMmZ);
		m_pageone.SetDlgItemInt(idPulsePerMm[3],m_pageone.m_PulsePerMmA);
		for(i=0;i<MAXAXISCOUNT;i++)
		{
			if(!m_pageone.m_DirLogic[i])
				m_pageone.SetDlgItemText(idDirLogic[i],_T("同相"));
			else
				m_pageone.SetDlgItemText(idDirLogic[i],_T("反相"));
		}*/
		break;
	case 1:
		m_pageone.ShowWindow(SW_HIDE);
		m_pagetwo.ShowWindow(SW_SHOW);
		m_pagefour.ShowWindow(SW_HIDE);
/*		for(i=0;i<MAXAXISCOUNT;i++)
		{
			if(!m_pagetwo.m_HomeDirection[i])
				m_pagetwo.SetDlgItemText(idHomeDir[i],_T("正相"));
			else
				m_pagetwo.SetDlgItemText(idHomeDir[i],_T("反相"));

			if(!m_pagetwo.m_HomeZLogic[i])
				m_pagetwo.SetDlgItemText(idHomeZLogic[i],_T("正相"));
			else
				m_pagetwo.SetDlgItemText(idHomeZLogic[i],_T("反相"));

			if(!m_pagetwo.m_HomeOrgLogic[i])
				m_pagetwo.SetDlgItemText(idHomeOrgLogic[i],_T("正相"));
			else
				m_pagetwo.SetDlgItemText(idHomeOrgLogic[i],_T("反相"));

			if(!m_pagetwo.m_HomeLimitLogic[i])
				m_pagetwo.SetDlgItemText(idHomeLimitLogic[i],_T("正相"));
			else
				m_pagetwo.SetDlgItemText(idHomeLimitLogic[i],_T("反相"));
		}
		m_pagetwo.UpdateData(FALSE);*/
		break;
	case 2:
		m_pageone.ShowWindow(SW_HIDE);
		m_pagetwo.ShowWindow(SW_HIDE);
		m_pagefour.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
}

void CSystemSet::OnSelchangingTabSystemset(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	switch(m_CurSelTab)
	{
	case 0:
		m_pageone.UpdateData(TRUE);
		break;
	case 1:
		m_pagetwo.UpdateData(TRUE);
		break;
	case 2:
		break;
	default:
		break;
	}
	*pResult = 0;
}
