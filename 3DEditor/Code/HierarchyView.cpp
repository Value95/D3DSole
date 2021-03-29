// ../Code/HierarchyView.cpp : 구현 파일입니다.
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
	DDX_Control(pDX, IDC_LIST1, m_objectListBox);
}

void CHierarchyView::SelectObjectClick()
{
	// 셀에 맞는 오브젝트 위치값을 가져오고 해당 위치값과 같은 오브젝트를찾는다.
	if (m_objectListBox.GetCurSel() == -1)
		return;

	SHARED(Engine::CGameObject) object = Engine::GET_CUR_SCENE->FindObjectPosition(m_objectPos[m_objectListBox.GetCurSel()]);

	CInspectorView* inspectorView = dynamic_cast<CInspectorView*>(dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd())->m_rightSplitter.GetPane(0, 0));
	inspectorView->SetData(object.get());

	Engine::GET_MAIN_CAM->GetOwner()->SetPosition(object->GetPosition());
	Engine::GET_MAIN_CAM->GetOwner()->SetPosition(Engine::GET_MAIN_CAM->GetOwner()->ReturnTranslate(vector3(0, 0, -8)));
}

BEGIN_MESSAGE_MAP(CHierarchyView, CFormView)
	ON_LBN_SELCHANGE(IDC_LIST1, &CHierarchyView::SelectObjectClick)
END_MESSAGE_MAP()


// CHierarchyView 진단입니다.

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



// CHierarchyView 메시지 처리기입니다.
