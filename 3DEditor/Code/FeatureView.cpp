// ../Code/FeatureView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "3DEditor.h"
#include "FeatureView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFeatureView

IMPLEMENT_DYNCREATE(CFeatureView, CFormView)

CFeatureView::CFeatureView()
	: CFormView(IDD_FEATUREVIEW)
{

}

CFeatureView::~CFeatureView()
{
}

void CFeatureView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFeatureView, CFormView)
END_MESSAGE_MAP()


// CFeatureView �����Դϴ�.

#ifdef _DEBUG
void CFeatureView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFeatureView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFeatureView �޽��� ó�����Դϴ�.
