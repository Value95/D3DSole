#include "stdafx.h"
#include "DongilScene.h"

#include "ScarecrowIdle.h"
#include "PlayerWapon.h"

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
	//LoadObject(L"TestScene");

	{
		m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();
		m_pMainCamera->GetOwner()->SetCamera(true);
		m_pMainCamera->GetOwner()->SetPosition(vector3(0, 0, 0));
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Player", L"Player", true);
		pObj->SetPosition(vector3(10,5,10));

		m_pMainCamera->GetOwner()->SetTarget(pObj.get());
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetPosition(vector3(10, 0,10));
		pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3One, vector3Zero));
		pObj->AddComponent<Engine::CBoxComponent>()->SetSize(vector3(1, 1, 1));
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetPosition(vector3(0, 0, 0));
		pObj->SetScale(vector3(10, 10, 10));
		pObj->AddComponent<Engine::CSkyBoxComponent>()->SetTextureKey(L"burger0");
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetRotation(vector3(30, -50, 0));
		pObj->AddComponent<Engine::CDirectionalLightComponent>();
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetName(L"Sword");
		pObj->SetPosition(vector3(0, 0, 0));
		pObj->SetRotation(vector3(45, 45, 45));
		pObj->SetScale(vector3(0.01f, 0.01f, 0.01f));
		pObj->AddComponent<CPlayerWapon>();
		pObj->AddComponent<Engine::CMeshComponent>()->SetMeshKey(L"Wapon_Sword_000.X");
		pObj->AddComponent<Engine::CStaticMeshRenderComponent>();
	}


	/*{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Monster", L"Scarecrow", true);
		pObj->SetPosition(vector3(5, 0, 5));
		pObj->AddComponent<CMonster>()->AddFSM<CScarecrowIdle>();
	}*/

	/*{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetPosition(vector3(0, 0, 7));
		pObj->SetCamera(true);
		pObj->SetRotationY(120);
		pObj->SetScale(vector3(0.01f, 0.01f, 0.01f));
		pObj->AddComponent<Engine::CMeshComponent>()->SetMeshKey(L"CrystalSpider.X");
		pObj->AddComponent<Engine::CStaticMeshRenderComponent>();
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
	AddLayer(L"Light");
	AddLayer(L"Camera");
	AddLayer(L"Player");
	AddLayer(L"Default");
	AddLayer(L"Monster");
	AddLayer(L"UI");
}

void CDongilScene::InitPrototypes(void)
{

}


/*{
SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
pObj->SetPosition(vector3(0, 0, 5));
pObj->SetScale(vector3(30, 30, 1));
pObj->AddComponent<Engine::CUIComponent>()->SetTextureKey(L"Blue");
}*/

/*{
SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
pObj->SetName(L"Player");
pObj->SetPosition(vector3(0, 0, 2));
pObj->SetScale(vector3(1, 1, 1));
pObj->AddComponent<Engine::CTriangleComponent>();
pObj->AddComponent<CPlayer>();
}*/

/*{
SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
pObj->SetPosition(vector3(0, 0, 0));
pObj->SetScale(vector3(0.5f, 0.5f, 0.5f));
pObj->AddComponent<Engine::CLineComponent>()->EndLinePosition(vector3(5,0,5));
}

{
SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
pObj->SetPosition(vector3(0, 0, 4));
pObj->SetScale(vector3(0.5f, 0.5f, 0.5f));
pObj->AddComponent<Engine::CBoxComponent>();
}*/

/*{
SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
pObj->SetPosition(vector3(0, 0, 7));
pObj->AddComponent<CPlayer>();
pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3Zero));
pObj->AddComponent<Engine::CMeshComponent>()->SetMeshKey(L"sylva.X");
pObj->AddComponent<Engine::CStaticMeshRenderComponent>();
}*/

/*{
SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
pObj->SetPosition(vector3(0, 0, 7));
pObj->SetScale(vector3(0.01f, 0.01f, 0.01f));
pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3Zero));
pObj->AddComponent<Engine::CAnimMeshRenderComponent>()->MeshInput(L"../../Resource/Mesh/Static/Pick/", L"Pick.X");
}

{
SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Player", L"Player", true);
pObj->AddComponent<CPlayer>();
pObj->SetPosition(vector3(0, 0, 0));
}*/

/*
{
SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
pObj->SetPosition(vector3(7, 0, 0));
pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3Zero));
pObj->AddComponent<Engine::CMeshComponent>();
pObj->AddComponent<Engine::CTextureComponent>();
pObj->AddComponent<Engine::CStaticMeshRenderComponent>();
}

{
SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
pObj->SetPosition(vector3(-7, 0, 0));
pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3Zero));
pObj->AddComponent<Engine::CMeshComponent>();
pObj->AddComponent<Engine::CTextureComponent>();
pObj->AddComponent<Engine::CStaticMeshRenderComponent>();
}

{
SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
pObj->SetPosition(vector3(0, 7, 0));
pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3Zero));
pObj->AddComponent<Engine::CMeshComponent>();
pObj->AddComponent<Engine::CTextureComponent>();
pObj->AddComponent<Engine::CStaticMeshRenderComponent>();
}

{
SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
pObj->SetPosition(vector3(0, -7, 0));
pObj->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3Zero));
pObj->AddComponent<Engine::CMeshComponent>();
pObj->AddComponent<Engine::CTextureComponent>();
pObj->AddComponent<Engine::CStaticMeshRenderComponent>();
}*/