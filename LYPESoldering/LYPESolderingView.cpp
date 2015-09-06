
// LYPESolderingView.cpp : CLYPESolderingView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CLYPESolderingView ����/����

CLYPESolderingView::CLYPESolderingView()
{
	// TODO: �ڴ˴���ӹ������

}

CLYPESolderingView::~CLYPESolderingView()
{
}

BOOL CLYPESolderingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CLYPESolderingView ����

void CLYPESolderingView::OnDraw(CDC* /*pDC*/)
{
	CLYPESolderingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CLYPESolderingView ���

#ifdef _DEBUG
void CLYPESolderingView::AssertValid() const
{
	CView::AssertValid();
}

void CLYPESolderingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLYPESolderingDoc* CLYPESolderingView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLYPESolderingDoc)));
	return (CLYPESolderingDoc*)m_pDocument;
}
#endif //_DEBUG


// CLYPESolderingView ��Ϣ�������
