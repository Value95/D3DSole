#include "EngineStdafx.h"
#include "ColliderComponent.h"
#include "Collider.h"
#include "ColliderManager.h"
#include "GameObject.h"
USING(Engine)

CColliderComponent::CColliderComponent(void)
{
}

CColliderComponent::~CColliderComponent(void)
{
	OnDestroy();
}

SHARED(CComponent) CColliderComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CColliderComponent) pClone(new CColliderComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);
	pClone->SetIsAwaked(m_isAwaked);
	pClone->SetColliders(m_vColliders);
	pClone->SetIsTrigger(m_isTrigger);
	return pClone;
}

void CColliderComponent::Awake(void)
{
	__super::Awake();
}

void CColliderComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
	/*CBoxCollider* a = static_cast<CBoxCollider*>(m_vColliders[0]);
	GetOwner()->AddComponent<CBoxComponent>()->SetSize(a->GetBoxSize() * 1000);
	GetOwner()->GetComponent<CBoxComponent>()->SetOffSet(a->GetOffset());*/
	CColliderManager::GetInstance()->ColliderInput(std::dynamic_pointer_cast<CColliderComponent>(spThis));
}

_uint CColliderComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CColliderComponent::Update(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CColliderComponent::LateUpdate(SHARED(CComponent) spSelf)
{
	return _uint();
}

void CColliderComponent::OnDestroy(void)
{
	for (int i = 0; i < m_vColliders.size(); i++)
	{
		SAFE_DELETE(m_vColliders[i]);
	}
}

void CColliderComponent::OnEnable(void)
{
}

void CColliderComponent::OnDisable(void)
{

}

CColliderComponent* CColliderComponent::AddCollider(CCollider* collider)
{
	m_vColliders.emplace_back(collider);
	return this;
}

