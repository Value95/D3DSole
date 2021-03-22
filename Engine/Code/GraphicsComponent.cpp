#include "EngineStdafx.h"
#include "GraphicsComponent.h"
#include "DeviceManager.h"
#include "GraphicsManager.h"
#include "SceneManager.h"
#include "Scene.h"

USING(Engine)
CGraphicsComponent::CGraphicsComponent(void)  
{
}

CGraphicsComponent::~CGraphicsComponent(void)
{
}

SHARED(CComponent) CGraphicsComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CGraphicsComponent) pClone(new CGraphicsComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	pClone->SetRenderID(m_renderID);

	return pClone;
}
void CGraphicsComponent::Awake(void)
{
	__super::Awake();
}

void CGraphicsComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	m_pMesh = m_pOwner->GetComponent<CMeshComponent>();
	m_pTexture = m_pOwner->GetComponent<CTextureComponent>();
}

_uint CGraphicsComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CGraphicsComponent::Update(SHARED(CComponent) spThis /* Shared pointer of current component*/)
{
	return _uint();
}

_uint CGraphicsComponent::LateUpdate(SHARED(CComponent) spThis)
{
	CGraphicsManager::GetInstance()->
		AddToRenderList(m_renderID, std::dynamic_pointer_cast<CGraphicsComponent>(spThis));
	return NO_EVENT;
}

_uint CGraphicsComponent::PreRender(void)
{
	if (m_pMesh == nullptr)
		MSG_BOX(__FILE__, L"m_pMesh is nullptr");

	GET_DEVICE->SetStreamSource(0, m_pMesh->GetMeshData()->vertexBuffer, 0, m_pMesh->GetMeshData()->vertexSize);
	GET_DEVICE->SetFVF(m_pMesh->GetMeshData()->FVF);
	GET_DEVICE->SetIndices(m_pMesh->GetMeshData()->indexBuffer);

	if (m_pTexture != nullptr)
		GET_DEVICE->SetTexture(0, m_pTexture->GetTexData()->pTexture);
	else
		GET_DEVICE->SetTexture(0, nullptr);

	GET_DEVICE->SetTransform(D3DTS_WORLD, &GetOwner()->GetWorldMatrix());
	GET_DEVICE->SetTransform(D3DTS_VIEW, &GET_CUR_SCENE->GetMainCamera()->GetViewMatrix());
	GET_DEVICE->SetTransform(D3DTS_PROJECTION, &GET_CUR_SCENE->GetMainCamera()->GetProjMatrix());

	return NO_EVENT;
}

_uint CGraphicsComponent::Render(void)
{
	GET_DEVICE->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		0,
		GetMesh()->GetMeshData()->vertexCount,
		0,
		GetMesh()->GetMeshData()->faceCount
	);

	return _uint();
}

_uint CGraphicsComponent::PostRender(void)
{
	return _uint();
}

void CGraphicsComponent::OnDestroy(void)
{
}

void CGraphicsComponent::OnEnable(void)
{
	__super::OnEnable();
}


void CGraphicsComponent::OnDisable(void)
{
}