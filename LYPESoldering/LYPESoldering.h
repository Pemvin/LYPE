
// LYPESoldering.h : LYPESoldering Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "Variable.h"
// CLYPESolderingApp:
// �йش����ʵ�֣������ LYPESoldering.cpp
//

class CLYPESolderingApp : public CWinAppEx
{
public:
	CLYPESolderingApp();

	static CVariable mVar;
	BOOL m_bShift;
// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern CLYPESolderingApp theApp;
