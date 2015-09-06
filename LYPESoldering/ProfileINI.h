// ProfileINI.h: interface for the CIniFilePoc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROFILEINI_H__2DCDB682_3758_4193_9B27_AA24339FAEB5__INCLUDED_)
#define AFX_PROFILEINI_H__2DCDB682_3758_4193_9B27_AA24339FAEB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProfileINI  
{
public:
	void SetPath(CString sPath,CString MainField);
	BOOL SetValue(CString TempValue,CString Field);
	BOOL SetValue(double Value,CString Field);
	BOOL SetValue(int Value,CString Field);
	CString GetString(CString Field);
	double GetDouble(CString Field);
	int GetIni(CString Field);
	CProfileINI();
	virtual ~CProfileINI();
private:
	CString m_MainField;
    CString m_IniFilePath;
};

#endif // !defined(AFX_PROFILEINI_H__2DCDB682_3758_4193_9B27_AA24339FAEB5__INCLUDED_)
