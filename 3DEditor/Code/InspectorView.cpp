// ../Code/InspectorView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "3DEditor.h"
#include "InspectorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CInspectorView

IMPLEMENT_DYNCREATE(CInspectorView, CFormView)

CInspectorView::CInspectorView()
	: CFormView(IDD_INSPECTORVIEW)
{

}

CInspectorView::~CInspectorView()
{
}

void CInspectorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CInspectorView, CFormView)
	//ON_EN_CHANGE(IDC_EDIT1, &CInspectorView::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CInspectorView �����Դϴ�.

#ifdef _DEBUG
void CInspectorView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInspectorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInspectorView �޽��� ó�����Դϴ�.
