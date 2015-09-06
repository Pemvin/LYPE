#if !defined(AFX_DLGRIGHT_H__D9199967_5101_463F_8893_133CCE091286__INCLUDED_)
#define AFX_DLGRIGHT_H__D9199967_5101_463F_8893_133CCE091286__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRight.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CDlgRight form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDlgRight : public CFormView
{
protected:
	
	DECLARE_DYNCREATE(CDlgRight)

// Form Data
public:
	//{{AFX_DATA(CDlgRight)
	enum { IDD = IDD_DLG_RIGHT };
	double	m_dptpdistance;
	double	m_SetCurrent;
	double	m_SetTime;
	double	m_SetTemp;
	double	m_RealCurrent;
	double	m_RealTemp;
	double	m_RealTime;
	int		m_TotalOperatingTimes;
	int		m_TotalOperatingCounts;
	//}}AFX_DATA
	BOOL	m_bPause;
// Attributes
public:
	HBITMAP hBitmapRed;
	HBITMAP hBitmapGray;
//	int RealPos[4];
//	int AxisState[4];
//	int NEGLIMIT[4];
//	int ORGLIMIT[4];
//	int POSLIMIT[4];
// Operations
public:
	void XForwardLBottonDown(short AxisNumber,short AxisDirection);
	void XForwardLBottonUp(short AxisNumber,short AxisDirection);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRight)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CDlgRight();           // protected constructor used by dynamic creation
	virtual ~CDlgRight();

	static UINT _cdecl Thread_LaserTime(LPVOID lparam);
	static UINT _cdecl Thread_LaserTemp(LPVOID lparam);
	static UINT _cdecl Thread_TempSample(LPVOID lparam);
	static UINT _cdecl Thread_FootSwitch(LPVOID lparam);
	static UINT _cdecl Thread_Operating(LPVOID lparam);
	static UINT _cdecl Thread_Locating(LPVOID lparam);
	static UINT _cdecl Thread_ZUpLocating(LPVOID lparam);
	static UINT _cdecl Thread_XYLocating(LPVOID lparam);
	static UINT _cdecl Thread_ToOrigin(LPVOID lparam);
	static UINT _cdecl Thread_LaserContinue(LPVOID lparam);
	static UINT _cdecl Thread_ManualMoveTo(LPVOID lparam);
protected:
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDlgRight)
	afx_msg void OnTimestozero();
	afx_msg void OnObjectstozero();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnServoState();
	afx_msg void OnChkptp();
	afx_msg void OnManualMoveTo();
	afx_msg void OnHome();
	afx_msg void OnStop();
	afx_msg void OnChangePTPDistance();
	afx_msg void OnChkkeymove();
	afx_msg void OnStart();
	afx_msg void OnFootswitch();
	afx_msg void OnSimulation();
	afx_msg void OnSinglepoint();
	afx_msg void OnCircleoperate();
	afx_msg void OnPause();
	afx_msg void OnLasertest();
	afx_msg void OnRenewCoordinate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	afx_msg LRESULT OnMessageLBtnDown(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnMessageLBtnUp(WPARAM wParam,LPARAM lParam);

	afx_msg LRESULT OnMessageStart(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnMessageStop(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnMessagePause(WPARAM wParam,LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedToorigin();
	afx_msg void OnBnClickedCurrentmode();
	afx_msg void OnBnClickedTempmode();
};

/////////////////////////////////////////////////////////////////////////////
double PID_Regulate_CH1(double ref,double feedback);
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_DLGRIGHT_H__D9199967_5101_463F_8893_133CCE091286__INCLUDED_)
