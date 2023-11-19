// MainView.cpp : implementation of the CMainView class
//

#include "stdafx.h"
#include "GraphCalculator.h"

#include "MainDoc.h"
#include "MainView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ROUND(x)					((x < 0) ? (int)(x + .5) : -(int)(.5 - x))


/////////////////////////////////////////////////////////////////////////////
// CMainView

IMPLEMENT_DYNCREATE(CMainView, CView)

BEGIN_MESSAGE_MAP(CMainView, CView)
	//{{AFX_MSG_MAP(CMainView)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_STATUS, OnUpdatePanel)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainView construction/destruction

CMainView::CMainView()
{
	// TODO: add construction code here

}

CMainView::~CMainView()
{
}

BOOL CMainView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainView drawing

void CMainView::OnDraw(CDC* pDC)
{
	CMainDoc* pDoc = GetDocument();
    CBrush brush(pDoc->m_BackColor);
    CDC MemDC;
    CBitmap MemBmp;
    CBitmap * pOldBitmap;
    CRect rect;

    ASSERT_VALID(pDoc);
	
    GetClientRect(&rect);

	MemDC.CreateCompatibleDC(pDC);
	MemBmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pOldBitmap = (CBitmap *)MemDC.SelectObject(&MemBmp);

    MemDC.FillRect(&rect, &brush);

    PaintCursor(&MemDC);
    PaintGrid(&MemDC);
    PaintGraph(&MemDC);

    pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);

    MemDC.SelectObject(pOldBitmap);
}



void CMainView::PaintCursor(CDC * pDC)
    {
    CMainDoc* pDoc = GetDocument();
    CPen pen(PS_SOLID, 1, pDoc->m_CursorColor);
    CPen * pOldPen;
    CRect rect;
    int plotx, ploty;

    GetClientRect(&rect);

    plotx = ROUND((float)rect.Width() / 2);
    ploty = ROUND((float)rect.Height() / 2);

    pOldPen = (CPen *)pDC->SelectObject(&pen);
    
    pDC->MoveTo(plotx, 0);
    pDC->LineTo(plotx, rect.Height());

    pDC->MoveTo(0, ploty);
    pDC->LineTo(rect.Width(), ploty);

    pDC->SelectObject(pOldPen);
    }



void CMainView::PaintGrid(CDC * pDC)
    {
    CMainDoc* pDoc = GetDocument();
    CPen pen(PS_SOLID, 1, pDoc->m_GridColor);
    CPen * pOldPen;
    CRect rect;
    int plotx, ploty;

    GetClientRect(&rect);

    plotx = pDoc->XToScreen(0.0f);
    ploty = pDoc->YToScreen(0.0f);

    pOldPen = (CPen *)pDC->SelectObject(&pen);
    
    pDC->MoveTo(plotx, 0);
    pDC->LineTo(plotx, rect.Height());

    pDC->MoveTo(0, ploty);
    pDC->LineTo(rect.Width(), ploty);

    pDC->SelectObject(pOldPen);
    }



void CMainView::PaintGraph(CDC * pDC)
    {
    CMainDoc* pDoc = GetDocument();
    CPen pen(PS_SOLID, 1, pDoc->m_GraphColor);
    CPen * pOldPen;
    CRect rect;
    float xval, yval[2];
    BOOL yvalgood[2], lastwasgood[2];
    int plotx, ploty, lastplotx[2], lastploty[2];


    if (!pDoc->m_ETree.HasExpression())
        return;


    // Get the client dimensions

    GetClientRect(&rect);


    // Select the graph pen

    pOldPen = (CPen *)pDC->SelectObject(&pen);

    
    lastwasgood[0]  = FALSE;
    lastwasgood[1]  = FALSE;


    for (plotx = -1; plotx < rect.Width(); plotx++)
        {
        xval = pDoc->ScreenToX(plotx);
        pDoc->XToY(xval, yval, yvalgood);

        for (int i = 0; i < 2; i++)
            {
            if (yvalgood[i])
                {
                ploty = pDoc->YToScreen(yval[i]);

                pDC->MoveTo(lastplotx[i], lastploty[i]);

                if (lastwasgood[i])
                    {
                    pDC->LineTo(plotx, ploty);
                    }
                else
                    {
                    pDC->MoveTo(plotx, ploty);
                    pDC->LineTo(plotx, ploty);
                    }

                lastplotx[i] = plotx;
                lastploty[i] = ploty;

                lastwasgood[i] = TRUE;
                }
            //else
              //  lastwasgood[i] = FALSE;
            }
        }

    pDC->SelectObject(pOldPen);
    }



/////////////////////////////////////////////////////////////////////////////
// CMainView printing

BOOL CMainView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMainView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMainView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMainView diagnostics

#ifdef _DEBUG
void CMainView::AssertValid() const
{
	CView::AssertValid();
}

void CMainView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMainDoc* CMainView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainDoc)));
	return (CMainDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainView message handlers

BOOL CMainView::OnEraseBkgnd(CDC* pDC) 
    {
    return TRUE;
    }



void CMainView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
    {
    CMainDoc* pDoc = GetDocument();
    CRect rect;

    GetClientRect(&rect);

    switch(nChar)
        {
        case VK_LEFT:
            pDoc->MoveLeft();
            break;

        case VK_RIGHT:
            pDoc->MoveRight();
            break;

        case VK_UP:
            pDoc->MoveUp();
            break;

        case VK_DOWN:
            pDoc->MoveDown();
            break;

        case VK_DELETE:
            pDoc->ScaleOut();
            break;

        case VK_END:
            pDoc->ScaleIn();
            break;

        default:
            break;
        }
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
    }




void CMainView::OnUpdatePanel(CCmdUI * pCmdUI)
    {
    CMainDoc* pDoc = GetDocument();
    char strText[256];

    sprintf(strText, "y = %s   Origin (%.2f, %.2f)   Scale (%.2f)", (LPCTSTR)pDoc->m_ETree.GetExpressionString(), pDoc->m_XOrigin, pDoc->m_YOrigin, pDoc->m_Scale);

    pCmdUI->Enable();
    pCmdUI->SetText(strText);
    }



void CMainView::OnMouseMove(UINT nFlags, CPoint point) 
    {
	CMainDoc* pDoc = GetDocument();
    CRect rect;

    GetClientRect(&rect);

    pDoc->MouseMove(point, nFlags & MK_SHIFT);

	CView::OnMouseMove(nFlags, point);
    }

void CMainView::OnRButtonDown(UINT nFlags, CPoint point) 
    {
	CMainDoc* pDoc = GetDocument();
    CRect rect;

    GetClientRect(&rect);

    pDoc->MouseRButton(point);

	CView::OnRButtonDown(nFlags, point);
    }


BOOL CMainView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
    {
	CMainDoc* pDoc = GetDocument();


	if (zDelta)
        pDoc->ScaleIn();
    else
        pDoc->ScaleOut();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
    }

void CMainView::OnSize(UINT nType, int cx, int cy) 
    {
    CMainDoc* pDoc = GetDocument();


    CView::OnSize(nType, cx, cy);
	
	pDoc->SetViewSize(cx, cy);	
    }
