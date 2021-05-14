#include "stdafx.h"
#include "TitleScene.h"
#include "MainRoomScene.h"

CTitleScene::CTitleScene()
{
}

CTitleScene::~CTitleScene()
{
}

SHARED(Engine::CScene) CTitleScene::Create(void)
{
	SHARED(CTitleScene) pCLogoScene(new CTitleScene, Engine::SmartDeleter<CTitleScene>);
	return pCLogoScene;
}

void CTitleScene::Awake(void)
{
	__super::Awake();

	InitLayers();
	InitPrototypes();
}

void CTitleScene::Start(void)
{
	__super::Start();
	
	LoadObject(L"TitleScene");

	{
		m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();
	}

}

_uint CTitleScene::FixedUpdate(void)
{
	__super::FixedUpdate();

	return NO_EVENT;
}

_uint CTitleScene::Update(void)
{
	_uint event = 0;
	if (event = __super::Update())
		return event;

	if (Engine::CInputManager::GetInstance()->KeyDown(KEY_Q))
	{
		NextScene();
	}

	return event;
}

_uint CTitleScene::LateUpdate(void)
{
	_uint event = 0;
	if (event = __super::LateUpdate())
		return event;

	return event;
}

void CTitleScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CTitleScene::OnEnable(void)
{
}

void CTitleScene::OnDisable(void)
{
}

void CTitleScene::InitLayers(void)
{
	AddLayer(L"Camera");
	AddLayer(L"Default");
	AddLayer(L"UI");

}

void CTitleScene::InitPrototypes(void)
{

}

void CTitleScene::NextScene()
{
	Engine::CSceneManager::GetInstance()->SceneChange(CMainRoomScene::Create());
}


