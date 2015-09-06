// ProfileINI.cpp: implementation of the CProfileINI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProfileINI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProfileINI::CProfileINI()
{

}

CProfileINI::~CProfileINI()
{

}
int CProfileINI::GetIni(CString Field)
{
    return(::GetPrivateProfileInt(m_MainField,Field,0,m_IniFilePath));
}

double CProfileINI::GetDouble(CString Field)
{
    CString TempValue;
    ::GetPrivateProfileString(m_MainField,Field,_T("Error"),
		TempValue.GetBuffer(10),10,m_IniFilePath);
	return(_ttof(TempValue));
}

CString CProfileINI::GetString(CString Field)
{
    CString TempValue;
	char TempChar[256];
	::GetPrivateProfileString(m_MainField,Field,_T("Error"),
		(LPWSTR)TempChar,256,m_IniFilePath);
	TempValue.Format(_T("%s"),TempChar);
	return(TempValue);
}

BOOL CProfileINI::SetValue(int Value, CString Field)
{
    CString TempValue;
	TempValue.Format(_T("%d"),Value);
	return(WritePrivateProfileString(m_MainField,Field,
		TempValue,m_IniFilePath));
}

BOOL CProfileINI::SetValue(double Value, CString Field)
{
    CString TempValue;
	TempValue.Format(_T("%f"),Value);
	return(WritePrivateProfileString(m_MainField,Field,
		TempValue,m_IniFilePath));
}

BOOL CProfileINI::SetValue(CString TempValue, CString Field)
{
    return(WritePrivateProfileString(m_MainField,Field,
		TempValue,m_IniFilePath));
}

void CProfileINI::SetPath(CString sPath,CString MainField)
{
    m_IniFilePath=sPath;
	m_MainField=MainField;
}
