#include "EngineStdafx.h"
#include "SphereComponent.h"
#include "DeviceManager.h"
#include "GameObject.h"
#include "DebugRendeerManager.h"
#include "StaticMeshRenderManager.h"

#include "SceneManager.h"

USING(Engine)
CSphereComponent::CSphereComponent()  
{
}


CSphereComponent::~CSphereComponent(void)
{
}

SHARED(CComponent) CSphereComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CSphereComponent) pClone(new CSphereComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	return pClone;
}

void CSphereComponent::Awake(void)
{
	__super::Awake();
}


void CSphereComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	m_mesh = nullptr;
}

_uint CSphereComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CSphereComponent::Update(SHARED(CComponent) spThis)
{

	return NO_EVENT;
}

_uint CSphereComponent::LateUpdate(SHARED(CComponent) spThis)
{
	CDebugRendeerManager::GetInstance()->AddToSphereRenderList(dynamic_pointer_cast<CSphereComponent>(spThis));
	return NO_EVENT;
}

_uint CSphereComponent::PreRender(void)
{
	// 데이터 셋팅
	if (GetOwner() == nullptr)
		MSG_BOX(__FILE__, L"Owner is nullptr");

	//좌표셋팅

	GET_DEVICE->SetTransform(D3DTS_WORLD, &GetOwner()->GetWorldMatrix());
	GET_DEVICE->SetTransform(D3DTS_VIEW, &GET_CUR_SCENE->GetMainCamera()->GetViewMatrix());
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());

	return _uint();
}

_uint CSphereComponent::Render(void)
{
	if (m_mesh == nullptr)
		m_mesh->Release();

	D3DXCreateSphere(GET_DEVICE, radus, 30, 30, &m_mesh, NULL); // D3D 함수

	m_mesh->DrawSubset(0);

	return _uint();
}

_uint CSphereComponent::PostRender(void)
{
	return _uint();
}

void CSphereComponent::OnDestroy(void)
{
}

void CSphereComponent::OnEnable(void)
{
}

void CSphereComponent::OnDisable(void)
{
}
