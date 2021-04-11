#include "EngineStdafx.h"
#include "AnimComponent.h"

USING(Engine)
CAnimComponent::CAnimComponent()
{
}


CAnimComponent::~CAnimComponent(void)
{
}

SHARED(CComponent) CAnimComponent::MakeClone(CGameObject* pObject)
{
	SHARED(CAnimComponent) pClone(new CAnimComponent);
	pClone->SetOwner(pObject);
	pClone->SetName(m_name);

	pClone->SetIsAwaked(m_isAwaked);

	return pClone;
}

void CAnimComponent::Awake(void)
{
	__super::Awake();
}


void CAnimComponent::Start(SHARED(CComponent) spThis)
{
	__super::Start(spThis);
}

_uint CAnimComponent::FixedUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CAnimComponent::Update(SHARED(CComponent) spThis)
{
	return _uint();
}

_uint CAnimComponent::LateUpdate(SHARED(CComponent) spThis)
{
	return _uint();
}

void CAnimComponent::OnDestroy(void)
{
}

void CAnimComponent::OnEnable(void)
{
}

void CAnimComponent::OnDisable(void)
{
}
