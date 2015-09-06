#if !defined(AFX_CCDVIEW_H__58EDF1AA_CC5F_41A8_938E_F736E98A332A__INCLUDED_)
#define AFX_CCDVIEW_H__58EDF1AA_CC5F_41A8_938E_F736E98A332A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CCDView.h : header file
//

//���������SDK��HVVideoģ��ͷ�ļ�
#include "HVDAILT.h"
#include "Raw2Rgb.h"

#pragma comment(lib,"HVDAILT.lib")
#pragma comment(lib,"Raw2Rgb.lib")

//�Զ�����ϢID��
#define WM_SNAP_CHANGE		(WM_USER + 100)
/////////////////////////////////////////////////////////////////////////////
// CCCDView view

class CCCDView : public CView
{
protected:
	           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCCDView)

// Attributes
public:
	afx_msg LRESULT OnMessageStartCapture(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnMessageStopCapture(WPARAM wParam,LPARAM lParam);
private:
	HHV	m_hhv;			//������������
	
//	BOOL m_bOpen;		//��ʼ����־
//	BOOL m_bStart;		//������־
	
	BITMAPINFO *m_pBmpInfo;		//BITMAPINFO �ṹָ�룬��ʾͼ��ʱʹ��
	BYTE *m_pRawBuffer;			//�ɼ�ͼ��ԭʼ���ݻ�����
	BYTE *m_pImageBuffer;		//Bayerת���󻺳���
	char m_chBmpBuf[2048];		//BIMTAPINFO �洢��������m_pBmpInfo��ָ��˻�����

//	int *m_pPatternBuf;    //��������ģ����ԵĻ�����
//	int m_nTempTimes;       //ȡģ��Ĵ���
//	BYTE *m_pBadPixel;

//	BOOL m_bIsToGetBadPixel;
//	BOOL m_bIsToRemoveBadPixel;	
//	BOOL m_bIsToGetTemplate;
//	BOOL m_bIsUseTemplate;
	/*
	 *	Snap �ص��������û�Ҳ���Զ���Ϊȫ�ֺ����� 
	 *	�����Ϊ��ĳ�Ա����������Ϊ��̬��Ա������
	 */
	static int CALLBACK SnapThreadCallback(HV_SNAP_INFO *pInfo); 
	
//	BOOL m_bNegative;	
	//��ɫ���ұ�
	BYTE m_pLutR[256] ;
	BYTE m_pLutG[256] ;
	BYTE m_pLutB[256] ;

	CRect RecStatic;
	BOOL Initialized;
	
	afx_msg LRESULT OnSnapChange(WPARAM wParam, LPARAM lParam);
// Operations
public:
	CCCDView();
	virtual ~CCCDView();
	void SetExposureTime(int nWindWidth,long lTintUpper,long lTintLower);
	void SetMirror(BOOL tempmirror);
	void SetGain(int tempgain);
	void Savebitmap();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCCDView)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CCCDView)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCDVIEW_H__58EDF1AA_CC5F_41A8_938E_F736E98A332A__INCLUDED_)
