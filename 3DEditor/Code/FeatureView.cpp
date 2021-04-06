#include "stdafx.h"
#include "3DEditor.h"
#include "FeatureView.h"
#include "EditorScene.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CFeatureView, CFormView)

CFeatureView::CFeatureView()
	: CFormView(IDD_FEATUREVIEW)
{

}

CFeatureView::~CFeatureView()
{
}

void CFeatureView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_main = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	hierarchyView = dynamic_cast<CProjectView*>(m_main->m_leftSplitter.GetPane(1, 0));
}

void CFeatureView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

void CFeatureView::NavMeshMode()
{
	dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE.get())->SetPickingObject(nullptr);

	if (m_main->m_mode == CMainFrame::Mode::NavMesh)
	{
		m_main->m_mode = CMainFrame::Mode::Normal;
	}
	else
	{
		m_main->m_mode = CMainFrame::Mode::NavMesh;
	}

}

// ������ ����
void CFeatureView::PrefabCreate()
{
	if (m_main->m_mode == CMainFrame::Mode::NavMesh)
		return;

	Engine::CGameObject* Tobject;
	ColliderData* Tcollider;

	Tobject = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE.get())->GetPickingObject();
	Tcollider = CColliderManager::GetInstance()->GetColliderData()[dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE.get())->m_pickNumber];

	if (Tobject == nullptr)
		return;

	CPrefabManager::GetInstance()->DataInit(Tobject->GetIsEnabled(), Tobject->GetName(), Tobject->GetLayerKey(), Tobject->GetObjectKey(), Tobject->GetComponent<Engine::CMeshComponent>()->GetMeshKey(),
		Tobject->GetComponent<Engine::CTextureComponent>()->GetTextureKey(), Tobject->GetRotation(), Tobject->GetScale(), Tcollider);

	hierarchyView->m_prefabList.AddString(Tobject->GetName().c_str());
}

// ������ ����
void CFeatureView::PrefabDelete() 
{
	if (m_main->m_mode == CMainFrame::Mode::NavMesh)
		return;

	int sel = hierarchyView->m_prefabList.GetCurSel();

	if (sel == -1)
		return;

	hierarchyView->m_prefabList.DeleteString(sel);
	CPrefabManager::GetInstance()->DataDelete(sel);
}

void CFeatureView::Save()
{
	// ��� ������Ʈ, ������, �׺�Ž�

	// ������Ʈ
	/*
	�̸�, ���̾�, ������ƮŰ, Ȱ��ȭ/��Ȱ��ȭ, ��ġ, ȸ��, ũ��, �ݶ��̴� Ÿ��
	*/

	// ������
	/*
	�̸�, ���̾�, ������ƮŰ, Ȱ��ȭ/��Ȱ��ȭ, �ݶ��̴� Ÿ��
	*/

	// �׺�Ž�
	/*
	������Ʈ ��ġ, Ʈ���̾ޱ� ��ġ����
	*/
	
	CFileDialog Dlg(FALSE,// ����(FALSE)�� ������ �ҷ�(TRUE)�� ������
		L"dat",
		L"*.dat",
		OFN_OVERWRITEPROMPT,
		L"Data File(*.dat) | *.dat||",
		this);

	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;
	if (Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			//MSG_BOX(__FILE__, L"Save File Failed");

			return;
		}

		std::unordered_map<std::wstring, SHARED(Engine::CLayer)> layers = Engine::CSceneManager::GetInstance()->GetCurScene()->GetLayers();
		DWORD dwByte = 0;

		for (auto& layer : layers)
		{
			for (auto& gameObject : layer.second->GetGameObjects())
			{
				if (gameObject->GetLayerKey() == L"Camera")
					continue;

				/*WriteFile(hFile, &gameObject->GetName(), sizeof(std::wstring), &dwByte, nullptr); // �̸�
				WriteFile(hFile, &gameObject->GetLayerKey(), sizeof(std::wstring), &dwByte, nullptr); // ���̾�
				WriteFile(hFile, &gameObject->GetObjectKey(), sizeof(std::wstring), &dwByte, nullptr); // ������Ʈ
				WriteFile(hFile, &gameObject->GetComponent<Engine::CTextureComponent>()->GetTextureKey(), sizeof(std::wstring), &dwByte, nullptr); // �ؽ���
				WriteFile(hFile, &gameObject->GetComponent<Engine::CMeshComponent>()->GetMeshKey(), sizeof(std::wstring), &dwByte, nullptr); // �޽�*/

				WriteFile(hFile, &gameObject->GetIsEnabled(), sizeof(bool), &dwByte, nullptr); // Ȱ��ȭ/��Ȱ��ȭ
				WriteFile(hFile, &gameObject->GetPosition(), sizeof(vector3), &dwByte, nullptr); // ��ġ
				WriteFile(hFile, &gameObject->GetRotation(), sizeof(vector3), &dwByte, nullptr); // ȸ��
				WriteFile(hFile, &gameObject->GetScale(), sizeof(vector3), &dwByte, nullptr); // ũ��
			}
		}

		CloseHandle(hFile);
	}

}

void CFeatureView::Load()
{
	CFileDialog Dlg(TRUE,// ����(FALSE)�� ������ �ҷ�(TRUE)�� ������
		L"dat",
		L"*.dat",
		OFN_OVERWRITEPROMPT,
		L"Data File(*.dat) | *.dat||",
		this);

	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (Dlg.DoModal())
	{
		std::unordered_map<std::wstring, SHARED(Engine::CLayer)> layer = Engine::CSceneManager::GetInstance()->GetCurScene()->GetLayers();

		CString wstrFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			return;
		}
		DWORD dwByte = 0;
		std::wstring stringValue;

		CHierarchyView* hierarchyView = dynamic_cast<CHierarchyView*>(dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd())->m_mainSplitter.GetPane(0, 1));
		hierarchyView->m_objectListBox.ResetContent();
		hierarchyView->m_objectPos.clear();

		Engine::CSceneManager::GetInstance()->GetCurScene()->AllDelete();

		while (true)
		{
			SHARED(Engine::CGameObject) obj = Engine::ADD_CLONE(L"Default", L"Default", true);

			/*ReadFile(hFile, &stringValue, sizeof(std::wstring), &dwByte, nullptr);
			obj->SetName(stringValue);

			ReadFile(hFile, &stringValue, sizeof(std::wstring), &dwByte, nullptr);
			obj->SetLayerKey(stringValue);

			ReadFile(hFile, &stringValue, sizeof(std::wstring), &dwByte, nullptr);
			obj->SetObjectKey(stringValue);

			ReadFile(hFile, &stringValue, sizeof(std::wstring), &dwByte, nullptr);
			obj->GetComponent<Engine::CTextureComponent>()->SetTextureKey(stringValue);

			ReadFile(hFile, &stringValue, sizeof(std::wstring), &dwByte, nullptr);
			obj->GetComponent<Engine::CMeshComponent>()->SetMeshKey(stringValue);*/

			ReadFile(hFile, &obj->GetIsEnabled(), sizeof(bool), &dwByte, nullptr);
			ReadFile(hFile, &obj->GetPosition(), sizeof(vector3), &dwByte, nullptr);
			ReadFile(hFile, &obj->GetRotation(), sizeof(vector3), &dwByte, nullptr);
			ReadFile(hFile, &obj->GetScale(), sizeof(vector3), &dwByte, nullptr);

			if (0 == dwByte)
			{
				obj->SetIsNeedToBeDeleted(true);
				break;
			}

			hierarchyView->m_objectListBox.AddString(obj.get()->GetName().c_str());
			hierarchyView->m_objectPos.emplace_back(obj.get()->GetPosition());
		}

		CloseHandle(hFile);
	}
}

BEGIN_MESSAGE_MAP(CFeatureView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON6, &CFeatureView::PrefabCreate)
	ON_BN_CLICKED(IDC_BUTTON1, &CFeatureView::Save)
	ON_BN_CLICKED(IDC_BUTTON2, &CFeatureView::Load)
	ON_BN_CLICKED(IDC_BUTTON11, &CFeatureView::PrefabDelete)
	ON_BN_CLICKED(IDC_BUTTON3, &CFeatureView::NavMeshMode)
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

