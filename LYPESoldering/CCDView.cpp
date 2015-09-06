// CCDView.cpp : implementation file
//

#include "stdafx.h"
#include "LYPESoldering.h"
#include "CCDView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//定义自己的0
#define  MY_ZERO 0.000000001

//const
const int DeviceNum = 1;
const HV_RESOLUTION Resolution = RES_MODE1;
const HV_SNAP_MODE SnapMode = CONTINUATION;
const HV_BAYER_LAYOUT Layout = BAYER_GR; //GV400Ux(BAYER_BG) 
const HV_BAYER_CONVERT_TYPE ConvertType = BAYER2RGB_NEIGHBOUR;
const HV_SNAP_SPEED SnapSpeed = NORMAL_SPEED;
const long Gain = 9;
const long ExposureTint_Upper = 5;
const long ExposureTint_Lower = 1000;

const long ShutterDelay = 0;
const long ADCLevel = ADC_LEVEL2;
const int XStart = 0;
const int YStart = 0;
const int width = PICTUREWIDTH;
const int height = PICTUREHEIGHT;
/////////////////////////////////////////////////////////////////////////////
// CCCDView

IMPLEMENT_DYNCREATE(CCCDView, CView)

BEGIN_MESSAGE_MAP(CCCDView, CView)
	//{{AFX_MSG_MAP(CCCDView)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_SNAP_CHANGE, OnSnapChange)
	//}}AFX_MSG_MAP
	ON_MESSAGE(IDC_STARTCAPTURE_MESSAGE,OnMessageStartCapture)
	ON_MESSAGE(IDC_STOPCAPTURE_MESSAGE,OnMessageStopCapture)
END_MESSAGE_MAP()

CCCDView::CCCDView()
{
	/*
	 *	初始化所有成员变量，同时打开数字摄像机
	 */
	HVSTATUS status = STATUS_OK;
	Initialized = FALSE;

	m_pBmpInfo		= NULL;
	m_pRawBuffer	= NULL;
	m_pImageBuffer	= NULL;

	for(int i=0;i<256;i++)
	{
		m_pLutR[i] = i;
		m_pLutG[i] = i;
		m_pLutB[i] = i;
	}

	//	打开数字摄像机 1
	status = BeginHVDevice(1,&m_hhv);
	//	检验函数执行状态，如果失败，则返回错误状态消息框
	if (!HV_SUCCESS(status)) 
	{
		AfxMessageBox(_T("相机无法找到，初始化失败！"));
		Initialized = FALSE;
	}
	else
	{
		Initialized = TRUE;
	}
//	HV_VERIFY(status);
}

CCCDView::~CCCDView()
{	
//	if(m_pPatternBuf)
//		delete[] m_pPatternBuf;
//	if(m_pBadPixel)
//		delete[] m_pBadPixel;
}

/////////////////////////////////////////////////////////////////////////////
// CCCDView drawing

void CCCDView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CCCDView diagnostics

#ifdef _DEBUG
void CCCDView::AssertValid() const
{
	CView::AssertValid();
}

void CCCDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCCDView message handlers

BOOL CCCDView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CCCDView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	pApp->mVar.m_IO.SendAOPort(0x01,(float)(pApp->mVar.LIGHT*MAXLASERVOLTAGE/100.));

	GetWindowRect(&RecStatic);
	// TODO: Add your specialized code here and/or call the base class
	/*
		*	初始化数字摄像机硬件状态，用户也可以在其他位置初始化数字摄像机，
		*	但应保证数字摄像机已经打开，建议用户在应用程序初始化时，
		*	同时初始化数字摄像机硬件。
	*/
	
	//	设置数字摄像机分辨率
	if (!Initialized)
		return;
	HVSetResolution(m_hhv, Resolution);		
	
	//	采集模式，包括 CONTINUATION(连续)、TRIGGER(外触发)
	HVSetSnapMode(m_hhv, SnapMode);
	
	//  设置各个分量的增益
	for (int i = 0; i < 4; i++)
	{
		HVAGCControl(m_hhv, RED_CHANNEL + i, pApp->mVar.GAIN);
	}

	HVSetSnapSpeed( m_hhv, HIGH_SPEED);
	
	//	设置曝光时间
	SetExposureTime(width,pApp->mVar.EXPOSURE,ExposureTint_Lower);	
	
	//  设置ADC的级别
	HVADCControl(m_hhv, ADC_BITS, ADCLevel);
	
//	HVEnableVideoMirror(m_hhv,VERT_DIR,TRUE);
	/*
	*	视频输出窗口，即视频输出范围，输出窗口取值范围必须在输入窗口范围以内，
	*  视频窗口左上角X坐标和窗口宽度应为4的倍数，左上角Y坐标和窗口高度应为2的倍数
	*	输出窗口的起始位置一般设置为(0, 0)即可。
	*/
	HVSetOutputWindow(m_hhv, XStart, YStart, width, height);
	
	//	m_pBmpInfo即指向m_chBmpBuf缓冲区，用户可以自己分配BTIMAPINFO缓冲区	
	m_pBmpInfo								= (BITMAPINFO *)m_chBmpBuf;
	//	初始化BITMAPINFO 结构，此结构在保存bmp文件、显示采集图像时使用
	m_pBmpInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	//	图像宽度，一般为输出窗口宽度
	m_pBmpInfo->bmiHeader.biWidth			= width;
	//	图像宽度，一般为输出窗口高度
	m_pBmpInfo->bmiHeader.biHeight			= height;
	
	/*
	*	以下设置一般相同，
	*	对于低于8位的位图，还应设置相应的位图调色板
	*/
	m_pBmpInfo->bmiHeader.biPlanes			= 1;
	m_pBmpInfo->bmiHeader.biBitCount		= 24;
	m_pBmpInfo->bmiHeader.biCompression		= BI_RGB;
	m_pBmpInfo->bmiHeader.biSizeImage		= 0;
	m_pBmpInfo->bmiHeader.biXPelsPerMeter	= 0;
	m_pBmpInfo->bmiHeader.biYPelsPerMeter	= 0;
	m_pBmpInfo->bmiHeader.biClrUsed			= 0;
	m_pBmpInfo->bmiHeader.biClrImportant	= 0;
	
	/*
	*	分配原始图像缓冲区，一般用来存储采集图像原始数据
	*  一般图像缓冲区大小由输出窗口大小和视频格式确定。
	*/
	m_pRawBuffer = new BYTE[width * height];
	ASSERT(m_pRawBuffer);

	/*
	分配Bayer转换后图像数据缓冲
	*/
	m_pImageBuffer = new BYTE[width * height * 3];
	ASSERT(m_pImageBuffer);

	HVSTATUS status = STATUS_OK;
	/*
	 *	初始化数字摄像机采集图像到内存的控制，
	 *	指定回调函数SnapThreadCallback和用户参数m_hWnd
	 */
	status = HVOpenSnap(m_hhv, SnapThreadCallback, m_hWnd);					
//	HV_VERIFY(status);
	if (!HV_SUCCESS(status)) 
	{
		AfxMessageBox(_T("CCD打开失败!"));
	}

	BYTE *ppBuf[1];
	ppBuf[0] = m_pRawBuffer;
	status = HVStartSnap(m_hhv, ppBuf,1);
//	HV_VERIFY(status);
	if (!HV_SUCCESS(status)) 
	{
		AfxMessageBox(_T("开始图像采集失败!"));
	}
}

int CALLBACK CCCDView::SnapThreadCallback(HV_SNAP_INFO *pInfo)
{
	HWND hwnd = (HWND)(pInfo->pParam);
	
	/*
	 *	发送自定义消息WM_SNAP_EX_CHANGE到主窗口，	
	 *	同时传入当前可以处理的图像序号
	 *	注意：用SendMessage发送消息，必须等待消息处理完毕后，才能退出整个SendMessage函数
	 */
	::SendMessage(hwnd, WM_SNAP_CHANGE, 0, 0);

	return 1;
}

/*
	函数:
		SetExposureTime
	输入参数:
		int nWindWidth			当前图像宽度		
		int lTintUpper			曝光时间的分子，shutter的取值
		int lTintLower			曝光时间的分母，与shutter的单位相关
								（ms:1000；s:1）
	输出参数:
		无						
	说明:
		设置曝光时间（其他的参数如摄像机时钟频率，消隐值都取默认值）
 */
void CCCDView::SetExposureTime(int nWindWidth,long lTintUpper,long lTintLower)
{
	if (!Initialized)
		return;
	int size = sizeof(HVTYPE);
	HVTYPE type;
	HVGetDeviceInfo(m_hhv,DESC_DEVICE_TYPE, &type, &size);	
	
	//请参考曝光系数转换公式
	long lClockFreq; 
	int nOutputWid;
	double dExposure = 0.0;
	double dTint = max((double)lTintUpper/(double)lTintLower,MY_ZERO);
	if (type == GV400UMTYPE || type == GV400UCTYPE)
	{
		long rate = 0;
		switch(Resolution)
		{
		case RES_MODE0:
			rate = 1;
			break;
		case RES_MODE1:
			rate = 2;
			break;
		default:
			return;
		}
		nOutputWid = nWindWidth*rate;
		lClockFreq = 26600000; 
		long lTb = 0x5e;
		if (dTint* lClockFreq <= ((double)nOutputWid + lTb - 255))
		{
			dExposure = 1;
		}
		dExposure = (dTint* lClockFreq - ((double)nOutputWid + lTb - 255))/((double)nOutputWid + lTb);
		if (dExposure > 32767) 
			dExposure = 32767;
	}
	else
	{
		nOutputWid = nWindWidth;
		lClockFreq = 24000000;
		if(type == HV1300UCTYPE || type == HV1301UCTYPE)	
		{
			long lTb = 0;
			dExposure = (dTint* lClockFreq + 180.0)/((double)nOutputWid + 244.0 + lTb);
		}
		else
		{		
			long lTb = 0;
			dExposure = (dTint* lClockFreq + 180.0)/((double)nOutputWid + 305.0 + lTb) + 1 ;
		}
		
		if (dExposure > 16383) 
			dExposure = 16383;
	}

	HVAECControl(m_hhv, AEC_EXPOSURE_TIME, (long)dExposure);
	
}

LRESULT CCCDView::OnSnapChange(WPARAM wParam, LPARAM lParam)
{
	HVSTATUS status = STATUS_OK;

	CDC *pDC			= GetDC();//pView->GetDC();		//得到VIEW的DC
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	int i;
	
    //同时将原始数据进行上下翻转
	ConvertBayer2Rgb(m_pImageBuffer,m_pRawBuffer,width,height,ConvertType,m_pLutR,m_pLutG,m_pLutB,true,Layout);
	for(i=0;i<width;i++)
	{
		*(m_pImageBuffer+(pApp->mVar.CROSSY*width+i)*3+0)=0;
		*(m_pImageBuffer+(pApp->mVar.CROSSY*width+i)*3+1)=255;
		*(m_pImageBuffer+(pApp->mVar.CROSSY*width+i)*3+2)=0;
	}

	for(i=0;i<height;i++)
	{
		*(m_pImageBuffer+pApp->mVar.CROSSX*3+width*3*i+0)=0;
		*(m_pImageBuffer+pApp->mVar.CROSSX*3+width*3*i+1)=255;
		*(m_pImageBuffer+pApp->mVar.CROSSX*3+width*3*i+2)=0;
	}
	SetStretchBltMode(pDC->GetSafeHdc(),COLORONCOLOR);

//	pApp->mVar.m_pImgBuffer=m_pImageBuffer;
//	pApp->mVar.m_pImgInfo=m_pBmpInfo;
	//在视图客户区显示图像
	StretchDIBits(pDC->GetSafeHdc(),
					0,						
					0,
					width,					//显示窗口宽度
					height,					//显示窗口高度
					0,
					0,
					width,					//图像宽度
					height,					//图像高度
					m_pImageBuffer,			//图像缓冲区
					m_pBmpInfo,				//BMP图像描述信息
					DIB_RGB_COLORS,
					SRCCOPY
					);
	if (pApp->mVar.m_bOperating)
	{
		DWORD dwTime = GetTickCount();
		dwTime = dwTime - pApp->mVar.StartTime;
		pApp->mVar.CostTime = (double)dwTime / (double)1000;
		CString szTime;
		szTime.Format(_T("Time:%0.3f"), pApp->mVar.CostTime);
		pDC->TextOut(10, 10, szTime);
	}
	ReleaseDC(pDC);
	
	return 1;
}

void CCCDView::OnDestroy() 
{
	//	停止采集图像到内存，可以再次调用HVStartSnapEx启动数字摄像机采集
//	HVStopSnap(m_hhv);
	/*
	 *	终止数字摄像机采集图像到内存，同时释放所有采集环境，
	 *	再次启动数字摄像机采集，必须重新初始化	
	 */
	if (Initialized)
	{
		HVCloseSnap(m_hhv);
		//	关闭数字摄像机，释放数字摄像机内部资源
		EndHVDevice(m_hhv);
		//	回收图像缓冲区
	}
	
	delete []m_pRawBuffer;
	delete []m_pImageBuffer;
//	delete []m_pBmpInfo;
	CView::OnDestroy();
	// TODO: Add your message handler code here
}

void CCCDView::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class

	CView::PostNcDestroy();
}

void CCCDView::SetMirror(BOOL tempmirror)
{
	if (!Initialized)
		return;
	HVEnableVideoMirror(m_hhv,VERT_DIR,tempmirror);
}

void CCCDView::SetGain(int tempgain)
{
	if (!Initialized)
		return;
	for (int i = 0; i < 4; i++)
	{
		HVAGCControl(m_hhv, RED_CHANNEL + i, tempgain);
	}
}

void CCCDView::Savebitmap()
{
	// TODO: Add your control notification handler code here
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	BITMAPFILEHEADER bfh	= {0};
	DWORD dwImageSize		= 0;
	DWORD dwBytesRead		= 0;
	BOOL bRVal				= TRUE;
	DWORD tempcount=GetTickCount();
	CString	tempstr;
	tempstr.Format(_T("%d"),tempcount);
	CString BmpPath=pApp->mVar.m_TotalPathName+_T("\\")+_T(".bmp");

	dwImageSize		=  PICTUREWIDTH * PICTUREHEIGHT * 3;	//计算图像大小，由视频输出窗口和视频格式确定

	bfh.bfType		= (WORD)'M' << 8 | 'B';			//定义文件类型
	bfh.bfOffBits	= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);	//定义文件头大小

	bfh.bfSize		= bfh.bfOffBits + dwImageSize;		//文件大小
	HANDLE hFile = ::CreateFile(BmpPath,
		GENERIC_WRITE ,
		0,
		NULL,
		CREATE_ALWAYS,														
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if (hFile == INVALID_HANDLE_VALUE) 
	{
		bRVal = FALSE;
	}			
	else
	{
		::WriteFile(hFile, &bfh, sizeof(BITMAPFILEHEADER), &dwBytesRead, NULL );
		::WriteFile(hFile, m_pBmpInfo, sizeof(BITMAPINFOHEADER), &dwBytesRead, NULL );
		::WriteFile(hFile, m_pImageBuffer, dwImageSize, &dwBytesRead, NULL );
	}

	CloseHandle(hFile);
}

LRESULT CCCDView::OnMessageStartCapture(WPARAM wParam,LPARAM lParam)
{
	if (!Initialized)
		return TRUE;
	HVSTATUS status = STATUS_OK;
	/*
	 *	初始化数字摄像机采集图像到内存的控制，
	 *	指定回调函数SnapThreadCallback和用户参数m_hWnd
	 */
	BYTE *ppBuf[1];
	ppBuf[0] = m_pRawBuffer;
	status = HVStartSnap(m_hhv, ppBuf,1);
//	HV_VERIFY(status);
	if (!HV_SUCCESS(status)) 
	{
		AfxMessageBox(_T("开始图像采集失败!"));
	}
	return TRUE;
}

LRESULT CCCDView::OnMessageStopCapture(WPARAM wParam,LPARAM lParam)
{
	if (!Initialized)
		return TRUE;
	HVSTATUS status = STATUS_OK;
	/*
	 *	初始化数字摄像机采集图像到内存的控制，
	 *	指定回调函数SnapThreadCallback和用户参数m_hWnd
	 */
	HVStopSnap(m_hhv);
//	HV_VERIFY(status);
	if (!HV_SUCCESS(status)) 
	{
		AfxMessageBox(_T("停止图像采集失败!"));
	}
	return TRUE;
}
