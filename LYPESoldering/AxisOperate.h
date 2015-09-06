//AxisOperate.h:interface for the axisoperate class
//
/////////////////////////////////////////

#if !defined(AFX_AXISOPERATE_H__793BC1B2_F372_494B_B0A1_6E165F2319DD__INCLUDED_)
#define AFX_AXISOPERATE_H__793BC1B2_F372_494B_B0A1_6E165F2319DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Classes.h"

#include "AdvMotDrv.h"
#include "AdvMotApi.h"


class CAxisOperate
{
public:
	DEVLIST	m_avaDevs[MAX_DEVICES];
	DWORD	m_dwDevNum;
	U16		m_bDirection[MAX_DEVICES];
	
public:	
	CAxisOperate();
	~CAxisOperate();

	BOOL OpenDevice(void);
	BOOL LoadConfig(void);
	BOOL CloseDevice(void);
	BOOL AxisMoveVel(U16 AxisNumber,U16 Direction);
	BOOL AxisStopVel(U16 AxisNumber);
	BOOL AxisStopDec(U16 AxisNumber);
	BOOL AxisMovePtp(U16 AxisNumber,double EndPoint,U16 AbsOrRel);
	BOOL AxesMoveTo(AxisCoordinate axiscoor);
	BOOL AxisHome(U16 AxisNumber,U16 HomeMode);
	BOOL AxisHomeOptionSet(U16 AxisNumber);
	BOOL AxisVelSet(U16 AxisNumber,double VelHigh,double VelLow,double Acc,double Dec);
	BOOL AxisVelChange(U16 AxisNumber, double AxisVelNew);
	double GetAxisRealPos(U16 AxisNumber);
	BOOL AxisSetLimit(U16 AxisNumber,BOOL bUse,double NegLimit,double PosLimit);

	BOOL SetAxisDirection(U16 AxisNumber,U32 AxPulseOutMode);
	BOOL SetAxisPulsePerMM(U16 AxisNumber,U32 AxPulsePerMM);
	BOOL AddAxisToGrp(unsigned short AxisNumber);
	BOOL CloseGrp(void);
	BOOL CircularInterpolation(double XEnd,double YEnd,double XCenter,double YCenter,U16 CircularDir);
	BOOL LinearInterpolation(double XEnd,double YEnd,double ZEnd);
	BOOL GrpVelSet(double GpVelHigh,double GpVelLow,double GpAcc,double GpDec);
	BOOL GrpVelChange(double GrpVelNew);
};
#endif  //!defined(AFX_AXISOPERATE_H__793BC1B2_F372_494B_B0A1_6E165F2319DD__INCLUDED_)