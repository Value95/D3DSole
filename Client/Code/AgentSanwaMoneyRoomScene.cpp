#include "stdafx.h"
#include "AgentSanwaMoneyRoomScene.h"

CAgentSanwaMoneyRoomScene::CAgentSanwaMoneyRoomScene()
{
}


CAgentSanwaMoneyRoomScene::~CAgentSanwaMoneyRoomScene()
{
}

SHARED(Engine::CScene) CAgentSanwaMoneyRoomScene::Create(void)
{
	SHARED(CAgentSanwaMoneyRoomScene) pCLogoScene(new CAgentSanwaMoneyRoomScene, Engine::SmartDeleter<CAgentSanwaMoneyRoomScene>);
	return pCLogoScene;
}

void CAgentSanwaMoneyRoomScene::Awake(void)
{
	__super::Awake();

	InitLayers();
	InitPrototypes();
}

void CAgentSanwaMoneyRoomScene::Start(void)
{
	__super::Start();

	{
		m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();
	}
}

_uint CAgentSanwaMoneyRoomScene::FixedUpdate(void)
{
	__super::FixedUpdate();

	return _uint();
}

_uint CAgentSanwaMoneyRoomScene::Update(void)
{
	_uint event = 0;
	if (event = __super::Update())
		return event;

	return event;
}

_uint CAgentSanwaMoneyRoomScene::LateUpdate(void)
{
	_uint event = 0;
	if (event = __super::LateUpdate())
		return event;

	return event;
}

void CAgentSanwaMoneyRoomScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CAgentSanwaMoneyRoomScene::OnEnable(void)
{
}

void CAgentSanwaMoneyRoomScene::OnDisable(void)
{
}

void CAgentSanwaMoneyRoomScene::InitLayers(void)
{
	AddLayer(L"Camera");
	AddLayer(L"Player");
	AddLayer(L"EventBlock");
	AddLayer(L"Default");
}

void CAgentSanwaMoneyRoomScene::InitPrototypes(void)
{

}