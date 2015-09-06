// DlgPull.cpp : 实现文件
//

#include "stdafx.h"
#include "LYPESoldering.h"
#include "DlgPull.h"


// CDlgPull

IMPLEMENT_DYNCREATE(CDlgPull, CFormView)

CDlgPull::CDlgPull()
	: CFormView(CDlgPull::IDD)
{
	m_current = 0;
	m_pointnum = 0;
	m_xaxiscoor = 0;;
	m_yaxiscoor = 0;
	m_zaxiscoor = 0;
	m_pointname= _T("");;
	m_startspd = 0;
	m_stopspd = 0;
	m_laserstartdelay = 0;
	m_laserstopdelay = 0;
	m_soldtemp = 0;
}

CDlgPull::~CDlgPull()
{
}

void CDlgPull::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_POINTNUM, m_pointnum);
	DDV_MinMaxInt(pDX, m_pointnum, 1, 2000);
	DDX_Text(pDX, IDC_XCOOR, m_xaxiscoor);
	DDV_MinMaxDouble(pDX, m_xaxiscoor, -100., 999.999);
	DDX_Text(pDX, IDC_YCOOR, m_yaxiscoor);
	DDV_MinMaxDouble(pDX, m_yaxiscoor, -100., 999.999);
	DDX_Text(pDX, IDC_ZCOOR, m_zaxiscoor);
	DDV_MinMaxDouble(pDX, m_zaxiscoor, -100., 999.999);
	DDX_Text(pDX, IDC_POINTNAME, m_pointname);
	DDX_Text(pDX, IDC_Current, m_current);
	DDX_Text(pDX, IDC_StartSpd, m_startspd);
	DDX_Text(pDX, IDC_EndSpd, m_stopspd);
	DDX_Text(pDX, IDC_LaserStartDelay, m_laserstartdelay);
	DDX_Text(pDX, IDC_LaserStopDelay, m_laserstopdelay);
	DDX_Control(pDX, IDC_POINTLIST, m_PointList);
	DDX_Text(pDX, IDC_SOLDTEMP, m_soldtemp);
	DDV_MinMaxDouble(pDX, m_soldtemp, 0, 500);
}

BEGIN_MESSAGE_MAP(CDlgPull, CFormView)
	ON_LBN_SELCHANGE(IDC_POINTLIST, OnSelchangePointlist)
	ON_EN_KILLFOCUS(IDC_XCOOR, OnKillfocusXcoor)
	ON_EN_KILLFOCUS(IDC_YCOOR, OnKillfocusXcoor)
	ON_EN_KILLFOCUS(IDC_ZCOOR, OnKillfocusXcoor)
	ON_EN_KILLFOCUS(IDC_POINTNAME, OnKillfocusXcoor)
	ON_EN_KILLFOCUS(IDC_Current, OnKillfocusXcoor)
	ON_EN_KILLFOCUS(IDC_StartSpd, OnKillfocusXcoor)
	ON_EN_KILLFOCUS(IDC_EndSpd, OnKillfocusXcoor)
	ON_EN_KILLFOCUS(IDC_LaserStartDelay, OnKillfocusXcoor)
	ON_EN_KILLFOCUS(IDC_LaserStopDelay, OnKillfocusXcoor)
	ON_EN_KILLFOCUS(IDC_SOLDTEMP, OnKillfocusXcoor)
	ON_MESSAGE(IDC_L_UPDATE_MESSAGE,MessageRenewObjects)
	ON_BN_CLICKED(IDC_POINTNEW, &CDlgPull::OnBnClickedPointnew)
	ON_BN_CLICKED(IDC_GetEndPoint, &CDlgPull::OnBnClickedGetendpoint)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_StartPoint, &CDlgPull::OnBnClickedStartpoint)
	ON_BN_CLICKED(IDC_MiddlePoint, &CDlgPull::OnBnClickedMiddlepoint)
	ON_BN_CLICKED(IDC_EndPoint, &CDlgPull::OnBnClickedEndpoint)
	ON_BN_CLICKED(IDC_POINTDEC, &CDlgPull::OnBnClickedPointdec)
	ON_BN_CLICKED(IDC_POINTADD, &CDlgPull::OnBnClickedPointadd)
	ON_BN_CLICKED(IDC_POINTDEL, &CDlgPull::OnBnClickedPointdel)
	ON_BN_CLICKED(IDC_POINTNULL, &CDlgPull::OnBnClickedPointnull)
	ON_BN_CLICKED(IDC_POINTUP, &CDlgPull::OnBnClickedPointup)
	ON_BN_CLICKED(IDC_POINTDOWN, &CDlgPull::OnBnClickedPointdown)
	ON_BN_CLICKED(IDC_POINTCUT, &CDlgPull::OnBnClickedPointcut)
	ON_BN_CLICKED(IDC_POINTCOPY, &CDlgPull::OnBnClickedPointcopy)
	ON_BN_CLICKED(IDC_POINTPASTE, &CDlgPull::OnBnClickedPointpaste)
	ON_EN_CHANGE(IDC_POINTNUM, &CDlgPull::OnEnChangePointnum)
	ON_BN_CLICKED(IDC_RenewCoordinate, &CDlgPull::OnBnClickedRenewcoordinate)
END_MESSAGE_MAP()


// CDlgPull 诊断

#ifdef _DEBUG
void CDlgPull::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDlgPull::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDlgPull 消息处理程序
void CDlgPull::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	RenewObjects();
}

void CDlgPull::OnKillfocusXcoor() 
{
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	UpdateData(TRUE);

	int temnum= pApp->mVar.currentpointnumber;
	pApp->mVar.m_autopara[temnum].AutoCoor.AxisXCoor = m_xaxiscoor;
	pApp->mVar.m_autopara[temnum].AutoCoor.AxisYCoor = m_yaxiscoor;
	pApp->mVar.m_autopara[temnum].AutoCoor.AxisZCoor = m_zaxiscoor;
	pApp->mVar.m_autopara[temnum].PointName = m_pointname;

	pApp->mVar.m_autopara[temnum].Current = m_current;
	pApp->mVar.m_autopara[temnum].StartSpd = m_startspd;
	pApp->mVar.m_autopara[temnum].StopSpd = m_stopspd;
	pApp->mVar.m_autopara[temnum].LaserStartDelay = m_laserstartdelay;
	pApp->mVar.m_autopara[temnum].LaserStopDelay = m_laserstopdelay;
	pApp->mVar.m_autopara[temnum].AutoTemp = m_soldtemp;
	if (pApp->mVar.m_autopara[temnum].AutoCoor.AxisXCoor > pApp->mVar.MAXCOOR[0])
	{
		pApp->mVar.m_autopara[temnum].AutoCoor.AxisXCoor = pApp->mVar.MAXCOOR[0];
	}
	if (pApp->mVar.m_autopara[temnum].AutoCoor.AxisXCoor < pApp->mVar.MINCOOR[0])
	{
		pApp->mVar.m_autopara[temnum].AutoCoor.AxisXCoor = pApp->mVar.MINCOOR[0];
	}
	if (pApp->mVar.m_autopara[temnum].AutoCoor.AxisYCoor > pApp->mVar.MAXCOOR[1])
	{
		pApp->mVar.m_autopara[temnum].AutoCoor.AxisYCoor = pApp->mVar.MAXCOOR[1];
	}
	if (pApp->mVar.m_autopara[temnum].AutoCoor.AxisYCoor < pApp->mVar.MINCOOR[1])
	{
		pApp->mVar.m_autopara[temnum].AutoCoor.AxisYCoor = pApp->mVar.MINCOOR[1];
	}
	if (pApp->mVar.m_autopara[temnum].AutoCoor.AxisZCoor > pApp->mVar.MAXCOOR[2])
	{
		pApp->mVar.m_autopara[temnum].AutoCoor.AxisZCoor = pApp->mVar.MAXCOOR[2];
	}
	if (pApp->mVar.m_autopara[temnum].AutoCoor.AxisZCoor < pApp->mVar.MINCOOR[2])
	{
		pApp->mVar.m_autopara[temnum].AutoCoor.AxisZCoor = pApp->mVar.MINCOOR[2];
	}
	RenewObjects();
}

LRESULT  CDlgPull::MessageRenewObjects(WPARAM wParam,LPARAM lParam) 
{
	RenewObjects();

	return TRUE;
}

void CDlgPull::RenewObjects()
{
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	//	int nID = this->GetFocus()->GetDlgCtrlID();
	//	GetDlgItem(IDC_Grp_APNum)->SetFocus();
	//	GetDlgItem(nID)->SetFocus();

	m_pointnum = pApp->mVar.currentpointnumber + 1;
	int temnum= pApp->mVar.currentpointnumber;
	m_xaxiscoor = pApp->mVar.m_autopara[temnum].AutoCoor.AxisXCoor;
	m_yaxiscoor = pApp->mVar.m_autopara[temnum].AutoCoor.AxisYCoor;
	m_zaxiscoor = pApp->mVar.m_autopara[temnum].AutoCoor.AxisZCoor;

	m_pointname = pApp->mVar.m_autopara[temnum].PointName;
	m_current = pApp->mVar.m_autopara[temnum].Current;
	m_startspd = pApp->mVar.m_autopara[temnum].StartSpd;
	m_stopspd = pApp->mVar.m_autopara[temnum].StopSpd;
	m_laserstartdelay = pApp->mVar.m_autopara[temnum].LaserStartDelay;
	m_laserstopdelay = pApp->mVar.m_autopara[temnum].LaserStopDelay;
	m_soldtemp = pApp->mVar.m_autopara[temnum].AutoTemp;
	UpdateData(FALSE);
	((CButton*)(GetDlgItem(IDC_StartPoint)))->SetCheck(pApp->mVar.m_autopara[temnum].PointType==0);
	((CButton*)(GetDlgItem(IDC_MiddlePoint)))->SetCheck(pApp->mVar.m_autopara[temnum].PointType==1);
	((CButton*)(GetDlgItem(IDC_EndPoint)))->SetCheck(pApp->mVar.m_autopara[temnum].PointType==2);
	if (pApp->mVar.m_autopara[temnum].PointType==2)
	{
		GetDlgItem(IDC_Current)->EnableWindow(FALSE);
		GetDlgItem(IDC_StartSpd)->EnableWindow(FALSE);
		GetDlgItem(IDC_EndSpd)->EnableWindow(FALSE);
		GetDlgItem(IDC_LaserStartDelay)->EnableWindow(FALSE);
		GetDlgItem(IDC_LaserStopDelay)->EnableWindow(FALSE);
		GetDlgItem(IDC_SOLDTEMP)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_Current)->EnableWindow(TRUE);
		GetDlgItem(IDC_StartSpd)->EnableWindow(TRUE);
		GetDlgItem(IDC_EndSpd)->EnableWindow(TRUE);
		GetDlgItem(IDC_LaserStartDelay)->EnableWindow(TRUE);
		GetDlgItem(IDC_LaserStopDelay)->EnableWindow(TRUE);
		GetDlgItem(IDC_SOLDTEMP)->EnableWindow(TRUE);
	}
	CString tempstr;
	tempstr.Format(_T("自动轨迹 %i/%i"),temnum+1,pApp->mVar.totalpointnumber);
	SetDlgItemText(IDC_Grp_APNum,tempstr);

	CString str[]={_T("起点"),_T("中点"),_T("尾点")};
	m_PointList.ResetContent();
	for(unsigned short i=0;i<pApp->mVar.totalpointnumber;i++)
	{
		tempstr.Format(_T("%s %s X:%.1f Y:%.1f I:%.1f"),str[pApp->mVar.m_autopara[i].PointType],pApp->mVar.m_autopara[i].PointName,pApp->mVar.m_autopara[i].AutoCoor.AxisXCoor,
			pApp->mVar.m_autopara[i].AutoCoor.AxisYCoor,pApp->mVar.m_autopara[i].Current);
		m_PointList.AddString(tempstr);
	}
	m_PointList.SetCurSel(pApp->mVar.currentpointnumber);
}

void CDlgPull::OnSelchangePointlist() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	if(pApp->mVar.m_bOperating)
		return;
	pApp->mVar.currentpointnumber=m_PointList.GetCurSel();
	RenewObjects();
}

void CDlgPull::OnBnClickedPointnew()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	unsigned short tempnum=pApp->mVar.currentpointnumber;

	pApp->mVar.totalpointnumber++;
	for(unsigned short i=pApp->mVar.totalpointnumber;i>tempnum+1;i--)
		pApp->mVar.m_autopara[i-1]=pApp->mVar.m_autopara[i-2];
	pApp->mVar.m_autopara[tempnum+1]=pApp->mVar.m_autopara[tempnum];

	pApp->mVar.currentpointnumber++;

	RenewObjects();
}

void CDlgPull::OnBnClickedGetendpoint()
{
	// TODO: 在此添加控件通知处理程序代码
	double pos[4];
	double CurPos;
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	unsigned short tempnum=pApp->mVar.currentpointnumber;
	pApp->mVar.totalpointnumber++;
	for(unsigned short i=pApp->mVar.totalpointnumber;i>tempnum+1;i--)
		pApp->mVar.m_autopara[i-1]=pApp->mVar.m_autopara[i-2];
	pApp->mVar.m_autopara[tempnum+1]=pApp->mVar.m_autopara[tempnum];

	pApp->mVar.currentpointnumber++;

	for(unsigned int i=0;i<pApp->mVar.m_ulAxisCount;i++)
	{
		Acm_AxGetCmdPosition(pApp->mVar.m_Axishand[i],&CurPos);
		pos[i]=CurPos;
	}
	pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisXCoor = pos[0];
	pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisYCoor = pos[1];
	pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisZCoor = pos[2];
	pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].PointType=1;
	if (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber-1].PointType==2)
	{
		pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].PointType=0;
	}

	RenewObjects();
}


void CDlgPull::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}


void CDlgPull::OnBnClickedStartpoint()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].PointType=0;
	RenewObjects();
}


void CDlgPull::OnBnClickedMiddlepoint()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].PointType=1;
	RenewObjects();
}


void CDlgPull::OnBnClickedEndpoint()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].PointType=2;
	RenewObjects();
}


void CDlgPull::OnBnClickedPointdec()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	if(pApp->mVar.m_bOperating)
		return;
	if(pApp->mVar.currentpointnumber<=0)
		return;
	pApp->mVar.currentpointnumber--;
	RenewObjects();
}


void CDlgPull::OnBnClickedPointadd()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	if(pApp->mVar.m_bOperating)
		return;
	if(pApp->mVar.currentpointnumber+1>=pApp->mVar.totalpointnumber || pApp->mVar.currentpointnumber>=MAXAUTOPOINTCOUNT-1)
		return;
	pApp->mVar.currentpointnumber++;
	RenewObjects();
}


void CDlgPull::OnBnClickedPointdel()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	if(pApp->mVar.totalpointnumber<=2)
		return;

	int i;
	for(i=pApp->mVar.currentpointnumber;i<pApp->mVar.totalpointnumber-1;i++)
	{
		pApp->mVar.m_autopara[i]=pApp->mVar.m_autopara[i+1];
	}
	pApp->mVar.totalpointnumber--;
	if(pApp->mVar.currentpointnumber>=pApp->mVar.totalpointnumber)
		pApp->mVar.currentpointnumber--;
	RenewObjects();
}


void CDlgPull::OnBnClickedPointnull()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	pApp->mVar.totalpointnumber=2;
	pApp->mVar.currentpointnumber=0;
	int i;
	for(i=0;i<pApp->mVar.totalpointnumber;i++)
	{
		pApp->mVar.m_autopara[i].AutoCoor.AxisXCoor=0.0;
		pApp->mVar.m_autopara[i].AutoCoor.AxisYCoor=0.0;
		pApp->mVar.m_autopara[i].AutoCoor.AxisZCoor=0.0;
		pApp->mVar.m_autopara[i].PointName = "";

		pApp->mVar.m_autopara[i].Current = 0;
		pApp->mVar.m_autopara[i].StartSpd = 0;
		pApp->mVar.m_autopara[i].StopSpd = 0;
		pApp->mVar.m_autopara[i].LaserStartDelay = 0;
		pApp->mVar.m_autopara[i].LaserStopDelay = 0;
		pApp->mVar.m_autopara[i].AutoTemp = 0;
	}
	pApp->mVar.m_autopara[0].PointType = 0;
	pApp->mVar.m_autopara[1].PointType = 2;
	RenewObjects();
}


void CDlgPull::OnBnClickedPointup()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	AutoParameter temppoint;
	unsigned short tempnum=m_PointList.GetCurSel();
	if(tempnum<=0) return;
	temppoint=pApp->mVar.m_autopara[tempnum];
	pApp->mVar.m_autopara[tempnum]=pApp->mVar.m_autopara[tempnum-1];
	pApp->mVar.m_autopara[tempnum-1]=temppoint;

	pApp->mVar.currentpointnumber--;

	RenewObjects();
}


void CDlgPull::OnBnClickedPointdown()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	AutoParameter temppoint;
	unsigned short tempnum=m_PointList.GetCurSel();
	if(tempnum>=pApp->mVar.totalpointnumber-1) return;
	temppoint=pApp->mVar.m_autopara[tempnum];
	pApp->mVar.m_autopara[tempnum]=pApp->mVar.m_autopara[tempnum+1];
	pApp->mVar.m_autopara[tempnum+1]=temppoint;

	pApp->mVar.currentpointnumber++;

	RenewObjects();
}


void CDlgPull::OnBnClickedPointcut()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	if(pApp->mVar.totalpointnumber<=2)
		return;
	unsigned short tempnum=m_PointList.GetCurSel();
	pastepoint=pApp->mVar.m_autopara[tempnum];
	pApp->mVar.totalpointnumber--;
	for(unsigned short i=tempnum;i<pApp->mVar.totalpointnumber;i++)
		pApp->mVar.m_autopara[i]=pApp->mVar.m_autopara[i+1];

	if(pApp->mVar.currentpointnumber>=pApp->mVar.totalpointnumber)
		pApp->mVar.currentpointnumber--;

	RenewObjects();
}


void CDlgPull::OnBnClickedPointcopy()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	unsigned short tempnum=m_PointList.GetCurSel();
	pastepoint=pApp->mVar.m_autopara[tempnum];
}


void CDlgPull::OnBnClickedPointpaste()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	unsigned short tempnum=m_PointList.GetCurSel();

	pApp->mVar.totalpointnumber++;
	for(unsigned short i=pApp->mVar.totalpointnumber;i>tempnum+1;i--)
		pApp->mVar.m_autopara[i-1]=pApp->mVar.m_autopara[i-2];
	pApp->mVar.m_autopara[tempnum+1]=pastepoint;

	pApp->mVar.currentpointnumber++;

	RenewObjects();
}


void CDlgPull::OnEnChangePointnum()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	if(!UpdateData(TRUE))
		return;
	if(m_pointnum>pApp->mVar.totalpointnumber)
	{
		AfxMessageBox(_T("该自动点尚未编辑!"));
		pApp->mVar.currentpointnumber=0;
	}
	else
	{
		pApp->mVar.currentpointnumber=m_pointnum-1;
	}
	RenewObjects();
}


void CDlgPull::OnBnClickedRenewcoordinate()
{
	// TODO: 在此添加控件通知处理程序代码
	double pos[4];
	double CurPos;
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	//	CMainFrame *pFrm=(CMainFrame *)(AfxGetApp()->m_pMainWnd);

	for(unsigned int i=0;i<pApp->mVar.m_ulAxisCount;i++)
	{
		Acm_AxGetCmdPosition(pApp->mVar.m_Axishand[i],&CurPos);
		pos[i]=CurPos;
	}
	pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisXCoor = pos[0];
	pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisYCoor = pos[1];
	pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisZCoor = pos[2];
	RenewObjects();
}
