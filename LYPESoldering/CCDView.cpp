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

//�����Լ���0
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
	 *	��ʼ�����г�Ա������ͬʱ�����������
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

	//	����������� 1
	status = BeginHVDevice(1,&m_hhv);
	//	���麯��ִ��״̬�����ʧ�ܣ��򷵻ش���״̬��Ϣ��
	if (!HV_SUCCESS(status)) 
	{
		AfxMessageBox(_T("����޷��ҵ�����ʼ��ʧ�ܣ�"));
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
		*	��ʼ�����������Ӳ��״̬���û�Ҳ����������λ�ó�ʼ�������������
		*	��Ӧ��֤����������Ѿ��򿪣������û���Ӧ�ó����ʼ��ʱ��
		*	ͬʱ��ʼ�����������Ӳ����
	*/
	
	//	��������������ֱ���
	if (!Initialized)
		return;
	HVSetResolution(m_hhv, Resolution);		
	
	//	�ɼ�ģʽ������ CONTINUATION(����)��TRIGGER(�ⴥ��)
	HVSetSnapMode(m_hhv, SnapMode);
	
	//  ���ø�������������
	for (int i = 0; i < 4; i++)
	{
		HVAGCControl(m_hhv, RED_CHANNEL + i, pApp->mVar.GAIN);
	}

	HVSetSnapSpeed( m_hhv, HIGH_SPEED);
	
	//	�����ع�ʱ��
	SetExposureTime(width,pApp->mVar.EXPOSURE,ExposureTint_Lower);	
	
	//  ����ADC�ļ���
	HVADCControl(m_hhv, ADC_BITS, ADCLevel);
	
//	HVEnableVideoMirror(m_hhv,VERT_DIR,TRUE);
	/*
	*	��Ƶ������ڣ�����Ƶ�����Χ���������ȡֵ��Χ���������봰�ڷ�Χ���ڣ�
	*  ��Ƶ�������Ͻ�X����ʹ��ڿ��ӦΪ4�ı��������Ͻ�Y����ʹ��ڸ߶�ӦΪ2�ı���
	*	������ڵ���ʼλ��һ������Ϊ(0, 0)���ɡ�
	*/
	HVSetOutputWindow(m_hhv, XStart, YStart, width, height);
	
	//	m_pBmpInfo��ָ��m_chBmpBuf���������û������Լ�����BTIMAPINFO������	
	m_pBmpInfo								= (BITMAPINFO *)m_chBmpBuf;
	//	��ʼ��BITMAPINFO �ṹ���˽ṹ�ڱ���bmp�ļ�����ʾ�ɼ�ͼ��ʱʹ��
	m_pBmpInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	//	ͼ���ȣ�һ��Ϊ������ڿ��
	m_pBmpInfo->bmiHeader.biWidth			= width;
	//	ͼ���ȣ�һ��Ϊ������ڸ߶�
	m_pBmpInfo->bmiHeader.biHeight			= height;
	
	/*
	*	��������һ����ͬ��
	*	���ڵ���8λ��λͼ����Ӧ������Ӧ��λͼ��ɫ��
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
	*	����ԭʼͼ�񻺳�����һ�������洢�ɼ�ͼ��ԭʼ����
	*  һ��ͼ�񻺳�����С��������ڴ�С����Ƶ��ʽȷ����
	*/
	m_pRawBuffer = new BYTE[width * height];
	ASSERT(m_pRawBuffer);

	/*
	����Bayerת����ͼ�����ݻ���
	*/
	m_pImageBuffer = new BYTE[width * height * 3];
	ASSERT(m_pImageBuffer);

	HVSTATUS status = STATUS_OK;
	/*
	 *	��ʼ������������ɼ�ͼ���ڴ�Ŀ��ƣ�
	 *	ָ���ص�����SnapThreadCallback���û�����m_hWnd
	 */
	status = HVOpenSnap(m_hhv, SnapThreadCallback, m_hWnd);					
//	HV_VERIFY(status);
	if (!HV_SUCCESS(status)) 
	{
		AfxMessageBox(_T("CCD��ʧ��!"));
	}

	BYTE *ppBuf[1];
	ppBuf[0] = m_pRawBuffer;
	status = HVStartSnap(m_hhv, ppBuf,1);
//	HV_VERIFY(status);
	if (!HV_SUCCESS(status)) 
	{
		AfxMessageBox(_T("��ʼͼ��ɼ�ʧ��!"));
	}
}

int CALLBACK CCCDView::SnapThreadCallback(HV_SNAP_INFO *pInfo)
{
	HWND hwnd = (HWND)(pInfo->pParam);
	
	/*
	 *	�����Զ�����ϢWM_SNAP_EX_CHANGE�������ڣ�	
	 *	ͬʱ���뵱ǰ���Դ����ͼ�����
	 *	ע�⣺��SendMessage������Ϣ������ȴ���Ϣ������Ϻ󣬲����˳�����SendMessage����
	 */
	::SendMessage(hwnd, WM_SNAP_CHANGE, 0, 0);

	return 1;
}

/*
	����:
		SetExposureTime
	�������:
		int nWindWidth			��ǰͼ����		
		int lTintUpper			�ع�ʱ��ķ��ӣ�shutter��ȡֵ
		int lTintLower			�ع�ʱ��ķ�ĸ����shutter�ĵ�λ���
								��ms:1000��s:1��
	�������:
		��						
	˵��:
		�����ع�ʱ�䣨�����Ĳ����������ʱ��Ƶ�ʣ�����ֵ��ȡĬ��ֵ��
 */
void CCCDView::SetExposureTime(int nWindWidth,long lTintUpper,long lTintLower)
{
	if (!Initialized)
		return;
	int size = sizeof(HVTYPE);
	HVTYPE type;
	HVGetDeviceInfo(m_hhv,DESC_DEVICE_TYPE, &type, &size);	
	
	//��ο��ع�ϵ��ת����ʽ
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

	CDC *pDC			= GetDC();//pView->GetDC();		//�õ�VIEW��DC
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	int i;
	
    //ͬʱ��ԭʼ���ݽ������·�ת
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
	//����ͼ�ͻ�����ʾͼ��
	StretchDIBits(pDC->GetSafeHdc(),
					0,						
					0,
					width,					//��ʾ���ڿ��
					height,					//��ʾ���ڸ߶�
					0,
					0,
					width,					//ͼ����
					height,					//ͼ��߶�
					m_pImageBuffer,			//ͼ�񻺳���
					m_pBmpInfo,				//BMPͼ��������Ϣ
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
	//	ֹͣ�ɼ�ͼ���ڴ棬�����ٴε���HVStartSnapEx��������������ɼ�
//	HVStopSnap(m_hhv);
	/*
	 *	��ֹ����������ɼ�ͼ���ڴ棬ͬʱ�ͷ����вɼ�������
	 *	�ٴ���������������ɼ����������³�ʼ��	
	 */
	if (Initialized)
	{
		HVCloseSnap(m_hhv);
		//	�ر�������������ͷ�����������ڲ���Դ
		EndHVDevice(m_hhv);
		//	����ͼ�񻺳���
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

	dwImageSize		=  PICTUREWIDTH * PICTUREHEIGHT * 3;	//����ͼ���С������Ƶ������ں���Ƶ��ʽȷ��

	bfh.bfType		= (WORD)'M' << 8 | 'B';			//�����ļ�����
	bfh.bfOffBits	= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);	//�����ļ�ͷ��С

	bfh.bfSize		= bfh.bfOffBits + dwImageSize;		//�ļ���С
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
	 *	��ʼ������������ɼ�ͼ���ڴ�Ŀ��ƣ�
	 *	ָ���ص�����SnapThreadCallback���û�����m_hWnd
	 */
	BYTE *ppBuf[1];
	ppBuf[0] = m_pRawBuffer;
	status = HVStartSnap(m_hhv, ppBuf,1);
//	HV_VERIFY(status);
	if (!HV_SUCCESS(status)) 
	{
		AfxMessageBox(_T("��ʼͼ��ɼ�ʧ��!"));
	}
	return TRUE;
}

LRESULT CCCDView::OnMessageStopCapture(WPARAM wParam,LPARAM lParam)
{
	if (!Initialized)
		return TRUE;
	HVSTATUS status = STATUS_OK;
	/*
	 *	��ʼ������������ɼ�ͼ���ڴ�Ŀ��ƣ�
	 *	ָ���ص�����SnapThreadCallback���û�����m_hWnd
	 */
	HVStopSnap(m_hhv);
//	HV_VERIFY(status);
	if (!HV_SUCCESS(status)) 
	{
		AfxMessageBox(_T("ֹͣͼ��ɼ�ʧ��!"));
	}
	return TRUE;
}
