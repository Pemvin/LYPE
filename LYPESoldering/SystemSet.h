#if !defined(AFX_SYSTEMSET_H__82ABC6BB_C708_46CA_AA38_DEB3D6A9E934__INCLUDED_)
#define AFX_SYSTEMSET_H__82ABC6BB_C708_46CA_AA38_DEB3D6A9E934__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SystemSet.h : header file
//
#include "PageOne.h"
#include "PageTwo.h"
#include "PageFour.h"
/////////////////////////////////////////////////////////////////////////////
// CSystemSet dialog

class CSystemSet : public CDialogEx
{
// Construction
public:
	CSystemSet(CWnd* pParent = NULL);   // standard constructor

//	CDialogEx *pDialog[2];
	CPageOne m_pageone;
	CPageTwo m_pagetwo;
	CPageFour  m_pagefour;
	int m_CurSelTab;

	void RenewTabControl(void);
// Dialog Data
	//{{AFX_DATA(CSystemSet)
	enum { IDD = IDD_SYSTEMSET };
	CTabCtrl	m_tab;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSystemSet)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabSystemset(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnSelchangingTabSystemset(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMSET_H__82ABC6BB_C708_46CA_AA38_DEB3D6A9E934__INCLUDED_)
