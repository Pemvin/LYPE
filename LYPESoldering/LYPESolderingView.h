
// LYPESolderingView.h : CLYPESolderingView ��Ľӿ�
//

#pragma once


class CLYPESolderingView : public CView
{
protected: // �������л�����
	CLYPESolderingView();
	DECLARE_DYNCREATE(CLYPESolderingView)

// ����
public:
	CLYPESolderingDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CLYPESolderingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // LYPESolderingView.cpp �еĵ��԰汾
inline CLYPESolderingDoc* CLYPESolderingView::GetDocument() const
   { return reinterpret_cast<CLYPESolderingDoc*>(m_pDocument); }
#endif

