// ../Code/HierarchyView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "3DEditor.h"
#include "HierarchyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHierarchyView

IMPLEMENT_DYNCREATE(CHierarchyView, CFormView)

CHierarchyView::CHierarchyView()
	: CFormView(IDD_HIERARCHYVIEW)
{

}

CHierarchyView::~CHierarchyView()
{
}

void CHierarchyView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHierarchyView, CFormView)
END_MESSAGE_MAP()


// CHierarchyView �����Դϴ�.

#ifdef _DEBUG
void CHierarchyView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CHierarchyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHierarchyView �޽��� ó�����Դϴ�.
