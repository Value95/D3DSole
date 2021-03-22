
// 3DEditorView.h : CMy3DEditorView Ŭ������ �������̽�
//

#pragma once

#include "3DEditorDoc.h"
#include "MainEditor.h"

class CMy3DEditorView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy3DEditorView();
	DECLARE_DYNCREATE(CMy3DEditorView)

// Ư���Դϴ�.
public:
	CMy3DEditorDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
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

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // 3DEditorView.cpp�� ����� ����
inline CMy3DEditorDoc* CMy3DEditorView::GetDocument() const
   { return reinterpret_cast<CMy3DEditorDoc*>(m_pDocument); }
#endif

