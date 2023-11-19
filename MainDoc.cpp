// MainDoc.cpp : implementation of the CMainDoc class
//

#include "stdafx.h"
#include <math.h>
#include "GraphCalculator.h"
#include "ChangeValuesDlg.h"
#include "MainDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ROUND(x)					((x < 0) ? (int)(x + .5) : -(int)(.5 - x))


IMPLEMENT_DYNCREATE(CMainDoc, CDocument)

BEGIN_MESSAGE_MAP(CMainDoc, CDocument)
	//{{AFX_MSG_MAP(CMainDoc)
	ON_COMMAND(ID_CHANGEVALUES, OnChangeValues)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




CMainDoc::CMainDoc()
    {
    m_BackColor     = RGB(0,0,0);
    m_GridColor     = RGB(50,128,255);
    m_GraphColor    = RGB(255,0,0);
    m_CursorColor   = RGB(0,0,128);
    }


CMainDoc::~CMainDoc()
    {
    }




BOOL CMainDoc::OnNewDocument()
    {
	if (!CDocument::OnNewDocument())
		return FALSE;

    m_XOrigin = 0.0f;
    m_YOrigin = 0.0f;
    m_Scale   = 1.0f;

	return TRUE;
    }



void CMainDoc::MouseRButton(CPoint point)
    {
    //m_XOrigin = ScreenToX(point.x);
    //m_YOrigin = XToY(m_XOrigin);

    UpdateAllViews(NULL);
    }
    

void CMainDoc::MouseMove(CPoint point, BOOL shift)
    {
/*    CPoint delta;

    if (shift)
        {
        delta = point - m_LastMousePoint;
        
        m_XOrigin += PixelToX() * delta.x;
        m_YOrigin = XToY(m_XOrigin);
            
        UpdateAllViews(NULL);
        }

    m_LastMousePoint = point;*/
    }



BOOL CMainDoc::XToY(float x, float * yval, BOOL * yvalgood)
    {
    return(m_ETree.FindSolution(x, yval, yvalgood));
    }




float CMainDoc::ScreenToX(int xval)
    {
    float lowx;
    float highx;
    float range;

    lowx    = m_XOrigin - (m_ViewHalfWidth * m_Scale);
    highx   = m_XOrigin + (m_ViewHalfWidth * m_Scale);
    range   = highx - lowx;

    return lowx + (range * ((float)xval / m_ViewWidth));
    }



float CMainDoc::ScreenToY(int yval)
    {
    float lowy;
    float highy;
    float range;

    lowy    = m_YOrigin - (m_ViewHalfHeight * m_Scale);
    highy   = m_YOrigin + (m_ViewHalfHeight * m_Scale);
    range   = highy - lowy;

    return lowy + (range * ((float)yval / m_ViewHeight));
    }



int CMainDoc::XToScreen(float xval)
    {
    float lowx;
    float highx;
    float range;

    lowx    = m_XOrigin - (m_ViewHalfWidth * m_Scale);
    highx   = m_XOrigin + (m_ViewHalfWidth * m_Scale);
    range   = highx - lowx;

    return ROUND(((xval - lowx) / range) * m_ViewWidth);
    }




int CMainDoc::YToScreen(float yval)
    {
    float lowy;
    float highy;
    float range;

    lowy    = m_YOrigin - (m_ViewHalfHeight * m_Scale);
    highy   = m_YOrigin + (m_ViewHalfHeight * m_Scale);
    range   = highy - lowy;

    return m_ViewHeight - 1 - ROUND(((yval - lowy) / range) * m_ViewHeight);
    }




float CMainDoc::PixelToX()
    {
    float range;

    range   = m_ViewWidth * m_Scale;

    return (range * (1.0f / m_ViewWidth));
    }





float CMainDoc::PixelToY()
    {
    float range;

    range   = m_ViewHeight * m_Scale;

    return (range * (1.0f / m_ViewHeight));
    }



void CMainDoc::OnChangeValues() 
    {
    CChangeValuesDlg dlg;
    
    
    dlg.m_strExpression = m_ETree.GetExpressionString();

    if (dlg.DoModal() == IDOK)
        {
        m_ETree.BuildExpression(dlg.m_strExpression);
        }
  

    UpdateAllViews(NULL);
    }




void CMainDoc::Serialize(CArchive& ar)
    {
	if (ar.IsStoring())
	    {	
    	}
	else
	    {
	    }
    }


#ifdef _DEBUG
void CMainDoc::AssertValid() const
    {
	CDocument::AssertValid();
    }

void CMainDoc::Dump(CDumpContext& dc) const
    {
	CDocument::Dump(dc);
    }
#endif //_DEBUG