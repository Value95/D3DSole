#include "EngineStdafx.h"
#include "BoxComponent.h"
#include "DeviceManager.h"
#include "GameObject.h"
#include "DebugRendeerManager.h"

#include "SceneManager.h"

USING(Engine)
CBoxComponent::CBoxComponent()  
{
}


CBoxComponent::~CBoxComponent(void)
{
}

SHARED(CComponent) CBoxComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CBoxComponent) pClone(new CBoxComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetSize(m_size);
	pClone->SetOffSet(m_offSet);

	pClone->SetIsAwaked(m_isAwaked);


	return pClone;
}

void CBoxComponent::Awake(void)
{
	__super::Awake();
}


void CBoxComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	m_mesh = nullptr;
	DateInit();
}

_uint CBoxComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CBoxComponent::Update(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CBoxComponent::LateUpdate(SHARED(CComponent) spThis)
{
	CDebugRendeerManager::GetInstance()->AddToBoxRenderList(dynamic_pointer_cast<CBoxComponent>(spThis));

	return NO_EVENT;
}

_uint CBoxComponent::PreRender(void)
{
	// 데이터 셋팅
	if (GetOwner() == nullptr)
		MSG_BOX(__FILE__, L"Owner is nullptr");

	//좌표셋팅

	GET_DEVICE->SetTransform(D3DTS_WORLD, &GetOwner()->GetWorldMatrix());
	GET_DEVICE->SetTransform(D3DTS_VIEW, &GET_CUR_SCENE->GetMainCamera()->GetViewMatrix());
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());

	GET_DEVICE->SetTexture(0, nullptr);

	return _uint();
}

_uint CBoxComponent::Render(void)
{
	if(m_mesh != nullptr)
		m_mesh->Release();

	/*GetOwner()->OutTranslate(m_size);
	GetOwner()->OutTranslate(m_offSet);*/

	D3DXCreateBox(GET_DEVICE, m_size.x + m_offSet.x, m_size.y + m_offSet.y, m_size.z + m_offSet.z, &m_mesh, NULL); // D3D 함수

	m_mesh->DrawSubset(0);

	return _uint();
}

_uint CBoxComponent::PostRender(void)
{
	return _uint();
}

void CBoxComponent::OnDestroy(void)
{
}

void CBoxComponent::OnEnable(void)
{
}

void CBoxComponent::OnDisable(void)
{
}

void CBoxComponent::DateInit()
{
	// FVF를 지정하여 보관할 데이터의 형식을 지정하고 사용자 정점을 보관할 메모리할당
	GET_DEVICE->CreateVertexBuffer(4 * sizeof(_CustomVertex), 0, customFVF, D3DPOOL_MANAGED, &m_meshDate.vertexBuffer, NULL);
}
