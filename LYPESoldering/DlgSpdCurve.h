#pragma once


// CDlgSpdCurve �Ի���

class CDlgSpdCurve : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSpdCurve)

public:
	CDlgSpdCurve(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSpdCurve();

// �Ի�������
	enum { IDD = IDD_Dlg_SpdCurve };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ReNewTable();
	afx_msg void OnDestroy();
};
