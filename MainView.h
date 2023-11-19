// MainView.h : interface of the CMainView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINVIEW_H__C97C384D_B5E2_11D6_B6C4_A04B6845B845__INCLUDED_)
#define AFX_MAINVIEW_H__C97C384D_B5E2_11D6_B6C4_A04B6845B845__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMainView : public CView
{
protected: // create from serialization only
	CMainView();
	DECLARE_DYNCREATE(CMainView)

// Attributes
public:
	CMainDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

    public:

    void PaintCursor(CDC * pDC);
    void PaintGrid(CDC * pDC);
    void PaintGraph(CDC * pDC);


// Implementation
public:
	virtual ~CMainView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMainView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnUpdatePanel(CCmdUI * pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MainView.cpp
inline CMainDoc* CMainView::GetDocument()
   { return (CMainDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINVIEW_H__C97C384D_B5E2_11D6_B6C4_A04B6845B845__INCLUDED_)
