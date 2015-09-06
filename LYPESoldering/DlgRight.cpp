// DlgRight.cpp : implementation file
//

#include "stdafx.h"
#include "LYPESoldering.h"
#include "DlgRight.h"
#include "Mainfrm.h"
#include "math.h"
#include <afxmt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
double pid_a, pid_b, pid_c;
double  ch1_OutK, ch1_dErrorK1, ch1_ErrorK1;
double	ch1_GK, ch1_GK1, ch1_FK, ch1_FK1;
// CDlgRight
BOOL flaginit = FALSE;
CWinThread *pThread_TempCurve = NULL;   //多线程句柄
CWinThread *pThread_LaserTemp = NULL;   //多线程句柄
CWinThread *pThread_FootSwitch = NULL;   //多线程句柄
CWinThread *pThread_Operating = NULL;   //多线程句柄
CWinThread *pThread_LaserTime = NULL;   //多线程句柄
CWinThread *pThread_Locating = NULL;   //多线程句柄
CWinThread *pThread_ZUpLocating = NULL;   //多线程句柄
CWinThread *pThread_XYLocating = NULL;   //多线程句柄
CWinThread *pThread_ToOrigin = NULL;   //多线程句柄
CWinThread *pThread_LaserContinue = NULL;
CWinThread *pThread_ManualMoveTo = NULL;
CEvent	Event_AllLocating;
CEvent	Event_LaserOff;
CEvent	Event_ZUpLocating;
CEvent	Event_XYLocating;
CEvent	Event_ToOrigin;
CEvent  Event_LaserContinue;
CEvent	Event_Stop;
HANDLE  g_hEventArray[2];

BOOL    gbThread_XYLocation(FALSE);
BOOL    gbThread_ZLocation(FALSE);
BOOL    gbThread_Location(FALSE);

BOOL	bManualMove = FALSE;
extern	COLORREF SysColor;
BOOL	bXAxisPull = FALSE;
BOOL	bMiddleStop = FALSE;
int		tempmaxpointnumber = 0;
double	temporatureValue = 0;
BOOL	TempStop = FALSE;

IMPLEMENT_DYNCREATE(CDlgRight, CFormView)

CDlgRight::CDlgRight()
: CFormView(CDlgRight::IDD)
{
	//{{AFX_DATA_INIT(CDlgRight)
	m_dptpdistance = 1.0;
	m_SetCurrent = 0.0;
	m_SetTemp = 0.0;
	m_SetTime = 0.0;
	m_RealCurrent = 0.0;
	m_RealTemp = 0.0;
	m_RealTime = 0.0;
	m_TotalOperatingTimes = 0;
	m_TotalOperatingCounts = 0;
	//}}AFX_DATA_INIT
	hBitmapRed = ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_RED));
	hBitmapGray = ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_GRAY));
	m_bPause = FALSE;
}

CDlgRight::~CDlgRight()
{
	pThread_TempCurve = NULL;
	pThread_LaserTemp = NULL;
	pThread_FootSwitch = NULL;
	pThread_Operating = NULL;
	pThread_LaserTime = NULL;
	pThread_Locating = NULL;
	pThread_ZUpLocating = NULL;
	pThread_XYLocating = NULL;
	pThread_ToOrigin = NULL;
	pThread_LaserContinue = NULL;
	pThread_ManualMoveTo = NULL;
}

void CDlgRight::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRight)
	DDX_Text(pDX, IDC_SETCURRENT, m_SetCurrent);
	DDX_Text(pDX, IDC_SETTIME, m_SetTime);
	DDX_Text(pDX, IDC_REALCURRENT, m_RealCurrent);
	DDV_MinMaxDouble(pDX, m_RealCurrent, 0., 53.);
	DDX_Text(pDX, IDC_REALTIME, m_RealTime);
	DDX_Text(pDX, IDC_OPERATINGTIMES, m_TotalOperatingTimes);
	DDX_Text(pDX, IDC_OPERATINGOBJ, m_TotalOperatingCounts);
	DDX_Text(pDX, IDC_SETTEMP, m_SetTemp);
	DDX_Text(pDX, IDC_REALTEMP, m_RealTemp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRight, CFormView)
	//{{AFX_MSG_MAP(CDlgRight)
	ON_BN_CLICKED(IDC_TIMESTOZERO, OnTimestozero)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ServoState, OnServoState)
	ON_BN_CLICKED(IDC_CHKPTP, OnChkptp)
	ON_BN_CLICKED(IDC_ManualMoveTo, OnManualMoveTo)
	ON_BN_CLICKED(IDC_Home, OnHome)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_EN_CHANGE(IDC_PTPDistance, OnChangePTPDistance)
	ON_BN_CLICKED(IDC_CHKKEYMOVE, OnChkkeymove)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_FOOTSWITCH, OnFootswitch)
	ON_BN_CLICKED(IDC_SIMULATION, OnSimulation)
	ON_BN_CLICKED(IDC_SINGLEPOINT, OnSinglepoint)
	ON_BN_CLICKED(IDC_CIRCLEOPERATE, OnCircleoperate)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_LASERTEST, OnLasertest)
	ON_BN_CLICKED(IDC_RenewCoordinate, OnRenewCoordinate)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_MESSAGE(IDC_R_LBtnDown_MESSAGE, OnMessageLBtnDown)
	ON_MESSAGE(IDC_R_LBtnUp_MESSAGE, OnMessageLBtnUp)
	ON_MESSAGE(IDC_F2_MESSAGE, OnMessageStart)
	ON_MESSAGE(IDC_F3_MESSAGE, OnMessagePause)
	ON_MESSAGE(IDC_ESC_MESSAGE, OnMessageStop)
	ON_BN_CLICKED(IDC_TOORIGIN, &CDlgRight::OnBnClickedToorigin)
	ON_BN_CLICKED(IDC_CURRENTMODE, &CDlgRight::OnBnClickedCurrentmode)
	ON_BN_CLICKED(IDC_TEMPMODE, &CDlgRight::OnBnClickedTempmode)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRight diagnostics

#ifdef _DEBUG
void CDlgRight::AssertValid() const
{
	CFormView::AssertValid();
}

void CDlgRight::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDlgRight message handlers

void CDlgRight::OnTimestozero()
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	pApp->mVar.TOTALOPERATINGTIMES = 0;
	pApp->mVar.TOTALOPERATINGCOUNTS = 0;
}

void CDlgRight::OnObjectstozero()
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();

	//	pApp->mVar.currentpointnumber++;
	//	CDlgLeft cl;
	//	cl.RenewObjects();

}

void CDlgRight::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	U32 Result;
	U32 Status;
	F64 CurPos;
	U16 State;
	CString strTemp;
	CButton * pBtn;
	int RealPos[] = { IDC_XRealPos, IDC_YRealPos, IDC_ZRealPos };
	int AxisState[] = { IDC_XAxisState, IDC_YAxisState, IDC_ZAxisState };
	int NEGLIMIT[] = { IDC_CHK_XNEG, IDC_CHK_YNEG, IDC_CHK_ZNEG };
	int ORGLIMIT[] = { IDC_CHK_XORG, IDC_CHK_YORG, IDC_CHK_ZORG };
	int POSLIMIT[] = { IDC_CHK_XPOS, IDC_CHK_YPOS, IDC_CHK_ZPOS };

	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	if (pApp->mVar.m_bInit)
	{
		for (unsigned int i = 0; i < pApp->mVar.m_ulAxisCount; i++)
		{
			Acm_AxGetCmdPosition(pApp->mVar.m_Axishand[i], &CurPos);
			strTemp.Format(_T("%.3f"), CurPos);;
			SetDlgItemText(RealPos[i], strTemp);

			Result = Acm_AxGetState(pApp->mVar.m_Axishand[i], &State);
			if (Result == SUCCESS)
			{
				switch (State)
				{
				case 0:
					strTemp.Format(_T("DISABLE"));
					break;
				case 1:
					strTemp.Format(_T("READY"));
					break;
				case 2:
					strTemp.Format(_T("STOPPING"));
					break;
				case 3:
					strTemp.Format(_T("ERROR"));
					break;
				case 4:
					strTemp.Format(_T("HOMING"));
					break;
				case 5:
					strTemp.Format(_T("PTP_MOT"));
					break;
				case 6:
					strTemp.Format(_T("CONTI_MOT"));
					break;
				case 7:
					strTemp.Format(_T("SYNC_MOT"));
					break;
				default:
					break;
				}
				SetDlgItemText(AxisState[i], strTemp);
			}

			Result = Acm_AxGetMotionIO(pApp->mVar.m_Axishand[i], &Status);
			if (Result == SUCCESS)
			{
				pBtn = (CButton*)GetDlgItem(ORGLIMIT[i]);
				if (Status & 0x10)//ORG 
				{
					pBtn->SetBitmap(hBitmapRed);
				}
				else
				{
					pBtn->SetBitmap(hBitmapGray);
				}
				/*	pBtn = (CButton*)GetDlgItem(IDC_CHECK_EZ);
					if (Status&0x200)//EZ
					{
					pBtn->SetBitmap(hBitmapRed);
					}
					else
					{
					pBtn->SetBitmap(hBitmapGray);
					}*/
				pBtn = (CButton*)GetDlgItem(POSLIMIT[i]);
				if (Status & 0x4)//+EL
				{
					pBtn->SetBitmap(hBitmapRed);
				}
				else
				{
					pBtn->SetBitmap(hBitmapGray);
				}
				pBtn = (CButton*)GetDlgItem(NEGLIMIT[i]);
				if (Status & 0x8)//+EL
				{
					pBtn->SetBitmap(hBitmapRed);
				}
				else
				{
					pBtn->SetBitmap(hBitmapGray);
				}
			}
		}
	}

	m_SetCurrent = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].Current;
	m_SetTime = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].StopSpd;
	m_SetTemp = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoTemp;

	m_RealTemp = (double)((int)(pApp->mVar.RealTemp * 10)) / 10;
	m_RealCurrent = (double)((int)(pApp->mVar.RealCurrent * 10)) / 10;
	m_RealTime = (double)((int)(pApp->mVar.RealSpd * 10)) / 10;

	m_TotalOperatingTimes = pApp->mVar.TOTALOPERATINGTIMES;
	m_TotalOperatingCounts = pApp->mVar.TOTALOPERATINGCOUNTS;

	UpdateData(FALSE);

	if (pApp->mVar.m_bOperating)
	{
		GetDlgItem(IDC_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_Home)->EnableWindow(FALSE);
		GetDlgItem(IDC_ManualMoveTo)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_Home)->EnableWindow(TRUE);
		GetDlgItem(IDC_ManualMoveTo)->EnableWindow(TRUE);
	}

	CFormView::OnTimer(nIDEvent);
}

void CDlgRight::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	CString tempstr;
	tempstr.Format(_T("%0.2f"), m_dptpdistance);
	SetDlgItemText(IDC_PTPDistance, tempstr);
	pApp->mVar.axisoperate.OpenDevice();
	pApp->mVar.axisoperate.LoadConfig();
	pApp->mVar.axisoperate.AddAxisToGrp(0);
	pApp->mVar.axisoperate.AddAxisToGrp(1);
	pApp->mVar.axisoperate.AddAxisToGrp(2);
	for (int i = 0; i < MAXAXISCOUNT; i++)
	{
		pApp->mVar.axisoperate.SetAxisPulsePerMM(i, pApp->mVar.PULSEPERMM[i]);
		pApp->mVar.axisoperate.AxisSetLimit(i, TRUE, pApp->mVar.MINCOOR[i], pApp->mVar.MAXCOOR[i]);
		pApp->mVar.axisoperate.AxisHomeOptionSet(i);
	}
	((CButton*)(GetDlgItem(IDC_TEMPMODE)))->SetCheck(pApp->mVar.OPERATEMODE);
	((CButton*)(GetDlgItem(IDC_CURRENTMODE)))->SetCheck(!pApp->mVar.OPERATEMODE);
	((CButton*)(GetDlgItem(IDC_FOOTSWITCH)))->SetCheck(pApp->mVar.FOOTSWITCHENABLE);
	((CButton*)(GetDlgItem(IDC_SINGLEPOINT)))->SetCheck(pApp->mVar.SINGLEPOINT);
	((CButton*)(GetDlgItem(IDC_SIMULATION)))->SetCheck(pApp->mVar.SIMULATION);
	((CButton*)(GetDlgItem(IDC_CIRCLEOPERATE)))->SetCheck(pApp->mVar.CIRCLEOPERATE);

	pThread_TempCurve = AfxBeginThread(Thread_TempSample, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	pThread_FootSwitch = AfxBeginThread(Thread_FootSwitch, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	//	OnFootswitch();
	if (!pApp->mVar.FOOTSWITCHENABLE)
		pThread_FootSwitch->SuspendThread();
	Event_Stop.ResetEvent();
	g_hEventArray[0] = Event_Stop.m_hObject;
	g_hEventArray[1] = Event_XYLocating.m_hObject;
	SetTimer(1, 100, NULL);
}

void CDlgRight::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: Add your message handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	pApp->mVar.axisoperate.CloseGrp();
	pApp->mVar.axisoperate.CloseDevice();
	KillTimer(1);
}

void CDlgRight::OnServoState()
{
	// TODO: Add your control notification handler code here
	U16 State;
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	if (pApp->mVar.m_bInit == TRUE)
	{
		for (UINT AxisNum = 0; AxisNum < pApp->mVar.m_ulAxisCount; AxisNum++)
		{
			Acm_AxResetError(pApp->mVar.m_Axishand[AxisNum]);
		}
		Acm_GpGetState(pApp->mVar.m_GpHand, &State);
		if (State == STA_GP_ERROR_STOP)
		{
			Acm_GpResetError(pApp->mVar.m_GpHand);
		}
	}
}

BOOL CDlgRight::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bReturn = FALSE;
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		bReturn = TRUE;
	else
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		int buID;
		CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
		buID = GetWindowLong(pMsg->hwnd, GWL_ID);
		switch (buID)
		{
		case IDC_XForward:
			//	SForwardLBottonDown(0);
			XForwardLBottonDown(0, 0);//pApp->mVar.AXISDIRECTION[0]);
			break;
		case IDC_YForward:
			XForwardLBottonDown(1, 0);//pApp->mVar.AXISDIRECTION[1]);
			break;
		case IDC_ZForward:
			XForwardLBottonDown(2, 0);//pApp->mVar.AXISDIRECTION[2]);
			break;
		case IDC_XBackward:
			XForwardLBottonDown(0, 1);//!pApp->mVar.AXISDIRECTION[0]);
			break;
		case IDC_YBackward:
			XForwardLBottonDown(1, 1);//!pApp->mVar.AXISDIRECTION[1]);
			break;
		case IDC_ZBackward:
			XForwardLBottonDown(2, 1);//!pApp->mVar.AXISDIRECTION[2]);
			break;
		default:
			bReturn = CFormView::PreTranslateMessage(pMsg);
			break;
		}
	}
	else
	if (pMsg->message == WM_LBUTTONUP)
	{
		int buID;
		CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
		buID = GetWindowLong(pMsg->hwnd, GWL_ID);
		switch (buID)
		{
		case IDC_XForward:
			//	SForwardLBottonUp(0);
			XForwardLBottonUp(0, 0);//pApp->mVar.AXISDIRECTION[0]);
			break;
		case IDC_YForward:
			XForwardLBottonUp(1, 0);//pApp->mVar.AXISDIRECTION[1]);
			break;
		case IDC_ZForward:
			XForwardLBottonUp(2, 0);//pApp->mVar.AXISDIRECTION[2]);
			break;
		case IDC_XBackward:
			XForwardLBottonUp(0, 1);//!pApp->mVar.AXISDIRECTION[0]);
			break;
		case IDC_YBackward:
			XForwardLBottonUp(1, 1);//!pApp->mVar.AXISDIRECTION[1]);
			break;
		case IDC_ZBackward:
			XForwardLBottonUp(2, 1);//!pApp->mVar.AXISDIRECTION[2]);
			break;
		default:
			bReturn = CFormView::PreTranslateMessage(pMsg);
			break;
		}
	}
	else
		bReturn = CFormView::PreTranslateMessage(pMsg);
	return bReturn;
	//	return CFormView::PreTranslateMessage(pMsg);
}

void CDlgRight::XForwardLBottonDown(short AxisNumber, short AxisDirection)
{
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	pApp->mVar.axisoperate.AxisVelSet(AxisNumber, pApp->mVar.MANUALVELHIGH[AxisNumber], pApp->mVar.MANUALVELLOW[AxisNumber],
		pApp->mVar.MANUALVELACC[AxisNumber], pApp->mVar.MANUALVELDEC[AxisNumber]);
	if (!pApp->mVar.m_bAbsPtp)
		pApp->mVar.axisoperate.AxisMoveVel(AxisNumber, AxisDirection);
	else
		return;
}

void CDlgRight::XForwardLBottonUp(short AxisNumber, short AxisDirection)
{
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();

	if (!pApp->mVar.m_bAbsPtp)
		pApp->mVar.axisoperate.AxisStopVel(AxisNumber);
	else
	{
		if (AxisDirection)
			pApp->mVar.axisoperate.AxisMovePtp(AxisNumber, -pApp->mVar.m_dPtpDistance, 1);
		else
			pApp->mVar.axisoperate.AxisMovePtp(AxisNumber, pApp->mVar.m_dPtpDistance, 1);
	}
}

void CDlgRight::OnChkptp()
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	CString tempstr;
	if (pApp->mVar.m_bAbsPtp)
		pApp->mVar.m_bAbsPtp = FALSE;
	else
		pApp->mVar.m_bAbsPtp = TRUE;
	GetDlgItemText(IDC_PTPDistance, tempstr);
	m_dptpdistance = _ttof(tempstr);
}

void CDlgRight::OnManualMoveTo()
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	if (pApp->mVar.m_bHomeDown == FALSE)
	{
		AfxMessageBox(_T("请先完成设备机械回零!"));
		return;
	}
	if (pApp->mVar.m_bOperating)
		return;
	pApp->mVar.bStopped = FALSE;
	pThread_ManualMoveTo = AfxBeginThread(Thread_ManualMoveTo, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
}

UINT _cdecl CDlgRight::Thread_ManualMoveTo(LPVOID lparam)
{
	/*	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
		Event_AllLocating.ResetEvent();
		Event_XYLocating.ResetEvent();
		pThread_XYLocating=AfxBeginThread(Thread_XYLocating,NULL,THREAD_PRIORITY_NORMAL,0,0,NULL);//
		WaitForSingleObject(Event_XYLocating,100000);//
		if(pApp->mVar.bStopped)
		return 1;
		pThread_Locating=AfxBeginThread(Thread_Locating,NULL,THREAD_PRIORITY_NORMAL,0,0,NULL);
		WaitForSingleObject(Event_AllLocating,100000);//
		return 1;*/
	U16 State[2];
	U32 Result;
	U16 Status;
	BOOL bResult(FALSE);
	AxisCoordinate tempaxiscoor;
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);

	pApp->mVar.axisoperate.AxisVelSet(0, pApp->mVar.MANUALVELHIGH[0],
		pApp->mVar.MANUALVELLOW[0], pApp->mVar.MANUALVELACC[0], pApp->mVar.MANUALVELACC[0]);
	pApp->mVar.axisoperate.AxisVelSet(1, pApp->mVar.MANUALVELHIGH[1],
		pApp->mVar.MANUALVELLOW[1], pApp->mVar.MANUALVELACC[1], pApp->mVar.MANUALVELACC[1]);
	pApp->mVar.axisoperate.AxisVelSet(2, pApp->mVar.MANUALVELHIGH[2],
		pApp->mVar.MANUALVELLOW[2], pApp->mVar.MANUALVELACC[2], pApp->mVar.MANUALVELACC[2]);

	tempaxiscoor.AxisXCoor = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisXCoor;
	tempaxiscoor.AxisYCoor = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisYCoor;
	tempaxiscoor.AxisZCoor = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisZCoor;

	bResult = pApp->mVar.axisoperate.AxisMovePtp(0, tempaxiscoor.AxisXCoor, 0);
	if (!bResult)
		AfxMessageBox(_T("手动模式下--X"));
	bResult = pApp->mVar.axisoperate.AxisMovePtp(1, tempaxiscoor.AxisYCoor, 0);
	if (!bResult)
		AfxMessageBox(_T("手动模式下--Y"));
	Sleep(30);
	while (1)
	{
		Sleep(10);
		if (pApp->mVar.bStopped)
		{
			return 0;
		}
		for (unsigned int i = 0; i < 2; i++)
		{
			Result = Acm_AxGetState(pApp->mVar.m_Axishand[i], &Status);
			if (Result == SUCCESS)
			{
				if (Status == 1)
					State[i] = TRUE;
				else
					State[i] = FALSE;
			}
		}
		if (State[0] == TRUE && State[1] == TRUE)
		{
			break;
		}
	}
	bResult = pApp->mVar.axisoperate.AxisMovePtp(2, tempaxiscoor.AxisZCoor, 0);
	if (!bResult)
	{
		AfxMessageBox(_T("Z轴没动！！！"));
		return 0;
	}
	Sleep(30);
	while (1)
	{
		Sleep(10);
		if (pApp->mVar.bStopped)
		{
			return 0;
		}
		Result = Acm_AxGetState(pApp->mVar.m_Axishand[2], &Status);
		if (Result == SUCCESS)
		{
			if (Status == 1)
			{
				return 1;
			}
		}
	}

	return 1;
}

UINT _cdecl CDlgRight::Thread_Locating(LPVOID lparam)
{
	BOOL State[3];
	U32 Result;
	U16 Status;
	BOOL bResult(FALSE);
	AxisCoordinate tempaxiscoor;
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	//自动手动时，使用不同的速度
	if (bManualMove)
	{
		for (int i = 0; i < MAXAXISCOUNT; i++)
		{
			pApp->mVar.axisoperate.AxisVelSet(i, pApp->mVar.MANUALVELHIGH[i], pApp->mVar.MANUALVELLOW[i],
				pApp->mVar.MANUALVELACC[i], pApp->mVar.MANUALVELDEC[i]);
		}
		bManualMove = FALSE;
	}
	else
	{
		/*		if(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoSpd.AxisXSpd>pApp->mVar.AUTOMAXVEL[0])
					pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoSpd.AxisXSpd=(int)pApp->mVar.AUTOMAXVEL[0];
					if(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoSpd.AxisYSpd>pApp->mVar.AUTOMAXVEL[1])
					pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoSpd.AxisYSpd=(int)pApp->mVar.AUTOMAXVEL[1];
					if(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoSpd.AxisZSpd>pApp->mVar.AUTOMAXVEL[2])
					pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoSpd.AxisZSpd=(int)pApp->mVar.AUTOMAXVEL[2];*/
		pApp->mVar.axisoperate.AxisVelSet(0, pApp->mVar.AUTOMAXVEL[0],
			pApp->mVar.MANUALVELLOW[0], pApp->mVar.MANUALVELACC[0], pApp->mVar.MANUALVELACC[0]);
		pApp->mVar.axisoperate.AxisVelSet(1, pApp->mVar.AUTOMAXVEL[1],
			pApp->mVar.MANUALVELLOW[1], pApp->mVar.MANUALVELACC[1], pApp->mVar.MANUALVELACC[1]);
		pApp->mVar.axisoperate.AxisVelSet(2, pApp->mVar.AUTOMAXVEL[2],
			pApp->mVar.MANUALVELLOW[2], pApp->mVar.MANUALVELACC[2], pApp->mVar.MANUALVELACC[2]);
	}

	tempaxiscoor.AxisXCoor = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisXCoor;
	tempaxiscoor.AxisYCoor = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisYCoor;
	tempaxiscoor.AxisZCoor = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisZCoor;

	bResult = pApp->mVar.axisoperate.AxesMoveTo(tempaxiscoor);
	if (!bResult)
	{
		AfxMessageBox(_T("Thread_Location Move Failed"));
		return 1;
	}
	Sleep(50);
	while (1)
	{
		Sleep(10);
		if (pApp->mVar.bStopped)
		{
			Event_AllLocating.SetEvent();
			return 1;
		}
		for (unsigned int i = 0; i < pApp->mVar.m_ulAxisCount; i++)
		{
			Result = Acm_AxGetState(pApp->mVar.m_Axishand[i], &Status);
			if (Result == SUCCESS)
			{
				if (Status == 1)
					State[i] = TRUE;
				else
					State[i] = FALSE;
			}
		}
		if (State[0] == TRUE && State[1] == TRUE && State[2] == TRUE)
		{
			Event_AllLocating.SetEvent();
			return 1;
		}
	}
	return 1;
}

UINT _cdecl CDlgRight::Thread_ToOrigin(LPVOID lparam)
{
	BOOL State[3];
	U32 Result;
	U16 Status;
	BOOL bResult(FALSE);
	AxisCoordinate tempaxiscoor;
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	//自动手动时，使用不同的速度
	pApp->mVar.axisoperate.AxisVelSet(0, pApp->mVar.AUTOMAXVEL[0],
		pApp->mVar.MANUALVELLOW[0], pApp->mVar.MANUALVELACC[0], pApp->mVar.MANUALVELACC[0]);
	pApp->mVar.axisoperate.AxisVelSet(1, pApp->mVar.AUTOMAXVEL[1],
		pApp->mVar.MANUALVELLOW[1], pApp->mVar.MANUALVELACC[1], pApp->mVar.MANUALVELACC[1]);
	pApp->mVar.axisoperate.AxisVelSet(2, pApp->mVar.AUTOMAXVEL[2],
		pApp->mVar.MANUALVELLOW[2], pApp->mVar.MANUALVELACC[2], pApp->mVar.MANUALVELACC[2]);

	tempaxiscoor.AxisXCoor = pApp->mVar.ORIGIN[0];
	tempaxiscoor.AxisYCoor = pApp->mVar.ORIGIN[1];
	tempaxiscoor.AxisZCoor = pApp->mVar.ORIGIN[2];

	bResult = pApp->mVar.axisoperate.AxesMoveTo(tempaxiscoor);
	if (!bResult)
	{
		AfxMessageBox(_T("Thread_Org move Failed"));
		return 1;
	}
	Sleep(50);
	while (1)
	{
		Sleep(10);
		if (pApp->mVar.bStopped)
		{
			Event_ToOrigin.SetEvent();
			return 0;
		}
		for (unsigned int i = 0; i < pApp->mVar.m_ulAxisCount; i++)
		{
			Result = Acm_AxGetState(pApp->mVar.m_Axishand[i], &Status);
			if (Result == SUCCESS)
			{
				if (Status == 1)
					State[i] = TRUE;
				else
					State[i] = FALSE;
			}
		}
		if (State[0] == TRUE && State[1] == TRUE && State[2] == TRUE)
		{
			Event_ToOrigin.SetEvent();
			return 1;
		}
	}
	return 1;
}


UINT _cdecl CDlgRight::Thread_ZUpLocating(LPVOID lparam)
{
	gbThread_ZLocation = TRUE;

	U32 Result;
	U16 Status;
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();

	pApp->mVar.axisoperate.AxisVelSet(2, pApp->mVar.AUTOMAXVEL[2],
		pApp->mVar.MANUALVELLOW[2], pApp->mVar.MANUALVELACC[2], pApp->mVar.MANUALVELACC[2]);

	pApp->mVar.axisoperate.AxisMovePtp(2, -pApp->mVar.ZUPDISTANCE, 1);
	Sleep(10);
	while (1)
	{
		Sleep(10);
		if (pApp->mVar.bStopped)
		{
			Event_ZUpLocating.SetEvent();
			gbThread_ZLocation = FALSE;
			return 1;
		}
		Result = Acm_AxGetState(pApp->mVar.m_Axishand[2], &Status);
		if (Result == SUCCESS)
		{
			if (Status == 1)
			{
				Event_ZUpLocating.SetEvent();
				gbThread_ZLocation = FALSE;

				return 1;
			}
		}
	}
	gbThread_ZLocation = FALSE;
	return 1;
}

UINT _cdecl CDlgRight::Thread_XYLocating(LPVOID lparam)
{
	gbThread_XYLocation = TRUE;
	U16 State[2];
	U32 Result;
	U16 Status;
	BOOL bResult(FALSE);
	AxisCoordinate tempaxiscoor;
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();

	if (!bXAxisPull)
	{
		pApp->mVar.axisoperate.AxisVelSet(0, pApp->mVar.AUTOMAXVEL[0],
			pApp->mVar.MANUALVELLOW[0], pApp->mVar.MANUALVELACC[0], pApp->mVar.MANUALVELACC[0]);
		pApp->mVar.axisoperate.AxisVelSet(1, pApp->mVar.AUTOMAXVEL[1],
			pApp->mVar.MANUALVELLOW[1], pApp->mVar.MANUALVELACC[1], pApp->mVar.MANUALVELACC[1]);

		tempaxiscoor.AxisXCoor = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisXCoor;
		tempaxiscoor.AxisYCoor = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisYCoor;

		bResult = pApp->mVar.axisoperate.AxisMovePtp(0, tempaxiscoor.AxisXCoor, 0);
		if (!bResult)
			AfxMessageBox(_T("XY定位--X"));
		bResult = pApp->mVar.axisoperate.AxisMovePtp(1, tempaxiscoor.AxisYCoor, 0);
		if (!bResult)
			AfxMessageBox(_T("XY定位--Y"));
		Sleep(50);
		while (1)
		{
			Sleep(10);
			if (pApp->mVar.bStopped)
			{
				Event_XYLocating.SetEvent();
				gbThread_XYLocation = FALSE;
				return 1;
			}
			for (unsigned int i = 0; i < 2; i++)
			{
				Result = Acm_AxGetState(pApp->mVar.m_Axishand[i], &Status);
				if (Result == SUCCESS)
				{
					if (Status == 1)
						State[i] = TRUE;
					else
						State[i] = FALSE;
				}
			}
			if (State[0] == TRUE && State[1] == TRUE)
			{
				Event_XYLocating.SetEvent();
				gbThread_XYLocation = FALSE;

				return 1;
			}
		}
	}
	else
	{
		bXAxisPull = FALSE;
		pApp->mVar.axisoperate.GrpVelSet(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].StartSpd,
			0, pApp->mVar.MANUALVELACC[0], pApp->mVar.MANUALVELACC[0]);
		tempaxiscoor.AxisXCoor = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber + 1].AutoCoor.AxisXCoor;
		tempaxiscoor.AxisYCoor = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber + 1].AutoCoor.AxisYCoor;
		tempaxiscoor.AxisZCoor = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber + 1].AutoCoor.AxisZCoor;
		pApp->mVar.axisoperate.LinearInterpolation(tempaxiscoor.AxisXCoor, tempaxiscoor.AxisYCoor, tempaxiscoor.AxisZCoor);
		double m_disx = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber + 1].AutoCoor.AxisXCoor - pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisXCoor;
		double m_disy = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber + 1].AutoCoor.AxisYCoor - pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisYCoor;
		double m_totaldis = (double)sqrtf((float)(m_disx*m_disx + m_disy*m_disy));
		double m_stepdis = m_totaldis / 100;
		double m_stepaddspd = (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].StopSpd - pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].StartSpd) / 100;
		int addtimes = 0;
		double pos[2];
		double temptotaldis = 0;
		double tempxdis;
		double tempydis;
		double tempspd;
		Sleep(10);
		while (1)
		{
			Sleep(10);
			if (pApp->mVar.bStopped)
			{
				Event_XYLocating.SetEvent();
				gbThread_XYLocation = FALSE;

				return 1;
			}
			for (unsigned int i = 0; i < 2; i++)
			{
				Result = Acm_AxGetState(pApp->mVar.m_Axishand[i], &Status);
				if (Result == SUCCESS)
				{
					if (Status == 1)
						State[i] = TRUE;
					else
						State[i] = FALSE;
				}
			}
			if (State[0] == TRUE && State[1] == TRUE)
			{
				pApp->mVar.RealSpd = 0;
				if (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStopDelay >= 0)
				{
				//	Sleep(int(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStopDelay * 1000));
				
					double k = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStopDelay;
					for (int i = INT(k); i != 0; i--, k--)
					{
						if (pApp->mVar.bStopped)
						{
//							AfxMessageBox(_T("ESC4"));
							break;
						}
						Sleep(1000);
					}
					if (pApp->mVar.bStopped)
						break;
					Sleep(k * 1000);
				
				}
				pApp->mVar.RealCurrent = 0;
				pApp->mVar.m_IO.SendAOPort(0x00, 0);
				Event_XYLocating.SetEvent();
				gbThread_XYLocation = FALSE;

				return 1;
			}
			for (unsigned int i = 0; i < 2; i++)
			{
				pos[i] = pApp->mVar.axisoperate.GetAxisRealPos(i);
			}
			tempxdis = pos[0] - pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisXCoor;
			tempydis = pos[1] - pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisYCoor;
			temptotaldis = (double)sqrtf((float)(tempxdis*tempxdis + tempydis*tempydis));
			if ((temptotaldis - m_stepdis) >= m_stepdis*addtimes)
			{
				//				addtimes++;
				addtimes = (int)(temptotaldis / m_stepdis) + 1;
				tempspd = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].StartSpd + m_stepaddspd*addtimes;
				pApp->mVar.RealSpd = tempspd;
				if (tempspd > 4000000)
					AfxMessageBox(_T("速度值错误"));
				else
					pApp->mVar.axisoperate.GrpVelChange(tempspd);
				//				Acm_GpGetCmdVel(pApp->mVar.m_GpHand,&tempspd);
				//				pApp->mVar.PullSpdData((int)(tempspd*10));
			}
			if (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStopDelay < 0)
			{
				if ((m_totaldis - temptotaldis) < pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].StopSpd*(-pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStopDelay))
				{
					pApp->mVar.RealCurrent = 0;
					pApp->mVar.m_IO.SendAOPort(0x00, 0);
				}
			}
			if (pApp->mVar.bStopped)
			{
				Event_XYLocating.SetEvent();
				gbThread_XYLocation = FALSE;

				return 1;
			}
		}
	}
	gbThread_XYLocation = FALSE;

	return 1;
}

void CDlgRight::OnHome()
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	if (pApp->mVar.m_bOperating)
		return;
	for (int i = 0; i < 3; i++)
	{
		pApp->mVar.axisoperate.AxisVelSet(i, pApp->mVar.HOMEVELHIGH[i], pApp->mVar.HOMEVELLOW[i],
			pApp->mVar.HOMEVELACC[i], pApp->mVar.HOMEVELACC[i]);
		pApp->mVar.axisoperate.AxisHome(i, pApp->mVar.HOMEMODE);
	}
	pApp->mVar.m_bHomeDown = TRUE;
}

void CDlgRight::OnStop()
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pApp->mVar.m_IO.SendAOPort(0x00, 0);


	pApp->mVar.bStopped = TRUE;
	Event_Stop.SetEvent();
	//	pApp->mVar.m_bOperating = FALSE;
	m_bPause = FALSE;
	pApp->mVar.RealCurrent = 0;
	for (unsigned short i = 0; i < MAXAXISCOUNT; i++)
		pApp->mVar.axisoperate.AxisStopDec(i);
	::PostMessage(pFrm->pDlgPull->m_hWnd, IDC_L_UPDATE_MESSAGE, 0, 0);
}

void CDlgRight::OnChangePTPDistance()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	CString tempstr;
	GetDlgItemText(IDC_PTPDistance, tempstr);
	m_dptpdistance = _ttof(tempstr);
	pApp->mVar.m_dPtpDistance = m_dptpdistance;
}

void CDlgRight::OnChkkeymove()
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	if (pApp->mVar.m_bKeyMoveEnable)
		pApp->mVar.m_bKeyMoveEnable = FALSE;
	else
		pApp->mVar.m_bKeyMoveEnable = TRUE;
}

void CDlgRight::OnStart()
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);

	if (pApp->mVar.m_bHomeDown == FALSE)
	{
		AfxMessageBox(_T("请先完成设备机械回零!"));
		return;
	}
	if (pApp->mVar.m_bOperating)
		return;

	pApp->mVar.bStopped = FALSE;
	int nID = GetFocus()->GetDlgCtrlID();
	if (IDC_START == nID || IDC_Home == nID || IDC_ManualMoveTo == nID)
		GetDlgItem(IDC_XRealPos)->SetFocus();

	//判断是否为单点加工
	if (!pApp->mVar.SINGLEPOINT)
	{
		if (!m_bPause)
		{
			pApp->mVar.currentpointnumber = 0;
			::PostMessage(pFrm->pDlgPull->m_hWnd, IDC_L_UPDATE_MESSAGE, 0, 0);
		}

	}
	m_bPause = FALSE;
	pApp->mVar.TOTALOPERATINGTIMES++;
	Event_Stop.ResetEvent();
	pApp->mVar.StartTime = GetTickCount();
	pApp->mVar.m_bOperating = TRUE;
	pThread_Operating = AfxBeginThread(Thread_Operating, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
}

UINT _cdecl CDlgRight::Thread_Operating(LPVOID lparam)
{
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	float CurrentValue;
	BOOL  bTemp = FALSE;
	int nCount(0);
	DWORD dwResult(0);
	BOOL bXYLocation(FALSE);
	BOOL bLocation(FALSE);
	BOOL bZLocation(FALSE);
	BOOL bLaserContinue(FALSE);
	BOOL bGoToOrg(FALSE);
	pApp->mVar.m_IO.WriteDOPort(pApp->mVar.COILSWITCHPORT, TRUE);
	Sleep((int)(pApp->mVar.COILONDELAY * 1000));
	for (;;)
	{
		if (pApp->mVar.bStopped)
			break;
		Event_AllLocating.ResetEvent();
		Event_XYLocating.ResetEvent();
		if (pApp->mVar.SINGLEPOINT)
		{
			if (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].PointType == 2)
				break;
			if (pApp->mVar.currentpointnumber >= pApp->mVar.totalpointnumber - 1)
				break;
		}
		while (gbThread_XYLocation && nCount < 100)
		{
			Sleep(10);
			nCount++;
			if (pApp->mVar.bStopped)
				break;
		}
		nCount = 0;
		if (pApp->mVar.bStopped)
			break;
		if (gbThread_XYLocation)
		{
			AfxMessageBox(_T("XY 定位线程超时1"));
			break;
		}
		g_hEventArray[1] = Event_XYLocating.m_hObject;
		pThread_XYLocating = AfxBeginThread(Thread_XYLocating, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
		dwResult = WaitForMultipleObjects(2,g_hEventArray,FALSE,10000);
		switch (dwResult)
		{
		case WAIT_OBJECT_0:
			break;
		case WAIT_OBJECT_0 +1:
			bXYLocation = TRUE;
			break;
		case WAIT_TIMEOUT:
			bXYLocation = FALSE;
			AfxMessageBox(_T("X Y 轴定位超时1"));
		default:
			break;
		}
		/*		dwResult = WaitForSingleObject(Event_XYLocating, 10000);
		switch (dwResult)
		{
		case WAIT_OBJECT_0:
			bXYLocation = TRUE;
			break;
		case WAIT_TIMEOUT:
			bXYLocation = FALSE;
			AfxMessageBox(_T("X Y 轴定位超时1"));
		default:
			break;
		}
*/
		if (pApp->mVar.bStopped || !bXYLocation)
			break;
		pThread_Locating = AfxBeginThread(Thread_Locating, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
		g_hEventArray[1] = Event_AllLocating.m_hObject;
		dwResult = WaitForMultipleObjects(2, g_hEventArray, FALSE, 10000);
		switch (dwResult)
		{
		case WAIT_OBJECT_0:
			break;
		case WAIT_OBJECT_0 + 1:
			bLocation = TRUE;
			break;
		case WAIT_TIMEOUT:
			bLocation = FALSE;
			AfxMessageBox(_T("定位超时1"));
		default:
			break;
		}
/*		pThread_Locating = AfxBeginThread(Thread_Locating, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
		dwResult = WaitForSingleObject(Event_AllLocating, 10000);
		switch (dwResult)
		{
		case WAIT_OBJECT_0:
			bLocation = TRUE;
			break;
		case WAIT_TIMEOUT:
			bLocation = FALSE;
			AfxMessageBox(_T("定位超时1"));
		default:
			break;
		}
*/
		if (pApp->mVar.bStopped || !bLocation)
			break;
		if (!pApp->mVar.SINGLEPOINT)
		{
			U32 Result;
			//			U16 Status;
			U32 ArrayElements = 3;
			double EndPoint_DataArray[3];
			CString strTemp;
			double dTemp;
			Event_LaserContinue.ResetEvent();
			bMiddleStop = FALSE;
			tempmaxpointnumber = 0;
			Result = Acm_GpResetPath(&pApp->mVar.m_GpHand);
			if (Result != SUCCESS)
			{
				strTemp.Format(_T("Reset Path Failed with Error Code:%xh"), Result);
				AfxMessageBox(strTemp);
				break;
			}

			dTemp = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].StartSpd;
			Result = Acm_SetProperty(pApp->mVar.m_GpHand, PAR_GpVelHigh, &dTemp, sizeof(dTemp));
			if (Result != SUCCESS)
			{
				strTemp.Format(_T("Reset Path Failed with Error Code:%xh"), Result);
				AfxMessageBox(strTemp);
				break;
			}

			if (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].PointType == 2)
			{
				if (pApp->mVar.currentpointnumber >= pApp->mVar.totalpointnumber - 1)
				{
					bTemp = FALSE;
				}
				else
				{
					pApp->mVar.currentpointnumber++;
					::PostMessage(pFrm->pDlgPull->m_hWnd, IDC_L_UPDATE_MESSAGE, 0, 0);
					continue;
				}
			}
			else
				bTemp = TRUE;

			if (bTemp)
			{
				for (unsigned short pathnumber = pApp->mVar.currentpointnumber; pathnumber < pApp->mVar.totalpointnumber - 1; pathnumber++)
				{
					if (pApp->mVar.m_autopara[pathnumber].PointType == 2)
						continue;

					EndPoint_DataArray[0] = pApp->mVar.m_autopara[pathnumber + 1].AutoCoor.AxisXCoor;
					EndPoint_DataArray[1] = pApp->mVar.m_autopara[pathnumber + 1].AutoCoor.AxisYCoor;
					EndPoint_DataArray[2] = pApp->mVar.m_autopara[pathnumber + 1].AutoCoor.AxisZCoor;
					Result = Acm_GpAddPath(pApp->mVar.m_GpHand, Abs3DLine, 0, pApp->mVar.m_autopara[pathnumber].StartSpd,
						pApp->mVar.m_autopara[pathnumber].StartSpd, EndPoint_DataArray, NULL, &ArrayElements);
					if (Result != SUCCESS)
					{
						strTemp.Format(_T("%d Add path failed with Error Code:%xh"), pathnumber, Result);
						AfxMessageBox(strTemp);
						break;
					}
					if (pApp->mVar.m_autopara[pathnumber].LaserStopDelay > 0.01)
					{
						Result = Acm_GpAddPath(pApp->mVar.m_GpHand, GPDELAY, 0, (int)(pApp->mVar.m_autopara[pathnumber].LaserStopDelay * 1000),
							0, NULL, NULL, &ArrayElements);
						if (Result != SUCCESS)
						{
							strTemp.Format(_T("%d Add path failed with Error Code:%xh"), pathnumber, Result);
							AfxMessageBox(strTemp);
							break;
						}
						tempmaxpointnumber = pathnumber;
						bMiddleStop = TRUE;
						break;
					}
					if (pApp->mVar.m_autopara[pathnumber + 1].PointType == 2)
						break;
				}
				Result = Acm_GpAddPath(pApp->mVar.m_GpHand, EndPath, 0, 0, 0, NULL, NULL, &ArrayElements);
				if (Result != SUCCESS)
				{
					strTemp.Format(_T("%d Add path failed with Error Code:%xh"), -1, Result);
					AfxMessageBox(strTemp);
					break;
				}
				if (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay >= 0)
				{
					pThread_LaserContinue = AfxBeginThread(Thread_LaserContinue, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);

					if (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay > 0.01)
					//	Sleep(int(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay * 1000));
					{
						double k = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay;
						for (int i = INT(k); i != 0; i--, k--)
						{
							if (pApp->mVar.bStopped)
								break;
							Sleep(1000);
						}
						if (pApp->mVar.bStopped)
							break;
						Sleep(k * 1000);
					}
					if (pApp->mVar.bStopped)
						break;
					if (pApp->mVar.OPERATEMODE)
					{
						TempStop = FALSE;
						pThread_LaserTemp = AfxBeginThread(Thread_LaserTemp, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
					}
					else
					{
						CurrentValue = (float)(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].Current / 10.);
						CurrentValue > MAXLASERVOLTAGE ? CurrentValue = MAXLASERVOLTAGE : CurrentValue;

						if (!pApp->mVar.SIMULATION)
						{
							pApp->mVar.RealCurrent = CurrentValue * 10;
							pApp->mVar.m_IO.SendAOPort(0x00, CurrentValue);
						}
					}
				}
				else
				{
					if (pApp->mVar.OPERATEMODE)
					{
						TempStop = FALSE;
						pThread_LaserTemp = AfxBeginThread(Thread_LaserTemp, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
					}
					else
					{
						CurrentValue = (float)(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].Current / 10.);
						CurrentValue > MAXLASERVOLTAGE ? CurrentValue = MAXLASERVOLTAGE : CurrentValue;

						if (!pApp->mVar.SIMULATION)
						{
							pApp->mVar.RealCurrent = CurrentValue * 10;
							pApp->mVar.m_IO.SendAOPort(0x00, CurrentValue);
						}
					}
					if (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay < -0.01)
					//	Sleep(int(-pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay * 1000));
					{
						double k = -pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay;
						for (int i = INT(k); i != 0; i--, k--)
						{
							if (pApp->mVar.bStopped)
							{
//								AfxMessageBox(_T("ESC1"));
								break;
							}
							Sleep(1000);
						}
						if (pApp->mVar.bStopped)
							break;
						Sleep(k * 1000);
					}
					if (pApp->mVar.bStopped)
						break;
					pThread_LaserContinue = AfxBeginThread(Thread_LaserContinue, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
				}
				g_hEventArray[1] = Event_LaserContinue.m_hObject;
				dwResult = WaitForMultipleObjects(2, g_hEventArray, FALSE, 10000);
				switch (dwResult)
				{
				case WAIT_OBJECT_0:
					break;
				case WAIT_OBJECT_0 + 1:
					bLaserContinue = TRUE;
					break;
				case WAIT_TIMEOUT:
					bLaserContinue = FALSE;
					AfxMessageBox(_T("LaserContinue超时1"));
				default:
					break;
				}
/*				dwResult = WaitForSingleObject(Event_LaserContinue, 10000);
				switch (dwResult)
				{
				case WAIT_OBJECT_0:
					bLaserContinue = TRUE;
					break;
				case WAIT_TIMEOUT:
					bLaserContinue = FALSE;
					AfxMessageBox(_T("LaserContinue超时1"));
				default:
					break;
				}
*/			
			}
		}
		else
		{
			if (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay >= 0)
			{
				bXAxisPull = TRUE;
				Event_XYLocating.ResetEvent();
				while (gbThread_XYLocation && nCount < 100)
				{
					Sleep(10);
					nCount++;
					if (pApp->mVar.bStopped)
						break;
				}
				nCount = 0;
				if (pApp->mVar.bStopped)
					break;
				if (gbThread_XYLocation)
				{
					AfxMessageBox(_T("XY定位超时（单点）"));
					break;
				}

				pThread_XYLocating = AfxBeginThread(Thread_XYLocating, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);

				if (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay > 0.01)
				//	Sleep(int(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay * 1000));
				{
					double k = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay;
					for (int i = (int)k; i != 0; i--,k--)
					{
						if (pApp->mVar.bStopped)
							break;
						Sleep(1000);
					}
					Sleep(k*1000);
				}
				if (pApp->mVar.OPERATEMODE)
				{
					TempStop = FALSE;
					pThread_LaserTemp = AfxBeginThread(Thread_LaserTemp, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
				}
				else
				{
					CurrentValue = (float)(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].Current / 10.);
					CurrentValue > MAXLASERVOLTAGE ? CurrentValue = MAXLASERVOLTAGE : CurrentValue;

					if (!pApp->mVar.SIMULATION)
					{
						pApp->mVar.RealCurrent = CurrentValue * 10;
						pApp->mVar.m_IO.SendAOPort(0x00, CurrentValue);
					}
				}
			}
			else
			{
				if (pApp->mVar.OPERATEMODE)
				{
					TempStop = FALSE;
					pThread_LaserTemp = AfxBeginThread(Thread_LaserTemp, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
				}
				else
				{
					float CurrentValue = (float)(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].Current / 10.);
					CurrentValue > MAXLASERVOLTAGE ? CurrentValue = MAXLASERVOLTAGE : CurrentValue;

					if (!pApp->mVar.SIMULATION)
					{
						pApp->mVar.RealCurrent = CurrentValue * 10;
						pApp->mVar.m_IO.SendAOPort(0x00, CurrentValue);
					}
				}
				if (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay < -0.01)
					//Sleep(int(-pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay * 1000));
				{	
					double k = -pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay;
					for (int i = INT(k); i != 0; i--,k--)
					{
						if (pApp->mVar.bStopped)
						{
//							AfxMessageBox(_T("ESC2"));
							break;
						}
						Sleep(1000);
					}
					if (pApp->mVar.bStopped)
						break;
					Sleep(k*1000);
				}
				bXAxisPull = TRUE;
				Event_XYLocating.ResetEvent();
				while (gbThread_XYLocation && nCount < 100)
				{
					Sleep(10);
					nCount++;
					if (pApp->mVar.bStopped)
						break;
				}
				nCount = 0;
				if (pApp->mVar.bStopped)
					break;
				if (gbThread_XYLocation)
				{
					AfxMessageBox(_T("XY定位线程超时2"));
					break;
				}
				pThread_XYLocating = AfxBeginThread(Thread_XYLocating, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);

			}
			g_hEventArray[1] = Event_XYLocating.m_hObject;
			dwResult = WaitForMultipleObjects(2, g_hEventArray, FALSE, 10000);
			switch (dwResult)
			{
			case WAIT_OBJECT_0:
				break;
			case WAIT_OBJECT_0 + 1:
				bXYLocation = TRUE;
				break;
			case WAIT_TIMEOUT:
				bXYLocation = FALSE;
				AfxMessageBox(_T("X Y 轴定位超时2"));
			default:
				break;
			}
			/*
			dwResult = WaitForSingleObject(Event_XYLocating, 10000);
			switch (dwResult)
			{
			case WAIT_OBJECT_0:
				bXYLocation = TRUE;
				break;
			case WAIT_TIMEOUT:
				bXYLocation = FALSE;
				AfxMessageBox(_T("X Y 轴定位超时2"));
			default:
				break;
			}
			*/
		}
		TempStop = TRUE;
		pApp->mVar.RealCurrent = 0;
		pApp->mVar.RealSpd = 0;
		pApp->mVar.m_IO.SendAOPort(0x00, 0);
		if (pApp->mVar.bStopped)
			break;
		if (bMiddleStop)
		{
			continue;
		}
		pApp->mVar.TOTALOPERATINGCOUNTS++;
		if (!gbThread_ZLocation)
		{
			pThread_ZUpLocating = AfxBeginThread(Thread_ZUpLocating, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
		}
		g_hEventArray[1] = Event_ZUpLocating.m_hObject;
		dwResult = WaitForMultipleObjects(2, g_hEventArray, FALSE, 10000);
		switch (dwResult)
		{
		case WAIT_OBJECT_0:
			break;
		case WAIT_OBJECT_0 + 1:
			bZLocation = TRUE;
			break;
		case WAIT_TIMEOUT:
			bZLocation = FALSE;
			AfxMessageBox(_T("Z轴定位超时2"));
		default:
			break;
		}
/*		dwResult = WaitForSingleObject(Event_ZUpLocating, 10000);
		switch (dwResult)
		{
		case WAIT_OBJECT_0:
			bZLocation = TRUE;
			break;
		case WAIT_TIMEOUT:
			bZLocation = FALSE;
			AfxMessageBox(_T("Z轴定位超时2"));
		default:
			break;
		}
*/
		if (pApp->mVar.bStopped || !bZLocation)
			break;
		//判断是否为单点加工
		BOOL startexist = FALSE;
		int tempi;
		if (!pApp->mVar.SINGLEPOINT)
		{
			for (tempi = pApp->mVar.currentpointnumber + 1; tempi < pApp->mVar.totalpointnumber; tempi++)
			{
				if (pApp->mVar.m_autopara[tempi].PointType == 0)
				{
					startexist = TRUE;
					break;
				}
			}

			if (startexist)
			{
				pApp->mVar.currentpointnumber = tempi;
				::PostMessage(pFrm->pDlgPull->m_hWnd, IDC_L_UPDATE_MESSAGE, 0, 0);
			}
			else
			{
				if (pApp->mVar.BACKTOORIGIN)
				{
					Event_ToOrigin.ResetEvent();
					g_hEventArray[1] = Event_ToOrigin.m_hObject;
					pThread_ToOrigin = AfxBeginThread(Thread_ToOrigin, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
					Sleep((int)(pApp->mVar.COILOFFDELAY * 1000));
					pApp->mVar.m_IO.WriteDOPort(pApp->mVar.COILSWITCHPORT, FALSE);
					dwResult = WaitForMultipleObjects(2, g_hEventArray, FALSE, 10000);
					switch (dwResult)
					{
					case WAIT_OBJECT_0:
						break;
					case WAIT_OBJECT_0 + 1:
						bGoToOrg = TRUE;
						break;
					case WAIT_TIMEOUT:
						bGoToOrg = FALSE;
						AfxMessageBox(_T("回原点超时"));
					default:
						break;
					}
					/*
					dwResult = WaitForSingleObject(Event_ToOrigin, 10000);
					switch (dwResult)
					{
					case WAIT_OBJECT_0:
						bGoToOrg = TRUE;
						break;
					case WAIT_TIMEOUT:
						bGoToOrg = FALSE;
						AfxMessageBox(_T("回原点超时"));
					default:
						break;
					}
					*/
					if (pApp->mVar.bStopped || !bGoToOrg)
						break;
				}
				if (pApp->mVar.CIRCLEOPERATE)
				{
					pApp->mVar.currentpointnumber = 0;
					::PostMessage(pFrm->pDlgPull->m_hWnd, IDC_L_UPDATE_MESSAGE, 0, 0);
					Sleep((int)(pApp->mVar.CIRCLEDELAY * 1000));
				}
				else
					break;
			}
			/*			if(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber+1].PointType==2)
						{
						for(int tempi=pApp->mVar.currentpointnumber;tempi<pApp->mVar.totalpointnumber;tempi++)
						if(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber+1].PointType==1);
						if(pApp->mVar.currentpointnumber>=pApp->mVar.totalpointnumber-2)
						{

						}
						else
						{
						pApp->mVar.currentpointnumber+=2;
						::PostMessage(pFrm->pDlgPull->m_hWnd,IDC_L_UPDATE_MESSAGE,0,0);
						}
						}
						else
						break;*/
		}
		else
		{
			if (!pApp->mVar.CIRCLEOPERATE)
				break;
			else
				Sleep((int)(pApp->mVar.CIRCLEDELAY * 1000));
		}
	}
	//	Sleep((int)(pApp->mVar.COILOFFDELAY*1000));
	pApp->mVar.m_IO.WriteDOPort(pApp->mVar.COILSWITCHPORT, FALSE);
	pApp->mVar.RealCurrent = 0;
	pApp->mVar.RealSpd = 0.0;
	pApp->mVar.m_bOperating = FALSE;
//	AfxMessageBox(_T("esc-----"));
	return 1;
}

UINT _cdecl CDlgRight::Thread_LaserContinue(LPVOID lparam)
{
	float CurrentValue;
	double temptime = 0;
	U32 Result;
	U16 Status;
	U32 ArrayElements = 3;
	//	double EndPoint_DataArray[3];
	CString strTemp;
	U32 Index, FreeCnt, Remain, CurCmd;
	//	U32 iTemp;
	//	double dTemp;
	int OldPath = -1;
	int tempcurrentnumber;
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);

	/*	Result = Acm_GpResetPath(&pApp->mVar.m_GpHand);
		if(Result != SUCCESS)
		{
		strTemp.Format(_T("Reset Path Failed with Error Code:%xh"),Result);
		AfxMessageBox(strTemp);
		Event_LaserContinue.SetEvent();
		return FALSE;
		}

		iTemp=0;
		Result= Acm_SetProperty(pApp->mVar.m_GpHand, CFG_GpBldTime, &iTemp, sizeof(iTemp));
		if (Result!=SUCCESS)
		{
		AfxMessageBox(_T("Set Property CFG_GpBldTime Failed"));
		Event_LaserContinue.SetEvent();
		return FALSE;
		}

		iTemp=1;
		Result= Acm_SetProperty(pApp->mVar.m_GpHand, CFG_GpSFEnable, &iTemp, sizeof(iTemp));
		if (Result!=SUCCESS)
		{
		AfxMessageBox(_T("Set Property CFG_GpSFEnable Failed"));
		Event_LaserContinue.SetEvent();
		return FALSE;
		}

		dTemp=pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].StartSpd;
		Result= Acm_SetProperty(pApp->mVar.m_GpHand, PAR_GpVelHigh, &dTemp, sizeof(dTemp));
		if (Result!=SUCCESS)
		{
		strTemp.Format(_T("Reset Path Failed with Error Code:%xh"),Result);
		AfxMessageBox(strTemp);
		Event_LaserContinue.SetEvent();
		return FALSE;
		}

		for(unsigned short pathnumber=pApp->mVar.currentpointnumber;pathnumber<pApp->mVar.totalpointnumber-1;pathnumber++)
		{
		EndPoint_DataArray[0]=pApp->mVar.m_autopara[pathnumber+1].AutoCoor.AxisXCoor;
		EndPoint_DataArray[1]=pApp->mVar.m_autopara[pathnumber+1].AutoCoor.AxisYCoor;
		EndPoint_DataArray[2]=pApp->mVar.m_autopara[pathnumber+1].AutoCoor.AxisZCoor;
		Result=Acm_GpAddPath (pApp->mVar.m_GpHand,Abs3DLine, 0,pApp->mVar.m_autopara[pathnumber].StartSpd,
		pApp->mVar.m_autopara[pathnumber].StartSpd, EndPoint_DataArray,NULL,&ArrayElements);
		if (Result!=SUCCESS)
		{
		strTemp.Format(_T("%d Add path failed with Error Code:%xh"),pathnumber,Result);
		AfxMessageBox(strTemp);
		Event_LaserContinue.SetEvent();
		return 1;
		}
		if(pApp->mVar.m_autopara[pathnumber+1].PointType==2)
		break;
		}
		Result=Acm_GpAddPath (pApp->mVar.m_GpHand,EndPath, 0,0,0, NULL,NULL,&ArrayElements);
		if (Result!=SUCCESS)
		{
		strTemp.Format(_T("%d Add path failed with Error Code:%xh"),-1,Result);
		AfxMessageBox(strTemp);
		Event_LaserContinue.SetEvent();
		return 1;
		}
		if (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay >=0)
		{
		Result = Acm_GpMovePath (pApp->mVar.m_GpHand,NULL);
		if (Result!=SUCCESS)
		{
		strTemp.Format(_T("Path move failed with Error Code:%xh"),Result);
		AfxMessageBox(strTemp);
		Event_LaserContinue.SetEvent();
		return 1;
		}
		if(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay > 0.01)
		Sleep(int(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay*1000));

		CurrentValue = (float)(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].Current/10.);
		CurrentValue>MAXLASERVOLTAGE ? CurrentValue = MAXLASERVOLTAGE : CurrentValue;

		if(!pApp->mVar.SIMULATION)
		{
		pApp->mVar.RealCurrent=CurrentValue*10;
		pApp->mVar.m_IO.SendAOPort(0x00,CurrentValue);
		}
		}
		else
		{
		CurrentValue = (float)(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].Current/10.);
		CurrentValue>MAXLASERVOLTAGE ? CurrentValue = MAXLASERVOLTAGE : CurrentValue;

		if(!pApp->mVar.SIMULATION)
		{
		pApp->mVar.RealCurrent=CurrentValue*10;
		pApp->mVar.m_IO.SendAOPort(0x00,CurrentValue);
		}
		if(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay < -0.01)
		Sleep(int(-pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStartDelay*1000));

		Result = Acm_GpMovePath (pApp->mVar.m_GpHand,NULL);
		if (Result!=SUCCESS)
		{
		strTemp.Format(_T("Path move failed with Error Code:%xh"),Result);
		AfxMessageBox(strTemp);
		Event_LaserContinue.SetEvent();
		return 1;
		}
		}*/
	Result = Acm_GpMovePath(pApp->mVar.m_GpHand, NULL);
	if (Result != SUCCESS)
	{
		strTemp.Format(_T("Path move failed with Error Code:%xh"), Result);
		AfxMessageBox(strTemp);
		TempStop = TRUE;
		Event_LaserContinue.SetEvent();
		return 1;
	}
	int temppointnumber = pApp->mVar.currentpointnumber;
	while (1)
	{
		Sleep(10);
		if (pApp->mVar.bStopped)
			break;
		Result = Acm_GpGetState(pApp->mVar.m_GpHand, &Status);
		if (Result == SUCCESS)
		{
			if (Status == STA_GP_READY&&!pApp->mVar.bStopped)
			{
				pApp->mVar.RealSpd = 0;
				if (bMiddleStop)
				{
					if (!pApp->mVar.bStopped)
					{
						pApp->mVar.currentpointnumber++;
						::PostMessage(pFrm->pDlgPull->m_hWnd, IDC_L_UPDATE_MESSAGE, 0, 0);
					}
				}
				else
				{
					if (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStopDelay >= 0)
					{
					//	Sleep(int(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStopDelay * 1000));
					
						double k = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStopDelay;
						for (int i = INT(k); i != 0; i--, k--)
						{
							if (pApp->mVar.bStopped)
							{
//								AfxMessageBox(_T("ESC3"));
								break;
							}
							Sleep(1000);
						}
						if (pApp->mVar.bStopped)
							break;
						Sleep(k * 1000);
					
					}
				}
				TempStop = TRUE;
				pApp->mVar.RealCurrent = 0;
				pApp->mVar.m_IO.SendAOPort(0x00, 0);
				Event_LaserContinue.SetEvent();
				return 1;
			}
		}
		if (pApp->mVar.bStopped)
			break;
		Result = Acm_GpGetPathStatus(pApp->mVar.m_GpHand, &Index, &CurCmd, &Remain, &FreeCnt);
		if (Result == SUCCESS && !pApp->mVar.bStopped)
		{
			if (bMiddleStop)
			if (tempmaxpointnumber < (temppointnumber + (unsigned short)Index - 1))
				continue;
			tempcurrentnumber = temppointnumber + (unsigned short)Index - 1;
			//			::PostMessage(pFrm->pDlgPull->m_hWnd,IDC_L_UPDATE_MESSAGE,0,0);
			if (OldPath != tempcurrentnumber)
			{
				pApp->mVar.currentpointnumber = tempcurrentnumber;
				::PostMessage(pFrm->pDlgPull->m_hWnd, IDC_L_UPDATE_MESSAGE, 0, 0);
				OldPath = pApp->mVar.currentpointnumber;
				if (pApp->mVar.OPERATEMODE)
				{
					double dtemp = (double)(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoTemp);
					dtemp = (dtemp - 100)*pApp->mVar.TEMPORATURERATIO / 500.;
					temporatureValue = dtemp;
				}
				else
				{
					CurrentValue = (float)(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].Current / 10.);
					CurrentValue > MAXLASERVOLTAGE ? CurrentValue = MAXLASERVOLTAGE : CurrentValue;

					if (!pApp->mVar.SIMULATION)
					{
						pApp->mVar.RealCurrent = CurrentValue * 10;
						pApp->mVar.m_IO.SendAOPort(0x00, CurrentValue);
					}
				}
			}

			double m_disx = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber + 1].AutoCoor.AxisXCoor - pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisXCoor;
			double m_disy = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber + 1].AutoCoor.AxisYCoor - pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisYCoor;
			double m_totaldis = (double)sqrtf((float)(m_disx*m_disx + m_disy*m_disy));
			double m_stepdis = m_totaldis / 100;
			double m_stepaddspd = (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].StopSpd - pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].StartSpd) / 100;
			int addtimes = 0;
			double pos[2];
			double temptotaldis = 0;
			double tempxdis;
			double tempydis;
			double tempspd;

			for (unsigned int i = 0; i < 2; i++)
			{
				pos[i] = pApp->mVar.axisoperate.GetAxisRealPos(i);
			}
			tempxdis = pos[0] - pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisXCoor;
			tempydis = pos[1] - pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoCoor.AxisYCoor;
			temptotaldis = (double)sqrtf((float)(tempxdis*tempxdis + tempydis*tempydis));
			if ((temptotaldis - m_stepdis) >= m_stepdis*addtimes)
			{
				addtimes = (int)(temptotaldis / m_stepdis) + 1;
				tempspd = pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].StartSpd + m_stepaddspd*addtimes;
				pApp->mVar.RealSpd = tempspd;
				if (pApp->mVar.bStopped)
					break;
				if (tempspd > 4000000)
					AfxMessageBox(_T("速度值错误"));
				else
					pApp->mVar.axisoperate.GrpVelChange(tempspd);
			}
			if (pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStopDelay < 0)
			{
				if ((m_totaldis - temptotaldis) < pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].StopSpd*(-pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].LaserStopDelay))
				{
					TempStop = TRUE;
					pApp->mVar.RealCurrent = 0;
					pApp->mVar.m_IO.SendAOPort(0x00, 0);
				}
			}
		}
	}
	TempStop = TRUE;
	pApp->mVar.RealCurrent = 0;
	pApp->mVar.RealSpd = 0;
	pApp->mVar.m_IO.SendAOPort(0x00, 0);
	Event_LaserContinue.SetEvent();
	return 1;
}

UINT _cdecl CDlgRight::Thread_LaserTime(LPVOID lparam)
{
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	float CurrentValue = (float)(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].Current / 10.);
	CurrentValue > MAXLASERVOLTAGE ? CurrentValue = MAXLASERVOLTAGE : CurrentValue;

	pApp->mVar.RealCurrent = CurrentValue * 10;
	pApp->mVar.m_IO.SendAOPort(0x00, CurrentValue);

	return 1;
}

UINT _cdecl CDlgRight::Thread_TempSample(LPVOID lparam)
{
	double dtemp;
	double aiValue;
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	while (1)
	{
		Sleep(50);
		aiValue = 0;//pApp->mVar.m_IO.ReadAIPort(SAMPLETEMPERATUREPORT & 0x0f);
		dtemp = aiValue * 50 / pApp->mVar.TEMPORATURERATIO;
		pApp->mVar.PullTempData((int)(dtemp));
		//		Acm_GpGetCmdVel(pApp->mVar.m_GpHand,&dtemp);
		//		pApp->mVar.PullSpdData((int)(dtemp*10));
	}
	return 1;
}

UINT _cdecl CDlgRight::Thread_FootSwitch(LPVOID lparam)
{
	U16		m_InputValue;
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);

	while (1)
	{
		if (!pApp->mVar.m_bOperating)
		{
			m_InputValue = pApp->mVar.m_IO.ReadDIPort();
			if (!pApp->mVar.m_bOperating && !(m_InputValue & (0x0001 << pApp->mVar.FOOTSWITCHPORT)))
			{
				Sleep(50);
				m_InputValue = pApp->mVar.m_IO.ReadDIPort();
				if (!pApp->mVar.m_bOperating && !(m_InputValue & (0x0001 << pApp->mVar.FOOTSWITCHPORT)))
				{
					::PostMessage(pFrm->pDlgRight->m_hWnd, IDC_F2_MESSAGE, 0, 0);
				}
			}
		}
		Sleep(200);
	}
	return 1;
}

void CDlgRight::OnFootswitch()
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();

	if (!pApp->mVar.FOOTSWITCHENABLE)
	{
		pApp->mVar.FOOTSWITCHENABLE = TRUE;
		pThread_FootSwitch->ResumeThread();
	}
	else
	{
		pApp->mVar.FOOTSWITCHENABLE = FALSE;
		pThread_FootSwitch->SuspendThread();
	}
}

void CDlgRight::OnSimulation()
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	pApp->mVar.SIMULATION = !pApp->mVar.SIMULATION;
}

void CDlgRight::OnSinglepoint()
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	pApp->mVar.SINGLEPOINT = !pApp->mVar.SINGLEPOINT;
}

void CDlgRight::OnCircleoperate()
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	pApp->mVar.CIRCLEOPERATE = !pApp->mVar.CIRCLEOPERATE;
}

void CDlgRight::OnPause()
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pApp->mVar.m_IO.SendAOPort(0x00, 0);
	for (unsigned short i = 0; i < MAXAXISCOUNT; i++)
		pApp->mVar.axisoperate.AxisStopDec(i);

	pApp->mVar.bStopped = TRUE;
//	pApp->mVar.m_bOperating = FALSE;
	m_bPause = TRUE;
	pApp->mVar.RealCurrent = 0;
	::PostMessage(pFrm->pDlgPull->m_hWnd, IDC_L_UPDATE_MESSAGE, 0, 0);
}

LRESULT CDlgRight::OnMessageLBtnDown(WPARAM wParam, LPARAM lParam)
{
	XForwardLBottonDown((unsigned short)wParam, (unsigned short)lParam);
	return TRUE;
}

LRESULT CDlgRight::OnMessageLBtnUp(WPARAM wParam, LPARAM lParam)
{
	XForwardLBottonUp((unsigned short)wParam, (unsigned short)lParam);
	return TRUE;
}

void CDlgRight::OnLasertest()
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();

	pApp->mVar.bStopped = FALSE;

	pThread_LaserTime = AfxBeginThread(Thread_LaserTime, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
}

void CDlgRight::OnRenewCoordinate()
{
	// TODO: Add your control notification handler code here
	//更新上料位坐标
	double pos[4];
	double CurPos;
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	//	CMainFrame *pFrm=(CMainFrame *)(AfxGetApp()->m_pMainWnd);

	for (unsigned int i = 0; i < pApp->mVar.m_ulAxisCount; i++)
	{
		Acm_AxGetCmdPosition(pApp->mVar.m_Axishand[i], &CurPos);
		pos[i] = CurPos;
	}
	pApp->mVar.ORIGIN[0] = pos[0];
	pApp->mVar.ORIGIN[1] = pos[1];
	pApp->mVar.ORIGIN[2] = pos[2];
	//	::PostMessage(pFrm->pDlgPull->m_hWnd,IDC_L_UPDATE_MESSAGE,0,0);
}


BOOL CDlgRight::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	/*	CBrush backBrush(SysColor);

		CBrush* pOldBrush = pDC->SelectObject(&backBrush);
		CRect rect;
		pDC->GetClipBox(&rect);
		pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
		pDC->SelectObject(pOldBrush);
		backBrush.DeleteObject();
		DeleteObject(pOldBrush);
		return TRUE;*/
	return CFormView::OnEraseBkgnd(pDC);
}

HBRUSH CDlgRight::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	/*	// TODO: Change any attributes of the DC here
		if(nCtlColor == CTLCOLOR_STATIC)
		{
		if(pWnd->GetDlgCtrlID() != IDC_OPE)
		{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);//CreateSolidBrush(RGB(234,178,153));
		}
		else
		{
		pDC->SetBkColor(SysColor);
		return (HBRUSH)GetStockObject(NULL_BRUSH);//CreateSolidBrush(RGB(234,178,153));
		}
		}
		if(nCtlColor == CTLCOLOR_BTN)
		{
		pDC->SetBkColor(SysColor);
		//		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);//CreateSolidBrush(RGB(234,178,153));
		}*/
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

LRESULT CDlgRight::OnMessageStart(WPARAM wParam, LPARAM lParam)
{
	OnStart();
	return TRUE;
}

LRESULT CDlgRight::OnMessageStop(WPARAM wParam, LPARAM lParam)
{
	OnStop();
	return TRUE;
}

LRESULT CDlgRight::OnMessagePause(WPARAM wParam, LPARAM lParam)
{
	OnPause();
	return TRUE;
}


/*void CDlgRight::OnBnClickedRedlight()
{
// TODO: 在此添加控件通知处理程序代码
CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
unsigned short m_OutputValue=0;
//	m_OutputValue=pApp->mVar.m_IO.ReadDOPort();
if(m_OutputValue & (0x0001<<1))
{
m_OutputValue=m_OutputValue & (~(0x0001<<1));
SetDlgItemText(IDC_RedLight,_T("红光关闭"));
}
else
{
m_OutputValue=m_OutputValue | (0x0001<<1);
SetDlgItemText(IDC_RedLight,_T("红光开启"));
}
//	pApp->mVar.m_IO.WriteDOPort(m_OutputValue);
}
*/

void CDlgRight::OnBnClickedToorigin()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	if (pApp->mVar.m_bHomeDown == FALSE)
	{
		AfxMessageBox(_T("请先完成设备机械回零!"));
		return;
	}
	if (pApp->mVar.m_bOperating)
		return;
	pThread_ToOrigin = AfxBeginThread(Thread_ToOrigin, NULL, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
}

/**************************************************************************************/
//增量法积分限制PID差分调节器
//#include "PID_Regulate.h"
double PID_Regulate_CH1(double ref, double feedback)
{
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();

	double  ch1_ErrorK, ch1_dOutK, ch1_dErrorK;
	//限制输入幅度，归一化到[-1，1]区间
	if (!flaginit)      //初始化参数=0
	{
		ch1_OutK = 0;
		ch1_dErrorK1 = 0;
		ch1_ErrorK1 = 0;
		ch1_ErrorK = 0;
		ch1_dOutK = 0;
		ch1_dErrorK = 0;
		flaginit = TRUE;
	}
	if (ref >= 1) ref = 1;
	if (ref <= -1) ref = -1;
	if (feedback >= 1) feedback = 1;
	if (feedback <= -1) feedback = -1;
	ch1_ErrorK = ref - feedback;
	ch1_dErrorK = ch1_ErrorK - ch1_ErrorK1;//de(K) = e(k) - e(k-1)
	ch1_dOutK = pApp->mVar.KP * ch1_dErrorK / 1000. + pApp->mVar.KI * ch1_ErrorK / 1000. + pApp->mVar.KD * (ch1_dErrorK - ch1_dErrorK1) / 1000.;
	//dU(k) = kp*de(k) + Ki*e(k)+Kd(de(k)- de(k-1))
	ch1_dErrorK1 = ch1_dErrorK; //de(k) -> de(k-1)
	ch1_OutK += ch1_dOutK;//u(k) =  u(k-1) +du(k)

	/*	//位置式PID
		ch1_ErrorK = ref - feedback;
		ch1_dErrorK = ch1_ErrorK - ch1_ErrorK1;
		ch1_dErrorK1 += ch1_ErrorK;//ik
		ch1_ErrorK1 = ch1_ErrorK;
		ch1_dOutK = pApp->mVar.KP * ch1_ErrorK + pApp->mVar.KI * ch1_dErrorK1 + pApp->mVar.KD * ch1_dErrorK;

		//增量式PID
		ch1_ErrorK = ref - feedback;
		ch1_dOutK = pApp->mVar.KP * ch1_ErrorK - pApp->mVar.KI * ch1_ErrorK1 + pApp->mVar.KD * ch1_dErrorK1;
		ch1_dErrorK1 = ch1_ErrorK1;
		ch1_ErrorK1 = ch1_ErrorK;
		ch1_OutK +=ch1_dOutK;*/

	if (ch1_OutK >= 1) ch1_OutK = 1; //限制幅度 1>=u(k)>=-1
	if (ch1_OutK <= -1) ch1_OutK = -1;
	return(ch1_OutK);

	/*	if(!flaginit)
		{
		ch1_OutK = 0;
		ch1_ErrorK = 0;
		ch1_ErrorK1 = 0;
		ch1_GK = 0;
		ch1_GK1 = 0;
		ch1_FK = 0;
		ch1_FK1 = 0;
		}
		ch1_ErrorK = ref -feedback;
		if(fabs(ch1_ErrorK)<= pApp->mVar.THRESHOLD)
		{	//PID
		ch1_OutK = pApp->mVar.KP * ch1_ErrorK +ch1_GK1;
		if(ch1_OutK > 5)	ch1_OutK = 5;
		ch1_GK = ch1_OutK - pApp->mVar.KI * ch1_ErrorK + pApp->mVar.KD * ch1_ErrorK1;
		}
		else
		{	//PD
		ch1_OutK = pApp->mVar.KP1 * ch1_ErrorK - ch1_FK1;
		ch1_FK = pApp->mVar.KD1 * ch1_ErrorK;
		}
		ch1_GK1 = ch1_GK;
		ch1_FK1 = ch1_FK;
		ch1_ErrorK1 = ch1_ErrorK;

		return ch1_OutK;*/
}

UINT _cdecl CDlgRight::Thread_LaserTemp(LPVOID lparam)
{
	//	DWORD times=0;
	double aiValue;
	double aoValue;
	double dtemp;
	int itemp = 0;

	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	pThread_TempCurve->SuspendThread();

	temporatureValue = (double)(pApp->mVar.m_autopara[pApp->mVar.currentpointnumber].AutoTemp);
	temporatureValue = (temporatureValue - 100)*pApp->mVar.TEMPORATURERATIO / 500.;
	flaginit = FALSE;

	while (1)
	{
		if (!pApp->mVar.bStopped && !TempStop)
		{
			Delay1ms(1000 / SAMPLEFREQUENCY);//0.005s
			if (!pApp->mVar.SIMULATION)
			{
				aiValue = pApp->mVar.m_IO.ReadAIPort(SAMPLETEMPERATUREPORT & 0x0f);
				aiValue = aiValue / 10.;
				aoValue = MAXLASERVOLTAGE*PID_Regulate_CH1(temporatureValue, aiValue);

				aoValue > MAXLASERVOLTAGE ? aoValue = MAXLASERVOLTAGE : aoValue;
				pApp->mVar.m_IO.SendAOPort(0x00, (float)aoValue);
				pApp->mVar.RealCurrent = aoValue*10.;
				dtemp = aiValue*500. / pApp->mVar.TEMPORATURERATIO + 100;
				pApp->mVar.RealTemp = dtemp;
			}
			else
				dtemp = 0;
			itemp++;
			if (itemp % 10 == 0)
			{
				itemp = 0;
				pApp->mVar.PullTempData((int)(dtemp - 100));
			}
			//			times++;
			//			pApp->mVar.RealSpd=0.005*times;
		}
		else
		{
			pApp->mVar.m_IO.SendAOPort(0x00, 0.0);
			pApp->mVar.RealCurrent = 0;
			pApp->mVar.RealTemp = 0;
			pThread_TempCurve->ResumeThread();
			//			Event_LaserOff.SetEvent(); 
			return 1;
		}
	}

	pApp->mVar.m_IO.SendAOPort(0x00, 0.0);
	pApp->mVar.RealTemp = 0;
	pApp->mVar.RealCurrent = 0;
	pThread_TempCurve->ResumeThread();
	//	Event_LaserOff.SetEvent();
	return 1;
}

void CDlgRight::OnBnClickedCurrentmode()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	pApp->mVar.OPERATEMODE = FALSE;
	((CButton*)(GetDlgItem(IDC_TEMPMODE)))->SetCheck(pApp->mVar.OPERATEMODE);
	((CButton*)(GetDlgItem(IDC_CURRENTMODE)))->SetCheck(!pApp->mVar.OPERATEMODE);
}


void CDlgRight::OnBnClickedTempmode()
{
	// TODO: 在此添加控件通知处理程序代码
	CLYPESolderingApp *pApp = (CLYPESolderingApp*)AfxGetApp();
	pApp->mVar.OPERATEMODE = TRUE;
	((CButton*)(GetDlgItem(IDC_TEMPMODE)))->SetCheck(pApp->mVar.OPERATEMODE);
	((CButton*)(GetDlgItem(IDC_CURRENTMODE)))->SetCheck(!pApp->mVar.OPERATEMODE);
}
