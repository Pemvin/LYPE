//IOCard.h:interface for the IOCard class
//
/////////////////////////////////////////

#if !defined(AFX_SILKSEND_H__798BC7C3_F372_495B_B5A1_6F065B0C145D__INCLUDED_)
#define AFX_SILKSEND_H__798BC7C3_F372_495B_B5A1_6F065B0C145D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "driver.h"

class CIOCard
{
public:
	//IO
	LRESULT		m_ErrCode;
	unsigned char			m_szBuffer[100];
	unsigned char			m_szErrorMsg[40];
	HGLOBAL					m_hUserBuf;
	HGLOBAL					m_hBuf;
	int						m_Conv;
	PT_FAIIntStart			m_ptFAIIntStart;					// FAIIntStart table
	PT_FAITransfer			m_ptFAITransfer;					// FAITransfer table
	PT_EnableEvent			m_ptEnableEvent;					// Enable event
	PT_CheckEvent			m_ptCheckEvent;						// Check event
	USHORT					m_gwOverrun;						// return by FAICheck, FAITransfer

	DEVLIST					m_DeviceList[100];
	DEVLIST					m_SubDeviceList[100];
	LONG					m_lDriverHandle;					// driver handle
	USHORT					m_usDevice, m_usSubDevice;			// Device index
	USHORT					m_usGain;							// gain index
	SHORT					m_sNumOfDevices, m_sNumOfSubdevices;// number of installed devices
	LRESULT					m_lrErrCode;
	char					m_szErrMsg[80];
	DEVFEATURES				m_DevFeatures;						// structure for device features
	PT_DeviceGetFeatures	m_ptDevFeatures;
	USHORT					m_usPort;
protected:
	PT_DioReadPortWord      m_ptDioReadPortWord;				//DioReadPortWord table
	PT_DioWritePortWord     m_ptDioWritePortWord;				//DioWritePortWord table
	PT_DioGetCurrentDOWord	m_ptDioGetCurrentDOWord;			//DioGetCurrentDOWord table
	PT_AOVoltageOut			m_ptAIVoltageOut;					// structure for AIVoltageIn table
	PT_AIConfig				m_ptAIConfig;						// structure for AIConfig table
	PT_AIVoltageIn			m_ptAIVoltageIn;					// structure for AIVoltageIn table

	USHORT					m_usValidMask;						// read port Word  valid mask
	USHORT					m_usWriteMask;						// write port Word  mask
	USHORT					m_usAOChannel;
	USHORT					m_usAIChannel;
//	USHORT					m_usGetDOValue;
	BOOL					IOCardInitial;
	
public:
	CIOCard();
	~CIOCard();
	BOOL ProcessInit(void);
	unsigned short ReadDOPort(void);
	void WriteDOPort(unsigned short m_PortNum, BOOL bValue);
	unsigned short ReadDIPort(void);
	void SendAOPort(unsigned short m_usChan,float m_fSendData);
	float ReadAIPort(unsigned short m_usChan);
};
#endif //!defined(AFX_SILKSEND_H__798BC7C3_F372_495B_B5A1_6F065B0C145D__INCLUDED_)