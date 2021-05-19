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

	LoadObject(L"Lodding");
	m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();
	m_pMainCamera->GetOwner()->GetComponent<CCameraMove>()->SetIsEnabled(false);

	m_init = false;
	m_initt = true;
}

_uint CLoddingScene::FixedUpdate(void)
{
	__super::FixedUpdate();
	if (m_init && m_initt)
	{
		m_hThread = (HANDLE)_beginthreadex(nullptr, 0, CLoddingScene::LoadDataObject, this, 0, nullptr);
		m_init = false;
		m_initt = false;
	}
	m_init = true;

	return NO_EVENT;
}

_uint CLoddingScene::Update(void)
{
	_uint event = 0;
	if (event = __super::Update())
		return event;

/*	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);*/

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
	AddLayer(L"Default");
	AddLayer(L"UI");
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
		SHARED(Engine::CScene) scene = CDongilScene::Create();
		Engine::CSceneManager::GetInstance()->SceneChange(scene);

	}
	else if (pLoad->m_nextScene == L"MainRoom")
	{
		SHARED(Engine::CScene) scene = CMainRoomScene::Create();
		Engine::CSceneManager::GetInstance()->SceneChange(scene);
	}

	cout << "로딩 끝" << endl;

	return 0;
}
