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
	m_projectView = dynamic_cast<CProjectView*>(m_main->m_leftSplitter.GetPane(1, 0));
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

void CFeatureView::UIMode()
{
	dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE.get())->SetPickingObject(nullptr);

	if (m_main->m_mode == CMainFrame::Mode::UI)
	{
		m_main->m_mode = CMainFrame::Mode::Normal;
	}
	else
	{
		m_main->m_mode = CMainFrame::Mode::UI;
	}
}

void CFeatureView::SaveWstring(HANDLE* file, DWORD* dwByte, std::wstring str)
{
	CString text = str.c_str();
	DWORD dwStringSize = sizeof(wchar_t) * (text.GetLength() + 1);
	WriteFile(*file, &dwStringSize, sizeof(DWORD), dwByte, nullptr); // 이름
	WriteFile(*file, text.GetString(), dwStringSize, dwByte, nullptr);

}

std::wstring CFeatureView::LoadWstring(HANDLE * file, DWORD * dwByte)
{
	DWORD dwStringSize = 0;

	ReadFile(*file, &dwStringSize, sizeof(DWORD), dwByte, nullptr); // 이름
	TCHAR* strName = new TCHAR[dwStringSize];
	ReadFile(*file, strName, dwStringSize, dwByte, nullptr);
	wstring returnstring = strName;
	delete[](strName);
	strName = nullptr;
	return returnstring;
}

void CFeatureView::ReSetProject()
{
	m_hierarchyView = dynamic_cast<CHierarchyView*>(dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd())->m_mainSplitter.GetPane(0, 1));
	m_hierarchyView->m_objectListBox.ResetContent();
	m_hierarchyView->m_objectPos.clear();

	Engine::CSceneManager::GetInstance()->GetCurScene()->AllDelete();
	dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE.get())->SetPickingObject(nullptr);

	SHARED(Engine::CGameObject) m_box;
	SHARED(Engine::CGameObject) m_sphere;

	m_box = Engine::CObjectFactory::GetInstance()->AddClone(L"Collider", L"Collider", true);
	m_box->SetScale(vector3One);
	m_box->AddComponent<Engine::CBoxComponent>();
	dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE.get())->m_box = m_box;

	m_sphere = Engine::CObjectFactory::GetInstance()->AddClone(L"Collider", L"Collider", true);
	m_sphere->SetScale(vector3Zero);
	m_sphere->AddComponent<Engine::CSphereComponent>();
	dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE.get())->m_sphere = m_sphere;
}

// 프리팹 생성
void CFeatureView::PrefabCreate()
{
	if (m_main->m_mode == CMainFrame::Mode::NavMesh)
		return;

	int sel = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE.get())->m_pickNumber;
	if (sel == -1)
		return;


	Engine::CGameObject* Tobject;
	ColliderData* Tcollider;

	Tobject = dynamic_cast<CEditorScene*>(Engine::GET_CUR_SCENE.get())->GetPickingObject();
	Tcollider = CColliderManager::GetInstance()->GetColliderData()[sel];

	if (Tobject == nullptr)
		return;

	CPrefabManager::GetInstance()->DataInit(Tobject->GetIsEnabled(), Tobject->GetName(), Tobject->GetLayerKey(), Tobject->GetObjectKey(), Tobject->GetComponent<Engine::CMeshComponent>()->GetMeshKey(),
		Tobject->GetRotation(), Tobject->GetScale(), Tcollider);

	m_projectView->m_prefabList.AddString(Tobject->GetName().c_str());
}

// 프리팹 삭제
void CFeatureView::PrefabDelete() 
{
	if (m_main->m_mode == CMainFrame::Mode::NavMesh)
		return;

	int sel = m_projectView->m_prefabList.GetCurSel();

	if (sel == -1)
		return;

	m_projectView->m_prefabList.DeleteString(sel);
	CPrefabManager::GetInstance()->DataDelete(sel);
}

void CFeatureView::Save()
{
	CFileDialog Dlg(FALSE,// 저장(FALSE)할 것인지 불러(TRUE)올 것인지
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
			return;

		std::unordered_map<std::wstring, SHARED(Engine::CLayer)> layers = Engine::CSceneManager::GetInstance()->GetCurScene()->GetLayers();

		DWORD dwByte = 0;
		DWORD dwStringSize = 0;
		CString text;
		_int objectCount = Engine::GET_CUR_SCENE->GetObjectCount() - layers[L"NavMesh"].get()->GetGameObjects().size() - 3;
		_int colliderCount = 0;
		// 오브젝트
		WriteFile(hFile, &objectCount, sizeof(_int), &dwByte, nullptr);

		for (auto& layer : layers)
		{
			if(layer.first == L"NavMesh" || layer.first == L"Collider" || layer.first == L"Camera")
				continue;

			for (auto& gameObject : layer.second->GetGameObjects())
			{
				SaveWstring(&hFile, &dwByte, gameObject->GetName()); // 이름

				SaveWstring(&hFile, &dwByte, gameObject->GetLayerKey()); // 레이어 키

				SaveWstring(&hFile, &dwByte, gameObject->GetObjectKey()); // 오브젝트 키

				if(gameObject->GetComponent<Engine::CUIComponent>())
					SaveWstring(&hFile, &dwByte, gameObject->GetComponent<Engine::CUIComponent>()->GetTextureKey()); // UI 텍스쳐
				if(gameObject->GetComponent<Engine::CMeshComponent>())
					SaveWstring(&hFile, &dwByte, gameObject->GetComponent<Engine::CMeshComponent>()->GetMeshKey()); // 메쉬

				WriteFile(hFile, &gameObject->GetIsEnabled(), sizeof(bool), &dwByte, nullptr); // 활성화/비활성화
				WriteFile(hFile, &gameObject->GetPosition(), sizeof(vector3), &dwByte, nullptr); // 위치
				WriteFile(hFile, &gameObject->GetRotation(), sizeof(vector3), &dwByte, nullptr); // 회전
				WriteFile(hFile, &gameObject->GetScale(), sizeof(vector3), &dwByte, nullptr); // 크기

				ColliderData* collider = CColliderManager::GetInstance()->GetColliderData()[colliderCount];
				colliderCount += 1;
				text = collider->colliderType.c_str();
				dwStringSize = sizeof(wchar_t) * (text.GetLength() + 1);
				WriteFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr);
				WriteFile(hFile, text.GetString(), dwStringSize, &dwByte, nullptr);

				WriteFile(hFile, &collider->offset, sizeof(vector3), &dwByte, nullptr); // 위치
				WriteFile(hFile, &collider->boxsize, sizeof(vector3), &dwByte, nullptr); // 크기
				WriteFile(hFile, &collider->radius, sizeof(_float), &dwByte, nullptr); // 반지름
			}
		}

		// 네브매쉬
		_int size = CNavMeshManager::GetInstance()->GetGameObject().size();
		WriteFile(hFile, &size, sizeof(_int), &dwByte, nullptr);
		WriteFile(hFile, CNavMeshManager::GetInstance()->GetTriangleCount(), sizeof(_int), &dwByte, nullptr);

		for (auto& gameObject : CNavMeshManager::GetInstance()->GetGameObject()) // 네브매쉬
		{
			WriteFile(hFile, &gameObject->GetPosition(), sizeof(vector3), &dwByte, nullptr);
		}

		for (auto& triangle : CNavMeshManager::GetInstance()->GetTriangle())
		{
			WriteFile(hFile, &(*triangle.point[0]), sizeof(vector3), &dwByte, nullptr);
			WriteFile(hFile, &(*triangle.point[1]), sizeof(vector3), &dwByte, nullptr);
			WriteFile(hFile, &(*triangle.point[2]), sizeof(vector3), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}

}

void CFeatureView::Load()
{
	CFileDialog Dlg(TRUE,// 저장(FALSE)할 것인지 불러(TRUE)올 것인지
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
		CString wstrFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			return;
		}
		DWORD dwByte = 0;
		DWORD dwStringSize = 0;

		ReSetProject();

		// 오브젝트------------------------------------------------------------------------------------

		_int objectCount = 0;
		ReadFile(hFile, &objectCount, sizeof(_int), &dwByte, nullptr);

		for (int i = 0; i < objectCount; i++)
		{
			std::wstring strName = LoadWstring(&hFile, &dwByte); // 이름

			std::wstring layerKey = LoadWstring(&hFile, &dwByte); // 레이어

			std::wstring objectKey = LoadWstring(&hFile, &dwByte); // 오브젝트

			SHARED(Engine::CGameObject) obj = Engine::ADD_CLONE(layerKey, objectKey, true);
			obj->SetName(strName);

			if (obj->GetComponent<Engine::CUIComponent>())
			{
				obj->GetComponent<Engine::CUIComponent>()->SetTextureKey(LoadWstring(&hFile, &dwByte));
			}
			else if(obj->GetComponent<Engine::CMeshComponent>())
			{
				obj->GetComponent<Engine::CMeshComponent>()->SetMeshKey(LoadWstring(&hFile, &dwByte));
			}

			ReadFile(hFile, &obj->GetIsEnabled(), sizeof(bool), &dwByte, nullptr);
			ReadFile(hFile, &obj->GetPosition(), sizeof(vector3), &dwByte, nullptr);
			ReadFile(hFile, &obj->GetRotation(), sizeof(vector3), &dwByte, nullptr);
			ReadFile(hFile, &obj->GetScale(), sizeof(vector3), &dwByte, nullptr);

			m_hierarchyView->m_objectListBox.AddString(obj.get()->GetName().c_str());
			m_hierarchyView->m_objectPos.emplace_back(obj.get()->GetPosition());

			ColliderData* colliderData = new ColliderData();

			ReadFile(hFile, &dwStringSize, sizeof(DWORD), &dwByte, nullptr); // 이름
			TCHAR* colliderType = new TCHAR[dwStringSize];
			ReadFile(hFile, colliderType, dwStringSize, &dwByte, nullptr);

			colliderData->colliderType = colliderType;
			ReadFile(hFile, &colliderData->offset, sizeof(vector3), &dwByte, nullptr);
			ReadFile(hFile, &colliderData->boxsize, sizeof(vector3), &dwByte, nullptr);
			ReadFile(hFile, &colliderData->radius, sizeof(_float), &dwByte, nullptr);

			CColliderManager::GetInstance()->SetColliderData(colliderData);
		}

		//-------------------------------------------------------------------------------
		// 네브매쉬 오브젝트--------------------------------------------------------------
		_int m_createCount = 0;
		_int m_triangleCount = 0;
		ReadFile(hFile, &m_createCount, sizeof(_int), &dwByte, nullptr);
		ReadFile(hFile, &m_triangleCount, sizeof(_int), &dwByte, nullptr);

		vector3 pos;
		for (int i = 0; i < m_createCount; i++)
		{
			SHARED(Engine::CGameObject) navMeshObj = Engine::ADD_CLONE(L"NavMesh", L"NavMesh", true);
			navMeshObj->SetName(L"NavMesh");

			ReadFile(hFile, &pos, sizeof(vector3), &dwByte, nullptr);

			navMeshObj->SetPosition(pos);
			CNavMeshManager::GetInstance()->SetGameObject(navMeshObj);
		}

		CNavMeshManager::GetInstance()->DeleteTriangle();

		vector3 trianglePoint[3];
		Engine::Triangle triangle;
		CNavMeshManager::GetInstance()->SetTriangleCount(m_triangleCount);
		for (int i = 0; i < m_triangleCount; i++) // 네브매쉬 트라이앵글
		{
			for (int i = 0; i < 3; i++)
			{
				ReadFile(hFile, &trianglePoint[i], sizeof(vector3), &dwByte, nullptr);
				SHARED(Engine::CGameObject)  navMeshObj = Engine::GET_CUR_SCENE->FindObjectPosition(trianglePoint[i]);
				triangle.point[i] = &navMeshObj->GetPosition();
			}
			CNavMeshManager::GetInstance()->SetTriangle(triangle);
			
		}

		CNavMeshManager::GetInstance()->SetTriangle(Engine::Triangle());
		CloseHandle(hFile);
	}
}

BEGIN_MESSAGE_MAP(CFeatureView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON6, &CFeatureView::PrefabCreate)
	ON_BN_CLICKED(IDC_BUTTON1, &CFeatureView::Save)
	ON_BN_CLICKED(IDC_BUTTON2, &CFeatureView::Load)
	ON_BN_CLICKED(IDC_BUTTON11, &CFeatureView::PrefabDelete)
	ON_BN_CLICKED(IDC_BUTTON3, &CFeatureView::NavMeshMode)
	ON_BN_CLICKED(IDC_BUTTON8, &CFeatureView::UIMode)
END_MESSAGE_MAP()


// CFeatureView 진단입니다.

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