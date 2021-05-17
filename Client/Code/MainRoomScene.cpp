#include "stdafx.h"
#include "MainRoomScene.h"

#include "PlayerWapon.h"
#include "PlayerMiniGock.h"

#include "DongilScene.h"
CMainRoomScene::CMainRoomScene()
{
}


CMainRoomScene::~CMainRoomScene()
{
}

SHARED(Engine::CScene) CMainRoomScene::Create(void)
{
	SHARED(CMainRoomScene) pCLogoScene(new CMainRoomScene, Engine::SmartDeleter<CMainRoomScene>);
	return pCLogoScene;
}

void CMainRoomScene::Awake(void)
{
	__super::Awake();

	InitLayers();
	InitPrototypes();
}

void CMainRoomScene::Start(void)
{
	__super::Start();

	LoadObject(L"MainRoom");
	LoadObject(L"StatReinforceShop");

	{ // Ä«¸Þ¶ó
		m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();
		m_pMainCamera->GetOwner()->SetCamera(true);
		m_pMainCamera->GetOwner()->SetPosition(vector3(0, 0, 0));
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
		pObj->AddComponent<Engine::CStaticMeshRenderComponent>();
	}

	{
		SHARED(Engine::CGameObject) pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Default", L"Default", true);
		pObj->SetIsEnabled(false);
		pObj->SetName(L"MiniGock");
		pObj->SetScale(vector3(0.01f, 0.01f, 0.01f));
		pObj->SetRotation(vector3(415, 414, 0));
		pObj->AddComponent<CPlayerMiniGock>();
		pObj->AddComponent<Engine::CMeshComponent>()->SetMeshKey(L"MiniGock.X");
		pObj->AddComponent<Engine::CStaticMeshRenderComponent>();
	}

	m_pMainCamera->GetOwner()->SetTarget(Engine::GET_CUR_SCENE->FindObjectByName(L"Player").get());

}

_uint CMainRoomScene::FixedUpdate(void)
{
	__super::FixedUpdate();

	return NO_EVENT;
}

_uint CMainRoomScene::Update(void)
{
	_uint event = 0;
	if (event = __super::Update())
		return event;

	return event;
}

_uint CMainRoomScene::LateUpdate(void)
{
	_uint event = 0;
	if (event = __super::LateUpdate())
		return event;

	return event;
}

void CMainRoomScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CMainRoomScene::OnEnable(void)
{
}

void CMainRoomScene::OnDisable(void)
{
}

void CMainRoomScene::InitLayers(void)
{
	AddLayer(L"Light");
	AddLayer(L"Camera");
	AddLayer(L"Player");
	AddLayer(L"Default");
	AddLayer(L"Monster");
	AddLayer(L"UI");
	AddLayer(L"Collider");
	AddLayer(L"Map");
	AddLayer(L"Interaction");
	AddLayer(L"NPC");
}

void CMainRoomScene::InitPrototypes(void)
{

}