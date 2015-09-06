#if !defined(AFX_PIDSET_H__A8471A8A_EA93_4EDA_8F4A_4B3F54173438__INCLUDED_)
#define AFX_PIDSET_H__A8471A8A_EA93_4EDA_8F4A_4B3F54173438__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PIDSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPIDSet dialog

class CPIDSet : public CDialogEx
{
// Construction
public:
	CPIDSet(CWnd* pParent = NULL);   // standard constructor
	double TempP;
	double TempI;
	double TempD;

// Dialog Data
	//{{AFX_DATA(CPIDSet)
	enum { IDD = IDD_PIDSET };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPIDSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CPIDSet)
	afx_msg void OnKillfocusKp();
	afx_msg void OnKillfocusKi();
	afx_msg void OnKillfocusKd();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIDSET_H__A8471A8A_EA93_4EDA_8F4A_4B3F54173438__INCLUDED_)
