// Variable.h: interface for the CVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VARIABLE_H__ACF4BE02_B805_4277_95A2_550D40489626__INCLUDED_)
#define AFX_VARIABLE_H__ACF4BE02_B805_4277_95A2_550D40489626__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "AxisOperate.h"
#include "IOCard.h"
#include "ProfileINI.h"

#define SAMPLEFREQUENCY			200
#define SAMPLETEMPERATUREPORT	14
#define MAXLASERVOLTAGE			5
#define MAXAXISCOUNT			3
#define	MAXAUTOPOINTCOUNT		2000
#define	MAXPATHCOUNT			100
//#define TEMPORATURERADIO		2
#define PICTUREWIDTH			640
#define PICTUREHEIGHT			512

class CVariable 
{
public:
	CVariable();
	virtual ~CVariable();
	void	PullTempData(int tempdata);
	void	PullSpdData(int spddata);
	void	ParametersSave_Total();
	void	ParametersLoad_Total();
	void	ProjectSave(CString strPathName,CString strFileName);
	void	ProjectLoad(CString strPathName,CString strFileName);

//软件运行参数
//	HANDLE			hDevice;
	//参数导入导出
	CProfileINI		m_Total_INI; 
	CProfileINI		m_Point_INI;
	CString			m_TotalPathName;
	CString			m_IniPathName;
	CString			m_sProjectPathName;
	CString			m_sProjectFileName;
	BOOL			m_bOperating;
	BOOL			m_bHomeDown;
	//工作点参数
	int				currentpointnumber;
	int				currentlasercurve;

	double			m_IncXCoor;
	double			m_IncYCoor;
	double			m_IncZCoor;

	//运动控制
	CAxisOperate	axisoperate;
	ULONG			m_ulAxisCount;					//控制卡总轴数
	ULONG			m_ulCurAxis;					//当前轴编号
	BOOL			m_bInit;						//轴初始化
	HAND			m_Axishand[MAXAXISCOUNT];		//轴句柄
	HAND			m_Devhand;						//设备句柄
	BOOL			m_bServoOn;						//
	BOOL			m_bAbsPtp;						//0时绝对运动，1时相对运动
	double			m_dPtpDistance;					//手动运行时，点动位移量
	HAND			m_GpHand;

	CIOCard			m_IO;

	//其他
	BOOL			m_bKeyMoveEnable;
	BOOL			bStopped;
	double			RealCurrent;
	double			RealSpd;
	double			RealTemp;
	int				tempcurve[200];
	int				spdcurve[200];

//	BITMAPINFO		*m_pImgInfo;		//BITMAPINFO 结构指针，显示图像时使用
//	BYTE			*m_pImgBuffer;		//Bayer转换后缓冲区
public:				
//存入系统文件参数
	BOOL			MESSAGEENABLE;							//显示报错对话框
	BOOL			OPERATEMODE;							//选择电流/温度模式
	BOOL			BACKTOORIGIN;
	U16				FOOTSWITCHPORT;
	BOOL			FOOTSWITCHENABLE;
	U16				COILSWITCHPORT;
	double			COILONDELAY;
	double			COILOFFDELAY;

	BOOL			SIMULATION;
	BOOL			SINGLEPOINT;
	BOOL			CIRCLEOPERATE;

	int				TOTALOPERATINGTIMES;
	int				TOTALOPERATINGCOUNTS;
	
	//运动控制部分
	U16				HOMEMODE;
	double			MAXCOOR[MAXAXISCOUNT];
	double			MINCOOR[MAXAXISCOUNT];
	UINT			PULSEPERMM[MAXAXISCOUNT];
	BOOL			AXISDIRECTION[MAXAXISCOUNT];
	double			ORIGIN[MAXAXISCOUNT];
	double			HOMEVELLOW[MAXAXISCOUNT];		
	double			HOMEVELHIGH[MAXAXISCOUNT];		
	double			HOMEVELACC[MAXAXISCOUNT];		

	BOOL			HOMEDIRECTION[MAXAXISCOUNT];
	BOOL			HOMEZLOGIC[MAXAXISCOUNT];
	BOOL			HOMEORGLOGIC[MAXAXISCOUNT];
	BOOL			HOMELIMITLOGIC[MAXAXISCOUNT];
	double			HOMECROSSDISTANCE[MAXAXISCOUNT];

	double			MANUALVELHIGH[MAXAXISCOUNT];
	double			MANUALVELLOW[MAXAXISCOUNT];
	double			MANUALVELACC[MAXAXISCOUNT];
	double			MANUALVELDEC[MAXAXISCOUNT];

//	double			AUTOVELDEC[MAXAXISCOUNT];
	double			AUTOMAXVEL[MAXAXISCOUNT];
	

	//CCD图像显示
	int				EXPOSURE;
	int				GAIN;
	int				CROSSX;
	int				CROSSY;
	BOOL			VMIRROR;
	int				LIGHT;
	DWORD			StartTime;
	double			CostTime;
//存入工程文件参数
	AutoParameter	m_autopara[MAXAUTOPOINTCOUNT];
//	LaserCurve		m_sLaserCurve[10];
	int				totalpointnumber;
	double			CIRCLEDELAY;
	double			ZUPDISTANCE;

	double			KP;
	double			KI;
	double			KD;
	double			TEMPORATURERATIO;
/*	double			SILKBACKDELAY;
	int				SILKMANUALSPEED;
	int				SILKBACKSPEED;
	BOOL			SILKDETECT;
	//温度反馈PID
	
	
	double			THRESHOLD;
	double			KP1;
	double			KD1;

	int				RECTCENTERX;
	int				RECTCENTERY;
	int				RECTWIDTH;
	int				RECTHEIGHT;
	int				RECTANGLE;

	double			ZTEMPUPDISTANCE;
//	double			LASERDELAY;
//	double			ZDOWNDELAY;
//	double			ZUPDELAY;
//	int				SILKLENGTHPEC;
//	int				SILKSPDPEC;
	double			CALIBSILKLENGTH;
	double			CALIBDETECTED;
	int				WhitePos;
	double			WHITESPACE;
	double			SEARCHLENGTH;
	BOOL			DIRECTIONLEFT;*/
};
#endif // !defined(AFX_VARIABLE_H__ACF4BE02_B805_4277_95A2_550D40489626__INCLUDED_)