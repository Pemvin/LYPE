#if !defined(AFX_PAGETWO_H__2EF8F5CA_F547_415A_9BE8_180FBC55D706__INCLUDED_)
#define AFX_PAGETWO_H__2EF8F5CA_F547_415A_9BE8_180FBC55D706__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageTwo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageTwo dialog

class CPageTwo : public CDialogEx
{
// Construction
public:
	CPageTwo(CWnd* pParent = NULL);   // standard constructor

	BOOL m_HomeDirection[3];
	BOOL m_HomeZLogic[3];
	BOOL m_HomeOrgLogic[3];
	BOOL m_HomeLimitLogic[3];
// Dialog Data
	//{{AFX_DATA(CPageTwo)
	enum { IDD = IDD_PAGETWO };
	double	m_HomeVelXAcc;
	double	m_HomeVelXHigh;
	double	m_HomeVelXLow;
	double	m_HomeVelYAcc;
	double	m_HomeVelYHigh;
	double	m_HomeVelYLow;
	double	m_HomeVelZAcc;
	double	m_HomeVelZHigh;
	double	m_HomeVelZLow;
	double	m_ManualVelXAcc;
	double	m_ManualVelXDec;
	double	m_ManualVelXHigh;
	double	m_ManualVelXLow;
	double	m_ManualVelYAcc;
	double	m_ManualVelYDec;
	double	m_ManualVelYHigh;
	double	m_ManualVelYLow;
	double	m_ManualVelZAcc;
	double	m_ManualVelZDec;
	double	m_ManualVelZHigh;
	double	m_ManualVelZLow;
	double	m_AutoMaxVelX;
	double	m_AutoMaxVelY;
	double	m_AutoMaxVelZ;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageTwo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageTwo)
	virtual BOOL OnInitDialog();
	afx_msg void OnHomedirectionx();
	afx_msg void OnHomezlogicx();
	afx_msg void OnHomeorglogicx();
	afx_msg void OnHomelimitlogicx();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGETWO_H__2EF8F5CA_F547_415A_9BE8_180FBC55D706__INCLUDED_)
