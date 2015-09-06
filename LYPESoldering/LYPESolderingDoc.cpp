
// LYPESolderingDoc.cpp : CLYPESolderingDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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


// CLYPESolderingDoc 构造/析构

CLYPESolderingDoc::CLYPESolderingDoc()
{
	// TODO: 在此添加一次性构造代码

}

CLYPESolderingDoc::~CLYPESolderingDoc()
{
}

BOOL CLYPESolderingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CLYPESolderingDoc 序列化

void CLYPESolderingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CLYPESolderingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CLYPESolderingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// CLYPESolderingDoc 诊断

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


// CLYPESolderingDoc 命令


void CLYPESolderingDoc::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
			AfxMessageBox(_T("加载出错，未知的格式或文件格式出错"));
            return;
		}
		strFileName=m_bFileOpen.GetFileName();
		strPathName=m_bFileOpen.GetPathName();
		pApp->mVar.m_sProjectFileName=strFileName;
		pApp->mVar.m_sProjectPathName=strPathName;

		pApp->mVar.ProjectLoad(strPathName,strFileName);
		if(pApp->mVar.totalpointnumber<=0)
		{
			AfxMessageBox(_T("加载出错，文件数据错误!"));
            return;
		}
		pApp->mVar.currentpointnumber=0;
		::PostMessage(pFrm->pDlgPull->m_hWnd,IDC_L_UPDATE_MESSAGE,0,0);
		pFrm->m_wndStatusBar.SetPaneText(0,_T("文件已打开"));
		pFrm->SetWindowText(strFileName);
	}
}


void CLYPESolderingDoc::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	CMainFrame *pFrm=(CMainFrame *)(AfxGetApp()->m_pMainWnd);

	SetFocus(pFrm->pDlgPull->m_hWnd);
	if(pApp->mVar.m_sProjectFileName!=_T("") && pApp->mVar.m_sProjectPathName!=_T(""))
	{
		pApp->mVar.ProjectSave(pApp->mVar.m_sProjectPathName,pApp->mVar.m_sProjectFileName);
		pFrm->m_wndStatusBar.SetPaneText(0,_T("文件已保存"));
	}
	else
	{
		OnFileSaveAs();
	}
}


void CLYPESolderingDoc::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
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
	pFrm->m_wndStatusBar.SetPaneText(0,_T("文件已另存"));
	pFrm->SetWindowText(pApp->mVar.m_sProjectFileName);
}


void CLYPESolderingDoc::OnFileSaveSystem()
{
	// TODO: 在此添加命令处理程序代码
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	pApp->mVar.ParametersSave_Total();
}
