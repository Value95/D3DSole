#include "stdafx.h"
#include "MainApp.h"

#pragma region IncludeScenes
#include "DongilScene.h"
#pragma endregion

CMainApp::CMainApp(void)
{
}

CMainApp::~CMainApp(void)
{
}

SHARED(CMainApp) CMainApp::Create(void)
{
	SHARED(CMainApp) pMainApp(new CMainApp, Engine::SmartDeleter<CMainApp>);

	return pMainApp;
}
void CMainApp::Awake(void)
{
	ClientSetting();
	srand((unsigned)time(NULL));

	Engine::CObjectFactory::GetInstance()->Awake();
	Engine::CStaticMeshRenderManager::GetInstance()->Awake();
	Engine::CAnimMeshRenderManager::GetInstance()->Awake();
	Engine::CInputManager::GetInstance()->Awake();
	Engine::CSceneManager::GetInstance()->Awake();
	Engine::CUIManager::GetInstance()->Awake();
	Engine::CDebugRendeerManager::GetInstance()->Awake();
	Engine::CColliderManager::GetInstance()->Awake();
	Engine::CSoundManager::GetInstance()->Awake();
}

void CMainApp::Start(void)
{
	InitStaticPrototype();

	Engine::CObjectFactory::GetInstance()->Start();
	Engine::CStaticMeshRenderManager::GetInstance()->Start();
	Engine::CAnimMeshRenderManager::GetInstance()->Start();
	Engine::CInputManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->SceneChange(CDongilScene::Create());
	Engine::CUIManager::GetInstance()->Start();
	Engine::CDebugRendeerManager::GetInstance()->Start();
	Engine::CColliderManager::GetInstance()->Start();
}

_uint CMainApp::FixedUpdate(void)
{
	_uint event = NO_EVENT;

	if (event = Engine::CStaticMeshRenderManager::GetInstance()->FixedUpdate())	return event;
	if (event = Engine::CAnimMeshRenderManager::GetInstance()->FixedUpdate())	return event;
	if (event = Engine::CInputManager::GetInstance()->FixedUpdate())	return event;
	if (event = Engine::CSceneManager::GetInstance()->FixedUpdate())	return event;

	return event;
}

_uint CMainApp::Update(void)
{
	_uint event = NO_EVENT;

	if (event = Engine::CStaticMeshRenderManager::GetInstance()->Update())	return event;
	if (event = Engine::CAnimMeshRenderManager::GetInstance()->Update())	return event;
	if (event = Engine::CInputManager::GetInstance()->Update())		return event;
	if (event = Engine::CSceneManager::GetInstance()->Update())		return event;
	return event;
}

_uint CMainApp::LateUpdate(void)
{
	_uint event = NO_EVENT;
	if (event = Engine::CStaticMeshRenderManager::GetInstance()->LateUpdate())	return event;
	if (event = Engine::CAnimMeshRenderManager::GetInstance()->LateUpdate())	return event;
	if (event = Engine::CInputManager::GetInstance()->LateUpdate())		return event;
	if (event = Engine::CSceneManager::GetInstance()->LateUpdate())		return event;
	if (event = Engine::CColliderManager::GetInstance()->LateUpdate())	return event;
	return event;
}



_uint CMainApp::Render(void)
{
	_uint event = NO_EVENT;
	
	if (event = Engine::CStaticMeshRenderManager::GetInstance()->PreRender())	return event;
	if (event = Engine::CStaticMeshRenderManager::GetInstance()->Render())	return event;

	if (event = Engine::CAnimMeshRenderManager::GetInstance()->PreRender())	return event;
	if (event = Engine::CAnimMeshRenderManager::GetInstance()->Render())	return event;

	if (event = Engine::CUIManager::GetInstance()->PreRender())	return event;
	if (event = Engine::CUIManager::GetInstance()->Render())		return event;

	if (event = Engine::CDebugRendeerManager::GetInstance()->PreRender())	return event;
	if (event = Engine::CDebugRendeerManager::GetInstance()->Render())	return event;

	return event;
}

_uint CMainApp::PostRender(void)
{
	_uint event = NO_EVENT;
	if (event = Engine::CStaticMeshRenderManager::GetInstance()->PostRender())	return event;
	if (event = Engine::CAnimMeshRenderManager::GetInstance()->PostRender())	return event;
	if (event = Engine::CUIManager::GetInstance()->PostRender())		return event;
	if (event = Engine::CDebugRendeerManager::GetInstance()->PostRender())	return event;
	return event;
}

void CMainApp::OnDestroy(void)
{
	Engine::CStaticMeshRenderManager::GetInstance()->DestroyInstance();
	Engine::CAnimMeshRenderManager::GetInstance()->DestroyInstance();
	Engine::CInputManager::GetInstance()->DestroyInstance();
	Engine::CSceneManager::GetInstance()->DestroyInstance();
	Engine::CObjectFactory::GetInstance()->DestroyInstance();
	Engine::CColliderManager::GetInstance()->DestroyInstance();
	Engine::CSoundManager::GetInstance()->DestroyInstance();
	Engine::CDebugRendeerManager::DestroyInstance();
	Engine::CUIManager::GetInstance()->DestroyInstance();
}

void CMainApp::OnEnable(void)
{

}

void CMainApp::OnDisable(void)
{
}

void CMainApp::ClientSetting()
{
	ShowCursor(false);
}

void CMainApp::InitStaticPrototype(void)
{
	SHARED(Engine::CGameObject) pCamera = Engine::CGameObject::Create(L"Camera", L"Camera", true);
	pCamera->SetPosition(vector3(0, 0, 0));
	pCamera->SetRotation(vector3Zero);
	pCamera->AddComponent<Engine::CCameraComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(pCamera);

	Default();
	Light();
	UI();
	Monster();
	Player();
}
// LayerKey 는 중첩 가능
// ObjectKey 는 중첩 불가능
void CMainApp::Default()
{
	SHARED(Engine::CGameObject) pDefault = Engine::CGameObject::Create(L"Default", L"Default", true);
	Engine::CObjectFactory::GetInstance()->AddPrototype(pDefault);

	SHARED(Engine::CGameObject) mess = Engine::CGameObject::Create(L"Default", L"Mess", true);
	mess->AddComponent<Engine::CStaticMeshRenderComponent>();
	mess->AddComponent<Engine::CMeshComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(mess);

	SHARED(Engine::CGameObject) collider = Engine::CGameObject::Create(L"Collider", L"Collider", true);
	Engine::CObjectFactory::GetInstance()->AddPrototype(collider);

	SHARED(Engine::CGameObject) navMesh = Engine::CGameObject::Create(L"NavMesh", L"NavMesh", true);
	navMesh->AddComponent<Engine::CSphereComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(navMesh);
}

void CMainApp::Light()
{
	SHARED(Engine::CGameObject) directionalLight = Engine::CGameObject::Create(L"Light", L"DirectionalLight", true);
	directionalLight->AddComponent<Engine::CDirectionalLightComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(directionalLight);
}

void CMainApp::UI()
{
	SHARED(Engine::CGameObject) ui = Engine::CGameObject::Create(L"UI", L"UI", true);
	ui->AddComponent<Engine::CUIComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(ui);
}

void CMainApp::Monster()
{
	SHARED(Engine::CGameObject) scarecrow = Engine::CGameObject::Create(L"Monster", L"Scarecrow", true);
	scarecrow->SetName(L"Scarecrow");
	scarecrow->SetScale(vector3(0.005f, 0.005f, 0.005f));
	scarecrow->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3(1, 10, 1), vector3Zero));
	scarecrow->AddComponent<Engine::CMeshComponent>()->SetMeshKey(L"Boss_CrystalSpider_000.X");
	scarecrow->AddComponent<Engine::CStaticMeshRenderComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(scarecrow);
}

void CMainApp::Player()
{
	SHARED(Engine::CGameObject) player = Engine::CGameObject::Create(L"Player", L"Player", true);
	player->SetName(L"Player");
	player->SetPosition(vector3(0, 0, 0));
	player->SetScale(vector3(0.01f, 0.01f, 0.01f));
	player->AddComponent<Engine::CRigidBodyComponent>();
	player->GetComponent<Engine::CRigidBodyComponent>()->SetBounciness(0.0f);
	player->GetComponent<Engine::CRigidBodyComponent>()->SetMass(80);
	player->AddComponent<CPlayer>();
	player->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3(0.1, 0.6, 0.1), vector3(0, 0.3, 0)));
	player->AddComponent<Engine::CAnimMeshRenderComponent>()->MeshInput(L"../../Resource/Mesh/Static/Player/", L"Player_Player_000.X");
	Engine::CObjectFactory::GetInstance()->AddPrototype(player);

}
