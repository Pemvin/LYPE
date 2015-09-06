
/*****************************************************************************
* File Name:	HVGigE_WP.h
* Author: IndCam
* DATE: 2011-10-9
* Description:  �����ӿں���
* Functions:
*
* Current Version: V1.1.2
* Date: 2012-1-4
******************************************************************************/



// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HVGIGE_WP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HVGIGE_WP_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.


#ifdef HVGIGE_WP_EXPORTS
#define HVGIGE_WP_API __declspec(dllexport)
#else
#define HVGIGE_WP_API __declspec(dllimport)
#endif

#include "HVGigE_WP_def.h"
//#include "HVGigE_WP_Inc.h"


#define HV_SUCCESS                 0x20000000    //�����ɹ�
EXTERN_C BOOL g_bShowCtrlPage;


// data structure definitions
/******************************************************************************/
enum{VIDEO_INFO};

typedef struct _HVGIGE_DEV_I
{
	CHAR * pName;                       //�豸GUID
	CHAR * pDescription;                //�豸������
	BYTE * pSrcMacSddr;
	struct _HVGIGE_DEV_I * pNext;        //ָ����һ���豸��ָ��
}HVGigE_Dev_i, *pHVGigE_Dev_i;


typedef struct _HVGIGE_IMG_I
{	
	void*    pDataBuffer;           //��ǰ���ݻ������ĵ�ַ
	int      nImgWidth;				//ÿ֡����ͼ��Ŀ��
	int      nImgHeight;			//ÿ֡����ͼ��ĸ߶�
	int      nBitCount;				//ÿ��������ռ���ֽ���
	int      nDevId;				//��ǰ�豸������       //***********
}HVGigE_Img_i, *pHVGigE_Img_i;

typedef struct _HVGIGE_VIDEO_I
{	
	int      nVideoWidth;            //ÿ֡����ͼ��Ŀ��
	int      nVideoHeight;           //ÿ֡����ͼ��ĸ߶�
}HVGigE_Video_i, *pHVGigE_Video_i;


typedef struct _HVGigE_PREVIEWSNAP_STATE_I
{
	int nPreview;  // 1 for preview; 0 for snapshot; 
	int nSnapMode; // 0 or 2 when in preview mode; 0-2 for snapshot;
}HVGigE_PreSnap_State_i, *pHVGigE_PreSnap_State_i;



typedef enum _HVGigE_IMGMIRROR_I
{
	NO_MIRROR = 0,
	MIRROR_ROW = 1,
	MIRROR_COLUM = 2,
}HVGigE_ImgMirror_i;

typedef struct _HVGIGE_RANGE_I
{
	int nMax;
	int nMin;
}HVGigE_Range_i, *pHVGigE_Range_i;




typedef struct _HVGIGE_CONTROL_I  // structure for BlackLevel, GlobalGain, Exposure Control;
{
	BOOL bEnable; //enable=1;disable=0
	BOOL bAuto; //auto=1;manual=0;
	HVGigE_Range_i sRange;
	int  nValueArr[5]; // for Mode,G1, G2, R, B channel, if color channel needed.
}HVGigE_Control_i, *pHVGigE_Control_i;

// ����
typedef enum _REG_MODE_CHANNEL 
{
	MODE=0,
	GLOBAL=0,
	G1=1,
	G2=2,
	R=3,
	B=4
}REG_MODE_CHANNEL;

typedef struct _HVGIGE_GENCONTROL_I
{
	int				  nImgMirror;
	BOOL			  bColor;
	BOOL			  bGamma;
 	HVGigE_Video_i    sResolution;

	HVGigE_Control_i  sBlackLevel;
 	HVGigE_Control_i  sGain;
 	HVGigE_Control_i  sExposure;

	WORD			  nHBlankTime;  // horizontal blanking
	WORD			  nVBlankTime;  // vertical blanking

}HVGigE_GenContrl_i, *pHVGigE_GenControl_i;


// IO �����������
typedef enum _SNAPIO_INMODE_
{ 
	IN_FALLING_EDGE = 0,
	IN_RISING_EDGE = 1,
	IN_LOW_LEVEL = 2,
	IN_HIGH_LEVEL = 3,
}SNAPIO_INMODE;

typedef enum _SNAPIO_OUTMODE_
{
	OUT_LOW_LEVEL = 0,
	OUT_HIGHT_LEVEL = 1,
}SNAPIO_OUTMODE;

typedef struct _HVGigE_SNAPIO_MODE_I
{
	int nInMode;  
				//nInMode:  0 for falling-edge valid trigger; 
				// 		  1 for rising-edge valide trigger;
				//		  2 for low-level valid trigger;
				//		  3 for high-level valid trigger;

	int nOutMode;
				//nOutMode: 0 for low-level output;
				//  	    1 for high-level output;  


}HVGigE_SnapIO_Mode_i, *pHVGigE_SnapIO_Mode_i;


// ����ģʽ����
typedef struct _HVGIGE_SNAPCONTROL_I
{
	HVGigE_PreSnap_State_i  sPrevSnapState;//
	LONG lDebouncerTime;
	LONG lExpTime;

	LONG		  lTrigFreq;   //������Ƶ��
	LONG          lTrigImgCount; //����һ�Σ��ɼ������ͼ��֡��

	HVGigE_Range_i sExpTimeRange;   // Exposure Time Range
	HVGigE_Range_i sTrigFreqRange; 
// 	HVGigE_Range_i sTrigImgCount;

	HVGigE_SnapIO_Mode_i sSnapIOMode;

}HVGigE_SnapControl_i, *pHVGigE_SnapControl_i;


typedef enum tagHVGIGE_RESOLUTION {
	RES_MODE0 = 0,
	RES_MODE1 = 1,
	RES_MODE2 = 2,
	RES_MODE3 = 3,
} HVGige_Resolution;



/******************************************************************************/



typedef int(CALLBACK* USER_CALLBACK_PROC)(pHVGigE_Img_i pCommuParam);

/******************************************************************************
* Function:	HV_EnumerateDevice
* Description: �豸ö��
* Format:
*     HRESULT HV_EnumerateDevice(pHVGigE_Dev_i * pDev, int * nDevCount) ;
* Params:
*     pHVGigE_Dev_i * pDev: ��ȡ���豸��Ϣ
*     int * nDevCount: ��ȡ�豸����
* Return: 
*     HV_SUCCESS: �ɹ�;   HV_NO_SUCH_DEVICE: δ�ҵ�
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_EnumerateDevice(pHVGigE_Dev_i * pDev, int * nDevCount);

/******************************************************************************
* Function:	HV_OpenDevice
* Description: ���豸
* Format:
*     HRESULT HV_OpenDevice(int nDevId) ;
* Params:
*     int nId: �豸����
* Return: 
*     HV_SUCCESS: �ɹ�;   HV_NO_SUCH_DEVICE: δ�ҵ�
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_OpenDevice(int nDevId);

/******************************************************************************
* Function:	HV_DevCapInit
* Description: �豸��׽��ʼ��
* Format:
*     HRESULT HV_DevCapInit(int nDevId) ;
* Params:
*     void
* Return: 
*     HV_SUCCESS: �ɹ�
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_DevCapInit(int nDevId, LPCSTR lpFileName = NULL);

/******************************************************************************
* Function:	HV_DevCapRelease
* Description: ��Դ�ͷ�
* Format:
*     HRESULT HV_DevCapRelease(int nDevId) ;
* Params:
*     void
* Return: 
*     void
******************************************************************************/
HVGIGE_WP_API void    __stdcall HV_DevCapRelease(int nDevId);

/******************************************************************************
* Function:	HV_SetCallBack
* Description: ���ûص�����
* Format:
*     HRESULT HV_SetCallBack(USER_CALLBACK_PROC pCallBack,int nDevId) ;
* Params:
*     USER_CALLBACK_PROC pCallBack: �ص�������ַ
* Return: 
*     void
******************************************************************************/
HVGIGE_WP_API void    __stdcall HV_SetCallBack(USER_CALLBACK_PROC pCallBack,int nDevId);

/******************************************************************************
* Function:	HV_StartCapture
* Description: ��ʼͼ�񲶻�
* Format:
*     HRESULT HV_StartCapture(int nDevId) ;
* Params:
*     void
* Return: 
*     HV_SUCCESS: �ɹ�
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_StartCapture(int nDevId);

/******************************************************************************
* Function:	HV_SuspendCapture
* Description: ����/�ָ� Data Thread �� Show Thread.
* Format:
*     HRESULT HV_SuspendCapture(BOOL bSuspend,int nDevId);
* Params:
*     BOOL bSuspend: 1 for capture and show suspend; 0 for capture and show resume;
* Return: 
*     HV_SUCCESS: �ɹ�
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SuspendCapture(BOOL bSuspend,int nDevId);


/******************************************************************************
* Function:	HV_StopCapture
* Description: ֹͣͼ�񲶻�
* Format:
*     HRESULT HV_StopCapture(int nDevId) ;
* Params:
*     void
* Return: 
*     HV_SUCCESS: �ɹ�
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_StopCapture(int nDevId);

/******************************************************************************
* Function:	HV_ShowControlPage
* Description: �򿪿������ԶԻ���
* Format:
*     HRESULT HV_ShowControlPage(int nDevId) ;
* Params:
*     void
* Return: 
*     �����ַ���
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_ShowControlPage(int nDevId);

/******************************************************************************
* Function:	HV_ShowRWPage
* Description: �򿪶�/д�Ĵ����Ի���
* Format:
*     HRESULT HV_ShowRWPage(int nDevId) ;
* Params:
*     void
* Return: 
*     �����ַ���
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_ShowRWPage(int nDevId);

HVGIGE_WP_API HRESULT __stdcall HV_ShowSnapshotPage(int nDevId);

/******************************************************************************
* Function:	HV_GetFrameRate
* Description: ��ȡ֡��
* Format:
*     HRESULT HV_GetFrameRate(double & nRate, int nDevId) ;
* Params:
*     double & nRate: ֡��
* Return: 
*     �����ַ���
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetFrameRate(double & nRate, int nDevId);

/******************************************************************************
* Function:	HV_GetParamInfo
* Description: ��ȡ������Ϣ
* Format:
*     HRESULT HV_GetParamInfo(int nType, PVOID* ppParamInfoStruct,int nDevId) ;
* Params:
*     int nType: ���ȡ��Ϣ�����ͣ�VIDEO_INFO��
*     PVOID* ppParamInfoStruct: ��ȡ�Ĳ�����Ϣ
* Return: 
*     �����ַ���
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetParamInfo(int nType, PVOID* ppParamInfoStruct,int nDevId);

/******************************************************************************
* Function:	HV_GetFrameBuffer
* Description: ��ȡһ֡ͼ������
* Format:
*     HRESULT HV_GetFrameBuffer(long & lBufSize, LPBYTE * pBuf, int & nFrmWidth, int & nFrmHeight, int nDevId) ;
* Params:
*     long & lBufSize: ͼ�񻺴��С
*     LPBYTE * pBuf: ͼ�񻺴�����
*     int nFrmWidth: ͼ���
*     int nFrmHeight: ͼ���
* Return: 
*     �����ַ���
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetFrameBuffer(long & lBufSize, LPBYTE * pBuf, int & nFrmWidth, int & nFrmHeight, int nDevId);




/******************************************************************************
* Function:	HV_SaveImg
* Description: ����һ֡ͼ��Ϊ.bmp�ļ�
* Format:
*     HRESULT HV_SaveImg(LPBYTE pBuffer, LPCSTR lpFileName, const int nFrmWidth,
*						  const int nFrmHeight, const long lBufferSize, int nDevId)
* Params:
*     LPBYTE pBuffer: ͼ������Bufferָ��
*     LPCTSTR lpFileName: ��Ҫ�����bmp�ļ���
*     int nFrmWidth: ͼ���
*     int nFrmHeight: ͼ���
*	  long lBufferSize: ͼ������Buffer�Ĵ�С
* Return: 
*     ����ʱ�����ش����ַ��������򣬷�����ȷ�ִ�
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SaveImg(LPBYTE pBuffer, LPCSTR lpFileName, const int nFrmWidth,
										    const int nFrmHeight, const long lBufSize, int nDevId);


/******************************************************************************
* Function:	HV_GetErrorString
* Description: ��ȡ�����ַ���
* Format:
*     HRESULT HV_GetErrorString(LONG lError) ;
* Params:
*     LONG lError: ����״̬
* Return: 
*     �����ַ���
******************************************************************************/
HVGIGE_WP_API CHAR*   __stdcall HV_GetErrorString(LONG lError);


/******************************************************************************
* Function:	HV_SetPreviewSnapMode()
* Description: ����Ϊ����Ԥ��(contionus)ģʽ
* Format:
*     HRESULT HV_SetPreviewSnapMode(int nPreview, int nSnapMode)
* Params:
*		nPreview: 1 for preview mode; 
*				  0 for snapshot mode;
*		nSnapshot: snapshot mode, selected from 0 to 2, for both outer and inner
*				  trigger source.     
*
* Return: 
*     HV_SUCCESS: �ɹ�
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetPreviewSnapMode(int nPreview, int nSnapMode,int nDevId);



/******************************************************************************
* Function:	HV_GetPreviewSnapMode()
* Description: �õ���ǰΪPreview��Snapshot
* Format:
*     HRESULT HV_GetPreviewSnapMode(HVGigE_PreSnap_State_i* psPreSnapStae,int nDevId)
* Params:
*		nPreview: 1 for preview mode; 0 for snapshot mode;
*		nSnapshot: snapshot mode, selected from 0 to 2;  
*		pPreSnapState:In\OUT; 
*					  pPreSnapState.nPreview = 1, pPreSnapState.nSnapMode=0, for preview;  
*					  pPreSnapState.nPreview = 0, pPreSnapState.nSnapMode=0-2, for snapshot of outer trigger source;
*
* Return: 
*     HV_SUCCESS: �ɹ�
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetPreviewSnapMode(HVGigE_PreSnap_State_i* psPreSnapState,int nDevId);

/******************************************************************************
* Function:	void HV_GetMaxResolution()
* Description: ��ȡCIS���ֱ��ʵĿ���
* Format:
*     HVGIGE_WP_API HRESULT __stdcall HV_GetMaxXResolution(int& nMaxWidth, int& nMaxHeight,int nDevId)
* Params:
*     nMaxWidth:  IN/OUT; Width for CIS max resolution;
*     nMaxHeight: IN/OUT; Height for CIS max resolution;
* Return: 
*     void
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetMaxResolution(int& nMaxWidth, int& nMaxHeight,int nDevId);

//========================== Image Mirror Control ======================================

/******************************************************************************
* Function:	HV_SetImageMirror()
* Description: ����ͼ��ľ����������ַ�ʽ��ˮƽ����ֱ��ˮƽ��ֱ��
* Format:
*     HV_SetImageMirror(int nMirror,int nDevId)
* Params:
*	  int nMirror�� ����ͼ��ľ����������ַ�ʽ��ˮƽ����ֱ��ˮƽ��ֱ��
*					RowMirror=1; ColumnMirror=2; both=3;
* Return:
*     HV_SUCCESS:�ɹ���
*     HV_REASONLESS_PARAMETER:����������Χ��
*     HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SetImageMirror(int nMirror,int nDevId);

/******************************************************************************
* Function:	HV_GetImageMirror()
* Description: �õ�ͼ��ľ���ʽ��ˮƽ����ֱ��ˮƽ��ֱ��
* Format:
*     HV_GetImageMirror(int* pnMirror,int nDevId)
* Params:
*	  int* pnMirror: ���ص�ǰ�ľ���ʽ�������������ַ�ʽ��ˮƽ����ֱ��ˮƽ��ֱ��
*					RowMirror=1; ColumnMirror=2; both=3;
* Return:
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetImageMirror(int* pnMirror,int nDevId);

//========================= Image Resolution Control ===========================================

/******************************************************************************
* Function:	HV_GetResolution
* Description: ��ȡ��Ƶ�ķֱ���
* Format:
*     HRESULT HV_GetResolution(HVGigE_Video_i* psResolution,int nDevId)
* Params:
*	  HVGigE_Video_i* psResolution: ͼ��ķֱ���(sResolution)�ķ���ֵ
* Return:
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetResolution(HVGigE_Video_i* psResolution,int nDevId);

/******************************************************************************
* Function:	HV_SetResolution
* Description: ������Ƶ�ķֱ���
* Format:
*      HRESULT HV_SetResolution(HVGigE_Video_i sResolution, int nDevId)
* Params:
*	  HVGigE_Video_i sResolution��ͼ��ķֱ���(sResolution)
* Return:
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SetResolution(HVGigE_Video_i sResolution,int nDevId);

//========================= Image Color Control ===========================================
/******************************************************************************
* Function:	HV_GetImageColorStat()
* Description: �õ�ͼ��Ĳ�ɫ/�Ҷ�״̬
* Format:
*     HV_GetImageColorStat(BOOL* pbColor,int nDevId)
* Params:
*	  BOOL* pbColor�� ����ͼ��Ĳ�ɫ/�Ҷ�״̬
* Return:
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetImageColorStat(BOOL* pbColor,int nDevId);

/******************************************************************************
* Function:	HV_SetImageColorStat()
* Description: ����ͼ��Ĳ�ɫ/�Ҷ�״̬
* Format:
*     HV_SetImageColorStat(BOOL bColor, int nDevId)
* Params:
*	  BOOL bColor�� ����ͼ��Ĳ�ɫ/�Ҷ�״̬
* Return:
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SetImageColorStat(BOOL bColor, int nDevId);

//========================= Image Gamma Control ===========================================

/******************************************************************************
* Function:	HV_GetImageGammaStat()
* Description: �õ�ͼ���Gamma״̬
* Format:
*     HV_GetImageGammaStat(BOOL* pbGamma,int nDevId)
* Params:
*	  BOOL* pbColor�� ����ͼ���Gamma״̬
* Return:
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetImageGammaStat(BOOL* pbGamma,int nDevId);

/******************************************************************************
* Function:	HV_SetImageGammaStat()
* Description: ����ͼ���Gamma״̬
* Format:
*     HV_SetImageGammaStat(BOOL bGamma, int nDevId)
* Params:
*	  BOOL bColor�� ����ͼ��Gamma״̬
* Return:
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SetImageGammaStat(BOOL bGamma, int nDevId);

//========================= Black Level Control ===========================================

/******************************************************************************
* Function:	HV_GetBlackLevelInfo
* Description: ��ȡBlackLevel������Ϣ
* Format:
*     HRESULT HV_GetBlackLevelInfo( HVGigE_Control_i* psBlackLevel,int nDevId)
* Params:
*	   HVGigE_Control_i* psBlackLevel: ����sBlackLevel�Ĳ���ֵ��
* Return:
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetBlackLevelInfo( HVGigE_Control_i* psBlackLevel,int nDevId);

/******************************************************************************
* Function:	HV_SetBlackLevelInfo
* Description: ����BlackLevel������Ϣ
* Format:
*     HRESULT HV_SetParamInfo(HVGigE_Control_i sBlackLevel,int nDevId)
* Params:
*	  HVGigE_Control_i sBlackLevel: ��Ҫ���õ�BlackLevel�Ĳ���
* Return:
*      none
*    
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetBlackLevelInfo(HVGigE_Control_i sBlackLevel,int nDevId);

/******************************************************************************
* Function:	HV_SetBlackLevelEnable
* Description: ����BlackLevel.bEnable��ֵ
* Format:
*     HRESULT HV_SetBlackLevelEnable(BOOL bbEnable,int nDevId)
* Params:
*	  BOOL bEnable: ��Ҫ���õ�BlackLevel.bEnable��ֵ
* Return:
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸  
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetBlackLevelEnable(BOOL bEnable,int nDevId);

/******************************************************************************
* Function:	HV_GetBlackLevelEnable
* Description: ��ȡBlackLevel.bEnable������Ϣ
* Format:
*     HRESULT HV_GetBlackLevelEnable(BOOL* pbEnable,int nDevId)
* Params:
*	  BOOL* pbEnable: BlackLevel.bEnable��ֵ
* Return:
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸  
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetBlackLevelEnable(BOOL* pbEnable,int nDevId);

/******************************************************************************
* Function:	HV_SetBlackLevelAuto
* Description: ����BlackLevel.bAuto��ֵ
* Format:
*     HRESULT HV_SetBlackLevelAuto(BOOL bAuto,int nDevId)
* Params:
*	  BOOL bAuto: ��Ҫ���õ�sBlackLevel.bAuto��ֵ
* Return:
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸  
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetBlackLevelAuto(BOOL bAuto,int nDevId);


/******************************************************************************
* Function:	HV_GetBlackLevelAuto
* Description: ��ȡBlackLevel.bAuto��ֵ
* Format:
*     HRESULT  HV_GetBlackLevelAuto(BOOL* pbAuto,int nDevId)
* Params:
*	  BOOL* pbAuto: BlackLevel.bAuto�ķ���ֵ
* Return:
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸  
******************************************************************************/


HVGIGE_WP_API HRESULT __stdcall HV_GetBlackLevelAuto(BOOL* pbAuto,int nDevId);


/******************************************************************************
* Function:	HV_SetBlackLevelRange
* Description: ����sBlackLevel.sRange��ֵ
* Format:
*     HRESULT HV_SetBlackLevelRange(HVGigE_Range_i sRange,int nDevId)
* Params:
*	  HVGigE_Range_i sRange��BlackLevel����Чȡֵ��Χ
* Return:
*      HV_INVALID_PARAM:��Ч�Ĳ�����Χ��
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸  
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetBlackLevelRange(HVGigE_Range_i sRange,int nDevId);


/******************************************************************************
* Function:	HV_GetBlackLevelRange
* Description: ��ȡBlackLevel��ȡֵ��Χ
* Format:
*     HRESULT  HV_GetBlackLevelRange(HVGigE_Range_i* psRange,int nDevId)
* Params:
*	  HVGigE_Range_i* psRange: BlackLevel����Чȡֵ��Χ
* Return:
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetBlackLevelRange(HVGigE_Range_i* psRange,int nDevId);

/******************************************************************************
* Function:	HV_SetBlackLevelValue
* Description: ����sBlackLevel.nValueArr[]��ֵ,���������ı�sBlackLevel.nValueArr[1:4]��
* Format:
*     HRESULT HV_SetBlackLevelValue(int* pnValue,int nDevId)
* Params:
*	  int* pnValue: ��Ҫ���õ�BlackLevel.nValue[]��ֵ
* Return:
*      HV_INVALID_PARAM:��Ч�Ĳ�����Χ��
*	   HV_SUCCESS: �ɹ�����sBlackLevel.nValueArr[1:4]��ֵ
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
*
* NOTE: just set the Black Value from sBlackLevel.nValueArr[1] to sBlackLevel.nValueArr[4],
*       Have done NOTHING to sBlackLevel.nValueArr[0]��
*    
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetBlackLevelValue(int* pnValue,int nDevId);


/******************************************************************************
* Function:	HV_GetBlackLevelValue
* Description: ��ȡBlackLevel.nValue��ֵ
* Format:
*     HRESULT HV_GetBlackLevelValue(int* pnValueArr,int nDevId)
* Params:
*	  int* pnValueArr: ����sBlackLevel.nValueArr[0:5]��ֵ(BlackLevel.nValueArr[0:5])
* Return:
*	  HV_SUCCESS:�����ɹ�
*     HV_NO_SUCH_DEVICE�� û�ж�Ӧ��Ӳ��
*    
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetBlackLevelValue(int* pnValueArr,int nDevId);


//========================== Gain Control =========================================================

/******************************************************************************
* Function:	HV_GetGainInfo
* Description: ��ȡGain�Ĳ�����Ϣ
* Format:
*     HRESULT HV_GetGainInfo(HVGigE_Control_i* psGain,int nDevId)
* Params:
*     HVGigE_Control_i* psGain: Gain�ķ���ֵ
* Return:
*	  HV_SUCCESS:�����ɹ�
*     HV_NO_SUCH_DEVICE�� û�ж�Ӧ��Ӳ��
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetGainInfo(HVGigE_Control_i* psGain,int nDevId);

/******************************************************************************
* Function:	HV_SetGainInfo
* Description: ����Gain������Ϣ
* Format:
*     HRESULT HV_SetGainInfo(HVGigE_Control_i sGain,int nDevId)
* Params:
*	  HVGigE_Control_i sGain: ��Ҫ���õ�Gain�Ĳ���
* Return:
*      HRESULT hResult: ״̬����
*    
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetGainInfo(HVGigE_Control_i sGain,int nDevId);


/******************************************************************************
* Function:	HV_SetGainEnable
* Description: ����sGain.bEnable��ֵ
* Format:
*     HRESULT HV_SetGainEnable(BOOL bEnable,int nDevId)
* Params:
*	  bEnable: ��Ҫ���õ�sGain.bEnable��ֵ
* Return:
*	  HV_SUCCESS:�����ɹ�
*     HV_NO_SUCH_DEVICE�� û�ж�Ӧ��Ӳ��
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetGainEnable(BOOL bEnable,int nDevId);

/******************************************************************************
* Function:	HV_GetGainEnable
* Description: ��ȡsGain.bEnable��ֵ
* Format:
*     HRESULT HV_GetGainEnable(BOOL* pbEnable,int nDevId)
* Params:
*	  BOOL* bEnable�����ص�sGain.bEnable��ֵ
* Return:
*	  HV_SUCCESS:�����ɹ�
*     HV_NO_SUCH_DEVICE�� û�ж�Ӧ��Ӳ��
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetGainEnable(BOOL* pbEnable,int nDevId);


/******************************************************************************
* Function:	HV_SetGainAuto
* Description: ����sGain.bAuto��ֵ
* Format:
*     HRESULT HV_SetGainAuto(BOOL bAuto,int nDevId)
* Params:
*	  BOOL bAuto: ��Ҫ���õ�sGain.bAuto��ֵ
* Return:
*	  HV_SUCCESS:�����ɹ�
*     HV_NO_SUCH_DEVICE�� û�ж�Ӧ��Ӳ��
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetGainAuto(BOOL bAuto,int nDevId);

/******************************************************************************
* Function:	HV_GetGainAuto
* Description: ��ȡsGain.bAuto��ֵ
* Format:
*     HRESULT HV_GetGainAuto(BOOL* pbAuto,int nDevId)
* Params:
*	  BOOL* pbAuto������sGain.bAuto��ֵ
* Return:
*	  HV_SUCCESS:�����ɹ�
*     HV_NO_SUCH_DEVICE�� û�ж�Ӧ��Ӳ��
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetGainAuto(BOOL* pbAuto,int nDevId);


/******************************************************************************
* Function:	HV_SetGainRange
* Description: ����sGain.sRange��ֵ
* Format:
*     HRESULT HV_SetGainRange(HVGigE_Range_i sRange,int nDevId)
* Params:
*     HVGigE_Range_i sRange: Gain����Чȡֵ��Χ
* Return:
*      HV_INVALID_PARAM:��Ч�Ĳ�����Χ��
*	   HV_SUCCESS: �ɹ���
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetGainRange(HVGigE_Range_i sRange,int nDevId);

/******************************************************************************
* Function:	HV_GetGainRange
* Description: ��ȡsGain.sRange��ֵ
* Format:
*     HRESULT HV_GetGainRange(HVGigE_Range_i* psRange,int nDevId)
* Params:
*	  HVGigE_Range_i* psRange��sGain.sRange�ķ���ֵ
* Return:
*	   HV_SUCCESS: �ɹ���
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetGainRange(HVGigE_Range_i* psRange,int nDevId);



/******************************************************************************
* Function:	HV_SetGainValue
* Description: ����sGain.nValue[0:4]��ֵ
* Format:
*     HRESULT HV_SetGainValue(int* pnValueArr,int nDevId)
* Params:
*	  int* pValueArr: sGain.valueArr[0:4]��ֵ
* Return:
*      HV_INVALID_PARAM:��Ч�Ĳ�����Χ��
*	   HV_SUCCESS: �ɹ�����Gain��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
* 
* NOTE: set gain value from sGain.nValue[0] to sGain.nValue[4].   
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetGainValue(int* pValueArr,int nDevId);

/******************************************************************************
* Function:	HV_GetGainValue
* Description: ��ȡsGain.nValue[0:4]��ֵ
* Format:
*     HRESULT HV_GetGainValue(int* nValue,int nDevId)
* Params:
*	  int* nValue������sGain.nValueArr[0:4]�ĵ�ǰֵ��������
*				   Global Gain��G1 Gain��G2 Gain��R Gain, B Gain;
* Return:
*	   HV_SUCCESS: �ɹ�����Gain��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetGainValue(int* pnValue,int nDevId);

//======================== Exposure Control ======================================================

////////////////////////////////////////////////////////////////////////////////////
//			Exposure�Ĳ����������ȡ
//
/******************************************************************************
* Function:	HV_GetExposureInfo
* Description: ��ȡExposure�Ĳ�����Ϣ
* Format:
*     HRESULT HV_GetExposureInfo(HVGigE_Control_i* psExposure,int nDevId)
* Params:
*	  HVGigE_Control_i* psExposur:����Exposure�����ò���
* Return:
*	   HV_SUCCESS: �ɹ���
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetExposureInfo(HVGigE_Control_i* psExposure,int nDevId);


/******************************************************************************
* Function:	HV_SetExposureInfo
* Description: ����Exposure������Ϣ
* Format:
*     HRESULT HV_SetExposureInfo(HVGigE_Control_i sExposure,int nDevId)
* Params:
*	  HVGigE_Control_i sExposure: ��Ҫ���õ�Exposure�Ĳ�����Ϣ
* Return:
*	   HV_SUCCESS: �ɹ���
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetExposureInfo(HVGigE_Control_i sExposure,int nDevId);


/******************************************************************************
* Function:	HV_SetExposureEnable
* Description: ����sExposure.bEnable��ֵ
* Format:
*     HRESULT HV_SetExposureEnable(BOOL bEnable,int nDevId)
* Params:
*	  bEnable: ��Ҫ���õ�sExposure.bEnable��ֵ
* Return:
*	   HV_SUCCESS: �ɹ�����Gain��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetExposureEnable(BOOL bEnable,int nDevId);


/******************************************************************************
* Function:	HV_GetExposureEnable
* Description: ��ȡExposure.bEnable������Ϣ
* Format:
*     BOOL HV_GetExposureEnable(BOOL* pbEnable,int nDevId)
* Params:
*	  BOOL* pbEnable: Exposure.bEnable��״̬
* Return:
*	   HV_SUCCESS: �ɹ�����Gain��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetExposureEnable(BOOL* pbEnable,int nDevId);



/******************************************************************************
* Function:	HV_SetExposureAuto
* Description: ����Exposure.bAuto��ֵ
* Format:
*     HRESULT HV_SetExposureAuto(BOOL bAuto,int nDevId)
* Params:
*	  BOOL bAuto: ��Ҫ���õ�sExposure.bAuto��ֵ
* Return:
*	   HV_SUCCESS: �ɹ���
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetExposureAuto(BOOL bAuto,int nDevId);


/******************************************************************************
* Function:	HV_GetExposureAuto
* Description: ��ȡsExposure.bAuto��ֵ
* Format:
*     HRESULT HV_GetExposure.bAuto(BOOL* pbAuto,int nDevId)
* Params:
*	  BOOL* pbAuto: sExposure.bAuto��ֵ
* Return:
*	   HV_SUCCESS: �ɹ���
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetExposureAuto(BOOL* pbAuto,int nDevId);


/******************************************************************************
* Function:	HV_SetExposureRange
* Description: ����Exposure����Чȡֵ��Χ��sExposure.sRange��ֵ
* Format:
*     HRESULT HV_SetExposureRange(HVGigE_Range_i sRange,int nDevId)
* Params:
*	  HVGigE_Range_i sRange��Exposure����Чȡֵ��Χ��sExposure.sRange��ֵ
* Return:     
*      HV_INVALID_PARAM: ����������Ч��Χ֮�ڣ�
*	   HV_SUCCESS: �ɹ�����Exposure�ķ�Χ
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetExposureRange(HVGigE_Range_i sRange,int nDevId);

/******************************************************************************
* Function:	HV_GetExposureRange
* Description: ��ȡExposure����Чȡֵ��Χ,sExposre.sRange��ֵ
* Format:
*     HRESULT  HV_GetExposureRange(HVGigE_Range_i* psRange,int nDevId)
* Params:
*	  HVGigE_Range_i* psRange: Exposure����Чȡֵ��Χ��sExposure.sRange��ֵ
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure�ķ�Χ
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetExposureRange(HVGigE_Range_i* psRange,int nDevId);


/******************************************************************************
* Function:	HV_SetExposureValue
* Description: ����Exposure.nValue��ֵ
* Format:
*     HRESULT HV_SetExposureValue(int nValue,int nDevId)
* Params:
*	  nValue: Exposure��ֵ(Exposure.nValue),��λΪ������
* Return:
*      HV_INVALID_PARAM: ����������Ч��Χ֮�ڣ�
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetExposureValue(int nValue,int nDevId);


/******************************************************************************
* Function:	HV_GetExposureValue
* Description: ��ȡExposure.nValue��ֵ
* Format:
*     HRESULT HV_GetExposureValue(int* pnValue,int nDevId)
* Params:
*	  int* pnValue:  Exposure�ĵ�ǰֵ(Exposure.nValue��ֵ)����λΪ����
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetExposureValue(int* pnValue,int nDevId);


//======================== Snapshot Control ======================================================
///////////////////////////////////////////////////////////////////////////////////
//		Snapshot �Ĳ����������ȡ
//

/******************************************************************************
* Function:	HV_GetSnapInfo
* Description: ��ȡExposure�Ĳ�����Ϣ
* Format:
*     HRESULT HV_GetSnapInfo(HVGigE_SnapControl_i* psSnapControl, int nDevId)
* Params:
*	  HVGigE_SnapControl_i* psSnapControl: Snapshot�����ò���
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetSnapInfo(HVGigE_SnapControl_i* psSnapControl, int nDevId);


/******************************************************************************
* Function:	HV_SetSnapInfo
* Description: ����Snapshot������Ϣ
* Format:
*     HRESULT HV_SetSnapInfo(HVGigE_SnapControl_i sSnap, int nDevId)
* Params:
*	  HVGigE_SnapControl_i sSnap: ��Ҫ���õ�Snapshot�Ĳ���
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetSnapInfo(HVGigE_SnapControl_i sSnap, int nDevId);

/******************************************************************************
* Function:	HV_SetSnapDebounceTime()
* Description: ��������ģʽʱ��ȥ����ʱ��(DebouncerTime)��ʱ�䵥λΪus.
* Format:
*     HRESULT HV_SetSnapDebounceTime(const LONG lDebouncerTime,int nDevId)
* Params:
*	 LONG lDebouncerTime: ȥ����ʱ�䣬��λΪus
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetSnapDebounceTime(const LONG lDebouncerTime,int nDevId);


/******************************************************************************
* Function:	HV_GetSnapDebounceTime()
* Description: ��ȡ����ģʽʱ��ȥ����ʱ��(DebouncerTime)��ʱ�䵥λΪus.
* Format:
*     LONG HV_GetSnapDebounceTime(LONG *plDebouncerTime,int nDevId)
* Params:
*	  LONG lDebouncerTime: ����ȥ����ʱ�䣬��λΪus
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetSnapDebounceTime(LONG *plDebouncerTime,int nDevId);



/******************************************************************************
* Function:	HV_SetSnapExpTime()
* Description: ��������ģʽʱ���ع�ʱ��(ExposureTime)��ʱ�䵥λΪus.
* Format:
*     HV_SetSnapExpTime(const LONG lExpTime,int nDevId)
* Params:
*	  LONG lExpTime���ع�ʱ�䣬��λΪus
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetSnapExpTime(const LONG lExpTime,int nDevId);



/******************************************************************************
* Function:	HV_GetSnapExpTime()
* Description: �������ģʽʱ���ع�ʱ��(ExposureTime)��ʱ�䵥λΪus.
* Format:
*     LONG HV_GetSnapExpTime(LONG* plExpTime,int nDevId) 
* Params:
*	 LONG* plExpTime�������ع�ʱ�䣬��λΪ΢��
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetSnapExpTime(LONG* plExpTime,int nDevId);

/******************************************************************************
* Function:	HV_GetSnapExpTimeRange(HVGigE_Range_i* psRange)
* Description: ��������ģʽʱ���ع�ʱ��(ExposureTime)����Чֵ��Χ.ʱ�䵥λΪus.
* Format:
*     HResult HV_GetSnapExpTimeRange(HVGigE_Range_i* psRange,int nDevId)
* Params:
*	 HVGigE_Range_i* psRange�������ع�ʱ����Чֵ�ķ�Χ����λΪ΢��
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetSnapExpTimeRange(HVGigE_Range_i* psRange,int nDevId);

/******************************************************************************
* Function:	HV_GetTrigFreqRange(HVGigE_Range_i* psRange,int nDevId)
* Description: ��������ģʽʱ������Ƶ�ʵ���Чֵ��Χ.
* Format:
*     HResult HV_GetTrigFreqRange(HVGigE_Range_i* psRange,int nDevId)
* Params:
*	 HVGigE_Range_i* psRange����������ģʽʱ������Ƶ�ʵ���Чֵ��Χ
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetTrigFreqRange(HVGigE_Range_i* psRange,int nDevId);


/******************************************************************************
* Function:	HV_GetTrigImgCountRange(HVGigE_Range_i* psRange)
* Description: ��������ģʽʱ������Ƶ�ʵ���Чֵ��Χ.
* Format:
*     HResult HV_GetTrigImgCountRange(HVGigE_Range_i* psRange,int nDevId)
* Params:
*	 HVGigE_Range_i* psRange����������ģʽʱ������������������Чֵ��Χ
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetTrigImgCountRange(HVGigE_Range_i* psRange,int nDevId);

/******************************************************************************
* Function:	HV_SetPreviewSnapMode()
* Description: ����Ϊ����Ԥ��(contionus)ģʽ
* Format:
*     HRESULT HV_SetPreviewSnapMode(int nPreview, int nSnapMode,int nDevId)
* Params:
*		nPreview: 1 for preview mode; 
*				  0 for snapshot mode ; 
*		nSnapshot: snapshot mode, selected from 0 to 2, for both outer and inner
*				  trigger source.     
*
* Return: 
*     HV_SUCCESS: �ɹ�
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetPreviewSnapMode(int nPreview, int nSnapMode,int nDevId);


/******************************************************************************
* Function:	HV_GetPreviewSnapMode()
* Description: �õ���ǰΪPreview��Snapshot
* Format:
*     HRESULT HV_GetPreviewSnapMode(HVGigE_PreSnap_State_i* psPreSnapStae)
* Params:
*		nPreview: 1 for preview mode; 0 for snapshot mode;
*		nSnapshot: snapshot mode, selected from 0 to 2;  
*		pPreSnapState:In\OUT; 
*					  pPreSnapState.nPreview = 1, pPreSnapState.nSnapMode=0, for preview;  
*					  pPreSnapState.nPreview = 0, pPreSnapState.nSnapMode=0-2, for both outer and inner
*				  trigger source.     
*
* Return: 
*     HV_SUCCESS: �ɹ�
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetPreviewSnapMode(HVGigE_PreSnap_State_i* psPreSnapState);

/******************************************************************************
* Function:	HV_SetSnapTrigFreqImgCount()
* Description: ��������ģʽʱ��������Ƶ���Լ�ÿ�δ��������ͼ������
* Format:
*     HRESULT HV_SetSnapTrigFreqImgCount(LONG lTrigFreq, LONG lTrigImgCount,int nDevId)
* Params:
*	 LONG lTrigFreq: ��������ģʽʱ��(����ƣ��Ĵ���Ƶ�ʡ���λΪÿ���֡����
*    LONG lTrigImgCount������һ�Σ����������ͼ��֡��
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT HV_SetSnapTrigFreqImgCount(LONG lTrigFreq, LONG lTrigImgCount,int nDevId);

/******************************************************************************
* Function:	HV_GetSnapTrigFreqImgCount()
* Description: ��������ģʽʱ��������Ƶ���Լ�ÿ�δ��������ͼ������
* Format:
*     HRESULT HV_GetSnapTrigFreqImgCount(LONG* plTrigFreq, LONG* plTrigImgCount,int nDevId)
* Params:
*	 LONG* plTrigFreq: ��������ģʽʱ��(����ƣ��Ĵ���Ƶ�ʡ���λΪÿ���֡����
*    LONG* plTrigImgCount������һ�Σ����������ͼ��֡��
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT HV_GetSnapTrigFreqImgCount(LONG* plTrigFreq, LONG* plTrigImgCount,int nDevId);


/******************************************************************************
* Function:	void HV_GetMaxResolution()
* Description: ��ȡCIS���ֱ��ʵĿ���
* Format:
*     HRESULT HV_GetMaxResolution(int& nMaxWidth, int& nMaxHeight,int nDevId)
* Params:
*     nMaxWidth:  IN/OUT; Width for CIS max resolution;
*     nMaxHeight: IN/OUT; Height for CIS max resolution;
* Return: 
*     void
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetMaxResolution(int& nMaxWidth, int& nMaxHeight,int nDevId);

/******************************************************************************
* Function:	void HV_SaveParaToIniFile()
* Description: ���������浽ini�ļ�
* Format:
*     HRESULT HV_SaveParaToIniFile(int nDevId, LPCSTR lpFileName = NULL)
* Params:
*	  none
* Return: 
*     void
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SaveParaToIniFile(int nDevId, LPCSTR lpFileName = NULL);

/******************************************************************************
* Function:	void HV_IniCamFromIniFile()
* Description: ʹ��ini�ļ��еĲ������������
* Format:
*     HRESULT HV_IniCamFromIniFile(int  nDevId)
* Params:
*	  none
* Return: 
*     void
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_IniCamFromIniFile(int nDevId,LPCSTR lpFileName = NULL);

/******************************************************************************
* Function:	HV_SetSnapIOMode()
* Description: ��������ģʽ(snapshot)�£����IO����ģʽ��
* Format:
*     HRESULT HV_SetSnapIOMode(HVGigE_SnapIO_Mode_i sSnapIOMode)
* Params:
*		sSnapIOMode.nInMode:  0 for falling-edge valid trigger; 
*							  1 for rising-edge valide trigger;
*							  2 for low-level valid trigger;
*							  3 for high-level valid trigger;
*		sSnapIOMode.nOutMode: 0 for low-level output;
*							  1 for high-level output;  
*
* Return: 
*     HV_SUCCESS: �ɹ�
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetSnapIOMode(HVGigE_SnapIO_Mode_i sSnapIOMode,int nDevId);

/******************************************************************************
* Function:	HV_GetSnapIOMode()
* Description: ��������ģʽ(snapshot)�£����IO����ģʽ��
* Format:
*     HRESULT HV_GetSnapIOMode(HVGigE_SnapIO_Mode_i* psSnapIOMode,int nDevId)
* Params:
*		psSnapIOMode->nInMode:  0 for falling-edge valid trigger; 
*								1 for rising-edge valide trigger;
*								2 for low-level valid trigger;
*								3 for high-level valid trigger;
*		psSnapIOMode->nOutMode: 0 for low-level output;
*								1 for high-level output;  
*
* Return: 
*     HV_SUCCESS: �ɹ�
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetSnapIOMode(HVGigE_SnapIO_Mode_i* psSnapIOMode,int nDevId);

/******************************************************************************
* Function:	HV_GetRawData(HVGigE_Img_i* pRawFrameInfo)
* Description: ����RawData���ݣ�
* Format:
*     HRESULT HV_GetRawData(HVGigE_Img_i* pRawFrameInfo,int nDevId)
* Params:
*		HVGigE_Img_i* pRawFrameInfo:  RawData ��Ϣ
*		pRawFrameInfo->nImgHeight: ͼ��ĸ�
*		pRawFrameInfo->nImgWidth��ͼ��Ŀ�
*		pRawFrameInfo->nBitCount��ÿ��ͼ��������ռ���ֽ���, ֵΪ1
*		pRawFrameInfo->pDataBuffer��ָ��RawData ͼ������Buffer��ָ��	
*
* Return: 
*     HV_SUCCESS: �ɹ�
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetRawData(HVGigE_Img_i* pRawFrameInfo,int nDevId);


/*****************************************************************************
* Function:	HV_GetRGBData(HVGigE_Img_i* pRGBFrameInfo)
* Description: ����RGB���ݣ�
* Format:
*     HRESULT HV_GetRGBData(HVGigE_Img_i* pRGBFrameInfo,int nDevId)
* Params:
*		HVGigE_Img_i* pRawFrameInfo:  RawData ��Ϣ
*		pRGBFrameInfo->nImgHeight: ͼ��ĸ�
*		pRGBFrameInfo->nImgWidth��ͼ��Ŀ�
*		pRGBFrameInfo->nBitCount��ÿ��ͼ��������ռ���ֽ�����ֵΪ3
*		pRGBFrameInfo->pDataBuffer��ָ��RGBͼ������Buffer��ָ��	
*
* Return: 
*     HV_SUCCESS: �ɹ�
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetRGBData(HVGigE_Img_i* pRGBFrameInfo,int nDevId);


/******************************************************************************
* Function:	HV_SnapSWTrigger()
* Description: Snapshotģʽʱ������ sw Trigger(�������)����Ӧ����
* Format:
*     void HV_SnapSWTrigger()
* Params:
*     void
* Return: 
*     HV_SUCCESS: �ɹ�
*     HV_UNSUCCESS: ʧ��
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall	HV_SnapSWTrigger(int nDevId);

/******************************************************************************
* Function:	HV_CloseDevice
* Description: �ر�������ͷ���Դ
* Format:
*     HRESULT HV_CloseDevice(int nDevId) ;
* Params:
*     void
* Return: 
*     void
******************************************************************************/
HVGIGE_WP_API void __stdcall HV_CloseDevice(int nDevId);

/******************************************************************************
* Function:	HV_SetROI
* Description: ������Ƶ��ROI(Region of Interest)
* Format:
*      HRESULT HV_SetROI(int Original_x, int Original_y,
*						int nImgWidth, int nImgHeight,int nDevId)
* Params:
*	  int Oringination_x: ROI����ʼ��x����
*	  int Oringination_y: ROI����ʼ��y����
*     int nImgWidth: ROI�Ŀ��
*     int nImgHeight: ROI�ĸ߶�
*     int nDevId: �豸������
* Return:
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SetROI(int Original_x, int Original_y, 
										  int nImgWidth, int nImgHeight,int nDevId);

/******************************************************************************
* Function:	HV_SetResolutionMode
* Description: ���÷ֱ���ģʽ
* Format:
*     HRESULT HV_SetResolutionMode(HVGige_Resolution Res_Mode, int nDevId) ;
* Params:
*     HVGige_Resolution Res_Mode �ֱ���ģʽ
*	  int nDevId  �豸������
* Return: 
*     HV_SUCCESS  �ɹ�
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SetResolutionMode(HVGige_Resolution Res_Mode, int nDevId);

/******************************************************************************
* Function:	HV_GetImageChannel
* Description: ��ȡͼ���ͨ������Ϊ1����3
* Format:
*     HRESULT HV_GetImageChannel(int& nChannel,int nDevId)
* Params:
*	  int& nBitCount: ͼ��ͨ�����ķ���ֵ
* Return:
*	   HV_SUCCESS: �ɹ�
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetImageChannel(int& nChannel,int nDevId);

