#pragma once
#include "afxwin.h"



// CHierarchyView �� ���Դϴ�.

class CHierarchyView : public CFormView
{
	DECLARE_DYNCREATE(CHierarchyView)
public:
	CListBox m_objectListBox;
	std::vector<Engine::CGameObject*> m_object;
protected:
	CHierarchyView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CHierarchyView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HIERARCHYVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void SelectObjectClick();
};


