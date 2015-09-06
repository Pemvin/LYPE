// CCDSet.cpp : implementation file
//

#include "stdafx.h"
#include "LYPESoldering.h"
#include "CCDSet.h"
#include "CCDView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCCDSet dialog


CCCDSet::CCCDSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCCDSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCCDSet)
	m_bVMirrorEnable = FALSE;
	m_CrossX = 0;
	m_CrossY = 0;
	m_Exposure = 0;
	m_Gain = 0;
	m_Light = 0;
	//}}AFX_DATA_INIT
}


void CCCDSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCCDSet)
	DDX_Check(pDX, IDC_CHK_VMIRROR, m_bVMirrorEnable);
	DDX_Text(pDX, IDC_CROSSX, m_CrossX);
	DDV_MinMaxInt(pDX, m_CrossX, 0, 1280);
	DDX_Text(pDX, IDC_CROSSY, m_CrossY);
	DDV_MinMaxInt(pDX, m_CrossY, 0, 1024);
	DDX_Text(pDX, IDC_EXPOSURE, m_Exposure);
	DDV_MinMaxInt(pDX, m_Exposure, 1, 1000);
	DDX_Text(pDX, IDC_GAIN, m_Gain);
	DDV_MinMaxInt(pDX, m_Gain, 1, 100);
	DDX_Text(pDX, IDC_Light, m_Light);
//	DDV_MinMaxInt(pDX, m_Light, 1, 100);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SLD_Light, m_SLDLight);
}


BEGIN_MESSAGE_MAP(CCCDSet, CDialogEx)
	//{{AFX_MSG_MAP(CCCDSet)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHK_VMIRROR, OnChkVmirror)
	ON_EN_KILLFOCUS(IDC_EXPOSURE, OnKillfocusExposure)
	ON_EN_KILLFOCUS(IDC_GAIN, OnKillfocusGain)
	ON_BN_CLICKED(IDC_SAVEBITMAP, OnSavebitmap)
	ON_EN_KILLFOCUS(IDC_CROSSX, OnKillfocusCrossx)
	ON_EN_KILLFOCUS(IDC_CROSSY, OnKillfocusCrossy)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_Light, OnCustomdrawSLDLight)
	ON_EN_KILLFOCUS(IDC_Light, OnKillfocusLight)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CCCDSet::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCCDSet message handlers

void CCCDSet::OnDestroy() 
{
	CDialogEx::OnDestroy();
	
	// TODO: Add your message handler code here
//	delete this;
}

BOOL CCCDSet::OnInitDialog() 
{
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	m_Exposure = pApp->mVar.EXPOSURE;
	m_Gain = pApp->mVar.GAIN;
	m_CrossX = pApp->mVar.CROSSX;
	m_CrossY = pApp->mVar.CROSSY;
	m_bVMirrorEnable = pApp->mVar.VMIRROR;
	m_Light = pApp->mVar.LIGHT;

	TempExposure = m_Exposure;
	TempGain = m_Gain;
	TempCrossX = m_CrossX;
	TempCrossY = m_CrossY;
	TempVMirrorEnable = m_bVMirrorEnable;
	TempLight = m_Light;

	m_SLDLight.SetRange(1,100);
	m_SLDLight.SetLineSize(10);
	m_SLDLight.SetPageSize(5);
	m_SLDLight.SetTicFreq(10);
	m_SLDLight.SetPos(m_Light);

	UpdateData( FALSE );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCCDSet::OnCancel() 
{
	// TODO: Add extra cleanup here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm=(CMainFrame *)(AfxGetApp()->m_pMainWnd);

	pApp->mVar.EXPOSURE = TempExposure;
	pApp->mVar.GAIN = TempGain;
	pApp->mVar.CROSSX = TempCrossX;
	pApp->mVar.CROSSY = TempCrossY;
	pApp->mVar.VMIRROR = TempVMirrorEnable;
	pApp->mVar.LIGHT = TempLight;


	pFrm->pDlgCCDView->SetExposureTime(PICTUREWIDTH,TempExposure,1000);
	pFrm->pDlgCCDView->SetMirror(TempVMirrorEnable);
	pFrm->pDlgCCDView->SetGain(TempGain);
	pApp->mVar.m_IO.SendAOPort(0x01,(float)(TempLight*MAXLASERVOLTAGE/100.));

	CDialogEx::OnCancel();
}

void CCCDSet::OnChkVmirror() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm=(CMainFrame *)(AfxGetApp()->m_pMainWnd);
	UpdateData();
	pFrm->pDlgCCDView->SetMirror(m_bVMirrorEnable);
}

void CCCDSet::OnKillfocusExposure() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm=(CMainFrame *)(AfxGetApp()->m_pMainWnd);
	UpdateData();
	pApp->mVar.EXPOSURE = m_Exposure;
	pFrm->pDlgCCDView->SetExposureTime(PICTUREWIDTH,m_Exposure,1000);
}

void CCCDSet::OnKillfocusGain() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm=(CMainFrame *)(AfxGetApp()->m_pMainWnd);
	UpdateData();
	pApp->mVar.GAIN = m_Gain;
	pFrm->pDlgCCDView->SetGain(m_Gain);
}

void CCCDSet::OnSavebitmap() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pFrm=(CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrm->pDlgCCDView->Savebitmap();
}

void CCCDSet::OnKillfocusCrossx() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	pApp->mVar.CROSSX = GetDlgItemInt(IDC_CROSSX);
}

void CCCDSet::OnKillfocusCrossy() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	pApp->mVar.CROSSY = GetDlgItemInt(IDC_CROSSY);
}

void CCCDSet::OnCustomdrawSLDLight(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
//	UpdateData(TRUE);
	m_Light=m_SLDLight.GetPos();
	UpdateData(FALSE);
	pApp->mVar.LIGHT = m_Light;
	pApp->mVar.m_IO.SendAOPort(0x01,(float)(m_Light*MAXLASERVOLTAGE/100.));
	*pResult = 0;
}

void CCCDSet::OnKillfocusLight() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	UpdateData(TRUE);
	m_SLDLight.SetPos(m_Light);
	pApp->mVar.LIGHT = m_Light;
	pApp->mVar.m_IO.SendAOPort(0x01,(float)(m_Light*MAXLASERVOLTAGE/100.));
}

void CCCDSet::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialogEx::PostNcDestroy();

	delete this;
}


void CCCDSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
