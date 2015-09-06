
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
* Description: ���豸����ʼ���豸�������豸�Ļص�������
* Format:
*     int HV_LabVIEWCapInit(int nDevId)
* Params:
*     int nDevId: �豸������
*	  LPCSTR lpFileName   ָ�������ļ�·����Ĭ��Ϊ�գ���Ĭ�ϵ�����·���ڵ�ǰ·���£�
* Return: 
*     HV_SUCCESS: �ɹ�
*     HVOCX_INVALID_PARAM: ��Ч����
*     HVOCX_DEVICE_OPEN_FAIL: ���豸ʧ��
*	  HVOCX_DEVICE_INI_FAIL�� ��ʼ���豸ʧ��
*	  HVOCX_GET_PARAMINFO_FAIL�� ��ȡ����ʧ��
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWCapInit(int nDevId, LPCSTR lpFileName=NULL);


/******************************************************************************
* Function:	HV_LabVIEWStartCapture
* Description: ��ʼͼ�񲶻�
* Format:
*     int HV_LabVIEWStartCapture(int nDevId)
* Params:
*     int nDevId: �豸������
* Return: 
*     HV_SUCCESS: �ɹ�
*     HVOCX_INVALID_PARAM: ��Ч����
*     HVOCX_DEVICE_START_FAIL: �����豸ʧ��
******************************************************************************/
INDCAM_LABVIEW_API BOOL _stdcall HV_LabVIEWStartCapture(int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWStopCapture
* Description: ֹͣͼ�񲶻�
* Format:
*     int HV_LabVIEWStopCapture(int nDevId);
* Params:
*     int nDevId: �豸������
* Return: 
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*     HVOCX_DEVICE_STOP_FAIL: ֹͣ�豸ʧ��
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWStopCapture(int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetImageData
* Description: ��ȡһ֡��ͼ�����ݣ����������ݻ���
* Format:
*     int HV_LabVIEWGetImageData(int* pData, int nWidth, int nHeight, int nDevId)
* Params:
*     int* pData: ָ��ͼ�����ݻ����ָ�룬ͼ�񻺴�Ĵ�СΪ��nWidth*nHeight
*     int nWidth: ͼ����
*	  int nHeight: ͼ��߶�
*    int   nDevId: �豸������
* Return: 
*     HV_SUCCESS: �ɹ�
*     HVOCX_INVALID_PARAM: ��Ч����
* 	  HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetImageData(int* pData, int nWidth, int nHeight, int nDevId);



/******************************************************************************
* Function:	HV_LabVIEWGetFrameRate
* Description: ��ȡ��ǰ��֡��
* Format:
*     double HV_LabVIEWGetFrameRate(int nDevId)
* Params:
*    int   nDevId: �豸������
* Return: 
*     
*	  �ɹ�������֡�ʣ�
*	  ���򣬷���HVOCX_INVALID_PARAM����Ч����
******************************************************************************/
INDCAM_LABVIEW_API double _stdcall HV_LabVIEWGetFrameRate(int nDevId);




/******************************************************************************
* Function:	HV_LabVIEWGetImageWidth
* Description: ��ȡ��ǰ�ֱ����£�ͼ��Ŀ��
* Format:
*     int HV_LabVIEWGetImageWidth(int* pnImgWidth��int nDevId)
* Params: 
*		   int* pnImgWidth: ָ��ͼ���ȵ�ָ�롣���������
*		   int nDevID: ��������š�
* Return: 
*     HV_SUCCESS: �ɹ�
*     HVOCX_INVALID_PARAM: ��Ч����
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetImageWidth(int* pnImgWidth, int nDevId);
/******************************************************************************
* Function:	HV_LabVIEWGetImageChannels
* Description: ��ȡ��ǰ�ֱ����£�ͼ���ͨ����
* Format:
*     int HV_LabVIEWGetImageChannels(int* pnImgBitCount, int nDevId)
* Params: 
*		   int nDevID: ��������š�
*		   int* pnChannels: ָ��ͼ��ͨ������ָ�롣���������
* Return: 
*     HV_SUCCESS: �ɹ�
*     HVOCX_INVALID_PARAM: ��Ч����
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetImageChannels(int* pnChannels, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWGetImageHeight
* Description: ��ȡ��ǰ�ֱ����£�ͼ��ĸ߶�
* Format:
*     int HV_LabVIEWGetImageHeight(int* pnImgHeight, int nDevId)
* Params: 
*		   int nDevID: ��������š�
*		   int* pnImgWidth: ָ��ͼ���ȵ�ָ�롣���������
* Return: 
*     HV_SUCCESS: �ɹ�
*     HVOCX_INVALID_PARAM: ��Ч����
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetImageHeight(int* pnImgHeight, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWCtrlPage
* Description: ��ʾ��������ҳ
* Format:
*     int HV_LabVIEWCtrlPage(int nDevId)
* Params: 
*	  int nDevID: ��������š�
* Return: 
*     HV_SUCCESS: �ɹ�
*     HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SHOW_CONTROL_PAGE_FAIL����ʾ����ҳʧ��
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWCtrlPage(int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWCapRelease
* Description: �ͷ���Դ
* Format:
*		   void  HV_LabVIEWCapRelease(int nDevId)
* Params: 
*		   int nDevID: ��������š�
* Return: 
*		   void
******************************************************************************/
INDCAM_LABVIEW_API void _stdcall HV_LabVIEWCapRelease(int nDevId);

/******************************************************************************
* Function:	HV_ShowSnapshotPage
* Description: �����նԻ���
* Format:
*     int _stdcall HV_LabVIEWSnapPage(int nDevId)
* Params:
*    int   nDevId: �豸������
* Return: 
*     HV_SUCCESS
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SHOW_CONTROL_PAGE_FAIL����ʾ����ҳʧ��
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSnapPage(int nDevId);



/******************************************************************************
* Function:	int HV_LabVIEWSaveParaToIniFile()
* Description: ���������浽ini�ļ�
* Format:
*     int HV_LabVIEWSaveParaToIniFile(int nDevId)
*	  LPCSTR lpFileName   ָ�������ļ�·����Ĭ��Ϊ�գ���Ĭ�ϵ�����·���ڵ�ǰ·���£�
* Params:
*    int   nDevId: �豸������
* Return: 
*	  HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SAVE_CONFIGURATION_FAIL: �����������ʧ��
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSaveParaToIniFile(int nDevId, LPCSTR lpFileName=NULL);


/******************************************************************************
* Function:	int HV_LabVIEWIniCamFromIniFile()
* Description: ʹ��ini�ļ��еĲ������������
* Format:
*     int  HV_LabVIEWIniCamFromIniFile()
*	  LPCSTR lpFileName   ָ�������ļ�·����Ĭ��Ϊ�գ���Ĭ�ϵ�����·���ڵ�ǰ·���£�
* Params:
*    int   nDevId: �豸������
* Return: 
*	  HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWIniCamFromIniFile(int nDevId, LPCSTR lpFileName=NULL);


/******************************************************************************
* Function: HV_LabVIEWSnapSWTrigger()
* Description: Snapshotģʽʱ������ sw Trigger(�������)����Ӧ����
* Format:
*     int HV_LabVIEWSnapSWTrigger(int nDevId)
* Params:
*    int   nDevId: �豸������
* Return: 
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*     HVOCX_SOFTWARE_TRIGGER_FAIL���������ʧ��
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSnapSWTrigger(int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWGetImageColorStat()
* Description: �õ�ͼ��Ĳ�ɫ/�Ҷ�״̬
* Format:
*     int HV_LabVIEWGetImageColorStat(BOOL* pbColor, int nDevId)
* Params:
*	  BOOL* pbColor�� ����ͼ��Ĳ�ɫ/�Ҷ�״̬
*     int nDevId:  �豸������
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HVOCX_INVALID_PARAM: ��Ч������
*	   HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetImageColorStat(BOOL* pbColor, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetImageColorStat()
* Description: ����ͼ��Ĳ�ɫ/�Ҷ�״̬
* Format:
*     int HV_LabVIEWSetImageColorStat(BOOL bColor, int nDevId)
* Params:
*	  BOOL bColor�� ����ͼ��Ĳ�ɫ/�Ҷ�״̬
*     int nDevId:  �豸������
* Return:
*	   HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL: ���ò�����Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSetImageColorStat(BOOL bColor, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetSnapDebounceTime()
* Description: ��ȡ����ģʽʱ��ȥ����ʱ��(DebouncerTime)��ʱ�䵥λΪus.
* Format:
*     int HV_LabVIEWGetSnapDebounceTime(int* plDebouncerTime, int nDevId)
* Params:
*	  int* plDebouncerTime: ����ȥ����ʱ�䣬��λΪus
*	  int  nDevId: �豸������
* Return:
*	   HV_SUCCESS: �ɹ���
*      HVOCX_INVALID_PARAM: ��Ч������
*	   HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetSnapDebounceTime(int* plDebouncerTime, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetSnapDebounceTime()
* Description: ��������ģʽʱ��ȥ����ʱ��(DebouncerTime)��ʱ�䵥λΪus.
* Format:
*     int HV_LabVIEWSetSnapDebounceTime(int lDebouncerTime, int nDevId)
* Params:
*	 int lDebouncerTime: ȥ����ʱ�䣬��λΪus
*	 int  nDevId: �豸������
* Return:
*	   HV_SUCCESS: �ɹ���
*      HVOCX_INVALID_PARAM: ��Ч������
*	   HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSetSnapDebounceTime(int lDebouncerTime, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetSnapDebounceTime()
* Description: ��ȡ����ģʽʱ��ȥ����ʱ��(DebouncerTime)��ʱ�䵥λΪus.
* Format:
*     int HV_LabVIEWGetSnapDebounceTime(int* plExpTime, int nDevId)
* Params:
*	  int* plDebouncerTime: ����ȥ����ʱ�䣬��λΪus
*	  int  nDevId: �豸������
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetSnapExpTime(int* plExpTime, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetSnapExpTime()
* Description: ��������ģʽʱ���ع�ʱ��(ExposureTime)��ʱ�䵥λΪus.
* Format:
*     int HV_LabVIEWSetSnapExpTime(int lExpTime, int nDevId)
* Params:
*	  int lExpTime���ع�ʱ�䣬��λΪus
*     int   nDevId: �豸������
* Return:
*	   HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSetSnapExpTime(int lExpTime, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetSnapExpTime()
* Description: ��������ģʽʱ���ع�ʱ��(ExposureTime)��ʱ�䵥λΪus.
* Format:
*     HV_LabVIEWSetSnapExpTime(int lExpTime, int nDevId)
* Params:
*	  int lExpTime���ع�ʱ�䣬��λΪus
*     int   nDevId: �豸������
* Return:
*	   HV_SUCCESS: �ɹ�����Exposure��ֵ��
*      HV_NO_SUCH_DEVICE: û���ҵ���Ӧ��Ӳ���豸
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSetSnapExpTime(int lExpTime, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetSnapTrigFreqImgCount()
* Description: ��ȡ����ģʽʱ��������Ƶ���Լ�ÿ�δ��������ͼ������
* Format:
*     int HV_LabVIEWGetSnapTrigFreqImgCount(int* plTrigFreq, int* plTrigImgCount, int nDevId)
* Params:
*	 int* plTrigFreq: ��������ģʽʱ��(����ƣ��Ĵ���Ƶ�ʡ���λΪÿ���֡����
*    int* plTrigImgCount������һ�Σ����������ͼ������
*    int   nDevId: �豸������
* Return:
*	   HV_SUCCESS: �ɹ�
*      HVOCX_INVALID_PARAM: ��Ч����
*	   HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetSnapTrigFreqImgCount(int* plTrigFreq, int* plTrigImgCount, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetSnapTrigFreqImgCount()
* Description: ��������ģʽʱ��������Ƶ���Լ�ÿ�δ��������ͼ������
* Format:
*     int HV_LabVIEWSetSnapTrigFreqImgCount(int lTrigFreq, int lTrigImgCount, int nDevId)
* Params:
*	 int lTrigFreq: ��������ģʽʱ��(����ƣ��Ĵ���Ƶ�ʡ���λΪÿ���֡����
*    int lTrigImgCount������һ�Σ����������ͼ��֡��
*    int   nDevId: �豸������
* Return:
*	  HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSetSnapTrigFreqImgCount(int lTrigFreq, int lTrigImgCount, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetTrigFreqRange()
* Description: ��ȡ����ģʽʱ��������Ƶ�ʵ���Ч��Χ
* Format:
*     int HV_LabVIEWGetTrigFreqRange(int* pnRangeMin, int* pnRangeMax, int nDevId)
* Params:
*	 int* pnRangeMin: ����ģʽʱ��(����ƣ��Ĵ���Ƶ�ʵ���Сֵ��
*    int* pnRangeMax������ģʽʱ��(����ƣ��Ĵ���Ƶ�ʵ����ֵ��
*    int   nDevId: �豸������
* Return:
*	   HV_SUCCESS: �ɹ�
*      HVOCX_INVALID_PARAM: ��Ч����
*	   HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWGetTrigFreqRange(int* pnRangeMin, int* pnRangeMax, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetSnapIOMode()
* Description: ��������ģʽ(snapshot)�£����IO����ģʽ��
* Format:
*     int HV_LabVIEWSetSnapIOMode(int nInMode, int nOutMode, int nDevId)
* Params:
*		int nInMode:  0 for falling-edge valid trigger; 
*							  1 for rising-edge valide trigger;
*							  2 for low-level valid trigger;
*							  3 for high-level valid trigger;
*		int nOutMode: 0 for low-level output;
*							  1 for high-level output;  
*       int   nDevId: �豸������
*
* Return: 
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int _stdcall HV_LabVIEWSetSnapIOMode(int nInMode, int nOutMode, int nDevId);



/******************************************************************************
* Function:	HV_LabVIEWGetSnapIOMode()
* Description: ��������ģʽ(snapshot)�£����IO����ģʽ��
* Format:
*     int HV_LabVIEWGetSnapIOMode(int* pnInMode, int* pnOutMOde, int nDevId)
* Params:
*	  int* pnInMode:  0 for falling-edge valid trigger; 
*								1 for rising-edge valide trigger;
*								2 for low-level valid trigger;
*								3 for high-level valid trigger;
*	  int* pnOutMode: 0 for low-level output;
*								1 for high-level output;  
*     int   nDevId: �豸������
*
* Return: 
*      HV_SUCCESS: �ɹ�
*      HVOCX_INVALID_PARAM: ��Ч������
*	   HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetSnapIOMode(int* pnInMode, int* pnOutMOde, int nDevId);


/******************************************************************************
* Function:	HV_GetPreviewSnapMode()
* Description: �õ���ǰΪPreview��Snapshot
* Format:
*     int HV_LabVIEWGetPreviewSnapMode(int* pnPreview, int* pnSnapMode, int nDevId)
* Params:
*		int* pnPreview: 1 for preview mode; 0 for snapshot mode;
*		int* pnSnapshot: snapshot mode, selected from 0 to 2;  
*					  *pnPreview = 1, *pnSnapMode=0, for preview;  
*					  *pnPreview = 0, *pnSnapMode=0-2, for snapshot of outer trigger source;
*		int nDevId: �豸�����ţ�
*
* Return: 
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetPreviewSnapMode(int* pnPreview, int* pnSnapMode, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetPreviewSnapMode()
* Description: ����Ϊ����Ԥ��(contionus)ģʽ
* Format:
*     int HV_LabVIEWSetPreviewSnapMode(int nPreview, int nSnapMode, int nDevId)
* Params:
*		nPreview: 1 for preview mode; 
*				  0 for snapshot mode;
*		nSnapshot: snapshot mode, selected from 0 to 2, for both outer and inner
*				  trigger source.     
*    int   nDevId: �豸������
* Return: 
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetPreviewSnapMode(int nPreview, int nSnapMode, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWDeviceClose
* Description: �ر�������ͷ���Դ
* Format:
*     int HV_LabVIEWDeviceClose(int nDevId) ;
* Params:
*    int   nDevId: �豸������
* Return: 
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWDeviceClose( int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWAllocation
* Description: ���·����ڴ�
* Format:
*     int HV_LabVIEWAllocation(int nWidth, int nHeight, int nDevId) ;
* Params:
*    int   nDevId: �豸������
* Return: 
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWAllocation( int nWidth, int nHeight, int nDevId);



//========================= Black Level Control ===========================================

/******************************************************************************
* Function:	HV_LabVIEWGetBlackLevelInfo
* Description: ��ȡBlackLevel������Ϣ
* Format:
*     int HV_LabVIEWGetBlackLevelInfo( BOOL* pbEnable, BOOL* pbAuto, int* pnRangeMin, int* pnRangeMax,
									   int* pnG1Val, int* pnG2Val, int* pnRVal, int* pnBVal,int nDevId)
* Params:
*	   BOOL* pbEnable: ʹ��״̬�����������TRUEΪEnable��FALSEΪDisable��
*	   BOOL* pbAuto; �Զ�/�ֶ�״̬�����������TRUEΪAuto��FALSEΪManual��
*	   int* pnRangeMin: ȡֵ��Χ����Сֵ�����������
*      int* pnRangeMax: ȡֵ��Χ�����ֵ�����������
*	   int* pnG1Val: G1ͨ����BlackLevelֵ�����������
*      int* pnG2Val: G2ͨ����BlackLevelֵ�����������
*	   int* pnRVal�� Rͨ����BlackLevelֵ�����������
*      int* pnBVal:  Bͨ����BlackLevleֵ�����������
*    int   nDevId: �豸������
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetBlackLevelInfo( BOOL* pbEnable, BOOL* pbAuto, int* pnRangeMin, int* pnRangeMax,
															 int* pnG1Val, int* pnG2Val, int* pnRVal, int* pnBVal,int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetBlackLevelInfo
* Description: ����BlackLevel������Ϣ
* Format:
*     int HV_LabVIEWSetBlackLevelInfo( BOOL bEnable, BOOL bAuto, int nRangeMin, int nRangeMax,
									   int nG1Val, int nG2Val, int nRVal, int nBVal,int nDevId)
* Params:
*	   BOOL bEnable: ʹ��״̬�����������TRUEΪEnable��FALSEΪDisable��
*	   BOOL bAuto; �Զ�/�ֶ�״̬�����������TRUEΪAuto��FALSEΪManual��
*	   int  nRangeMin: ȡֵ��Χ����Сֵ�������������Сֵ����С��-255��
*      int  nRangeMax: ȡֵ��Χ�����ֵ��������������ֵ���ܴ���255��
*	   int  nG1Val: G1ͨ����BlackLevelֵ�����������
*      int  nG2Val: G2ͨ����BlackLevelֵ�����������
*	   int  nRVal�� Rͨ����BlackLevelֵ�����������
*      int  nBVal:  Bͨ����BlackLevleֵ�����������
*      int   nDevId: �豸������
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetBlackLevelInfo( BOOL bEnable, BOOL bAuto, int nRangeMin, int nRangeMax,
															 int nG1Val, int nG2Val, int nRVal, int nBVal,int nDevId);

/******************************************************************************
* Function:	HV_GetBlackLevelValue
* Description: ��ȡBlackLevel��ֵ
* Format:
*     int HV_LabVIEWGetBlackLevelValue(int* pnG1Value, int* pnG2Value, int* pnRValue, int* pnBValue, int nDevId)
* Params:
*	   int* pnG1Val: G1ͨ����BlackLevelֵ�����������
*      int* pnG2Val: G2ͨ����BlackLevelֵ�����������
*	   int* pnRVal�� Rͨ����BlackLevelֵ�����������
*      int* pnBVal:  Bͨ����BlackLevleֵ�����������
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetBlackLevelValue(int* pnG1Value, int* pnG2Value, 
															  int* pnRValue, int* pnBValue, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetBlackLevelValue
* Description: ����Exposure��ֵ
* Format:
*     int HV_LabVIEWSetBlackLevelValue(int nG1Val, int nG2Val, int nRVal,
*															 int nBVal,int nDevId)
* Params:
*	   int  nG1Val: G1ͨ����BlackLevelֵ�����������
*      int  nG2Val: G2ͨ����BlackLevelֵ�����������
*	   int  nRVal�� Rͨ����BlackLevelֵ�����������
*      int  nBVal:  Bͨ����BlackLevleֵ�����������
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetBlackLevelValue(int nG1Val, int nG2Val, int nRVal,
															 int nBVal,int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetExposureInfo
* Description: ��ȡ�ع�(Exposure)������Ϣ
* Format:
*     int HV_LabVIEWGetExposureInfo( BOOL* pbEnable, BOOL* pbAuto, int* pnRangeMin, int* pnRangeMax,
															 int* pnExpsoureVal,int nDevId)
* Params:
*	   BOOL* pbEnable: ʹ��״̬�����������TRUEΪEnable��FALSEΪDisable��
*	   BOOL* pbAuto; �Զ�/�ֶ�״̬�����������TRUEΪAuto��FALSEΪManual��
*	   int* pnRangeMin: ȡֵ��Χ����Сֵ�����������
*      int* pnRangeMax: ȡֵ��Χ�����ֵ�����������
*	   int* pnExpsoureVal:  �ع�ֵ����λΪ���������������
*      int  nDevId: �豸������
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetExposureInfo( BOOL* pbEnable, BOOL* pbAuto, int* pnRangeMin, int* pnRangeMax,
															 int* pnExposureVal,int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetExposureInfo
* Description: �����ع�(Exposure)�Ĳ�����Ϣ
* Format:
*     int HV_LabVIEWSetExposureInfo( BOOL bEnable, BOOL bAuto, int nRangeMin, int nRangeMax,
															 int nExpsoureVal,int nDevId)
* Params:
*	   BOOL bEnable: ʹ��״̬�����������TRUEΪEnable��FALSEΪDisable��
*	   BOOL bAuto; �Զ�/�ֶ�״̬�����������TRUEΪAuto��FALSEΪManual��
*	   int  nRangeMin: ȡֵ��Χ����Сֵ�������������������ֵ���Զ�������Сֵ��
*      int  nRangeMax: ȡֵ��Χ�����ֵ�������������������ֵ���Զ��������ֵ��
*	   int  nExpsoureVal:  �ع�ֵ����λΪ������
*      int   nDevId: �豸������
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetExposureInfo( BOOL bEnable, BOOL bAuto, int nRangeMin, int nRangeMax,
															 int nExpsoureVal,int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetExposureValue
* Description: ��ȡ�ع�(Exposure)��ֵ
* Format:
*     int HV_GetExposureValue(int* pnValue,int nDevId)
* Params:
*	  int* pnValue:  Exposure�ĵ�ǰֵ�������������λΪ����
*     int   nDevId: �豸������
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetExposureValue(int* pnValue,int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetExposureValue
* Description: ����Exposure��ֵ
* Format:
*     int HV_LabVIEWSetExposureValue(int nValue,int nDevId)
* Params:
*	  nValue: Exposure��ֵ,��λΪ������
*     int  nDevId: �豸������
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetExposureValue(int nValue, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetGainValue
* Description: ��ȡ����(Gain)���ͨ����ֵ
* Format:
*     int HV_LabVIEWGetGainValue(int* pnGlobalValue,int* pnG1Value, int* pnG2Value,
*								 int* pnRValue, int* pnBValue, int nDevId)
* Params:
*	   int* pnGlobalVal:  ȫ������(Global Gain)ֵ�����������
*	   int* pnG1Val:  G1ͨ������ֵ�����������
*	   int* pnG2Val:  G2ͨ������ֵ�����������
*	   int* pnRVal:  Rͨ������ֵ�����������
*	   int* pnBVal:  Bͨ������ֵ�����������
*      int  nDevId: �豸�����š�
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_GET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int  __stdcall HV_LabVIEWGetGainValue(int* pnGlobalValue,int* pnG1Value, int* pnG2Value,
											   int* pnRValue, int* pnBValue, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetGainValue
* Description: �������ͨ��������ֵ
* Format:
*     int HV_LabVIEWSetGainValue(int nGlobalValue,int nG1Value, int nG2Value,
								 int nRValue, int nBValue, int nDevId)
* Params:
*	  int nGlobalValue��ȫ������(Global Gain)��ֵ��
*	  int nG1Value��G1 ͨ��������ֵ��
*     int nG2Value��G2 ͨ��������ֵ��
*	  int nRValue��R ͨ��������ֵ��
*     int nBValue��B ͨ��������ֵ��
*      int  nDevId: �豸�����š�
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/

INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetGainValue(int nGlobalValue,int nG1Value, int nG2Value,
														int nRValue, int nBValue, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetGainInfo
* Description: ��ȡ����(Gain)���ƵĲ�����Ϣ
* Format:
*     int HV_LabVIEWGetGainInfo( BOOL* pbEnable, BOOL* pbAuto, int* pnRangeMin, int* pnRangeMax,
									 int* pnGlobalVal, int* pnG1Val, int* pnG2Val, int* pnRVal, 
									 int* pnBVal,int nDevId)
* Params:
*	   BOOL* pbEnable: ʹ��״̬�����������TRUEΪEnable��FALSEΪDisable��
*	   BOOL* pbAuto; �Զ�/�ֶ�״̬�����������TRUEΪAuto��FALSEΪManual��
*	   int* pnRangeMin: ȡֵ��Χ����Сֵ�����������
*      int* pnRangeMax: ȡֵ��Χ�����ֵ�����������
*	   int* pnGlobalVal:  ȫ������(Global Gain)ֵ�����������
*	   int* pnG1Val:  G1ͨ������ֵ�����������
*	   int* pnG2Val:  G2ͨ������ֵ�����������
*	   int* pnRVal:  Rͨ������ֵ�����������
*	   int* pnBVal:  Bͨ������ֵ�����������
*      int  nDevId: �豸������
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetGainInfo( BOOL* pbEnable, BOOL* pbAuto, int* pnRangeMin, int* pnRangeMax,
													    int* pnGlobalVal, int* pnG1Val, int* pnG2Val, int* pnRVal, 
														int* pnBVal, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetGainInfo
* Description: ��������(Gain)���ƵĲ�����Ϣ
* Format:
*     int HV_LabVIEWSetGainInfo( BOOL bEnable, BOOL bAuto, int nRangeMin, int nRangeMax,
*									int nGlobalVal, int nG1Val, int nG2Val, int nRVal,
*									int nBVal,int nDevId)
* Params:
*	   BOOL bEnable: ʹ��״̬�����������TRUEΪEnable��FALSEΪDisable��
*	   BOOL bAuto; �Զ�/�ֶ�״̬�����������TRUEΪAuto��FALSEΪManual��
*	   int  nRangeMin: ȡֵ��Χ����Сֵ�������������СΪ1��
*      int  nRangeMax: ȡֵ��Χ�����ֵ�����������HV130GM���Ϊ15; HV300GM,HV500GC/M���Ϊ128��
*	   int  nGlobalVal:  ȫ������(Global Gain)ֵ��
*	   int  nG1Val:  G1ͨ������ֵ��
*	   int  nG2Val:  G2ͨ������ֵ��
*	   int  nRVal:  Rͨ������ֵ��
*	   in   nBVal:  Bͨ������ֵ��
*      int  nDevId: �豸�����š�
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetGainInfo( BOOL bEnable, BOOL bAuto, int nRangeMin, int nRangeMax,
														int nGlobalVal, int nG1Val, int nG2Val, int nRVal,
														int nBVal,int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetImageGammaStat()
* Description: ����ͼ���Gamma״̬
* Format:
*     int HV_LabVIEWSetImageGammaStat(BOOL bGamma,int nDevId)
* Params:
*	  BOOL bColor�� ͼ���Gamma״̬
*      int  nDevId: �豸�����š�
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetImageGammaStat(BOOL bGamma,int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWGetImageGammaStat()
* Description: ��ȡͼ���Gamma״̬
* Format:
*     int HV_LabVIEWGetImageGammaStat(BOOL* pbGamma,int nDevId)
* Params:
*	  BOOL* pbColor�� ����ͼ���Gamma״̬
*      int  nDevId: �豸�����š�
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetImageGammaStat(BOOL* pbGamma,int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWGetImageMirror()
* Description: ��ȡͼ��ľ���(Mirror)��ʽ
* Format:
*     int HV_LabVIEWGetImageMirror(int* pnMirror,int nDevId)
* Params:
*	  int* pnMirror: ���ص�ǰ�ľ���ʽ�������������ַ�ʽ����ֱ��ˮƽ����ֱˮƽ��
*					RowMirror=1; ColumnMirror=2; both=3;
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetImageMirror(int* pnMirror,int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetImageMirror()
* Description: ����ͼ����(Mirror)��ʽ
* Format:
*     int   HV_LabVIEWSetImageMirror(int nMirror,int nDevId)
* Params:
*	  int nMirror: ���õ�ǰ�ľ���ʽ�������������ַ�ʽ����ֱ��ˮƽ��ˮƽ��ֱ��
*					RowMirror=1; ColumnMirror=2; both=3;
*      int  nDevId: �豸�����š�
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetImageMirror(int nMirror,int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetROI
* Description: ������Ƶ��ROI(Region of Interest)
* Format:
*      int HV_LabVIEWSetROI(int Original_x, int Original_y,
*						int nImgWidth, int nImgHeight,int nDevId)
* Params:
*	  int Oringination_x: ROI����ʼ��x����
*	  int Oringination_y: ROI����ʼ��y����
*     int nImgWidth: ROI�Ŀ��
*     int nImgHeight: ROI�ĸ߶�
*     int nDevId: �豸������
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetResolution(int* pnVideoWidth, int* pnVideoHeight,int nDevId);



/******************************************************************************
* Function:	HV_LabVIEWGetMaxResolution()
* Description: ��ȡCIS���ֱ��ʵĿ���
* Format:
*     int HV_LabVIEWGetMaxResolution(int* pnMaxWidth, int* pnMaxHeight, int nDevId)
* Params:
*	  int* pnMaxWidth: CIS�����ͼ���ȣ�
*     int* pnMaxHeight: CIS�����ͼ��߶ȣ�
*      int  nDevId: �豸�����š�
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetMaxResolution(int* pnMaxWidth, int* pnMaxHeight, int nDevId);

/******************************************************************************
* Function:	HV_LabVIEWSetResolutionMode
* Description: ���÷ֱ���ģʽ
* Format:
*      int HV_LabVIEWSetResolutionMode(int nResMode, int nDevId)
* Params:
*	  int nResMode: ͼ��ķֱ���ģʽ��ȡֵ0-3��
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
*     int  nDevId: �豸�����š�
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetResolution(int nVideoWidth, int nVideoHeight, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetResolutionMode
* Description: ���÷ֱ���ģʽ
* Format:
*      int HV_LabVIEWSetResolutionMode(int nResMode, int nDevId)
* Params:
*	  int nResMode: ͼ��ķֱ���ģʽ��ȡֵ0-3��
*     int  nDevId: �豸�����š�
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetResolutionMode(int nResMode, int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSetROI
* Description: ������Ƶ��ROI(Region of Interest)
* Format:
*      int HV_LabVIEWSetROI(int Original_x, int Original_y,
*						int nImgWidth, int nImgHeight,int nDevId)
* Params:
*	  int Oringination_x: ROI����ʼ��x����
*	  int Oringination_y: ROI����ʼ��y����
*     int nImgWidth: ROI�Ŀ��
*     int nImgHeight: ROI�ĸ߶�
*     int nDevId: �豸������
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSetROI(int Original_x, int Original_y, 
										  int nImgWidth, int nImgHeight,int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWSuspendCapture
* Description: ����/�ָ� Data Thread �� Show Thread.
* Format:
*     int HV_LabVIEWSuspendCapture(BOOL bSuspend,int nDevId);
* Params:
*     BOOL bSuspend: 1 for suspend; 0 for resume;
*     int nDevId: �豸������
* Return: 
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_SET_PARAMINFO_FAIL�����ò�����Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWSuspendCapture(BOOL bSuspend,int nDevId);


/******************************************************************************
* Function:	HV_LabVIEWGetTrigImgCountRange
* Description: ��������ģʽʱ������Ƶ�ʵ���Чֵ��Χ.
* Format:
*     int HV_LabVIEWGetTrigImgCountRange(int* pnRangeMin, int* pnRangeMax, int nDevId)
* Params:
*	 int* pnRangeMin: ��������ģʽʱ������������������Чֵ��Χ����Сֵ�����������
*	 int* pnRangeMax: ��������ģʽʱ������������������Чֵ��Χ�����ֵ�����������
*     int nDevId: �豸������
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetTrigImgCountRange(int* pnRangeMin, int* pnRangeMax, int nDevId);



/******************************************************************************
* Function:	HV_LabVIEWGetSnapExpTimeRange
* Description: ��ȡ����ģʽʱ���ع�ʱ��(ExposureTime)����Чֵ��Χ.ʱ�䵥λΪus.
* Format:
*     int HV_LabVIEWGetSnapExpTimeRange(int* pnRangeMin, int* pnRangeMax, int nDevId)
* Params:
*	 int* pnRangeMin: ��������ģʽʱ���ع�ʱ��(ExposureTime)����Чֵ��Χ����Сֵ,��λΪ΢�롣���������
*	 int* pnRangeMax: ��������ģʽʱ���ع�ʱ��(ExposureTime)����Чֵ��Χ�����ֵ,��λΪ΢�롣���������
*     int nDevId: �豸������
* Return:
*     HV_SUCCESS: �ɹ�
*	  HVOCX_INVALID_PARAM: ��Ч����
*	  HVOCX_GET_PARAMINFO_FAIL����ȡ������Ϣʧ��
******************************************************************************/
INDCAM_LABVIEW_API int __stdcall HV_LabVIEWGetSnapExpTimeRange(int* pnRangeMin, int* pnRangeMax, int nDevId);







	

// ERRORs
#define HVOCX_DEVICE_STATUS_EXIST				-1				//״̬�Ѿ����ڣ��������ظ�������ͬ״̬
#define HVOCX_DEVICE_START_FAIL					-2				//�����豸ʧ��
#define HVOCX_DEVICE_STOP_FAIL					-3				//ֹͣ�豸ʧ��
#define	HVOCX_DEVICE_SUSPEND_FAIL				-4				//�����豸�����ݴ���ʧ��
#define HVOCX_DEVICE_RESUME_FAIL				-5				//�ָ��豸�����ݴ���ʧ��

#define HVOCX_SAVE_IMAGE_FAIL					-6				//����ͼƬʧ��
#define HVOCX_INVALID_PARAM						-7			    //��Ч����
#define HVOCX_GET_DEVICELIST_FAIL				-8				//��ȡ�豸�б�ʧ��
#define HVOCX_NO_SUCH_DEVICE					-9				//�豸�����ڻ���Ч�豸
#define HVOCX_NO_SUCH_DEVICETYPE				-10				//�Ҳ���ָ�����豸����
#define HVOCX_DEVICE_INI_FAIL					-11				//�豸��ʼ��ʧ��
#define HVOCX_SET_CALLBACK_FAIL					-12				//���ûص�����ʧ��
#define HVOCX_INVALID_HANDLE_VALUE				-13				//��Ч�ľ��ֵ
#define HVOCX_GET_DATABUF_FAIL					-14				//��ȡͼ������ʧ��
#define HVOCX_GET_PARAMINFO_FAIL				-15				//��ȡ������Ϣʧ��
#define HVOCX_SET_PARAMINFO_FAIL				-16				//���ò�����Ϣʧ��
#define HVOCX_ENTER_TRIGGERMODE_FAIL			-17				//���봥��ģʽʧ��
#define HVOCX_LEAVE_TRIGGERMODE_FAIL			-18				//�뿪����ģʽʧ��
#define HVOCX_NO_DEVICE_SELECTED				-19				//û��ѡ���豸
#define HVOCX_GET_DEVICE_FAIL					-20				//��ȡָ���豸ʧ��
#define HVOCX_SAVE_CONFIGURATION_FAIL			-21				//�����������ʧ��
#define HVOCX_GET_NO_DATA						-22				//δ�õ�����

//GigE
#define HVOCX_DEVICE_OPEN_FAIL					-23				//���豸ʧ��



#define HVOCX_SHOW_CONTROL_PAGE_FAIL			-24				//��ʾ����ҳʧ��
#define HVOCX_SOFTWARE_TRIGGER_FAIL		    	-25             //�������ʧ��
