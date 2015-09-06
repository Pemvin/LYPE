// IOCard.cpp: implementation of the CIOCard class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "IOCard.h"
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIOCard

CIOCard::CIOCard()
{
	memset(&m_DeviceList,0,sizeof(m_DeviceList));
	memset(&m_SubDeviceList,0,sizeof(m_SubDeviceList));
	m_lDriverHandle=NULL;          // driver handle
	m_usDevice=0;
	m_usSubDevice=0;      // Device index
	m_usGain=0;                         // gain index
	m_sNumOfDevices=0;
	m_sNumOfSubdevices=0;  // number of installed devices
	m_usPort = 0;
	m_usWriteMask = 0xFFFF;	

	m_usAOChannel=0;
	m_usAIChannel=0;
	m_Conv=100;
	IOCardInitial = FALSE;
	int	nOutEntries;
	// TODO: Add extra initialization here
    // --------------------------------
    // Initialize Device List Combobox
    // --------------------------------
    // get number of the installed devices
    if ((m_lrErrCode = DRV_DeviceGetNumOfList((SHORT far *)&m_sNumOfDevices)) != SUCCESS)
    {
         DRV_GetErrorMessage(m_lrErrCode,(LPSTR)m_szErrMsg);
         AfxMessageBox((LPCTSTR)m_szErrMsg);
         return;
    }
    if (m_sNumOfDevices > 100)
        m_sNumOfDevices = 100;

    // retrieve the information of all installed devices
    if ((m_lrErrCode = DRV_DeviceGetList((DEVLIST far *)&m_DeviceList[0],
        (SHORT)m_sNumOfDevices, (SHORT far *)&nOutEntries)) != (LONG)SUCCESS)
    {
        DRV_GetErrorMessage(m_lrErrCode,(LPSTR)m_szErrMsg);
        AfxMessageBox((LPCTSTR)m_szErrMsg);
        return;
    }

	m_usDevice=0;
    // check if there is any device attached on this COM port or CAN
    m_sNumOfSubdevices = m_DeviceList[m_usDevice].nNumOfSubdevices;
    if (m_sNumOfSubdevices > 100)
        m_sNumOfSubdevices = 100;

    // retrieve the information of all installed devices
    if (m_sNumOfSubdevices != 0)
    {
        if ((m_lrErrCode = DRV_DeviceGetSubList(
            (DWORD)m_DeviceList[m_usDevice].dwDeviceNum,
            (DEVLIST far *)&m_SubDeviceList[0],
            (SHORT)m_sNumOfSubdevices,
            (SHORT far *)&nOutEntries)) != (LONG)SUCCESS)
        {
            DRV_GetErrorMessage(m_lrErrCode,(LPSTR)m_szErrMsg);
            AfxMessageBox((LPCTSTR)m_szErrMsg);
            return;
        }
		m_usSubDevice=0;
    }
	DRV_DeviceClose((LONG far *)&m_lDriverHandle);
}

CIOCard::~CIOCard()
{
	SendAOPort(0,0);
	SendAOPort(1,0);
	DRV_DeviceClose((LONG far *)&m_lDriverHandle);

	GlobalUnlock(m_hBuf);
	GlobalUnlock(m_hUserBuf);
	GlobalFree(m_hBuf);
	GlobalFree(m_hUserBuf);
}

BOOL CIOCard::ProcessInit()
{
	int	i=0;
	//
	// open device
	if (m_sNumOfSubdevices == 0)
	{
		m_lrErrCode = DRV_DeviceOpen(m_DeviceList[m_usDevice].dwDeviceNum,(LONG far *)&m_lDriverHandle);
	}
	else
	{
		m_lrErrCode = DRV_DeviceOpen(m_SubDeviceList[m_usSubDevice].dwDeviceNum,(LONG far *)&m_lDriverHandle);
	}

	if (m_lrErrCode != SUCCESS)
	{
		AfxMessageBox(_T("数据采集卡无法找到，初始化失败!"));
		IOCardInitial = FALSE;
		return FALSE;
	}

	//Get device features
    m_ptDevFeatures.buffer = (LPDEVFEATURES)&m_DevFeatures;
    m_ptDevFeatures.size = sizeof(DEVFEATURES);
    m_lrErrCode = DRV_DeviceGetFeatures(m_lDriverHandle,(LPT_DeviceGetFeatures)&m_ptDevFeatures);
    if (m_lrErrCode != SUCCESS)
    {
         DRV_GetErrorMessage(m_lrErrCode,(LPSTR)m_szErrMsg);
         AfxMessageBox((LPCTSTR)m_szErrMsg);
         DRV_DeviceClose((LONG far *)&m_lDriverHandle);
    }

	m_ptAIConfig.DasGain = m_DevFeatures.glGainList[m_usGain].usGainCde;
    m_ptAIConfig.DasChan = m_usAIChannel;

    if ((m_lrErrCode = DRV_AIConfig(m_lDriverHandle,
         (LPT_AIConfig)&m_ptAIConfig)) != 0)
    {
        DRV_GetErrorMessage(m_lrErrCode,(LPSTR)m_szErrMsg);
        AfxMessageBox((LPCTSTR)m_szErrMsg);
        DRV_DeviceClose((LONG far *)&m_lDriverHandle);
    }
	IOCardInitial = TRUE;
	return TRUE;
}

unsigned short CIOCard::ReadDOPort(void)
{	
	if(!IOCardInitial)
	{
		return 0;
	}
	unsigned short	usResult=0x0000;
	m_ptDioGetCurrentDOWord.port = m_usPort;
	m_ptDioGetCurrentDOWord.ValidChannelMask = ( USHORT far * )&m_usValidMask;
	m_ptDioGetCurrentDOWord.value = ( USHORT far * )&usResult;
	m_lrErrCode = DRV_DioGetCurrentDOWord( 
            m_lDriverHandle,
			( LPT_DioGetCurrentDOWord )&m_ptDioGetCurrentDOWord );
    if ( m_lrErrCode != 0)
	{
	  DRV_GetErrorMessage(m_lrErrCode,(LPSTR)m_szErrMsg);
	  AfxMessageBox((LPCTSTR)m_szErrMsg);
	}
	return usResult;
}

void CIOCard::WriteDOPort(unsigned short m_PortNum, BOOL bValue)
{
	if(!IOCardInitial)
	{
		return;
	}
	unsigned short temps;
	temps=ReadDOPort();
	m_ptDioWritePortWord.port = m_usPort;
    m_ptDioWritePortWord.mask = m_usWriteMask;
	if(bValue)
		m_ptDioWritePortWord.state = (USHORT)( temps | (0x0001 << m_PortNum));
	else
		m_ptDioWritePortWord.state = (USHORT)( temps & (~(0x0001 << m_PortNum)));

    m_lrErrCode = DRV_DioWritePortWord(
           m_lDriverHandle, 
		   (LPT_DioWritePortWord)&m_ptDioWritePortWord);
    if ( m_lrErrCode != 0)
	{
	  DRV_GetErrorMessage(m_lrErrCode,(LPSTR)m_szErrMsg);
	  AfxMessageBox((LPCTSTR)m_szErrMsg);
	}
}

unsigned short CIOCard::ReadDIPort(void)
{
	if(!IOCardInitial)
	{
		return 0;
	}
	unsigned short	usResult=0x0000;
	m_ptDioReadPortWord.port = m_usPort;
	m_ptDioReadPortWord.ValidChannelMask = ( USHORT far * )&m_usValidMask;
	m_ptDioReadPortWord.value = ( USHORT far * )&usResult;
	m_lrErrCode = DRV_DioReadPortWord(
					m_lDriverHandle, 
					(LPT_DioReadPortWord)&m_ptDioReadPortWord);
	if ( m_lrErrCode != 0 )
	{
		DRV_GetErrorMessage(m_lrErrCode,(LPSTR)m_szErrMsg);
		AfxMessageBox((LPCTSTR)m_szErrMsg);
	}
	return usResult;
}

void CIOCard::SendAOPort(unsigned short m_usChan,float m_fSendData)
{
	if(!IOCardInitial)
	{
		return;
	}
	m_ptAIVoltageOut.chan = m_usChan;
    m_ptAIVoltageOut.OutputValue = m_fSendData;

    if ((m_lrErrCode = DRV_AOVoltageOut(m_lDriverHandle,
               (LPT_AOVoltageOut)&m_ptAIVoltageOut)) != 0)
    {
        DRV_GetErrorMessage(m_lrErrCode,(LPSTR)m_szErrMsg);
        AfxMessageBox((LPCTSTR)m_szErrMsg);
    }
}

float CIOCard::ReadAIPort(unsigned short m_usChan)
{
	if(!IOCardInitial)
	{
		return 0;
	}
	float aiValue;
	m_ptAIVoltageIn.chan = m_usAIChannel;
    m_ptAIVoltageIn.gain = m_ptAIConfig.DasGain;
    m_ptAIVoltageIn.TrigMode = 0;               // internal trigger
    m_ptAIVoltageIn.voltage = (FLOAT far *)&aiValue;

    if ((m_lrErrCode = DRV_AIVoltageIn(m_lDriverHandle,
               (LPT_AIVoltageIn)&m_ptAIVoltageIn)) != 0)
    {
        DRV_GetErrorMessage(m_lrErrCode,(LPSTR)m_szErrMsg);
        AfxMessageBox((LPCTSTR)m_szErrMsg);
        DRV_DeviceClose((LONG far *)&m_lDriverHandle);
    }
	return aiValue;
}
