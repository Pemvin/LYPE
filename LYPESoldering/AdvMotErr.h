//
// Copyright (c) Advantech Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Advantech end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//


#ifndef __ADV_MOT_ERR_H__
#define __ADV_MOT_ERR_H__

#ifndef SUCCESS
#define SUCCESS						0x00000000
#endif
#define Warning                     0x10000000
#define FuncError					0x80000000
#define CommError					0x80001000
#define MotionError				    0x80002000
#define DaqError					0x80003000
#define DevEvtError                 0x80004000
#define DspError                    0x80005000 //  [9/26/2011 dan.yang]
#define DspAxError                  0x80005100 //  [9/26/2011 dan.yang]
#define DspGpError                  0x80005200 //  [9/26/2011 dan.yang]
#define DspRbError                  0x80005500
#define GmError						0x81000000	//by dujunling on 2012.11.22 for GM code error

#define InvalidDevNumber			(FuncError + 0)
#define DevRegDataLost			    (FuncError + 1)
#define LoadDllFailed				(FuncError + 2)
#define GetProcAddrFailed        (FuncError + 3)
#define MemAllocateFailed        (FuncError + 4)
#define InvalidHandle				(FuncError + 5)
#define CreateFileFailed         (FuncError + 6)
#define OpenEventFailed          (FuncError + 7)
#define EventTimeOut             (FuncError + 8)
#define InvalidInputParam			(FuncError + 9)
#define PropertyIDNotSupport		(FuncError + 10)
#define PropertyIDReadOnly			(FuncError + 11)
#define ConnectWinIrqFailed		    (FuncError + 12)

#define InvalidAxCfgVel				(FuncError + 13)
#define InvalidAxCfgAcc				(FuncError + 14)
#define InvalidAxCfgDec				(FuncError + 15)
#define InvalidAxCfgJerk			(FuncError + 16)
#define InvalidAxParVelLow			(FuncError + 17)
#define InvalidAxParVelHigh	  	    (FuncError + 18)
#define InvalidAxParAcc				(FuncError + 19)
#define InvalidAxParDec				(FuncError + 20)
#define InvalidAxParJerk			(FuncError + 21)
#define InvalidAxPulseInMode		(FuncError + 22)
#define InvalidAxPulseOutMode		(FuncError + 23)
#define InvalidAxAlarmEn			(FuncError + 24)
#define InvalidAxAlarmLogic		    (FuncError + 25)
#define InvalidAxInPEn				(FuncError + 26)
#define InvalidAxInPLogic			(FuncError + 27)
#define InvalidAxHLmtEn				(FuncError + 28)
#define InvalidAxHLmtLogic			(FuncError + 29)
#define InvalidAxHLmtReact			(FuncError + 30)
#define InvalidAxSLmtPEn			(FuncError + 31)
#define InvalidAxSLmtPReact	   (FuncError + 32)
#define InvalidAxSLmtPValue		(FuncError + 33)
#define InvalidAxSLmtMEn			(FuncError + 34)
#define InvalidAxSLmtMReact		(FuncError + 35)
#define InvalidAxSLmtMValue		(FuncError + 36)
#define InvalidAxOrgLogic			(FuncError + 37)
#define InvalidAxOrgEnable			(FuncError + 38)
#define InvalidAxEzLogic			(FuncError + 39)
#define InvalidAxEzEnable			(FuncError + 40)
#define InvalidAxEzCount			(FuncError + 41)
#define InvalidAxState  			(FuncError + 42)
#define InvalidAxInEnable			(FuncError + 43)


#define InvalidAxSvOnOff			(FuncError + 44)
#define InvalidAxDistance			(FuncError + 45)
#define InvalidAxPosition			(FuncError + 46)
#define InvalidAxHomeModeKw	   (FuncError + 47)

#define InvalidAxCntInGp			(FuncError + 48)
#define AxInGpNotFound				(FuncError + 49)
#define AxIsInOtherGp				(FuncError + 50)
#define AxCannotIntoGp				(FuncError + 51)
#define GpInDevNotFound				(FuncError + 52)
#define InvalidGpCfgVel				(FuncError + 53)
#define InvalidGpCfgAcc				(FuncError + 54)
#define InvalidGpCfgDec				(FuncError + 55)
#define InvalidGpCfgJerk			(FuncError + 56)
#define InvalidGpParVelLow			(FuncError + 57)
#define InvalidGpParVelHigh	        (FuncError + 58)
#define InvalidGpParAcc				(FuncError + 59)
#define InvalidGpParDec				(FuncError + 60)
#define InvalidGpParJerk			(FuncError + 61)
#define JerkNotSupport		        (FuncError + 62)
#define ThreeAxNotSupport           (FuncError + 63)
#define DevIpoNotFinished		    (FuncError + 64)
#define InvalidGpState				(FuncError + 65)
#define OpenFileFailed		        (FuncError + 66)
#define InvalidPathCnt		        (FuncError + 67)
#define InvalidPathHandle		    (FuncError + 68)
#define InvalidPath                 (FuncError + 69)

#define IoctlError		            (FuncError + 70)
#define AmnetRingUsed		        (FuncError + 71)
#define DeviceNotOpened		        (FuncError + 72)
#define InvalidRing			        (FuncError + 73)
#define InvalidSlaveIP			   (FuncError + 74)
#define InvalidParameter		   (FuncError + 75)
#define InvalidGpCenterPosition	   (FuncError + 76)
#define InvalidGpEndPosition	   (FuncError + 77)
#define InvalidAddress			   (FuncError + 78)
#define DeviceDisconnect		   (FuncError + 79)
#define DataOutBufExceeded		   (FuncError + 80)
#define SlaveDeviceNotMatch			(FuncError + 81)
#define SlaveDeviceError		   (FuncError + 82)
#define SlaveDeviceUnknow		   (FuncError + 83)
#define FunctionNotSupport			(FuncError + 84)
#define InvalidPhysicalAxis			(FuncError + 85)			//[Dean 2008.1.31]
#define InvalidVelocity				(FuncError + 86)			//[Dean 2008.2.5]
#define InvalidAxPulseInLogic		(FuncError + 87)			//[Dean 2008.2.13]
#define InvalidAxPulseInSource		(FuncError + 88)			//[Dean 2008.2.13]
#define InvalidAxErcLogic			(FuncError + 89)			//[Dean 2008.2.13]
#define InvalidAxErcOnTime			(FuncError + 90)			//[Dean 2008.2.13]
#define InvalidAxErcOffTime			(FuncError + 91)			//[Dean 2008.2.13]
#define InvalidAxErcEnableMode		(FuncError + 92)			//[Dean 2008.2.13]
#define InvalidAxSdEnable			(FuncError + 93)			//[Dean 2008.2.13]
#define InvalidAxSdLogic			(FuncError + 94)			//[Dean 2008.2.13]
#define InvalidAxSdReact			(FuncError + 95)			//[Dean 2008.2.13]
#define InvalidAxSdLatch			(FuncError + 96)			//[Dean 2008.2.13]
#define InvalidAxHomeResetEnable	(FuncError + 97)			//[Dean 2008.2.13]
#define InvalidAxBacklashEnable		(FuncError + 98)			//[Dean 2008.2.13]
#define InvalidAxBacklashPulses		(FuncError + 99)			//[Dean 2008.2.13]
#define InvalidAxVibrationEnable	(FuncError + 100)			//[Dean 2008.2.13]
#define InvalidAxVibrationRevTime	(FuncError + 101)			//[Dean 2008.2.13]
#define InvalidAxVibrationFwdTime	(FuncError + 102)			//[Dean 2008.2.13]
#define InvalidAxAlarmReact			(FuncError + 103)			//[Dean 2008.2.13]
#define InvalidAxLatchLogic			(FuncError + 104)			//[Dean 2008.2.13]
#define InvalidFwMemoryMode			(FuncError + 105)
#define InvalidConfigFile           (FuncError + 106)
#define InvalidAxEnEvtArraySize     (FuncError + 107)
#define InvalidAxEnEvtArray         (FuncError + 108)
#define InvalidGpEnEvtArraySize     (FuncError + 109)
#define InvalidGpEnEvtArray         (FuncError + 110)
#define InvalidIntervalData         (FuncError + 111)
#define InvalidEndPosition          (FuncError + 112)
#define InvalidAxisSelect			(FuncError + 113)
#define InvalidTableSize			(FuncError + 114)
#define InvalidGpHandle				(FuncError + 115)
#define InvalidCmpSource			(FuncError + 116)
#define InvalidCmpMethod			(FuncError + 117)
#define InvalidCmpPulseMode			(FuncError + 118)
#define InvalidCmpPulseLogic		(FuncError + 119)
#define InvalidCmpPulseWidth		(FuncError + 120)
#define InvalidPathFunctionID		(FuncError + 121)
#define SysBufAllocateFailed        (FuncError + 122)
#define SpeedFordFunNotSpported     (FuncError + 123)
#define InvalidNormVector			(FuncError + 124)//zhaocui add
#define InvalidCmpTimeTableCount    (FuncError + 125)
#define InvalidCmpTime              (FuncError + 126)
#define FWDownLoading               (FuncError + 127)//zhaocui add 20131209
#define FWVersionNotMatch           (FuncError + 128)//zhaocui add 20131209       
               

//AMONet Communication error
#define SlaveIOUpdateError			(FuncError + 150)
#define NoSlaveDevFound				(FuncError + 151)
#define MasterDevNotOpen            (FuncError + 152)
#define MasterRingNotOpen           (FuncError + 153)


//DAQ function  [1/24/2008 Dean] -----------------------------------
#define InvalidDIPort				(FuncError + 200)
#define InvalidDOPort				(FuncError + 201)
#define InvalidDOValue				(FuncError + 202)

//EVT function
#define CreateEventFailed           (FuncError + 203)
#define CreateThreadFailed          (FuncError + 204)

#define InvalidHomeModeEx           (FuncError + 205)
#define InvalidDirMode              (FuncError + 206)
#define AxHomeMotionFailed          (FuncError + 207)
#define ReadFileFailed              (FuncError + 208)
#define PathBufIsFull               (FuncError + 209)
#define PathBufIsEmpty              (FuncError + 210)
#define GetAuthorityFailed          (FuncError + 211)  //  [3/17/2011 dan.yang]
#define GpIDAllocatedFailed         (FuncError + 212)  //  [04/15/2011 dan.yang]
#define FirmWareDown                (FuncError + 213) //  [4/26/2011 dan.yang] todo
#define InvalidGpRadius             (FuncError + 214) //  [4/28/2011 dan.yang]
#define InvalidAxCmd                (FuncError + 215) //  [4/28/2011 dan.yang]
#define InvalidaxExtDrv             (FuncError + 216) //  [4/29/2011 dan.yang]
#define InvalidGpMovCmd             (FuncError + 217) //  [5/4/2011 dan.yang]
#define SpeedCurveNotSupported      (FuncError + 218) //  [5/20/2011 dan.yang]
#define InvalidCounterNo            (FuncError + 219) //  [5/24/2011 dan.yang]
#define InvalidPathMoveMode         (FuncError + 220) //  [6/2/2011 dan.yang]
#define PathSelStartCantRunInSpeedForwareMode (FuncError + 221) //  [6/21/2011 dan.yang]
#define InvalidCamTableID           (FuncError + 222) //  [6/23/2011 dan.yang]
#define InvalidCamPointRange        (FuncError + 223) //  [6/23/2011 dan.yang]
#define CamTableIsEmpty             (FuncError + 224) //  [6/23/2011 dan.yang]
#define InvalidPlaneVector          (FuncError + 225) //  [6/24/2011 dan.yang]
#define MasAxIDSameSlvAxID          (FuncError + 226) //  [6/24/2011 dan.yang]
#define InvalidGpRefPlane           (FuncError + 227) //  [7/4/2011 dan.yang]
#define InvalidAxModuleRange        (FuncError + 228) //  [7/8/2011 dan.yang]
#define DownloadFileFailed          (FuncError + 229) //  [7/12/2011 dan.yang]
#define InvalidFileLength           (FuncError + 230) //  [7/12/2011 dan.yang] 
#define InvalidCmpCnt               (FuncError + 231) //  [8/10/2011 dan.yang]
#define JerkExceededMaxValue        (FuncError + 232) //  [12/9/2011 dan.yang]
#define AbsMotionNotSupport         (FuncError + 233) //  [1/17/2012 dan.yang]
#define invalidAiRange              (FuncError + 234) //  [4/18/2012 dan.yang]
#define AIScaleFailed               (FuncError + 235) //  [4/18/2012 dan.yang]
#define AxInRobot                   (FuncError + 236) //  [7/31/2013 zhaocui]  
#define Invalid3DArcFlat            (FuncError + 237) //  [7/31/2013 zhaocui]
#define InvalidIpoMap                (FuncError + 238)
#define AxisNotFound                 (FuncError + 240) //  [10/30/2013 dan.yang]
#define DataSizeNotCorrect          (FuncError + 239) //  [10/28/2013 dan.yang]

#define HLmtPExceeded				(MotionError + 0)
#define HLmtNExceeded				(MotionError + 1)
#define SLmtPExceeded				(MotionError + 2)
#define SLmtNExceeded				(MotionError + 3)
#define AlarmHappened				(MotionError + 4)
#define EmgHappened			    	(MotionError + 5)
#define TimeLmtExceeded				(MotionError + 6)
#define DistLmtExceeded				(MotionError + 7)
#define InvalidPositionOverride		        (MotionError + 8)			//[Dean 2008.2.18]
#define OperationErrorHappened		        (MotionError + 9)
#define SimultaneousStopHappened	        (MotionError + 10)
#define OverflowInPAPB				        (MotionError + 11)
#define OverflowInIPO				        (MotionError + 12)
#define STPHappened				            (MotionError + 13)
#define SDHappened				            (MotionError + 14)
#define AxsiNoCmpDataLeft                   (MotionError + 15)


#define DevEvtTimeOut				(DevEvtError + 1)
#define DevNoEvt			        (DevEvtError + 2)
//*************************************************************
#define Warning_AxWasInGp			(Warning + 1)
//inconsistent rate of PPU setting
#define Warning_GpInconsistRate     (Warning + 2)
#define Warning_GpInconsistPPU      (Warning + 3)
#define Warning_GpMoveDistanceCanntBeZero (Warning + 4)


// Dsp Error //  [9/26/2011 dan.yang]
// ----------------------------------------------------------------------------
#define ERR_SYS_TIME_OUT					(DspError + 0x01)
#define Dsp_PropertyIDNotSupport			(DspError + 0x02)
#define Dsp_PropertyIDReadOnly				(DspError + 0x03)

#define Dsp_InvalidParameter				(DspError + 0x04)
#define Dsp_DataOutBufExceeded				(DspError + 0x05)
#define Dsp_FunctionNotSupport				(DspError + 0x06)
#define Dsp_InvalidConfigFile				(DspError + 0x07)
#define Dsp_InvalidIntervalData				(DspError + 0x08)
#define Dsp_InvalidTableSize				(DspError + 0x09)
#define Dsp_InvalidTableID					(DspError + 0x0a)
#define Dsp_DataIndexExceedBufSize			(DspError + 0x0b)
#define Dsp_InvalidCompareInterval			(DspError + 0x0c)
#define Dsp_InvalidCompareRange				(DspError + 0x0d)
#define Dsp_PropertyIDWriteOnly				(DspError + 0x0e)
#define Dsp_NcError							(DspError + 0x0f)	
#define Dsp_CamTableIsInUse					(DspError + 0x10)	
#define Dsp_EraseBlockFailed				(DspError + 0x11)	
#define Dsp_ProgramFlashFailed				(DspError + 0x12)	
#define Dsp_WatchdogError					(DspError + 0x13)	
#define Dsp_ReadPrivateOverMaxTimes			(DspError + 0x14)	//[v1.0.8.4]
#define Dsp_InvalidPrivateID				(DspError + 0x15)	//[v1.0.8.4]
#define Dsp_DataNotReady					(DspError + 0x16)	//[v1.0.8.4]
#define Dsp_LastOperationNotOver 			(DspError + 0x17)
#define Dsp_WritePrivateTimeout 			(DspError + 0x18)
#define Dsp_FwIsDownloading                 (DspError + 0x19)
#define Dsp_FwDownloadStepError             (DspError + 0x20)

// Axis Error
// ----------------------------------------------------------------------------


#define Dsp_InvalidAxCfgVel				(DspAxError + 0x01)
#define Dsp_InvalidAxCfgAcc				(DspAxError + 0x02)
#define Dsp_InvalidAxCfgDec				(DspAxError + 0x03)
#define Dsp_InvalidAxCfgJerk			(DspAxError + 0x04)
#define Dsp_InvalidAxParVelLow			(DspAxError + 0x05)
#define Dsp_InvalidAxParVelHigh			(DspAxError + 0x06)
#define Dsp_InvalidAxParAcc				(DspAxError + 0x07)
#define Dsp_InvalidAxParDec				(DspAxError + 0x08)
#define Dsp_InvalidAxParJerk			(DspAxError + 0x09)
#define Dsp_InvalidAxPptValue			(DspAxError + 0x0a)
#define Dsp_InvalidAxState				(DspAxError + 0x0b)
#define Dsp_InvalidAxSvOnOff			(DspAxError + 0x0c)
#define Dsp_InvalidAxDistance			(DspAxError + 0x0d)
#define Dsp_InvalidAxPosition			(DspAxError + 0x0e)
#define Dsp_InvalidAxHomeMode			(DspAxError + 0x0f)
#define Dsp_InvalidPhysicalAxis			(DspAxError + 0x10)			
#define Dsp_HLmtPExceeded				(DspAxError + 0x11)
#define Dsp_HLmtNExceeded				(DspAxError + 0x12)
#define Dsp_SLmtPExceeded				(DspAxError + 0x13)
#define Dsp_SLmtNExceeded				(DspAxError + 0x14)
#define Dsp_AlarmHappened				(DspAxError + 0x15)
#define Dsp_EmgHappened					(DspAxError + 0x16)
#define Dsp_CmdValidOnlyInConstSec		(DspAxError + 0x17)			// Command valid only in the constant section
#define Dsp_InvalidAxCmd				(DspAxError + 0x18)
#define Dsp_InvalidAxHomeDirMode		(DspAxError + 0x19)
#define Dsp_AxisMustBeModuloAxis		(DspAxError + 0x1a)
#define Dsp_AxIdCantSameAsMasId			(DspAxError + 0x1b)
#define Dsp_CantResetPosiOfMasAxis		(DspAxError + 0x1c)
#define Dsp_InvalidAxExtDrvOperation	(DspAxError + 0x1d)
#define Dsp_AxAccExceededMaxAcc         (DspAxError + 0x1e)
#define Dsp_AxVelExceededMaxVel         (DspAxError + 0x1f)
#define Dsp_NotEnoughPulseForChgV   	(DspAxError + 0x20)
#define Dsp_NewVelMustGreaterThanVelLow (DspAxError + 0x21)
#define Dsp_InvalidAxGearMode 			(DspAxError + 0x22)
#define Dsp_InvalidGearRatio 			(DspAxError + 0x23)
#define Dsp_InvalidPWMDataCount			(DspAxError	+ 0x24)
#define	Dsp_InvalidAxPWMFreq			(DspAxError	+ 0x25)
#define	Dsp_InvalidAxPWMDuty			(DspAxError	+ 0x26)
#define Dsp_AxGantryExceedMaxDiffValue  (DspAxError + 0x27)
#define	Dsp_ChanelIsDisable				(DspAxError + 0x28)
#define	Dsp_ChanelBufferIsFull			(DspAxError + 0x29)
#define	Dsp_ChanelBufferIsEmpty			(DspAxError + 0x30)
// Group Error //  [9/26/2011 dan.yang]
// ----------------------------------------------------------------------------
#define Dsp_InvalidAxCntInGp			(DspGpError + 0x01)
#define Dsp_AxInGpNotFound				(DspGpError + 0x02)
#define Dsp_AxIsInOtherGp				(DspGpError + 0x03)
#define Dsp_AxCannotIntoGp				(DspGpError + 0x04)
#define Dsp_GpInDevNotFound				(DspGpError + 0x05)
#define Dsp_InvalidGpCfgVel				(DspGpError + 0x06)
#define Dsp_InvalidGpCfgAcc				(DspGpError + 0x07)
#define Dsp_InvalidGpCfgDec				(DspGpError + 0x08)
#define Dsp_InvalidGpCfgJerk			(DspGpError + 0x09)
#define Dsp_InvalidGpParVelLow			(DspGpError + 0x0a)
#define Dsp_InvalidGpParVelHigh	        (DspGpError + 0x0b)
#define Dsp_InvalidGpParAcc				(DspGpError + 0x0c)
#define Dsp_InvalidGpParDec				(DspGpError + 0x0d)
#define Dsp_InvalidGpParJerk			(DspGpError + 0x0e)
#define Dsp_JerkNotSupport		        (DspGpError + 0x0f)
#define Dsp_ThreeAxNotSupport           (DspGpError + 0x10)
#define Dsp_DevIpoNotFinished		    (DspGpError + 0x11)
#define Dsp_InvalidGpState				(DspGpError + 0x12)
#define Dsp_OpenFileFailed		        (DspGpError + 0x13)
#define Dsp_InvalidPathCnt		        (DspGpError + 0x14)
#define Dsp_InvalidPathHandle		    (DspGpError + 0x15)
#define Dsp_InvalidPath                 (DspGpError + 0x16)
#define Dsp_GpSlavePositionOverMaster  	(DspGpError + 0x17)
#define Dsp_GpPathBufferOverflow 		(DspGpError + 0x19)
#define Dsp_InvalidPathFunctionID		(DspGpError + 0x1a)
#define Dsp_SysBufAllocateFailed        (DspGpError + 0x1b)
#define Dsp_InvalidGpCenterPosition		(DspGpError + 0x1c)
#define Dsp_InvalidGpEndPosition		(DspGpError + 0x1d)
#define Dsp_InvalidGpCmd				(DspGpError + 0x1e)
#define Dsp_AxHasBeenInInGp				(DspGpError + 0x1f)
#define Dsp_InvalidPathRange			(DspGpError + 0x20)
#define Dsp_InvalidNormVector			(DspGpError + 0x21)

//  [1/22/2014 deng]




#define Dsp_RbInvalidGpid                                 (DspRbError + 0x01)
#define Dsp_RbInvalidMode                               (DspRbError + 0x01)
#define Dsp_RbInvalidArmLength                     (DspRbError + 0x02)
#define Dsp_RbInvalidAxesNum                        (DspRbError + 0x03)
#define Dsp_RbInvalidHandDir                          (DspRbError + 0x04)
#define Dsp_RbAreaExceeded                                     (DspRbError + 0x05)
#define Dsp_RbAngleExceeded                                   (DspRbError + 0x06)
#define Dsp_RbSwLmtNotEnabled                    (DspRbError + 0x07)
#define Dsp_RbVectorDistExceededZTargetDist (DspRbError + 0x08)




//add by dujunling 2012.11.23
#define Gm_CodeError					(GmError + 0x100)
#define Gm_SystemError					(GmError + 0x200)

/////////////Gm_CodeError
#define	Gm_InvalidCharacter				(Gm_CodeError + 1)
#define Gm_InvalidCode					(Gm_CodeError + 2)
#define Gm_InvalidGCode					(Gm_CodeError + 3)
#define Gm_InvalidMCode					(Gm_CodeError + 4)
#define Gm_GroupCodeAlreadyExist		(Gm_CodeError + 5)
#define Gm_MissingNumber				(Gm_CodeError + 6)
//
#define Gm_MissingFWord					(Gm_CodeError + 7)
#define Gm_MissingSWord					(Gm_CodeError + 8)
#define Gm_MissingOWord					(Gm_CodeError + 9)
#define Gm_MissingNWord					(Gm_CodeError + 10)
#define Gm_MissingLWord					(Gm_CodeError + 11)
#define Gm_MissingPWord					(Gm_CodeError + 12)
#define Gm_MissingQWord					(Gm_CodeError + 13)
#define Gm_MissingRWord					(Gm_CodeError + 14)
#define Gm_MissingEWord					(Gm_CodeError + 15)
#define Gm_MissingHWord					(Gm_CodeError + 16)
#define Gm_MissingDWord					(Gm_CodeError + 17)
#define Gm_MissingTWord					(Gm_CodeError + 18)
#define	Gm_MissingAxisWord				(Gm_CodeError + 19)
#define	Gm_MissingSubAxisWord			(Gm_CodeError + 20)
//
#define Gm_InvalidFValue				(Gm_CodeError + 21)
#define Gm_InvalidSValue				(Gm_CodeError + 22)
#define Gm_InvalidOValue				(Gm_CodeError + 23)
#define Gm_InvalidNValue				(Gm_CodeError + 24)
#define Gm_InvalidLValue				(Gm_CodeError + 25)
#define Gm_InvalidPValue				(Gm_CodeError + 26)
#define Gm_InvalidQValue				(Gm_CodeError + 27)
#define Gm_InvalidRValue				(Gm_CodeError + 28)
#define Gm_InvalidEValue				(Gm_CodeError + 29)
#define Gm_InvalidHValue				(Gm_CodeError + 31)
#define Gm_InvalidDValue				(Gm_CodeError + 32)
#define Gm_InvalidTValue				(Gm_CodeError + 33)
#define Gm_InvalidAxisValue				(Gm_CodeError + 34)
#define Gm_InvalidSubAxisValue			(Gm_CodeError + 35)

#define Gm_OverloadAxisNum				(Gm_CodeError + 36)
#define Gm_InvalidAxisNumber			(Gm_CodeError + 37)
#define Gm_MacroNotFound				(Gm_CodeError + 38)

//////////////Gm_SystemError
#define Gm_InvalidGMSHandle				(Gm_SystemError + 1)
#define Gm_InvalidThreadHandle			(Gm_SystemError + 2)  
#define Gm_SystemNotReady				(Gm_SystemError + 3)

#define Gm_NotEnoughMemory              (Gm_SystemError + 4)
#define Gm_InvalidPatternId				(Gm_SystemError + 5)
#define Gm_InvalidBreakPoint			(Gm_SystemError + 6)
#define Gm_InvalidMacroNumber			(Gm_SystemError + 7)

#define Gm_CodeOverload					(Gm_SystemError + 8)
#define Gm_MacroOverload				(Gm_SystemError + 9)
#define Gm_InvalidFeedRate				(Gm_SystemError + 10)
#define Gm_InvalidModuleRange			(Gm_SystemError + 11)


#define Gm_RadiusCompensationAlreadyOn	(Gm_SystemError + 12)
#define Gm_OverCut						(Gm_SystemError + 13)
#define Gm_WrongRefPlane				(Gm_SystemError + 14)



#define Gm_DllNotFound					(Gm_SystemError + 15)
#define Gm_Ax_ErrorStop					(Gm_SystemError + 16)

#define Gm_OverrunDwell					(Gm_SystemError + 17)
#define Gm_InvalidSetCoordinate			(Gm_SystemError + 18)




#define Gm_OverrunAxisNum				(Gm_SystemError + 19)
#define Gm_InvalidG29					(Gm_SystemError + 10)
#define	Gm_BothOfGCodeUseAxisWords		(Gm_SystemError + 21)
#define	Gm_NotFoundNext					(Gm_SystemError + 22)
#define	Gm_ArcAxisNumError				(Gm_SystemError + 23)
#define	Gm_OverrunContiAxis				(Gm_SystemError + 24)
#define	Gm_ContiArcAxisError			(Gm_SystemError + 25)
#define	Gm_G272829CanNotBeConti			(Gm_SystemError + 26)
#define	Gm_CheckHomeFailed				(Gm_SystemError + 27)

#define	Gm_StackOverflow				(Gm_SystemError + 28)
#define	Gm_StackUnderflow				(Gm_SystemError + 29)
#define	Gm_InvalidAxHomeMode			(Gm_SystemError + 30)
#define Gm_OverrunFilePath				(Gm_SystemError + 31)
#define Gm_OverrunLineText				(Gm_SystemError + 32)
#define Gm_InvalidSSTA                  (Gm_SystemError + 33)       //Added by W.Y.Z on 2012.08.22 modify by dujunling on 2012.10.26

#define Gm_InfineLoop        			(Gm_SystemError + 34)       //Added bydujunling on 2012.9.27 for loadjob,uploadjob,

////do error			added by dujunling 2012.10.26
#define Gm_InvalidDoDevice				(Gm_SystemError + 35)
#define Gm_InvalidDoChannel				(Gm_SystemError + 36)
#define Gm_InvalidDoLevel				(Gm_SystemError + 37)
//di
#define Gm_InvalidDiDevice				(Gm_SystemError + 38)
#define Gm_InvalidDiChannel				(Gm_SystemError + 39)
#define Gm_InvalidDiLevel				(Gm_SystemError + 40)
//custom m code
#define Gm_RunCustomMcodeError			(Gm_SystemError + 41)

#define Gm_ZeroVector					(Gm_SystemError + 42)
#define Gm_LineParallel					(Gm_SystemError + 43)
//
#define Gm_InvalidBufferLength			(Gm_SystemError + 44)
#define GmInvalidOptionPauseParam       (Gm_SystemError + 45)
#define GmInvalidOptionSkip             (Gm_SystemError + 46)
#define GmWaitDiTimeOut             	(Gm_SystemError + 47)
#define GmCannotInvokeMacroInMacro      (Gm_SystemError + 48)
#define GmThreadTimeOut				    (Gm_SystemError + 49)

#endif // __ADV_MOT_ERR_H__
