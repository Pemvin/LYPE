#if !defined(AFX_PARAMETERSETDLG_H__BA5B4595_CDA7_4430_9BB8_E98303E31527__INCLUDED_)
#define AFX_PARAMETERSETDLG_H__BA5B4595_CDA7_4430_9BB8_E98303E31527__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParameterSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParameterSetDlg dialog

class CParameterSetDlg : public CDialog
{
// Construction
public:
	CParameterSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CParameterSetDlg)
	enum { IDD = IDD_ParameterSet };
	double		m_currentlimit;
	int		m_rmanspeed;
	int		m_rdotdistance;
	int		m_rrrturnspeed;
	int		m_rspeedlimit;
	int		m_santodistance;
	double	m_sbackdistance;
	int		m_sbackspeed;
	double	m_sdotdistance;
	int		m_smandistance;
	int		m_templimit;
	double	m_xdotdistance;
	int		m_xmanspeed;
	int		m_xreturnspeed;
	int		m_xspeedlimit;

	double	m_ydotdistance;
	int		m_ymanspeed;
	int		m_yreturnspeed;
	int		m_yspeedlimit;

	double	m_zdotdistance;
	int		m_zmanspeed;
	int		m_zreturnspeed;
	int		m_zspeedlimit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParameterSetDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RefreshControls();
	// Generated message map functions
	//{{AFX_MSG(CParameterSetDlg)
	afx_msg void OnDefault();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMETERSETDLG_H__BA5B4595_CDA7_4430_9BB8_E98303E31527__INCLUDED_)
