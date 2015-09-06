// DlgSpdCurve.cpp : 实现文件
//

#include "stdafx.h"
#include "LYPESoldering.h"
#include "DlgSpdCurve.h"
#include "afxdialogex.h"


// CDlgSpdCurve 对话框

IMPLEMENT_DYNAMIC(CDlgSpdCurve, CDialogEx)

CDlgSpdCurve::CDlgSpdCurve(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSpdCurve::IDD, pParent)
{

}

CDlgSpdCurve::~CDlgSpdCurve()
{
}

void CDlgSpdCurve::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSpdCurve, CDialogEx)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlgSpdCurve 消息处理程序


void CDlgSpdCurve::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	CDialogEx::PostNcDestroy();
	delete this;
}


BOOL CDlgSpdCurve::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetTimer(0,100,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgSpdCurve::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ReNewTable();
	CDialogEx::OnTimer(nIDEvent);
}

void CDlgSpdCurve::ReNewTable() 
{
	int i;
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	//	float pt[200];
	//	for(int)
	//	biliner(200,200,200,pApp->mVar.tempcurve);

	CDC MemDC; //首先定义一个显示设备对象
	CBitmap MemBitmap;
	CDC *pDC=GetDC();
	CPen pen(PS_SOLID,1,RGB(255,0,255));
	CPen LinePen(PS_SOLID,1,RGB(150,150,150));
	CRect re,re2;

	GetWindowRect(&re);
	ScreenToClient(&re);
	GetDlgItem(IDC_LineH)->GetWindowRect(&re2);
	ScreenToClient(&re2);

	MemDC.CreateCompatibleDC(NULL);
	int width=re.Width();
	int height=re2.top;
	MemBitmap.CreateCompatibleBitmap(pDC,width,height);
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0,0,width,height,RGB(234,247,172));
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
	MemDC.DrawText(_T("10 (mm/s)"),CRect(3,0,100,25),0);
	MemDC.DrawText(_T("9"),CRect(3,19,100,39),0);
	MemDC.DrawText(_T("8"),CRect(3,45,100,65),0);
	MemDC.DrawText(_T("7"),CRect(3,71,100,91),0);
	MemDC.DrawText(_T("6"),CRect(3,97,100,117),0);
	MemDC.DrawText(_T("5"),CRect(3,123,100,143),0);
	MemDC.DrawText(_T("4"),CRect(3,149,100,169),0);
	MemDC.DrawText(_T("3"),CRect(3,175,100,195),0);
	MemDC.DrawText(_T("2"),CRect(3,201,100,221),0);
	MemDC.DrawText(_T("1"),CRect(3,227,100,247),0);
	MemDC.SelectObject(&pen);
	double ht=(double)(height)/100.;
	double wh=(double)(width)/200.;	
	MemDC.MoveTo((int)(wh-0),(int)(height-ht*pApp->mVar.spdcurve[0]));
	for(i=1;i<200;i++)
	{
		MemDC.LineTo((int)((i+1)*wh),(int)(height-ht*pApp->mVar.spdcurve[i]));
	}

	pDC->BitBlt(re.left,re.top+29,width,height,&MemDC,0,0,SRCCOPY);

	MemDC.SelectObject(pOldPen);
	DeleteObject(pen);
	DeleteObject(LinePen);
	pOldPen->DeleteObject();
	ReleaseDC(pDC);
	pOldBit->DeleteObject();
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
}

void CDlgSpdCurve::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	KillTimer(0);
}
