
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the INDCAM_LABVIEW_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// INDCAM_LABVIEW_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.


#ifdef INDCAM_LABVIEW_EXPORTS
#define INDCAM_LABVIEW_API __declspec(dllexport)
#else
#define INDCAM_LABVIEW_API __declspec(dllimport)
#endif

/******************************************************************************
* Function:	HV_LabVIEWCapInit
* Description: 打开设备，初始化设备，设置设备的回调函数。
* Format:
*     int HV_LabVIEWCapInit(int nDevId)
* Params:
*     int nDevId: 设备索引号
*	  LPCSTR lpFileName   指定配置文件路径（默认为空，即默认的配置路径在当前路径下）
* Return: 
*     HV_SUCCESS: 成功
*     HVOCX_INVALID_PARAM: 无效参数
*     HVOCX_DEVICE_OPEN_FAIL: 打开设备失败
*	  HVOCX_DEVICE_INI_FAIL： 初始化设备失败
*	  HVOCX_GET_PARAMINFO_FAIL： 获取参数失败
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWCapInit(int nDevId, LPCSTR lpFileName=NULL);


/******************************************************************************
* Function:	HV_LabVIEWStartCapture
* Description: 开始图像捕获
* Format:
*     int HV_LabVIEWStartCapture(int nDevId)
* Params:
*     int nDevId: 设备索引号
* Return: 
*     HV_SUCCESS: 成功
*     HVOCX_INVALID_PARAM: 无效参数
*     HVOCX_DEVICE_START_FAIL: 开启设备失败
******************************************************************************/
INDCAM_LABVIEW_API BOOL _stdcall HV_LabVIEWStartCapture(int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWStopCapture
* Description: 停止图像捕获
* Format:
*     int HV_LabVIEWStopCapture(int nDevId);
* Params:
*     int nDevId: 设备索引号
* Return: 
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*     HVOCX_DEVICE_STOP_FAIL: 停止设备失败
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWStopCapture(int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetImageData
* Description: 获取一帧的图像数据，并存入数据缓存
* Format:
*     int HV_LabVIEWGetImageData(int* pData, int nWidth, int nHeight, int nDevId)
* Params:
*     int* pData: 指向图像数据缓存的指针，图像缓存的大小为：nWidth*nHeight
*     int nWidth: 图像宽度
*	  int nHeight: 图像高度
*    int   nDevId: 设备索引号
* Return: 
*     HV_SUCCESS: 成功
*     HVOCX_INVALID_PARAM: 无效参数
* 	  HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetImageData(int* pData, int nWidth, int nHeight, int nDevId);



/******************************************************************************
* Function:	HV_LabVIEWGetFrameRate
* Description: 获取当前的帧率
* Format:
*     double HV_LabVIEWGetFrameRate(int nDevId)
* Params:
*    int   nDevId: 设备索引号
* Return: 
*     
*	  成功，返回帧率；
*	  否则，返回HVOCX_INVALID_PARAM，无效参数
******************************************************************************/
INDCAM_LABVIEW_API double _stdcall HV_LabVIEWGetFrameRate(int nDevId);




/******************************************************************************
* Function:	HV_LabVIEWGetImageWidth
* Description: 获取当前分辨率下，图像的宽度
* Format:
*     int HV_LabVIEWGetImageWidth(int* pnImgWidth，int nDevId)
* Params: 
*		   int* pnImgWidth: 指向图像宽度的指针。输出参数。
*		   int nDevID: 相机索引号。
* Return: 
*     HV_SUCCESS: 成功
*     HVOCX_INVALID_PARAM: 无效参数
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetImageWidth(int* pnImgWidth, int nDevId);
/******************************************************************************
* Function:	HV_LabVIEWGetImageChannels
* Description: 获取当前分辨率下，图像的通道数
* Format:
*     int HV_LabVIEWGetImageChannels(int* pnImgBitCount, int nDevId)
* Params: 
*		   int nDevID: 相机索引号。
*		   int* pnChannels: 指向图像通道数的指针。输出参数。
* Return: 
*     HV_SUCCESS: 成功
*     HVOCX_INVALID_PARAM: 无效参数
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetImageChannels(int* pnChannels, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWGetImageHeight
* Description: 获取当前分辨率下，图像的高度
* Format:
*     int HV_LabVIEWGetImageHeight(int* pnImgHeight, int nDevId)
* Params: 
*		   int nDevID: 相机索引号。
*		   int* pnImgWidth: 指向图像宽度的指针。输出参数。
* Return: 
*     HV_SUCCESS: 成功
*     HVOCX_INVALID_PARAM: 无效参数
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetImageHeight(int* pnImgHeight, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWCtrlPage
* Description: 显示控制属性页
* Format:
*     int HV_LabVIEWCtrlPage(int nDevId)
* Params: 
*	  int nDevID: 相机索引号。
* Return: 
*     HV_SUCCESS: 成功
*     HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SHOW_CONTROL_PAGE_FAIL：显示属性页失败
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWCtrlPage(int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWCapRelease
* Description: 释放资源
* Format:
*		   void  HV_LabVIEWCapRelease(int nDevId)
* Params: 
*		   int nDevID: 相机索引号。
* Return: 
*		   void
******************************************************************************/
INDCAM_LABVIEW_API void _stdcall HV_LabVIEWCapRelease(int nDevId);

/******************************************************************************
* Function:	HV_ShowSnapshotPage
* Description: 打开拍照对话框
* Format:
*     int _stdcall HV_LabVIEWSnapPage(int nDevId)
* Params:
*    int   nDevId: 设备索引号
* Return: 
*     HV_SUCCESS
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SHOW_CONTROL_PAGE_FAIL：显示属性页失败
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSnapPage(int nDevId);



/******************************************************************************
* Function:	int HV_LabVIEWSaveParaToIniFile()
* Description: 将参数保存到ini文件
* Format:
*     int HV_LabVIEWSaveParaToIniFile(int nDevId)
*	  LPCSTR lpFileName   指定配置文件路径（默认为空，即默认的配置路径在当前路径下）
* Params:
*    int   nDevId: 设备索引号
* Return: 
*	  HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SAVE_CONFIGURATION_FAIL: 保存相机配置失败
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSaveParaToIniFile(int nDevId, LPCSTR lpFileName=NULL);


/******************************************************************************
* Function:	int HV_LabVIEWIniCamFromIniFile()
* Description: 使用ini文件中的参数，配置相机
* Format:
*     int  HV_LabVIEWIniCamFromIniFile()
*	  LPCSTR lpFileName   指定配置文件路径（默认为空，即默认的配置路径在当前路径下）
* Params:
*    int   nDevId: 设备索引号
* Return: 
*	  HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWIniCamFromIniFile(int nDevId, LPCSTR lpFileName=NULL);


/******************************************************************************
* Function: HV_LabVIEWSnapSWTrigger()
* Description: Snapshot模式时，单击 sw Trigger(软件触发)的响应函数
* Format:
*     int HV_LabVIEWSnapSWTrigger(int nDevId)
* Params:
*    int   nDevId: 设备索引号
* Return: 
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*     HVOCX_SOFTWARE_TRIGGER_FAIL：软件触发失败
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSnapSWTrigger(int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWGetImageColorStat()
* Description: 得到图像的彩色/灰度状态
* Format:
*     int HV_LabVIEWGetImageColorStat(BOOL* pbColor, int nDevId)
* Params:
*	  BOOL* pbColor： 返回图像的彩色/灰度状态
*     int nDevId:  设备索引号
* Return:
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HVOCX_INVALID_PARAM: 无效参数；
*	   HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetImageColorStat(BOOL* pbColor, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetImageColorStat()
* Description: 设置图像的彩色/灰度状态
* Format:
*     int HV_LabVIEWSetImageColorStat(BOOL bColor, int nDevId)
* Params:
*	  BOOL bColor： 设置图像的彩色/灰度状态
*     int nDevId:  设备索引号
* Return:
*	   HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL: 设置参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSetImageColorStat(BOOL bColor, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetSnapDebounceTime()
* Description: 获取拍照模式时，去抖动时间(DebouncerTime)，时间单位为us.
* Format:
*     int HV_LabVIEWGetSnapDebounceTime(int* plDebouncerTime, int nDevId)
* Params:
*	  int* plDebouncerTime: 返回去抖动时间，单位为us
*	  int  nDevId: 设备索引号
* Return:
*	   HV_SUCCESS: 成功；
*      HVOCX_INVALID_PARAM: 无效参数；
*	   HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetSnapDebounceTime(int* plDebouncerTime, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetSnapDebounceTime()
* Description: 设置拍照模式时，去抖动时间(DebouncerTime)，时间单位为us.
* Format:
*     int HV_LabVIEWSetSnapDebounceTime(int lDebouncerTime, int nDevId)
* Params:
*	 int lDebouncerTime: 去抖动时间，单位为us
*	 int  nDevId: 设备索引号
* Return:
*	   HV_SUCCESS: 成功；
*      HVOCX_INVALID_PARAM: 无效参数；
*	   HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSetSnapDebounceTime(int lDebouncerTime, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetSnapDebounceTime()
* Description: 获取拍照模式时，去抖动时间(DebouncerTime)，时间单位为us.
* Format:
*     int HV_LabVIEWGetSnapDebounceTime(int* plExpTime, int nDevId)
* Params:
*	  int* plDebouncerTime: 返回去抖动时间，单位为us
*	  int  nDevId: 设备索引号
* Return:
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetSnapExpTime(int* plExpTime, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetSnapExpTime()
* Description: 设置拍照模式时，曝光时间(ExposureTime)，时间单位为us.
* Format:
*     int HV_LabVIEWSetSnapExpTime(int lExpTime, int nDevId)
* Params:
*	  int lExpTime：曝光时间，单位为us
*     int   nDevId: 设备索引号
* Return:
*	   HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSetSnapExpTime(int lExpTime, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetSnapExpTime()
* Description: 设这拍照模式时，曝光时间(ExposureTime)，时间单位为us.
* Format:
*     HV_LabVIEWSetSnapExpTime(int lExpTime, int nDevId)
* Params:
*	  int lExpTime：曝光时间，单位为us
*     int   nDevId: 设备索引号
* Return:
*	   HV_SUCCESS: 成功设置Exposure的值；
*      HV_NO_SUCH_DEVICE: 没有找到对应的硬件设备
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSetSnapExpTime(int lExpTime, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetSnapTrigFreqImgCount()
* Description: 获取拍照模式时，触发的频率以及每次触发输出的图像张数
* Format:
*     int HV_LabVIEWGetSnapTrigFreqImgCount(int* plTrigFreq, int* plTrigImgCount, int nDevId)
* Params:
*	 int* plTrigFreq: 设置拍照模式时，(闪光灯）的触发频率。单位为每秒的帧数。
*    int* plTrigImgCount：触发一次，连续输出的图像张数
*    int   nDevId: 设备索引号
* Return:
*	   HV_SUCCESS: 成功
*      HVOCX_INVALID_PARAM: 无效参数
*	   HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetSnapTrigFreqImgCount(int* plTrigFreq, int* plTrigImgCount, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetSnapTrigFreqImgCount()
* Description: 设置拍照模式时，触发的频率以及每次触发输出的图像张数
* Format:
*     int HV_LabVIEWSetSnapTrigFreqImgCount(int lTrigFreq, int lTrigImgCount, int nDevId)
* Params:
*	 int lTrigFreq: 设置拍照模式时，(闪光灯）的触发频率。单位为每秒的帧数。
*    int lTrigImgCount：触发一次，连续输出的图像帧数
*    int   nDevId: 设备索引号
* Return:
*	  HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSetSnapTrigFreqImgCount(int lTrigFreq, int lTrigImgCount, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetTrigFreqRange()
* Description: 获取拍照模式时，触发的频率的有效范围
* Format:
*     int HV_LabVIEWGetTrigFreqRange(int* pnRangeMin, int* pnRangeMax, int nDevId)
* Params:
*	 int* pnRangeMin: 拍照模式时，(闪光灯）的触发频率的最小值；
*    int* pnRangeMax：拍照模式时，(闪光灯）的触发频率的最大值；
*    int   nDevId: 设备索引号
* Return:
*	   HV_SUCCESS: 成功
*      HVOCX_INVALID_PARAM: 无效参数
*	   HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetTrigFreqRange(int* pnRangeMin, int* pnRangeMax, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetSnapIOMode()
* Description: 设置拍照模式(snapshot)下，相机IO控制模式；
* Format:
*     int HV_LabVIEWSetSnapIOMode(int nInMode, int nOutMode, int nDevId)
* Params:
*		int nInMode:  0 for falling-edge valid trigger; 
*							  1 for rising-edge valide trigger;
*							  2 for low-level valid trigger;
*							  3 for high-level valid trigger;
*		int nOutMode: 0 for low-level output;
*							  1 for high-level output;  
*       int   nDevId: 设备索引号
*
* Return: 
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSetSnapIOMode(int nInMode, int nOutMode, int nDevId);



/******************************************************************************
* Function:	HV_LabVIEWGetSnapIOMode()
* Description: 返回拍照模式(snapshot)下，相机IO控制模式；
* Format:
*     int HV_LabVIEWGetSnapIOMode(int* pnInMode, int* pnOutMOde, int nDevId)
* Params:
*	  int* pnInMode:  0 for falling-edge valid trigger; 
*								1 for rising-edge valide trigger;
*								2 for low-level valid trigger;
*								3 for high-level valid trigger;
*	  int* pnOutMode: 0 for low-level output;
*								1 for high-level output;  
*     int   nDevId: 设备索引号
*
* Return: 
*      HV_SUCCESS: 成功
*      HVOCX_INVALID_PARAM: 无效参数；
*	   HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetSnapIOMode(int* pnInMode, int* pnOutMOde, int nDevId);


/******************************************************************************
* Function:	HV_GetPreviewSnapMode()
* Description: 得到当前为Preview或Snapshot
* Format:
*     int HV_LabVIEWGetPreviewSnapMode(int* pnPreview, int* pnSnapMode, int nDevId)
* Params:
*		int* pnPreview: 1 for preview mode; 0 for snapshot mode;
*		int* pnSnapshot: snapshot mode, selected from 0 to 2;  
*					  *pnPreview = 1, *pnSnapMode=0, for preview;  
*					  *pnPreview = 0, *pnSnapMode=0-2, for snapshot of outer trigger source;
*		int nDevId: 设备索引号；
*
* Return: 
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetPreviewSnapMode(int* pnPreview, int* pnSnapMode, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetPreviewSnapMode()
* Description: 设置为连续预览(contionus)模式
* Format:
*     int HV_LabVIEWSetPreviewSnapMode(int nPreview, int nSnapMode, int nDevId)
* Params:
*		nPreview: 1 for preview mode; 
*				  0 for snapshot mode;
*		nSnapshot: snapshot mode, selected from 0 to 2, for both outer and inner
*				  trigger source.     
*    int   nDevId: 设备索引号
* Return: 
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetPreviewSnapMode(int nPreview, int nSnapMode, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWDeviceClose
* Description: 关闭相机并释放资源
* Format:
*     int HV_LabVIEWDeviceClose(int nDevId) ;
* Params:
*    int   nDevId: 设备索引号
* Return: 
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWDeviceClose( int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWAllocation
* Description: 重新分配内存
* Format:
*     int HV_LabVIEWAllocation(int nWidth, int nHeight, int nDevId) ;
* Params:
*    int   nDevId: 设备索引号
* Return: 
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWAllocation( int nWidth, int nHeight, int nDevId);



//========================= Black Level Control ===========================================

/******************************************************************************
* Function:	HV_LabVIEWGetBlackLevelInfo
* Description: 获取BlackLevel参数信息
* Format:
*     int HV_LabVIEWGetBlackLevelInfo( BOOL* pbEnable, BOOL* pbAuto, int* pnRangeMin, int* pnRangeMax,
									   int* pnG1Val, int* pnG2Val, int* pnRVal, int* pnBVal,int nDevId)
* Params:
*	   BOOL* pbEnable: 使能状态。输出参数。TRUE为Enable，FALSE为Disable；
*	   BOOL* pbAuto; 自动/手动状态。输出参数。TRUE为Auto，FALSE为Manual；
*	   int* pnRangeMin: 取值范围的最小值。输出参数。
*      int* pnRangeMax: 取值范围的最大值。输出参数。
*	   int* pnG1Val: G1通道的BlackLevel值。输出参数。
*      int* pnG2Val: G2通道的BlackLevel值。输出参数。
*	   int* pnRVal： R通道的BlackLevel值。输出参数。
*      int* pnBVal:  B通道的BlackLevle值。输出参数。
*    int   nDevId: 设备索引号
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetBlackLevelInfo( BOOL* pbEnable, BOOL* pbAuto, int* pnRangeMin, int* pnRangeMax,
															 int* pnG1Val, int* pnG2Val, int* pnRVal, int* pnBVal,int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetBlackLevelInfo
* Description: 设置BlackLevel参数信息
* Format:
*     int HV_LabVIEWSetBlackLevelInfo( BOOL bEnable, BOOL bAuto, int nRangeMin, int nRangeMax,
									   int nG1Val, int nG2Val, int nRVal, int nBVal,int nDevId)
* Params:
*	   BOOL bEnable: 使能状态。输入参数。TRUE为Enable，FALSE为Disable；
*	   BOOL bAuto; 自动/手动状态。输入参数。TRUE为Auto，FALSE为Manual；
*	   int  nRangeMin: 取值范围的最小值。输入参数。最小值不能小于-255。
*      int  nRangeMax: 取值范围的最大值。输入参数。最大值不能大于255。
*	   int  nG1Val: G1通道的BlackLevel值。输入参数。
*      int  nG2Val: G2通道的BlackLevel值。输入参数。
*	   int  nRVal： R通道的BlackLevel值。输入参数。
*      int  nBVal:  B通道的BlackLevle值。输入参数。
*      int   nDevId: 设备索引号
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetBlackLevelInfo( BOOL bEnable, BOOL bAuto, int nRangeMin, int nRangeMax,
															 int nG1Val, int nG2Val, int nRVal, int nBVal,int nDevId);

/******************************************************************************
* Function:	HV_GetBlackLevelValue
* Description: 获取BlackLevel的值
* Format:
*     int HV_LabVIEWGetBlackLevelValue(int* pnG1Value, int* pnG2Value, int* pnRValue, int* pnBValue, int nDevId)
* Params:
*	   int* pnG1Val: G1通道的BlackLevel值。输出参数。
*      int* pnG2Val: G2通道的BlackLevel值。输出参数。
*	   int* pnRVal： R通道的BlackLevel值。输出参数。
*      int* pnBVal:  B通道的BlackLevle值。输出参数。
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetBlackLevelValue(int* pnG1Value, int* pnG2Value, 
															  int* pnRValue, int* pnBValue, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetBlackLevelValue
* Description: 设置Exposure的值
* Format:
*     int HV_LabVIEWSetBlackLevelValue(int nG1Val, int nG2Val, int nRVal,
*															 int nBVal,int nDevId)
* Params:
*	   int  nG1Val: G1通道的BlackLevel值。输入参数。
*      int  nG2Val: G2通道的BlackLevel值。输入参数。
*	   int  nRVal： R通道的BlackLevel值。输入参数。
*      int  nBVal:  B通道的BlackLevle值。输入参数。
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetBlackLevelValue(int nG1Val, int nG2Val, int nRVal,
															 int nBVal,int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetExposureInfo
* Description: 获取曝光(Exposure)参数信息
* Format:
*     int HV_LabVIEWGetExposureInfo( BOOL* pbEnable, BOOL* pbAuto, int* pnRangeMin, int* pnRangeMax,
															 int* pnExpsoureVal,int nDevId)
* Params:
*	   BOOL* pbEnable: 使能状态。输出参数。TRUE为Enable，FALSE为Disable；
*	   BOOL* pbAuto; 自动/手动状态。输出参数。TRUE为Auto，FALSE为Manual；
*	   int* pnRangeMin: 取值范围的最小值。输出参数。
*      int* pnRangeMax: 取值范围的最大值。输出参数。
*	   int* pnExpsoureVal:  曝光值，单位为行数。输出参数。
*      int  nDevId: 设备索引号
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetExposureInfo( BOOL* pbEnable, BOOL* pbAuto, int* pnRangeMin, int* pnRangeMax,
															 int* pnExposureVal,int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetExposureInfo
* Description: 设置曝光(Exposure)的参数信息
* Format:
*     int HV_LabVIEWSetExposureInfo( BOOL bEnable, BOOL bAuto, int nRangeMin, int nRangeMax,
															 int nExpsoureVal,int nDevId)
* Params:
*	   BOOL bEnable: 使能状态。输入参数。TRUE为Enable，FALSE为Disable；
*	   BOOL bAuto; 自动/手动状态。输入参数。TRUE为Auto，FALSE为Manual；
*	   int  nRangeMin: 取值范围的最小值。输入参数。输入任意值，自动计算最小值。
*      int  nRangeMax: 取值范围的最大值。输入参数。输入任意值，自动计算最大值。
*	   int  nExpsoureVal:  曝光值，单位为行数。
*      int   nDevId: 设备索引号
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetExposureInfo( BOOL bEnable, BOOL bAuto, int nRangeMin, int nRangeMax,
															 int nExpsoureVal,int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetExposureValue
* Description: 获取曝光(Exposure)的值
* Format:
*     int HV_GetExposureValue(int* pnValue,int nDevId)
* Params:
*	  int* pnValue:  Exposure的当前值，输出参数，单位为行数
*     int   nDevId: 设备索引号
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetExposureValue(int* pnValue,int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetExposureValue
* Description: 设置Exposure的值
* Format:
*     int HV_LabVIEWSetExposureValue(int nValue,int nDevId)
* Params:
*	  nValue: Exposure的值,单位为行数；
*     int  nDevId: 设备索引号
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetExposureValue(int nValue, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetGainValue
* Description: 获取增益(Gain)五个通道的值
* Format:
*     int HV_LabVIEWGetGainValue(int* pnGlobalValue,int* pnG1Value, int* pnG2Value,
*								 int* pnRValue, int* pnBValue, int nDevId)
* Params:
*	   int* pnGlobalVal:  全局增益(Global Gain)值。输出参数。
*	   int* pnG1Val:  G1通道增益值。输出参数。
*	   int* pnG2Val:  G2通道增益值。输出参数。
*	   int* pnRVal:  R通道增益值。输出参数。
*	   int* pnBVal:  B通道增益值。输出参数。
*      int  nDevId: 设备索引号。
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_GET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int  __stdcall HV_LabVIEWGetGainValue(int* pnGlobalValue,int* pnG1Value, int* pnG2Value,
											   int* pnRValue, int* pnBValue, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetGainValue
* Description: 设置五个通道的增益值
* Format:
*     int HV_LabVIEWSetGainValue(int nGlobalValue,int nG1Value, int nG2Value,
								 int nRValue, int nBValue, int nDevId)
* Params:
*	  int nGlobalValue：全局增益(Global Gain)的值；
*	  int nG1Value：G1 通道的增益值；
*     int nG2Value：G2 通道的增益值；
*	  int nRValue：R 通道的增益值；
*     int nBValue：B 通道的增益值；
*      int  nDevId: 设备索引号。
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetGainValue(int nGlobalValue,int nG1Value, int nG2Value,
														int nRValue, int nBValue, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetGainInfo
* Description: 获取增益(Gain)控制的参数信息
* Format:
*     int HV_LabVIEWGetGainInfo( BOOL* pbEnable, BOOL* pbAuto, int* pnRangeMin, int* pnRangeMax,
									 int* pnGlobalVal, int* pnG1Val, int* pnG2Val, int* pnRVal, 
									 int* pnBVal,int nDevId)
* Params:
*	   BOOL* pbEnable: 使能状态。输出参数。TRUE为Enable，FALSE为Disable；
*	   BOOL* pbAuto; 自动/手动状态。输出参数。TRUE为Auto，FALSE为Manual；
*	   int* pnRangeMin: 取值范围的最小值。输出参数。
*      int* pnRangeMax: 取值范围的最大值。输出参数。
*	   int* pnGlobalVal:  全局增益(Global Gain)值。输出参数。
*	   int* pnG1Val:  G1通道增益值。输出参数。
*	   int* pnG2Val:  G2通道增益值。输出参数。
*	   int* pnRVal:  R通道增益值。输出参数。
*	   int* pnBVal:  B通道增益值。输出参数。
*      int  nDevId: 设备索引号
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetGainInfo( BOOL* pbEnable, BOOL* pbAuto, int* pnRangeMin, int* pnRangeMax,
													    int* pnGlobalVal, int* pnG1Val, int* pnG2Val, int* pnRVal, 
														int* pnBVal, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetGainInfo
* Description: 设置增益(Gain)控制的参数信息
* Format:
*     int HV_LabVIEWSetGainInfo( BOOL bEnable, BOOL bAuto, int nRangeMin, int nRangeMax,
*									int nGlobalVal, int nG1Val, int nG2Val, int nRVal,
*									int nBVal,int nDevId)
* Params:
*	   BOOL bEnable: 使能状态。输入参数。TRUE为Enable，FALSE为Disable；
*	   BOOL bAuto; 自动/手动状态。输入参数。TRUE为Auto，FALSE为Manual；
*	   int  nRangeMin: 取值范围的最小值。输入参数。最小为1；
*      int  nRangeMax: 取值范围的最大值。输入参数。HV130GM最大为15; HV300GM,HV500GC/M最大为128；
*	   int  nGlobalVal:  全局增益(Global Gain)值。
*	   int  nG1Val:  G1通道增益值。
*	   int  nG2Val:  G2通道增益值。
*	   int  nRVal:  R通道增益值。
*	   in   nBVal:  B通道增益值。
*      int  nDevId: 设备索引号。
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetGainInfo( BOOL bEnable, BOOL bAuto, int nRangeMin, int nRangeMax,
														int nGlobalVal, int nG1Val, int nG2Val, int nRVal,
														int nBVal,int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetImageGammaStat()
* Description: 设置图像的Gamma状态
* Format:
*     int HV_LabVIEWSetImageGammaStat(BOOL bGamma,int nDevId)
* Params:
*	  BOOL bColor： 图像的Gamma状态
*      int  nDevId: 设备索引号。
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetImageGammaStat(BOOL bGamma,int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWGetImageGammaStat()
* Description: 获取图像的Gamma状态
* Format:
*     int HV_LabVIEWGetImageGammaStat(BOOL* pbGamma,int nDevId)
* Params:
*	  BOOL* pbColor： 返回图像的Gamma状态
*      int  nDevId: 设备索引号。
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetImageGammaStat(BOOL* pbGamma,int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetImageMirror()
* Description: 获取图像的镜像(Mirror)方式
* Format:
*     int HV_LabVIEWGetImageMirror(int* pnMirror,int nDevId)
* Params:
*	  int* pnMirror: 返回当前的镜像方式。镜像方向，有三种方式：竖直、水平、竖直水平。
*					RowMirror=1; ColumnMirror=2; both=3;
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetImageMirror(int* pnMirror,int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetImageMirror()
* Description: 设置图像镜像(Mirror)方式
* Format:
*     int   HV_LabVIEWSetImageMirror(int nMirror,int nDevId)
* Params:
*	  int nMirror: 设置当前的镜像方式。镜像方向，有三种方式：竖直、水平、水平竖直。
*					RowMirror=1; ColumnMirror=2; both=3;
*      int  nDevId: 设备索引号。
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetImageMirror(int nMirror,int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetROI
* Description: 设置视频的ROI(Region of Interest)
* Format:
*      int HV_LabVIEWSetROI(int Original_x, int Original_y,
*						int nImgWidth, int nImgHeight,int nDevId)
* Params:
*	  int Oringination_x: ROI的起始点x坐标
*	  int Oringination_y: ROI的起始点y坐标
*     int nImgWidth: ROI的宽度
*     int nImgHeight: ROI的高度
*     int nDevId: 设备索引号
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetResolution(int* pnVideoWidth, int* pnVideoHeight,int nDevId);



/******************************************************************************
* Function:	HV_LabVIEWGetMaxResolution()
* Description: 获取CIS最大分辨率的宽、高
* Format:
*     int HV_LabVIEWGetMaxResolution(int* pnMaxWidth, int* pnMaxHeight, int nDevId)
* Params:
*	  int* pnMaxWidth: CIS的最大图像宽度；
*     int* pnMaxHeight: CIS的最大图像高度；
*      int  nDevId: 设备索引号。
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetMaxResolution(int* pnMaxWidth, int* pnMaxHeight, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetResolutionMode
* Description: 设置分辨率模式
* Format:
*      int HV_LabVIEWSetResolutionMode(int nResMode, int nDevId)
* Params:
*	  int nResMode: 图像的分辨率模式，取值0-3；
*		For HV500GC/M
*			Res_Mode=0; 2592x1944;
*			Res_Mode=1: 1024x768;
*			Res_Mode=2: 800x600;
*			Res_Mode=3: 640x480
*		For HV300GC/M:
*			Res_Mode=0; 2048x1536;
*			Res_Mode=1: 1024x768;
*			Res_Mode=2: 800x600;
*			Res_Mode=3: 640x480
*		For HV130GC/M:
*			Res_Mode=0; 1280x1024;
*			Res_Mode=1: 640x480;
*			Res_Mode=2: 320x240;
*     int  nDevId: 设备索引号。
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetResolution(int nVideoWidth, int nVideoHeight, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetResolutionMode
* Description: 设置分辨率模式
* Format:
*      int HV_LabVIEWSetResolutionMode(int nResMode, int nDevId)
* Params:
*	  int nResMode: 图像的分辨率模式，取值0-3；
*     int  nDevId: 设备索引号。
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetResolutionMode(int nResMode, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetROI
* Description: 设置视频的ROI(Region of Interest)
* Format:
*      int HV_LabVIEWSetROI(int Original_x, int Original_y,
*						int nImgWidth, int nImgHeight,int nDevId)
* Params:
*	  int Oringination_x: ROI的起始点x坐标
*	  int Oringination_y: ROI的起始点y坐标
*     int nImgWidth: ROI的宽度
*     int nImgHeight: ROI的高度
*     int nDevId: 设备索引号
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetROI(int Original_x, int Original_y, 
										  int nImgWidth, int nImgHeight,int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSuspendCapture
* Description: 挂起/恢复 Data Thread 和 Show Thread.
* Format:
*     int HV_LabVIEWSuspendCapture(BOOL bSuspend,int nDevId);
* Params:
*     BOOL bSuspend: 1 for suspend; 0 for resume;
*     int nDevId: 设备索引号
* Return: 
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_SET_PARAMINFO_FAIL：设置参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSuspendCapture(BOOL bSuspend,int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWGetTrigImgCountRange
* Description: 设置拍照模式时，触发频率的有效值范围.
* Format:
*     int HV_LabVIEWGetTrigImgCountRange(int* pnRangeMin, int* pnRangeMax, int nDevId)
* Params:
*	 int* pnRangeMin: 设置拍照模式时，连续拍照张数的有效值范围的最小值。输出参数。
*	 int* pnRangeMax: 设置拍照模式时，连续拍照张数的有效值范围的最大值。输出参数。
*     int nDevId: 设备索引号
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetTrigImgCountRange(int* pnRangeMin, int* pnRangeMax, int nDevId);



/******************************************************************************
* Function:	HV_LabVIEWGetSnapExpTimeRange
* Description: 获取拍照模式时，曝光时间(ExposureTime)的有效值范围.时间单位为us.
* Format:
*     int HV_LabVIEWGetSnapExpTimeRange(int* pnRangeMin, int* pnRangeMax, int nDevId)
* Params:
*	 int* pnRangeMin: 设置拍照模式时，曝光时间(ExposureTime)的有效值范围的最小值,单位为微秒。输出参数。
*	 int* pnRangeMax: 设置拍照模式时，曝光时间(ExposureTime)的有效值范围的最大值,单位为微秒。输出参数。
*     int nDevId: 设备索引号
* Return:
*     HV_SUCCESS: 成功
*	  HVOCX_INVALID_PARAM: 无效参数
*	  HVOCX_GET_PARAMINFO_FAIL：获取参数信息失败
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetSnapExpTimeRange(int* pnRangeMin, int* pnRangeMax, int nDevId);







	

// ERRORs
#define HVOCX_DEVICE_STATUS_EXIST				-1				//状态已经存在，不允许重复操作相同状态
#define HVOCX_DEVICE_START_FAIL					-2				//开启设备失败
#define HVOCX_DEVICE_STOP_FAIL					-3				//停止设备失败
#define	HVOCX_DEVICE_SUSPEND_FAIL				-4				//挂起设备的数据传输失败
#define HVOCX_DEVICE_RESUME_FAIL				-5				//恢复设备的数据传输失败

#define HVOCX_SAVE_IMAGE_FAIL					-6				//保存图片失败
#define HVOCX_INVALID_PARAM						-7			    //无效参数
#define HVOCX_GET_DEVICELIST_FAIL				-8				//获取设备列表失败
#define HVOCX_NO_SUCH_DEVICE					-9				//设备不存在或无效设备
#define HVOCX_NO_SUCH_DEVICETYPE				-10				//找不到指定的设备类型
#define HVOCX_DEVICE_INI_FAIL					-11				//设备初始化失败
#define HVOCX_SET_CALLBACK_FAIL					-12				//设置回调函数失败
#define HVOCX_INVALID_HANDLE_VALUE				-13				//无效的句柄值
#define HVOCX_GET_DATABUF_FAIL					-14				//获取图像数据失败
#define HVOCX_GET_PARAMINFO_FAIL				-15				//获取参数信息失败
#define HVOCX_SET_PARAMINFO_FAIL				-16				//设置参数信息失败
#define HVOCX_ENTER_TRIGGERMODE_FAIL			-17				//进入触发模式失败
#define HVOCX_LEAVE_TRIGGERMODE_FAIL			-18				//离开触发模式失败
#define HVOCX_NO_DEVICE_SELECTED				-19				//没有选中设备
#define HVOCX_GET_DEVICE_FAIL					-20				//获取指定设备失败
#define HVOCX_SAVE_CONFIGURATION_FAIL			-21				//保存相机配置失败
#define HVOCX_GET_NO_DATA						-22				//未得到数据

//GigE
#define HVOCX_DEVICE_OPEN_FAIL					-23				//打开设备失败



#define HVOCX_SHOW_CONTROL_PAGE_FAIL			-24				//显示属性页失败
#define HVOCX_SOFTWARE_TRIGGER_FAIL		    	-25             //软件触发失败
