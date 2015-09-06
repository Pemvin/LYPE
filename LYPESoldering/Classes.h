//Classes.h
#define MAX_DEVICES 4

typedef struct SAxisCoordinate
{
	double AxisXCoor;
	double AxisYCoor;
	double AxisZCoor;
//	double AxisACoor;
}AxisCoordinate;

typedef struct SAxisSpeed
{
	int AxisXSpd;
	int AxisYSpd;
	int AxisZSpd;
//	int AxisASpd;
}AxisSpeed;

typedef struct SAutoParameter
{
	AxisCoordinate  AutoCoor;
	CString			PointName;
	double	Current;
	double	StartSpd;
	double	StopSpd;
	double	LaserStartDelay;
	double  LaserStopDelay;
	int		PointType;
	int		AutoTemp;
}AutoParameter;

/*
typedef struct SLaserCurve
{
	int currentprecent[10];
	int timeprecent[10];
}LaserCurve;
*/