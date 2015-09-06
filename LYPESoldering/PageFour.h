#if !defined(AFX_PAGEFOUR_H__44A9DAE2_EA70_401E_931C_5091F0FE5395__INCLUDED_)
#define AFX_PAGEFOUR_H__44A9DAE2_EA70_401E_931C_5091F0FE5395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageFour.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageFour dialog

class CPageFour : public CDialogEx
{
// Construction
public:
	CPageFour(CWnd* pParent = NULL);   // standard constructor

	HBITMAP hBitmapRed;
	HBITMAP hBitmapGray;
	unsigned short m_InputValue, m_OutputValue;
	unsigned short m_AIChannel;
	unsigned short m_AOChannel;
	BOOL	m_bReceiveEnable;
// Dialog Data
	//{{AFX_DATA(CPageFour)
	enum { IDD = IDD_PAGEFOUR };
//	CComboBox	m_cmbAOChannel;
//	CComboBox	m_cmbAIChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageFour)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	void RenewObjects(void);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageFour)
	virtual BOOL OnInitDialog();
	afx_msg void OnOut0();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnSenddata();
	afx_msg void OnReceivedata();
	afx_msg void OnSelchangeComboAichannel();
	afx_msg void OnSelchangeComboAochannel();
	afx_msg void OnStopreceive();
	afx_msg void OnStartreceive();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cmbAIChannel;
	CComboBox m_cmbAOChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEFOUR_H__44A9DAE2_EA70_401E_931C_5091F0FE5395__INCLUDED_)
