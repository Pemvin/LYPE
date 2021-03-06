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

#ifndef __ADV_MOT_DRV_H__
#define __ADV_MOT_DRV_H__

/*
+-----------------------------------------------------------------------------+
| ************ Advantech Motion Date Type Definition ************************ |
+-----------------------------------------------------------------------------+
*/
#define  U8         UCHAR
#define  U16        USHORT
#define  U32        ULONG
#define  U64        ULONGLONG 

#define  I8         CHAR
#define  I16        SHORT
#define  I32        LONG
#define  I64        LONGLONG

#define  F32        float
#define  F64        DOUBLE

#define  PU8        UCHAR*
#define  PU16       USHORT*
#define  PU32       ULONG*
#define  PU64       ULONGLONG* 

#define  PI8        CHAR*
#define  PI16       SHORT*
#define  PI32       LONG*
#define  PI64       LONGLONG*

#define  PF32       FLOAT*
#define  PF64       DOUBLE*

#ifdef _WIN64
#define LONG_PTR LONG_PTR
#define ULONG_PTR ULONG_PTR
#else
#define LONG_PTR LONG
#define ULONG_PTR ULONG
#endif

// #if defined (_AMD64_)  
// #define  HAND       U64
// #define  PHAND      U64*
// #else
// #define  HAND       U32
// #define  PHAND      U32*
// #endif

#define	 HAND			UINT_PTR
#define	 PHAND			UINT_PTR*
#ifndef  ULONG_PTR
#define  ULONG_PTR  unsigned   long*
#endif


/*
+-----------------------------------------------------------------------------+
| ********************** Physical Axis Define ******************************* |
+-----------------------------------------------------------------------------+
*/
#define 		X_AXIS  						0
#define 		Y_AXIS  						1
#define 		Z_AXIS  						2
#define 		U_AXIS  						3
#define         A_AXIS                          4  //[Dan.Yang 2011.03.10]
#define         B_AXIS                          5  //[Dan.Yang 2011.03.10]
/*+-----------------------------------------------------------------------------+
| ******************** Settings' Limit  *************************** |
+-----------------------------------------------------------------------------+
*/

#ifdef PCI1244
#define MAX_RATE       150
#define MIN_RATE       0
#define MAX_R          4096
#define MIN_R          0
#define MAX_V          32767
#define MIN_V          1
#define MAX_D          65535
#define MIN_D          1
#define MAX_A          65535
#define MIN_A          1
#define MAX_K          65535
#define MIN_K          1
#define MAX_PULSE      268435455
#define MIN_PULSE      0
#define MAX_POSITION   268435455
//#define MIN_POSITION   -2147483648
#define MIN_POSITION  MAX_POSITION*(-1)-1
#else
#define MAX_RATE       500
#define MIN_RATE       1
#define MAX_R          8000000
#define MIN_R          16000
#define MAX_V          8000
#define MIN_V          1
#define MAX_D          8000
#define MIN_D          1
#define MAX_A          8000
#define MIN_A          1
#define MAX_K          65535
#define MIN_K          1
#define MAX_PULSE      268435455
#define MIN_PULSE      0
#define MAX_POSITION   2147483647
//#define MIN_POSITION   -2147483648
#define MIN_POSITION  MAX_POSITION*(-1)-1
#endif

#define		NOT_DEFINE		0xffffffff

#define	  MAX_CMPPULSEWIDTH  85899345
/*
+-----------------------------------------------------------------------------+
| ******************** Device Function Map Define *************************** |
+-----------------------------------------------------------------------------+
*/
#define     DEV_FUNC_MOT                              0x001
#define     DEV_FUNC_DI                               0x002
#define     DEV_FUNC_DO                               0x004
#define     DEV_FUNC_AI                               0x008
#define     DEV_FUNC_AO                               0x010
#define     DEV_FUNC_TMR                              0x020
#define     DEV_FUNC_CNT                              0x040
#define     DEV_FUNC_DAQDI                            0x080
#define     DEV_FUNC_DAQDO                            0x100
#define     DEV_FUNC_DAQAI                            0x200
#define     DEV_FUNC_DAQAO                            0x400
#define     DEV_FUNC_EMG                              0x800
#define     DEV_FUNC_MDAQ				              0x1000	
     
/*
+-----------------------------------------------------------------------------+
| **************** Device Interpolation Type Map Define ********************* |
+-----------------------------------------------------------------------------+
*/
#define     DEV_IPO_LINE_2AX  		0x01
#define     DEV_IPO_LINE_3AX  		0x02
//////////////////////////////////////////////////////////////////////////
//ydd:add for pci1265.20110309
#define     DEV_IPO_LINE_4AX        0x04
#define     DEV_IPO_LINE_5AX        0x08
#define     DEV_IPO_LINE_6AX        0x10
#define     DEV_IPO_LINE_7AX        0x20
#define     DEV_IPO_LINE_8AX        0x40
//////////////////////////////////////////////////////////////////////////
#define     DEV_IPO_ARC_2AX   		0x0100
#define     DEV_IPO_ARC_3AX   		0x0200
#define     DEV_IPO_SPIRAL          0x0400 //  [6/20/2011 dan.yang]
#define     DEV_IPO_BLENDING   		0x0800
#define     DEV_IPO_SPEED_FORWARD	0x1000
#define     DEV_IPO_GEAR           0x00010000 //  [9/14/2011 dan.yang]
#define     DEV_IPO_CAM            0x00020000 //  [9/14/2011 dan.yang]
#define     DEV_IPO_GANTRY         0x00040000 //  [9/14/2011 dan.yang]
#define     DEV_IPO_TANGENT        0x00080000 //  [9/14/2011 dan.yang]
#define     DEV_IPO_SELPTH         0x01000000 //  [9/14/2011 dan.yang]
/*
+-----------------------------------------------------------------------------+
| ********************* Axis Feature Map Define ***************************** |
+-----------------------------------------------------------------------------+
*/
#define     AX_FUNC_INP         		0x01
#define     AX_FUNC_ALM					0x02
#define     AX_FUNC_ERC					0x04
#define     AX_FUNC_SD					0x08
#define     AX_FUNC_EL                 0x10
#define     AX_FUNC_SW_EL              0x20
#define     AX_FUNC_ORG                0x40
#define     AX_FUNC_EZ                 0x80
#define     AX_FUNC_BACKLASH_CORRECT   0x0100
#define     AX_FUNC_SUPPRESS_VIBRATION 0x0200
#define     AX_FUNC_HOME               0x0400
#define     Ax_FUNC_IMPOSE             0x0800  //  [9/14/2011 dan.yang]
#define     Ax_FUNC_CMP                0x1000  //  [9/14/2011 dan.yang]
#define     Ax_FUNC_LATCH              0x2000  //  [9/14/2011 dan.yang]
#define     Ax_FUNC_CAMDO              0x4000  //  [9/14/2011 dan.yang]
#define     Ax_FUNC_EXTDRV             0x8000  //  [9/14/2011 dan.yang]
#define     Ax_FUNC_SIMSTART           0x010000  //  [9/14/2011 dan.yang]
#define     AX_FUNC_IN1_STOP           0x020000  //  [12/15/2012 dan.yang]
#define     AX_FUNC_IN2_STOP           0x040000  //  [12/15/2012 dan.yang]
#define     AX_FUNC_IN3_STOP           0x080000  //  [12/15/2012 dan.yang]
#define     AX_FUNC_IN4_STOP           0x100000  //  [12/15/2012 dan.yang]
#define     AX_FUNC_IN5_STOP           0x200000  //  [12/15/2012 dan.yang]

/*
+-----------------------------------------------------------------------------+
| ******************** Axis Pulse In Map Define ***************************** |
+-----------------------------------------------------------------------------+
*/
#define     AX_PI_MODE					1
#define     AX_PI_LOGIC 				2
#define     AX_PI_SOURCE 				4	
/*
+-----------------------------------------------------------------------------+
| ******************* Axis Pulse In Mode Map Define ************************* |
+-----------------------------------------------------------------------------+
*/
#define     AX_PIM_1XAB 				1
#define     AX_PIM_2XAB 				2
#define     AX_PIM_4XAB 				4
#define     AX_PIM_CWCCW 				8
/*
+-----------------------------------------------------------------------------+
| ******************* Axis Pulse Out Map Define ***************************** |
+-----------------------------------------------------------------------------+
*/
#define     AX_PO_MODE 					1
/*
+-----------------------------------------------------------------------------+
| ******************* Axis Pulse Out Mode Map Define ************************ |
+-----------------------------------------------------------------------------+
*/
#define     AX_POM_OUT_DIR 			1
#define     AX_POM_OUT_DIR_OUTNEG   2
#define     AX_POM_OUT_DIR_DIRNEG   4
#define     AX_POM_OUT_DIR_ALLNEG   8
#define     AX_POM_CW_CCW 			16
#define     AX_POM_CW_CCW_ALLNEG    32
#define     AX_POM_AB               64
#define     AX_POM_BA               128
#define     AX_POM_CW_CCW_OUTNEG	256
#define     AX_POM_CW_CCW_DIRNEG	512
/*
+-----------------------------------------------------------------------------+
| *********************** Axis Alarm Map Define ***************************** |
+-----------------------------------------------------------------------------+
*/
#define     AX_ALM_EN               1
#define     AX_ALM_LOGIC            2
#define     AX_ALM_REACT            4
/*
+-----------------------------------------------------------------------------+
| ********************** Axis InPosition Map Define ************************* |
+-----------------------------------------------------------------------------+
*/
#define     AX_INP_EN               1
#define     AX_INP_LOGIC            2	
/*
+-----------------------------------------------------------------------------+
| *********************** Axis ERC Map Define ******************************* |
+-----------------------------------------------------------------------------+
*/
#define     AX_ERC_EN_MODE          1
#define     AX_ERC_LOGIC            2
#define     AX_ERC_ON_TIME          4
#define     AX_ERC_OFF_TIME         8
/*
+-----------------------------------------------------------------------------+
| *********************** Axis SD Map Define ******************************** |
+-----------------------------------------------------------------------------+
*/
#define     AX_SD_EN                1
#define     AX_SD_LOGIC             2
#define     AX_SD_REACT             4
#define     AX_SD_LATCH             8
/*
+-----------------------------------------------------------------------------+
| ***************** Axis Hardware Limit Map Define ************************** |
+-----------------------------------------------------------------------------+
*/
#define     AX_EL_EN                1
#define     AX_EL_LOGIC             2
#define     AX_EL_REACT             4	
/*
+-----------------------------------------------------------------------------+
| ************** Axis Software Minus Limit Map Define *********************** |
+-----------------------------------------------------------------------------+
*/
#define     AX_SW_MEL_EN            1
#define     AX_SW_MEL_REACT         2
#define     AX_SW_MEL_VALUE         4	
/*
+-----------------------------------------------------------------------------+
| ************** Axis Software Plus Limit Map Define ************************ |
+-----------------------------------------------------------------------------+
*/
#define     AX_SW_PEL_EN            1
#define     AX_SW_PEL_REACT         2
#define     AX_SW_PEL_VALUE         4
/*
+-----------------------------------------------------------------------------+
| ******************** Axis Home Map Define ********************************* |
+-----------------------------------------------------------------------------+
*/
#define     AX_HM_MODE              0x01
#define     AX_HM_ORG_LOGIC         0x02
#define     AX_HM_EZ_LOGIC          0x04
#define     AX_HM_RESET_EN          0x08  //  [9/14/2011 dan.yang]
#define     AX_HM_ORG_REACT         0x10  //  [12/27/2011 dan.yang]
/*
+-----------------------------------------------------------------------------+
| ******************** Axis Compare Map Define ********************************* |  //  [9/14/2011 dan.yang]
+-----------------------------------------------------------------------------+
*/
#define     AX_CMP_EN              0x01
#define     AX_CMP_LOGIC           0x02
#define     AX_CMP_SRC             0x04
#define     AX_CMP_METHOD          0x08
#define     AX_CMP_PULSE_MODE      0x10
#define     AX_CMP_PULSE_WIDTH     0x20
/*
+-----------------------------------------------------------------------------+
| ******************** Axis Latch Map Define ********************************* |  //  [9/14/2011 dan.yang]
+-----------------------------------------------------------------------------+
*/
#define     AX_LATCH_EN              0x01
#define     AX_LATCH_LOGIC           0x02
#define     AX_LATCH_BUF_EN          0x04
//  [3/6/2013 dan.yang]:Add for latch buffer
#define     AX_LATCH_BUF_MINDST      0x08
#define     AX_LATCH_BUF_EVTNUM      0x10
#define     AX_LATCH_BUF_SRC         0x20
#define     AX_LATCH_BUF_AXID        0x40
#define     AX_LATCH_BUF_EDGE        0x80
/*
+-----------------------------------------------------------------------------+
| ******************** Axis Cam DO Map Define ********************************* |  //  [9/14/2011 dan.yang]
+-----------------------------------------------------------------------------+
*/
#define     AX_CAMDO_EN              0x01
#define     AX_CAMDO_LOGIC           0x02
#define     AX_CAMDO_CMP_SRC         0x04
#define     AX_CAMDO_LOW_LIMIT       0x08
#define     AX_CAMDO_HIGH_LIMIT      0x10
#define     AX_CAMDO_MODE            0x20
#define     AX_CAMDO_DIR             0x40
/*
+-----------------------------------------------------------------------------+
| ******************** Axis External Drive Map Define ********************************* |  //  [9/14/2011 dan.yang]
+-----------------------------------------------------------------------------+
*/
#define     AX_EXT_MASTER_SRC              0x01
#define     AX_EXT_SEL_EN                  0x02
#define     AX_EXT_PULSE_Num               0x04
#define     AX_EXT_PULSE_IN_MODE           0x08
#define     AX_EXT_PRESET_NUM              0x10
/*
+-----------------------------------------------------------------------------+
| ******************** Axis External Master Source Map Define ********************************* |  //  [9/14/2011 dan.yang]
+-----------------------------------------------------------------------------+
*/
#define     ExtSrcAxis0					0x01
#define     ExtSrcAxis1					0x02
#define     ExtSrcAxis2					0x04
#define     ExtSrcAxis3					0x08
/*
+-----------------------------------------------------------------------------+
| ******************** Axis Simultaneous Start/Stop source Map Define ********************************* |  //  [9/14/2011 dan.yang]
+-----------------------------------------------------------------------------+
*/
#define SimSrc_Disable          0x000000
#define SimSrc_STA				0x000001
#define SimSrc_TRIGP_AX0		0x000100
#define SimSrc_TRIGP_AX1		0x000200
#define SimSrc_TRIGP_AX2		0x000400
#define SimSrc_TRIGP_AX3		0x000800
#define SimSrc_TRIGP_AX4		0x001000
#define SimSrc_TRIGP_AX5		0x002000
#define SimSrc_TRIGP_AX6        0x004000
#define SimSrc_TRIGP_AX7        0x008000
#define SimSrc_STOP_AX0			0x010000
#define SimSrc_STOP_AX1			0x020000
#define SimSrc_STOP_AX2			0x040000
#define SimSrc_STOP_AX3			0x080000
#define SimSrc_STOP_AX4			0x100000
#define SimSrc_STOP_AX5			0x200000
#define SimSrc_STOP_AX6			0x400000
#define SimSrc_STOP_AX7			0x800000
/*
+-----------------------------------------------------------------------------+
| ******************** Axis Gen_DO Map Define ********************************* |  //  [9/14/2011 dan.yang]
+-----------------------------------------------------------------------------+
*/
#define     OUT4oCAM_DO					0x01
#define     OUT5oTRIG_P					0x02
#define     OUT6oSVON					0x04
#define     OUT7oERC					0x08	
/*
+-----------------------------------------------------------------------------+
| ******************** Axis Gen_DI Start/Stop Mode Map Define ********************************* |  //  [9/14/2011 dan.yang]
+-----------------------------------------------------------------------------+
*/
#define     IN1oLTC						0x01
#define     IN2oRDY						0x02
#define     IN3oJOG_P					0x04
#define     IN4oJOG_M					0x08	

/*
+-----------------------------------------------------------------------------+
| ******************** Axis IN1~IN5 Stop Map Define ********************************* | //  [12/15/2012 dan.yang]
+-----------------------------------------------------------------------------+
*/
#define     IN_STOP_ENABLE					0x01
#define     IN_STOP_LOGIC					0x02
#define     IN_STOP_REACT					0x04
/*
+-----------------------------------------------------------------------------+
+-----------------------------------------------------------------------------+
*/
/*
+-----------------------------------------------------------------------------+
| ******************** Pulse In Mode Define ********************************* |
+-----------------------------------------------------------------------------+
*/
#define    AB_1X 						0
#define	   AB_2X 						1
#define	   AB_4X 						2
#define	   I_CW_CCW 					3
/*
+-----------------------------------------------------------------------------+
| ******************** Pulse In Logic Define ******************************** |
+-----------------------------------------------------------------------------+
*/
#define     NO_INV_DIR 					0
#define	   INV_DIR 						1
/*
+-----------------------------------------------------------------------------+
| ******************** Pulse In Source Define ******************************* |
+-----------------------------------------------------------------------------+
*/
#define     EXTERNAL_FEEBACK        0
#define	   COMMAND_PULSE 				1
/*
+-----------------------------------------------------------------------------+
| ******************** Pulse Out Mode Define ******************************** |
+-----------------------------------------------------------------------------+
*/
#define     OUT_DIR  					1
#define     OUT_DIR_OUT_NEG 			2
#define	   OUT_DIR_DIR_NEG 			4
#define     OUT_DIR_ALL_NEG 			8
#define	   O_CW_CCW 					16
#define     CW_CCW_ALL_NEG 			32
#define	   AB_PHASE 					64
#define	   BA_PHASE 					128
#define		CW_CCW_OUT_NEG			256
#define   CW_CCW_DIR_NEG			512
/*
+-----------------------------------------------------------------------------+
| ******************** Alarm Enable Define ********************************** |
+-----------------------------------------------------------------------------+
*/
#define     ALM_DIS 						0
#define     ALM_EN 						1
/*
+-----------------------------------------------------------------------------+
| ******************** Alarm Logic Define *********************************** |
+-----------------------------------------------------------------------------+
*/
#define     ALM_ACT_LOW 				0
#define     ALM_ACT_HIGH 				1
/*
+-----------------------------------------------------------------------------+
| ******************** Alarm React Define *********************************** |
+-----------------------------------------------------------------------------+
*/
#define     ALM_IMMED_STOP          0
#define     ALM_DEC_TO_STOP 			1
/*
+-----------------------------------------------------------------------------+
| ******************** Inposition Enable Define ***************************** |
+-----------------------------------------------------------------------------+
*/
#define     INP_DIS 						0
#define	   INP_EN 						1
/*
+-----------------------------------------------------------------------------+
| ******************** Inposition Logic Define ****************************** |
+-----------------------------------------------------------------------------+
*/
#define     INP_ACT_LOW 				0
#define	   INP_ACT_HIGH 				1
/*
+-----------------------------------------------------------------------------+
| ******************** SD Enable Define ***************************** |
+-----------------------------------------------------------------------------+
*/
#define     SD_ENABLE 						0
#define	    SD_DISABLE 						1
/*
+-----------------------------------------------------------------------------+
| ******************** SD Latch Define ***************************** |
+-----------------------------------------------------------------------------+
*/
#define     SD_LEVEL 						0
#define	    SD_LATCH 						1
/*
+-----------------------------------------------------------------------------+
| ******************** SD Logic Define ****************************** |
+-----------------------------------------------------------------------------+
*/
#define     SD_ACT_LOW 				0
#define	    SD_ACT_HIGH 				1
/*
+-----------------------------------------------------------------------------+
| ******************** SD React Define *********************************** |
+-----------------------------------------------------------------------------+
*/
#define     SD_IMMED_STOP          1
#define     SD_DEC_AND_STOP 			0
/*
+-----------------------------------------------------------------------------+
| ****************** Hardware Limit Enable Define *************************** |
+-----------------------------------------------------------------------------+
*/
#define     HLMT_DIS 					0
#define	    HLMT_EN 						1
/*
+-----------------------------------------------------------------------------+
| ****************** Out Logic Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define     OUT_ACT_LOW 				0
#define	   OUT_ACT_HIGH 				1
/*
+-----------------------------------------------------------------------------+
| ****************** Dir Logic Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define     DIR_ACT_LOW 				0
#define	   DIR_ACT_HIGH 				1
/*
+-----------------------------------------------------------------------------+
| ****************** Erc Logic Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define	    ERC_DIS 			0
#define     ERC_EN 				1
/*
+-----------------------------------------------------------------------------+
| ****************** Erc Timer Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define	    ERC_OFF_TIME_DIS 			0
#define     ERC_OFF_TIME_EN 				1
/*
+-----------------------------------------------------------------------------+
| ****************** Hardware Limit Enable Define *************************** |
+-----------------------------------------------------------------------------+
*/
#define     HLMT_DIS 					0
#define	   HLMT_EN 						1
/*
+-----------------------------------------------------------------------------+
| ****************** Hardware Limit Logic Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define     HLMT_ACT_LOW 				0
#define	   HLMT_ACT_HIGH 				1
/*
+-----------------------------------------------------------------------------+
| ****************** Hardware Limit React Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define     HLMT_IMMED_STOP 			0
#define	   HLMT_DEC_TO_STOP 			1

/*
+-----------------------------------------------------------------------------+
| ****************** IN Disable or Enable Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define    IN_DISABLE              0
#define    IN_ENABLE               1
/*
+-----------------------------------------------------------------------------+
| ****************** Software Limit Enable Define *************************** |
+-----------------------------------------------------------------------------+
*/
#define     SLMT_DIS 					0
#define	   SLMT_EN 						1
/*
+-----------------------------------------------------------------------------+
| ****************** Software Limit React Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define     SLMT_IMMED_STOP 			0
#define	   SLMT_DEC_TO_STOP 			1
/*
+-----------------------------------------------------------------------------+
| ****************** ORG React Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define     ORG_IMMED_STOP 			0
#define	   ORG_DEC_TO_STOP 			1

/*
+-----------------------------------------------------------------------------+
| ****************** Ax General DOĦĦEnable Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define     GEN_DO_DISABLE 			0
#define	   GEN_DO_ENABLE 			1
/*
+-----------------------------------------------------------------------------+
| ****************** Ax External Master Source Define ************************ |
+-----------------------------------------------------------------------------+
*/
#define    EXT_MASTER_SRC_AX_0		0
#define	   EXT_MASTER_SRC_AX_1 		1
#define    EXT_MASTER_SRC_AX_2		2
#define	   EXT_MASTER_SRC_AX_3 		3
#define	   EXT_MASTER_SRC_SELF 		4
/*
+-----------------------------------------------------------------------------+
| ****************** Ax External Drive Mode ************************ |
+-----------------------------------------------------------------------------+
*/
#define    EXT_DRIVE_DISABLE		0
#define	   EXT_DRIVE_JOG 	     	1
#define    EXT_DRIVE_MPG		    2
#define    EXT_DRIVE_MPG_CONT	    3
#define    EXT_DRIVE_MPG_PRESETP	4
#define    EXT_DRIVE_MPG_PRESETN	5
/*
+-----------------------------------------------------------------------------+
| ********************* ORG Enable Define *********************************** |
+-----------------------------------------------------------------------------+
*/
#define     ORG_DISABLE 				0
#define	   ORG_ENABLE 					1
/*
+-----------------------------------------------------------------------------+
| ********************* ORG Logic Define ************************************ |
+-----------------------------------------------------------------------------+
*/
#define     ORG_ACT_LOW 				0
#define	   ORG_ACT_HIGH 				1
/*
+-----------------------------------------------------------------------------+
| ********************* ORG Latch Define ************************************ |
+-----------------------------------------------------------------------------+
*/
#define     ORG_LEVEL 				1
#define	   ORG_LATCH 				0
/*
+-----------------------------------------------------------------------------+
| ********************** EZ Enable Define *********************************** |
+-----------------------------------------------------------------------------+
*/
#define     EZ_DISABLE 					0
#define	   EZ_ENABLE 					1
/*
+-----------------------------------------------------------------------------+
| ********************** EZ Logic Define ************************************ |
+-----------------------------------------------------------------------------+
*/
#define     EZ_ACT_LOW 					0
#define	   EZ_ACT_HIGH 				1
/*
+-----------------------------------------------------------------------------+
| ********************** In1 Enable Define *********************************** |
+-----------------------------------------------------------------------------+
*/
#define     IN1_DISABLE 					0
#define	   IN1_ENABLE 					1
/*
+-----------------------------------------------------------------------------+
| ********************** IN1 Logic Define ************************************ |
+-----------------------------------------------------------------------------+
*/
#define     IN1_ACT_LOW 					0
#define	   IN1_ACT_HIGH 				1
/*
+-----------------------------------------------------------------------------+
| ********************** In2 Enable Define *********************************** |
+-----------------------------------------------------------------------------+
*/
#define     IN2_DISABLE 					0
#define	   IN2_ENABLE 					1
/*
+-----------------------------------------------------------------------------+
| ********************** IN2 Logic Define ************************************ |
+-----------------------------------------------------------------------------+
*/
#define     IN2_ACT_LOW 					0
#define	   IN2_ACT_HIGH 				1
/*
+-----------------------------------------------------------------------------+
| ********************** Servo State Define ********************************* |
+-----------------------------------------------------------------------------+
*/
#define     SV_OFF                  0
#define     SV_ON 						1
/*
+-----------------------------------------------------------------------------+
| ********************** Motion Axis State Define *************************** |
+-----------------------------------------------------------------------------+
*/
#define     STA_AX_DISABLE          0
#define     STA_AX_READY 			1
#define     STA_AX_STOPPING 	    2
#define     STA_AX_ERROR_STOP 	    3
#define     STA_AX_HOMING 			4
#define     STA_AX_PTP_MOT 			5
#define     STA_AX_CONTI_MOT 		6
#define     STA_AX_SYNC_MOT 		7
#define     STA_AX_EXT_JOG 		    8
#define     STA_AX_EXT_MPG		    9
#define     STA_AX_PAUSE			10 //  [5/16/2013 dan.yang]
#define     STA_AX_BUSY				11 //  [5/16/2013 dan.yang]

/*
+-----------------------------------------------------------------------------+
| ********************** Motion Group State Define ************************** |
+-----------------------------------------------------------------------------+
*/
#define     STA_GP_DISABLE          0
#define		STA_GP_READY            1
#define		STA_GP_STOPPING         2
#define		STA_GP_ERROR_STOP       3
#define		STA_GP_MOTION           4
#define		STA_GP_AX_MOTION        5
#define		STA_GP_MOTION_PATH      6
#define     STA_GP_PAUSE            7 //  [5/7/2013 dan.yang]
#define     STA_GP_BUSY             8 //  [5/15/2013 dan.yang]
/*
+-----------------------------------------------------------------------------+
| ********************** Motion Group State Define ************************** |//zhaocui add 201308
+-----------------------------------------------------------------------------+
*/
#define     STA_RB_DISABLE          0
#define		STA_RB_READY            1
#define		STA_RB_STOPPING         2
#define		STA_RB_ERROR_STOP       3
#define		STA_RB_MOTION           4
#define		STA_RB_AX_MOTION        5
#define		STA_RB_MOTION_PATH      6
#define     STA_RB_PAUSE            7 
#define     STA_RB_BUSY             8 
/*
+-----------------------------------------------------------------------------+
| ****************** Velocity Move Direction Define ************************* |
+-----------------------------------------------------------------------------+
*/
#define     DIR_POSITIVE            0
#define     DIR_NEGATIVE 			   1
/*
+-----------------------------------------------------------------------------+
| ********************* Motion Home Mode Define ***************************** |
+-----------------------------------------------------------------------------+
*/
#define     AbsSwitch               0
#define		LmtSwitch               1
#define		RefPulse                2
#define		Direct                  3

#define		MODE1_Abs			    0 
#define		MODE2_Lmt			    1
#define		MODE3_Ref			    2
#define		MODE4_Abs_Ref		    3
#define		MODE5_Abs_NegRef	    4
#define		MODE6_Lmt_Ref		    5
#define		MODE7_AbsSearch		    6
#define		MODE8_LmtSearch		    7
#define		MODE9_AbsSearch_Ref	    8
#define	    MODE10_AbsSearch_NegRef	9
#define	    MODE11_LmtSearch_Ref	10
#define	    MODE12_AbsSearchReFind			11 //  [6/13/2012 dan.yang]
#define	    MODE13_LmtSearchReFind			12 //  [6/13/2012 dan.yang]
#define	    MODE14_AbsSearchReFind_Ref		13 //  [6/13/2012 dan.yang]
#define	    MODE15_AbsSearchReFind_NegRef	14 //  [6/13/2012 dan.yang]
#define	    MODE16_LmtSearchReFind_Ref		15 //  [6/13/2012 dan.yang]

/*
+-----------------------------------------------------------------------------+
| ****************** Motion Home Direction Mode Define ********************** |
+-----------------------------------------------------------------------------+
*/
#define	   PosiDir                 0
#define	   NegDir                  1
#define	   SwitchPosi              2
#define	   SwitchNeg               3
/*
+-----------------------------------------------------------------------------+
| ********************* Motion Home Switch Mode Define ********************** |
+-----------------------------------------------------------------------------+
*/
#define     LevelOn                    0
#define	   LevelOff                   1
#define	   EdgeOn                     2
#define	   EdgeOff                    3
/*
+-----------------------------------------------------------------------------+
| ********************* Motion HomeEx Steps Define ********************** |
+-----------------------------------------------------------------------------+
*/
#define HomeStep0               0
#define HomeStep1               1
#define HomeStep2               2
#define HomeStep3               3
#define HomeStep4               4
#define HomeStep5               5
#define HomeStep6               6
/*
+-----------------------------------------------------------------------------+
| ***************** Arc Interpolation Direction Define ********************** |
+-----------------------------------------------------------------------------+
*/
#define     DIR_CW                     0
#define     DIR_CCW 			            1
/*
+-----------------------------------------------------------------------------+
| ***************** Compare Source Define *********************************** |
+-----------------------------------------------------------------------------+
*/
#define     SRC_COMMAND_POSITION            0
#define     SRC_ACTUAL_POSITION 			1
/*
+-----------------------------------------------------------------------------+
| ***************** Compare Pulse mode Define ******************************* |
+-----------------------------------------------------------------------------+
*/
#define     CMP_PULSE                     0
#define     CMP_TOGGLE 			          1
#define     CMP_PWM                       2
/*
+-----------------------------------------------------------------------------+
| ***************** Compare Enable Define *********************************** |
+-----------------------------------------------------------------------------+
*/
#define     CMP_ENABLE                     1
#define     CMP_DISABLE		               0
/*
+-----------------------------------------------------------------------------+
| ***************** Compare Pulse Logic Define ****************************** |
+-----------------------------------------------------------------------------+
*/
#define     CP_ACT_LOW                     0
#define     CP_ACT_HIGH 			       1
/*
+-----------------------------------------------------------------------------+
| ***************** Compare Pulse Width Define ****************************** |
+-----------------------------------------------------------------------------+
*/
#define     CP_5US                     0
#define     CP_10US                    1
#define     CP_20US                    2
#define     CP_50US                    3
#define     CP_100US                   4
#define     CP_200US                   5
#define     CP_500US                   6
#define     CP_1000US                  7
/*
+-----------------------------------------------------------------------------+
| ************************* Compare Method Define ****************************|
+-----------------------------------------------------------------------------+
*/
#define     MTD_GREATER_POSITION            0
#define     MTD_SMALLER_POSITION 			1
#define     MTD_DIRECTIONLESS 			    2
#define     MTD_UNDEFINED                   3 //  [4/13/2012 dan.yang]
/*


+-----------------------------------------------------------------------------+
| ************************* Event Type Define ******************************* |
+-----------------------------------------------------------------------------+
*/
#define     AX_MOTION_DONE             0x80
#define     AX_COMPARE                 0x1E
#define     EVT_NO_EVENT               0x00
#define     EVT_AX_MOTION_DONE         0x01
#define     EVT_AX_COMPARED            0x02
#define     EVT_AX_LATCHED             0x04     //  [Dan.Yang 2011.07.26]
#define     EVT_AX_ERROR               0x08     //  [12/14/2012 dan.yang]
#define     EVT_AX_VH_START			   0x10		//  [6/13/2012 dan.yang]
#define     EVT_AX_VH_END			   0x20		//  [6/13/2012 dan.yang]
#define     EVT_AX_LATCHBUF_DONE       0x40     //  [3/6/2013 dan.yang]

#define     EVT_GP_MOTION_DONE         0x02
#define     EVT_GP1_MOTION_DONE        0x01     // done event of GroupID 1
#define     EVT_GP2_MOTION_DONE        0x02     // done event of GroupID 2
#define     EVT_GP3_MOTION_DONE        0x04     // done event of GroupID 3
#define     EVT_GP4_MOTION_DONE        0x08
//Start High Speed
#define     EVT_GP1_VH_START           0x01  
#define     EVT_GP2_VH_START           0x02  
#define     EVT_GP3_VH_START           0x04
#define     EVT_GP4_VH_START           0x08 

//Start deceleration
#define     EVT_GP1_VH_END             0x01  
#define     EVT_GP2_VH_END             0x02
#define     EVT_GP3_VH_END             0x04
#define     EVT_GP4_VH_END             0x08

#define     EVT_CANCELED               0x10
#define     EVT_TIMEOUT                0xFFFF

enum  EVENT_TYPE
          {     
              TYPE_DISABLED,
				  
              TYPE_X_PULSE,
			  TYPE_X_GREATER_COMP_NEG, 
			  TYPE_X_LESS_COMP_NEG, 
			  TYPE_X_LESS_COMP_POS, 
			  TYPE_X_GREATER_COMP_POS, 
			  TYPE_X_C_END,
			  TYPE_X_C_STA,
			  TYPE_X_D_END,

			  TYPE_Y_PULSE,
			  TYPE_Y_GREATER_COMP_NEG, 
			  TYPE_Y_LESS_COMP_NEG, 
			  TYPE_Y_LESS_COMP_POS, 
			  TYPE_Y_GREATER_COMP_POS, 
			  TYPE_Y_C_END,
			  TYPE_Y_C_STA,
			  TYPE_Y_D_END,

			  TYPE_Z_PULSE,
			  TYPE_Z_GREATER_COMP_NEG, 
			  TYPE_Z_LESS_COMP_NEG, 
			  TYPE_Z_LESS_COMP_POS, 
			  TYPE_Z_GREATER_COMP_POS, 
			  TYPE_Z_C_END,
			  TYPE_Z_C_STA,
			  TYPE_Z_D_END,

			  TYPE_U_PULSE,
			  TYPE_U_GREATER_COMP_NEG, 
			  TYPE_U_LESS_COMP_NEG, 
			  TYPE_U_LESS_COMP_POS, 
			  TYPE_U_GREATER_COMP_POS, 
			  TYPE_U_C_END,
			  TYPE_U_C_STA,
			  TYPE_U_D_END,

			  TYPE_INTERPOLATION
    
          }; 
#define  MAX_EVENT_TYPE_NUM  64  //TYPE_IPO+1

#define NodeHd_Type                         0xFO
#define HdType_Dev     						0xF1
#define HdType_Axis    						0xF2
#define HdType_Group   						0xF3
#define HdType_AxInGp 						0xF4
#define HdType_MasDev  						0xF5

//WR3 setting can be one of these types
#define WR3_Mask             0X0f9f//use '&'
//#define Ax_Sync_TMove        0x0f98//use '&'{bit0:MANLD(0) bit1:DSNDE(0) bit2:SACC(0)}
//#define Ax_Async_TMove       0x0f9E//bit0:MANLD(1) bit1:DSNDE(1) bit2:SACC(0)
//#define Ax_Sync_SMove        0x0f99//use bit0:MANLD(0) bit1:DSNDE(0) bit2:SACC(1)
//#define Ax_Async_SMove       0x0f9f//bit0:MANLD(1) bit1:DSNDE(1) bit2:SACC(1)


//********************************Motion type of Axis OR Group*****************
//Ptp types:
#define Unknown         					0
#define SynTPtP         					1
#define AsynTPtP        					2
#define SynSPtP         					3
#define AsynSPtP        					4
//Conti types:
#define SynTConti       					5
#define AsynTConti      					6
#define SynSConti       					7
#define AsynSConti      					8
//Home types:
#define HomeEX                         9

//Stop types:
#define SynTDecStop                    22
#define AsynTDecStop                   23
#define SynSDecStop                    24
#define AsynSDecStop                   25

 #define EmgStop                        26
//IPO types:
#define SynTLineIpo                    27
#define AsynTLineIpo                   28
#define SynSLineIpo                    29
#define AsynSLineIpo                   30
#define SynTContiIpo                   31
#define AsynTContiIpo                  32
#define SynTArcIpo                     33
#define AsynTArcIpo                    34
#define SynTDirectIpo                  35
#define AsynTDirectIpo                 36
#define SynSDirectIpo                  37
#define AsynSDirectIpo                 38
#define SynTDecStopGp                  39
#define AsynTDecStopGp                 40
#define SynSDecStopGp                  41
#define AsynSDecStopGp                 42
#define EmgStopGp                      43

//  [2/26/2008 kiya.chen] add
#define SynSArcIpo                     44
#define AsynSArcIpo                    45
#define SynSContiIpo                   46
#define AsynSContiIpo                  47

//******************Home Sub Types***************************//

#define SearchLevelOnOrgByFixDir       0
#define SearchLevelOffOrgByFixDir      1
#define SearchEdgeOnOrgByFixDir        2 //HomeEX_SubType1,2,3,4
#define SearchEdgeOffOrgByFixDir       3
#define SearchLevelOnOrgBySwitchDir    4
#define SearchLevelOffOrgBySwitchDir   5
#define SearchEdgeOnOrgBySwitchDir     6//HomeEX_SubType5,6,7,8
#define SearchEdgeOffOrgBySwitchDir    7

#define SearchLevelOnLmtBySwitchDir    8
#define SearchLevelOffLmtBySwitchDir   9
#define SearchEdgeOnLmtByFixDir        10 //HomeEX_SubType9,10,11,12
#define SearchEdgeOnLmtBySwitchDir     11 //HomeEX_SubType13,14,15,16
#define SearchEdgeOffLmtBySwitchDir    12
#define SearchEz                       13 //HomeEX_SubType17,18,19,20

#define HomeEX_SubType1          1 //AbsSwitch+PosiDir+EdgeOn+HighActive
#define HomeEX_SubType2          2 //AbsSwitch+PosiDir+EdgeOn+LowActive
#define HomeEX_SubType3          3 //AbsSwitch+NegDir+EdgeOn+HighActive
#define HomeEX_SubType4          4 //AbsSwitch+NegDir+EdgeOn+LowActive
#define HomeEX_SubType5          5 //AbsSwitch+SwitchPosi+EdgeOn+HighActive
#define HomeEX_SubType6          6 //AbsSwitch+SwitchPosi+EdgeOn+LowActive
#define HomeEX_SubType7          7 //AbsSwitch+SwitchNeg+EdgeOn+HighActive
#define HomeEX_SubType8          8 //AbsSwitch+SwitchNeg+EdgeOn+LowActive

#define HomeEX_SubType9          9 //LimitSwitch+PosiDir+EdgeOn+HighActive
#define HomeEX_SubType10         10 //LimitSwitch+PosiDir+EdgeOn+LowActive
#define HomeEX_SubType11         11 //LimitSwitch+NegDir+EdgeOn+HighActive
#define HomeEX_SubType12         12 //LimitSwitch+NegDir+EdgeOn+LowActive
#define HomeEX_SubType13         13 //LimitSwitch+SwitchPosi+EdgeOn+HighActive
#define HomeEX_SubType14         14 //LimitSwitch+SwitchPosi+EdgeOn+LowActive
#define HomeEX_SubType15         15 //LimitSwitch+SwitchNeg+EdgeOn+HighActive
#define HomeEX_SubType16         16 //LimitSwitch+SwitchNeg+EdgeOn+LowActive

#define HomeEX_SubType17         17 //RefPulse+PosiDir+EdgeOn+HighActive
#define HomeEX_SubType18         18 //RefPulse+PosiDir+EdgeOn+LowActive
#define HomeEX_SubType19         19 //RefPulse+NegDir+EdgeOn+HighActive
#define HomeEX_SubType20         20 //RefPulse+NegDir+EdgeOn+LowActive
//******************End of Home Sub Types***************************//
//**********************************End of Motion type***************************

#define Ptp_PosDir                     0
#define Ptp_NegDir                     1

#define Conti_PosDir                   0
#define Conti_NegDir                   1

#define Home_PosDir                    0
#define Home_NegDir                    1
/*
+-----------------------------------------------------------------------------+
| ********************* Motion Home Phase Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define    Home_Phase_Search_ORG                    0
#define	   Home_Phase_Search_EL                     1
#define	   Home_Phase_Search_EZ                     2
#define	   Home_Phase_CrossDistance                 3
#define    Home_Phase_ORG_OUTING                    4
#define    Home_Phase_EL_OUTING                     5
#define    Home_Phase_EZ_OUTING                     6
/*
+-----------------------------------------------------------------------------+
| ********************* Motion Home Switch Mode Define ********************** |
+-----------------------------------------------------------------------------+
*/
#define    LevelOn                    0
#define	   LevelOff                   1
#define	   EdgeOn                     2
#define	   EdgeOff                    3
/*
+-----------------------------------------------------------------------------+
| ********************* Motion Path Cmd Define ****************************** |
+-----------------------------------------------------------------------------+
*/
#define     EndPath                    0
#define	   Abs2DLine                  1
#define	   Rel2DLine                  2
#define	   Abs2DArcCW                 3
#define	   Abs2DArcCCW                4
#define	   Rel2DArcCW                 5
#define	   Rel2DArcCCW                6
#define     Abs3DLine                  7
#define     Rel3DLine                  8
#define     AbsMultiLine                  9
#define     RelMultiLine                  10
//Add for pci1245 and pci1265[dan.yang 2011.05.04]// Reserved.
#define     Abs2DDirect                 11  
#define     Rel2DDirect                 12
#define     Abs3DDirect                 13
#define     Rel3DDirect                 14
#define     Abs4DDirect                 15
#define     Rel4DDirect                 16
#define     Abs5DDirect                 17
#define     Rel5DDirect                 18
#define     Abs6DDirect                 19
#define     Rel6DDirect                 20
#define     Abs3DArcCW                  21
#define     Rel3DArcCW                  22
#define     Abs3DArcCCW                 23
#define     Rel3DArcCCW                 24
#define     Abs3DSpiralCW               25  
#define     Rel3DSpiralCW               26
#define     Abs3DSpiralCCW              27
#define     Rel3DSpiralCCW              28
#define     GPDELAY                     29

#define     Abs4DSpiralCW               30  //add by zhaocui.deng 20130402
#define     Rel4DSpiralCW               31
#define     Abs4DSpiralCCW              32
#define     Rel4DSpiralCCW              33
#define     Abs5DSpiralCW               34  
#define     Rel5DSpiralCW               35
#define     Abs5DSpiralCCW              36
#define     Rel5DSpiralCCW              37
#define     Abs6DSpiralCW               38  
#define     Rel6DSpiralCW               39
#define     Abs6DSpiralCCW              40
#define     Rel6DSpiralCCW              41
#define     Abs7DSpiralCW               42  
#define     Rel7DSpiralCW               43
#define     Abs7DSpiralCCW              44
#define     Rel7DSpiralCCW              45
#define     Abs8DSpiralCW               46  
#define     Rel8DSpiralCW               47
#define     Abs8DSpiralCCW              48
#define     Rel8DSpiralCCW              49



//added by zhaocui.deng 20130502

#define	    Abs2DArcCWAngle                 50
#define	    Rel2DArcCWAngle                 51
#define	    Abs2DArcCCWAngle                52
#define	    Rel2DArcCCWAngle                53
#define     Abs3DArcCWAngle                 54
#define     Rel3DArcCWAngle                 55
#define     Abs3DArcCCWAngle                56
#define     Rel3DArcCCWAngle                57
#define     Abs3DSpiralCWAngle              58  
#define     Rel3DSpiralCWAngle              59
#define     Abs3DSpiralCCWAngle             60
#define     Rel3DSpiralCCWAngle             61
#define     Abs4DSpiralCWAngle              62  
#define     Rel4DSpiralCWAngle              63
#define     Abs4DSpiralCCWAngle             64
#define     Rel4DSpiralCCWAngle             65
#define     Abs5DSpiralCWAngle              66  
#define     Rel5DSpiralCWAngle              67
#define     Abs5DSpiralCCWAngle             68
#define     Rel5DSpiralCCWAngle             69
#define     Abs6DSpiralCWAngle              70 
#define     Rel6DSpiralCWAngle              71
#define     Abs6DSpiralCCWAngle             72
#define     Rel6DSpiralCCWAngle             73
#define     Abs7DSpiralCWAngle              74  
#define     Rel7DSpiralCWAngle              75
#define     Abs7DSpiralCCWAngle             76
#define     Rel7DSpiralCCWAngle             77
#define     Abs8DSpiralCWAngle              78  
#define     Rel8DSpiralCWAngle              79
#define     Abs8DSpiralCCWAngle             80
#define     Rel8DSpiralCCWAngle             81
#define     Abs7DDirect                     82
#define     Rel7DDirect                     83
#define     Abs8DDirect                     84
#define     Rel8DDirect                     85

#define     DoControl                   90  //  [2/27/2014 dan.yang]

/*
+-----------------------------------------------------------------------------+
| *********************Robot  Motion Path Cmd Define ************************ |
+-----------------------------------------------------------------------------+
*///  [9/17/2013 dan.yang]: For different with general path command.
#define RB_EndPath       0
#define RB_AbsMove       1
#define RB_RelMove       2
#define RB_AbsMoveDirect 3
#define RB_RelMoveDirect 4
#define RB_AbsMoveLine   5
#define RB_RelMoveLine   6
#define RB_AbsMoveArcCW    7 
#define RB_RelMoveArcCW    8 
#define RB_AbsMoveArcCCW    9 
#define RB_RelMoveArcCCW    10
#define RB_DELAY           11
/*+-----------------------------------------------------------------------------+
| ********************* Motion Path Mode Define ***************************** |
+-----------------------------------------------------------------------------+
*/
#define     BlendingEn                 0
#define     BlendingDis                1
#define     COUSTOM_MODE               2
/*

/*
+-----------------------------------------------------------------------------+
| ********************* Motion Event Name Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define     ADV_EVT_NUM                6
#define     ADV_EVT_AX_DONE            "EVT_AX_DONE"
#define     ADV_EVT_GP_DONE            "EVT_GP_DONE"
#define     ADV_EVT_CANCELED           "EVT_CANCELED"
	

/*
+-----------------------------------------------------------------------------+
| *********************** Axis ERC Map Define ******************************* |
+-----------------------------------------------------------------------------+
*/
#define     AX_ERC_EN_MODE          1
#define     AX_ERC_LOGIC            2
#define     AX_ERC_ON_TIME          4
#define     AX_ERC_OFF_TIME         8


/*
+-----------------------------------------------------------------------------+
| ******************** Axis ERC On-Time Map Define ************************** |
+-----------------------------------------------------------------------------+
*/
#define     AX_ERC_ON_12US				1
#define     AX_ERC_ON_102US			2
#define     AX_ERC_ON_409US			4
#define     AX_ERC_ON_1600US			8
#define     AX_ERC_ON_13MS				16
#define     AX_ERC_ON_52MS				32
#define     AX_ERC_ON_104MS			64
#define     AX_ERC_ON_LEVEL			128

/*
+-----------------------------------------------------------------------------+
| ******************** Axis ERC Enable mode Map Define ********************** |
+-----------------------------------------------------------------------------+
*/
#define     AX_ERC_ON_HOME          1
#define     AX_ERC_ON_MIO		     2
#define     AX_ERC_ON_HOME_MIO      4

/*
+-----------------------------------------------------------------------------+
| ******************** Axis ERC Off-Time Map Define ************************** |
+-----------------------------------------------------------------------------+
*/
#define     AX_ERC_OFF_0US				1
#define     AX_ERC_OFF_12US			2
#define     AX_ERC_OFF_1600US			4
#define     AX_ERC_OFF_104MS			8

/*
+-----------------------------------------------------------------------------+
| ******************** Axis BACKLASH Map Define ************************** |
+-----------------------------------------------------------------------------+
*/
#define     AX_BKSH_EN					1
#define     AX_BKSH_VALUE				2

/*
+-----------------------------------------------------------------------------+
| ******************** Axis VIBRATION Map Define ************************** |
+-----------------------------------------------------------------------------+
*/
#define     AX_VIBRA_EN					1
#define     AX_VIBRA_FWD_VALUE		2
#define     AX_VIBRA_REV_VALUE		4



/*
+-----------------------------------------------------------------------------+
| ***************** ERC Acitve Logic Define ********************************* |
+-----------------------------------------------------------------------------+
*/
#define     ERC_ACT_LOW                        0
#define     ERC_ACT_HIGH 			            1


//Added by Dean -----------------------------------------------
#define     ERC_ON_DISABLE       0
#define     ERC_ON_HOME          1
#define     ERC_ON_MIO		      2
#define     ERC_ON_HOME_MIO      3

/*
+-----------------------------------------------------------------------------+
| ******************** Axis ERC On-Time Define ****************************** |
+-----------------------------------------------------------------------------+
*/
#define     ERC_ON_12US				0
#define     ERC_ON_102US			1
#define     ERC_ON_409US			2
#define     ERC_ON_1600US			3
#define     ERC_ON_13MS				4
#define     ERC_ON_52MS				5
#define     ERC_ON_104MS			6
#define     ERC_ON_LEVEL			7

/*
+-----------------------------------------------------------------------------+
| ******************** Axis ERC Off-Time Define ***************************** |
+-----------------------------------------------------------------------------+
*/
#define     ERC_OFF_0US				0
#define     ERC_OFF_12US			1
#define     ERC_OFF_1600US			2
#define     ERC_OFF_104MS			3

/*
+-----------------------------------------------------------------------------+
| ***************** ERC on home Define(only for KW Dialog) ****************** |
+-----------------------------------------------------------------------------+
*/
#define     ERC_HOME_DISABLE                    0
#define     ERC_HOME_ENABLE 			            1

/*
+-----------------------------------------------------------------------------+
| ***************** ERC on motion_io Define(only for KW Dialog) ************* |
+-----------------------------------------------------------------------------+
*/
#define     ERC_ERRMIO_DISABLE                        0
#define     ERC_ERRMIO_ENABLE 			            1

/*
+-----------------------------------------------------------------------------+
| ****************** SD  Enable Define *************************** |
+-----------------------------------------------------------------------------+
*/
#define     SD_DIS 					0
#define		SD_EN 					1
/*
+-----------------------------------------------------------------------------+
| ****************** SD React Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define     SD_DEC		 			0
#define		SD_DEC_TO_STOP 			1

/*
+-----------------------------------------------------------------------------+
| ****************** SD Latch Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define     SD_LATCH_DIS			0
#define		SD_LATCH_EN 			1

/*
+-----------------------------------------------------------------------------+
| ****************** Latch Logic Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define     LATCH_ACT_LOW 				0
#define		LATCH_ACT_HIGH 			1

/*
+-----------------------------------------------------------------------------+
| ****************** Home Reset Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define     HOME_RESET_DIS			0
#define		HOME_RESET_EN 			1
/*
+-----------------------------------------------------------------------------+
| ****************** Backlash enable Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define     BKSH_DIS			0
#define		BKSH_EN 			1
/*
+-----------------------------------------------------------------------------+
| ****************** Viabration enable Define **************************** | //ydd:modified.20110309
+-----------------------------------------------------------------------------+
*/
#define     VIBRA_DIS			0
#define		VIBRA_EN 			1

/*
+-----------------------------------------------------------------------------+
| ****************** Baudrate Define **************************** |
+-----------------------------------------------------------------------------+
*/
#define		BR_AMONET_2500K		0x00
#define		BR_AMONET_5M		0x01
#define		BR_AMONET_10M		0x02
#define		BR_AMONET_20M		0x03
#define		BR_CAN_10K			0x10
#define		BR_CAN_20K			0x11
#define		BR_CAN_50K			0x12
#define		BR_CAN_125K			0x13
#define		BR_CAN_250K			0x14
#define		BR_CAN_500K			0x15
#define		BR_CAN_800K			0x16
#define		BR_CAN_1000K		0x17

/*
+-----------------------------------------------------------------------------+
| ****************** Master Communication Status **************************** |
+-----------------------------------------------------------------------------+
*/
#define  COM_ST_DISCONNECTED    0x00
#define  COM_ST_CONNECTED       0x01
#define  COM_ST_SLAVE_ERROR     0x02
#define  COM_ST_BUSY            0x03
#define  COM_ST_ERROR           0x04

/*
+-----------------------------------------------------------------------------+
| ********************* CAM DO Mode ***************************************** |
+-----------------------------------------------------------------------------+
//Add for pci1245 and pci1265.[dan.yang 2011.05.25]
*/
#define     CamDOByPosition			         0
#define		CamDOByTime			             1

/*
+-----------------------------------------------------------------------------+
| ********************* Encode Pulse in Max Frequency ***************************************** |
+-----------------------------------------------------------------------------+
//Add for pci1245 and pci1265.[dan.yang 2011.06.20]
*/
#define    ENC_500KHZ 					0x00
#define	   ENC_1MHZ 					0x01
#define	   ENC_2MHZ 					0x02
#define	   ENC_4MHZ	 					0x03
/*
+-----------------------------------------------------------------------------+
| *********************Reference plane for Arc interpolation /spiral interpolation/Gantry function * |
+-----------------------------------------------------------------------------+
//Add for pci1245 and pci1265.[dan.yang 2011.06.20]
*/
#define  XY_PLANE                        0
#define  YZ_PLANE                        1
#define  XZ_PLANE                        2
/*
+-----------------------------------------------------------------------------+
| *********************PWM ***************************************************|
+-----------------------------------------------------------------------------+
//Add for pci1245 and pci1265.[zhaocui  2013.07.15]
*/
#define MaxPWMFreq    250000
#define MinPWMFreq    1
/*
+-----------------------------------------------------------------------------+
| ********** Motion DAQ channel type MAP* |
+-----------------------------------------------------------------------------+
//Add for pci1245 and pci1265.[dan.yang 2012.06.13]
*/
#define MP_MQ_TYPE_CMDPOSI               0x01                         // cmd position information
#define MP_MQ_TYPE_ACTPOSI               0x02                         // act position information
#define MP_MQ_TYPE_LAGPOSI               0x04                         // cmd - act position information
#define MP_MQ_TYPE_CMDVEL                0x08                         // cmd velocity information (reserved)
/*
+-----------------------------------------------------------------------------+
| *********************Motion DAQ Channel Type * |
+-----------------------------------------------------------------------------+
//Add for pci1245 and pci1265.[dan.yang 2012.06.13]
*/
#define MQ_TYPE_CMDPOSI               0                        // cmd position information
#define MQ_TYPE_ACTPOSI               1                        // act position information
#define MQ_TYPE_LAGPOSI               2                        // cmd - act position information
#define MQ_TYPE_CMDVEL                3                        // cmd velocity information (reserved)
/*
+-----------------------------------------------------------------------------+
| *********************Motion DAQ trigger type * |
+-----------------------------------------------------------------------------+
//Add for pci1245 and pci1265.[dan.yang 2012.06.13]
*/
// Motion DAQ trigger type (each channel can be set to trigger in what state )
#define MQ_TRIG_DISABLE			0				// Disable
#define MQ_TRIG_SW				1				// Trigger by Software 
#define MQ_TRIG_DI				2				// Trigger by DI (reserved)
#define MQ_TRIG_AX0_START		3				// Trigger by Axis0 start move
#define MQ_TRIG_AX1_START		4				// Trigger by Axis1 start move
#define MQ_TRIG_AX2_START		5				// Trigger by Axis2 start move
#define MQ_TRIG_AX3_START		6				// Trigger by Axis3 start move
#define MQ_TRIG_AX4_START		7				// Trigger by Axis4 start move
#define MQ_TRIG_AX5_START		8				// Trigger by Axis5 start move
#define MQ_TRIG_AX6_START		9				// Trigger by Axis6 start move
#define MQ_TRIG_AX7_START		10				// Trigger by Axis7 start move
#define MQ_TRIG_AX8_START		11				// Trigger by Axis8 start move
#define MQ_TRIG_AX9_START		12				// Trigger by Axis9 start move
#define MQ_TRIG_AX10_START		13				// Trigger by Axis10 start move
#define MQ_TRIG_AX11_START		14				// Trigger by Axis11 start move

/*
+-----------------------------------------------------------------------------+
| *********************Motion DAQ trigger Map * |
+-----------------------------------------------------------------------------+
//Add for pci1245 and pci1265.[dan.yang 2012.06.18]
*/
#define MP_MQ_TRIG_DISABLE			0x0000				// Disable
#define MP_MQ_TRIG_SW				0x0001				// Trigger by Software 
#define MP_MQ_TRIG_DI				0x0002				// Trigger by DI (reserved)
#define MP_MQ_TRIG_AX_START			0x0004				// Trigger by AXIS

/*
+-----------------------------------------------------------------------------+
| *********************Home Mode Map * |
+-----------------------------------------------------------------------------+
//Add for pci1245 and pci1265.[dan.yang 2012.06.13]
*/
#define		MP_MODE1_Abs							0x0001 
#define		MP_MODE2_Lmt							0x0002
#define		MP_MODE3_Ref							0x0004
#define		MP_MODE4_Abs_Ref						0x0008
#define		MP_MODE5_Abs_NegRef						0x0010
#define		MP_MODE6_Lmt_Ref						0x0020
#define		MP_MODE7_AbsSearch						0x0040
#define		MP_MODE8_LmtSearch						0x0080
#define		MP_MODE9_AbsSearch_Ref					0x0100
#define	    MP_MODE10_AbsSearch_NegRef				0x0200
#define	    MP_MODE11_LmtSearch_Ref					0x0400
#define	    MP_MODE12_AbsSearchReFind				0x0800
#define	    MP_MODE13_LmtSearchReFind				0x1000
#define	    MP_MODE14_AbsSearchReFind_Ref			0x2000
#define	    MP_MODE15_AbsSearchReFind_NegRef		0x4000
#define	    MP_MODE16_LmtSearchReFind_Ref			0x8000

#endif // __ADV_MOT_DRV_H__

