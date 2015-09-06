// AxisOperate.cpp: implementation of the CAxisOperate class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "AxisOperate.h"
//#include "Variable.h"
#include "LYPESoldering.h"
#include "stdlib.h"
#include "General.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#pragma comment(lib,"ADVMOT.lib")


CAxisOperate::CAxisOperate()
{
	memset(m_avaDevs,0,sizeof(m_avaDevs));
}

CAxisOperate::~CAxisOperate()
{

}

BOOL CAxisOperate::OpenDevice()
{
	U32			Result;
	ULONG		deviceNumber=0;
	ULONG		buffLen=4;
	ULONG		AxesPerDev,AxisNumber;
	CString		strString;

	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	Result = Acm_GetAvailableDevs(m_avaDevs,MAX_DEVICES,&deviceNumber);
	if (Result!=SUCCESS)
	{
		AfxMessageBox(_T("no available device in system"));
		return FALSE;
	}

	m_dwDevNum=m_avaDevs[0].dwDeviceNum;
	Result = Acm_DevOpen(m_dwDevNum, &pApp->mVar.m_Devhand);
	if (Result != SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strString.Format(_T("Open Device Failed with Error Code:%x"),Result);
			AfxMessageBox(strString);
		}
		return FALSE;
	}

	Result = Acm_GetProperty(pApp->mVar.m_Devhand,FT_DevAxesCount,&AxesPerDev,&buffLen);
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strString.Format(_T("Get Device Axes Count Failed with Error Code:%x"),Result);
			AfxMessageBox(strString);
		}
		return FALSE;
	}
	
	AxisNumber=AxesPerDev;
	
	pApp->mVar.m_ulAxisCount=3;//AxisNumber;	

	for(AxisNumber=0;AxisNumber<pApp->mVar.m_ulAxisCount;AxisNumber++)
	{
		//Open every Axis and get the each Axis Handle
		//And Initial property for each Axis 		
		//Open Axis 
		Result =Acm_AxOpen(pApp->mVar.m_Devhand, (USHORT)AxisNumber, &pApp->mVar.m_Axishand[AxisNumber]);
		if(Result != SUCCESS)
		{
			if(pApp->mVar.MESSAGEENABLE)
			{
				strString.Format(_T("Open Axis Failed with Error Code:%x"),Result);
				AfxMessageBox(strString);
			}
			return FALSE;
		}
        //Reset Command Counter
		Acm_AxSetCmdPosition(pApp->mVar.m_Axishand[AxisNumber],  0);	
		
		Result=Acm_AxSetSvOn(pApp->mVar.m_Axishand[AxisNumber],0);
		if(Result != SUCCESS)
		{
			if(pApp->mVar.MESSAGEENABLE)
			{
				strString.Format(_T("Servo On Failed with Error Code:%x"),Result);
				AfxMessageBox(strString);
			}
			return FALSE;
		}
		pApp->mVar.m_bServoOn=true;
	}

	pApp->mVar.m_bInit = TRUE;
	pApp->mVar.m_ulCurAxis=0;
	return TRUE;
}

BOOL CAxisOperate::LoadConfig()
{
	U32		Result;
//	char	TempPath[128];

	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	CString strString(pApp->mVar.m_TotalPathName);
	strString+=_T("\\SysConfig.cfg");

	//注意：以下n和len的值大小不同,n是按字符计算的，len是按字节计算的
	int n = strString.GetLength();     // n = 14, len = 18
	//获取宽字节字符的大小，大小是按字节计算的
	int len = WideCharToMultiByte(CP_ACP,0,strString,strString.GetLength(),NULL,0,NULL,NULL);
	//为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小
	char * pFileName = new char[len+1];   //以字节为单位
	//宽字节编码转换成多字节编码
	WideCharToMultiByte(CP_ACP,0,strString,strString.GetLength(),pFileName,len,NULL,NULL);
	pFileName[len] = '\0';   //多字节字符以'/0'结束
	
	Result=Acm_DevLoadConfig(pApp->mVar.m_Devhand,pFileName/*(char *)strString.GetBuffer(strString.GetLength())*/);
	if(Result != SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strString.Format(_T("Load config Failed with Error Code:%xh"),Result);
			AfxMessageBox(strString);
		}
		return FALSE;
	}	
	return TRUE;
}

BOOL CAxisOperate::CloseDevice()
{
	USHORT		usAxisState[3];
	UINT		AxisNum;

	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	//Stop Every Axes
	if (pApp->mVar.m_bInit == TRUE)
	{
		for (AxisNum=0;AxisNum<pApp->mVar.m_ulAxisCount;AxisNum++)
		{
			Acm_AxGetState(pApp->mVar.m_Axishand[AxisNum], &usAxisState[AxisNum]);
			if(usAxisState[AxisNum]==STA_AX_ERROR_STOP)
			{
				Acm_AxResetError(pApp->mVar.m_Axishand[AxisNum]);					
				Acm_AxStopDec(pApp->mVar.m_Axishand[AxisNum]);
			}
		}

		//Close Axes
		for(AxisNum=0;AxisNum<pApp->mVar.m_ulAxisCount;AxisNum++)
		{
			Acm_AxClose(&pApp->mVar.m_Axishand[AxisNum]);
		}
		//Close Device
		Acm_DevClose(&pApp->mVar.m_Devhand);

		pApp->mVar.m_bInit = FALSE;
	}	
	return TRUE;
}

BOOL CAxisOperate::AxisMoveVel(U16 AxisNumber,U16 Direction)
{
	U16			AxisState;
	U32			Result;
	CString		strString;

	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	Result=Acm_AxGetState(pApp->mVar.m_Axishand[AxisNumber],&AxisState);

	if (AxisState==STA_AX_READY)
	{
		Result=Acm_AxMoveVel(pApp->mVar.m_Axishand[AxisNumber],Direction);
		if(Result != SUCCESS)
		{
			if(pApp->mVar.MESSAGEENABLE)
			{
				strString.Format(_T("Vol Move failed with Error Code:%xh"),Result);
				AfxMessageBox(strString);
			}
			return FALSE;
		}	
	}
	return TRUE;
}

double CAxisOperate::GetAxisRealPos(U16 AxisNumber)
{
//	U16			AxisState;
	U32			Result;
	CString		strString;
	double		CurPos;

	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	Result=Acm_AxGetCmdPosition(pApp->mVar.m_Axishand[AxisNumber],&CurPos);
	if(Result != SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strString.Format(_T("Get Axis Real Pos failed with Error Code:%xh"),Result);
			AfxMessageBox(strString);
		}
		return 0;	
	}
	return CurPos;
}

BOOL CAxisOperate::AxisStopVel(U16 AxisNumber)
{
	USHORT usAxisState=0;
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	//if axis is in error state , reset it first. then Stop Axes
	Acm_AxGetState(pApp->mVar.m_Axishand[AxisNumber], &usAxisState);
	if(usAxisState==STA_AX_ERROR_STOP)
	{
		Acm_AxResetError(pApp->mVar.m_Axishand[AxisNumber]);
	}
				
	Acm_AxStopEmg(pApp->mVar.m_Axishand[AxisNumber]);
	return TRUE;	
}

BOOL CAxisOperate::AxisStopDec(U16 AxisNumber)
{
	USHORT usAxisState=0;
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	//if axis is in error state , reset it first. then Stop Axes
	Acm_GpGetState(pApp->mVar.m_GpHand,&usAxisState);
	if( usAxisState == STA_GP_ERROR_STOP)
	{	
		Acm_GpResetError(pApp->mVar.m_GpHand);
	}		
	Acm_GpStopEmg(pApp->mVar.m_GpHand);

	Acm_AxGetState(pApp->mVar.m_Axishand[AxisNumber], &usAxisState);
	if(usAxisState==STA_AX_ERROR_STOP)
	{
		Acm_AxResetError(pApp->mVar.m_Axishand[AxisNumber]);
	}
				
	Acm_AxStopDec(pApp->mVar.m_Axishand[AxisNumber]);
	return TRUE;	
}

BOOL CAxisOperate::AxisMovePtp(U16 AxisNumber,double EndPoint,U16 AbsOrRel)
{
	CString		strString;
	U16			State;
	U32			Result;

	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	if(AbsOrRel==1)// For Relative Movement
	{
		Result=Acm_AxGetState (pApp->mVar.m_Axishand[AxisNumber],&State);
		if(Result != SUCCESS)
		{
			if(pApp->mVar.MESSAGEENABLE)
			{
				strString.Format(_T("Axis:%d Get State Failed with Error Code:%xh"),AxisNumber,Result);
				AfxMessageBox(strString);
			}
			return FALSE;
		}
		if (State!=STA_AX_READY)
		{
			if(pApp->mVar.MESSAGEENABLE)
			{
				strString.Format(_T("Axis:%d is not ready"),AxisNumber);
				AfxMessageBox(strString);
			}
			return FALSE;
		}
		Result=Acm_AxMoveRel(pApp->mVar.m_Axishand[AxisNumber],EndPoint);//*pApp->mVar.PULSEPERMM[AxisNumber]);
		if(Result != SUCCESS)
		{
			if(pApp->mVar.MESSAGEENABLE)
			{
				strString.Format(_T("Axis:%d Move Rel Failed with Error Code:%xh"),AxisNumber,Result);
				AfxMessageBox(strString);
			}
			return FALSE;
		}
	}
	else	//For Absolute movement
	{
		Result=Acm_AxGetState (pApp->mVar.m_Axishand[AxisNumber],&State);
		if(Result != SUCCESS)
		{
			if(pApp->mVar.MESSAGEENABLE)
			{
				strString.Format(_T("Axis:%d Get State Failed with Error Code:%xh"),AxisNumber,Result);
				AfxMessageBox(strString);
			}
			return FALSE;
		}
		if (State!=STA_AX_READY)
		{
			if(pApp->mVar.MESSAGEENABLE)
			{
				strString.Format(_T("Axis:%d's state(%d) is Invalid"),AxisNumber,State);
				AfxMessageBox(strString);
			}
			return FALSE;
		}
//		if(!pApp->mVar.AXISDIRECTION[AxisNumber])
//			tempdou=EndPoint;//*pApp->mVar.PULSEPERMM[AxisNumber];
//		else
//			tempdou=-EndPoint;//*pApp->mVar.PULSEPERMM[AxisNumber];
		Result=Acm_AxMoveAbs(pApp->mVar.m_Axishand[AxisNumber],EndPoint);
		if(Result != SUCCESS)
		{
			if(pApp->mVar.MESSAGEENABLE)
			{
				strString.Format(_T("Axis:%d Move Abs Failed with Error Code:%xh"),AxisNumber,Result);
				AfxMessageBox(strString);
			}
			return FALSE;
		}	
	}
	return TRUE;
}

BOOL CAxisOperate::AxesMoveTo(AxisCoordinate axiscoor)
{
	if(!AxisMovePtp(0,axiscoor.AxisXCoor,0))
		return FALSE;
	if(!AxisMovePtp(1,axiscoor.AxisYCoor,0))
		return FALSE;
	if(!AxisMovePtp(2,axiscoor.AxisZCoor,0))
		return FALSE;
//	if(!AxisMovePtp(3,axiscoor.AxisAoor,0))
//		return FALSE;
	return TRUE;
}

BOOL CAxisOperate::AxisHome(U16 AxisNumber,U16 HomeMode)
{
	U32			Result;
	CString		strTemp;

	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	Result= Acm_AxHome(pApp->mVar.m_Axishand[AxisNumber], HomeMode, pApp->mVar.HOMEDIRECTION[AxisNumber]?1:0);
	if (Result!=SUCCESS)
	{		
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("AxHome Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CAxisOperate::AxisHomeOptionSet(U16 AxisNumber)
{
	U32			Result;
	CString		strString;

	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], CFG_AxElLogic,
		&pApp->mVar.HOMELIMITLOGIC[AxisNumber], sizeof(pApp->mVar.HOMELIMITLOGIC[AxisNumber]));
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strString.Format(_T("Set Property-AxElLogic Failed with Error Code:%x"),Result);
			AfxMessageBox(strString);
		}
		return FALSE;
	}

	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], CFG_AxEzLogic, 
		&pApp->mVar.HOMEZLOGIC[AxisNumber], sizeof(pApp->mVar.HOMEZLOGIC[AxisNumber]));
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strString.Format(_T("Set Property-AxEzLogic Failed with Error Code:%x"),Result);
			AfxMessageBox(strString);
		}
		return FALSE;
	}

	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], CFG_AxOrgLogic, 
		&pApp->mVar.HOMEORGLOGIC[AxisNumber], sizeof(pApp->mVar.HOMEORGLOGIC[AxisNumber]));
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strString.Format(_T("Set Property-AxOrgLogic Failed with Error Code:%x"),Result);
			AfxMessageBox(strString);
		}
		return FALSE;
	}

	U32 m_HomeExSwitchMode=2;
	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], PAR_AxHomeExSwitchMode, 
		&m_HomeExSwitchMode, sizeof(m_HomeExSwitchMode));
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strString.Format(_T("Set Property-AxHomeExSwitchMode Failed with Error Code:%x"),Result);
			AfxMessageBox(strString);
		}
		return FALSE;
	}

	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], PAR_AxHomeCrossDistance, 
		&pApp->mVar.HOMECROSSDISTANCE[AxisNumber], sizeof(pApp->mVar.HOMECROSSDISTANCE[AxisNumber]));
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strString.Format(_T("Set Property-AxHomeCrossDistance Failed with Error Code:%x"),Result);
			AfxMessageBox(strString);
		}
		return FALSE;
	}
	
	return TRUE;
}

BOOL CAxisOperate::AxisVelSet(U16 AxisNumber,double VelHigh,double VelLow,double Acc,double Dec)
{
	U32 Result;
	CString strTemp;

	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	double tempdou=500;
	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], CFG_AxMaxVel, &tempdou, sizeof(tempdou));
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("AxHome Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], PAR_AxVelLow, &VelLow, sizeof(VelLow));
	if (Result!=SUCCESS)
	{	
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-AxVelLow Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], PAR_AxVelHigh, &VelHigh, sizeof(VelHigh));
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-AxVelHigh Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], PAR_AxAcc, &Acc, sizeof(Acc));
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-AxAcc Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], PAR_AxDec, &Dec, sizeof(Dec));
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-AxVelDec Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CAxisOperate::GrpVelSet(double GpVelHigh,double GpVelLow,double GpAcc,double GpDec)
{
	U32 Result;
	CString strTemp;

	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	Result= Acm_SetProperty(pApp->mVar.m_GpHand, PAR_GpVelLow, &GpVelLow, sizeof(GpVelLow));
	if (Result!=SUCCESS)
	{	
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-GpVelLow Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	Result= Acm_SetProperty(pApp->mVar.m_GpHand, PAR_GpVelHigh, &GpVelHigh, sizeof(GpVelHigh));
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-GpVelHigh Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	Result= Acm_SetProperty(pApp->mVar.m_GpHand, PAR_GpAcc, &GpAcc, sizeof(GpAcc));
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-GpAcc Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	Result= Acm_SetProperty(pApp->mVar.m_GpHand, PAR_GpDec, &GpDec, sizeof(GpDec));
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-GpVelDec Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CAxisOperate::SetAxisDirection(U16 AxisNumber,U32 AxPulseOutMode)
{
	U32 Result;
	CString strTemp;

	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], CFG_AxPulseOutMode, &AxPulseOutMode, sizeof(AxPulseOutMode));
	if (Result!=SUCCESS)
	{	
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-AxPulseOutMode Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CAxisOperate::SetAxisPulsePerMM(U16 AxisNumber,U32 AxPulsePerMM)
{
	U32 Result;
	CString strTemp;

	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], CFG_AxPPU, &AxPulsePerMM, sizeof(AxPulsePerMM));
	if (Result!=SUCCESS)
	{	
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-AxPulsePerMM Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CAxisOperate::AddAxisToGrp(unsigned short AxisNumber)
{
	U32 Result;
	CString strTemp;

	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	Result = Acm_GpAddAxis(&pApp->mVar.m_GpHand,pApp->mVar.m_Axishand[AxisNumber]);
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Add Axis To Group Failed With Error Code:%xh"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CAxisOperate::CloseGrp(void)
{
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();
	Acm_GpClose(&pApp->mVar.m_GpHand);
	return TRUE;
}

BOOL CAxisOperate::CircularInterpolation(double XEnd,double YEnd,
										 double XCenter,double YCenter,U16 CircularDir)
{
	U32			Result;
	U32			AxisNum=2;
	U16			State;
	double		CenterArray[2];
	double		EndArray[2];
	CString		strTemp;
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	CenterArray[0]=XCenter;
	CenterArray[1]=YCenter;
	EndArray[0]=XEnd;
	EndArray[1]=YEnd;
	Result = Acm_GpGetState(pApp->mVar.m_GpHand,&State);
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Gp Get State Failed With Error Code:%xh"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;	
	}
	if (State != STA_GP_READY)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Gp's State Error:%xh"),State);
			AfxMessageBox(strTemp);
		}
		return FALSE;	
	}

	Result =Acm_GpMoveCircularAbs(pApp->mVar.m_GpHand,CenterArray,EndArray,&AxisNum,CircularDir);
		
	if (Result!=SUCCESS)
	{
		if (!(Result & Warning) && pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Move CircularAbs Failed With Error Code:%xh"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}						
	return TRUE;
}
	
BOOL CAxisOperate::LinearInterpolation(double XEnd,double YEnd,double ZEnd)
{
	U32			Result;
	U32			AxisNum=3;
	U16			State;
	double		EndArray[3];
	CString		strTemp;
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	EndArray[0]=XEnd;
	EndArray[1]=YEnd;
	EndArray[2]=ZEnd;
	Result = Acm_GpGetState(pApp->mVar.m_GpHand,&State);
	if (Result!=SUCCESS)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Gp Get State Failed With Error Code:%xh"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;	
	}
	if (State != STA_GP_READY)
	{
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Gp's State Error:%xh"),State);
			AfxMessageBox(strTemp);
		}
		return FALSE;	
	}

	Result =Acm_GpMoveLinearAbs(pApp->mVar.m_GpHand,EndArray,&AxisNum);
		
	if (Result!=SUCCESS)
	{
		if (pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Move LinearAbs Failed With Error Code:%xh"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	return TRUE;
}


BOOL CAxisOperate::GrpVelChange(double GrpVelNew)
{
	U32			Result;
	CString		strTemp;
	U16			Status;
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	Result =Acm_GpGetState(pApp->mVar.m_GpHand,&Status);
	if (Result==SUCCESS)
	{
		if(Status == STA_GP_READY)
		{
			return FALSE;
		}
	}
	Result =Acm_GpChangeVel(pApp->mVar.m_GpHand,GrpVelNew);
	if (Result!=SUCCESS)
	{
		if (pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Group Vel Change Failed With Error Code:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}						
	return TRUE;
}


BOOL CAxisOperate::AxisVelChange(U16 AxisNumber, double AxisVelNew)
{
	U32			Result;
	CString		strTemp;
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	Result =Acm_AxChangeVel(pApp->mVar.m_Axishand[AxisNumber],AxisVelNew);

	if (Result!=SUCCESS)
	{
		if (pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Axis Vel Change Failed With Error Code:%xh"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}						
	return TRUE;
}

BOOL CAxisOperate::AxisSetLimit(U16 AxisNumber,BOOL bUse,double NegLimit,double PosLimit)
{
	U32			Result;
	CString		strTemp;
	CLYPESolderingApp *pApp=(CLYPESolderingApp*)AfxGetApp();

	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], CFG_AxSwMelEnable, &bUse, sizeof(bUse));
	if (Result!=SUCCESS)
	{	
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-Use Limit Mel Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], CFG_AxSwPelEnable, &bUse, sizeof(bUse));
	if (Result!=SUCCESS)
	{	
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-Use Limit Pel Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	BOOL btemp=FALSE;
	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], CFG_AxSwMelReact, &btemp, sizeof(btemp));
	if (Result!=SUCCESS)
	{	
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-Neg Limit React Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], CFG_AxSwPelReact, &btemp, sizeof(btemp));
	if (Result!=SUCCESS)
	{	
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-Pos Limit React Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	int itemp;
	itemp=(int)(NegLimit*pApp->mVar.PULSEPERMM[AxisNumber]);
	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], CFG_AxSwMelValue, &itemp, sizeof(itemp));
	if (Result!=SUCCESS)
	{	
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-Neg Limit Coor Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	itemp=(int)(PosLimit*pApp->mVar.PULSEPERMM[AxisNumber]);
	Result= Acm_SetProperty(pApp->mVar.m_Axishand[AxisNumber], CFG_AxSwPelValue, &itemp, sizeof(itemp));
	if (Result!=SUCCESS)
	{	
		if(pApp->mVar.MESSAGEENABLE)
		{
			strTemp.Format(_T("Set Property-Pos Limit Coor Failed with error:%x"),Result);
			AfxMessageBox(strTemp);
		}
		return FALSE;
	}
	return TRUE;
}