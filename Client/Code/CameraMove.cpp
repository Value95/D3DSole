#include "stdafx.h"
#include "CameraMove.h"

CCameraMove::CCameraMove()
{
}

CCameraMove::~CCameraMove(void)
{
	OnDestroy();
}

SHARED(Engine::CComponent) CCameraMove::MakeClone(Engine::CGameObject* pObject)
{
	SHARED(CCameraMove) pClone(new CCameraMove);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);


	return pClone;
}

void CCameraMove::Awake(void)
{
	__super::Awake();

}

void CCameraMove::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
}

_uint CCameraMove::FixedUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

_uint CCameraMove::Update(SHARED(CComponent) spThis)
{
	/*vector3 orgine = GetOwner()->GetPosition();
	vector3 dir = GetOwner()->GetTarget()->GetPosition() - GetOwner()->GetPosition();
	D3DXVec3Normalize(&dir, &dir);
	_float distance = Engine::Distance(orgine, GetOwner()->GetTarget()->GetPosition());
	vector3 outHit;
	Engine::CGameObject* obj = Engine::CRaycast::MeshRayCast(orgine, dir, distance, L"Map", outHit);

	if (obj == nullptr)
	{
		GetOwner()->SetCameraDirPos(vector3(0, 3, -8));
	}
	else
	{
		vector3 a = orgine - outHit;
		GetOwner()->SetCameraDirPos(orgine - outHit);
	}*/

	return NO_EVENT;
}

_uint CCameraMove::LateUpdate(SHARED(CComponent) spThis)
{
	return NO_EVENT;
}

void CCameraMove::OnDestroy(void)
{
}

void CCameraMove::OnEnable(void)
{
}

void CCameraMove::OnDisable(void)
{
}