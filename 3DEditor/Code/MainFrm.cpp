
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "3DEditor.h"

#include "MainFrm.h"
#include "3DEditorView.h"
#include "ProjectView.h"
#include "HierarchyView.h"
#include "InspectorView.h"
#include "FeatureView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyleEx(0, WS_EX_APPWINDOW);
	ModifyStyle(WS_CAPTION | WS_THICKFRAME, WS_POPUP);
	SetWindowPos(0, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);

	//::SetWindowPos(this->m_hWnd, HWND_NOTOPMOST, 0, 0, cx, cy, SWP_FRAMECHANGED);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{

	/*
	//  -------------------------
	//  |  left | main  | right |
	//	|	0,0	|		|		|
	//	|		|		|	0,0 |
	//	|-------|	0,1	|--------
	//	|	1,0	|		|	1,0 |
	//	|		|		|		|
	//  -------------------------
	 */
	
	_uint winCX = WINDOWCX;
	_uint winCY = WINDOWCY;
	
	_uint firstCX = winCX * 0.55f;
	_uint hierarchCX = 280;
	
	_uint valCY_0 = winCY * 0.6f;
	_uint valCY_1 = winCY * 0.4f;

	// 툴을 세로로 3등분 나눔
	m_mainSplitter.CreateStatic(this, 1, 3);

	// left
	m_leftSplitter.CreateStatic(&m_mainSplitter, 2, 1, WS_VISIBLE | WS_CHILD, m_mainSplitter.IdFromRowCol(0, 0));
	m_leftSplitter.CreateView(0, 0, RUNTIME_CLASS(CMy3DEditorView), CSize(firstCX, valCY_0), pContext); // Scene View
	m_leftSplitter.CreateView(1, 0, RUNTIME_CLASS(CProjectView), CSize(firstCX, valCY_1), pContext); // Mesh, texture, scene info View
	m_mainSplitter.SetColumnInfo(0, firstCX, 10);

	// center
	m_mainSplitter.CreateView(0, 1, RUNTIME_CLASS(CHierarchyView), CSize(hierarchCX, winCY), pContext); // object list View
	m_mainSplitter.SetColumnInfo(1, hierarchCX, 10);

	// right
	m_rightSplitter.CreateStatic(&m_mainSplitter, 2, 1, WS_VISIBLE | WS_CHILD, m_mainSplitter.IdFromRowCol(0, 2));
	m_rightSplitter.CreateView(0, 0, RUNTIME_CLASS(CInspectorView), CSize(100, valCY_0), pContext); // transform, collision View
	m_rightSplitter.CreateView(1, 0, RUNTIME_CLASS(CFeatureView), CSize(100, valCY_1), pContext); // other View
	m_mainSplitter.SetColumnInfo(2, 100, 10);

	return TRUE;
}
