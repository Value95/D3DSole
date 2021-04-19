#include "stdafx.h"
#include "LoddingScene.h"

CLoddingScene::CLoddingScene()
{
}


CLoddingScene::~CLoddingScene()
{
}

SHARED(Engine::CScene) CLoddingScene::Create(void)
{
	SHARED(CLoddingScene) pCLogoScene(new CLoddingScene, Engine::SmartDeleter<CLoddingScene>);
	return pCLogoScene;
}

void CLoddingScene::Awake(void)
{
	__super::Awake();

	InitLayers();
	InitPrototypes();
}

void CLoddingScene::Start(void)
{
	__super::Start();

	{
		m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();
	}
}

_uint CLoddingScene::FixedUpdate(void)
{
	__super::FixedUpdate();

	return _uint();
}

_uint CLoddingScene::Update(void)
{
	_uint event = 0;
	if (event = __super::Update())
		return event;

	return event;
}

_uint CLoddingScene::LateUpdate(void)
{
	_uint event = 0;
	if (event = __super::LateUpdate())
		return event;

	return event;
}

void CLoddingScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CLoddingScene::OnEnable(void)
{
}

void CLoddingScene::OnDisable(void)
{
}

void CLoddingScene::InitLayers(void)
{
	AddLayer(L"Camera");
	AddLayer(L"Player");
	AddLayer(L"EventBlock");
	AddLayer(L"Default");
}

void CLoddingScene::InitPrototypes(void)
{

}