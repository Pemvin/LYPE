
/*****************************************************************************
* File Name:	HVGigE_WP.h
* Author: IndCam
* DATE: 2011-10-9
* Description:  导出接口函数
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


#define HV_SUCCESS                 0x20000000    //操作成功
EXTERN_C BOOL g_bShowCtrlPage;


// data structure definitions
/******************************************************************************/
enum{VIDEO_INFO};

typedef struct _HVGIGE_DEV_I
{
	CHAR * pName;                       //设备GUID
	CHAR * pDescription;                //设备描述符
	BYTE * pSrcMacSddr;
	struct _HVGIGE_DEV_I * pNext;        //指向下一个设备的指针
}HVGigE_Dev_i, *pHVGigE_Dev_i;


typedef struct _HVGIGE_IMG_I
{	
	void*    pDataBuffer;           //当前数据缓冲区的地址
	int      nImgWidth;				//每帧数据图像的宽度
	int      nImgHeight;			//每帧数据图像的高度
	int      nBitCount;				//每个像素所占的字节数
	int      nDevId;				//当前设备索引号       //***********
}HVGigE_Img_i, *pHVGigE_Img_i;

typedef struct _HVGIGE_VIDEO_I
{	
	int      nVideoWidth;            //每帧数据图像的宽度
	int      nVideoHeight;           //每帧数据图像的高度
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

// 控制
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


// IO 输入输出类型
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


// 拍照模式控制
typedef struct _HVGIGE_SNAPCONTROL_I
{
	HVGigE_PreSnap_State_i  sPrevSnapState;//
	LONG lDebouncerTime;
	LONG lExpTime;

	LONG		  lTrigFreq;   //触发的频率
	LONG          lTrigImgCount; //触发一次，采集输出的图像帧数

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
* Description: 设备枚举
* Format:
*     HRESULT HV_EnumerateDevice(pHVGigE_Dev_i * pDev, int * nDevCount) ;
* Params:
*     pHVGigE_Dev_i * pDev: 获取的设备信息
*     int * nDevCount: 获取设备个数
* Return: 
*     HV_SUCCESS: 成功;   HV_NO_SUCH_DEVICE: 未找到
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_EnumerateDevice(pHVGigE_Dev_i * pDev, int * nDevCount);

/******************************************************************************
* Function:	HV_OpenDevice
* Description: 打开设备
* Format:
*     HRESULT HV_OpenDevice(int nDevId) ;
* Params:
*     int nId: 设备索引
* Return: 
*     HV_SUCCESS: 成功;   HV_NO_SUCH_DEVICE: 未找到
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_OpenDevice(int nDevId);

/******************************************************************************
* Function:	HV_DevCapInit
* Description: 设备捕捉初始化
* Format:
*     HRESULT HV_DevCapInit(int nDevId) ;
* Params:
*     void
* Return: 
*     HV_SUCCESS: 成功
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_DevCapInit(int nDevId, LPCSTR lpFileName = NULL);

/******************************************************************************
* Function:	HV_DevCapRelease
* Description: 资源释放
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
* Description: 设置回调函数
* Format:
*     HRESULT HV_SetCallBack(USER_CALLBACK_PROC pCallBack,int nDevId) ;
* Params:
*     USER_CALLBACK_PROC pCallBack: 回调函数地址
* Return: 
*     void
******************************************************************************/
HVGIGE_WP_API void    __stdcall HV_SetCallBack(USER_CALLBACK_PROC pCallBack,int nDevId);

/******************************************************************************
* Function:	HV_StartCapture
* Description: 开始图像捕获
* Format:
*     HRESULT HV_StartCapture(int nDevId) ;
* Params:
*     void
* Return: 
*     HV_SUCCESS: 成功
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_StartCapture(int nDevId);

/******************************************************************************
* Function:	HV_SuspendCapture
* Description: 挂起/恢复 Data Thread 和 Show Thread.
* Format:
*     HRESULT HV_SuspendCapture(BOOL bSuspend,int nDevId);
* Params:
*     BOOL bSuspend: 1 for capture and show suspend; 0 for capture and show resume;
* Return: 
*     HV_SUCCESS: 成功
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SuspendCapture(BOOL bSuspend,int nDevId);


/******************************************************************************
* Function:	HV_StopCapture
* Description: 停止图像捕获
* Format:
*     HRESULT HV_StopCapture(int nDevId) ;
* Params:
*     void
* Return: 
*     HV_SUCCESS: 成功
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_StopCapture(int nDevId);

/******************************************************************************
* Function:	HV_ShowControlPage
* Description: 打开控制属性对话框
* Format:
*     HRESULT HV_ShowControlPage(int nDevId) ;
* Params:
*     void
* Return: 
*     错误字符串
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_ShowControlPage(int nDevId);

/******************************************************************************
* Function:	HV_ShowRWPage
* Description: 打开读/写寄存器对话框
* Format:
*     HRESULT HV_ShowRWPage(int nDevId) ;
* Params:
*     void
* Return: 
*     错误字符串
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_ShowRWPage(int nDevId);

HVGIGE_WP_API HRESULT __stdcall HV_ShowSnapshotPage(int nDevId);

/******************************************************************************
* Function:	HV_GetFrameRate
* Description: 获取帧率
* Format:
*     HRESULT HV_GetFrameRate(double & nRate, int nDevId) ;
* Params:
*     double & nRate: 帧率
* Return: 
*     错误字符串
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetFrameRate(double & nRate, int nDevId);

/******************************************************************************
* Function:	HV_GetParamInfo
* Description: 获取参数信息
* Format:
*     HRESULT HV_GetParamInfo(int nType, PVOID* ppParamInfoStruct,int nDevId) ;
* Params:
*     int nType: 需获取信息的类型（VIDEO_INFO）
*     PVOID* ppParamInfoStruct: 获取的参数信息
* Return: 
*     错误字符串
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetParamInfo(int nType, PVOID* ppParamInfoStruct,int nDevId);

/******************************************************************************
* Function:	HV_GetFrameBuffer
* Description: 获取一帧图像数据
* Format:
*     HRESULT HV_GetFrameBuffer(long & lBufSize, LPBYTE * pBuf, int & nFrmWidth, int & nFrmHeight, int nDevId) ;
* Params:
*     long & lBufSize: 图像缓存大小
*     LPBYTE * pBuf: 图像缓存数据
*     int nFrmWidth: 图像宽
*     int nFrmHeight: 图像高
* Return: 
*     错误字符串
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetFrameBuffer(long & lBufSize, LPBYTE * pBuf, int & nFrmWidth, int & nFrmHeight, int nDevId);




/******************************************************************************
* Function:	HV_SaveImg
* Description: 保存一帧图像为.bmp文件
* Format:
*     HRESULT HV_SaveImg(LPBYTE pBuffer, LPCSTR lpFileName, const int nFrmWidth,
*						  const int nFrmHeight, const long lBufferSize, int nDevId)
* Params:
*     LPBYTE pBuffer: 图像数据Buffer指针
*     LPCTSTR lpFileName: 将要保存的bmp文件名
*     int nFrmWidth: 图像宽
*     int nFrmHeight: 图像高
*	  long lBufferSize: 图像数据Buffer的大小
* Return: 
*     出错时，返回错误字符串；否则，返回正确字串
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SaveImg(LPBYTE pBuffer, LPCSTR lpFileName, const int nFrmWidth,
										    const int nFrmHeight, const long lBufSize, int nDevId);


/******************************************************************************
* Function:	HV_GetErrorString
* Description: 获取错误字符串
* Format:
*     HRESULT HV_GetErrorString(LONG lError) ;
* Params:
*     LONG lError: 错误状态
* Return: 
*     错误字符串
******************************************************************************/
HVGIGE_WP_API CHAR*   __stdcall HV_GetErrorString(LONG lError);


/******************************************************************************
* Function:	HV_SetPreviewSnapMode()
* Description: 设置为连续预览(contionus)模式
* Format:
*     HRESULT HV_SetPreviewSnapMode(int nPreview, int nSnapMode)
* Params:
*		nPreview: 1 for preview mode; 
*				  0 for snapshot mode;
*		nSnapshot: snapshot mode, selected from 0 to 2, for both outer and inner
*				  trigger source.     
*
* Return: 
*     HV_SUCCESS: 成功
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetPreviewSnapMode(int nPreview, int nSnapMode,int nDevId);



/******************************************************************************
* Function:	HV_GetPreviewSnapMode()
* Description: 得到当前为Preview或Snapshot
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
*     HV_SUCCESS: 成功
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetPreviewSnapMode(HVGigE_PreSnap_State_i* psPreSnapState,int nDevId);

/******************************************************************************
* Function:	void HV_GetMaxResolution()
* Description: 获取CIS最大分辨率的宽、高
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
* Description: 设置图像的镜像方向，有三种方式：水平、竖直、水平竖直。
* Format:
*     HV_SetImageMirror(int nMirror,int nDevId)
* Params:
*	  int nMirror： 设置图像的镜像方向，有三种方式：水平、竖直、水平竖直。
*					RowMirror=1; ColumnMirror=2; both=3;
* Return:
*     HV_SUCCESS:成功；
*     HV_REASONLESS_PARAMETER:参数超出范围；
*     HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SetImageMirror(int nMirror,int nDevId);

/******************************************************************************
* Function:	HV_GetImageMirror()
* Description: 得到图像的镜像方式：水平、竖直、水平竖直。
* Format:
*     HV_GetImageMirror(int* pnMirror,int nDevId)
* Params:
*	  int* pnMirror: 返回当前的镜像方式。镜像方向，有三种方式：水平、竖直、水平竖直。
*					RowMirror=1; ColumnMirror=2; both=3;
* Return:
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetImageMirror(int* pnMirror,int nDevId);

//========================= Image Resolution Control ===========================================

/******************************************************************************
* Function:	HV_GetResolution
* Description: 获取视频的分辨率
* Format:
*     HRESULT HV_GetResolution(HVGigE_Video_i* psResolution,int nDevId)
* Params:
*	  HVGigE_Video_i* psResolution: 图像的分辨率(sResolution)的返回值
* Return:
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetResolution(HVGigE_Video_i* psResolution,int nDevId);

/******************************************************************************
* Function:	HV_SetResolution
* Description: 设置视频的分辨率
* Format:
*      HRESULT HV_SetResolution(HVGigE_Video_i sResolution, int nDevId)
* Params:
*	  HVGigE_Video_i sResolution：图像的分辨率(sResolution)
* Return:
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SetResolution(HVGigE_Video_i sResolution,int nDevId);

//========================= Image Color Control ===========================================
/******************************************************************************
* Function:	HV_GetImageColorStat()
* Description: 得到图像的彩色/灰度状态
* Format:
*     HV_GetImageColorStat(BOOL* pbColor,int nDevId)
* Params:
*	  BOOL* pbColor： 返回图像的彩色/灰度状态
* Return:
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetImageColorStat(BOOL* pbColor,int nDevId);

/******************************************************************************
* Function:	HV_SetImageColorStat()
* Description: 设置图像的彩色/灰度状态
* Format:
*     HV_SetImageColorStat(BOOL bColor, int nDevId)
* Params:
*	  BOOL bColor： 设置图像的彩色/灰度状态
* Return:
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SetImageColorStat(BOOL bColor, int nDevId);

//========================= Image Gamma Control ===========================================

/******************************************************************************
* Function:	HV_GetImageGammaStat()
* Description: 得到图像的Gamma状态
* Format:
*     HV_GetImageGammaStat(BOOL* pbGamma,int nDevId)
* Params:
*	  BOOL* pbColor： 返回图像的Gamma状态
* Return:
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetImageGammaStat(BOOL* pbGamma,int nDevId);

/******************************************************************************
* Function:	HV_SetImageGammaStat()
* Description: 设置图像的Gamma状态
* Format:
*     HV_SetImageGammaStat(BOOL bGamma, int nDevId)
* Params:
*	  BOOL bColor： 设置图像Gamma状态
* Return:
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SetImageGammaStat(BOOL bGamma, int nDevId);

//========================= Black Level Control ===========================================

/******************************************************************************
* Function:	HV_GetBlackLevelInfo
* Description: 获取BlackLevel参数信息
* Format:
*     HRESULT HV_GetBlackLevelInfo( HVGigE_Control_i* psBlackLevel,int nDevId)
* Params:
*	   HVGigE_Control_i* psBlackLevel: 返回sBlackLevel的参数值。
* Return:
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetBlackLevelInfo( HVGigE_Control_i* psBlackLevel,int nDevId);

/******************************************************************************
* Function:	HV_SetBlackLevelInfo
* Description: 设置BlackLevel参数信息
* Format:
*     HRESULT HV_SetParamInfo(HVGigE_Control_i sBlackLevel,int nDevId)
* Params:
*	  HVGigE_Control_i sBlackLevel: 将要设置的BlackLevel的参数
* Return:
*      none
*    
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetBlackLevelInfo(HVGigE_Control_i sBlackLevel,int nDevId);

/******************************************************************************
* Function:	HV_SetBlackLevelEnable
* Description: 设置BlackLevel.bEnable的值
* Format:
*     HRESULT HV_SetBlackLevelEnable(BOOL bbEnable,int nDevId)
* Params:
*	  BOOL bEnable: 将要设置的BlackLevel.bEnable的值
* Return:
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备  
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetBlackLevelEnable(BOOL bEnable,int nDevId);

/******************************************************************************
* Function:	HV_GetBlackLevelEnable
* Description: 获取BlackLevel.bEnable参数信息
* Format:
*     HRESULT HV_GetBlackLevelEnable(BOOL* pbEnable,int nDevId)
* Params:
*	  BOOL* pbEnable: BlackLevel.bEnable的值
* Return:
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备  
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetBlackLevelEnable(BOOL* pbEnable,int nDevId);

/******************************************************************************
* Function:	HV_SetBlackLevelAuto
* Description: 设置BlackLevel.bAuto的值
* Format:
*     HRESULT HV_SetBlackLevelAuto(BOOL bAuto,int nDevId)
* Params:
*	  BOOL bAuto: 将要设置的sBlackLevel.bAuto的值
* Return:
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备  
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetBlackLevelAuto(BOOL bAuto,int nDevId);


/******************************************************************************
* Function:	HV_GetBlackLevelAuto
* Description: 获取BlackLevel.bAuto的值
* Format:
*     HRESULT  HV_GetBlackLevelAuto(BOOL* pbAuto,int nDevId)
* Params:
*	  BOOL* pbAuto: BlackLevel.bAuto的返回值
* Return:
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备  
******************************************************************************/


HVGIGE_WP_API HRESULT __stdcall HV_GetBlackLevelAuto(BOOL* pbAuto,int nDevId);


/******************************************************************************
* Function:	HV_SetBlackLevelRange
* Description: 设置sBlackLevel.sRange的值
* Format:
*     HRESULT HV_SetBlackLevelRange(HVGigE_Range_i sRange,int nDevId)
* Params:
*	  HVGigE_Range_i sRange：BlackLevel的有效取值范围
* Return:
*      HV_INVALID_PARAM:无效的参数范围；
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备  
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetBlackLevelRange(HVGigE_Range_i sRange,int nDevId);


/******************************************************************************
* Function:	HV_GetBlackLevelRange
* Description: 获取BlackLevel的取值范围
* Format:
*     HRESULT  HV_GetBlackLevelRange(HVGigE_Range_i* psRange,int nDevId)
* Params:
*	  HVGigE_Range_i* psRange: BlackLevel的有效取值范围
* Return:
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetBlackLevelRange(HVGigE_Range_i* psRange,int nDevId);

/******************************************************************************
* Function:	HV_SetBlackLevelValue
* Description: 设置sBlackLevel.nValueArr[]的值,本函数仅改变sBlackLevel.nValueArr[1:4]。
* Format:
*     HRESULT HV_SetBlackLevelValue(int* pnValue,int nDevId)
* Params:
*	  int* pnValue: 将要设置的BlackLevel.nValue[]的值
* Return:
*      HV_INVALID_PARAM:无效的参数范围；
*	   HV_SUCCESS: 成功设置sBlackLevel.nValueArr[1:4]的值
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
*
* NOTE: just set the Black Value from sBlackLevel.nValueArr[1] to sBlackLevel.nValueArr[4],
*       Have done NOTHING to sBlackLevel.nValueArr[0]。
*    
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetBlackLevelValue(int* pnValue,int nDevId);


/******************************************************************************
* Function:	HV_GetBlackLevelValue
* Description: 获取BlackLevel.nValue的值
* Format:
*     HRESULT HV_GetBlackLevelValue(int* pnValueArr,int nDevId)
* Params:
*	  int* pnValueArr: 返回sBlackLevel.nValueArr[0:5]的值(BlackLevel.nValueArr[0:5])
* Return:
*	  HV_SUCCESS:操作成功
*     HV_NO_SUCH_DEVICE： 没有对应的硬件
*    
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetBlackLevelValue(int* pnValueArr,int nDevId);


//========================== Gain Control =========================================================

/******************************************************************************
* Function:	HV_GetGainInfo
* Description: 获取Gain的参数信息
* Format:
*     HRESULT HV_GetGainInfo(HVGigE_Control_i* psGain,int nDevId)
* Params:
*     HVGigE_Control_i* psGain: Gain的返回值
* Return:
*	  HV_SUCCESS:操作成功
*     HV_NO_SUCH_DEVICE： 没有对应的硬件
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetGainInfo(HVGigE_Control_i* psGain,int nDevId);

/******************************************************************************
* Function:	HV_SetGainInfo
* Description: 设置Gain参数信息
* Format:
*     HRESULT HV_SetGainInfo(HVGigE_Control_i sGain,int nDevId)
* Params:
*	  HVGigE_Control_i sGain: 将要设置的Gain的参数
* Return:
*      HRESULT hResult: 状态返回
*    
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetGainInfo(HVGigE_Control_i sGain,int nDevId);


/******************************************************************************
* Function:	HV_SetGainEnable
* Description: 设置sGain.bEnable的值
* Format:
*     HRESULT HV_SetGainEnable(BOOL bEnable,int nDevId)
* Params:
*	  bEnable: 将要设置的sGain.bEnable的值
* Return:
*	  HV_SUCCESS:操作成功
*     HV_NO_SUCH_DEVICE： 没有对应的硬件
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetGainEnable(BOOL bEnable,int nDevId);

/******************************************************************************
* Function:	HV_GetGainEnable
* Description: 获取sGain.bEnable的值
* Format:
*     HRESULT HV_GetGainEnable(BOOL* pbEnable,int nDevId)
* Params:
*	  BOOL* bEnable：返回的sGain.bEnable的值
* Return:
*	  HV_SUCCESS:操作成功
*     HV_NO_SUCH_DEVICE： 没有对应的硬件
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetGainEnable(BOOL* pbEnable,int nDevId);


/******************************************************************************
* Function:	HV_SetGainAuto
* Description: 设置sGain.bAuto的值
* Format:
*     HRESULT HV_SetGainAuto(BOOL bAuto,int nDevId)
* Params:
*	  BOOL bAuto: 将要设置的sGain.bAuto的值
* Return:
*	  HV_SUCCESS:操作成功
*     HV_NO_SUCH_DEVICE： 没有对应的硬件
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetGainAuto(BOOL bAuto,int nDevId);

/******************************************************************************
* Function:	HV_GetGainAuto
* Description: 获取sGain.bAuto的值
* Format:
*     HRESULT HV_GetGainAuto(BOOL* pbAuto,int nDevId)
* Params:
*	  BOOL* pbAuto：返回sGain.bAuto的值
* Return:
*	  HV_SUCCESS:操作成功
*     HV_NO_SUCH_DEVICE： 没有对应的硬件
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetGainAuto(BOOL* pbAuto,int nDevId);


/******************************************************************************
* Function:	HV_SetGainRange
* Description: 设置sGain.sRange的值
* Format:
*     HRESULT HV_SetGainRange(HVGigE_Range_i sRange,int nDevId)
* Params:
*     HVGigE_Range_i sRange: Gain的有效取值范围
* Return:
*      HV_INVALID_PARAM:无效的参数范围；
*	   HV_SUCCESS: 成功；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetGainRange(HVGigE_Range_i sRange,int nDevId);

/******************************************************************************
* Function:	HV_GetGainRange
* Description: 获取sGain.sRange的值
* Format:
*     HRESULT HV_GetGainRange(HVGigE_Range_i* psRange,int nDevId)
* Params:
*	  HVGigE_Range_i* psRange：sGain.sRange的返回值
* Return:
*	   HV_SUCCESS: 成功；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetGainRange(HVGigE_Range_i* psRange,int nDevId);



/******************************************************************************
* Function:	HV_SetGainValue
* Description: 设置sGain.nValue[0:4]的值
* Format:
*     HRESULT HV_SetGainValue(int* pnValueArr,int nDevId)
* Params:
*	  int* pValueArr: sGain.valueArr[0:4]的值
* Return:
*      HV_INVALID_PARAM:无效的参数范围；
*	   HV_SUCCESS: 成功设置Gain的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
* 
* NOTE: set gain value from sGain.nValue[0] to sGain.nValue[4].   
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetGainValue(int* pValueArr,int nDevId);

/******************************************************************************
* Function:	HV_GetGainValue
* Description: 获取sGain.nValue[0:4]的值
* Format:
*     HRESULT HV_GetGainValue(int* nValue,int nDevId)
* Params:
*	  int* nValue：返回sGain.nValueArr[0:4]的当前值，包括：
*				   Global Gain，G1 Gain，G2 Gain，R Gain, B Gain;
* Return:
*	   HV_SUCCESS: 成功设置Gain的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetGainValue(int* pnValue,int nDevId);

//======================== Exposure Control ======================================================

////////////////////////////////////////////////////////////////////////////////////
//			Exposure的参数设置与获取
//
/******************************************************************************
* Function:	HV_GetExposureInfo
* Description: 获取Exposure的参数信息
* Format:
*     HRESULT HV_GetExposureInfo(HVGigE_Control_i* psExposure,int nDevId)
* Params:
*	  HVGigE_Control_i* psExposur:返回Exposure的设置参数
* Return:
*	   HV_SUCCESS: 成功；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetExposureInfo(HVGigE_Control_i* psExposure,int nDevId);


/******************************************************************************
* Function:	HV_SetExposureInfo
* Description: 设置Exposure参数信息
* Format:
*     HRESULT HV_SetExposureInfo(HVGigE_Control_i sExposure,int nDevId)
* Params:
*	  HVGigE_Control_i sExposure: 将要设置的Exposure的参数信息
* Return:
*	   HV_SUCCESS: 成功；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetExposureInfo(HVGigE_Control_i sExposure,int nDevId);


/******************************************************************************
* Function:	HV_SetExposureEnable
* Description: 设置sExposure.bEnable的值
* Format:
*     HRESULT HV_SetExposureEnable(BOOL bEnable,int nDevId)
* Params:
*	  bEnable: 将要设置的sExposure.bEnable的值
* Return:
*	   HV_SUCCESS: 成功设置Gain的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetExposureEnable(BOOL bEnable,int nDevId);


/******************************************************************************
* Function:	HV_GetExposureEnable
* Description: 获取Exposure.bEnable参数信息
* Format:
*     BOOL HV_GetExposureEnable(BOOL* pbEnable,int nDevId)
* Params:
*	  BOOL* pbEnable: Exposure.bEnable的状态
* Return:
*	   HV_SUCCESS: 成功设置Gain的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetExposureEnable(BOOL* pbEnable,int nDevId);



/******************************************************************************
* Function:	HV_SetExposureAuto
* Description: 设置Exposure.bAuto的值
* Format:
*     HRESULT HV_SetExposureAuto(BOOL bAuto,int nDevId)
* Params:
*	  BOOL bAuto: 将要设置的sExposure.bAuto的值
* Return:
*	   HV_SUCCESS: 成功；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetExposureAuto(BOOL bAuto,int nDevId);


/******************************************************************************
* Function:	HV_GetExposureAuto
* Description: 获取sExposure.bAuto的值
* Format:
*     HRESULT HV_GetExposure.bAuto(BOOL* pbAuto,int nDevId)
* Params:
*	  BOOL* pbAuto: sExposure.bAuto的值
* Return:
*	   HV_SUCCESS: 成功；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetExposureAuto(BOOL* pbAuto,int nDevId);


/******************************************************************************
* Function:	HV_SetExposureRange
* Description: 设置Exposure的有效取值范围，sExposure.sRange的值
* Format:
*     HRESULT HV_SetExposureRange(HVGigE_Range_i sRange,int nDevId)
* Params:
*	  HVGigE_Range_i sRange：Exposure的有效取值范围，sExposure.sRange的值
* Return:     
*      HV_INVALID_PARAM: 参数不在有效范围之内；
*	   HV_SUCCESS: 成功设置Exposure的范围
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetExposureRange(HVGigE_Range_i sRange,int nDevId);

/******************************************************************************
* Function:	HV_GetExposureRange
* Description: 获取Exposure的有效取值范围,sExposre.sRange的值
* Format:
*     HRESULT  HV_GetExposureRange(HVGigE_Range_i* psRange,int nDevId)
* Params:
*	  HVGigE_Range_i* psRange: Exposure的有效取值范围，sExposure.sRange的值
* Return:
*	   HV_SUCCESS: 成功设置Exposure的范围
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetExposureRange(HVGigE_Range_i* psRange,int nDevId);


/******************************************************************************
* Function:	HV_SetExposureValue
* Description: 设置Exposure.nValue的值
* Format:
*     HRESULT HV_SetExposureValue(int nValue,int nDevId)
* Params:
*	  nValue: Exposure的值(Exposure.nValue),单位为行数；
* Return:
*      HV_INVALID_PARAM: 参数不在有效范围之内；
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetExposureValue(int nValue,int nDevId);


/******************************************************************************
* Function:	HV_GetExposureValue
* Description: 获取Exposure.nValue的值
* Format:
*     HRESULT HV_GetExposureValue(int* pnValue,int nDevId)
* Params:
*	  int* pnValue:  Exposure的当前值(Exposure.nValue的值)，单位为行数
* Return:
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetExposureValue(int* pnValue,int nDevId);


//======================== Snapshot Control ======================================================
///////////////////////////////////////////////////////////////////////////////////
//		Snapshot 的参数设置与获取
//

/******************************************************************************
* Function:	HV_GetSnapInfo
* Description: 获取Exposure的参数信息
* Format:
*     HRESULT HV_GetSnapInfo(HVGigE_SnapControl_i* psSnapControl, int nDevId)
* Params:
*	  HVGigE_SnapControl_i* psSnapControl: Snapshot的设置参数
* Return:
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetSnapInfo(HVGigE_SnapControl_i* psSnapControl, int nDevId);


/******************************************************************************
* Function:	HV_SetSnapInfo
* Description: 设置Snapshot参数信息
* Format:
*     HRESULT HV_SetSnapInfo(HVGigE_SnapControl_i sSnap, int nDevId)
* Params:
*	  HVGigE_SnapControl_i sSnap: 将要设置的Snapshot的参数
* Return:
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetSnapInfo(HVGigE_SnapControl_i sSnap, int nDevId);

/******************************************************************************
* Function:	HV_SetSnapDebounceTime()
* Description: 设置拍照模式时，去抖动时间(DebouncerTime)，时间单位为us.
* Format:
*     HRESULT HV_SetSnapDebounceTime(const LONG lDebouncerTime,int nDevId)
* Params:
*	 LONG lDebouncerTime: 去抖动时间，单位为us
* Return:
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetSnapDebounceTime(const LONG lDebouncerTime,int nDevId);


/******************************************************************************
* Function:	HV_GetSnapDebounceTime()
* Description: 获取拍照模式时，去抖动时间(DebouncerTime)，时间单位为us.
* Format:
*     LONG HV_GetSnapDebounceTime(LONG *plDebouncerTime,int nDevId)
* Params:
*	  LONG lDebouncerTime: 返回去抖动时间，单位为us
* Return:
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetSnapDebounceTime(LONG *plDebouncerTime,int nDevId);



/******************************************************************************
* Function:	HV_SetSnapExpTime()
* Description: 设这拍照模式时，曝光时间(ExposureTime)，时间单位为us.
* Format:
*     HV_SetSnapExpTime(const LONG lExpTime,int nDevId)
* Params:
*	  LONG lExpTime：曝光时间，单位为us
* Return:
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetSnapExpTime(const LONG lExpTime,int nDevId);



/******************************************************************************
* Function:	HV_GetSnapExpTime()
* Description: 获得拍照模式时，曝光时间(ExposureTime)，时间单位为us.
* Format:
*     LONG HV_GetSnapExpTime(LONG* plExpTime,int nDevId) 
* Params:
*	 LONG* plExpTime：返回曝光时间，单位为微秒
* Return:
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetSnapExpTime(LONG* plExpTime,int nDevId);

/******************************************************************************
* Function:	HV_GetSnapExpTimeRange(HVGigE_Range_i* psRange)
* Description: 设置拍照模式时，曝光时间(ExposureTime)的有效值范围.时间单位为us.
* Format:
*     HResult HV_GetSnapExpTimeRange(HVGigE_Range_i* psRange,int nDevId)
* Params:
*	 HVGigE_Range_i* psRange：返回曝光时间有效值的范围，单位为微秒
* Return:
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetSnapExpTimeRange(HVGigE_Range_i* psRange,int nDevId);

/******************************************************************************
* Function:	HV_GetTrigFreqRange(HVGigE_Range_i* psRange,int nDevId)
* Description: 设置拍照模式时，触发频率的有效值范围.
* Format:
*     HResult HV_GetTrigFreqRange(HVGigE_Range_i* psRange,int nDevId)
* Params:
*	 HVGigE_Range_i* psRange：设置拍照模式时，触发频率的有效值范围
* Return:
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetTrigFreqRange(HVGigE_Range_i* psRange,int nDevId);


/******************************************************************************
* Function:	HV_GetTrigImgCountRange(HVGigE_Range_i* psRange)
* Description: 设置拍照模式时，触发频率的有效值范围.
* Format:
*     HResult HV_GetTrigImgCountRange(HVGigE_Range_i* psRange,int nDevId)
* Params:
*	 HVGigE_Range_i* psRange：设置拍照模式时，连续拍照张数的有效值范围
* Return:
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetTrigImgCountRange(HVGigE_Range_i* psRange,int nDevId);

/******************************************************************************
* Function:	HV_SetPreviewSnapMode()
* Description: 设置为连续预览(contionus)模式
* Format:
*     HRESULT HV_SetPreviewSnapMode(int nPreview, int nSnapMode,int nDevId)
* Params:
*		nPreview: 1 for preview mode; 
*				  0 for snapshot mode ; 
*		nSnapshot: snapshot mode, selected from 0 to 2, for both outer and inner
*				  trigger source.     
*
* Return: 
*     HV_SUCCESS: 成功
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetPreviewSnapMode(int nPreview, int nSnapMode,int nDevId);


/******************************************************************************
* Function:	HV_GetPreviewSnapMode()
* Description: 得到当前为Preview或Snapshot
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
*     HV_SUCCESS: 成功
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetPreviewSnapMode(HVGigE_PreSnap_State_i* psPreSnapState);

/******************************************************************************
* Function:	HV_SetSnapTrigFreqImgCount()
* Description: 设置拍照模式时，触发的频率以及每次触发输出的图像张数
* Format:
*     HRESULT HV_SetSnapTrigFreqImgCount(LONG lTrigFreq, LONG lTrigImgCount,int nDevId)
* Params:
*	 LONG lTrigFreq: 设置拍照模式时，(闪光灯）的触发频率。单位为每秒的帧数。
*    LONG lTrigImgCount：触发一次，连续输出的图像帧数
* Return:
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT HV_SetSnapTrigFreqImgCount(LONG lTrigFreq, LONG lTrigImgCount,int nDevId);

/******************************************************************************
* Function:	HV_GetSnapTrigFreqImgCount()
* Description: 返回拍照模式时，触发的频率以及每次触发输出的图像张数
* Format:
*     HRESULT HV_GetSnapTrigFreqImgCount(LONG* plTrigFreq, LONG* plTrigImgCount,int nDevId)
* Params:
*	 LONG* plTrigFreq: 设置拍照模式时，(闪光灯）的触发频率。单位为每秒的帧数。
*    LONG* plTrigImgCount：触发一次，连续输出的图像帧数
* Return:
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT HV_GetSnapTrigFreqImgCount(LONG* plTrigFreq, LONG* plTrigImgCount,int nDevId);


/******************************************************************************
* Function:	void HV_GetMaxResolution()
* Description: 获取CIS最大分辨率的宽、高
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
* Description: 将参数保存到ini文件
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
* Description: 使用ini文件中的参数，配置相机
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
* Description: 设置拍照模式(snapshot)下，相机IO控制模式；
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
*     HV_SUCCESS: 成功
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_SetSnapIOMode(HVGigE_SnapIO_Mode_i sSnapIOMode,int nDevId);

/******************************************************************************
* Function:	HV_GetSnapIOMode()
* Description: 返回拍照模式(snapshot)下，相机IO控制模式；
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
*     HV_SUCCESS: 成功
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetSnapIOMode(HVGigE_SnapIO_Mode_i* psSnapIOMode,int nDevId);

/******************************************************************************
* Function:	HV_GetRawData(HVGigE_Img_i* pRawFrameInfo)
* Description: 返回RawData数据；
* Format:
*     HRESULT HV_GetRawData(HVGigE_Img_i* pRawFrameInfo,int nDevId)
* Params:
*		HVGigE_Img_i* pRawFrameInfo:  RawData 信息
*		pRawFrameInfo->nImgHeight: 图像的高
*		pRawFrameInfo->nImgWidth：图像的宽
*		pRawFrameInfo->nBitCount：每个图像像素所占的字节数, 值为1
*		pRawFrameInfo->pDataBuffer：指向RawData 图像数据Buffer的指针	
*
* Return: 
*     HV_SUCCESS: 成功
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetRawData(HVGigE_Img_i* pRawFrameInfo,int nDevId);


/*****************************************************************************
* Function:	HV_GetRGBData(HVGigE_Img_i* pRGBFrameInfo)
* Description: 返回RGB数据；
* Format:
*     HRESULT HV_GetRGBData(HVGigE_Img_i* pRGBFrameInfo,int nDevId)
* Params:
*		HVGigE_Img_i* pRawFrameInfo:  RawData 信息
*		pRGBFrameInfo->nImgHeight: 图像的高
*		pRGBFrameInfo->nImgWidth：图像的宽
*		pRGBFrameInfo->nBitCount：每个图像像素所占的字节数，值为3
*		pRGBFrameInfo->pDataBuffer：指向RGB图像数据Buffer的指针	
*
* Return: 
*     HV_SUCCESS: 成功
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_GetRGBData(HVGigE_Img_i* pRGBFrameInfo,int nDevId);


/******************************************************************************
* Function:	HV_SnapSWTrigger()
* Description: Snapshot模式时，单击 sw Trigger(软件触发)的响应函数
* Format:
*     void HV_SnapSWTrigger()
* Params:
*     void
* Return: 
*     HV_SUCCESS: 成功
*     HV_UNSUCCESS: 失败
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall	HV_SnapSWTrigger(int nDevId);

/******************************************************************************
* Function:	HV_CloseDevice
* Description: 关闭相机并释放资源
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
* Description: 设置视频的ROI(Region of Interest)
* Format:
*      HRESULT HV_SetROI(int Original_x, int Original_y,
*						int nImgWidth, int nImgHeight,int nDevId)
* Params:
*	  int Oringination_x: ROI的起始点x坐标
*	  int Oringination_y: ROI的起始点y坐标
*     int nImgWidth: ROI的宽度
*     int nImgHeight: ROI的高度
*     int nDevId: 设备索引号
* Return:
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SetROI(int Original_x, int Original_y, 
										  int nImgWidth, int nImgHeight,int nDevId);

/******************************************************************************
* Function:	HV_SetResolutionMode
* Description: 设置分辨率模式
* Format:
*     HRESULT HV_SetResolutionMode(HVGige_Resolution Res_Mode, int nDevId) ;
* Params:
*     HVGige_Resolution Res_Mode 分辨率模式
*	  int nDevId  设备索引号
* Return: 
*     HV_SUCCESS  成功
******************************************************************************/
HVGIGE_WP_API HRESULT __stdcall HV_SetResolutionMode(HVGige_Resolution Res_Mode, int nDevId);

/******************************************************************************
* Function:	HV_GetImageChannel
* Description: 获取图像的通道数，为1或者3
* Format:
*     HRESULT HV_GetImageChannel(int& nChannel,int nDevId)
* Params:
*	  int& nBitCount: 图像通道数的返回值
* Return:
*	   HV_SUCCESS: 成功
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

HVGIGE_WP_API HRESULT __stdcall HV_GetImageChannel(int& nChannel,int nDevId);

