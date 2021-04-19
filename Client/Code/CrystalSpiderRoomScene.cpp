#include "stdafx.h"
#include "CrystalSpiderRoomScene.h"

CCrystalSpiderRoomScene::CCrystalSpiderRoomScene()
{
}


CCrystalSpiderRoomScene::~CCrystalSpiderRoomScene()
{
}

SHARED(Engine::CScene) CCrystalSpiderRoomScene::Create(void)
{
	SHARED(CCrystalSpiderRoomScene) pCLogoScene(new CCrystalSpiderRoomScene, Engine::SmartDeleter<CCrystalSpiderRoomScene>);
	return pCLogoScene;
}

void CCrystalSpiderRoomScene::Awake(void)
{
	__super::Awake();

	InitLayers();
	InitPrototypes();
}

void CCrystalSpiderRoomScene::Start(void)
{
	__super::Start();

	{
		m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();
	}
}

_uint CCrystalSpiderRoomScene::FixedUpdate(void)
{
	__super::FixedUpdate();

	return _uint();
}

_uint CCrystalSpiderRoomScene::Update(void)
{
	_uint event = 0;
	if (event = __super::Update())
		return event;

	return event;
}

_uint CCrystalSpiderRoomScene::LateUpdate(void)
{
	_uint event = 0;
	if (event = __super::LateUpdate())
		return event;

	return event;
}

void CCrystalSpiderRoomScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CCrystalSpiderRoomScene::OnEnable(void)
{
}

void CCrystalSpiderRoomScene::OnDisable(void)
{
}

void CCrystalSpiderRoomScene::InitLayers(void)
{
	AddLayer(L"Camera");
	AddLayer(L"Player");
	AddLayer(L"EventBlock");
	AddLayer(L"Default");
}

void CCrystalSpiderRoomScene::InitPrototypes(void)
{

}