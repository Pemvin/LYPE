
// LYPESolderingView.cpp : CLYPESolderingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "LYPESoldering.h"
#endif
#include "MainFrm.h"
#include "LYPESolderingDoc.h"
#include "LYPESolderingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLYPESolderingView

IMPLEMENT_DYNCREATE(CLYPESolderingView, CView)

BEGIN_MESSAGE_MAP(CLYPESolderingView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CLYPESolderingView 构造/析构

CLYPESolderingView::CLYPESolderingView()
{
	// TODO: 在此处添加构造代码

}

CLYPESolderingView::~CLYPESolderingView()
{
}

BOOL CLYPESolderingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLYPESolderingView 绘制

void CLYPESolderingView::OnDraw(CDC* /*pDC*/)
{
	CLYPESolderingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CLYPESolderingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLYPESolderingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLYPESolderingView 诊断

#ifdef _DEBUG
void CLYPESolderingView::AssertValid() const
{
	CView::AssertValid();
}

void CLYPESolderingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLYPESolderingDoc* CLYPESolderingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLYPESolderingDoc)));
	return (CLYPESolderingDoc*)m_pDocument;
}
#endif //_DEBUG


// CLYPESolderingView 消息处理程序
