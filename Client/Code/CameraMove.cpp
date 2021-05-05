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