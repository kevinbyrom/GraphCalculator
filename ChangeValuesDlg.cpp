// ChangeValuesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphCalculator.h"
#include "ChangeValuesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeValuesDlg dialog


CChangeValuesDlg::CChangeValuesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeValuesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeValuesDlg)
	m_strExpression = _T("");
	//}}AFX_DATA_INIT
}


void CChangeValuesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeValuesDlg)
	DDX_Text(pDX, IDC_EXPRESSION, m_strExpression);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeValuesDlg, CDialog)
	//{{AFX_MSG_MAP(CChangeValuesDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeValuesDlg message handlers
