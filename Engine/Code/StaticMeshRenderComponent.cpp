#include "EngineStdafx.h"
#include "StaticMeshRenderComponent.h"
#include "DeviceManager.h"
#include "StaticMeshRenderManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ShaderStore.h"

USING(Engine)
CStaticMeshRenderComponent::CStaticMeshRenderComponent(void)
{
}

CStaticMeshRenderComponent::~CStaticMeshRenderComponent(void)
{
}

SHARED(CComponent) CStaticMeshRenderComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CStaticMeshRenderComponent) pClone(new CStaticMeshRenderComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	pClone->SetRenderID(m_renderID);
	pClone->SetShader(m_shader);

	return pClone;
}

void CStaticMeshRenderComponent::Awake(void)
{
	__super::Awake();
}

void CStaticMeshRenderComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	m_mesh = m_pOwner->GetComponent<CMeshComponent>();

	if (m_shader)
	{
		m_shader->State();
		m_shader->SetGameObject(GetOwner());
	}
}

_uint CStaticMeshRenderComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CStaticMeshRenderComponent::Update(SHARED(CComponent) spThis /* Shared pointer of current component*/)
{
	return _uint();
}

_uint CStaticMeshRenderComponent::LateUpdate(SHARED(CComponent) spThis)
{
	CStaticMeshRenderManager::GetInstance()->AddToRenderList(m_renderID, std::dynamic_pointer_cast<CStaticMeshRenderComponent>(spThis));
	return NO_EVENT;
}

_uint CStaticMeshRenderComponent::PreRender(void)
{
	if (m_mesh == nullptr)
		MSG_BOX(__FILE__, L"m_pMesh is nullptr");

	GET_DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GET_DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	GET_DEVICE->SetTransform(D3DTS_WORLD, &GetOwner()->GetWorldMatrix());
	GET_DEVICE->SetTransform(D3DTS_VIEW, &GET_CUR_SCENE->GetMainCamera()->GetViewMatrix());
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());

	if (m_shader)
	{
		m_shader->PreRender();
		m_shader->ShaderReady();
	}


	return NO_EVENT;
}

_uint CStaticMeshRenderComponent::Render(void)
{
	for (_ulong i = 0; i < m_mesh->GetMeshData()->materialsCount; i++)
	{
		GET_DEVICE->SetTexture(0, m_mesh->GetMeshData()->texture[i]);
		m_mesh->GetMeshData()->mesh->DrawSubset(i);
	}

	return _uint();
}

_uint CStaticMeshRenderComponent::PostRender(void)
{
	if (m_shader)
		m_shader->ShaderEnd();

	return _uint();
}

void CStaticMeshRenderComponent::OnDestroy(void)
{

}

void CStaticMeshRenderComponent::OnEnable(void)
{
	__super::OnEnable();
}


void CStaticMeshRenderComponent::OnDisable(void)
{

}