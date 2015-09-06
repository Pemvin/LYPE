#pragma once



// CDlgPull 窗体视图

class CDlgPull : public CFormView
{
	DECLARE_DYNCREATE(CDlgPull)

protected:
	CDlgPull();           // 动态创建所使用的受保护的构造函数
	virtual ~CDlgPull();
	double	m_current;
	int		m_pointnum;
	double	m_xaxiscoor;
	double	m_yaxiscoor;
	double	m_zaxiscoor;
	CString	m_pointname;
	double	m_startspd;
	double	m_stopspd;
	double	m_laserstartdelay;
	double  m_laserstopdelay;
	int		m_soldtemp;
	CListBox m_PointList;
	AutoParameter pastepoint;
public:
	enum { IDD = IDD_DLG_PullSold };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	virtual void OnInitialUpdate();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void RenewObjects(void);
	afx_msg LRESULT MessageRenewObjects(WPARAM wParam,LPARAM lParam);
	afx_msg void OnSelchangePointlist();
	afx_msg void OnKillfocusXcoor();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPointnew();
	afx_msg void OnBnClickedGetendpoint();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedStartpoint();
	afx_msg void OnBnClickedMiddlepoint();
	afx_msg void OnBnClickedEndpoint();
	afx_msg void OnBnClickedPointdec();
	afx_msg void OnBnClickedPointadd();
	afx_msg void OnBnClickedPointdel();
	afx_msg void OnBnClickedPointnull();
	afx_msg void OnBnClickedPointup();
	afx_msg void OnBnClickedPointdown();
	afx_msg void OnBnClickedPointcut();
	afx_msg void OnBnClickedPointcopy();
	afx_msg void OnBnClickedPointpaste();
	afx_msg void OnEnChangePointnum();
	afx_msg void OnBnClickedRenewcoordinate();
};


