#include "EngineStdafx.h"
#include "SphereCollider.h"
#include "ColliderManager.h"
#include "GameObject.h"

USING(Engine)
CSphereCollider::CSphereCollider(void)
{
}

CSphereCollider::~CSphereCollider(void)
{
}

CSphereCollider * CSphereCollider::Create(_float radius, _bool active)
{
	CSphereCollider* pSphere = new CSphereCollider();
	pSphere->m_radius = radius;
	pSphere->SetActive(active);
	pSphere->Awake();

	return pSphere;
}

void CSphereCollider::Awake(void)
{
	__super::Awake();
	m_colliderType = (_int)EColliderType::Sphere;
}

void CSphereCollider::OnDestroy(void)
{
}

void CSphereCollider::OnEnable(void)
{
}

void CSphereCollider::OnDisable(void)
{
}