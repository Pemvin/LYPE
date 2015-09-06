
/*****************************************************************************
* File Name:	HVGigE_Err.h
* Author: IndCam
* DATE: 2011.06.20
* Description:  错误定义
* Functions:
*    …
* Current Version:
*    V1.0.0
* Revision:
*    DATE          NAME      DESCRIPTION
******************************************************************************/

#ifndef _HVGigE_ERR_H
#define _HVGigE_ERR_H

#define HV_UNSUCCESS               0xE0000000    //操作失败
#define HV_NO_SUCH_DEVICE	       0xE0000001    //找不到指定的设备
#define HV_DEVICE_INIT_FAIL        0xE0000002    //设备初始化失败
#define HV_DEVICE_INIT_NOT         0xE0000003    //没有设备初始化
#define HV_CAP_INIT_FAIL           0xE0000004    //捕获初始化失败
#define HV_CAP_INIT_NOT            0xE0000005    //没有捕获初始化
#define HV_CAPTURE_STOP            0xE0000006    //捕获停止



	#define HV_DEVICE_NOT_MATCH			0xE0000007	//设备不匹配
	#define HV_DEVICE_TRANS_FAILED		0xE0000008	//设备传输失败
	#define HV_CONFIGFILE_NOT_MATCH		0xE0000009	//配置文件不匹配
 	#define HV_INVALID_PARAM			0xE000000A	//无效参数
	#define HV_INVALID_TRIGGER_SOURCE	0xE000000B	//无效的触发源
	#define HV_INVALID_TRIGGER_MODE		0xE000000C	//无效的触发模式
	#define HV_INVALID_HANDLE_VALUE		0xE000000D	//无效的句柄值
	#define HV_INSUFFICIENT_RESOURCE	0xE000000E	//资源不足
	#define HV_REASONLESS_PARAMETER		0xE000000F	//不合理的参数
	#define HV_RESONLESS_PACKETSIZE		0xE0000010	//不合理的包大小
	#define HV_FEATURE_NOT_SUPPORT		0xE0000011	//特性属性不支持
	#define HV_VIDEOFORMAT_NOT_SUPPORT	0xE0000012	//视频格式不支持
	#define HV_TRIGGER_NOT_SUPPORT	    0xE0000013	//触发不支持
	#define HV_STROBE_NOT_SUPPORT		0xE0000014	//频闪灯通道不支持
	#define HV_FRAMERATE_NOT_SUPPORT	0xE0000015	//帧频不支持
	#define HV_PIXELFORMAT_NOT_SUPPORT	0xE0000016	//像素格式不支持
	#define HV_AOI_NOT_SUPPORT		    0xE0000017	//开窗不支持
	#define HV_REGISTER_RW_NOT_SUPPORT	0xE0000018	//某地址的寄存器读写不支持
	#define HV_AUTOWHB_NOT_SUPPORT	    0xE0000019	//自动白平衡不支持
	#define HV_TRANSMODE_NOT_SUPPORT	0xE000001A	//传输模式不支持
	#define HV_TRANSSPEED_NOT_SUPPORT	0xE000001B	//传输速度不支持
	#define HV_SOFTTRIGGER_BUSY			0xE000001C	//上一帧软件触发没有结束
	#define HV_DEVICE_NOT_RUN			0xE000001D	//设备未运行

	#define HV_SEND_PACKET_FAIL			0xE000001E  //发送数据包失败
#define  HV_RESET_BUFFER_FAIL           0xE000001F  //更改分辨率后，Reset Buffer失败

#define HV_PACKET_TIMEOUT          0xE0000100    //获取Packet超时
#define HV_DEVICE_CONNECT_TIMEOUT	0xE0000101	  //相机链接超时

#endif