// ../Code/HierarchyView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "3DEditor.h"
#include "HierarchyView.h"
#include "EditorScene.h"
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

void CHierarchyView::SelectObjectClick() // ���� �´� ������Ʈ ��ġ���� �������� �ش� ��ġ���� ���� ������Ʈ��ã�´�.
{
	int sel = m_objectListBox.GetCurSel();
	if (sel == -1)
		return;

	SHARED(Engine::CGameObject) object = Engine::GET_CUR_SCENE->FindObjectPoint(m_object[sel]);

	if (object == nullptr)
		return;

	CInspectorView* inspectorView = dynamic_cast<CInspectorView*>(dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd())->m_rightSplitter.GetPane(0, 0));
	inspectorView->SetData(object.get());

	Engine::GET_MAIN_CAM->GetOwner()->SetPosition(object->GetPosition());
	Engine::GET_MAIN_CAM->GetOwner()->SetPosition(Engine::GET_MAIN_CAM->GetOwner()->ReturnPosTranslate(vector3(0, 0, -8)));

	dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE.get())->m_pickingObject = object.get();
	dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE.get())->m_pickNumber = sel;
}

BEGIN_MESSAGE_MAP(CHierarchyView, CFormView)
	ON_LBN_SELCHANGE(IDC_LIST1, &CHierarchyView::SelectObjectClick)
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
