
// MainFrm.h : CMainFrame ��Ľӿ�
//
#include "MiddleSplitter.h"
#include "DlgRight.h"
//#include "DlgLeft.h"
#include "CCDView.h"
#include "DlgPull.h"

//class CDlgLeft;
class CDlgRight;
class CCCDView;
class CDlgPull;
#pragma once

class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
protected:
//	CSplitterWnd m_wndSplitter;
public:
	BOOL m_bShift;
	CDlgPull		*pDlgPull;
	CDlgRight		*pDlgRight;
	CCCDView		*pDlgCCDView;
	CMFCStatusBar     m_wndStatusBar;
// ����
public:

// ��д
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
//	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

	CMiddleSplitter m_ownSplitterWnd;
	CMiddleSplitter	m_defSplitterWnd;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSetLasercurve();
	afx_msg void OnSetSystem();
	afx_msg void OnSetSilkdetect();
	afx_msg void OnSetCcd();
	afx_msg void OnAppHelp();
	afx_msg void OnAppSpdcurve();
	afx_msg void OnSetPid();
};


