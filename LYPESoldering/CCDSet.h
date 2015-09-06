#include "afxcmn.h"
#if !defined(AFX_CCDSET_H__51894620_A63F_46F8_A596_E2F8E66F5461__INCLUDED_)
#define AFX_CCDSET_H__51894620_A63F_46F8_A596_E2F8E66F5461__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CCDSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCCDSet dialog

class CCCDSet : public CDialogEx
{
// Construction
public:
	CCCDSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCCDSet)
	enum { IDD = IDD_CCDSET };
	//CSliderCtrl	m_SLDLight;
	BOOL	m_bVMirrorEnable;
	int		m_CrossX;
	int		m_CrossY;
	int		m_Exposure;
	int		m_Gain;
	int		m_Light;
	//}}AFX_DATA
	BOOL	TempVMirrorEnable;
	int		TempCrossX;
	int		TempCrossY;
	int		TempExposure;
	int		TempGain;
	int		TempLight;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCCDSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCCDSet)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnChkVmirror();
	afx_msg void OnKillfocusExposure();
	afx_msg void OnKillfocusGain();
	afx_msg void OnSavebitmap();
	afx_msg void OnKillfocusCrossx();
	afx_msg void OnKillfocusCrossy();
	afx_msg void OnCustomdrawSLDLight(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusLight();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_SLDLight;
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCDSET_H__51894620_A63F_46F8_A596_E2F8E66F5461__INCLUDED_)
