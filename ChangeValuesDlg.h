#if !defined(AFX_CHANGEVALUESDLG_H__C97C3857_B5E2_11D6_B6C4_A04B6845B845__INCLUDED_)
#define AFX_CHANGEVALUESDLG_H__C97C3857_B5E2_11D6_B6C4_A04B6845B845__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeValuesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangeValuesDlg dialog

class CChangeValuesDlg : public CDialog
{
// Construction
public:
	CChangeValuesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChangeValuesDlg)
	enum { IDD = IDD_CHANGEVALUES };
	CString	m_strExpression;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeValuesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangeValuesDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEVALUESDLG_H__C97C3857_B5E2_11D6_B6C4_A04B6845B845__INCLUDED_)
