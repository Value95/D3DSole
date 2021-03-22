
// 3DEditorView.h : CMy3DEditorView 클래스의 인터페이스
//

#pragma once

#include "3DEditorDoc.h"
#include "MainEditor.h"

class CMy3DEditorView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy3DEditorView();
	DECLARE_DYNCREATE(CMy3DEditorView)

// 특성입니다.
public:
	CMy3DEditorDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMy3DEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	void Engine_Awake();
	void Engine_Start();

protected:
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	SHARED(CMainEditor) m_pMainEditor = nullptr;

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // 3DEditorView.cpp의 디버그 버전
inline CMy3DEditorDoc* CMy3DEditorView::GetDocument() const
   { return reinterpret_cast<CMy3DEditorDoc*>(m_pDocument); }
#endif

