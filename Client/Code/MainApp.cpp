#include "stdafx.h"
#include "MainApp.h"

#pragma region IncludeScenes
#include "TitleScene.h"
#include "DongilScene.h"
#pragma endregion

#include "CameraMove.h"

#pragma region Monster
#include "ScarecrowIdle.h"
#include "SanwaMoneyIdle.h"
#pragma endregion

#pragma region Shader
#include "ShaderMesh.h"
#pragma endregion

#include "ParticleBlood.h"

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
	Engine::CFontManager::GetInstance()->Awake();
}

void CMainApp::Start(void)
{
	InitStaticPrototype();

	Engine::CObjectFactory::GetInstance()->Start();
	Engine::CStaticMeshRenderManager::GetInstance()->Start();
	Engine::CAnimMeshRenderManager::GetInstance()->Start();
	Engine::CInputManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->Start();
	Engine::CSceneManager::GetInstance()->SceneChange(CTitleScene::Create());
	Engine::CUIManager::GetInstance()->Start();
	Engine::CDebugRendeerManager::GetInstance()->Start();
	Engine::CColliderManager::GetInstance()->Start();
	Engine::CFontManager::GetInstance()->Start();
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

	if (event = Engine::CFontManager::GetInstance()->PreRender())	return event;
	if (event = Engine::CFontManager::GetInstance()->Render())	return event;

	return event;
}

_uint CMainApp::PostRender(void)
{
	_uint event = NO_EVENT;
	if (event = Engine::CStaticMeshRenderManager::GetInstance()->PostRender())	return event;
	if (event = Engine::CAnimMeshRenderManager::GetInstance()->PostRender())	return event;
	if (event = Engine::CUIManager::GetInstance()->PostRender())		return event;
	if (event = Engine::CDebugRendeerManager::GetInstance()->PostRender())	return event;
	if (event = Engine::CFontManager::GetInstance()->PostRender())	return event;
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
	Engine::CFontManager::GetInstance()->DestroyInstance();
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
	pCamera->AddComponent<CCameraMove>();
	pCamera->AddComponent<CCameraShake>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(pCamera);

	Default();
	Light();
	UI();
	Monster();
	Player();
	Interaction();
	Npc();
	Particle();
}

void CMainApp::Default()
{
	SHARED(Engine::CGameObject) default = Engine::CGameObject::Create(L"Default", L"Default", true);
	Engine::CObjectFactory::GetInstance()->AddPrototype(default);

	SHARED(Engine::CGameObject) collider = Engine::CGameObject::Create(L"Collider", L"Collider", true);
	Engine::CObjectFactory::GetInstance()->AddPrototype(collider);

	SHARED(Engine::CGameObject) navMesh = Engine::CGameObject::Create(L"NavMesh", L"NavMesh", true);
	navMesh->AddComponent<Engine::CSphereComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(navMesh);

	SHARED(Engine::CGameObject) map = Engine::CGameObject::Create(L"Map", L"Map", true);
	map->AddComponent<Engine::CMeshComponent>();
	map->AddComponent<Engine::CStaticMeshRenderComponent>()->SetShader(new CShaderMesh());
	Engine::CObjectFactory::GetInstance()->AddPrototype(map);
}

void CMainApp::Light()
{
	SHARED(Engine::CGameObject) directionalLight = Engine::CGameObject::Create(L"Light", L"DirectionalLight", true);
	directionalLight->SetName(L"DirectionalLight");
	directionalLight->AddComponent<Engine::CDirectionalLightComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(directionalLight);
}

void CMainApp::UI()
{
	SHARED(Engine::CGameObject) ui = Engine::CGameObject::Create(L"UI", L"UI", true);
	ui->AddComponent<Engine::CUIComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(ui);

	SHARED(Engine::CGameObject) worldUi = Engine::CGameObject::Create(L"UI", L"WorldUI", true);
	worldUi->AddComponent<Engine::CWorldUIComponent>();
	Engine::CObjectFactory::GetInstance()->AddPrototype(worldUi);
}

void CMainApp::Monster()
{
	SHARED(Engine::CGameObject) scarecrow = Engine::CGameObject::Create(L"Monster", L"Scarecrow", true);
	scarecrow->SetName(L"Scarecrow");
	scarecrow->SetScale(vector3(0.01f, 0.01f, 0.01f));
	scarecrow->AddComponent<CMonster>()->AddFSM<CScarecrowIdle>();
	scarecrow->AddComponent<Engine::CMeshComponent>();
	scarecrow->AddComponent<Engine::CStaticMeshRenderComponent>();
	scarecrow->AddComponent<Engine::CParticleSystem>()->Init(L"Cat", 5, 5, vector3Zero);
	Engine::CObjectFactory::GetInstance()->AddPrototype(scarecrow);

	SHARED(Engine::CGameObject) sanwaMoney = Engine::CGameObject::Create(L"Boss", L"SanwaMoney", true);
	sanwaMoney->SetName(L"SanwaMoney");
	sanwaMoney->SetPosition(vector3(0, 0, 0));
	sanwaMoney->SetScale(vector3(0.01f, 0.01f, 0.01f));
	sanwaMoney->AddComponent<CMonster>()->AddFSM<CSanwaMoneyIdle>();
	sanwaMoney->AddComponent<Engine::CRigidBodyComponent>();
	sanwaMoney->GetComponent<Engine::CRigidBodyComponent>()->SetBounciness(0.0f);
	sanwaMoney->GetComponent<Engine::CRigidBodyComponent>()->SetMass(80);
	sanwaMoney->AddComponent<Engine::CParticleSystem>()->Init(L"Blood", 2, 15, vector3Up * 2.5);
	sanwaMoney->AddComponent<Engine::CAnimMeshRenderComponent>()->MeshInput(L"../../Resource/Mesh/Static/DynamicMesh/Boss/AgentSanwaMoney/", L"Boss_AgentSanwaMoney_000.X");
	Engine::CObjectFactory::GetInstance()->AddPrototype(sanwaMoney);
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
	player->AddComponent<Engine::CAnimMeshRenderComponent>()->MeshInput(L"../../Resource/Mesh/Static/DynamicMesh/Player/", L"Player_Player_000.X");
	player->GetComponent<Engine::CAnimMeshRenderComponent>()->SetShader(new CShaderMesh());
	Engine::CObjectFactory::GetInstance()->AddPrototype(player);

}

void CMainApp::Interaction()
{
	SHARED(Engine::CGameObject) CSPStatue = Engine::CGameObject::Create(L"Interaction", L"CSPStatue", true);
	CSPStatue->AddComponent<Engine::CMeshComponent>();
	CSPStatue->AddComponent<Engine::CStaticMeshRenderComponent>()->SetShader(new CShaderMesh());
	Engine::CObjectFactory::GetInstance()->AddPrototype(CSPStatue);

	SHARED(Engine::CGameObject) SMStatue = Engine::CGameObject::Create(L"Interaction", L"SMStatue", true);
	SMStatue->AddComponent<Engine::CMeshComponent>();
	SMStatue->AddComponent<Engine::CStaticMeshRenderComponent>()->SetShader(new CShaderMesh());
	Engine::CObjectFactory::GetInstance()->AddPrototype(SMStatue);
}

void CMainApp::Npc()
{
	SHARED(Engine::CGameObject) MuscleMan = Engine::CGameObject::Create(L"NPC", L"MuscleMan", true);
	MuscleMan->SetName(L"MuscleMan");
	MuscleMan->SetPosition(vector3(0, 0, 0));
	MuscleMan->SetScale(vector3(0.01f, 0.01f, 0.01f));
	MuscleMan->AddComponent<Engine::CColliderComponent>()->SetIsTrigger(false);
	MuscleMan->AddComponent<Engine::CAnimMeshRenderComponent>()->MeshInput(L"../../Resource/Mesh/Static/DynamicMesh/NPC/MuscleMan/", L"NPC_MuscleMan.X");
	Engine::CObjectFactory::GetInstance()->AddPrototype(MuscleMan);
}

void CMainApp::Particle()
{
	SHARED(Engine::CGameObject) blood = Engine::CGameObject::Create(L"Particle", L"Blood", true);
	blood->SetScale(vector3(0.01f, 0.01f, 0.01f));
	blood->SetIsEnabled(false);
	blood->AddComponent<CParticleBlood>()->SetForce(vector3(5, 5, 5));
	blood->AddComponent<Engine::CRigidBodyComponent>();
	blood->GetComponent<Engine::CRigidBodyComponent>()->SetBounciness(0.0f);
	blood->GetComponent<Engine::CRigidBodyComponent>()->SetMass(80);
	blood->AddComponent<Engine::CMeshComponent>()->SetMeshKey(L"sphere.X");
	blood->AddComponent<Engine::CStaticMeshRenderComponent>()->SetShader(new CShaderMesh());
	Engine::CObjectFactory::GetInstance()->AddPrototype(blood);

	SHARED(Engine::CGameObject) cat = Engine::CGameObject::Create(L"Particle", L"Cat", true);
	cat->SetScale(vector3(0.005f, 0.005f, 0.005f));
	cat->SetIsEnabled(false);
	cat->AddComponent<CParticleBlood>()->SetForce(vector3(8,8,8));
	cat->AddComponent<Engine::CRigidBodyComponent>();
	cat->GetComponent<Engine::CRigidBodyComponent>()->SetBounciness(0.0f);
	cat->GetComponent<Engine::CRigidBodyComponent>()->SetMass(80);
	cat->AddComponent<Engine::CMeshComponent>()->SetMeshKey(L"Cat.X");
	cat->AddComponent<Engine::CStaticMeshRenderComponent>()->SetShader(new CShaderMesh());
	Engine::CObjectFactory::GetInstance()->AddPrototype(cat);
}
