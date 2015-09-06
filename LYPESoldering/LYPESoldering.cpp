
// LYPESoldering.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "LYPESoldering.h"
#include "LYPESolderingDoc.h"
#include "LYPESolderingView.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLYPESolderingApp

BEGIN_MESSAGE_MAP(CLYPESolderingApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CLYPESolderingApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CLYPESolderingApp ����

CLYPESolderingApp::CLYPESolderingApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("LYPESoldering.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CLYPESolderingApp ����

CLYPESolderingApp theApp;


// CLYPESolderingApp ��ʼ��
CVariable CLYPESolderingApp::mVar;

BOOL CLYPESolderingApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)
	mVar.ParametersLoad_Total();

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CLYPESolderingDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CLYPESolderingView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
//	SetDialogBkColor(RGB(231,209,143),RGB(0,0,0));
	return TRUE;
}

int CLYPESolderingApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CLYPESolderingApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CLYPESolderingApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CLYPESolderingApp �Զ������/���淽��

void CLYPESolderingApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CLYPESolderingApp::LoadCustomState()
{
}

void CLYPESolderingApp::SaveCustomState()
{
}

// CLYPESolderingApp ��Ϣ�������





BOOL CLYPESolderingApp::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	CMainFrame *pFrm=(CMainFrame *)(AfxGetApp()->m_pMainWnd);
	BOOL bReturn = TRUE;

	if( pMsg->message == WM_KEYDOWN )
	{
		switch(pMsg-> wParam)
		{
			case VK_F2:
				::PostMessage(pFrm->pDlgPull->m_hWnd,IDC_L_UPDATE_MESSAGE,0,0);
				::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_F2_MESSAGE,0,0);
				return bReturn;
			case VK_F3:
				::PostMessage(pFrm->pDlgPull->m_hWnd,IDC_L_UPDATE_MESSAGE,0,0);
				::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_F3_MESSAGE,0,0);
				return bReturn;
			case VK_ESCAPE:
				::PostMessage(pFrm->pDlgPull->m_hWnd,IDC_L_UPDATE_MESSAGE,0,0);
				::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_ESC_MESSAGE,0,0);
				return bReturn;
		}
	}
	else
	if( pMsg->message == WM_KEYUP )
	{
		switch(pMsg-> wParam)
		{
			case VK_F2:
				return bReturn;
			case VK_F3:
				return bReturn;
			case VK_ESCAPE:
				return bReturn;
		}
	}

	if(!mVar.m_bKeyMoveEnable)
		return CWinAppEx::PreTranslateMessage(pMsg);
	
	if( pMsg->message == WM_KEYDOWN )
	{
		switch(pMsg-> wParam)
		{
			case VK_LEFT:
				if(m_bShift)
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnDown_MESSAGE,3,0);
				else
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnDown_MESSAGE,0,0);
//				dlg.XForwardLBottonDown(3,0):dlg.XForwardLBottonDown(0,0);
				break;
			case VK_RIGHT:
				if(m_bShift)
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnDown_MESSAGE,3,1);
				else
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnDown_MESSAGE,0,1);
//				m_bShift?dlg.XForwardLBottonDown(3,1):dlg.XForwardLBottonDown(0,1);
				break;
			case VK_UP:
				if(m_bShift)
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnDown_MESSAGE,2,1);
				else
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnDown_MESSAGE,1,1);
//				m_bShift?dlg.XForwardLBottonDown(2,1):dlg.XForwardLBottonDown(1,1);
				break;
			case VK_DOWN:
				if(m_bShift)
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnDown_MESSAGE,2,0);
				else
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnDown_MESSAGE,1,0);
//				m_bShift?dlg.XForwardLBottonDown(2,0):dlg.XForwardLBottonDown(1,0);
				break;
			case VK_SHIFT:
				m_bShift=TRUE;
				break;
			default:
				bReturn = CWinAppEx::PreTranslateMessage(pMsg);
				break;
		}
	}
	else
	if( pMsg->message == WM_KEYUP )
	{
		switch(pMsg-> wParam)
		{
			case VK_LEFT:
				if(m_bShift)
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnUp_MESSAGE,3,0);
				else
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnUp_MESSAGE,0,0);
//				m_bShift?dlg.XForwardLBottonUp(3,0):dlg.XForwardLBottonUp(0,0);
				break;
			case VK_RIGHT:
				if(m_bShift)
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnUp_MESSAGE,3,1);
				else
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnUp_MESSAGE,0,1);
//				m_bShift?dlg.XForwardLBottonUp(3,1):dlg.XForwardLBottonUp(0,1);
				break;
			case VK_UP:
				if(m_bShift)
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnUp_MESSAGE,2,1);
				else
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnUp_MESSAGE,1,1);
//				m_bShift?dlg.XForwardLBottonUp(2,1):dlg.XForwardLBottonUp(1,1);
				break;
			case VK_DOWN:
				if(m_bShift)
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnUp_MESSAGE,2,0);
				else
					::PostMessage(pFrm->pDlgRight->m_hWnd,IDC_R_LBtnUp_MESSAGE,1,0);
//				m_bShift?dlg.XForwardLBottonUp(2,0):dlg.XForwardLBottonUp(1,0);
				break;
			case VK_SHIFT:
				m_bShift=FALSE;
				break;
			default:
				bReturn = CWinAppEx::PreTranslateMessage(pMsg);
				break;
		}
	}
	else
		bReturn = CWinAppEx::PreTranslateMessage(pMsg);
	return bReturn;
	
//	return CWinAppEx::PreTranslateMessage(pMsg);
}
