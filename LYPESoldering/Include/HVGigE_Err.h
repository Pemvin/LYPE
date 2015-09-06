
/*****************************************************************************
* File Name:	HVGigE_Err.h
* Author: IndCam
* DATE: 2011.06.20
* Description:  ������
* Functions:
*    ��
* Current Version:
*    V1.0.0
* Revision:
*    DATE          NAME      DESCRIPTION
******************************************************************************/

#ifndef _HVGigE_ERR_H
#define _HVGigE_ERR_H

#define HV_UNSUCCESS               0xE0000000    //����ʧ��
#define HV_NO_SUCH_DEVICE	       0xE0000001    //�Ҳ���ָ�����豸
#define HV_DEVICE_INIT_FAIL        0xE0000002    //�豸��ʼ��ʧ��
#define HV_DEVICE_INIT_NOT         0xE0000003    //û���豸��ʼ��
#define HV_CAP_INIT_FAIL           0xE0000004    //�����ʼ��ʧ��
#define HV_CAP_INIT_NOT            0xE0000005    //û�в����ʼ��
#define HV_CAPTURE_STOP            0xE0000006    //����ֹͣ



	#define HV_DEVICE_NOT_MATCH			0xE0000007	//�豸��ƥ��
	#define HV_DEVICE_TRANS_FAILED		0xE0000008	//�豸����ʧ��
	#define HV_CONFIGFILE_NOT_MATCH		0xE0000009	//�����ļ���ƥ��
 	#define HV_INVALID_PARAM			0xE000000A	//��Ч����
	#define HV_INVALID_TRIGGER_SOURCE	0xE000000B	//��Ч�Ĵ���Դ
	#define HV_INVALID_TRIGGER_MODE		0xE000000C	//��Ч�Ĵ���ģʽ
	#define HV_INVALID_HANDLE_VALUE		0xE000000D	//��Ч�ľ��ֵ
	#define HV_INSUFFICIENT_RESOURCE	0xE000000E	//��Դ����
	#define HV_REASONLESS_PARAMETER		0xE000000F	//������Ĳ���
	#define HV_RESONLESS_PACKETSIZE		0xE0000010	//������İ���С
	#define HV_FEATURE_NOT_SUPPORT		0xE0000011	//�������Բ�֧��
	#define HV_VIDEOFORMAT_NOT_SUPPORT	0xE0000012	//��Ƶ��ʽ��֧��
	#define HV_TRIGGER_NOT_SUPPORT	    0xE0000013	//������֧��
	#define HV_STROBE_NOT_SUPPORT		0xE0000014	//Ƶ����ͨ����֧��
	#define HV_FRAMERATE_NOT_SUPPORT	0xE0000015	//֡Ƶ��֧��
	#define HV_PIXELFORMAT_NOT_SUPPORT	0xE0000016	//���ظ�ʽ��֧��
	#define HV_AOI_NOT_SUPPORT		    0xE0000017	//������֧��
	#define HV_REGISTER_RW_NOT_SUPPORT	0xE0000018	//ĳ��ַ�ļĴ�����д��֧��
	#define HV_AUTOWHB_NOT_SUPPORT	    0xE0000019	//�Զ���ƽ�ⲻ֧��
	#define HV_TRANSMODE_NOT_SUPPORT	0xE000001A	//����ģʽ��֧��
	#define HV_TRANSSPEED_NOT_SUPPORT	0xE000001B	//�����ٶȲ�֧��
	#define HV_SOFTTRIGGER_BUSY			0xE000001C	//��һ֡�������û�н���
	#define HV_DEVICE_NOT_RUN			0xE000001D	//�豸δ����

	#define HV_SEND_PACKET_FAIL			0xE000001E  //�������ݰ�ʧ��
#define  HV_RESET_BUFFER_FAIL           0xE000001F  //���ķֱ��ʺ�Reset Bufferʧ��

#define HV_PACKET_TIMEOUT          0xE0000100    //��ȡPacket��ʱ
#define HV_DEVICE_CONNECT_TIMEOUT	0xE0000101	  //������ӳ�ʱ

#endif