#pragma once


// CDlgSpdCurve 对话框

class CDlgSpdCurve : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSpdCurve)

public:
	CDlgSpdCurve(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSpdCurve();

// 对话框数据
	enum { IDD = IDD_Dlg_SpdCurve };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ReNewTable();
	afx_msg void OnDestroy();
};
