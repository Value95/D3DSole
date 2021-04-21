#include "stdafx.h"
#include "EditorScene.h"
#include "ColliderManager.h"

CEditorScene::CEditorScene()
{
}

CEditorScene::~CEditorScene()
{
}

SHARED(Engine::CScene) CEditorScene::Create(void)
{
	SHARED(CEditorScene) pCLogoScene(new CEditorScene, Engine::SmartDeleter<CEditorScene>);

	return pCLogoScene;
}

void CEditorScene::Awake(void)
{
	__super::Awake();
	InitLayers();
	InitPrototypes();
}

void CEditorScene::Start(void)
{
	__super::Start();

	m_main = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	m_editorView = dynamic_cast<CMy3DEditorView*>(m_main->m_leftSplitter.GetPane(0, 0));
	m_projectView = dynamic_cast<CProjectView*>(m_main->m_leftSplitter.GetPane(1, 0));
	m_hierarchyView = dynamic_cast<CHierarchyView*>(m_main->m_mainSplitter.GetPane(0, 1));
	m_inspectorView = dynamic_cast<CInspectorView*>(m_main->m_rightSplitter.GetPane(0, 0));

	m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();

	{
		m_box = Engine::CObjectFactory::GetInstance()->AddClone(L"Collider", L"Collider", true);
		m_box->SetScale(vector3Zero);
		m_box->AddComponent<Engine::CBoxComponent>();
	}

	{
		m_sphere = Engine::CObjectFactory::GetInstance()->AddClone(L"Collider", L"Collider", true);
		m_sphere->SetScale(vector3Zero);
		m_sphere->AddComponent<Engine::CSphereComponent>();
	}
}

_uint CEditorScene::FixedUpdate(void)
{
	_uint event = NO_EVENT;
	if (event = __super::FixedUpdate())
		return event;

	return _uint();
}

_uint CEditorScene::Update(void)
{
	std::unordered_map<std::wstring, SHARED(Engine::CLayer)> layer = Engine::CSceneManager::GetInstance()->GetCurScene()->GetLayers();

	_uint event = NO_EVENT;
	if (event = __super::Update())
		return event;

	Camera();

	// 네브매쉬모드가되면 생성방법 픽킹방법이바뀐다.
	if (m_main->m_mode == CMainFrame::Mode::Normal)
	{
		ObjectCreate();
		ObjectPicking(L"Default");
		ColliderSesting(m_pickNumber, m_pickingObject);
	}
	else if (m_main->m_mode == CMainFrame::Mode::NavMesh)
	{
		CNavMeshManager::GetInstance()->ObjectCreate();
		
		Engine::CGameObject* T = CNavMeshManager::GetInstance()->ObjectPicking();
		if (T != nullptr)
			m_pickingObject = T;
	}
	if (m_main->m_mode == CMainFrame::Mode::UI)
	{
		ObjectCreate();
	}

	ObjectMove();
	ObjectMoveToView();

	if (Engine::IMKEY_DOWN(KEY_DEL))
	{
		m_inspectorView->DeleteObject();
	}
	if (Engine::IMKEY_DOWN(KEY_RETURN))
	{
		m_inspectorView->InputData();
	}

	return event;
}

_uint CEditorScene::LateUpdate(void)
{
	_uint event = NO_EVENT;
	if (event = __super::LateUpdate())
		return event;


	return event;
}

void CEditorScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CEditorScene::OnEnable(void)
{
}

void CEditorScene::OnDisable(void)
{
}

void CEditorScene::InitLayers(void)
{
	AddLayer(L"Camera");
	AddLayer(L"Default");
	AddLayer(L"UI");
	AddLayer(L"Light");
	AddLayer(L"NavMesh");
	AddLayer(L"Collider");
}

void CEditorScene::InitPrototypes(void)
{
	SHARED(Engine::CGameObject) camera = Engine::CGameObject::Create(L"Camera", L"Camera", true);
	camera->AddComponent<Engine::CCameraComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(camera);

	SHARED(Engine::CGameObject) mess = Engine::CGameObject::Create(L"Default", L"Mess", true);
	mess->AddComponent<Engine::CGraphicsComponent>();
	mess->AddComponent<Engine::CMeshComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(mess);

	SHARED(Engine::CGameObject) collider = Engine::CGameObject::Create(L"Collider", L"Collider", true);
	Engine::CObjectFactory::GetInstance()->AddPrototype(collider);

	SHARED(Engine::CGameObject) navMesh = Engine::CGameObject::Create(L"NavMesh", L"NavMesh", true);
	navMesh->AddComponent<Engine::CSphereComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(navMesh);

	SHARED(Engine::CGameObject) directionalLight = Engine::CGameObject::Create(L"Light", L"DirectionalLight", true);
	directionalLight->AddComponent<Engine::CDirectionalLightComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(directionalLight);

	SHARED(Engine::CGameObject) ui = Engine::CGameObject::Create(L"UI", L"UI", true);
	ui->AddComponent<Engine::CUIComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(ui);
}

void CEditorScene::Camera()
{
	if (!Engine::IMKEY_PRESS(KEY_LBUTTON))
	{
		m_pMainCamera->CameraMove();
	}

	if (Engine::IMKEY_PRESS(KEY_RBUTTON))
	{
		if (Engine::IMKEY_DOWN(KEY_RBUTTON))
		{
			POINT curPt;
			GetCursorPos(&curPt);
			m_pMainCamera->SetCenterPt(curPt);
		}
		m_pMainCamera->CameraRotation();
	}
}

void CEditorScene::ObjectCreate()
{
	if (Engine::IMKEY_PRESS(KEY_LBUTTON))
	{
		return;
	}

	if (Engine::IMKEY_DOWN(KEY_E))
	{
		DirectionalLightObject(L"DirectionalLight");
	}

	if (Engine::IMKEY_DOWN(KEY_Q))
	{
		CString cMessKey, cTextureKey, cPrefabKey;

		_int messlistSel = m_projectView->m_messList.GetCurSel();
		_int textureSel = m_projectView->m_textureList.GetCurSel();
		_int prefabSel = m_projectView->m_prefabList.GetCurSel();

		if(messlistSel != -1)
			m_projectView->m_messList.GetText(messlistSel, cMessKey);
		if(textureSel != -1)
			m_projectView->m_textureList.GetText(textureSel, cTextureKey);
		if (prefabSel != -1)
			m_projectView->m_prefabList.GetText(prefabSel, cPrefabKey);

		if (cMessKey != L"Default")
			NormalObject(cMessKey);
		else if (cTextureKey != L"Default")
			UIObject(cTextureKey);
		else if (cPrefabKey != L"")
			PrefabObject();
	}

}

void CEditorScene::ObjectPicking(std::wstring layerKey)
{
	if (Engine::IMKEY_DOWN(KEY_LBUTTON))
	{
		POINT point;
		GetCursorPos(&point);
		vector3		origin;

		if (point.x >= 1056 || point.y >= 648)
			return;

		// 마우스좌표(뷰포트) -> (월드행렬)로변환
		D3DVIEWPORT9		ViewPort;
		ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));

		Engine::GET_DEVICE->GetViewport(&ViewPort);

		origin.x = point.x / (1056 * 0.5f) - 1.f;
		origin.y = point.y / (648 * -0.5f) + 1.f;
		origin.z = 0.f;

		// 투영 -> 뷰스페이스

		matrix4x4 matProj;
		Engine::GET_DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);
		D3DXMatrixInverse(&matProj, NULL, &matProj);
		D3DXVec3TransformCoord(&origin, &origin, &matProj);

		// 뷰스페이스 -> 월드

		vector3	rayDir, rayPos;

		rayPos = vector3(0.0f, 0.0f, 0.0f);
		rayDir = origin - rayPos;

		matrix4x4		matView;
		Engine::GET_DEVICE->GetTransform(D3DTS_VIEW, &matView);
		D3DXMatrixInverse(&matView, NULL, &matView);

		D3DXVec3TransformCoord(&rayPos, &rayPos, &matView);
		D3DXVec3TransformNormal(&rayDir, &rayDir, &matView);

		Engine::CGameObject* obj = Engine::CRaycast::RayCast(rayPos, rayDir, 1000, layerKey);
		if (obj != nullptr)
		{
			for (int i = 0; i <= m_hierarchyView->m_objectPos.size() - 1; i++)
			{
				if (Engine::Dropdecimalpoint(m_hierarchyView->m_objectPos[i].x, 1000) == Engine::Dropdecimalpoint(obj->GetPosition().x, 1000) &&
					Engine::Dropdecimalpoint(m_hierarchyView->m_objectPos[i].y, 1000) == Engine::Dropdecimalpoint(obj->GetPosition().y, 1000))
				{
					m_pickingObject = obj;
					m_pickNumber = i;
					m_hierarchyView->m_objectListBox.SetCurSel(m_pickNumber);
					break;
				}
			}

			m_inspectorView->SetData(obj);
		}
	}
}

void CEditorScene::ObjectMove()
{
	if (m_pickingObject == nullptr || (m_pickNumber == -1 && m_main->m_mode != CMainFrame::Mode::NavMesh))
		return;

	if (Engine::IMKEY_PRESS(KEY_LBUTTON))
	{
		_float speed = 10.f;
		if (Engine::IMKEY_PRESS(KEY_SHIFT))
		{
			speed = 200;
		}

		if (Engine::IMKEY_PRESS(KEY_W))
		{
			m_pickingObject->CameraDirTranslate(vector3Forward * deltaTime * speed);
			InspactorSesting(m_pickNumber, m_pickingObject);
		}
		if (Engine::IMKEY_PRESS(KEY_S))
		{
			m_pickingObject->CameraDirTranslate(vector3Back * deltaTime * speed);
			InspactorSesting(m_pickNumber, m_pickingObject);
		}

		if (Engine::IMKEY_PRESS(KEY_A))
		{
			m_pickingObject->CameraDirTranslate(vector3Left * deltaTime * speed);
			InspactorSesting(m_pickNumber, m_pickingObject);
		}
		if (Engine::IMKEY_PRESS(KEY_D))
		{
			m_pickingObject->CameraDirTranslate(vector3Right * deltaTime * speed);
			InspactorSesting(m_pickNumber, m_pickingObject);
		}
		if (Engine::IMKEY_PRESS(KEY_Q))
		{
			m_pickingObject->CameraDirTranslate(vector3Up * deltaTime * speed);
			InspactorSesting(m_pickNumber, m_pickingObject);
		}
		if (Engine::IMKEY_PRESS(KEY_E))
		{
			m_pickingObject->CameraDirTranslate(vector3Down * deltaTime * speed);
			InspactorSesting(m_pickNumber, m_pickingObject);
		}
	}

	if(m_main->m_mode != CMainFrame::Mode::NavMesh)
	{
		m_hierarchyView->m_objectPos[m_pickNumber] = m_pickingObject->GetPosition();
	}
}

void CEditorScene::ObjectMoveToView()
{
	if (m_pickingObject == nullptr || m_pickNumber == -1)
		return;

	if (Engine::IMKEY_PRESS(KEY_CTRL))
	{
		if (Engine::IMKEY_DOWN(KEY_F))
		{
			m_pickingObject->SetPosition(Engine::GET_MAIN_CAM->GetOwner()->GetPosition());
		}
	}
}

void CEditorScene::NormalObject(CString messKey)
{
	if (messKey == L"")
		return;

	std::wstring wMessKey;
	wMessKey = CStringW(messKey);

	SHARED(Engine::CGameObject) pObj = Engine::ADD_CLONE(L"Default", L"Mess", true);
	pObj->SetIsEnabled(true);
	pObj->SetName(L"GameObejct");
	pObj->GetComponent<Engine::CMeshComponent>()->SetMeshKey(wMessKey);

	pObj->SetPosition(m_pMainCamera->GetOwner()->ReturnTranslate(vector3(0, 0, 5)));

	CColliderManager::GetInstance()->SetColliderData(new ColliderData());

	m_hierarchyView->m_objectListBox.AddString(pObj.get()->GetName().c_str());
	m_hierarchyView->m_objectPos.emplace_back(pObj.get()->GetPosition());

	m_inspectorView->SetData(pObj.get());
}

void CEditorScene::PrefabObject()
{
	_bool enable = true;;
	std::wstring wMessKey;
	CString messKey;
	std::wstring name = L"GameObejct";
	std::wstring layerKey = L"Default", objectKey = L"Mess";
	vector3 rotation = vector3Zero;
	vector3 scale = vector3One;

	ColliderData* Tcollider = new ColliderData();
	PrefabData TprefabData;

	int sel = m_projectView->m_prefabList.GetCurSel();
	if (sel != -1) // 프리팹이 설정되어있다면 프리팹을
	{
		TprefabData = CPrefabManager::GetInstance()->GetPrefabData()[sel];
		enable = TprefabData.enable;
		name = TprefabData.name;
		layerKey = TprefabData.layerKey;
		objectKey = TprefabData.objectKey;
		messKey = TprefabData.messKey.c_str();
		rotation = TprefabData.rotation;
		scale = TprefabData.scale;

		Tcollider->colliderType = TprefabData.collider->colliderType;
		Tcollider->offset = TprefabData.collider->offset;
		Tcollider->boxsize = TprefabData.collider->boxsize;
		Tcollider->radius = TprefabData.collider->radius;
	}
	else
	{
		return;
	}

	wMessKey = CStringW(messKey);

	// 오브젝트 생성--------------------------------------------------
	SHARED(Engine::CGameObject) pObj = Engine::ADD_CLONE(L"Default", L"Mess", true);
	pObj->SetLayerKey(layerKey);
	pObj->SetObjectKey(objectKey);
	pObj->SetIsEnabled(enable);
	pObj->SetName(name);
	pObj->GetComponent<Engine::CMeshComponent>()->SetMeshKey(wMessKey);

	pObj->SetPosition(m_pMainCamera->GetOwner()->ReturnTranslate(vector3(0, 0, 5)));
	pObj->SetRotation(rotation);
	pObj->SetScale(scale);

	CColliderManager::GetInstance()->SetColliderData(Tcollider);

	m_hierarchyView->m_objectListBox.AddString(pObj.get()->GetName().c_str());
	m_hierarchyView->m_objectPos.emplace_back(pObj.get()->GetPosition());

	m_inspectorView->SetData(pObj.get());
}

void CEditorScene::DirectionalLightObject(CString objectKey)
{
	std::wstring wObjectKey;

	std::wstring name = L"Light";

	ColliderData* Tcollider = new ColliderData();
	
	wObjectKey = CStringW(objectKey);

	// 오브젝트 생성--------------------------------------------------
	SHARED(Engine::CGameObject) pObj = Engine::ADD_CLONE(L"Light", wObjectKey, true);
	pObj->SetName(name);

	pObj->SetPosition(m_pMainCamera->GetOwner()->ReturnTranslate(vector3(0, 0, 5)));
	CColliderManager::GetInstance()->SetColliderData(Tcollider);

	m_hierarchyView->m_objectListBox.AddString(pObj.get()->GetName().c_str());
	m_hierarchyView->m_objectPos.emplace_back(pObj.get()->GetPosition());

	m_inspectorView->SetData(pObj.get());
}

void CEditorScene::UIObject(CString textureKey)
{
	if (textureKey == L"Default" || textureKey == L"")
		return;

	std::wstring wTextureKey;

	std::wstring name = L"UI";

	ColliderData* Tcollider = new ColliderData();

	wTextureKey = CStringW(textureKey);

	// 오브젝트 생성--------------------------------------------------
	SHARED(Engine::CGameObject) pObj = Engine::ADD_CLONE(L"UI", L"UI", true);
	pObj->SetName(name);
	pObj->SetPosition(vector3Zero);
	pObj->GetComponent<Engine::CUIComponent>()->SetTextureKey(wTextureKey);

	CColliderManager::GetInstance()->SetColliderData(Tcollider);

	m_hierarchyView->m_objectListBox.AddString(pObj.get()->GetName().c_str());
	m_hierarchyView->m_objectPos.emplace_back(pObj.get()->GetPosition());

	m_inspectorView->SetData(pObj.get());
}

void CEditorScene::ColliderSesting(int value, Engine::CGameObject * object)
{
	if (value == -1 || object == nullptr || CColliderManager::GetInstance()->GetColliderData().size() <= value)
		return;

	if (CColliderManager::GetInstance()->GetColliderData()[value]->colliderType == L"BOX")
	{
		m_box->SetPosition(object->GetPosition() + CColliderManager::GetInstance()->GetColliderData()[value]->offset);
		m_box->SetScale(CColliderManager::GetInstance()->GetColliderData()[value]->boxsize);
	}
	else if (CColliderManager::GetInstance()->GetColliderData()[value]->colliderType == L"SPHERE")
	{
		m_sphere->SetPosition(object->GetPosition());
		vector3 scale = vector3(CColliderManager::GetInstance()->GetColliderData()[value]->radius, CColliderManager::GetInstance()->GetColliderData()[value]->radius, CColliderManager::GetInstance()->GetColliderData()[value]->radius);
		m_sphere->SetScale(scale);
	}
}

void CEditorScene::InspactorSesting(int value, Engine::CGameObject * object)
{
	if (value == -1 || object == nullptr || CColliderManager::GetInstance()->GetColliderData().size() <= value)
		return;

	m_inspectorView->SetData(object);

}
