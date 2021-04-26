#include "EngineStdafx.h"
#include "MeshComponent.h"
#include "StaticMeshRenderManager.h"
#include "MeshStore.h"
#include "DataStore.h"
#include "GameObject.h"

USING(Engine)
CMeshComponent::CMeshComponent(void)  
{
}


CMeshComponent::~CMeshComponent(void)
{
}

SHARED(CComponent) CMeshComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CMeshComponent) pClone(new CMeshComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	pClone->SetMeshKey(m_meshKey);
	pClone->SetMeshData(m_pMeshData);

	
	return pClone;
}

void CMeshComponent::Awake(void)
{
	__super::Awake();
}

void CMeshComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	_bool isStatic = m_pOwner->GetIsStatic();
	std::wstring layeKey = m_pOwner->GetLayerKey();
	std::wstring objectKey = m_pOwner->GetObjectKey();

	if (m_meshKey == L"")
		m_meshKey = L"Cube";

	m_pMeshData = CMeshStore::GetInstance()->GetMeshData(m_meshKey);
}

_uint CMeshComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CMeshComponent::Update(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CMeshComponent::LateUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

void CMeshComponent::OnDestroy(void)
{
}

void CMeshComponent::OnEnable(void)
{

}

void CMeshComponent::OnDisable(void)
{
}
