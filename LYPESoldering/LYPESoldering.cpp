
// LYPESoldering.cpp : 定义应用程序的类行为。
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
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CLYPESolderingApp 构造

CLYPESolderingApp::CLYPESolderingApp()
{
	m_bHiColorIcons = TRUE;

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("LYPESoldering.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CLYPESolderingApp 对象

CLYPESolderingApp theApp;


// CLYPESolderingApp 初始化
CVariable CLYPESolderingApp::mVar;

BOOL CLYPESolderingApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)
	mVar.ParametersLoad_Total();

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CLYPESolderingDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CLYPESolderingView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
//	SetDialogBkColor(RGB(231,209,143),RGB(0,0,0));
	return TRUE;
}

int CLYPESolderingApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CLYPESolderingApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

// 用于运行对话框的应用程序命令
void CLYPESolderingApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CLYPESolderingApp 自定义加载/保存方法

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

// CLYPESolderingApp 消息处理程序





BOOL CLYPESolderingApp::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
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
