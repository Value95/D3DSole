// ../Code/InspectorView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "3DEditor.h"
#include "InspectorView.h"
#include "EditorScene.h"
#include "ColliderManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CInspectorView

IMPLEMENT_DYNCREATE(CInspectorView, CFormView)

CInspectorView::CInspectorView()
	: CFormView(IDD_INSPECTORVIEW)
	, m_enable(FALSE)
	, m_name(_T(""))
	, m_positionX(0)
	, m_positionY(0)
	, m_positionZ(0)
	, m_rotationX(0)
	, m_rotationY(0)
	, m_rotationZ(0)
	, m_scaleX(0)
	, m_scaleY(0)
	, m_scaleZ(0)
	, m_offsetX(0)
	, m_offsetY(0)
	, m_offsetZ(0)
	, m_boxSizeX(0)
	, m_boxSizeY(0)
	, m_boxSizeZ(0)
	, m_radius(0)
{
}

CInspectorView::~CInspectorView()
{
}

void CInspectorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_main = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	m_hierarchyView = dynamic_cast<CHierarchyView*>(m_main->m_mainSplitter.GetPane(0, 1));

	LayerAddString();
	ObjectAddString();
	ColliderAddString();
}

void CInspectorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK2, m_enable);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_positionX);
	DDX_Text(pDX, IDC_EDIT2, m_positionY);
	DDX_Text(pDX, IDC_EDIT4, m_positionZ);
	DDX_Text(pDX, IDC_EDIT6, m_rotationX);
	DDX_Text(pDX, IDC_EDIT5, m_rotationY);
	DDX_Text(pDX, IDC_EDIT7, m_rotationZ);
	DDX_Text(pDX, IDC_EDIT9, m_scaleX);
	DDX_Text(pDX, IDC_EDIT8, m_scaleY);
	DDX_Text(pDX, IDC_EDIT10, m_scaleZ);
	DDX_Control(pDX, IDC_COMBO1, m_layerComboBox);
	DDX_Control(pDX, IDC_COMBO2, m_objectKeyComboBox);
	DDX_Text(pDX, IDC_EDIT12, m_offsetX);
	DDX_Text(pDX, IDC_EDIT11, m_offsetY);
	DDX_Text(pDX, IDC_EDIT13, m_offsetZ);
	DDX_Text(pDX, IDC_EDIT15, m_boxSizeX);
	DDX_Text(pDX, IDC_EDIT14, m_boxSizeY);
	DDX_Text(pDX, IDC_EDIT16, m_boxSizeZ);
	DDX_Text(pDX, IDC_EDIT17, m_radius);
	DDX_Control(pDX, IDC_COMBO3, m_colliderTypeComboBox);
}

void CInspectorView::SetData(Engine::CGameObject* gameObject) // 현재 선택한 오브젝트의 정보를 인스팩터에 표시해주는 함수
{
	if (gameObject == nullptr)
		return;

	UpdateData(TRUE);
	m_gameObejct = gameObject;

	m_enable = m_gameObejct->GetIsEnabled();
	m_name = m_gameObejct->GetName().c_str();
	m_positionX = m_gameObejct->GetPosition().x;
	m_positionY = m_gameObejct->GetPosition().y;
	m_positionZ = m_gameObejct->GetPosition().z;
	m_rotationX = m_gameObejct->GetRotation().x;
	m_rotationY = m_gameObejct->GetRotation().y;
	m_rotationZ = m_gameObejct->GetRotation().z;
	m_scaleX = m_gameObejct->GetScale().x;
	m_scaleY = m_gameObejct->GetScale().y;
	m_scaleZ = m_gameObejct->GetScale().z;

	CString temp;
	for (int i = 0; i < m_layerComboBox.GetCount(); i++)
	{
		m_layerComboBox.GetLBText(i, temp);
		if (temp == m_gameObejct->GetLayerKey().c_str())
		{
			m_layerComboBox.SetCurSel(i);
		}
	}
	for (int i = 0; i < m_objectKeyComboBox.GetCount(); i++)
	{
		m_objectKeyComboBox.GetLBText(i, temp);
		if (temp == m_gameObejct->GetObjectKey().c_str())
		{
			m_objectKeyComboBox.SetCurSel(i);
		}
	}

	if (m_main->m_mode == CMainFrame::Mode::NavMesh)
	{
		UpdateData(FALSE);
		return;
	}

	// 콜라이더 데이터 띄우기
	int sel = m_hierarchyView->m_objectListBox.GetCurSel();
	if (sel == -1)
	{
		UpdateData(FALSE);
		return;
	}

	ColliderData* TData = CColliderManager::GetInstance()->GetColliderData()[sel];

	for (int i = 0; i < m_colliderTypeComboBox.GetCount(); i++)
	{
		m_colliderTypeComboBox.GetLBText(i, temp);
		if (TData->colliderType.c_str() == temp)
		{
			m_colliderTypeComboBox.SetCurSel(i);
		}
	}

	m_offsetX = TData->offset.x;
	m_offsetY = TData->offset.y;
	m_offsetZ = TData->offset.z;
	m_boxSizeX = TData->boxsize.x;
	m_boxSizeY = TData->boxsize.y;
	m_boxSizeZ = TData->boxsize.z;
	m_radius = TData->radius;

	UpdateData(FALSE);
}

void CInspectorView::InputData() // 선택된 오브젝트한테 트랜스폼 정보 인풋
{
	if (m_gameObejct == nullptr)
		return;

	int sel = m_hierarchyView->m_objectListBox.GetCurSel();

	if (sel == -1 && m_main->m_mode != CMainFrame::Mode::NavMesh)
		return;

	UpdateData(TRUE);
	m_gameObejct->GetIsEnabled() = m_enable;
	m_gameObejct->GetName() = m_name;
	m_gameObejct->SetPositionX(m_positionX);
	m_gameObejct->SetPositionY(m_positionY);
	m_gameObejct->SetPositionZ(m_positionZ);
	m_gameObejct->SetRotationX(m_rotationX);
	m_gameObejct->SetRotationY(m_rotationY);
	m_gameObejct->SetRotationZ(m_rotationZ);
	m_gameObejct->SetScaleX(m_scaleX);
	m_gameObejct->SetScaleY(m_scaleY);
	m_gameObejct->SetScaleZ(m_scaleZ);

	if (m_main->m_mode == CMainFrame::Mode::NavMesh)
	{
		UpdateData(FALSE);
		return;
	}

	CString temp;
	m_objectKeyComboBox.GetLBText(m_objectKeyComboBox.GetCurSel(), temp);
	std::wstring objectkey = CStringW(temp);
	m_gameObejct->SetObjectKey(objectkey);

	m_layerComboBox.GetLBText(m_layerComboBox.GetCurSel(), temp);
	std::wstring layerKey = CStringW(temp);
	m_gameObejct->SetLayerKey(layerKey);

	UpdateData(FALSE);

	// 하이어락키 이름변경
	m_hierarchyView->m_objectListBox.DeleteString(sel); // 현재 이름 삭제
	m_hierarchyView->m_objectListBox.InsertString(sel, m_name); // 지운셀에 새로운 이름 추가
	m_hierarchyView->m_objectListBox.SetCurSel(sel); // 새로운 이름이 추가된셀로 다시 셀번호 설정

	// 하이어락키가 가지고있는 오브젝트의 위치값 변경
	m_hierarchyView->m_object[sel] = m_gameObejct;
}

void CInspectorView::LayerAddString()
{
	m_layerComboBox.AddString(TEXT("Default"));
	m_layerComboBox.AddString(TEXT("Light"));
	m_layerComboBox.AddString(TEXT("UI"));
}

void CInspectorView::ObjectAddString()
{
	m_objectKeyComboBox.AddString(TEXT("Default"));
	m_objectKeyComboBox.AddString(TEXT("Mess"));
	m_objectKeyComboBox.AddString(TEXT("UI"));
	m_objectKeyComboBox.AddString(TEXT("DirectionalLight"));
}

void CInspectorView::ColliderAddString()
{
	m_colliderTypeComboBox.AddString(TEXT("Default"));
	m_colliderTypeComboBox.AddString(TEXT("BOX"));
	m_colliderTypeComboBox.AddString(TEXT("SPHERE"));
}

void CInspectorView::InputColliderData()  // 선택된 오브젝트한테 콜라이더 정보 인풋
{
	int sel = m_hierarchyView->m_objectListBox.GetCurSel();
	if (sel == -1)
		return;

	UpdateData(TRUE);
	
	CColliderManager::GetInstance()->GetColliderData()[sel]->offset.x = m_offsetX;
	CColliderManager::GetInstance()->GetColliderData()[sel]->offset.y = m_offsetY;
	CColliderManager::GetInstance()->GetColliderData()[sel]->offset.z = m_offsetZ;
	CColliderManager::GetInstance()->GetColliderData()[sel]->boxsize.x = m_boxSizeX;
	CColliderManager::GetInstance()->GetColliderData()[sel]->boxsize.y = m_boxSizeY;
	CColliderManager::GetInstance()->GetColliderData()[sel]->boxsize.z = m_boxSizeZ;
	CColliderManager::GetInstance()->GetColliderData()[sel]->radius = m_radius;

	CString temp;
	m_colliderTypeComboBox.GetLBText(m_colliderTypeComboBox.GetCurSel(), temp);
	CColliderManager::GetInstance()->GetColliderData()[sel]->colliderType = CStringW(temp);

	UpdateData(FALSE);

}

void CInspectorView::DeleteObject() // 선택된 오브젝트 삭제
{
	if (m_gameObejct == nullptr)
		return;

	int sel = m_hierarchyView->m_objectListBox.GetCurSel();
	if (sel == -1 && m_main->m_mode != CMainFrame::Mode::NavMesh)
		return;

	SHARED(Engine::CGameObject) object = Engine::GET_CUR_SCENE->FindObjectPosition(m_gameObejct->GetPosition());
	object->SetIsNeedToBeDeleted(true);

	m_gameObejct = nullptr;
	dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE.get())->SetPickingObject(nullptr);

	if (m_main->m_mode == CMainFrame::Mode::NavMesh)
	{
		CNavMeshManager::GetInstance()->ObjectDelete(object);
		return;
	}

	
	m_hierarchyView->m_object.erase(m_hierarchyView->m_object.begin() + sel);
	m_hierarchyView->m_objectListBox.DeleteString(sel);

	CColliderManager::GetInstance()->DataDelete(sel);

}

BEGIN_MESSAGE_MAP(CInspectorView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CInspectorView::InputData)
	ON_BN_CLICKED(IDC_BUTTON4, &CInspectorView::DeleteObject)
	ON_BN_CLICKED(IDC_BUTTON15, &CInspectorView::InputColliderData)
END_MESSAGE_MAP()


// CInspectorView 진단입니다.

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


// CInspectorView 메시지 처리기입니다.
