#include "stdafx.h"
#include "DongilScene.h"

CDongilScene::CDongilScene()
{
}


CDongilScene::~CDongilScene()
{
}

SHARED(Engine::CScene) CDongilScene::Create(void)
{
	SHARED(CDongilScene) pCLogoScene(new CDongilScene, Engine::SmartDeleter<CDongilScene>);
	return pCLogoScene;
}

void CDongilScene::Awake(void)
{
	__super::Awake();

	InitLayers();
	InitPrototypes();
}

void CDongilScene::Start(void)
{
	__super::Start();

	{
		m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();
	}

	/*{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetPosition(vector3(0, 0, 5));
		pObj->SetScale(vector3(30, 30, 1));
		pObj->AddComponent<Engine::CUIComponent>();
	}*/

	/*{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetName(L"Player");
		pObj->SetPosition(vector3(0, 0, 2));
		pObj->SetScale(vector3(1, 1, 1));
		pObj->AddComponent<Engine::CTriangleComponent>();
		pObj->AddComponent<CPlayer>();
	}*/

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetPosition(vector3(0, 0, 4));
		pObj->SetScale(vector3(0.5f, 0.5f, 0.5f));
		pObj->AddComponent<Engine::CSphereComponent>();
	}

	/*{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetPosition(vector3(0, 0, 7));
		pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3Zero));
		pObj->AddComponent<Engine::CMeshComponent>()->SetMeshKey(L"Cube");
		pObj->AddComponent<Engine::CTextureComponent>()->SetTextureKey(L"Blue");
		pObj->AddComponent<Engine::CGraphicsComponent>();
	}*/

	/*
	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetPosition(vector3(7, 0, 0));
		pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3Zero));
		pObj->AddComponent<Engine::CMeshComponent>();
		pObj->AddComponent<Engine::CTextureComponent>();
		pObj->AddComponent<Engine::CGraphicsComponent>();
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetPosition(vector3(-7, 0, 0));
		pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3Zero));
		pObj->AddComponent<Engine::CMeshComponent>();
		pObj->AddComponent<Engine::CTextureComponent>();
		pObj->AddComponent<Engine::CGraphicsComponent>();
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetPosition(vector3(0, 7, 0));
		pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3Zero));
		pObj->AddComponent<Engine::CMeshComponent>();
		pObj->AddComponent<Engine::CTextureComponent>();
		pObj->AddComponent<Engine::CGraphicsComponent>();
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetPosition(vector3(0, -7, 0));
		pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3Zero));
		pObj->AddComponent<Engine::CMeshComponent>();
		pObj->AddComponent<Engine::CTextureComponent>();
		pObj->AddComponent<Engine::CGraphicsComponent>();
	}*/
}

_uint CDongilScene::FixedUpdate(void)
{
	__super::FixedUpdate();

	return _uint();
}

_uint CDongilScene::Update(void)
{
	_uint event = 0;
	if (event = __super::Update())
		return event;
	m_pMainCamera->CameraMove();

	return event;
}

_uint CDongilScene::LateUpdate(void)
{
	_uint event = 0;
	if (event = __super::LateUpdate())
		return event;

	return event;
}

void CDongilScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CDongilScene::OnEnable(void)
{
}

void CDongilScene::OnDisable(void)
{
}

void CDongilScene::InitLayers(void)
{
	AddLayer(L"Camera");
	AddLayer(L"Player");
	AddLayer(L"EventBlock");
	AddLayer(L"Default");
}

void CDongilScene::InitPrototypes(void)
{

}