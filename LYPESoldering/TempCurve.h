#if !defined(AFX_TEMPCURVE_H__7A750329_4293_43E8_8D74_A7320B9D02D4__INCLUDED_)
#define AFX_TEMPCURVE_H__7A750329_4293_43E8_8D74_A7320B9D02D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TempCurve.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTempCurve form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CTempCurve : public CFormView
{
protected:
	CTempCurve();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTempCurve)

// Form Data
public:
	//{{AFX_DATA(CTempCurve)
	enum { IDD = IDD_TEMPCURVE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void ReNewTable();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTempCurve)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTempCurve();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTempCurve)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPCURVE_H__7A750329_4293_43E8_8D74_A7320B9D02D4__INCLUDED_)
