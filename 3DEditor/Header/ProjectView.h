#pragma once
#include "afxwin.h"

class CProjectView : public CFormView
{
	DECLARE_DYNCREATE(CProjectView)
public:
	CListBox m_messList;
	CListBox m_textureList;
	CListBox m_prefabList;

	bool init;
protected:
	CProjectView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CProjectView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECTVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void MessListClick();
	afx_msg void TextureListClick();
	afx_msg void PrefabListClick();
};


