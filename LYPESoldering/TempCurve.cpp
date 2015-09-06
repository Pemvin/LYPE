// TempCurve.cpp : implementation file
//

#include "stdafx.h"
#include "LYPESoldering.h"
#include "TempCurve.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTempCurve

IMPLEMENT_DYNCREATE(CTempCurve, CFormView)

CTempCurve::CTempCurve()
	: CFormView(CTempCurve::IDD)
{
	//{{AFX_DATA_INIT(CTempCurve)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CTempCurve::~CTempCurve()
{
}

void CTempCurve::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTempCurve)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTempCurve, CFormView)
	//{{AFX_MSG_MAP(CTempCurve)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTempCurve diagnostics

#ifdef _DEBUG
void CTempCurve::AssertValid() const
{
	CFormView::AssertValid();
}

void CTempCurve::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTempCurve message handlers

void CTempCurve::ReNewTable() 
{
	int i;
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

//	float pt[200];
//	for(int)
//	biliner(200,200,200,pApp->mVar.tempcurve);

	CDC MemDC; //首先定义一个显示设备对象
	CBitmap MemBitmap;
	CDC *pDC=GetDC();
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	CPen LinePen(PS_SOLID,1,RGB(150,150,150));
	CRect re,re2;

	GetWindowRect(&re);
	ScreenToClient(&re);
	GetDlgItem(IDC_LineSetH)->GetWindowRect(&re2);
	ScreenToClient(&re2);

	MemDC.CreateCompatibleDC(NULL);
	int width=re.Width();
	int height=re2.top;
	MemBitmap.CreateCompatibleBitmap(pDC,width,height);
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0,0,width,height+10,RGB(234,247,172));
	CPen *pOldPen=MemDC.SelectObject(&LinePen);
	for(i=0;i<11;i++)
	{
		MemDC.MoveTo(1+2*i*width/20,0);
		MemDC.LineTo(1+2*i*width/20,height);
		MemDC.MoveTo(1+(2*i+1)*width/20,0);
		MemDC.LineTo(1+(2*i+1)*width/20,height);
		MemDC.MoveTo(1,i*height/10);
		MemDC.LineTo(width,i*height/10);
	}
	MemDC.DrawText(_T("350 (摄氏度)"),CRect(3,5,100,25),0);
	MemDC.DrawText(_T("300"),CRect(3,55,100,75),0);
	MemDC.DrawText(_T("250"),CRect(3,117,100,137),0);
	MemDC.DrawText(_T("200"),CRect(3,181,100,201),0);
	MemDC.DrawText(_T("150"),CRect(3,243,100,263),0);
	MemDC.SelectObject(&pen);
	double ht=(double)(height)/250.;
	double wh=(double)(width)/200.;	
	MemDC.MoveTo((int)(wh-0),(int)(height-ht*pApp->mVar.tempcurve[0]));
	for(i=1;i<200;i++)
	{
		MemDC.LineTo((int)((i+1)*wh),(int)(height-ht*pApp->mVar.tempcurve[i]));
	}

	pDC->BitBlt(re.left,re.top,width,height+10,&MemDC,0,0,SRCCOPY);

	MemDC.SelectObject(pOldPen);
	DeleteObject(pen);
	DeleteObject(LinePen);
	pOldPen->DeleteObject();
	ReleaseDC(pDC);
	pOldBit->DeleteObject();
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
}

void CTempCurve::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	ReNewTable();
	CFormView::OnTimer(nIDEvent);
}

void CTempCurve::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	SetTimer(0,100,NULL);
}

void CTempCurve::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	KillTimer(0);
}
