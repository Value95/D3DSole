#include "EngineStdafx.h"
#include "BoxCollider.h"
#include "ColliderManager.h"
#include "GameObject.h"

USING(Engine)
CBoxCollider::CBoxCollider(void)
{
}

CBoxCollider::~CBoxCollider(void)
{
}

CBoxCollider* CBoxCollider::Create(vector3 boxSize, vector3 position)
{
	CBoxCollider* box = new CBoxCollider();
	box->SetBoxSize(boxSize);
	box->SetOffset(position);
	box->Awake();

	return box;
}

void CBoxCollider::Awake(void)
{
	__super::Awake();
	m_colliderType = (_int)EColliderType::Box;
	
}

void CBoxCollider::OnDestroy(void)
{
}

void CBoxCollider::OnEnable(void)
{
}

void CBoxCollider::OnDisable(void)
{
}
