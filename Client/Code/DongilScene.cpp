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
	pCLogoScene->InitLayers();
	pCLogoScene->InitPrototypes();
	pCLogoScene->LoadObject(L"TestScene", pCLogoScene);
	pCLogoScene->LoadObject(L"StatReinforceShop", pCLogoScene);
	return pCLogoScene;
}

void CDongilScene::Awake(void)
{
	__super::Awake();
}

void CDongilScene::Start(void)
{
	Engine::CSoundManager::GetInstance()->PlayBGM(L"Map_Fx_City_01.wav");

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

	__super::Start();

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
	Engine::CSoundManager::GetInstance()->StopAll();

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