// PIDSet.cpp : implementation file
//

#include "stdafx.h"
#include "LYPESoldering.h"
#include "PIDSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPIDSet dialog


CPIDSet::CPIDSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPIDSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPIDSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPIDSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPIDSet)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPIDSet, CDialogEx)
	//{{AFX_MSG_MAP(CPIDSet)
	ON_EN_KILLFOCUS(IDC_KP, OnKillfocusKp)
	ON_EN_KILLFOCUS(IDC_KI, OnKillfocusKi)
	ON_EN_KILLFOCUS(IDC_KD, OnKillfocusKd)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &CPIDSet::OnBnClickedCancel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPIDSet message handlers

void CPIDSet::OnKillfocusKp() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	CString str;
	GetDlgItemText(IDC_KP,str);
	pApp->mVar.KP=_ttof(str);
}

void CPIDSet::OnKillfocusKi() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	CString str;
	GetDlgItemText(IDC_KI,str);
	pApp->mVar.KI=_ttof(str);
}

void CPIDSet::OnKillfocusKd() 
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	CString str;
	GetDlgItemText(IDC_KD,str);
	pApp->mVar.KD=_ttof(str);
}

void CPIDSet::OnCancel() 
{
	// TODO: Add extra cleanup here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	this->SetFocus();
	pApp->mVar.KP=TempP;
	pApp->mVar.KI=TempI;
	pApp->mVar.KD=TempD;

//	CDialogEx::OnCancel();
	DestroyWindow();
}

BOOL CPIDSet::OnInitDialog() 
{
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	CString tempstr;
	tempstr.Format(_T("%f"),pApp->mVar.KP);
	SetDlgItemText(IDC_KP,tempstr);
	tempstr.Format(_T("%f"),pApp->mVar.KI);
	SetDlgItemText(IDC_KI,tempstr);
	tempstr.Format(_T("%f"),pApp->mVar.KD);
	SetDlgItemText(IDC_KD,tempstr);

	TempP=pApp->mVar.KP;
	TempI=pApp->mVar.KI;
	TempD=pApp->mVar.KD;

	CRect rt;
	GetWindowRect(&rt);
	MoveWindow(100,500,rt.Width(),rt.Height());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPIDSet::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PostNcDestroy();
	delete this;
}

void CPIDSet::OnSize(UINT nType, int cx, int cy) 
{
	CDialogEx::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/*	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_View);
	if(pWnd)
	{
		pWnd->MoveWindow(CRect(0,0,cx,cy));
		vHeight=cx;
		vWidth=cy;
	}*/
}

void CPIDSet::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
