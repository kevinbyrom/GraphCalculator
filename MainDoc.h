// MainDoc.h : interface of the CMainDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINDOC_H__C97C384B_B5E2_11D6_B6C4_A04B6845B845__INCLUDED_)
#define AFX_MAINDOC_H__C97C384B_B5E2_11D6_B6C4_A04B6845B845__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "ExpressionTree.h"


class CMainDoc : public CDocument
    {
    protected: 
	    CMainDoc();
	    DECLARE_DYNCREATE(CMainDoc)


    public:

        virtual ~CMainDoc();
    
    #ifdef _DEBUG
	    virtual void AssertValid() const;
	    virtual void Dump(CDumpContext& dc) const;
    #endif


    public:

        void MoveLeft()     { m_XOrigin -= PixelToX(); UpdateAllViews(NULL); }
        void MoveRight()    { m_XOrigin += PixelToX(); UpdateAllViews(NULL); }
        void MoveUp()       { m_YOrigin += PixelToY(); UpdateAllViews(NULL); }
        void MoveDown()     { m_YOrigin -= PixelToY(); UpdateAllViews(NULL); }

        void MouseRButton(CPoint point);
        void MouseMove(CPoint point, BOOL Shift);

        void ScaleIn()      { m_Scale *= 2; UpdateAllViews(NULL); }
        void ScaleOut()     { m_Scale /= 2; UpdateAllViews(NULL); }

        BOOL XToY(float x, float * yval, BOOL * yvalgood);

        void SetViewSize(int width, int height) { m_ViewWidth = width; m_ViewHeight = height; m_ViewHalfWidth = width / 2; m_ViewHalfHeight = height / 2; }

        float ScreenToX(int xval);
        float ScreenToY(int yval);
        int XToScreen(float xval);
        int YToScreen(float yval);
        float PixelToX();            
        float PixelToY();

        CExpressionTree m_ETree;

        float m_XOrigin;
        float m_YOrigin;

        int   m_ViewWidth;
        int   m_ViewHeight;
        int   m_ViewHalfWidth;
        int   m_ViewHalfHeight;

        float m_Scale;

        BOOL m_LockedToMouse;
        CPoint m_LastMousePoint;

        COLORREF m_BackColor;
        COLORREF m_GridColor;
        COLORREF m_GraphColor;
        COLORREF m_CursorColor;


    public:

        // Overrides
	    // ClassWizard generated virtual function overrides
	    //{{AFX_VIRTUAL(CMainDoc)
	    public:
	    virtual BOOL OnNewDocument();
	    virtual void Serialize(CArchive& ar);
	    //}}AFX_VIRTUAL


    protected:
	    //{{AFX_MSG(CMainDoc)
	    afx_msg void OnChangeValues();
	    //}}AFX_MSG
	    DECLARE_MESSAGE_MAP()
    };



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDOC_H__C97C384B_B5E2_11D6_B6C4_A04B6845B845__INCLUDED_)

