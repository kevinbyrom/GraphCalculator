// GraphCalculator.h : main header file for the GRAPHCALCULATOR application
//

#if !defined(AFX_GRAPHCALCULATOR_H__C97C3845_B5E2_11D6_B6C4_A04B6845B845__INCLUDED_)
#define AFX_GRAPHCALCULATOR_H__C97C3845_B5E2_11D6_B6C4_A04B6845B845__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMainApp:
// See GraphCalculator.cpp for the implementation of this class
//

class CMainApp : public CWinApp
{
public:
	CMainApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMainApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHCALCULATOR_H__C97C3845_B5E2_11D6_B6C4_A04B6845B845__INCLUDED_)
