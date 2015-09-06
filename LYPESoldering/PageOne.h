#if !defined(AFX_PAGEONE_H__EAFDF935_096F_4DB8_A208_5E7617B2B408__INCLUDED_)
#define AFX_PAGEONE_H__EAFDF935_096F_4DB8_A208_5E7617B2B408__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageOne.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageOne dialog

class CPageOne : public CDialogEx
{
// Construction
public:
	CPageOne(CWnd* pParent = NULL);   // standard constructor

	BOOL	m_DirLogic[3];
//	BOOL	m_PulsePerMm[4];
// Dialog Data
	//{{AFX_DATA(CPageOne)
	enum { IDD = IDD_PAGEONE };
	UINT	m_PulsePerMmX;
	UINT	m_PulsePerMmY;
	UINT	m_PulsePerMmZ;
	BOOL	m_MessageEnable;
	double	m_TempRatio;
	//}}AFX_DATA
	double m_ZMaxCoor;
	double m_XMaxCoor;
	double m_XMinCoor;
	double m_YMaxCoor;
	double m_YMinCoor;
	double m_ZMinCoor;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageOne)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageOne)
	afx_msg void OnDirectionlogicx();
	afx_msg void OnDirectionlogicy();
	afx_msg void OnDirectionlogicz();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	double m_CircleDelay;
	double	m_ZUpDistance;
	BOOL m_BackToOrigin;
	double m_OriginX;
	double m_OriginY;
	double m_OriginZ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEONE_H__EAFDF935_096F_4DB8_A208_5E7617B2B408__INCLUDED_)
