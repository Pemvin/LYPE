// PageFour.cpp : implementation file
//

#include "stdafx.h"
#include "LYPESoldering.h"
#include "PageFour.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int idInput[]={IDC_IN0,IDC_IN1,IDC_IN2,IDC_IN3,IDC_IN4,IDC_IN5,IDC_IN6,IDC_IN7,IDC_IN8,IDC_IN9,
				IDC_IN10,IDC_IN11,IDC_IN12,IDC_IN13,IDC_IN14,IDC_IN15};
int idOutput[]={IDC_OUT0,IDC_OUT1,IDC_OUT2,IDC_OUT3,IDC_OUT4,IDC_OUT5,IDC_OUT6,IDC_OUT7,IDC_OUT8,
				IDC_OUT9,IDC_OUT10,IDC_OUT11,IDC_OUT12,IDC_OUT13,IDC_OUT14,IDC_OUT15};
/////////////////////////////////////////////////////////////////////////////
// CPageFour dialog


CPageFour::CPageFour(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPageFour::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageFour)
	hBitmapRed = ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_RED));
    hBitmapGray= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_GRAY));
	//}}AFX_DATA_INIT
	m_AIChannel = 0;
	m_AOChannel = 0;
	m_bReceiveEnable =FALSE;
}


void CPageFour::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageFour)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO_AICHANNEL, m_cmbAIChannel);
	DDX_Control(pDX, IDC_COMBO_AOCHANNEL, m_cmbAOChannel);
}


BEGIN_MESSAGE_MAP(CPageFour, CDialogEx)
	//{{AFX_MSG_MAP(CPageFour)
	ON_BN_CLICKED(IDC_OUT0, OnOut0)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SENDDATA, OnSenddata)
//	ON_BN_CLICKED(IDC_RECEIVEDATA, OnReceivedata)
	ON_CBN_SELCHANGE(IDC_COMBO_AICHANNEL, OnSelchangeComboAichannel)
	ON_CBN_SELCHANGE(IDC_COMBO_AOCHANNEL, OnSelchangeComboAochannel)
	ON_BN_CLICKED(IDC_STOPRECEIVE, OnStopreceive)
	ON_BN_CLICKED(IDC_OUT1, OnOut0)
	ON_BN_CLICKED(IDC_OUT2, OnOut0)
	ON_BN_CLICKED(IDC_OUT3, OnOut0)
	ON_BN_CLICKED(IDC_OUT4, OnOut0)
	ON_BN_CLICKED(IDC_OUT5, OnOut0)
	ON_BN_CLICKED(IDC_OUT6, OnOut0)
	ON_BN_CLICKED(IDC_OUT7, OnOut0)
	ON_BN_CLICKED(IDC_OUT8, OnOut0)
	ON_BN_CLICKED(IDC_OUT9, OnOut0)
	ON_BN_CLICKED(IDC_OUT10, OnOut0)
	ON_BN_CLICKED(IDC_OUT11, OnOut0)
	ON_BN_CLICKED(IDC_OUT12, OnOut0)
	ON_BN_CLICKED(IDC_OUT13, OnOut0)
	ON_BN_CLICKED(IDC_OUT14, OnOut0)
	ON_BN_CLICKED(IDC_OUT15, OnOut0)
	ON_BN_CLICKED(IDC_STARTRECEIVE, OnStartreceive)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageFour message handlers

BOOL CPageFour::OnInitDialog() 
{
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	m_InputValue=pApp->mVar.m_IO.ReadDIPort();
	m_OutputValue=pApp->mVar.m_IO.ReadDOPort();

	m_cmbAIChannel.SetCurSel(0);
	m_cmbAOChannel.SetCurSel(0);
	RenewObjects();
	SetDlgItemText(IDC_AOVALUE,_T("0"));
	SetTimer(0,200,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageFour::OnOut0() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	int nID=GetFocus()->GetDlgCtrlID();
	short pos;
	for(pos=0;pos<16;pos++)
		if(nID==idOutput[pos])
			break;
		else 
			continue;
		if(m_OutputValue & (0x0001<<pos))
		{
			m_OutputValue=m_OutputValue & (~(0x0001<<pos));
			pApp->mVar.m_IO.WriteDOPort(pos,FALSE);
		}
		else
		{
			m_OutputValue=m_OutputValue | (0x0001<<pos);
			pApp->mVar.m_IO.WriteDOPort(pos,TRUE);
		}
		RenewObjects();
}

void CPageFour::RenewObjects()
{
	CButton * pBtn;
	for(int i=0;i<16;i++)
	{
		pBtn = (CButton*)GetDlgItem(idInput[i]);
		if (m_InputValue&(0x0001<<i))//ORG 
		{		
			pBtn->SetBitmap(hBitmapRed);
		}
		else
		{
			pBtn->SetBitmap(hBitmapGray);
		}
		pBtn = (CButton*)GetDlgItem(idOutput[i]);
		if (m_OutputValue&(0x0001<<i))//ORG 
		{		
			pBtn->SetBitmap(hBitmapRed);
		}
		else
		{
			pBtn->SetBitmap(hBitmapGray);
		}
	}
}

void CPageFour::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	m_InputValue=pApp->mVar.m_IO.ReadDIPort();
	m_OutputValue=pApp->mVar.m_IO.ReadDOPort();
	RenewObjects();
	if(m_bReceiveEnable)
		OnReceivedata();
	
	CDialogEx::OnTimer(nIDEvent);
}

void CPageFour::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(0);
	CDialogEx::OnClose();
}

void CPageFour::OnSenddata() 
{
	// TODO: Add your control notification handler code here
	float aoValue;
	CString tempstr;
//	unsigned short nChan=GetDlgItemInt(IDC_AOCHANNEL);
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	
	GetDlgItemText(IDC_AOVALUE,tempstr);
	aoValue=(float)_ttof(tempstr);
	aoValue>MAXLASERVOLTAGE ? aoValue = MAXLASERVOLTAGE:aoValue;
	pApp->mVar.m_IO.SendAOPort(m_AOChannel & 0x01,aoValue);
}

void CPageFour::OnReceivedata() 
{
	// TODO: Add your control notification handler code here
	float aiValue;
	CString tempstr;
//	unsigned short nChan=GetDlgItemInt(IDC_AICHANNEL);
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	aiValue=pApp->mVar.m_IO.ReadAIPort(m_AIChannel & 0x0f);
	tempstr.Format(_T("%0.2f"),aiValue);
	SetDlgItemText(IDC_AIVALUE,tempstr);
}

void CPageFour::OnSelchangeComboAichannel() 
{
	// TODO: Add your control notification handler code here
	m_AIChannel = m_cmbAIChannel.GetCurSel();
}

void CPageFour::OnSelchangeComboAochannel() 
{
	// TODO: Add your control notification handler code here
	m_AOChannel = m_cmbAOChannel.GetCurSel();
}

void CPageFour::OnStopreceive() 
{
	// TODO: Add your control notification handler code here
	m_bReceiveEnable = FALSE;
}

void CPageFour::OnStartreceive() 
{
	// TODO: Add your control notification handler code here
	m_bReceiveEnable = TRUE;
}
