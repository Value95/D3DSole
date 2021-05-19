#include "stdafx.h"
#include "LoddingScene.h"
#include "DongilScene.h"
#include "MainRoomScene.h"
CLoddingScene::CLoddingScene()
{
}


CLoddingScene::~CLoddingScene()
{
}

SHARED(Engine::CScene) CLoddingScene::Create(std::wstring nextScene)
{
	SHARED(CLoddingScene) pCLogoScene(new CLoddingScene, Engine::SmartDeleter<CLoddingScene>);
	pCLogoScene->SetNextScene(nextScene);

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

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, CLoddingScene::LoadDataObject, this, 0, nullptr);

	m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();

}

_uint CLoddingScene::FixedUpdate(void)
{
	__super::FixedUpdate();

	return NO_EVENT;
}

_uint CLoddingScene::Update(void)
{
	_uint event = 0;
	if (event = __super::Update())
		return event;

	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);


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
	AddLayer(L"Light");
	AddLayer(L"Camera");
	AddLayer(L"Player");
	AddLayer(L"Default");
	AddLayer(L"Boss");
	AddLayer(L"Monster");
	AddLayer(L"UI");
	AddLayer(L"Collider");
	AddLayer(L"Map");
	AddLayer(L"Interaction");
	AddLayer(L"NPC");
}

void CLoddingScene::InitPrototypes(void)
{

}

unsigned CLoddingScene::LoadDataObject(LPVOID pArg)
{
	CLoddingScene* pLoad = static_cast<CLoddingScene*>(pArg);

	cout << "로딩 시작" << endl;

	if (pLoad->m_nextScene == L"CDolngilScene")
	{
		Engine::CSceneManager::GetInstance()->SceneChange(CDongilScene::Create());

	}
	else if (pLoad->m_nextScene == L"MainRoom")
	{
		Engine::CSceneManager::GetInstance()->SceneChange(CMainRoomScene::Create());
	}

	cout << "로딩 끝" << endl;

	return 0;
}
