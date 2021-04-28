#include "stdafx.h"
#include "MainRoomScene.h"

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

	{
		m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();
	}
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
	AddLayer(L"Camera");
	AddLayer(L"Player");
	AddLayer(L"EventBlock");
	AddLayer(L"Default");
}

void CMainRoomScene::InitPrototypes(void)
{

}