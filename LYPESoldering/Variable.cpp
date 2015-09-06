// Variable.cpp: implementation of the CVariable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LYPESoldering.h"
#include "Variable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define STR_DOUBLE(x) (atof((LPSTR)(LPCTSTR)(x)))
#define STR_INT(x)    (atoi((LPSTR)(LPCTSTR)(x)))
static inline CString DOUBLE_STR3(double x){CString str; str.Format(_T("%.3f"),x); return str;}
static inline CString INT_STR(int x){CString str; str.Format(_T("%d"),x); return str;}
static inline CString NumToString(int x){CString str; switch(x){ case 0:str='X';break;
																case 1:str='Y';break;
																case 2:str='Z';break;
																case 3:str='A';break;};return str;}


CVariable::CVariable()
{
	totalpointnumber=2;
	currentpointnumber=0;
	m_IncXCoor=0;
	m_IncYCoor=0;
	m_IncZCoor=0;
	m_bOperating=FALSE;
	m_bHomeDown=FALSE;
	int i;
	for(i=0;i<totalpointnumber;i++)
	{
		m_autopara[i].AutoCoor.AxisXCoor=0.0;
		m_autopara[i].AutoCoor.AxisYCoor=0.0;
		m_autopara[i].AutoCoor.AxisZCoor=0.0;
		m_autopara[i].PointName = _T("");

		m_autopara[i].Current = 0;
		m_autopara[i].StartSpd = 0;
		m_autopara[i].StopSpd = 0;
		m_autopara[i].LaserStartDelay = 0;
		m_autopara[i].LaserStopDelay = 0;
		m_autopara[i].AutoTemp = 0;
	}
	m_autopara[0].PointType = 0;
	m_autopara[1].PointType = 2;
	MESSAGEENABLE=FALSE;
	BACKTOORIGIN=FALSE;
/*	SILKBACKDELAY=0;
	SILKMANUALSPEED=14;
	SILKBACKSPEED=30;
	SILKDETECT=FALSE;*/
	
	currentlasercurve=0;
	m_bServoOn=FALSE;
	m_bAbsPtp=FALSE;
	HOMEMODE=6;

	for(i=0;i<MAXAXISCOUNT;i++)
	{
		MAXCOOR[i]=200;
		MINCOOR[i]=-30;
		PULSEPERMM[i]=1000;
		ORIGIN[i]=0;
		AXISDIRECTION[i]=FALSE;
		HOMEVELLOW[i]=1.;
		HOMEVELHIGH[i]=10.;
		HOMEVELACC[i]=200;
		HOMEDIRECTION[i]=TRUE;
		HOMEZLOGIC[i]=FALSE;
		HOMEORGLOGIC[i]=FALSE;
		HOMELIMITLOGIC[i]=FALSE;
		HOMECROSSDISTANCE[i]=10.;

		MANUALVELHIGH[i]=30.;
		MANUALVELLOW[i]=10.;
		MANUALVELACC[i]=100.;
		MANUALVELDEC[i]=100.;

//		AUTOVELDEC[i]=200.;
		AUTOMAXVEL[i]=100.;
	}

	m_IO.ProcessInit();

	m_bKeyMoveEnable = FALSE;
	bStopped =FALSE;

	EXPOSURE= 5;
	GAIN = 9;
	CROSSX = 373;
	CROSSY = 267;
	VMIRROR = FALSE;
	LIGHT=80;

	KP=0;
	KI=0;
	KD=0;
	TEMPORATURERATIO=1;
/*	THRESHOLD=10;
	KP1=0;
	KD1=0;*/
	OPERATEMODE=FALSE;		//FALSE:电流模式，TRUE：功率模式

	memset(tempcurve,0,200);
	memset(spdcurve,0,200);

	FOOTSWITCHPORT=2;
	FOOTSWITCHENABLE=FALSE;
	COILSWITCHPORT=3;
	COILONDELAY=1;
	COILOFFDELAY=1;

	SIMULATION=FALSE;
	SINGLEPOINT=TRUE;
	CIRCLEOPERATE=FALSE;
	CIRCLEDELAY=2.0;
	ZUPDISTANCE=1.0;

	//load parameters (*.ini)
//	GetCurrentDirectory(256,m_IniPathName.GetBufferSetLength(MAX_PATH+1));
//	m_TotalPathName.ReleaseBuffer();
	TCHAR szPath[256];
    GetModuleFileName( NULL, szPath, 256 );
	CString str(szPath);
	int nIndex = str.ReverseFind(_T('\\'));
	CString pathstr(str, nIndex);
	m_TotalPathName=pathstr;
	m_IniPathName=pathstr + _T("\\total param.ini");
	m_sProjectFileName=_T("");
	m_sProjectPathName=_T("");

	TOTALOPERATINGTIMES = 0;
	TOTALOPERATINGCOUNTS = 0;
	StartTime = 0;
	CostTime = 0;
/*	RECTCENTERX=200;
	RECTCENTERY=200;
	RECTWIDTH=30;
	RECTHEIGHT=10;
	RECTANGLE=0;

	ZTEMPUPDISTANCE=0;
//	LASERDELAY=0;
//	ZDOWNDELAY=0;
//	ZUPDELAY=0;
//	SILKLENGTHPEC = 0;
//	SILKSPDPEC = 0;
	CALIBSILKLENGTH=0;
	CALIBDETECTED=1;
	WhitePos=100;
	WHITESPACE=20;
	SEARCHLENGTH=300;
	DIRECTIONLEFT=FALSE;//默认从左向右
	*/
}

CVariable::~CVariable()
{
}

/*************************************************************
函数功能：	将采集的温度数据存入数组尾端
返 回 值：	无
时	  间：	2014-6-17
**************************************************************/
void CVariable::PullTempData(int tempdata)
{
	for(int i=0;i<199;i++)
	{
		tempcurve[i]=tempcurve[i+1];
	}
	tempcurve[199]=tempdata;
}

void CVariable::PullSpdData(int spddata)
{
	for(int i=0;i<199;i++)
	{
		spdcurve[i]=spdcurve[i+1];
	}
	spdcurve[199]=spddata;
}

/**************************************************************
函数功能：	将软件系统参数存入软件目录下的Initial parameters文件
返 回 值：	无
时	  间：	2014-6-17
***************************************************************/
void CVariable::ParametersSave_Total()
{
	//initial parameters
	m_Total_INI.SetPath(m_IniPathName, _T("Initial parameters"));
	//initial pos distance
	CString str,strLetter;

	strLetter=_T("MESSAGEENABLE");						m_Total_INI.SetValue(MESSAGEENABLE,strLetter);
	strLetter=_T("OPERATEMODE");						m_Total_INI.SetValue(OPERATEMODE,strLetter);
	strLetter=_T("BACKTOORIGIN");						m_Total_INI.SetValue(BACKTOORIGIN,strLetter);
	strLetter=_T("FOOTSWITCHPORT");						m_Total_INI.SetValue(FOOTSWITCHPORT,strLetter);
	strLetter=_T("FOOTSWITCHENABLE");					m_Total_INI.SetValue(FOOTSWITCHENABLE,strLetter);
	strLetter=_T("COILSWITCHPORT");						m_Total_INI.SetValue(COILSWITCHPORT,strLetter);
	strLetter=_T("COILONDELAY");						m_Total_INI.SetValue(COILONDELAY,strLetter);
	strLetter=_T("COILOFFDELAY");						m_Total_INI.SetValue(COILOFFDELAY,strLetter);

	strLetter=_T("SIMULATION");							m_Total_INI.SetValue(SIMULATION,strLetter);
	strLetter=_T("SINGLEPOINT");						m_Total_INI.SetValue(SINGLEPOINT,strLetter);
	strLetter=_T("CIRCLEOPERATE");						m_Total_INI.SetValue(CIRCLEOPERATE,strLetter);
	

	//运动控制部分
	strLetter=_T("HOMEMODE");							m_Total_INI.SetValue(HOMEMODE,strLetter);

	for(unsigned short i=0 ; i < MAXAXISCOUNT; i++)
	{
		str=NumToString(i);	
		strLetter=_T("AXIS ")+str+_T(" MAXCOOR");			m_Total_INI.SetValue(MAXCOOR[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" MINCOOR");			m_Total_INI.SetValue(MINCOOR[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" MAXCOOR");			m_Total_INI.SetValue(MAXCOOR[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" MINCOOR");			m_Total_INI.SetValue(MINCOOR[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" PULSEPERMM");		m_Total_INI.SetValue((int)PULSEPERMM[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" ORIGIN");			m_Total_INI.SetValue(ORIGIN[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" AXISDIRECTION");		m_Total_INI.SetValue(AXISDIRECTION[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMEVELLOW");		m_Total_INI.SetValue(HOMEVELLOW[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMEVELHIGH");		m_Total_INI.SetValue(HOMEVELHIGH[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMEVELACC");		m_Total_INI.SetValue(HOMEVELACC[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMEDIRECTION");		m_Total_INI.SetValue(HOMEDIRECTION[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMEZLOGIC");		m_Total_INI.SetValue(HOMEZLOGIC[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMEORGLOGIC");		m_Total_INI.SetValue(HOMEORGLOGIC[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMELIMITLOGIC");	m_Total_INI.SetValue(HOMELIMITLOGIC[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMECROSSDISTANCE");	m_Total_INI.SetValue(HOMECROSSDISTANCE[i],strLetter);

		strLetter=_T("AXIS ")+str+_T(" MANUALVELHIGH");		m_Total_INI.SetValue(MANUALVELHIGH[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" MANUALVELLOW");		m_Total_INI.SetValue(MANUALVELLOW[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" MANUALVELACC");		m_Total_INI.SetValue(MANUALVELACC[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" MANUALVELDEC");		m_Total_INI.SetValue(MANUALVELDEC[i],strLetter);

//		strLetter=_T("AXIS ")+str+_T(" AUTOVELDEC");		m_Total_INI.SetValue(AUTOVELDEC[i],strLetter);
		strLetter=_T("AXIS ")+str+_T(" AUTOMAXVEL");		m_Total_INI.SetValue(AUTOMAXVEL[i],strLetter);
	}

	//CCD图像显示
	strLetter=_T("CCD EXPOSURE");						m_Total_INI.SetValue(EXPOSURE,strLetter);
	strLetter=_T("CCD GAIN");							m_Total_INI.SetValue(GAIN,strLetter);
	strLetter=_T("CCD CROSSX");							m_Total_INI.SetValue(CROSSX,strLetter);
	strLetter=_T("CCD CROSSY");							m_Total_INI.SetValue(CROSSY,strLetter);
	strLetter=_T("CCD VMIRROR");						m_Total_INI.SetValue(VMIRROR,strLetter);
	strLetter=_T("CCD LIGHT");							m_Total_INI.SetValue(LIGHT,strLetter);
	strLetter=_T("TEMPORATURERATIO");					m_Total_INI.SetValue(TEMPORATURERATIO,strLetter);
	strLetter=_T("TOTALOPERATINGTIMES");				m_Total_INI.SetValue(TOTALOPERATINGTIMES,strLetter);
	strLetter=_T("TOTALOPERATINGCOUNTS");				m_Total_INI.SetValue(TOTALOPERATINGCOUNTS,strLetter);
}

/**************************************************************
函数功能：	将软件系统参数从软件目录下的Initial parameters文件中
			导入
返 回 值：	无
时	  间：	2014-6-17
***************************************************************/
void CVariable::ParametersLoad_Total()
{
	//initial parameters
	m_Total_INI.SetPath(m_IniPathName, _T("Initial parameters"));
	//initial pos distance
	CString str,strLetter;

	strLetter=_T("MESSAGEENABLE");						MESSAGEENABLE=m_Total_INI.GetIni(strLetter);
	strLetter=_T("OPERATEMODE");						OPERATEMODE=m_Total_INI.GetIni(strLetter);
	strLetter=_T("BACKTOORIGIN");						BACKTOORIGIN=m_Total_INI.GetIni(strLetter);
	strLetter=_T("FOOTSWITCHPORT");						FOOTSWITCHPORT=m_Total_INI.GetIni(strLetter);
	strLetter=_T("FOOTSWITCHENABLE");					FOOTSWITCHENABLE=m_Total_INI.GetIni(strLetter);
	strLetter=_T("COILSWITCHPORT");						COILSWITCHPORT=m_Total_INI.GetIni(strLetter);
	strLetter=_T("COILONDELAY");						COILONDELAY=m_Total_INI.GetDouble(strLetter);
	strLetter=_T("COILOFFDELAY");						COILOFFDELAY=m_Total_INI.GetDouble(strLetter);

	strLetter=_T("SIMULATION");							SIMULATION=m_Total_INI.GetIni(strLetter);
	strLetter=_T("SINGLEPOINT");						SINGLEPOINT=m_Total_INI.GetIni(strLetter);
	strLetter=_T("CIRCLEOPERATE");						CIRCLEOPERATE=m_Total_INI.GetIni(strLetter);
	
	//运动控制部分
	strLetter=_T("HOMEMODE");							HOMEMODE=m_Total_INI.GetIni(strLetter);
	for(unsigned short i=0 ; i < MAXAXISCOUNT; i++)
	{
		str=NumToString(i);	
		strLetter=_T("AXIS ")+str+_T(" MAXCOOR");			MAXCOOR[i]=m_Total_INI.GetDouble(strLetter);
		strLetter=_T("AXIS ")+str+_T(" MINCOOR");			MINCOOR[i]=m_Total_INI.GetDouble(strLetter);
		strLetter=_T("AXIS ")+str+_T(" PULSEPERMM");		PULSEPERMM[i]=m_Total_INI.GetIni(strLetter);
		strLetter=_T("AXIS ")+str+_T(" ORIGIN");			ORIGIN[i]=m_Total_INI.GetDouble(strLetter);
		strLetter=_T("AXIS ")+str+_T(" AXISDIRECTION");		AXISDIRECTION[i]=m_Total_INI.GetIni(strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMEVELLOW");		HOMEVELLOW[i]=m_Total_INI.GetDouble(strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMEVELHIGH");		HOMEVELHIGH[i]=m_Total_INI.GetDouble(strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMEVELACC");		HOMEVELACC[i]=m_Total_INI.GetDouble(strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMEDIRECTION");		HOMEDIRECTION[i]=m_Total_INI.GetIni(strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMEZLOGIC");		HOMEZLOGIC[i]=m_Total_INI.GetIni(strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMEORGLOGIC");		HOMEORGLOGIC[i]=m_Total_INI.GetIni(strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMELIMITLOGIC");	HOMELIMITLOGIC[i]=m_Total_INI.GetIni(strLetter);
		strLetter=_T("AXIS ")+str+_T(" HOMECROSSDISTANCE");	HOMECROSSDISTANCE[i]=m_Total_INI.GetDouble(strLetter);

		strLetter=_T("AXIS ")+str+_T(" MANUALVELHIGH");		MANUALVELHIGH[i]=m_Total_INI.GetDouble(strLetter);
		strLetter=_T("AXIS ")+str+_T(" MANUALVELLOW");		MANUALVELLOW[i]=m_Total_INI.GetDouble(strLetter);
		strLetter=_T("AXIS ")+str+_T(" MANUALVELACC");		MANUALVELACC[i]=m_Total_INI.GetDouble(strLetter);
		strLetter=_T("AXIS ")+str+_T(" MANUALVELDEC");		MANUALVELDEC[i]=m_Total_INI.GetDouble(strLetter);

//		strLetter=_T("AXIS ")+str+_T(" AUTOVELDEC");		AUTOVELDEC[i]=m_Total_INI.GetDouble(strLetter);
		strLetter=_T("AXIS ")+str+_T(" AUTOMAXVEL");		AUTOMAXVEL[i]=m_Total_INI.GetDouble(strLetter);
	}

	//CCD图像显示
	strLetter=_T("CCD EXPOSURE");						EXPOSURE=m_Total_INI.GetIni(strLetter);
	strLetter=_T("CCD GAIN");							GAIN=m_Total_INI.GetIni(strLetter);
	strLetter=_T("CCD CROSSX");							CROSSX=m_Total_INI.GetIni(strLetter);
	strLetter=_T("CCD CROSSY");							CROSSY=m_Total_INI.GetIni(strLetter);
	strLetter=_T("CCD VMIRROR");						VMIRROR=m_Total_INI.GetIni(strLetter);
	strLetter=_T("CCD LIGHT");							LIGHT=m_Total_INI.GetIni(strLetter);
	strLetter=_T("TEMPORATURERATIO");					TEMPORATURERATIO=m_Total_INI.GetDouble(strLetter);
	strLetter=_T("TOTALOPERATINGTIMES");				TOTALOPERATINGTIMES=m_Total_INI.GetIni(strLetter);
	strLetter=_T("TOTALOPERATINGCOUNTS");				TOTALOPERATINGCOUNTS=m_Total_INI.GetIni(strLetter);
}

/**************************************************************
函数功能：	将工程文件参数存入至自命名文件中
返 回 值：	无
时	  间：	2014-6-17
***************************************************************/
void CVariable::ProjectSave(CString strPathName,CString strFileName)
{
	m_Point_INI.SetPath(strPathName,strFileName);
	//initial pos distance
	CString str,str2,strLetter;
	unsigned short i;
	strLetter=_T("TOTALPOINTNUMBER");						m_Point_INI.SetValue(totalpointnumber,strLetter);
	for(i=0 ; i < totalpointnumber; i++)
	{
		str=INT_STR(i);	

		strLetter=_T("POINT ")+str+_T(" XCOORDINATE");			m_Point_INI.SetValue(m_autopara[i].AutoCoor.AxisXCoor,strLetter);
		strLetter=_T("POINT ")+str+_T(" YCOORDINATE");			m_Point_INI.SetValue(m_autopara[i].AutoCoor.AxisYCoor,strLetter);
		strLetter=_T("POINT ")+str+_T(" ZCOORDINATE");			m_Point_INI.SetValue(m_autopara[i].AutoCoor.AxisZCoor,strLetter);
		
		strLetter=_T("POINT ")+str+_T(" POINTNAME");			m_Point_INI.SetValue(m_autopara[i].PointName,strLetter);
		strLetter=_T("POINT ")+str+_T(" Current");				m_Point_INI.SetValue(m_autopara[i].Current,strLetter);
		strLetter=_T("POINT ")+str+_T(" StartSpd");				m_Point_INI.SetValue(m_autopara[i].StartSpd,strLetter);
		strLetter=_T("POINT ")+str+_T(" StopSpd");				m_Point_INI.SetValue(m_autopara[i].StopSpd,strLetter);
		strLetter=_T("POINT ")+str+_T(" PointType");			m_Point_INI.SetValue(m_autopara[i].PointType,strLetter);
		strLetter=_T("POINT ")+str+_T(" LaserStartDelay");		m_Point_INI.SetValue(m_autopara[i].LaserStartDelay,strLetter);
		strLetter=_T("POINT ")+str+_T(" LaserStopDelay");		m_Point_INI.SetValue(m_autopara[i].LaserStopDelay,strLetter);
		strLetter=_T("POINT ")+str+_T(" AUTOTEMPERATURE");		m_Point_INI.SetValue(m_autopara[i].AutoTemp,strLetter);
	}
	strLetter=_T("PID KP");									m_Point_INI.SetValue(KP,strLetter);
	strLetter=_T("PID KI");									m_Point_INI.SetValue(KI,strLetter);
	strLetter=_T("PID KD");									m_Point_INI.SetValue(KD,strLetter);

	strLetter=_T("CIRCLEDELAY");							m_Point_INI.SetValue(CIRCLEDELAY,strLetter);
	strLetter=_T("ZUPDISTANCE");							m_Point_INI.SetValue(ZUPDISTANCE,strLetter);
}

/**************************************************************
函数功能：	从自命名文件中取出工程文件参数
返 回 值：	无
时	  间：	2014-6-17
***************************************************************/	
void CVariable::ProjectLoad(CString strPathName,CString strFileName)
{
	m_Point_INI.SetPath(strPathName, strFileName);
	//initial pos distance
	CString str,str2,strLetter;
	unsigned short i;
	strLetter=_T("TOTALPOINTNUMBER");					totalpointnumber=m_Point_INI.GetIni(strLetter);
	for(i=0 ; i < totalpointnumber; i++)
	{
		str=INT_STR(i);	
		strLetter=_T("POINT ")+str+_T(" XCOORDINATE");			m_autopara[i].AutoCoor.AxisXCoor=m_Point_INI.GetDouble(strLetter);
		strLetter=_T("POINT ")+str+_T(" YCOORDINATE");			m_autopara[i].AutoCoor.AxisYCoor=m_Point_INI.GetDouble(strLetter);
		strLetter=_T("POINT ")+str+_T(" ZCOORDINATE");			m_autopara[i].AutoCoor.AxisZCoor=m_Point_INI.GetDouble(strLetter);
	
		strLetter=_T("POINT ")+str+_T(" POINTNAME");			m_autopara[i].PointName=m_Point_INI.GetString(strLetter);

		strLetter=_T("POINT ")+str+_T(" Current");				m_autopara[i].Current=m_Point_INI.GetDouble(strLetter);
		strLetter=_T("POINT ")+str+_T(" StartSpd");				m_autopara[i].StartSpd=m_Point_INI.GetDouble(strLetter);
		strLetter=_T("POINT ")+str+_T(" StopSpd");				m_autopara[i].StopSpd=m_Point_INI.GetDouble(strLetter);
		strLetter=_T("POINT ")+str+_T(" PointType");			m_autopara[i].PointType=m_Point_INI.GetIni(strLetter);
		strLetter=_T("POINT ")+str+_T(" LaserStartDelay");		m_autopara[i].LaserStartDelay=m_Point_INI.GetDouble(strLetter);
		strLetter=_T("POINT ")+str+_T(" LaserStopDelay");		m_autopara[i].LaserStopDelay=m_Point_INI.GetDouble(strLetter);
		strLetter=_T("POINT ")+str+_T(" AUTOTEMPERATURE");		m_autopara[i].AutoTemp=m_Point_INI.GetIni(strLetter);
	}
	strLetter=_T("PID KP");									KP=m_Point_INI.GetDouble(strLetter);
	strLetter=_T("PID KI");									KI=m_Point_INI.GetDouble(strLetter);
	strLetter=_T("PID KD");									KD=m_Point_INI.GetDouble(strLetter);
	
	strLetter=_T("CIRCLEDELAY");							CIRCLEDELAY=m_Point_INI.GetDouble(strLetter);
	strLetter=_T("ZUPDISTANCE");							ZUPDISTANCE=m_Point_INI.GetDouble(strLetter);
}