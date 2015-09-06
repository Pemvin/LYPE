
// LYPESolderingDoc.cpp : CLYPESolderingDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "LYPESoldering.h"
#endif
#include "MainFrm.h"
#include "LYPESolderingDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLYPESolderingDoc

IMPLEMENT_DYNCREATE(CLYPESolderingDoc, CDocument)

BEGIN_MESSAGE_MAP(CLYPESolderingDoc, CDocument)
	ON_COMMAND(ID_FILE_NEW, &CLYPESolderingDoc::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CLYPESolderingDoc::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CLYPESolderingDoc::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CLYPESolderingDoc::OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE_SYSTEM, &CLYPESolderingDoc::OnFileSaveSystem)
END_MESSAGE_MAP()


// CLYPESolderingDoc ����/����

CLYPESolderingDoc::CLYPESolderingDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CLYPESolderingDoc::~CLYPESolderingDoc()
{
}

BOOL CLYPESolderingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CLYPESolderingDoc ���л�

void CLYPESolderingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CLYPESolderingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CLYPESolderingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CLYPESolderingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CLYPESolderingDoc ���

#ifdef _DEBUG
void CLYPESolderingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLYPESolderingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLYPESolderingDoc ����


void CLYPESolderingDoc::OnFileNew()
{
	// TODO: �ڴ���������������
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm=(CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pApp->mVar.totalpointnumber=2;
	pApp->mVar.currentpointnumber=0;
	int i;
	for(i=0;i<pApp->mVar.totalpointnumber;i++)
	{
		pApp->mVar.m_autopara[i].AutoCoor.AxisXCoor=0.0;
		pApp->mVar.m_autopara[i].AutoCoor.AxisYCoor=0.0;
		pApp->mVar.m_autopara[i].AutoCoor.AxisZCoor=0.0;
		pApp->mVar.m_autopara[i].PointName = "";
		
		pApp->mVar.m_autopara[i].Current = 0;
		pApp->mVar.m_autopara[i].StartSpd = 0;
		pApp->mVar.m_autopara[i].StopSpd = 0;
		pApp->mVar.m_autopara[i].LaserStartDelay = 0;
		pApp->mVar.m_autopara[i].LaserStopDelay = 0;
		pApp->mVar.m_autopara[i].AutoTemp = 0;
	}
	pApp->mVar.m_autopara[0].PointType = 0;
	pApp->mVar.m_autopara[1].PointType = 2;
	pApp->mVar.m_sProjectFileName="";
	pApp->mVar.m_sProjectPathName="";

	::PostMessage(pFrm->pDlgPull->m_hWnd,IDC_L_UPDATE_MESSAGE,0,0);
}


void CLYPESolderingDoc::OnFileOpen()
{
	// TODO: �ڴ���������������
	CString AnStrA,strPathName,strFileName;
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm=(CMainFrame *)(AfxGetApp()->m_pMainWnd);

	CFileDialog m_bFileOpen(TRUE);
	m_bFileOpen.m_ofn.lpstrFilter = _T("(*.ini)\0*.ini\0\0");
	if(pApp->mVar.m_sProjectPathName==_T(""))
		m_bFileOpen.m_ofn.lpstrInitialDir = pApp->mVar.m_IniPathName;
	else
		m_bFileOpen.m_ofn.lpstrInitialDir = pApp->mVar.m_sProjectPathName;
	m_bFileOpen.m_ofn.lpstrDefExt=_T("ini");
	if(IDOK==m_bFileOpen.DoModal())
	{
		strPathName = m_bFileOpen.GetPathName();
		AnStrA = m_bFileOpen.GetFileExt();
		if(AnStrA.CompareNoCase(_T("ini")))
		{
			AfxMessageBox(_T("���س���δ֪�ĸ�ʽ���ļ���ʽ����"));
            return;
		}
		strFileName=m_bFileOpen.GetFileName();
		strPathName=m_bFileOpen.GetPathName();
		pApp->mVar.m_sProjectFileName=strFileName;
		pApp->mVar.m_sProjectPathName=strPathName;

		pApp->mVar.ProjectLoad(strPathName,strFileName);
		if(pApp->mVar.totalpointnumber<=0)
		{
			AfxMessageBox(_T("���س����ļ����ݴ���!"));
            return;
		}
		pApp->mVar.currentpointnumber=0;
		::PostMessage(pFrm->pDlgPull->m_hWnd,IDC_L_UPDATE_MESSAGE,0,0);
		pFrm->m_wndStatusBar.SetPaneText(0,_T("�ļ��Ѵ�"));
		pFrm->SetWindowText(strFileName);
	}
}


void CLYPESolderingDoc::OnFileSave()
{
	// TODO: �ڴ���������������
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm=(CMainFrame *)(AfxGetApp()->m_pMainWnd);

	SetFocus(pFrm->pDlgPull->m_hWnd);
	if(pApp->mVar.m_sProjectFileName!=_T("") && pApp->mVar.m_sProjectPathName!=_T(""))
	{
		pApp->mVar.ProjectSave(pApp->mVar.m_sProjectPathName,pApp->mVar.m_sProjectFileName);
		pFrm->m_wndStatusBar.SetPaneText(0,_T("�ļ��ѱ���"));
	}
	else
	{
		OnFileSaveAs();
	}
}


void CLYPESolderingDoc::OnFileSaveAs()
{
	// TODO: �ڴ���������������
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm=(CMainFrame *)(AfxGetApp()->m_pMainWnd);

	CFileDialog m_bFileSave(FALSE);
	m_bFileSave.m_ofn.lpstrFilter=_T("(*.ini)\0*.ini\0\0");
	m_bFileSave.m_ofn.lpstrInitialDir = pApp->mVar.m_IniPathName;
	m_bFileSave.m_ofn.lpstrDefExt=_T("ini");
	if(IDOK==m_bFileSave.DoModal())
	{
		pApp->mVar.m_sProjectFileName=m_bFileSave.GetFileName();
		pApp->mVar.m_sProjectPathName=m_bFileSave.GetPathName();
		pApp->mVar.ProjectSave(pApp->mVar.m_sProjectPathName,pApp->mVar.m_sProjectFileName);
	}
	pFrm->m_wndStatusBar.SetPaneText(0,_T("�ļ������"));
	pFrm->SetWindowText(pApp->mVar.m_sProjectFileName);
}


void CLYPESolderingDoc::OnFileSaveSystem()
{
	// TODO: �ڴ���������������
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	pApp->mVar.ParametersSave_Total();
}
