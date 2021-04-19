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
	Engine::CGraphicsManager::GetInstance()->Awake();
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
	Engine::CGraphicsManager::GetInstance()->Start();
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

	if (event = Engine::CGraphicsManager::GetInstance()->FixedUpdate())	return event;
	if (event = Engine::CAnimMeshRenderManager::GetInstance()->FixedUpdate())	return event;
	if (event = Engine::CInputManager::GetInstance()->FixedUpdate())	return event;
	if (event = Engine::CSceneManager::GetInstance()->FixedUpdate())	return event;

	return event;
}

_uint CMainApp::Update(void)
{
	_uint event = NO_EVENT;

	if (event = Engine::CGraphicsManager::GetInstance()->Update())	return event;
	if (event = Engine::CAnimMeshRenderManager::GetInstance()->Update())	return event;
	if (event = Engine::CInputManager::GetInstance()->Update())		return event;
	if (event = Engine::CSceneManager::GetInstance()->Update())		return event;
	return event;
}

_uint CMainApp::LateUpdate(void)
{
	_uint event = NO_EVENT;
	if (event = Engine::CGraphicsManager::GetInstance()->LateUpdate())	return event;
	if (event = Engine::CAnimMeshRenderManager::GetInstance()->LateUpdate())	return event;
	if (event = Engine::CInputManager::GetInstance()->LateUpdate())		return event;
	if (event = Engine::CSceneManager::GetInstance()->LateUpdate())		return event;
	if (event = Engine::CColliderManager::GetInstance()->LateUpdate())	return event;
	return event;
}



_uint CMainApp::Render(void)
{
	_uint event = NO_EVENT;
	
	if (event = Engine::CGraphicsManager::GetInstance()->PreRender())	return event;
	if (event = Engine::CGraphicsManager::GetInstance()->Render())	return event;

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
	if (event = Engine::CGraphicsManager::GetInstance()->PostRender())	return event;
	if (event = Engine::CAnimMeshRenderManager::GetInstance()->PostRender())	return event;
	if (event = Engine::CUIManager::GetInstance()->PostRender())		return event;
	if (event = Engine::CDebugRendeerManager::GetInstance()->PostRender())	return event;
	return event;
}

void CMainApp::OnDestroy(void)
{
	Engine::CGraphicsManager::GetInstance()->DestroyInstance();
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


	SHARED(Engine::CGameObject) pDefault = Engine::CGameObject::Create(L"Default", L"Default", true);
	Engine::CObjectFactory::GetInstance()->AddPrototype(pDefault);

	SHARED(Engine::CGameObject) mess = Engine::CGameObject::Create(L"Default", L"Mess", true);
	mess->AddComponent<Engine::CGraphicsComponent>();
	mess->AddComponent<Engine::CMeshComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(mess);

	SHARED(Engine::CGameObject) directionalLight = Engine::CGameObject::Create(L"Light", L"DirectionalLight", true);
	directionalLight->AddComponent<Engine::CDirectionalLightComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(directionalLight);

	SHARED(Engine::CGameObject) player = Engine::CGameObject::Create(L"Player", L"Player", true);
	player->SetPosition(vector3(0, 0, 0));
	player->SetScale(vector3(0.01f, 0.01f, 0.01f));
	player->AddComponent<Engine::CRigidBodyComponent>();
	player->AddComponent<CPlayer>();
	player->AddComponent<Engine::CColliderComponent>()->AddCollider(Engine::CBoxCollider::Create(vector3(1, 1, 1), vector3Zero));
	player->AddComponent<Engine::CAnimMeshRenderComponent>()->MeshInput(L"../../Resource/Mesh/Static/Boss/CrystalSpider/", L"CrystalSpider.X");
	Engine::CObjectFactory::GetInstance()->AddPrototype(player);

	SHARED(Engine::CGameObject) ui = Engine::CGameObject::Create(L"UI", L"Default", true);
	ui->AddComponent<Engine::CUIComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(ui);

	SHARED(Engine::CGameObject) collider = Engine::CGameObject::Create(L"Collider", L"Collider", true);
	Engine::CObjectFactory::GetInstance()->AddPrototype(collider);

	SHARED(Engine::CGameObject) navMesh = Engine::CGameObject::Create(L"NavMesh", L"NavMesh", true);
	navMesh->AddComponent<Engine::CSphereComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(navMesh);




}