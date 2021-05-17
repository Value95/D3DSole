#include "stdafx.h"
#include "DongilScene.h"
#include "SceneManager.h"

#include "PlayerWapon.h"
#include "PlayerMiniGock.h"

#include "ShaderMesh.h"

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
	LoadObject(L"TestScene");
	LoadObject(L"StatReinforceShop");

	{ // 카메라
		m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();
		m_pMainCamera->GetOwner()->SetCamera(true);
		m_pMainCamera->GetOwner()->SetPosition(vector3(0, 0, 0));
	}

	{ // 스카이박스
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetPosition(vector3(0, 0, 0));
		pObj->SetScale(vector3(10, 10, 10));
		pObj->AddComponent<Engine::CSkyBoxComponent>()->SetTextureKey(L"burger0");
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Light", L"DirectionalLight", true);
		pObj->SetRotation(vector3(50, -30, 0));
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetName(L"Sword");
		pObj->SetScale(vector3(0.1f, 0.1f, 0.1f));
		pObj->SetRotation(vector3(325, 175, 364));
		pObj->AddComponent<CPlayerWapon>();
		pObj->AddComponent<Engine::CMeshComponent>()->SetMeshKey(L"Wapon_LongHammer_000.X");
		pObj->AddComponent<Engine::CStaticMeshRenderComponent>()->SetShader(new CShaderMesh());
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetIsEnabled(false);
		pObj->SetName(L"MiniGock");
		pObj->SetScale(vector3(0.01f, 0.01f, 0.01f));
		pObj->SetRotation(vector3(415, 414, 0));
		pObj->AddComponent<CPlayerMiniGock>();
		pObj->AddComponent<Engine::CMeshComponent>()->SetMeshKey(L"MiniGock.X");
		pObj->AddComponent<Engine::CStaticMeshRenderComponent>()->SetShader(new CShaderMesh());
	}

	m_pMainCamera->GetOwner()->SetTarget(Engine::GET_CUR_SCENE->FindObjectByName(L"Player").get());

}

_uint CDongilScene::FixedUpdate(void)
{
	__super::FixedUpdate();


	return NO_EVENT;
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
	AddLayer(L"Boss");
	AddLayer(L"UI");
	AddLayer(L"Collider");
	AddLayer(L"Map");
	AddLayer(L"Interaction");
}

void CDongilScene::InitPrototypes(void)
{

}

/*

{
SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
pObj->SetPosition(vector3(5, 0, 0));
pObj->AddComponent<Engine::CEffectComponent>()->Reset(L"Explosion", 89);
pObj->AddComponent<Engine::CAnimMeshRenderComponent>();
}

{
	SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"UI", L"UI", true);
	pObj->SetPosition(vector3(0, 0, 0));
	pObj->SetScale(vector3(800, 600, 0));
	pObj->GetComponent<Engine::CUIComponent>()->SetTextureKey(L"MainLogo");
	pObj->GetComponent<Engine::CUIComponent>()->SetShader(Engine::CShader::Create(L"Shader_Sample.hpp"));
}*/

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
