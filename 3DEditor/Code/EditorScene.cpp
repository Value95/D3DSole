#include "stdafx.h"
#include "EditorScene.h"


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
	hierarchyView = dynamic_cast<CHierarchyView*>(m_main->m_mainSplitter.GetPane(0, 1));
	inspectorView = dynamic_cast<CInspectorView*>(m_main->m_rightSplitter.GetPane(0, 0));

	m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", false)->GetComponent<Engine::CCameraComponent>();
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
	_uint event = NO_EVENT;
	if (event = __super::Update())
		return event;

	Camera();
	ObjectCreate();
	ObjectPicking();

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

}

void CEditorScene::InitPrototypes(void)
{
	SHARED(Engine::CGameObject) camera = Engine::CGameObject::Create(L"Camera", L"Camera", false);
	camera->SetPosition(vector3(0, 0, -5));
	camera->AddComponent<Engine::CCameraComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(camera);

	SHARED(Engine::CGameObject) default = Engine::CGameObject::Create(L"Default", L"Default", false);
	default->SetPosition(vector3(0, 0, 0));
	default->SetScale(vector3One);
	default->SetRotation(vector3Zero);
	default->AddComponent<Engine::CGraphicsComponent>();
	default->AddComponent<Engine::CTextureComponent>();
	default->AddComponent<Engine::CMeshComponent>();
	default->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3Zero));
	Engine::CObjectFactory::GetInstance()->AddPrototype(default);
}

void CEditorScene::Camera()
{
	m_pMainCamera->CameraMove();

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
	if (Engine::IMKEY_DOWN(KEY_Q))
	{
		CString cMessKey, cTextureKey;
		m_projectView->m_messList.GetText(m_projectView->m_messList.GetCurSel(), cMessKey);
		m_projectView->m_textureList.GetText(m_projectView->m_textureList.GetCurSel(), cTextureKey);

		// 오브젝트 생성
		std::wstring wMessKey, wTextureKey;

		wMessKey = CStringW(cMessKey);
		wTextureKey = CStringW(cTextureKey);

		if (cMessKey == L"Default" || cTextureKey == L"Default")
		{
			return;
		}

		SHARED(Engine::CGameObject) pObj = Engine::ADD_CLONE(L"Default", L"Default", false);
		pObj->SetName(wMessKey);
		pObj->GetComponent<Engine::CMeshComponent>()->SetMeshKey(wMessKey);
		pObj->GetComponent<Engine::CTextureComponent>()->SetTextureKey(wTextureKey);

		vector3 outHit;
		Engine::CGameObject* obj = Engine::CRaycast::RayCast(m_pMainCamera->GetOwner()->GetPosition(), Engine::AtDirectine(vector3Forward, m_pMainCamera->GetOwner()->GetRotation()), 100, L"Default", outHit);
		if (obj != nullptr)
		{
			pObj->SetPosition(m_pMainCamera->GetOwner()->ReturnTranslate(outHit));
		}
		else
		{
			pObj->SetPosition(m_pMainCamera->GetOwner()->ReturnTranslate(vector3(0, 0, 5)));
		}
		inspectorView->SetData(pObj.get());

		hierarchyView->m_objectListBox.AddString(pObj.get()->GetName().c_str());
		hierarchyView->m_objectPos.emplace_back(pObj.get()->GetPosition());
	}

}
void CEditorScene::ObjectPicking()
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

		Engine::CGameObject* obj = Engine::CRaycast::RayCast(rayPos, rayDir, 1000, L"Default");
		if (obj != nullptr)
		{
			inspectorView->SetData(obj);

			for (int i=0; i <= hierarchyView->m_objectPos.size()-1; i++)
			{
				if (Engine::Dropdecimalpoint(hierarchyView->m_objectPos[i].x, 1000) == Engine::Dropdecimalpoint(obj->GetPosition().x,1000) &&
					Engine::Dropdecimalpoint(hierarchyView->m_objectPos[i].y, 1000) == Engine::Dropdecimalpoint(obj->GetPosition().y, 1000))
				{
					hierarchyView->m_objectListBox.SetCurSel(i);
					return;
				}
			}
		}
	}

}

